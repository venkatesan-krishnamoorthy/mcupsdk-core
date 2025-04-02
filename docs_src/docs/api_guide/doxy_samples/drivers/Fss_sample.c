//! [include]
#include <drivers/fss.h>
#include <drivers/hw_include/cslr_fss.h>
//! [include]

void configBootSeg()
{
    ///! [fssconf]
    FSS_Config fssConf;
    /* IP base addrress is defined in the CSL files */
    fssConf.ipBaseAddress = CSL_MSS_CTRL_U_BASE;
    /* Assume that size of external flash is 32MB */
    fssConf.extFlashSize = 32 * 1024 * 1024;;
    ///! [fssconf]

    ///! [fss_bootfrom_a]
    DebugP_assert(FSS_selectRegionA(&fssConf) == SystemP_SUCCESS);
    ///! [fss_bootfrom_a]

    ///! [fss_bootfrom_b]
    DebugP_assert(FSS_selectRegionB(&fssConf) == SystemP_SUCCESS);
    ///! [fss_bootfrom_b]

    ///! [fss_getbootfrom]
    uint32_t bootRegion = FSS_getBootRegion(&fssConf);
    if(1U == bootRegion)
    {
        DebugP_log("Booting from 2nd half of flash (or B region).");
    }
    else
    {
        DebugP_log("Booting from 1st half of flash (or A region).");
    }
    ///! [fss_getbootfrom]
}

void OTFAECCM_Config()
{
    ///! [fss_configeccm]
    FSS_ECCRegionConfig region;
    /*
        ECCM IP can config 4 regions. Index is to indicate
        for which region this config is for.
    */
    region.regionIndex = 0;
    region.size = 1 * 1024 * 1024;
    region.startAddress = 16 * 1024;
    /* disable ECC initially */
    FSS_disableECC();
    FSS_configECCMRegion(&region);
    FSS_enableECC();
    ///! [fss_configeccm]
}