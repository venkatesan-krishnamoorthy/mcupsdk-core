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
#include <drivers/hw_include/cslr_fsi_rx.h>
#include <drivers/fsi.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "test_fsi_hld_common.h"
#include "test_fsi_rx_hld_task.h"

/* ========================================================================== */
/*                         Global Varialbe Declarations                       */
/* ========================================================================== */

uint16_t gRxBufData[FSI_MAX_VALUE_BUF_PTR_OFF + 1U];

extern SemaphoreP_Object gFsiTxRx_SyncSemaphoreObj;

volatile uint32_t gRxFrameWdTest = FALSE;
volatile uint32_t gRxPingWdTest = FALSE;

/* ========================================================================== */
/*                         Static Function Declarations                       */
/* ========================================================================== */

/* ========================================================================== */
/*                         Function Definitions                                 */
/* ========================================================================== */

void fsi_rx_hld_main(void *args)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t rxBaseAddr = 0, rxBufAddr;
    uint16_t dataSize;
    uint16_t bufIdx;
    uint16_t *tmpBufAddr;
    SemaphoreP_Object *p_taskDoneSemaphoreObj;
    FSI_HLD_RxTestParams  *rxTestParams = (FSI_HLD_RxTestParams  *)args;
    FSI_Rx_Params rxParams = rxTestParams->fsi_rx_params;

    FSI_Rx_close(gFsiRxHandle[CONFIG_FSI_RX0]);

    gFsiRxHandle[CONFIG_FSI_RX0] = FSI_Rx_open(CONFIG_FSI_RX0, &rxParams);

    /* Test parameters */
    rxBaseAddr = FSI_Rx_getBaseAddr(gFsiRxHandle[CONFIG_FSI_RX0]);
    status = FSI_enableRxInternalLoopback(rxBaseAddr);
    DebugP_assert(status == SystemP_SUCCESS);
    dataSize = rxParams.frameDataSize;
    bufIdx = 0U;
    p_taskDoneSemaphoreObj = &rxTestParams->taskDoneSemaphoreObj;

    DebugP_log("[FSI] Loopback RX application test started ...\r\n");

    /* sync between rx and tx */
    status = SemaphoreP_pend(&gFsiTxRx_SyncSemaphoreObj,SystemP_WAIT_FOREVER);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Memset RX buffer with 0 for every loop */
    for (uint32_t i = 0; i < dataSize; i++)
    {
        gRxBufData[i] = 0;
    }

    if (rxParams.rxFrameWDTest != TRUE && rxParams.rxPingWDTest != TRUE)
    {
        status = FSI_Rx_hld(gFsiRxHandle[CONFIG_FSI_RX0], gRxBufData, NULL, bufIdx);
        DebugP_assert(status == SystemP_SUCCESS);

        FSI_getRxBufferAddress(rxBaseAddr, &rxBufAddr);
        tmpBufAddr = (uint16_t *)rxBufAddr;
        for (uint32_t i = 0; i < dataSize; i++)
        {
            DebugP_assert(gRxBufData[i] == tmpBufAddr[i]);
        }

#if defined (SOC_AM263X) || defined (SOC_AM263PX) || defined (SOC_AM261X)
        if(rxParams.udataFilterTest == TRUE)
        {
            uint16_t userData;
            FSI_getRxUserDefinedData(rxBaseAddr, &userData);
            if ((userData & FSI_APP_RX_USER_DATA_BIT_MASK) !=
                (rxParams.userData & FSI_APP_RX_USER_DATA_BIT_MASK))
                {
                    DebugP_assert(FALSE);
                }
        }
#endif
    }
    else
    {
        status = FSI_Rx_hld(gFsiRxHandle[CONFIG_FSI_RX0], gRxBufData, NULL, bufIdx);
        DebugP_assert(status == SystemP_SUCCESS);
    }

    if(rxParams.errorCheck != FSI_RX_NO_ERROR_CHECK)
    {
        FSI_Rx_errorCheck(gFsiRxHandle[CONFIG_FSI_RX0], gRxBufData);
    }

    SemaphoreP_post(p_taskDoneSemaphoreObj);   

    FSI_disableRxInternalLoopback(rxBaseAddr);

    while(1)
    {
        /* Yield to the main task which deletes this task. */
        TaskP_yield();
    };
}