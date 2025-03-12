
#include <stdio.h>
//! [include]
#include <board/pmic.h>
//! [include]

void open(void)
{
//! [open_blackbird]

PMIC_Params gPmicParams[CONFIG_PMIC_NUM_INSTANCES] =
{
    {
        .deviceType  = PMIC_DEV_BB_TPS65386X,
        .commMode    = PMIC_INTF_SPI,
        .instType    = PMIC_MAIN_INST,
        .instance    = CONFIG_MCSPI0,
    },
};

PMIC_Handle[CONFIG_PMIC0] = PMIC_open(CONFIG_PMIC0, &gPmicParams[CONFIG_PMIC0]);

/*gPmicHandle[CONFIG_PMIC0] return from PMIC_open*/
PMIC_configure(gPmicHandle[CONFIG_PMIC0]);
//! [open_blackbird]

//! [open_derby]

PMIC_Params gPmicParams[CONFIG_PMIC_NUM_INSTANCES] =
{
    {
        .i2cAddr     = 0x60,
        .instance    = CONFIG_MCSPI0,
    },
};

PMIC_Handle[CONFIG_PMIC0] = PMIC_open(CONFIG_PMIC0, &gPmicParams[CONFIG_PMIC0]);

/*gPmicHandle[CONFIG_PMIC0] return from PMIC_open*/
PMIC_configure(gPmicHandle[CONFIG_PMIC0]);
//! [open_derby]
}

void close(void)
{
//! [close]
PMIC_close(gPmicHandle[CONFIG_PMIC0]);
//! [close]
}