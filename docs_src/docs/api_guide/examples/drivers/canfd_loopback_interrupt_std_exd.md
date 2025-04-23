# CANFD Loopback Interrupt {#EXAMPLES_DRIVERS_CANFD_LOOPBACK_INTERRUPT_STANDARD_EXTENDED_EXAMPLE}

[TOC]

# Introduction

This example demonstrates the CAN message transmission and reception in
digital loop back mode for standard and extended CAN with the following 
configuration.

- Message ID for standard and extended CAN is 0x1C and 0x29E respectively.
- MCAN is configured in Interrupt Mode.
- Arbitration Bit Rate 1Mbps.
- Data Bit Rate 5Mbps.
- Buffer mode is used for Tx and RX to store message in message RAM.

Message is transmitted and received back internally using internal loopback
mode. When the received message id and the data matches with the transmitted
one, then the example is completed.

# Supported Combinations {#EXAMPLES_DRIVERS_CANFD_LOOPBACK_INTERRUPT_STANDARD_EXTENDED_COMBOS}

\cond SOC_AM263X || SOC_AM263PX || SOC_AM261X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 ^              | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER, @VAR_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/mcan/canfd_loopback_interrupt_std_exd

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref DRIVERS_CANFD_HLD_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
[MCAN] Loopback Interrupt mode for Standard and Extended CAN test application started ...
MCAN Extended mode test started..
MCAN Extended mode test passed.
MCAN Standard mode test started..
MCAN Standard mode test passed.
All tests have passed!!
\endcode
