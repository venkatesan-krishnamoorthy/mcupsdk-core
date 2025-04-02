# OptiFlash Memory Technology {#OPTIFLASH}

[TOC]

## Introduction

Optiflash memory technology provides an ecosystem of silicon hardware peripherals and software tools to improve the application performance executing from external flash.

For more information, please go through the following resources:
1. \htmllink{https://www.ti.com/lit/an/spradf0a/spradf0a.pdf, TI OptiFlash Memory Technology Appnote}
2. \htmllink{https://dev.ti.com/tirex/explore/node?node=A__AbwavWpXk6C8-NYNjOH-pA__AM26X-ACADEMY__t0CaxbG__LATEST&search=OptiFlash, OptiFlash Tool MCU Academy}
3. Technical reference manual for that particular device (eg. AM261x, AM263Px, etc).

The following image shows what Optiflash provides:

\imageStyle{optiflash_entire.png,width:70%} \image html optiflash_entire.png "OptiFlash Technology Ecosystem"

## Software Tools

There are 3 software tools

### Smart placement

Smart placement is a name given to a process, using which functions and other linker-placed objects are distributed across different memories, while accounting for their criticality, directly from the source code.

To get started with the smart placement, go to: \ref SMART_PLACEMENT_GETTING_STARTED

For detailed understanding on how smart placement work, go to: \ref SMART_PLACEMENT

### Optishare

The Optishare tool is used to remove redundant code in multicore projects.

Read more on this at \ref OPTIFLASH_OPTISHARE

### Overlay Manager

Although this is not a tool as such, however, this is a technique to bring code from external memory to internal memory at runtime.

\cond SOC_AM263PX
Please refer to \ref EXAMPLES_SRAM_OVERLAY to see how to implement this.
\endcond

## SDK Drivers

### Fast Local Copy (FLC)

On how to configure, please refer to \ref OPTIFLASH_CONFIGURE

For example, \ref EXAMPLES_FLC

### Region Address Translation (RAT)

On how to configure, please refer to \ref OPTIFLASH_CONFIGURE

For example, \ref EXAMPLES_RAT

### Remote L2 Cache (RL2)

On how to configure, please refer to \ref OPTIFLASH_CONFIGURE

For example, \ref EXAMPLES_RL2

### On-the-fly-Safety and Security

On how to enable safety and security on an application,
1. For Safety: \ref OPTIFLASH_ECCM
2. For Security: Refer to **Enabling secure XIP using OTFA** of \ref BOOTFLOW_XIP

By default, Safety and Security is disabled. For an application, it should be enabled with special build flags as mentioned in the above links.

### Firmware-Update-Over-Air (FOTA)

To enable FOTA use-case, FOTA accelerators has been added in the SOC. More can be read on this in the TRM and appnote.

\ref bootseg_ip_working

In the SDK, go through the following resources on how to enable FOTA use case:
 S.No | SDK Component | Description Page | SDK Driver Page | Examples
 -----|---------------|-------------------------|----------|----------
 1    | A/B Swap      | \ref bootseg_ip_working, | \ref DRIVERS_FSS_PAGE, | \ref EXAMPLES_DRIVERS_SBL_OSPI_SWAP, \ref EXAMPLES_DRIVERS_SWAP_TO_B,
 2    | FLSOPSKD      | \ref FLSOPSKD_IP, | \ref DRIVERS_FLSOPSKD_PAGE, |\ref EXAMPLES_FLSOPSKD_BENCHMARK,
 3    | FOTA Agent    |  | \ref DRIVERS_FOTA_AGENT_PAGE, | \ref EXAMPLES_DRIVERS_FOTA_AGENT,


### Flash Controller (OSPI)

Here the aim is to configure the flash to work at full speed. On how to use flash, please refer to \ref BOARD_FLASH_PAGE
