# Using FOTA Agent (FSS Switch To B) {#EXAMPLES_DRIVERS_FOTA_AGENT}

[TOC]

# Introduction

This example provides a simple use case on how to implement a FOTAAgent in a FOTA use case. FOTAAgent is used to write files received on the interface to the flash.

Hello world application is being embedded into this example as a C array which is then programmed using `FOTAAgent` (\ref DRIVERS_FOTA_AGENT_PAGE) APIs. However, in a real-world use case, a new application will be received on some interface (eg. CAN, Ethernet, etc.) in some packets.

This application, flash the program using the following loop:
\code

    for (uint32_t cnt = 0; cnt < hello_world_release_xip_size; cnt++)
    {
        /*
            as and when a byte is being recv, it is being sent to agent which will handle
            all the intricacies.
        */
        uint8_t byte = hello_world_release_xip[cnt];

        status = FOTAAgent_writeUpdate(&gFotaAgentHandle, &byte, 1);

        DebugP_assert(status == SystemP_SUCCESS);
    }

\endcode

In the actual application, for loop can be replaced with a while loop, which would terminate when all the packets have been received.

Typically, after application compilation, TI post-build step produces .mcelf and .mcelf_xip files. It is required to flash these 2 files in the flash. Therefore, it is required to call `FOTAAgent` API 2 times on these 2 files.

Once both the files are flashed in the external flash, it is required to update the boot sector of the flash.

\code

    offset = BOOINFO_ADDRESS;

    CacheP_inv((void *)(SOC_getFlashDataBaseAddr() + offset), ERASE_SECTOR_SIZE, CacheP_TYPE_ALL);

    memcpy((void *)&bootinfo.bin, (void *)(SOC_getFlashDataBaseAddr() + offset), ERASE_SECTOR_SIZE);

    bootinfo.fields.bootRegion = BOOT_REGION_B;

    status = FLSOPSKD_erase(&gFotaAgentHandle.flopsHandle, offset);

    DebugP_assert(status == SystemP_SUCCESS);

    status = FLSOPSKD_write(&gFotaAgentHandle.flopsHandle, offset, (uint8_t *)&bootinfo.bin, ERASE_SECTOR_SIZE);

    DebugP_assert(status == SystemP_SUCCESS);

    CacheP_inv((void *)(SOC_getFlashDataBaseAddr() + offset), ERASE_SECTOR_SIZE, CacheP_TYPE_ALL);


\endcode


The above code does that.


If the \ref EXAMPLES_DRIVERS_SBL_OSPI_SWAP is being used, the on next board reset, hello world application will run instead of this application.

# Supported Combinations {#EXAMPLES_DRIVERS_FOTA_AGENT_COMBOS}


\cond SOC_AM263PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/fss/fss_switch_b

\endcond

\cond SOC_AM261X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_LP_BOARD_NAME_LOWER
 Example folder | examples/drivers/fss/fss_switch_b

\endcond

# Steps to Run the Example

- **When using makefiles to build**
    - please make sure to build and run example \ref EXAMPLES_HELLO_WORLD_XIP_FSS1 to validate.
    - using python3, run python script bin_to_c_array.py. 
    - note the required combination (\ref EXAMPLES_DRIVERS_FOTA_AGENT_COMBOS) and build using make command (see \ref MAKEFILE_BUILD_PAGE)
- Load the application using \ref EXAMPLES_DRIVERS_SBL_OSPI_SWAP

# Sample Output

