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
#include <drivers/fsi.h>
#include <drivers/pinmux.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "test_fsi_hld_common.h"
#include "test_fsi_rx_hld_task.h"
#include "test_fsi_tx_hld_task.h"

/* ========================================================================== */
/*                         Global Varialbe Declarations                       */
/* ========================================================================== */
/* Semaphore to track end of rx_task and tx_task */
SemaphoreP_Object gFsiTaskDoneSemaphoreObj;
SemaphoreP_Object gFsiTxRx_SyncSemaphoreObj;

uint8_t gFsiRxTaskStack[FSI_TASK_STACK_SIZE] __attribute__((aligned(32)));
TaskP_Object gFsiRxTaskObject;

uint8_t gFsiTxTaskStack[FSI_TASK_STACK_SIZE] __attribute__((aligned(32)));
TaskP_Object gFsiTxTaskObject;

/* +1 to allocate full 16 elements FSI_MAX_VALUE_BUF_PTR_OFF is 15 */
extern uint16_t gRxBufData[FSI_MAX_VALUE_BUF_PTR_OFF + 1U];
extern uint16_t gTxBufData[FSI_MAX_VALUE_BUF_PTR_OFF + 1U];
uint32_t        gDataWordArray[FSI_MAX_VALUE_BUF_PTR_OFF + 1U] =
                {1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U,
                 9U, 10U, 11U, 12U, 13U, 14U, 15U, 16U};
/* TX Functional Clock should be less than SYSCLK / 2 */
uint32_t        gPrescalValArray[FSI_MAX_VALUE_BUF_PTR_OFF + 1U] =
                {2U, 3U, 4U, 5U, 6U, 7U, 8U, 9U,
                 16U, 32U, 64U, 96U, 128U, 160U, 200U, 255U};

FSI_HLD_RxTestParams gFsiRxTestParams = {0U};
FSI_HLD_TxTestParams gFsiTxTestParams = {0U};

static int32_t Fsi_appCompareData(uint16_t *txBufPtr, uint16_t *rxBufPtr);
static void Fsi_appTxRxTestParamsInit(FSI_HLD_RxTestParams *rxTestParms,
                                      FSI_HLD_TxTestParams *txTestParms);
void test_fsi_txrx(void *args);
static void test_fsi_set_params(FSI_MainTestParams *testParams, uint32_t testCaseNo);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{
    FSI_MainTestParams  testParams;

    Drivers_open();

    UNITY_BEGIN();

    test_fsi_set_params(&testParams, 1);
    RUN_TEST(test_fsi_txrx, 1, (void*)&testParams);

    test_fsi_set_params(&testParams, 2);
    RUN_TEST(test_fsi_txrx, 2, (void*)&testParams);

    test_fsi_set_params(&testParams, 3);
    RUN_TEST(test_fsi_txrx, 3, (void*)&testParams);

    test_fsi_set_params(&testParams, 4);
    RUN_TEST(test_fsi_txrx, 4, (void*)&testParams);

    test_fsi_set_params(&testParams, 5);
    RUN_TEST(test_fsi_txrx, 5, (void*)&testParams);

    test_fsi_set_params(&testParams, 6);
    RUN_TEST(test_fsi_txrx, 6, (void*)&testParams);

    test_fsi_set_params(&testParams, 7);
    RUN_TEST(test_fsi_txrx, 7, (void*)&testParams);

    UNITY_END();

    Drivers_close();
}

