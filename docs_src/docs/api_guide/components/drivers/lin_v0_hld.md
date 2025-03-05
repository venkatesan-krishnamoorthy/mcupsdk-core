# LIN HLD {#DRIVERS_LIN_V0_HLD_PAGE}

[TOC]

The General-Purpose LIN/SCI driver provides APIs to configure the available LIN
modules in multiple modes.

## Features Supported

- Compatibility with LIN 1.3 , 2.0, and 2.1 protocols.
- Configurable baud rate up to 20 kbps.
- Two external pins: LINRX and LINTX.
- Multi-buffered receive and transmit units.
- Identification masks for message filtering.
- Automatic commander header generation
    - Programmable synchronization break field.
    - Synchronization field.
    - Identifier field.
- Responder Automatic Synchronization
    - Synchronization break detection.
    - Optional baud rate update.
    - Synchronization validation.
- 231 programmable transmission rates with 7 fractional bits.
- Wakeup on LINRX active level from transceiver.
- Automatic idle bus detection
- Error detection
    - Bit error.
    - Bus error.
    - No-response error.
    - Checksum error.
    - Synchronization field error.
    - Parity error.
- Capability to use Direct Memory Access (DMA) to transmit and receive data.
- 2 interrupt lines (INT0 and INT1) with user-configurable interrupt sources
    - Receive.
    - Transmit.
    - ID, error, and status.
- Support for LIN 2.0 checksum.
- Enhanced synchronizer finite state machine (FSM) support for frame processing.
- Enhanced handling of extended frames.
- Enhanced baud rate generator.

## SysConfig Features

@VAR_SYSCFG_USAGE_NOTE

SysConfig can be used to configure below parameters apart from common configurations like Clock,MPU,RAT and others.

- LIN module configuration parameters Such as Clock Source, Operating Mode, Transfer Mode, Baud Rate.
- LIN instances and pin Configuration for each Instance.
- LIN frame specific Configurations such as Parity, LIN Mode(Commander/Responder), Checksum Type, Sync Delimiter, Sync Break.

- Based on above parameters, the SysConfig generated code does below as part of Drivers_open and Drivers_close functions.
    - Set LIN instance parameter configuration.
    - ISR/DMA Configuration for Transactions.

## Features not Supported

- Extended Frames.
- Wake-Up on LINRX active level from transceiver.
- Automatic Wake-Up.

## Usage Overview

### API Sequence

- #LIN_Params_init(): Fill Default Value in #LIN_OpenParams Structure.

- #LIN_open(): Open an LIN HLD Instance.

- #LIN_close(): Close an LIN HLD Instance.

- #LIN_SCI_Frame_init():  Fill Default Value in #LIN_SCI_Frame Structure.

- #LIN_SCI_transferFrame(): Initiate a LIN Transaction.

- #LIN_getHandle(): Get LIN Handle from index.

### Initializing the LIN HLD Driver

#LIN_init() must be called before any other LIN Open is called.

#LIN_open() must be called before calling any LIN APIs.
This function takes index and params to initialize an instance and returns the handle to the LIN instance.

Calling #LIN_close() closes the instance passed.

Please note that the initialization of LIN HLD instances is taken care by the
SysConfig generated code.

## Example Usage

Include the below file to access the APIs
\snippet Lin_Hld_sample_v0.c include

Instance Open Example
\snippet Lin_Hld_sample_v0.c open

Instance Close Example
\snippet Lin_Hld_sample_v0.c close

LIN Commander Write
\snippet Lin_Hld_sample_v0.c lin_commander_write_blocking

## API

\ref DRV_LIN_HLD_MODULE