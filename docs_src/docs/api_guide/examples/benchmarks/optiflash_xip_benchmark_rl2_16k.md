# Optiflash XIP Benchmark with 16KB L2 Cache {#EXAMPLES_OPTIFLASH_XIP_16K_BENCHMARK}

[TOC]

# Supported Combinations {#EXAMPLES_OPTIFLASH_XIP_16K_BENCHMARK_COMBOS}
\cond SOC_AM263PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/benchmarks/optiflash_benchmark/flash_xip_l2_cache_16k

\endcond

\cond SOC_AM261X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_LP_BOARD_NAME_LOWER
 Example folder | examples/benchmarks/optiflash_benchmark/flash_xip_l2_cache_16k

\endcond

# Introduction

This is the same application as \ref EXAMPLES_OPTIFLASH_OCRAM_BENCHMARK, however, target functions are kept in external flash and L2 cache of 16KB is enabled. The effect of it is seen in the execution time.

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
KPI_DATA: [BOOTLOADER PROFILE] LoadHsmRtFw                      :       9336us
KPI_DATA: [BOOTLOADER PROFILE] Board_driversOpen                :       2759us
KPI_DATA: [BOOTLOADER PROFILE] CPU load                         :       3862us
KPI_DATA: [BOOTLOADER PROFILE] SBL End                          :         17us
KPI_DATA: [BOOTLOADER_PROFILE] SBL Total Time Taken             :      16716us

Image loading done, switching to application ...

OCMC benchmarking:: Board_init success
Filling up the buffers

master_task

master_task -- start sending
    memcpy Exec Time   I$ Miss    I$ Acc      INST   ICM/sec  INST/sec
         0B     39194us     86769   1072743   2170576       2.7      68.4
       100B     39809us     87314   1218601   2360071       2.7      73.2
       200B     39920us     85347   1370911   2559908       2.6      79.2
       400B     42264us     87497   1670641   2962137       2.6      86.6
       700B     42304us     83523   2112108   3547545       2.4     103.6
      1000B     45358us     85778   2575572   4162536       2.3     113.3
      1500B     49447us     85142   3324430   5155015       2.1     128.8
      2250B     57111us     86513   4466199   6669640       1.9     144.2
      2500B     59938us     86307   4830701   7157259       1.8     147.5
      4096B     74117us     86666   7231126  10353174       1.4     172.5

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
KPI_DATA: [BOOTLOADER PROFILE] Board_driversOpen                :       4501us
KPI_DATA: [BOOTLOADER PROFILE] CPU load                         :       3607us
KPI_DATA: [BOOTLOADER PROFILE] SBL End                          :          8us
KPI_DATA: [BOOTLOADER_PROFILE] SBL Total Time Taken             :       8712us

Image loading done, switching to application ...

OCMC benchmarking:: Board_init success
Filling up the buffers

master_task

master_task -- start sending
    memcpy Exec Time   I$ Miss    I$ Acc      INST   ICM/sec  INST/sec
         0B     31201us     85983   1073886   2169476       3.4      85.9
       100B     31901us     86247   1223635   2358979       3.3      91.3
       200B     32214us     85832   1372983   2558957       3.3      98.1
       400B     34200us     87916   1674185   2961071       3.2     106.9
       700B     33988us     82973   2116351   3546487       3.0     128.9
      1000B     36400us     85692   2579868   4161456       2.9     141.2
      1500B     39516us     84308   3327332   5153546       2.6     161.1
      2250B     45826us     86186   4470127   6667998       2.3     179.7
      2500B     48070us     86331   4837108   7155812       2.2     183.8
      4096B     59326us     85987   7234534  10351014       1.8     215.5

All tests have passed

\endcode
\endcond