void test_fsi_txrx(void *args)
{
    int32_t         status;
    TaskP_Params    txTaskParms, rxTaskParms;
    FSI_MainTestParams *testParams = (FSI_MainTestParams*)args;
    FSI_HLD_TxTestParams *txTestParams = testParams->txTestParams;
    FSI_HLD_RxTestParams *rxTestParams = testParams->rxTestParams;

    status = SemaphoreP_constructBinary(&gFsiTxRx_SyncSemaphoreObj, 0);
    DebugP_assert(status == SystemP_SUCCESS);
    status = SemaphoreP_constructCounting(&txTestParams->taskDoneSemaphoreObj, 0, 2);
    DebugP_assert(status == SystemP_SUCCESS);
    status = SemaphoreP_constructCounting(&rxTestParams->taskDoneSemaphoreObj, 0, 2);
    DebugP_assert(status == SystemP_SUCCESS);

    TaskP_Params_init(&txTaskParms);
    txTaskParms.name = "FSI-TX Task";
    txTaskParms.stackSize = FSI_TASK_STACK_SIZE;
    txTaskParms.stack = gFsiTxTaskStack;
    txTaskParms.priority = FSI_TASK_PRIORITY;
    txTaskParms.args = txTestParams;
    txTaskParms.taskMain = testParams->testCaseTxFxnPtr;;
    status = TaskP_construct(&gFsiTxTaskObject, &txTaskParms);
    DebugP_assert(status == SystemP_SUCCESS);

    TaskP_Params_init(&rxTaskParms);
    rxTaskParms.name = "FSI-RX Task";
    rxTaskParms.stackSize = FSI_TASK_STACK_SIZE;
    rxTaskParms.stack = gFsiRxTaskStack;
    rxTaskParms.priority = FSI_TASK_PRIORITY;
    rxTaskParms.args = rxTestParams;
    rxTaskParms.taskMain = testParams->testCaseRxFxnPtr;
    status = TaskP_construct(&gFsiRxTaskObject, &rxTaskParms);
    DebugP_assert(status == SystemP_SUCCESS);

    SemaphoreP_pend(&txTestParams->taskDoneSemaphoreObj, SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&rxTestParams->taskDoneSemaphoreObj, SystemP_WAIT_FOREVER);

    TaskP_destruct(&gFsiRxTaskObject);
    TaskP_destruct(&gFsiTxTaskObject);

    /* Compare data */
    if ((rxTestParams->rxFrameWDTest != TRUE) && (rxTestParams->rxPingWDTest != TRUE) )
    {
        status = Fsi_appCompareData(gTxBufData, gRxBufData);
        DebugP_assert(status == SystemP_SUCCESS);
    }

    SemaphoreP_destruct(&gFsiTxRx_SyncSemaphoreObj);
    SemaphoreP_destruct(&txTestParams->taskDoneSemaphoreObj);
    SemaphoreP_destruct(&rxTestParams->taskDoneSemaphoreObj);
}

static int32_t Fsi_appCompareData(uint16_t *txBufPtr, uint16_t *rxBufPtr)
{
    int32_t     status = SystemP_SUCCESS;
    uint32_t    i;

    for(i = 0; i < FSI_APP_FRAME_DATA_WORD_SIZE; i++)
    {
        if(*rxBufPtr++ != *txBufPtr++)
        {
            status = SystemP_FAILURE;
            break;
        }
    }

    return status;
}

/*
 * Unity framework required functions
 */
void setUp(void)
{
}

void tearDown(void)
{
}

/*
 * Testcases
 */
