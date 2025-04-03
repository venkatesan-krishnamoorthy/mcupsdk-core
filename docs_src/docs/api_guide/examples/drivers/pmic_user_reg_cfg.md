# PMIC user register configuration example {#EXAMPLES_PMIC_USER_REG_CFG}

[TOC]

# Introduction
# Introduction

The example demonstrates the the configuration of user space registers for various features in the PMIC. The application
configures the thermal monitoring, voltage monitoring, GPIO pin, Timer and gets the status. Set/Get/clear IRQ mask and flag
Use Pmic_io(Rx/Tx)Byte Api to direct access of register. Refer the PMIC datasheet for more information on the parameters 
configured. The example passes if the configuration and get status is success.

# Supported Combinations {#EXAMPLES_DRIVERS_PMIC_USER_REG_CFG_COMBOS}

\cond SOC_AM261X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 ^              | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_LP_BOARD_NAME_LOWER
 ^              | @VAR_BOARD_NAME_LOWER 
 Example folder | examples/drivers/pmic/pmic_user_reg_cfg

\endcond

\cond SOC_AM263PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 ^              | r5fss0-0 nortos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER 
 Example folder | examples/drivers/pmic/pmic_user_reg_cfg

\endcond

# Steps

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# Sample Output Derby PMIC

Shown below is a sample output when the application is run,
\code
Starting PMIC user space register configuration example !!

Setting BUCK2 configurations...
BUCK2 configurations have been set
Getting actual BUCK2 configurations...
BUCK2 configurations have been obtained
Validating BUCK2 configurations...
BUCK2 configurations have been successfully validated
Setting LDO configurations...
LDO configurations have been set
Getting actual LDO configurations...
LDO configurations have been obtained
Validating LDO configurations...
LDO configurations have been successfully validated
Voltage monitoring status:
BUCK2 Active voltage status: set
BUCK2 over voltage status: cleared
BUCK2 under voltage status: cleared
BUCK2 over voltage protection status: cleared
LDO Active voltage status: set
LDO over voltage status: cleared
LDO under voltage status: cleared
LDO over voltage protection status: cleared
PMIC VMON and BUCK configuration and status report complete


Setting thermal shutdown configurations
Thermal shutdown configurations have been set
Getting actual thermal shutdown configurations...
Thermal configurations have been obtained
Validating thermal shutdown configurations...
Thermal configurations have been successfully validated
Thermal monitoring status:
Thermal immediate shutdown bit: 0
PMIC thermal monitoring configuration and get status complete


Setting GPIO output state as High...
Getting actual GPIO configurations...
GPIO configurations have been obtained...
Validating GPIO configurations, pin state: High...
GPIO configurations have been successfully validated
GPIO Pin status: High
Setting GPO1 output state as LOW...
Getting actual GPIO configurations...
GPIO configurations have been obtained...
Validating GPIO configurations, pin state: Low...
GPIO configurations have been successfully validated
GPIO Pin status: Low
Setting GPO1 as ESM IN...
Getting actual GPIO configurations...
GPIO configurations have been obtained...
Validating GPIO configurations, pin state: ESM IN...
GPIO configurations have been successfully validated

Setting IRQ mask...
Validating IRQ mask status...
IRQ mask have been successfully validated

Get status of all IRQ's...
Clear next IRQ's if its flag set
Cleared IRQ's whose flag were set

Reading initial value of CUSTOMER_SCRATCH1...
Initial value of CUSTOMER_SCRATCH1: 255
Writing expected value of 0 to CUSTOMER_SCRATCH1...
Write complete
Reading actual value of CUSTOMER_SCRATCH1...
Actual CUSTOMER_SCRATCH1 register value: 0
Direct register write and read successful
PMIC user space register configuration example is successful !!
\endcode

# Sample Output Blackbird PMIC

Shown below is a sample output when the application is run,
\code
Starting PMIC user space register configuration example !!

Setting PLDO1 config...
Validating PLDO1 configurations...
PLDO1 configurations have been successfully validated
PLDO voltage, thermal and current limit status
PLDO1 over voltage error status: cleared
PLDO1 under voltage error status: cleared
PLDO1 current limit error status: cleared
PLDO1 Thermal shutdown warning status: cleared
PLDO1 Thermal shutdown error status: cleared

Setting LDO2 config...
Validating LDO2 configurations...
LDO2 configurations have been successfully validated
LDO voltage, thermal and current limit status
LDO2 over voltage error status: cleared
LDO2 under voltage error status: cleared
LDO2 current limit error status: cleared
LDO2 Thermal shutdown warning status: cleared
LDO2 Thermal shutdown error status: cleared
PMIC PLDO and LDO configuration and status report complete

Setting GPO1 output state as High...
Getting actual GPIO configurations...
GPIO configurations have been obtained...
Validating GPIO configurations, pin state: High...
GPIO configurations have been successfully validated
GPIO Pin status: High
Setting GPO1 output state as LOW...
Getting actual GPIO configurations...
GPIO configurations have been obtained...
Validating GPIO configurations, pin state: Low...
GPIO configurations have been successfully validated
GPIO Pin status: Low
Setting GPO1 as NINT...
Getting actual GPIO configurations...
GPIO configurations have been obtained...
Validating GPIO configurations, pin state: NINT...
GPIO configurations have been successfully validated

Setting multiple IRQ mask and configs...
Validating IRQ mask status...
IRQ mask have been successfully validated

Get status of all IRQ's...
Clear next IRQ's if its flag set
Cleared IRQ's whose flag were set

Setting PMIC timer configurations...
Validating Timer configurations...
Timer configurations have been successfully validated
Adding delay of 3 sec to increment the timer count
Pmic Timer count value : 4

Reading initial value of CUSTOMER_SCRATCH1...
Initial value of CUSTOMER_SCRATCH1: 0
Writing expected value of 255 to CUSTOMER_SCRATCH1...
Write complete
Reading actual value of CUSTOMER_SCRATCH1...
Actual CUSTOMER_SCRATCH1 register value: 255
Direct register write and read successful
PMIC user space register configuration example is successful !!
\endcode