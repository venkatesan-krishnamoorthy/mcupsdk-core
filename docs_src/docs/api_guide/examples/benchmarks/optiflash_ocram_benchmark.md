# Optiflash OCRAM Benchmark {#EXAMPLES_OPTIFLASH_OCRAM_BENCHMARK}

[TOC]

# Supported Combinations {#EXAMPLES_OPTIFLASH_OCRAM_BENCHMARKCOMBOS}
\cond SOC_AM263PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/benchmarks/optiflash_benchmark/ocram

\endcond

\cond SOC_AM261X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_LP_BOARD_NAME_LOWER, @VAR_BOARD_NAME_LOWER
 Example folder | examples/benchmarks/optiflash_benchmark/ocram

\endcond

# Introduction


- This demo provides a means of measuring the performance of a realistic application where the text of the application is sitting in various memory locations and the data is sitting in On-Chip-Memory RAM (referred to as OCM, OCMC or OCMRAM).
- The application executes 10 different configurations of the same text varying by data vs. instruction cache intensity. Each test calls 16 separate functions 500 total times in random order.
- The most instruction intensive example achieves a instruction cache miss rate (ICM/sec) of ~3-4 million per second when run entirely from OCMRAM. This is a rate that we have similarly seen in real-world customer examples.
- More data intensive tests have more repetitive code, achieving much lower ICM rates.

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
KPI_DATA: [BOOTLOADER_PROFILE] Boot Image Size  : 121 KB
KPI_DATA: [BOOTLOADER_PROFILE] Cores present    :
r5f0-0
KPI_DATA: [BOOTLOADER PROFILE] System_init                      :        603us
KPI_DATA: [BOOTLOADER PROFILE] Drivers_open                     :        137us
KPI_DATA: [BOOTLOADER PROFILE] LoadHsmRtFw                      :       9335us
KPI_DATA: [BOOTLOADER PROFILE] Board_driversOpen                :       2758us
KPI_DATA: [BOOTLOADER PROFILE] CPU load                         :       5815us
KPI_DATA: [BOOTLOADER PROFILE] SBL End                          :         17us
KPI_DATA: [BOOTLOADER_PROFILE] SBL Total Time Taken             :      18668us

Image loading done, switching to application ...

OCMC benchmarking:: Board_init success
Filling up the buffers

master_task

master_task -- start sending
    memcpy Exec Time   I$ Miss    I$ Acc      INST   ICM/sec  INST/sec
         0B     12450us     85318   1046450   2162880       8.5     214.6
       100B     12998us     84394   1191682   2352420       8.0     223.5
       200B     13667us     84705   1341724   2552549       7.7     230.7
       400B     15044us     85799   1643566   2954476       7.0     242.5
       700B     16813us     82423   2084262   3540160       6.1     260.0
      1000B     19206us     84301   2546558   4155016       5.4     267.2
      1500B     23748us     82726   3296846   5147364       4.3     267.7
      2250B     31153us     84861   4437201   6662237       3.4     264.1
      2500B     33682us     86060   4802825   7149636       3.2     262.2
      4096B     48094us     84698   7203272  10345626       2.2     265.7

All tests have passed
\endcode
\endcond

\cond SOC_AM261X
\code
Starting OSPI Bootloader ...
KPI_DATA: [BOOTLOADER_PROFILE] Boot Media       : NOR SPI FLASH
KPI_DATA: [BOOTLOADER_PROFILE] Boot Media Clock : 166.667 MHz
KPI_DATA: [BOOTLOADER_PROFILE] Boot Image Size  : 121 KB
KPI_DATA: [BOOTLOADER_PROFILE] Cores present    :
r5f0-0
KPI_DATA: [BOOTLOADER PROFILE] System_init                      :        497us
KPI_DATA: [BOOTLOADER PROFILE] Drivers_open                     :         96us
KPI_DATA: [BOOTLOADER PROFILE] LoadHsmRtFw                      :          1us
KPI_DATA: [BOOTLOADER PROFILE] Board_driversOpen                :       4490us
KPI_DATA: [BOOTLOADER PROFILE] CPU load                         :       5181us
KPI_DATA: [BOOTLOADER PROFILE] SBL End                          :          8us
KPI_DATA: [BOOTLOADER_PROFILE] SBL Total Time Taken             :      10275us

Image loading done, switching to application ...

OCMC benchmarking:: Board_init success
Filling up the buffers

master_task

master_task -- start sending
    memcpy Exec Time   I$ Miss    I$ Acc      INST   ICM/sec  INST/sec
         0B     10195us     84232   1049510   2162638      10.2     262.0
       100B     10709us     84708   1193273   2352112       9.8     271.3
       200B     11224us     84838   1342528   2552134       9.3     280.8
       400B     12364us     86139   1644728   2954222       8.6     295.1
       700B     13757us     82472   2087699   3539614       7.4     317.8
      1000B     15684us     83935   2550506   4154643       6.6     327.1
      1500B     19389us     83647   3302552   5146808       5.3     327.8
      2250B     25322us     85830   4443354   6661437       4.2     324.9
      2500B     27326us     85986   4808912   7148822       3.9     323.1
      4096B     38978us     84819   7211679  10344260       2.7     327.8

All tests have passed

\endcode
\endcond

