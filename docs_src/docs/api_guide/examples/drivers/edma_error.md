# EDMA Error Interrupt {#EXAMPLES_DRIVERS_EDMA_ERROR_INTERRUPT}

[TOC]

# Introduction

This example demonstrates the error handling functionality of EDMA. A Count,
B Count and C count are set to 0 to emulate a NULL transfer.
After starting the transfer, EDMA detects a NULL transfer and signals
TPCC error. Application error callback gets invoked which signals an 
error.

# Supported Combinations {#EXAMPLES_DRIVERS_EDMA_ERROR_INTERRUPT_COMBOS}

\cond SOC_AM263X || SOC_AM263PX || SOC_AM261X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 ^              | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER, @VAR_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/edma/edma_error_interrupt/

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
[EDMA] Interrupt Error Interrupt Test Started...
[EDMA] TPCC Error detected due to NULL transfer on below EDMA channels -
[EDMA] Channel: 0
[EDMA] Error Transfer Test Completed. Null tranfer error detected !!
All tests have passed!!
\endcode

