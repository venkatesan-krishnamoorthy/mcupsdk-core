/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>
#include <unity.h>
#include <kernel/dpl/DebugP.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TEST_RAM_TX_BUF_SIZE      (4096U)
#define TEST_RAM_RX_BUF_SIZE      (4096U)
#define TEST_RAM_MAX_SIZE         (16*1024*1024U)
#define NUM_OF_ITERATIONS         (8U)

/* ========================================================================== */
/*                             Global Variables                               */
/* ========================================================================== */

uint8_t gRamTestTxBuf[TEST_RAM_TX_BUF_SIZE];

uint8_t gRamTestRxBuf[TEST_RAM_RX_BUF_SIZE] __attribute__((aligned(128U)));

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void test_ram_fill_io_buffers(void);
static void test_ram_readwrite_random(void *args);
static void test_ram_readwrite_fullmem(void *args);
static void test_ram_io_compare(uint32_t offset,uint32_t len,uint32_t startIdx);
static uint32_t getRandomNumber(uint32_t min,uint32_t max);

void test_main(void *args)
{
    UNITY_BEGIN();
    srand(time(0));
    Drivers_open();
    RUN_TEST(test_ram_readwrite_random, 14235, NULL);
    Drivers_close();

    Drivers_open();
    RUN_TEST(test_ram_readwrite_fullmem, 14236, NULL);
    Drivers_close();

    UNITY_END();
    return;
}

/* Unity framework required information */
void setUp(void)
{
}

void tearDown(void)
{
}

static uint32_t getRandomNumber(uint32_t min,uint32_t max)
{
    uint32_t range = max - min + 1;
    return rand()%range + min;
}

static void test_ram_fill_io_buffers(void)
{
    
    for(uint32_t i=0;i<TEST_RAM_TX_BUF_SIZE;i++)
    {
        gRamTestTxBuf[i] = getRandomNumber(i,TEST_RAM_TX_BUF_SIZE)%256;
        gRamTestRxBuf[i] = 0;
    }
}

static void test_ram_io_compare(uint32_t offset,uint32_t len,uint32_t startIdx)
{
    int32_t retVal = SystemP_SUCCESS;

    retVal = Ram_write(gRamHandle[CONFIG_RAM0], offset, gRamTestTxBuf + startIdx, len);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = Ram_read(gRamHandle[CONFIG_RAM0], offset, gRamTestRxBuf + startIdx, len);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = memcmp(gRamTestRxBuf+startIdx,gRamTestTxBuf+startIdx,len);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

}

static void test_ram_readwrite_random(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t offset,len,startIdx;

    for(uint32_t i=0;i<NUM_OF_ITERATIONS;i++)
    {
        retVal = Board_driversOpen();
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

        offset = getRandomNumber(0,TEST_RAM_MAX_SIZE);    
        if(offset&1) 
        {
            offset--;
        }

        len = getRandomNumber(2,TEST_RAM_TX_BUF_SIZE);
        if(len&1)
        {
            len--;
        }

        if(TEST_RAM_MAX_SIZE-offset <= len)
        {
            len = TEST_RAM_MAX_SIZE-offset;
        }

        startIdx = getRandomNumber(0,TEST_RAM_TX_BUF_SIZE-len);
        if(startIdx&1) 
        {
            startIdx--;
        }

        test_ram_fill_io_buffers();
        test_ram_io_compare(offset,len,startIdx);

        Board_driversClose();

    }
}

static void test_ram_readwrite_fullmem(void *args)
{
    int32_t retVal = SystemP_SUCCESS;
    uint32_t offset = 0;
    uint32_t i;

    retVal = Board_driversOpen();
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    test_ram_fill_io_buffers();

    for(i=0;i<(TEST_RAM_MAX_SIZE/TEST_RAM_TX_BUF_SIZE);i++)
    {
        retVal = Ram_write(gRamHandle[CONFIG_RAM0], offset + i*TEST_RAM_TX_BUF_SIZE, gRamTestTxBuf, TEST_RAM_TX_BUF_SIZE);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    }

    for(i=0;i<(TEST_RAM_MAX_SIZE/TEST_RAM_RX_BUF_SIZE);i++)
    {
        retVal = Ram_read(gRamHandle[CONFIG_RAM0], offset + i*TEST_RAM_RX_BUF_SIZE, gRamTestRxBuf, TEST_RAM_RX_BUF_SIZE);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

        retVal = memcmp(gRamTestRxBuf,gRamTestTxBuf,TEST_RAM_RX_BUF_SIZE);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

        memset(gRamTestRxBuf, '\0', TEST_RAM_RX_BUF_SIZE);
    }
    
    Board_driversClose();

}