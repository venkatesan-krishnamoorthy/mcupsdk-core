# How to use Flash Operation Scheduler Hardware {#FLSOPSKD_IP}

[TOC]

## Introduction

This page goes over different aspect of flash operation scheduler (FLSOPSKD) hardware engine.


### Why is FLSOPSKD Hardware Engine?

OptiFlash technology (\ref OPTIFLASH) enables XIP, in case, where an application is performing flash writes, would look like as follows:

The following image shows the same:
\imageStyle{general_flash_access_request_multicore.png,width:40%}
\image html general_flash_access_request_multicore.png "General Flash Access Usecase"

Here each CPU is requestion data from the external flash through `flash controller` for performing XIP or read from the external flash and sending erase, write or status read request. On top of this, each request is asynchronous in nature, meaning that any request can come at anytime.

External flash is connected to microcontroller over 8 data lines (OSPI) and on same data lines, both reads and writes would happen. And in any flash write scenerio, writes would be happening while XIP is going on. During writing, reading should be stopped which also mean that XIP needs to be stopped and this would have an impact on performance and increased complexity in system design.

To synchronize all the read and write request on same 8bit data bus and to minimize the XIP/Read downtime, FLSOPSKD IP has been added. This will help schedule different flash related transaction by prioritizing XIP/Reads. XIP/Reads are prioritized because writes and erase to a nor flash are anyway very slow (may take multiple seconds for a single operation, depending on flash).

### What is FLSOPSKD Hardware Engine?

\note please refer to TRM and datasheet for details of this hardware.

To achieve this sort of scheduling, with Optiflash, FLSOPSKD Hardware Engine has been added on top of Flash controller.

The following image shows the same:
\imageStyle{flsopskd_internal.png,width:40%}
\image html flsopskd_internal.png "Flash Operation Scheduler Hardware"

One key feature of this hardware is that there is a 8051MCU inside this which is also programable. It has its own program memory (2KB in case of AM263Px) and data memory of 256B.

This 8051 has a very close access to flash controller's configuration and some hooks to know the state of the flash controller (or OSPI controller in case of AM263Px).

R5F CPU or anyother CPU, when it is required to communicate to 8051 would program the MMR registers and signal the firmware that is running inside the 8051 to further process it.

\note  TI provide an 8051 firmware OOB as an example.

## Example Firmware

TI Provides some recommendation on how to write custom implementation of the above described scheduling.

The following image shows the same:
\imageStyle{fw_example_implementation.png,width:40%}
\image html fw_example_implementation.png "Firmware Example Implementation"

On the left hand side, any core which is trying to communicate to 8051 fiirmware would follow the and on the right hand side are the steps that 8051 would follow after recieving signal from SOC core.

Based on the above steps, MCU+ SDK drivers come with prebuit firmware of 8051 and its corresponding R5F drivers.

## Using FLSOPSKD in Application

Please refer to \ref DRIVERS_FLSOPSKD_PAGE
