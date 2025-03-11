# Optiflash XIP Benchmark with 8KB L2 Cache {#EXAMPLES_OPTIFLASH_XIP_8K_BENCHMARK}

[TOC]

# Supported Combinations {#EXAMPLES_OPTIFLASH_XIP_8K_BENCHMARK_COMBOS}
\cond SOC_AM263PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/benchmarks/optiflash_benchmark/flash_xip_l2_cache_8k

\endcond

\cond SOC_AM261X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_LP_BOARD_NAME_LOWER
 Example folder | examples/benchmarks/optiflash_benchmark/flash_xip_l2_cache_8k

\endcond

# Introduction

This is the same application as \ref EXAMPLES_OPTIFLASH_OCRAM_BENCHMARK, however, target functions are kept in external flash and L2 cache of 8KB is enabled. The effect of it is seen in the execution time.

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
KPI_DATA: [BOOTLOADER PROFILE] Board_driversOpen                :       2765us
KPI_DATA: [BOOTLOADER PROFILE] CPU load                         :       3862us
KPI_DATA: [BOOTLOADER PROFILE] SBL End                          :         17us
KPI_DATA: [BOOTLOADER_PROFILE] SBL Total Time Taken             :      16722us

Image loading done, switching to application ...

OCMC benchmarking:: Board_init success
Filling up the buffers

master_task

master_task -- start sending
    memcpy Exec Time   I$ Miss    I$ Acc      INST   ICM/sec  INST/sec
         0B     42429us     84846   1073722   2171188       2.5      63.2
       100B     43629us     85745   1219469   2360448       2.4      66.8
       200B     44235us     86137   1369836   2560637       2.4      71.5
       400B     46522us     88015   1670257   2962838       2.3      78.7
       700B     46363us     83076   2111854   3548107       2.2      94.5
      1000B     50028us     86167   2574150   4163356       2.1     102.8
      1500B     54164us     84277   3322523   5155565       1.9     117.6
      2250B     62366us     86963   4466142   6670464       1.7     132.1
      2500B     64859us     87344   4830520   7157912       1.7     136.3
      4096B     78599us     85887   7230479  10353557       1.3     162.7

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
KPI_DATA: [BOOTLOADER PROFILE] Board_driversOpen                :       4478us
KPI_DATA: [BOOTLOADER PROFILE] CPU load                         :       3609us
KPI_DATA: [BOOTLOADER PROFILE] SBL End                          :          8us
KPI_DATA: [BOOTLOADER_PROFILE] SBL Total Time Taken             :       8692us

Image loading done, switching to application ...

OCMC benchmarking:: Board_init success
Filling up the buffers

master_task

master_task -- start sending
    memcpy Exec Time   I$ Miss    I$ Acc      INST   ICM/sec  INST/sec
         0B     34698us     86508   1075578   2170054       3.1      77.2
       100B     35409us     86897   1223210   2359503       3.0      82.3
       200B     35433us     85547   1373892   2559390       3.0      89.2
       400B     36996us     86875   1675846   2961500       2.9      98.9
       700B     37410us     83367   2116356   3547053       2.8     117.1
      1000B     40295us     86212   2579598   4161845       2.6     127.6
      1500B     43573us     84025   3326077   5154199       2.4     146.1
      2250B     50173us     86438   4470091   6668695       2.1     164.1
      2500B     52256us     86831   4834398   7156358       2.1     169.1
      4096B     63264us     86107   7233876  10351522       1.7     202.1

All tests have passed

\endcode
\endcond

