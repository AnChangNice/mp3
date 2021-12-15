#ifndef __MMC_DISKIO_H
#define __MMC_DISKIO_H

#include "main.h"

int MMC_disk_initialize(void);
int MMC_disk_read(uint8_t *buff, uint32_t sector, uint32_t count);
int MMC_disk_write(uint8_t *buff, uint32_t sector, uint32_t count);
int MMC_disk_status(void);

void MMC_disk_ioctl_sync(void);
uint32_t MMC_disk_ioctl_get_sector_count(void);
uint32_t MMC_disk_ioctl_get_sector_size(void);
uint32_t MMC_disk_ioctl_get_block_size(void);
void MMC_disk_ioctl_erase_blocks(uint32_t start_addr, uint32_t end_addr);

#endif