/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
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

#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/SystemP.h>
#include <drivers/gpio.h>
#include <drivers/eqep.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/*
 *  CW/CCW Input demonstration to eQEP
 * 
 *  This example emulates CW and CCW pulses using 2 GPIO's and Timer based interrupts, before feeding them to the eQEP module.
 *  QMA MODE 2 (Active Pulse High is Enabled)
 *  We calculate and watch position, direction, frequency and speed post feeding these
 *  signals to eQEP module.
 *  
 * 
 *  The configuration for this example is as follows
 *  - 50 CW pulses followed by 50 CCW pulses
 *  - Encoder resolution is configured to 1000 counts/revolution
 *  - GPIO's are routed through PWMXBAR to eQEP module
 *  - GPIO's (simulating CW/CCW encoder signals) are configured for a 2.5kHz frequency
 *    or 150 rpm (= 2500 cnts/sec * 60 sec/min) / 1000 cnts/rev)
 * 
 * 
 *  External Connections (Only needed if you want to view the input CW/CCW Signals)\n
 * 
 *  AM263x-CC, AM263Px-CC
 *  - Scope GPIO43/Hsec 49 (simulates eQEP Phase A signal)
 *  - Scope GPIO44/Hsec 51 (simulates eQEP Phase B signal)
 *  - Scope GPIO48/Hsec 52 (simulates eQEP Index Signal)
 * 
 *  AM263x-LP, AM263Px-LP
 *  - Scope GPIO43/J2.11 (simulates eQEP Phase A signal)
 *  - Scope GPIO44/J6.59 (simulates eQEP Phase B signal)
 *  - Scope GPIO48/J4.40 (simulates eQEP Index Signal)
 *
 *  AM261x-SOM
 *  - Scope GPIO49 (simulates eQEP Phase A signal)
 *  - Scope GPIO50 (simulates eQEP Phase B signal)
 *  - Scope GPIO48 (simulates eQEP Index Signal)
 * 
 *  AM261x-LP
 *  - Scope GPIO49/J4.38 (simulates eQEP Phase A signal)
 *  - Scope GPIO50/J4.37 (simulates eQEP Phase B signal)
 *  - Scope GPIO48/J4.36 (simulates eQEP Index Signal)
 * 
 */ 

/* Configuration Constants */
#define APP_LOOP_CNT          (100U)     /* Number of interrupt cycles before completion */
#define APP_INT_IS_PULSE      (1U)       /* Configure interrupt as pulse type */
#define ENCODER_SLOTS         (1000U)    /* Encoder resolution (counts per revolution) */
#define UNIT_PERIOD           (10000U)   /* Unit timeout period in microseconds (10ms) */

#define EXPECTED_FREQ_HZ      (2500)    /* Expected frequency in Hz */
#define EXPECTED_RPM          (150U)    /* Expected RPM */

/* Global Variables for Position and Speed Calculation */
typedef struct {
    uint32_t oldCount;           /* Previous position count at last unit timeout */
    uint32_t newCount;           /* Latest latched position count at unit timeout */
    uint32_t currentEncoderPos;  /* Current absolute encoder position */
    int32_t freq;               /* Pulse frequency in Hz */
    float speed;                /* Motor speed in RPM */
    int32_t direction;          /* Current direction: 1 = CW, -1 = CCW */
} EncoderState;

/* Make encoder state globally accessible for debugging */
volatile EncoderState gEncoderState = {0};

/* Global Variables */
static uint32_t gEqepBaseAddr;
static uint16_t gInterruptCount = 0;
static HwiP_Object gEqepHwiObject;
static SemaphoreP_Object gEqepSyncSem;
static volatile bool gEqepTestComplete = false;
static bool qmaValid = true;

/* Function Prototypes */
static void App_eqepISR(void *args);
static void App_calculateSpeed(void);
static inline void App_gpioPinToggle(uint32_t baseAddr, uint32_t pinNum);

