#ifndef __MMC_DISKIO_H
#define __MMC_DISKIO_H

#include "main.h"

int MMC_disk_initialize(void);
int MMC_disk_read(uint8_t *buff, uint64_t sector, uint32_t count);
int MMC_disk_write(uint8_t *buff, uint64_t sector, uint32_t count);
int MMC_disk_status(void);

#endif