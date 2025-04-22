#  FSS1 XIP Hello World Project {#EXAMPLES_HELLO_WORLD_XIP_FSS1}

[TOC]

# Introduction


This example other than just doing the driver and board initialization and prints the string, Hello World! on UART console. It does 
that while doing the XIP from FSS1 interface. 

Make sure to update `MCELF_XIP_RANGE` in deconfig.mak to `0x80000000:0x88000000` before building.

# Supported Combinations {#EXAMPLES_HELLO_WORLD_XIP_FSS1_COMBOS}

\cond SOC_AM261X 

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 ^              | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_LP_BOARD_NAME_LOWER
 Example folder | examples/hello_world_xip_fss1/

\endcond

\cond SOC_AM263PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 ^              | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/hello_world_xip_fss1/

\endcond


# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# Sample Output

Shown below is a sample output when the application is run.

\code
  Hello World!
\endcode