\cond SOC_AM263PX
\code

    Starting OSPI Bootloader ...
    KPI_DATA: [BOOTLOADER_PROFILE] Boot Media       : NOR SPI FLASH
    KPI_DATA: [BOOTLOADER_PROFILE] Boot Media Clock : 133.333 MHz
    KPI_DATA: [BOOTLOADER_PROFILE] Boot Image Size  : 66 KB
    KPI_DATA: [BOOTLOADER_PROFILE] Cores present    :
    r5f0-0
    KPI_DATA: [BOOTLOADER PROFILE] System_init                      :        599us
    KPI_DATA: [BOOTLOADER PROFILE] Drivers_open                     :        136us
    KPI_DATA: [BOOTLOADER PROFILE] LoadHsmRtFw                      :       9337us
    KPI_DATA: [BOOTLOADER PROFILE] Board_driversOpen                :       2757us
    KPI_DATA: [BOOTLOADER PROFILE] CPU load                         :       4838us
    KPI_DATA: [BOOTLOADER PROFILE] SBL End                          :         18us
    KPI_DATA: [BOOTLOADER_PROFILE] SBL Total Time Taken             :      17687us

    Image loading done, switching to application ...
    Starting application
    Receiving application...
    Got MCELF file
    Got MCELF_XIP file
    Done writing new application to flash...
    Updating Flash's Boot Sector...
    Finish Updating Flash's Boot Sector... Please reset board to start new application

    Starting OSPI Bootloader ...
    KPI_DATA: [BOOTLOADER_PROFILE] Boot Media       : NOR SPI FLASH
    KPI_DATA: [BOOTLOADER_PROFILE] Boot Media Clock : 133.333 MHz
    KPI_DATA: [BOOTLOADER_PROFILE] Boot Image Size  : 7 KB
    KPI_DATA: [BOOTLOADER_PROFILE] Cores present    :
    r5f0-0
    KPI_DATA: [BOOTLOADER PROFILE] System_init                      :        599us
    KPI_DATA: [BOOTLOADER PROFILE] Drivers_open                     :        136us
    KPI_DATA: [BOOTLOADER PROFILE] LoadHsmRtFw                      :       9336us
    KPI_DATA: [BOOTLOADER PROFILE] Board_driversOpen                :       2766us
    KPI_DATA: [BOOTLOADER PROFILE] CPU load                         :       3787us
    KPI_DATA: [BOOTLOADER PROFILE] SBL End                          :         18us
    KPI_DATA: [BOOTLOADER_PROFILE] SBL Total Time Taken             :      16644us

    Image loading done, switching to application ...
    Hello World!

\endcode
\endcond

\cond SOC_AM261X
\code

    Starting OSPI Bootloader ... 
    KPI_DATA: [BOOTLOADER_PROFILE] Boot Media       : NOR SPI FLASH 
    KPI_DATA: [BOOTLOADER_PROFILE] Boot Media Clock : 166.667 MHz 
    KPI_DATA: [BOOTLOADER_PROFILE] Boot Image Size  : 65 KB 
    KPI_DATA: [BOOTLOADER_PROFILE] Cores present    : 
    KPI_DATA: [BOOTLOADER PROFILE] System_init                      :        443us 
    KPI_DATA: [BOOTLOADER PROFILE] Drivers_open                     :         94us 
    KPI_DATA: [BOOTLOADER PROFILE] LoadHsmRtFw                      :       6251us 
    KPI_DATA: [BOOTLOADER PROFILE] Board_driversOpen                :      22850us 
    KPI_DATA: [BOOTLOADER PROFILE] CPU load                         :       4323us 
    KPI_DATA: [BOOTLOADER PROFILE] SBL End                          :          9us 
    KPI_DATA: [BOOTLOADER_PROFILE] SBL Total Time Taken             :      33973us 

    Image loading done, switching to application ...
    Starting application
    Receiving application... 
    Got MCELF file
    Got MCELF_XIP file
    Done writing new application to flash...
    Updating Flash's Boot Sector...
    Finish Updating Flash's Boot Sector... Please reset board to start new application


    Starting OSPI Bootloader ... 
    KPI_DATA: [BOOTLOADER_PROFILE] Boot Media       : NOR SPI FLASH 
    KPI_DATA: [BOOTLOADER_PROFILE] Boot Media Clock : 166.667 MHz 
    KPI_DATA: [BOOTLOADER_PROFILE] Boot Image Size  : 5 KB 
    KPI_DATA: [BOOTLOADER_PROFILE] Cores present    : 
    KPI_DATA: [BOOTLOADER PROFILE] System_init                      :        443us 
    KPI_DATA: [BOOTLOADER PROFILE] Drivers_open                     :         94us 
    KPI_DATA: [BOOTLOADER PROFILE] LoadHsmRtFw                      :       6251us 
    KPI_DATA: [BOOTLOADER PROFILE] Board_driversOpen                :      24701us 
    KPI_DATA: [BOOTLOADER PROFILE] CPU load                         :       3963us 
    KPI_DATA: [BOOTLOADER PROFILE] SBL End                          :          9us 
    KPI_DATA: [BOOTLOADER_PROFILE] SBL Total Time Taken             :      35464us 

    Image loading done, switching to application ...
    Hello World!
\endcode
\endcond 
