# PMIC ESM Level mode example {#EXAMPLES_PMIC_ESM_LEVEL_MODE}

[TOC]

# Introduction

The example demonstrates the PMIC IN ESM level mode, where in the first instance delay1 and delay2 
ESM errors are configured to generate an interrupt, and in the second instance delay2 error is configured
to device transitions to RESET-MCU state, when the ESM_IN pin of the PMIC is low.

# Supported Combinations {#EXAMPLES_DRIVERS_PMIC_ESM_LEVEL_MODE_COMBOS}

\cond SOC_AM261X || SOC_AM263PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 ^              | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/pmic/pmic_esm_level_mode

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
Starting ESM level mode example !!

Interrupt: Setting ESM Delay1 and Delay2 error config to generate Interrupt
Generating error from MCU to PMIC
Error generated from MCU.. Waiting for the PMIC interrupt... 
Received interrupt for PMIC ESM error !! 
Cleared PMIC ESM error states and ESM error from MCU

Reset: Setting ESM Delay2 error config to device transitions to RESET-MCU state
Generating error from MCU to PMIC
Error generated from MCU..
All test Passed. MCU will reset once reset ocuurs from PMIC
\endcode

