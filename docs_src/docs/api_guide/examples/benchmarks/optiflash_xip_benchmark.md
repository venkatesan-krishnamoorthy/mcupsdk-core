# Optiflash XIP Benchmark {#EXAMPLES_OPTIFLASH_XIP_BENCHMARK}

[TOC]

# Supported Combinations {#EXAMPLES_OPTIFLASH_XIP_BENCHMARKCOMBOS}
\cond SOC_AM263PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/benchmarks/optiflash_benchmark/flash_xip

\endcond

\cond SOC_AM261X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_LP_BOARD_NAME_LOWER, @VAR_BOARD_NAME_LOWER
 Example folder | examples/benchmarks/optiflash_benchmark/flash_xip

\endcond

# Introduction

This is the same application as \ref EXAMPLES_OPTIFLASH_OCRAM_BENCHMARK, however, target functions are kept in external flash. The effect of it is seen in the execution time.

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
KPI_DATA: [BOOTLOADER PROFILE] Board_driversOpen                :       2761us
KPI_DATA: [BOOTLOADER PROFILE] CPU load                         :       3855us
KPI_DATA: [BOOTLOADER PROFILE] SBL End                          :         17us
KPI_DATA: [BOOTLOADER_PROFILE] SBL Total Time Taken             :      16712us

Image loading done, switching to application ...

OCMC benchmarking:: Board_init success
Filling up the buffers

master_task

master_task -- start sending
    memcpy Exec Time   I$ Miss    I$ Acc      INST   ICM/sec  INST/sec
         0B     46566us     88401   1071760   2171688       2.3      57.6
       100B     47008us     86724   1219816   2361040       2.3      62.0
       200B     47977us     86925   1370689   2561127       2.2      65.9
       400B     50518us     89793   1671400   2963213       2.2      72.4
       700B     50618us     85176   2112802   3548732       2.1      86.6
      1000B     55253us     88373   2574724   4164047       2.0      93.1
      1500B     61398us     86541   3322556   5156600       1.7     103.7
      2250B     70884us     88528   4462778   6671463       1.5     116.2
      2500B     74000us     89345   4831231   7159217       1.5     119.5
      4096B     88364us     87994   7229022  10354911       1.2     144.7

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
KPI_DATA: [BOOTLOADER PROFILE] CPU load                         :       3601us
KPI_DATA: [BOOTLOADER PROFILE] SBL End                          :          8us
KPI_DATA: [BOOTLOADER_PROFILE] SBL Total Time Taken             :       8679us

Image loading done, switching to application ...

OCMC benchmarking:: Board_init success
Filling up the buffers

master_task

master_task -- start sending
    memcpy Exec Time   I$ Miss    I$ Acc      INST   ICM/sec  INST/sec
         0B     37013us     87162   1074736   2170362       2.9      72.4
       100B     37628us     86327   1222952   2359690       2.8      77.4
       200B     37858us     85448   1373268   2559775       2.8      83.5
       400B     39842us     88104   1676065   2961887       2.7      91.8
       700B     39757us     83118   2115272   3547263       2.6     110.2
      1000B     43627us     85863   2580078   4162379       2.4     117.8
      1500B     48945us     85644   3326582   5154946       2.2     130.1
      2250B     57802us     88279   4470783   6669791       1.9     142.5
      2500B     60022us     88601   4836857   7157313       1.8     147.3
      4096B     72074us     86891   7237837  10352783       1.5     177.4

All tests have passed

\endcode
\endcond

