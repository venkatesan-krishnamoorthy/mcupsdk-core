/*
 * Copyright (C) 2024-25 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <unity.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/TaskP.h>
#include <drivers/hw_include/csl_types.h>
#include <drivers/hw_include/cslr_fsi_tx.h>
#include <drivers/fsi.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "test_fsi_hld_common.h"
#include "test_fsi_tx_hld_task.h"

/* ========================================================================== */
/*                         Global Varialbe Declarations                       */
/* ========================================================================== */

uint16_t gTxBufData[FSI_MAX_VALUE_BUF_PTR_OFF + 1U];

extern SemaphoreP_Object gFsiTxRx_SyncSemaphoreObj;

/* ========================================================================== */
/*                         Static Function Declarations                       */
/* ========================================================================== */

/* ========================================================================== */
/*                         Function Definitions                                 */
/* ========================================================================== */

void fsi_tx_hld_main(void *args)
{
    int32_t status;
    uint32_t txBaseAddr, rxBaseAddr;
    uint16_t dataSize;
    uint16_t bufIdx;
    SemaphoreP_Object *p_taskDoneSemaphoreObj;
    FSI_HLD_TxTestParams  *txTestParams = (FSI_HLD_TxTestParams  *)args;
    FSI_Tx_Params txParams = txTestParams->fsi_tx_params;
    FSI_Rx_Params rxParams;

    FSI_Tx_Config *tx_config = NULL;
    FSI_Tx_Attrs  *tx_attrs   = NULL;

    tx_config = (FSI_Tx_Config *)gFsiTxHandle[CONFIG_FSI_TX0];
    tx_attrs = tx_config->attrs;

    FSI_Tx_close(gFsiTxHandle[CONFIG_FSI_TX0]);
    FSI_Rx_close(gFsiRxHandle[CONFIG_FSI_RX0]);

    /* Test parameters */
    txBaseAddr = FSI_Tx_getBaseAddr(gFsiTxHandle[CONFIG_FSI_TX0]);
    dataSize = txParams.frameDataSize;
    bufIdx = 0U;
    p_taskDoneSemaphoreObj = &txTestParams->taskDoneSemaphoreObj;

    DebugP_log("[FSI] Loopback Tx application started ...\r\n");

    FSI_Tx_open(CONFIG_FSI_TX0, &txParams);

    /* FSI_enableRxInternalLoopback should be called before FSI transmits the data
       and FSI_Rx_Open should be called before "FSI_enableRxInternalLoopback" function
    */
    rxParams.loopCnt = txParams.loopCnt;
    rxParams.frameDataSize = txParams.frameDataSize;
    rxParams.numLane = txParams.numLane;
    rxParams.transferMode = txParams.transferMode;
    rxParams.transferCallbackFxn = NULL;
    rxParams.errorCallbackFxn = NULL;
    rxParams.errorCheck = txParams.errorCheck;
    rxParams.delayLineCtrl = txParams.delayLineCtrl;
    FSI_Rx_open(CONFIG_FSI_RX0, &rxParams);

    /* Enable loopback */
    /* Test parameters */
    rxBaseAddr = FSI_Rx_getBaseAddr(gFsiRxHandle[CONFIG_FSI_RX0]);
    status = FSI_enableRxInternalLoopback(rxBaseAddr);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Send Flush Sequence to sync, after every rx soft reset */
    status = FSI_executeTxFlushSequence(txBaseAddr, tx_attrs->preScalarVal);
    DebugP_assert(status == SystemP_SUCCESS);


    /* Start transfer */
    /* Memset TX buffer with new data for every loop */
    for (uint32_t i = 0; i < dataSize; i++)
    {
        gTxBufData[i] = dataSize + i;
    }
 
    if(txParams.errorCheck != FSI_TX_NO_ERROR_CHECK)
    {
        FSI_Tx_errorCheck(gFsiTxHandle[CONFIG_FSI_TX0], gTxBufData);
    }

    if (txTestParams->rxFrameWDTest != TRUE)
    {
        /* Transmit data */
        status = FSI_Tx_hld(gFsiTxHandle[CONFIG_FSI_TX0], gTxBufData, NULL, bufIdx);
        DebugP_assert(status == SystemP_SUCCESS);
    }
    else
    {
        status = FSI_Tx_hld(gFsiTxHandle[CONFIG_FSI_TX0], gTxBufData, NULL, bufIdx);
        DebugP_assert(status == SystemP_SUCCESS);
        FSI_disableTxClock(txBaseAddr);
    }

    /* sync between rx and tx */
    status = SemaphoreP_pend(&gFsiTxRx_SyncSemaphoreObj, SystemP_WAIT_FOREVER);
    DebugP_assert(status == SystemP_SUCCESS);

    SemaphoreP_post(p_taskDoneSemaphoreObj);

    FSI_disableRxInternalLoopback(rxBaseAddr);

    FSI_Tx_close(gFsiTxHandle[CONFIG_FSI_TX0]);
    FSI_Rx_close(gFsiRxHandle[CONFIG_FSI_RX0]);

    while(1)
    {
        /* Yield to the main task which deletes this task. */
        TaskP_yield();
    };
}