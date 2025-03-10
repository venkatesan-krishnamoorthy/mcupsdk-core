# FLSOPSKD Benchmark {#EXAMPLES_FLSOPSKD_BENCHMARK}

[TOC]

# Supported Combinations {#EXAMPLES_FLSOPSKD_BENCHMARK_COMBOS}

\cond SOC_AM261X || SOC_AM263PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 ^              | r5fss0-1 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER, @VAR_LP_BOARD_NAME_LOWER
 Example folder | examples/benchmarks/flsopskd_benchmark

\endcond

# Introduction

\note Number in this example is for illustration and will vary from flash to flash and age of flash.

One of the key KPI of FLSOPSKD is the worst case XIP downtime. This application does the following:
1. Core r5fss0-1 performs flash writes and erase while r5fss0-0 is performing XIP.
2. Core r5fss0-1 reads the worst case XIP downtime, measued by FLSOPSKD, and prints it.

# Building benchmark application

building normally with make command will build the application.

# Running benchmark application

After running the application, the following is the expected output:


\code

        Starting OSPI Bootloader ...
        KPI_DATA: [BOOTLOADER_PROFILE] Boot Media       : NOR SPI FLASH
        KPI_DATA: [BOOTLOADER_PROFILE] Boot Media Clock : 133.333 MHz
        KPI_DATA: [BOOTLOADER_PROFILE] Boot Image Size  : 172 KB
        KPI_DATA: [BOOTLOADER_PROFILE] Cores present    :
        r5f0-0
        r5f0-1
        KPI_DATA: [BOOTLOADER PROFILE] System_init                      :        603us
        KPI_DATA: [BOOTLOADER PROFILE] Drivers_open                     :        137us
        KPI_DATA: [BOOTLOADER PROFILE] LoadHsmRtFw                      :       9336us
        KPI_DATA: [BOOTLOADER PROFILE] Board_driversOpen                :      96857us
        KPI_DATA: [BOOTLOADER PROFILE] CPU load                         :       6768us
        KPI_DATA: [BOOTLOADER PROFILE] SBL End                          :         18us
        KPI_DATA: [BOOTLOADER_PROFILE] SBL Total Time Taken             :     113722us

        Image loading done, switching to application ...

        Starting Benchmark.

        Starting XIP Function.
        XIP Function ended.
        [r5f0-1]    24.409322s : Time to flash : 24 sec
        [r5f0-1]    24.409348s : Status Polls Sent: 550
        [r5f0-1]    24.409373s : Worst Case XIP Downtime Measured: 2772780 ns
        [r5f0-1]    24.409406s : All tests have passed!!

\endcode

# Results

From core R5F01, total time to flash to external flash was 27sec and of which 28ms was total XIP downtime, while other core was performing XIP.

