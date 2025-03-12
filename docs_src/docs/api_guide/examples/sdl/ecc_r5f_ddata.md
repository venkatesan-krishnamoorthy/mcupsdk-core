# SDL R5F ECC DDATA {#EXAMPLES_SDL_R5F_ECC_DDATA}

[TOC]

# Introduction

The example shows how to setup and use the ECC Safety Diagnostic operation on d-data cache momory of R5F core.
Shows the generation of SEC error on R5F ECC Aggregator for DDATA cache moemories.
Use Cases
---------
\cond (SOC_AM263X || SOC_AM263PX || SOC_AM261X)
 Use Case | Description
 ---------|------------
 UC-1     | Single bit error injection.
 UC-2     | Double bit error injection.
\endcond


# Supported Combinations {#EXAMPLES_SDL_R5F_ECC_DDATA_COMBOS}

\cond (SOC_AM263X || SOC_AM263PX)
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 ^              | r5fss1-0 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/sdl/ecc/sdl_ecc_r5_d-data/
\endcond
\cond (SOC_AM261X)
 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 ^              | r5fss0-1 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/sdl/ecc/sdl_ecc_r5_d-data/
\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref SDL_ECC_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\cond (SOC_AM263X || SOC_AM263PX || SOC_AM261X)
\code

ECC Example Application

ECC UC-1 and UC-2 Test 

ECC_Test_init: Exception init complete 

ESM_Test_init: Init MSS ESM complete 

ECC_Test_init: R5FSS0 ECC initialization is completed 

Starting Tests for Ddata cache - single error correction

Waiting for ESM Interrupt 

Injected error and got ESM Interrupt for ram_Id = 13

Waiting for ESM Interrupt 

Injected error and got ESM Interrupt for ram_Id = 14

Waiting for ESM Interrupt 

Injected error and got ESM Interrupt for ram_Id = 15

Waiting for ESM Interrupt 

Injected error and got ESM Interrupt for ram_Id = 16

Waiting for ESM Interrupt 

Injected error and got ESM Interrupt for ram_Id = 17

Waiting for ESM Interrupt 

Injected error and got ESM Interrupt for ram_Id = 18

Waiting for ESM Interrupt 

Injected error and got ESM Interrupt for ram_Id = 19

Waiting for ESM Interrupt 

Injected error and got ESM Interrupt for ram_Id = 20

Starting Tests for Ddata cache - double error detection

Waiting for ESM Interrupt 

Injected error and got ESM Interrupt for ram_Id = 13

Waiting for ESM Interrupt 

Injected error and got ESM Interrupt for ram_Id = 14

Waiting for ESM Interrupt 

Injected error and got ESM Interrupt for ram_Id = 15

Waiting for ESM Interrupt 

Injected error and got ESM Interrupt for ram_Id = 16

Waiting for ESM Interrupt 

Injected error and got ESM Interrupt for ram_Id = 17

Waiting for ESM Interrupt 

Injected error and got ESM Interrupt for ram_Id = 18

Waiting for ESM Interrupt 

Injected error and got ESM Interrupt for ram_Id = 19

Waiting for ESM Interrupt 

Injected error and got ESM Interrupt for ram_Id = 20

All tests have passed. 

\endcode
\endcond
