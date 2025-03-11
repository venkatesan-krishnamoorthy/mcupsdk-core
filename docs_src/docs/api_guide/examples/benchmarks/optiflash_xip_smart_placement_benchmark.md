# Optiflash XIP Benchmark with Smart Placement {#EXAMPLES_OPTIFLASH_XIP_SP_BENCHMARK}

[TOC]

# Supported Combinations {#EXAMPLES_OPTIFLASH_XIP_SP_BENCHMARK_COMBOS}
\cond SOC_AM263PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/benchmarks/optiflash_benchmark/flash_xip_smart_placement

\endcond

\cond SOC_AM261X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_LP_BOARD_NAME_LOWER
 Example folder | examples/benchmarks/optiflash_benchmark/flash_xip_smart_placement

\endcond

# Introduction

This is the same application as \ref EXAMPLES_OPTIFLASH_OCRAM_BENCHMARK, however, target functions are kept in external flash and smart placement enabled (\ref SMART_PLACEMENT). The effect of it is seen in the execution time.

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
KPI_DATA: [BOOTLOADER_PROFILE] Boot Image Size  : 93 KB
KPI_DATA: [BOOTLOADER_PROFILE] Cores present    :
KPI_DATA: [BOOTLOADER PROFILE] System_init                      :        524us
KPI_DATA: [BOOTLOADER PROFILE] Drivers_open                     :        126us
KPI_DATA: [BOOTLOADER PROFILE] LoadHsmRtFw                      :       8447us
KPI_DATA: [BOOTLOADER PROFILE] Board_driversOpen                :       2744us
KPI_DATA: [BOOTLOADER PROFILE] CPU load                         :      22121us
KPI_DATA: [BOOTLOADER PROFILE] SBL End                          :         18us
KPI_DATA: [BOOTLOADER_PROFILE] SBL Total Time Taken             :      33982us

Image loading done, switching to application ...

OCMC benchmarking:: Board_init success
Filling up the buffers

master_task

master_task -- start sending
    memcpy Exec Time   I$ Miss    I$ Acc      INST   ICM/sec  INST/sec
         0B     11014us     15315    498221   2195857       1.7     246.2
       100B     11625us     15494    557616   2384970       1.6     253.4
       200B     12210us     14197    579859   2584748       1.4     261.4
       400B     13628us     16335    735752   2987079       1.5     270.7
       700B     15389us     14986    873334   3572196       1.2     286.7
      1000B     17837us     17258   1115790   4187693       1.2     289.9
      1500B     22259us     13811   1278045   5179595       0.8     287.4
      2250B     29759us     16555   1734787   6694864       0.7     277.8
      2500B     32200us     16010   1832068   7181934       0.6     275.5
      4096B     46572us     16070   2860229  10377804       0.4     275.2

All tests have passed

\endcode
\endcond

\cond SOC_AM261X
\code
Starting OSPI Bootloader ...
KPI_DATA: [BOOTLOADER_PROFILE] Boot Media       : NOR SPI FLASH
KPI_DATA: [BOOTLOADER_PROFILE] Boot Media Clock : 166.667 MHz
KPI_DATA: [BOOTLOADER_PROFILE] Boot Image Size  : 93 KB
KPI_DATA: [BOOTLOADER_PROFILE] Cores present    :
KPI_DATA: [BOOTLOADER PROFILE] System_init                      :        505us
KPI_DATA: [BOOTLOADER PROFILE] Drivers_open                     :         97us
KPI_DATA: [BOOTLOADER PROFILE] LoadHsmRtFw                      :          1us
KPI_DATA: [BOOTLOADER PROFILE] Board_driversOpen                :       4488us
KPI_DATA: [BOOTLOADER PROFILE] CPU load                         :      17981us
KPI_DATA: [BOOTLOADER PROFILE] SBL End                          :          8us
KPI_DATA: [BOOTLOADER_PROFILE] SBL Total Time Taken             :      23082us

Image loading done, switching to application ...

OCMC benchmarking:: Board_init success
Filling up the buffers

master_task

master_task -- start sending
    memcpy Exec Time   I$ Miss    I$ Acc      INST   ICM/sec  INST/sec
         0B      9099us     15827    469124   2195561       2.1     298.0
       100B      9602us     16130    528723   2384680       2.1     306.7
       200B     10035us     13975    550468   2584512       1.7     318.1
       400B     11153us     16325    704276   2986674       1.8     330.7
       700B     12556us     14824    843990   3571789       1.5     351.3
      1000B     14475us     17269   1085599   4187298       1.5     357.3
      1500B     17968us     13723   1247664   5179069       0.9     356.0
      2250B     23982us     17051   1703055   6694086       0.9     344.7
      2500B     25901us     15922   1802392   7181096       0.8     342.4
      4096B     37595us     16079   2829983  10376565       0.5     340.9

All tests have passed

\endcode
\endcond

