# PMIC {#BOARD_PMIC_PAGE}

[TOC]

\cond SOC_AM261X
The PMIC driver provides API to control I2C/SPI based PMIC present in the board. It supports configuration
of various features/modules in the PMIC. I2C/MCSPI controller is used to read/write to the PMIC registers.
Refer to the corresponding PMIC datasheet for more details.
\endcond
\cond SOC_AM263PX
The PMIC driver provides API to control SPI based PMIC present in the board. It supports configuration
of various features/modules in the PMIC. MCSPI controller is used to read/write to the PMIC registers.
Refer to the corresponding PMIC datasheet for more details.
\endcond

## Features Supported

- Support enable/disable watchdog
- Watchdog in Trigger and Q&A mode with interrupt/reset support upon failure
- GPIO configuration
- Thermal monitoring
- Voltage monitoring
- IRQ
- ESM

## SysConfig Features

\cond SOC_AM261X
@VAR_SYSCFG_USAGE_NOTE
\endcond

\cond SOC_AM261X
- Option to select the PMIC
- Supported PMIC's
    - TPS65386xx (Blackbird)
    - TPS65036xx (Derby)
\endcond
\cond SOC_AM263PX
NA
\endcond

## Features NOT Supported

- NA

## Important Usage Guidelines

- Power cycle the board to restore the PMIC register configurations.

## Example Usage

Include the below file to access the APIs
\snippet Pmic_sample.c include

Instance Open Blackbird PMIC Example
\snippet Pmic_sample.c open_blackbird

\cond SOC_AM261X
Instance Open Derby PMIC Example
\snippet Pmic_sample.c open_derby
\endcond

Instance Close Example
\snippet Pmic_sample.c close

## API

\ref BOARD_PMIC_MODULE