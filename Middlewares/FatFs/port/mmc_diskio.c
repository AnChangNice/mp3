
#include "mmc_diskio.h"

#include "sdmmc.h"

static HAL_SD_CardInfoTypeDef sd_info;

int MMC_disk_initialize(void)
{
    if(HAL_SD_STATE_READY == HAL_SD_GetState(&hsd1))
    {
        (void)HAL_SD_GetCardInfo(&hsd1, &sd_info);
    }

    return MMC_disk_status();
}

int MMC_disk_read(uint8_t *buff, uint32_t sector, uint32_t count)
{
    HAL_StatusTypeDef status;
    
    if((((uint64_t)sector + (uint64_t)count) > 0xffffffff) || (buff == NULL))
    {
        return 4; //RES_PARERR
    }

    status = HAL_SD_ReadBlocks_DMA(&hsd1, buff, (uint32_t)sector, count);

    if(status == HAL_OK)
    {
        //wait read complete.
        while (HAL_SD_STATE_READY != HAL_SD_GetState(&hsd1));
        return 0; //RES_OK
    }
    
    return 1; //RES_ERROR
}

int MMC_disk_write(uint8_t *buff, uint32_t sector, uint32_t count)
{
    HAL_StatusTypeDef status;
    
    if((((uint64_t)sector + (uint64_t)count) > 0xffffffff) || (buff == NULL))
    {
        return 4; //RES_PARERR
    }

    status = HAL_SD_WriteBlocks_DMA(&hsd1, buff, (uint32_t)sector, count);

    if(status == HAL_OK)
    {
        //wait read complete.
        while (HAL_SD_STATE_READY != HAL_SD_GetState(&hsd1));
        return 0; //RES_OK
    }
    
    return 1; //RES_ERROR      
}

int MMC_disk_status(void)
{
    HAL_SD_StateTypeDef state;
    int res = 0;

    state = HAL_SD_GetState(&hsd1);

    switch(state)
    {
       case HAL_SD_STATE_RESET       : res = 1; break; /* Drive not initialized */
       case HAL_SD_STATE_READY       : res = 0; break; /* Ready for use. */
       case HAL_SD_STATE_TIMEOUT     : res = 4; break; /* Write protected */
       case HAL_SD_STATE_BUSY        : res = 4; break; /* Write protected */
       case HAL_SD_STATE_PROGRAMMING : res = 4; break; /* Write protected */
       case HAL_SD_STATE_RECEIVING   : res = 4; break; /* Write protected */
       case HAL_SD_STATE_TRANSFER    : res = 4; break; /* Write protected */
       case HAL_SD_STATE_ERROR       : res = 4; break; /* Write protected */
       default: res = 2; break; /* No medium in the drive */
    }

    return res;
}

void MMC_disk_ioctl_sync(void)
{
    //wait write complete.
    while (HAL_SD_STATE_READY != HAL_SD_GetState(&hsd1));
}

uint32_t MMC_disk_ioctl_get_sector_count(void)
{
    return sd_info.LogBlockNbr;
}

uint32_t MMC_disk_ioctl_get_sector_size(void)
{
    return sd_info.LogBlockSize;
}

uint32_t MMC_disk_ioctl_get_block_size(void)
{
    return sd_info.BlockSize;
}

void MMC_disk_ioctl_erase_blocks(uint32_t start_addr, uint32_t end_addr)
{
    //FatFs not care about its result.
    (void)HAL_SD_Erase(&hsd1, start_addr, end_addr);
}