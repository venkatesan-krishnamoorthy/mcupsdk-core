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
    uint32_t txBaseAddr;
    uint16_t dataSize;
    uint16_t bufIdx;
    SemaphoreP_Object *p_taskDoneSemaphoreObj;
    FSI_HLD_TxTestParams  *txTestParams = (FSI_HLD_TxTestParams  *)args;
    FSI_Tx_Params txParams = txTestParams->fsi_tx_params;

    FSI_Tx_Config *tx_config = NULL;
    FSI_Tx_Attrs  *tx_attrs   = NULL;

    FSI_Tx_close(gFsiTxHandle[CONFIG_FSI_TX0]);

    gFsiTxHandle[CONFIG_FSI_TX0] = FSI_Tx_open(CONFIG_FSI_TX0, &txParams);

    tx_config = (FSI_Tx_Config *)gFsiTxHandle[CONFIG_FSI_TX0];
    tx_attrs = tx_config->attrs;

    /* Test parameters */
    txBaseAddr = FSI_Tx_getBaseAddr(gFsiTxHandle[CONFIG_FSI_TX0]);
    dataSize = txParams.frameDataSize;
    bufIdx = 0U;
    p_taskDoneSemaphoreObj = &txTestParams->taskDoneSemaphoreObj;

    DebugP_log("[FSI] Loopback Tx application started ...\r\n");

    /* Send Flush Sequence to sync, after every rx soft reset */
    status = FSI_executeTxFlushSequence(txBaseAddr, tx_attrs->preScalarVal);
    DebugP_assert(status == SystemP_SUCCESS);

    /* post semaphore to sync with rx */
    SemaphoreP_post(&gFsiTxRx_SyncSemaphoreObj);

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

    status = FSI_Tx_hld(gFsiTxHandle[CONFIG_FSI_TX0], gTxBufData, NULL, bufIdx);
    DebugP_assert(status == SystemP_SUCCESS);

    FSI_Tx_close(gFsiTxHandle[CONFIG_FSI_TX0]);

    SemaphoreP_post(p_taskDoneSemaphoreObj);

    while(1)
    {
        /* Yield to the main task which deletes this task. */
        TaskP_yield();
    };
}