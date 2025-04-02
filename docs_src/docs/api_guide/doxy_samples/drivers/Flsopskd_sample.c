//! [include]
#include <drivers/flsopskd.h>
//! [include]

//! [defines]
#define FLASH_DATA_OFFSET           (10 * 1024 * 1024U)
#define CALIBRATION_DATA_LENGTH     (128 * 1024U)
#define EXT_FLASH_ERASE_OPCODE      (0x21U)
#define EXT_FLASH_ERASE_EXTOPCODE   (0x21U)
#define EXT_FLASH_ERASE_SIZE        (4096U)
#define EXT_FLASH_PAGE_SIZE         (256U)
//! [defines]

uint32_t gWrCalibrationData[CALIBRATION_DATA_LENGTH/sizeof(uint32_t)] = {0};

void write_to_flash()
{
    //! [flsopskd_init]
    uint32_t fw8051version = 0;
    uint32_t totalDowntime = 0;
    uint32_t totalPollsCount = 0;
    FLSOPSKD_Handle gFlopsdkHandle;
    FLSOPSKD_Params params;

    FLSOPSKD_Params_init(&params);
    params.eraseOpCode = EXT_FLASH_ERASE_OPCODE;
    params.eraseExOpCode = EXT_FLASH_ERASE_EXTOPCODE;
    params.pageSizeInBytes = EXT_FLASH_PAGE_SIZE;
    params.eraseSizeInBytes = EXT_FLASH_ERASE_SIZE;
    FLSOPSKD_init(&gFlopsdkHandle, &params);
    //! [flsopskd_init]

    //! [flsopskd_versioncheck]
    FLSOPSKD_getFwVersion(&gFlopsdkHandle, &fw8051version);
    DebugP_assert(fw8051version == FLSOPSKD_EXPECTED_FW_VERSION);
    //! [flsopskd_versioncheck]

    //! [flsopskd_erase]
    for(uint32_t i = 0; i < CALIBRATION_DATA_LENGTH / EXT_FLASH_ERASE_SIZE; i++)
    {
        FLSOPSKD_erase(&gFlopsdkHandle, FLASH_DATA_OFFSET + EXT_FLASH_ERASE_SIZE * i);
    }
    //! [flsopskd_erase]

    //! [flsopskd_write]
    FLSOPSKD_write(&gFlopsdkHandle, FLASH_DATA_OFFSET, (uint8_t*)gWrCalibrationData, CALIBRATION_DATA_LENGTH);
    //! [flsopskd_write]

    //! [flsopskd_perf]
    FLSOPSKD_perfGetDowntime(&gFlopsdkHandle, &totalDowntime);
    FLSOPSKD_perfGetPollCounts(&gFlopsdkHandle, &totalPollsCount);
    //! [flsopskd_perf]
}