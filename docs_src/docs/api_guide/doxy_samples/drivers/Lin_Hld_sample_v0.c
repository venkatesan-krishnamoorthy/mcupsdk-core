#include <kernel/dpl/DebugP.h>
//! [include]
#include <drivers/lin.h>
//! [include]

#define CONFIG_LIN0     (0U)
extern LIN_Config       gLinConfig[];
LIN_Handle              gLinHandle;

void open(void)
{
//! [open]
    /* Open Params Structure */
    LIN_OpenParams      params;

    /* Initialize parameters */
    LIN_Params_init(&params);

    /* Call LIN open */
    gLinHandle = LIN_open(CONFIG_LIN0, &params);

    DebugP_assert(gLinHandle != NULL);
//! [open]
}

void close(void)
{
//! [close]
    LIN_close(gLinHandle);
//! [close]
}

void lin_commander_write_main(void)
{
//! [lin_commander_write_blocking]
    uint8_t     i = 0;
    int32_t     status = SystemP_SUCCESS;
    uint8_t     txData[8] __attribute__((aligned(CacheP_CACHELINE_ALIGNMENT)));

    for (uint8_t i = 0; i < 8; i++)
    {
        txData[i] =  0xA1 + i;
    }

    LIN_SCI_Frame linFrame;

    LIN_SCI_Frame_init(&linFrame);

    linFrame.id = 0x11 + i;
    linFrame.frameLen = i + 1U;
    linFrame.dataBuf = txData;

    status = LIN_SCI_transferFrame(gLinHandle, &linFrame);
    DebugP_assert (SystemP_SUCCESS == status);
//! [lin_commander_write_blocking]
}