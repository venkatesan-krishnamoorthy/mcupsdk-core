
//! [include]
#include <stdio.h>
#include <drivers/fota_agent/v0/fota_agent.h>
//! [include]

#define APP_OSPI_DATA_SIZE (20*1024U)
#define MAX_ELF_PROGRAM_HEADER (21U)
#define WRITE_CHUNK_SIZE   (4*1024U)
uint8_t gOspiTxBuf[APP_OSPI_DATA_SIZE] __attribute__((aligned(128), section(".bss.filebuf")));


void transfer_FOTAAgent(void)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t offset = 0x81000;
    /* initialise buffer*/
    for(int i=0;i<APP_OSPI_DATA_SIZE;i++)
    {
        gOspiTxBuf[i] = i%256;
    }
    //! [fota_init]
    FOTAAgent_Handle fotaAgentHandle;
    FOTAAgent_Params agentParams;
    uint8_t gFotaAgentProcessingBuffer[WRITE_CHUNK_SIZE];
    ELFUP_ELFPH gProgramHeaderArray[MAX_ELF_PROGRAM_HEADER];

    FOTAAgent_Params_init(&agentParams);
    agentParams.pProcessingBuffer = gFotaAgentProcessingBuffer;
    agentParams.pProgramHeader = gProgramHeaderArray;
    agentParams.programHeaderCnt = MAX_ELF_PROGRAM_HEADER;
    FOTAAgent_init(&fotaAgentHandle, &agentParams);
    //! [fota_init]
//! [fota_write_start]
    status = FOTAAgent_writeStart(&fotaAgentHandle, offset, TRUE);
//! [fota_write_start]

//! [fota_write_update]
    for(int i = 0; i < APP_OSPI_DATA_SIZE; i++)
    {
        status = FOTAAgent_writeUpdate(&fotaAgentHandle, &gOspiTxBuf[i], 1);
        DebugP_assert(status == SystemP_SUCCESS);
    }
//! [fota_write_update]

//! [fota_write_end]
    status += FOTAAgent_writeEnd(&fotaAgentHandle);
    DebugP_assert(status==SystemP_SUCCESS);
//! [fota_write_end]

}