static void test_fsi_set_params(FSI_MainTestParams *testParams, uint32_t testCaseNo)
{
    testParams->testCaseTxFxnPtr = fsi_tx_hld_main;
    testParams->testCaseRxFxnPtr = fsi_rx_hld_main;
    testParams->rxTestParams = &gFsiRxTestParams;
    testParams->txTestParams = &gFsiTxTestParams;

    FSI_Tx_Attrs  *tx_attrs   = NULL;
    FSI_Rx_Attrs  *rx_attrs   = NULL;

    FSI_Tx_Config *tx_config = NULL;
    FSI_Rx_Config *rx_config = NULL;

    tx_config = (FSI_Tx_Config *)gFsiTxHandle[CONFIG_FSI_TX0];
    tx_attrs = tx_config->attrs;

    rx_config = (FSI_Rx_Config *)gFsiRxHandle[CONFIG_FSI_RX0];
    rx_attrs = rx_config->attrs;

    /* memset both TX/RX buffers to 0 for each testcase */
    memset(gTxBufData, 0U, sizeof(gTxBufData));
    memset(gRxBufData, 0U, sizeof(gRxBufData));
    switch (testCaseNo)
    {
        case 1:
            Fsi_appTxRxTestParamsInit(&gFsiRxTestParams, &gFsiTxTestParams);
            break;
        case 2:
            Fsi_appTxRxTestParamsInit(&gFsiRxTestParams, &gFsiTxTestParams);
            gFsiRxTestParams.fsi_rx_params.numLane = FSI_DATA_WIDTH_2_LANE;
            gFsiTxTestParams.fsi_tx_params.numLane = FSI_DATA_WIDTH_2_LANE;
            break;
        case 3:
            Fsi_appTxRxTestParamsInit(&gFsiRxTestParams, &gFsiTxTestParams);
            gFsiRxTestParams.fsi_rx_params.frameDataSize = 2;
            gFsiTxTestParams.fsi_tx_params.frameDataSize = 2;
            break;
        case 4:
            Fsi_appTxRxTestParamsInit(&gFsiRxTestParams, &gFsiTxTestParams);
            tx_attrs->intrLine = CONFIG_FSI_TX0_INTR2;
            tx_attrs->intrNum  = FSI_INT2;
            rx_attrs->intrLine = CONFIG_FSI_RX0_INTR2;
            rx_attrs->intrNum  = FSI_INT2;
            break;
        case 5:
            Fsi_appTxRxTestParamsInit(&gFsiRxTestParams, &gFsiTxTestParams);
            gFsiRxTestParams.fsi_rx_params.errorCheck = FSI_RX_USER_DEFINED_CRC_CHECK;
            gFsiTxTestParams.fsi_tx_params.errorCheck = FSI_TX_USER_DEFINED_CRC_CHECK;
            break;
        case 6:
            Fsi_appTxRxTestParamsInit(&gFsiRxTestParams, &gFsiTxTestParams);
            gFsiRxTestParams.fsi_rx_params.errorCheck = FSI_RX_ECC_ERROR_CHECK;
            gFsiTxTestParams.fsi_tx_params.errorCheck = FSI_TX_ECC_ERROR_CHECK;
            break;
        case 7:
            Fsi_appTxRxTestParamsInit(&gFsiRxTestParams, &gFsiTxTestParams);
            gFsiRxTestParams.fsi_rx_params.numLane = FSI_DATA_WIDTH_2_LANE;
            gFsiTxTestParams.fsi_tx_params.numLane = FSI_DATA_WIDTH_2_LANE;
            gFsiRxTestParams.fsi_rx_params.delayLineCtrl = TRUE;
            /* TX Delay Test is applicable for AM263X, AM263PX & AM261X only */
#if defined (SOC_AM263X) || defined (SOC_AM263PX) || defined (SOC_AM261X)
            gFsiTxTestParams.fsi_tx_params.delayLineCtrl = TRUE;
#endif
            break;
    }

    return;
}

static void Fsi_appTxRxTestParamsInit(FSI_HLD_RxTestParams *rxTestParms,
                                      FSI_HLD_TxTestParams *txTestParms)
{
    FSI_Tx_Params *tx_params = &(txTestParms->fsi_tx_params);
    FSI_Rx_Params *rx_params = &(rxTestParms->fsi_rx_params);

    FSI_HLD_TxParams_init(tx_params);
    FSI_HLD_RxParams_init(rx_params);

    rxTestParms->rxFrameWDTest = FALSE;
    rxTestParms->rxPingWDTest  = FALSE;

    txTestParms->rxFrameWDTest = FALSE;
    txTestParms->rxPingWDTest  = FALSE;

    return;
}
