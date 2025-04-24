# Enabling XIP or eXecute In Place {#BOOTFLOW_XIP}

[TOC]

## Introduction

- Normally, when running a application, the application code is first copied to RAM by bootloader and then code executes from RAM.
- XIP or eXecute In Place allows a application to execute part of the code from flash without having to copy to RAM.
- Advantage is, this allows users to have a larger code size limited by flash size rather than limited by RAM size.
- Disadvantage is,
  - The flash memory is typically slower (~300MB/s bandwidth) vs RAM memory ( > 1600 MB/s),
  - Due to this, execution speed, esp when code is not cached in the CPU cache, will be slower as compared to when executing from RAM.
- However in some situations it is needed to execute code from flash for non-real time, non high performance code.
- XIP allows to do this.

## Additional References

See also these additional pages for more details and examples about XIP,
\cond SOC_AM64X || SOC_AM243X
- To understand and run a example in XIP mode see
  - \ref EXAMPLES_KERNEL_DPL_XIP_BENCHMARK
\endcond

\cond SOC_AM263PX || SOC_AM261X
- To understand and run a example in XIP mode see
  - \ref BENCHMARK_SMART_PLACEMENT_COMBOS
\endcond

- To understand overall boot flow see, \ref BOOTFLOW_GUIDE

## Pre-requisites

- The flash memory should be visible to the CPU, in "direct access mode (DAC)" i.e memory mapped mode.
  - Here the contents of the flash can be read as any other memory region.
  - This typically is a "read-only" memory
- The secondary bootloader needs to enable flash at highest throughput mode in this DAC mode, before booting the application.
- The application entry point, interrupt vectors and initial code upto `main()` should still execute from RAM.
  After `main()` the code can execute from flash.

## Enable XIP for an application

### Using linker.cmd

To enable XIP for a application, below changes need to be done,

- Enable cache for the XIP flash region. This is need to get better performance for the XIP execution
     - On R5F, this is done by adding a MPU entry for region `0x60000000` of size 256MB. This can be done via SysConfig.
     - If a CPU, say M4F, does not have any cache, then recommend to not use XIP for that CPU.
     - A sample MPU setting on AM64x, AM243x SOC done via SysConfig is shown below.
       - Make sure to enable code execution, and cache for this region.

      \imageStyle{bootflow_xip_mpu_setup.png,width:60%}
      \image html bootflow_xip_mpu_setup.png "Flash section in R5F MPU"

- Update the linker command file to re-direct required `.text` and `.rodata` sections to `FLASH` region as shown below
    \code

    SECTIONS {
        ...
        GROUP {
            .text.hwi: palign(8)
            .text.cache: palign(8)
            .text.mpu: palign(8)
            .text.boot: palign(8)
            .text.main: palign(8) /*  this helps ccs to put breakpoint at main */
            .text:abort: palign(8) /* this helps in loading symbols when using XIP mode */
        } > MSRAM

        cio > MSRAM
        {
            -llibsysbm.a<trgmsg.c.obj> (.text)
        }
        ...
        GROUP {
            .text:   {} palign(8)   /* This is where code resides */
            .rodata: {} palign(8)   /* This is where const's go */
        } > FLASH
        ...
        GROUP {
            .rodata.cfg: {} palign(8)   /* MPU configurations */
        } > MSRAM
    }

    MEMORY
    {
        ...
        FLASH     : ORIGIN = 0x60100000 , LENGTH = 0x80000
        ...
    }
    \endcode

- When printing logs, CCS utilizes CIO breakpoints. For loading and running XIP .out from CCS, it's essential to keep -llibsysbm.a<trgmsg.c.obj> (.text) inside MSRAM. Additionally, ensure that the main symbol is also kept in the MSRAM because CCS uses it to halt the core at the main when loading the .out.

- The same process can be repeated for multiple CPUs if needed, only make sure the `FLASH` defined in `MEMORY { ... }` for the
  linker command files of each CPU are non-overlapping.

- **NOTE**, when multiple CPUs run using XIP, the overall available flash bandwidth get split across multi-CPUs. So
  the overall performance will degrade vs using single CPU in XIP mode. However, functionally nothing restricts such a mode of operation.

- As part of post build step, one extra step is run as compared to non-XIP case, as listed below
  - `xipGen` tool is used to split the application into non-XIP and XIP sections

- The file containing XIP sections is additionally flashed to the flash using the special `flash-xip` command passed to the flash writer

- **NOTE**, the secondary bootloader remains exactly the same when running applications in XIP or non-XIP mode.

- For all the SDK examples
  - The linker command is updated to include the `FLASH` memory segment. The code/rodata section are NOT re-directed to FLASH by default though, unless mentioned otherwise in the example.
  - XIP post-build steps are always invoked as part of application post build. Invoking these steps even though there is no XIP section has no side effect.
  - The default flash writer config file has the flashing command needed to flash the XIP sections. Again, if XIP sections are not present there is no side effect on normal non-XIP operation.

- Thus, all one needs to do to enable XIP is
  - Add a MPU/MMU entry to mark the flash region as executable + cached
  - And update the linker command to mark the code/rodata sections as `FLASH` instead of RAM.
  - Rest of the steps remain exactly the same as non-XIP case.

