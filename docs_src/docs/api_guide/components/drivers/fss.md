# FSS {#DRIVERS_FSS_PAGE}

[TOC]

## Usage of FSS driver

FSS driver is used to configure bootseg IP and ECCM IP.

Bootseg IP is used to perform A/B swap in Firmware-Update-Over-The-Air (FOTA) application. Please refer to Technical Resource Manual of the deivce for more details of this IP.

ECCM is on-the-fly-Ecc module which perform ECC check on the fly which makes XIP from external flash secure. Please refer to Technical Resource Manual of the deivce for more details of this IP.

## Example Usage

### Configuring FSS for Bootseg peripheral

Includes the following files

\snippet Fss_sample.c include

Initilize the following struct

\snippet Fss_sample.c fssconf

Note that, ipBaseAddress address is in CSLR file.

To remap 2nd half of flash to 1st half of the flash (or boot from 2nd half of flash.)

\snippet Fss_sample.c fss_bootfrom_b

To boot from 1st half of flash,

\snippet Fss_sample.c fss_bootfrom_a

Somtimes, it is requried to find from which part of flash, application boots from. Following code snippet shows that:

\snippet Fss_sample.c fss_getbootfrom

### Configuring FSS for ECCM

\snippet Fss_sample.c fss_configeccm

make sure to disable ECC before configuring it.

## API

\ref DRV_FSS_MODULE