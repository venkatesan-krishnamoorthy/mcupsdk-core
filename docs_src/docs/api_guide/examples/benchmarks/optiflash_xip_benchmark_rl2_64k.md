# Optiflash XIP Benchmark with 64KB L2 Cache {#EXAMPLES_OPTIFLASH_XIP_64K_BENCHMARK}

[TOC]

# Supported Combinations {#EXAMPLES_OPTIFLASH_XIP_64K_BENCHMARK_COMBOS}
\cond SOC_AM263PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/benchmarks/optiflash_benchmark/flash_xip_l2_cache_64k

\endcond

\cond SOC_AM261X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_LP_BOARD_NAME_LOWER, @VAR_BOARD_NAME_LOWER
 Example folder | examples/benchmarks/optiflash_benchmark/flash_xip_l2_cache_64k

\endcond

# Introduction

This is the same application as \ref EXAMPLES_OPTIFLASH_OCRAM_BENCHMARK, however, target functions are kept in external flash and L2 cache of 64KB is enabled. The effect of it is seen in the execution time.

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
KPI_DATA: [BOOTLOADER PROFILE] Board_driversOpen                :       2773us
KPI_DATA: [BOOTLOADER PROFILE] CPU load                         :       3865us
KPI_DATA: [BOOTLOADER PROFILE] SBL End                          :         17us
KPI_DATA: [BOOTLOADER_PROFILE] SBL Total Time Taken             :      16733us

Image loading done, switching to application ...

OCMC benchmarking:: Board_init success
Filling up the buffers

master_task

master_task -- start sending
    memcpy Exec Time   I$ Miss    I$ Acc      INST   ICM/sec  INST/sec
         0B     20446us     85756   1073014   2168138       5.2     131.0
       100B     20144us     85838   1218341   2357359       5.3     144.5
       200B     21074us     84912   1369630   2557472       5.0     149.9
       400B     22903us     86541   1671421   2959620       4.7     159.6
       700B     23603us     82573   2112567   3545137       4.3     185.5
      1000B     26529us     86151   2574894   4160128       4.0     193.7
      1500B     30906us     85199   3321261   5152454       3.4     205.9
      2250B     38626us     85345   4468294   6667274       2.7     213.2
      2500B     41378us     86052   4830008   7154754       2.6     213.5
      4096B     55926us     85746   7230276  10350539       1.9     228.6

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
         0B     16503us     85713   1076234   2167576       6.4     162.2
       100B     16379us     84832   1221300   2356841       6.4     177.7
       200B     17112us     85971   1370906   2557067       6.2     184.5
       400B     18586us     87576   1673473   2958903       5.8     196.6
       700B     19208us     83417   2115014   3544559       5.4     227.9
      1000B     21494us     85525   2577901   4159290       4.9     239.0
      1500B     24943us     84683   3327743   5151634       4.2     255.1
      2250B     31189us     86719   4470469   6666130       3.4     264.0
      2500B     33269us     86626   4836459   7153610       3.2     265.6
      4096B     45017us     85468   7234375  10349054       2.3     283.9

All tests have passed

\endcode
\endcond

