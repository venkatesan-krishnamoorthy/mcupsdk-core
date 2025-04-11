# TMU 4 Cores Support {#EXAMPLES_DRIVERS_TMU_CORES_SUPPORT}

[TOC]

# Introduction

This example demonstrates the usage of all four cores by TMU. Additionally, the example also implements Park and Inverse Park Transform which has use cases in high performance
drive architectures related to permanent magnet synchronous and asynchronous machines. The implementation of this transform is as follows:

**Park Transform:**

    Isd = Ialpha*cos(theta) + Ibeta*sin(theta)
    Isq = -Ialpha*sin(theta) + Ibeta*cos(theta)

**Inverse Park Transform**

    Ialpha = Isd*cos(theta) - Isq*sin(theta)
    Ibeta = Isd*sin(theta) + Iq*cos(theta)

Ialpha = Stationary d-axis stator current

Ibeta = Stationary q-axis stator current

Isd = Rotating d-axis stator current

Isq = Rotating q-axis stator current

theta = Rotating angle in per unit

To implement the trigonometric function calls, TMU specific operations have been put into use as TMU have better performance in comparison to the C mathlib supported
trigonometric function calls. This example can be run parallely on all four cores supported by the chip, due to it's multi-core functionality

\cond SOC_AM263PX
# Errata : TMU Writes Curropts TCMA region from 0x40 to 0x3A0 {#TMU_TCMA_ERRATA}

In AM263Px, the writes to TMU (TMU instance of core 1, in each cluster) curropt the TCMA of the respective cores. That is, the writes TMU registers offset from 0x40 to 0x3A0 of TMU, will be reflected on the TCMA register offsets 0x40 to 0x3A0. 

The code / data present in the TCMA of these cores will be curropted upon using these TMUs. Hence the following workarounds are proposed.
1. If the TMUs of Cores 1 are being used, their respective TCMAs should be blocked for the initial register offsets from 0x40 to 0x3A0.
 - this workaround is implemented in the example \ref EXAMPLES_DRIVERS_TMU_CORES_SUPPORT, by considering the TCM start address to be 0x3A4, please refer its example.syscfg file under the Memory sections.

2. If the TMU of Core 0 (in same cluster) is not used, the Core 1, can use the TMU of Core 0, using its global address instead of 0x60040.
 - This workaround introduces some latency over the usage of self TMU.

\endcond


# Supported Combinations {#EXAMPLES_DRIVERS_TMU_CORES_SUPPORT_COMBOS}

\cond SOC_AM263PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 ^              | r5fss0-1 nortos
 ^              | r5fss1-0 nortos
 ^              | r5fss1-1 nortos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER, @VAR_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/tmu/tmu_cores_support/

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Establish connections as mentioned in External Connections section
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE
- View the console log for results


# Sample Output

Shown below is a sample output when the application is run,

\code
[Cortex_R5_0] TMU Cores Support Test Started ...
Park Transform value : 500.000000 , 400.000000
Inverse Park Transform value : 150.000000 , 275.000000
TMU Cores Support Test Passed ...
All tests have passed!! ...
[Cortex_R5_1] TMU Cores Support Test Started ...
Park Transform value : 500.000000 , 400.000000
Inverse Park Transform value : 150.000000 , 275.000000
TMU Cores Support Test Passed ...
All tests have passed!! ...
[Cortex_R5_2] TMU Cores Support Test Started ...
Park Transform value : 500.000000 , 400.000000
Inverse Park Transform value : 150.000000 , 275.000000
TMU Cores Support Test Passed ...
All tests have passed!! ...
[Cortex_R5_3] TMU Cores Support Test Started ...
Park Transform value : 500.000000 , 400.000000
Inverse Park Transform value : 150.000000 , 275.000000
TMU Cores Support Test Passed ...
All tests have passed!! ...
\endcode

# See Also
- \ref TMU_LIBRARY
- \ref TMU_GUIDE
- \ref DRV_TMU_MODULE