/* Main Application Entry Point */
void eqep_cw_ccw_main(void *args)
{
    int32_t status;
    HwiP_Params hwiPrms;
    
    /* Initialize drivers and board */
    Drivers_open();
    Board_driversOpen();

    gEqepBaseAddr = CONFIG_EQEP0_BASE_ADDR;

    /* Create synchronization semaphore */
    status = SemaphoreP_constructBinary(&gEqepSyncSem, 0);
    DebugP_assert(status == SystemP_SUCCESS);

    DebugP_log("EQEP Position Speed Test Started ...\r\n");
    
    /* Configure and register EQEP interrupt handler */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum = CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_0;
    hwiPrms.callback = &App_eqepISR;
    hwiPrms.isPulse = APP_INT_IS_PULSE;
    
    status = HwiP_construct(&gEqepHwiObject, &hwiPrms);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Clear any pending interrupts */
    EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_UNIT_TIME_OUT|EQEP_INT_GLOBAL);

    /* Start the timer and wait for completion */
    TimerP_start(gTimerBaseAddr[CONFIG_TIMER0]);
    SemaphoreP_pend(&gEqepSyncSem, SystemP_WAIT_FOREVER);
    TimerP_stop(gTimerBaseAddr[CONFIG_TIMER0]);

    /* Validate frequency and speed measurements */
    bool freqValid = (gEncoderState.freq >= (EXPECTED_FREQ_HZ - 100) && 
                     gEncoderState.freq <= (EXPECTED_FREQ_HZ + 100));
    bool speedValid = (gEncoderState.speed >= (EXPECTED_RPM - 10) && 
                      gEncoderState.speed <= (EXPECTED_RPM + 10));
    
    if(!freqValid || !speedValid || !qmaValid) {
        DebugP_log("EQEP Validation Failed!\r\n");
        DebugP_log("Results:\r\n");
        DebugP_log("  Frequency: %d Hz (Expected: %d Hz ±100)\r\n", 
                  gEncoderState.freq, EXPECTED_FREQ_HZ);
        DebugP_log("  Speed: %.2f RPM (Expected: %d RPM ±10)\r\n",
                  gEncoderState.speed, EXPECTED_RPM);
        DebugP_log("  Direction: %s\r\n", 
                  (gEncoderState.direction > 0) ? "Clockwise" : "Counter-clockwise");
        
        if(!qmaValid) {
            DebugP_log("ERROR: QMA Error detected\r\n");
        }
        if(!freqValid) {
            DebugP_log("ERROR: Frequency out of valid range\r\n");
        }
        if(!speedValid) {
            DebugP_log("ERROR: Speed out of valid range\r\n"); 
        }
        
        DebugP_log("Test Failed!\r\n");
    }
    else {
        DebugP_log("EQEP Validation Passed\r\n");
        DebugP_log("Results:\r\n");
        DebugP_log("  Frequency: %d Hz\r\n", gEncoderState.freq);
        DebugP_log("  Speed: %.2f RPM\r\n", gEncoderState.speed);
        DebugP_log("  Direction: %s\r\n",
                  (gEncoderState.direction > 0) ? "Clockwise" : "Counter-clockwise");
        DebugP_log("All tests passed successfully!\r\n");
    }

    /* Cleanup resources */
    HwiP_destruct(&gEqepHwiObject);
    SemaphoreP_destruct(&gEqepSyncSem);

    Board_driversClose();
    Drivers_close();
}