### Using Memory Configurator 

#### Moving .rodata and .text to flash
As mentioned in the previous section, move <b>`.rodata`</b> and <b>`.text`</b> in external flash, as shown in the following image:

\imageStyle{enabling_xip_mem_configurator_1.png,width:80%}
\image html enabling_xip_mem_configurator_1.png "Moving text and rodata to flash."

Here load and run memory, both are set to FLASH memory. 

Make sure that <b>`Alignment with padding`</b> checkbox has been checked.

#### Moving cfg rodata to internal memory 
Then, it is required to move <b>`.rodata.cfg`</b> in the internal memory. For this, refer to the following image:

\imageStyle{enabling_xip_mem_configurator_2.png,width:80%}
\image html enabling_xip_mem_configurator_2.png "Moving cfg rodata to internal memory."

Here, <b>`.cfg.rodata`</b> output section has been added in <b>`Text Segments`</b> group. 

Make sure that <b> `Alignment with padding` </b> checkbox has been checked.

#### Moving CIO to internal memory

Refer to following image:

\imageStyle{enabling_xip_mem_configurator_3.png,width:80%}
\image html enabling_xip_mem_configurator_3.png "Moving CIO to internal memory."

1. add <b>`cio`</b> output section to <b>`Text Segments`</b> group.
2. Make sure that <b>`Alignment with padding`</b> checkbox has been checked.
3. Add <b>`-llibsysbm.a<trgmsg.c.obj> (.text)`</b> as the input section 

With the above, this will direct cio library in internal memory.

This step is required if CCS logs are enabled. In production build, CCS logs should be disabled.

## Enabling secure XIP using OTFA

- Applications stored in external flash are susceptible to physical and logical attacks. Ensuring the security and safety of the image executed in place is important to achieve advanced security for the device.
- Signing and encrypting application image to be executed from flash enables this. AM261X and AM263PX are equipped with OTFA (On-The-Fly-Authentication and Decryption) hardware module to authenticate and decrypt an application running from flash.
- OTFA can be configured to authenticate and decrypt up to four distinct regions in the flash, with different keys.
- The application binary, converted to MCELF format is post-processed for safety and security using the __`genimage.py`__ tool [Refer \ref TOOLS_BOOT]

To enable security in XIP image,
  1. Enter the OTFA configuration settings in JSON format like below:
    \code
    {
    "mac_size": 4,
    "regions": [
        {
            "start": "0x60000000",
            "size": "0x1000000",
            "authKeyID" : 1,
            "authKey": "../../../../../../source/security/security_common/tools/boot/signing/mcu_custMek.key",
            "encKeyID" : 1,
            "encKey": "../../../../../../source/security/security_common/tools/boot/signing/mcu_custMek.key",
            "kdSalt" : "../../../../../../source/security/security_common/tools/boot/signing/kd_salt.txt",
            "keyFetchMode" : 1,
            "cryptoMode":"gcm",
            "eccEnable": false
        }
        ]
    }
    \endcode
    * KeyIDs correspond to the indices of the keys in Keyring, which will be used by __HsmServer__ for authentication and decryption.
        * If KeyID=1 [root key], HKDF derives a key from the input key file using the input salt. Derived keys will be used for signing and encryption.
        * If KeyID >= 32, derivation is skipped. The plain key inputs are used for signing and encryption.
        * Example JSON Path : mcu_plus_sdk/tools/boot/otfa_eccm/otfaConf.json
  2. Build the application image with the above JSON file as a tool input
      * Example : _`make -s DEVICE=am263px DEVICE_TYPE=HS oeconfig=mcu_plus_sdk/tools/boot/otfa_eccm/otfaConf.json all`_
      * This generates
          * a post-processed MCELF_XIP image, encrypted and authenticated with DSMEK
          * a note-appended MCELF_RAM image, that contains the OTFA configuration parameters' details
  3. Flash the image using uart_uniflash.py tool with any sbl_ospi bootloader. (example: sbl_ospi_multicore_elf)
  4. If using auxiliary keys, generate a keyring certificate containing the same key material and import the certificate in SBL build


## Debugging XIP applications

- XIP applications can not be loaded via CCS, hence to debug a XIP application one needs to always flash and run the application
  and then "load symbols" via CCS to debug the application

- Another alternative is develop and debug the application with all code in "RAM" and then just update the linker command to use "FLASH"
  and do the final test or debug with application in XIP mode.

- The CCS option to load symbols is shown below,

    \imageStyle{bootflow_xip_load_symbols.png,width:60%}
    \image html bootflow_xip_load_symbols.png "CCS Load Symbols"

- Normal "SW" breakpoints in CCS wont work for code in flash, and "HW" breakpoints should be used.
 - To put a breakpoint CCS needs to write a special instruction at the point in code,
 - However since the flash memory is "read-only", this will result in a error, hence one should use "HW" breakpoints instead

- Below shows a example of putting a HW breakpoint,

    \imageStyle{bootflow_xip_hw_break_point.png,width:60%}
    \image html bootflow_xip_hw_break_point.png "HW Breakpoint"

- When prompted enter the function name on which you want the breakpoint to hit.




