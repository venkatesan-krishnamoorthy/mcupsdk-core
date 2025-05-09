# Optiflash XIP Benchmark with 32KB L2 Cache {#EXAMPLES_OPTIFLASH_XIP_32K_BENCHMARK}

[TOC]

# Supported Combinations {#EXAMPLES_OPTIFLASH_XIP_32K_BENCHMARK_COMBOS}
\cond SOC_AM263PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/benchmarks/optiflash_benchmark/flash_xip_l2_cache_32k

\endcond

\cond SOC_AM261X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_LP_BOARD_NAME_LOWER, @VAR_BOARD_NAME_LOWER
 Example folder | examples/benchmarks/optiflash_benchmark/flash_xip_l2_cache_32k

\endcond

# Introduction

This is the same application as \ref EXAMPLES_OPTIFLASH_OCRAM_BENCHMARK, however, target functions are kept in external flash and L2 cache of 32KB is enabled. The effect of it is seen in the execution time.

# Steps to Run the Example

## Building the application

- When using CCS projects to build, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- When using makefiles to build, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)

## Running the application

Flash the application binary to the device, follow the steps mentioned here
 (see \ref GETTING_STARTED_FLASH).

## Sample output


\cond SOC_AM263PX
\code

Starting OSPI Bootloader ...
KPI_DATA: [BOOTLOADER_PROFILE] Boot Media       : NOR SPI FLASH
KPI_DATA: [BOOTLOADER_PROFILE] Boot Media Clock : 133.333 MHz
KPI_DATA: [BOOTLOADER_PROFILE] Boot Image Size  : 6 KB
KPI_DATA: [BOOTLOADER_PROFILE] Cores present    :
r5f0-0
KPI_DATA: [BOOTLOADER PROFILE] System_init                      :        603us
KPI_DATA: [BOOTLOADER PROFILE] Drivers_open                     :        137us
KPI_DATA: [BOOTLOADER PROFILE] LoadHsmRtFw                      :       9335us
KPI_DATA: [BOOTLOADER PROFILE] Board_driversOpen                :       2790us
KPI_DATA: [BOOTLOADER PROFILE] CPU load                         :       3858us
KPI_DATA: [BOOTLOADER PROFILE] SBL End                          :         17us
KPI_DATA: [BOOTLOADER_PROFILE] SBL Total Time Taken             :      16743us

Image loading done, switching to application ...

OCMC benchmarking:: Board_init success
Filling up the buffers

master_task

master_task -- start sending
    memcpy Exec Time   I$ Miss    I$ Acc      INST   ICM/sec  INST/sec
         0B     31881us     85094   1073575   2169655       3.3      84.0
       100B     31533us     84265   1221370   2358979       3.3      92.4
       200B     32709us     84846   1369193   2559098       3.2      96.6
       400B     35374us     87981   1672383   2961186       3.1     103.4
       700B     35271us     82231   2113015   3546739       2.9     124.2
      1000B     38125us     85559   2576552   4161585       2.8     134.8
      1500B     42672us     84488   3321470   5154070       2.4     149.2
      2250B     50621us     87960   4466079   6668856       2.1     162.7
      2500B     53556us     86251   4830831   7156461       2.0     165.0
      4096B     67154us     85129   7232200  10352040       1.6     190.4

All tests have passed

\endcode
\endcond

\cond SOC_AM261X
\code
Starting OSPI Bootloader ...
KPI_DATA: [BOOTLOADER_PROFILE] Boot Media       : NOR SPI FLASH
KPI_DATA: [BOOTLOADER_PROFILE] Boot Media Clock : 166.667 MHz
KPI_DATA: [BOOTLOADER_PROFILE] Boot Image Size  : 6 KB
KPI_DATA: [BOOTLOADER_PROFILE] Cores present    :
r5f0-0
KPI_DATA: [BOOTLOADER PROFILE] System_init                      :        497us
KPI_DATA: [BOOTLOADER PROFILE] Drivers_open                     :         96us
KPI_DATA: [BOOTLOADER PROFILE] LoadHsmRtFw                      :          1us
KPI_DATA: [BOOTLOADER PROFILE] Board_driversOpen                :       4475us
KPI_DATA: [BOOTLOADER PROFILE] CPU load                         :       3605us
KPI_DATA: [BOOTLOADER PROFILE] SBL End                          :          8us
KPI_DATA: [BOOTLOADER_PROFILE] SBL Total Time Taken             :       8684us

Image loading done, switching to application ...

OCMC benchmarking:: Board_init success
Filling up the buffers

master_task

master_task -- start sending
    memcpy Exec Time   I$ Miss    I$ Acc      INST   ICM/sec  INST/sec
         0B     25457us     86576   1075457   2168807       4.2     105.2
       100B     25227us     86072   1222264   2358034       4.2     115.4
       200B     26261us     86573   1372107   2558131       4.1     120.3
       400B     28200us     87814   1676802   2960263       3.8     129.6
       700B     28158us     83225   2115467   3545671       3.7     155.5
      1000B     30558us     85485   2578388   4160642       3.5     168.2
      1500B     34107us     84059   3328963   5152837       3.0     186.6
      2250B     40341us     87028   4471527   6667359       2.7     204.1
      2500B     42833us     86446   4835914   7154867       2.5     206.3
      4096B     53754us     86089   7236358  10350263       2.0     237.8

All tests have passed
\endcode
\endcond