/* Timer ISR for Generating Test Signals */
void timerISR(void) {
    static uint32_t toggleCount = 0;
    static uint32_t indexPulseCount = 0;

    toggleCount++;

    /* Generate CW and CCW test pulses */
    if(toggleCount <= 100) {  // First 50 CW pulses
        App_gpioPinToggle(GPIO_CW_PIN_BASE_ADDR, GPIO_CW_PIN_PIN);
    }
    else if(toggleCount <= 200) {  // Next 50 CCW pulses
        App_gpioPinToggle(GPIO_CCW_PIN_BASE_ADDR, GPIO_CCW_PIN_PIN);
    }
    else {  // Reset counter
        toggleCount = 0;
    }

    /* Generate index pulse every 1000 counts */
    if(toggleCount % 1000 == 0) {
        GPIO_pinWriteHigh(GPIO_INDEX_PIN_BASE_ADDR, GPIO_INDEX_PIN_PIN);
        indexPulseCount = 1;
    }
    else if(indexPulseCount > 0) {
        indexPulseCount++;
        if(indexPulseCount >= 4) {
            GPIO_pinWriteLow(GPIO_INDEX_PIN_BASE_ADDR, GPIO_INDEX_PIN_PIN);
            indexPulseCount = 0;
        }
    }
}

/* EQEP Interrupt Service Routine */
static void App_eqepISR(void *args)
{
    int32_t status = EQEP_getInterruptStatus(gEqepBaseAddr);

    gInterruptCount++;

    /* Handle QMA Error */
    if(status & EQEP_INT_QMA_ERROR) {
        EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_QMA_ERROR|EQEP_INT_GLOBAL);
        qmaValid = false;
        SemaphoreP_post(&gEqepSyncSem);
    }
    else {
        /* Update encoder state and calculate speed */
        gEncoderState.currentEncoderPos = EQEP_getPosition(gEqepBaseAddr);
        gEncoderState.direction = EQEP_getDirection(gEqepBaseAddr);
        gEncoderState.newCount = EQEP_getPositionLatch(gEqepBaseAddr);

        App_calculateSpeed();
        
        EQEP_clearInterruptStatus(gEqepBaseAddr, EQEP_INT_UNIT_TIME_OUT|EQEP_INT_GLOBAL);
    }

    /* Check for test completion */
    if(gInterruptCount >= APP_LOOP_CNT) {
        gEqepTestComplete = true;
        SemaphoreP_post(&gEqepSyncSem);
    }
}

/* Calculate Speed and Update Encoder State */
static void App_calculateSpeed(void)
{
    /* Calculate position change based on direction */
    if (gEncoderState.direction > 0) {
        if (gEncoderState.newCount >= gEncoderState.oldCount)
            gEncoderState.newCount -= gEncoderState.oldCount;
        else
            gEncoderState.newCount = (ENCODER_SLOTS - gEncoderState.oldCount) + gEncoderState.newCount;
    }
    else {
        if (gEncoderState.newCount <= gEncoderState.oldCount)
            gEncoderState.newCount = gEncoderState.oldCount - gEncoderState.newCount;
        else
            gEncoderState.newCount = (ENCODER_SLOTS - gEncoderState.newCount) + gEncoderState.oldCount;
    }

    /* Update old count for next calculation */
    gEncoderState.oldCount = gEncoderState.currentEncoderPos;

    /* Calculate frequency and speed */
    gEncoderState.freq = (gEncoderState.newCount * (uint32_t)1000000U) / ((uint32_t)UNIT_PERIOD);
    gEncoderState.speed = (gEncoderState.freq * 60.0f) / ((float)(ENCODER_SLOTS));
}

/* GPIO Pin Toggle Helper Function */
static inline void App_gpioPinToggle(uint32_t baseAddr, uint32_t pinNum)
{
    uint32_t regIndex, regVal;
    volatile CSL_GpioRegs* hGpio = (volatile CSL_GpioRegs*)((uintptr_t) baseAddr);

    regIndex = GPIO_GET_REG_INDEX(pinNum);
    regVal = GPIO_GET_BIT_MASK(pinNum);
    CSL_REG32_WR(&hGpio->BANK_REGISTERS[regIndex].OUT_DATA, 
                 CSL_REG32_RD(&hGpio->BANK_REGISTERS[regIndex].OUT_DATA) ^ regVal);
}