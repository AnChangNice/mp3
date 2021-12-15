/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */



/* Definitions of physical drive number for each drive */
//#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
//#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */

#if defined(DEV_MMC)
#include "mmc_diskio.h" /* User defined mmc/sd diskio interface. */
#endif

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {

#if defined(DEV_RAM)
	case DEV_RAM :
		result = RAM_disk_status();

		// translate the reslut code here

		return stat;
#endif

#if defined(DEV_MMC)
	case DEV_MMC :
		result = MMC_disk_status();

		// translate the reslut code here
		stat = (DSTATUS)result;

		return stat;
#endif

#if defined(DEV_USB)
	case DEV_USB :
		result = USB_disk_status();

		// translate the reslut code here

		return stat;
#endif

	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {

#if defined(DEV_RAM)
	case DEV_RAM :
		result = RAM_disk_initialize();

		// translate the reslut code here

		return stat;
#endif

#if defined(DEV_MMC)
	case DEV_MMC :
		result = MMC_disk_initialize();

		// translate the reslut code here
		stat = (DSTATUS)result;

		return stat;
#endif

#if defined(DEV_USB)
	case DEV_USB :
		result = USB_disk_initialize();

		// translate the reslut code here

		return stat;
#endif

	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {

#if defined(DEV_RAM)
	case DEV_RAM :
		// translate the arguments here

		result = RAM_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;
#endif

#if defined(DEV_MMC)
	case DEV_MMC :
		// translate the arguments here

		result = MMC_disk_read((uint8_t *)buff, sector, count);

		// translate the reslut code here
		res = (DRESULT)result;

		return res;
#endif

#if defined(DEV_USB)
	case DEV_USB :
		// translate the arguments here

		result = USB_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;
#endif

	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {

#if defined(DEV_RAM)
	case DEV_RAM :
		// translate the arguments here

		result = RAM_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;
#endif

#if defined(DEV_MMC)
	case DEV_MMC :
		// translate the arguments here

		result = MMC_disk_write((uint8_t *)buff, sector, count);

		// translate the reslut code here
		res = (DRESULT)result;

		return res;
#endif

#if defined(DEV_USB)
	case DEV_USB :
		// translate the arguments here

		result = USB_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;
#endif

	}

	return RES_PARERR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	//int result;
	LBA_t start_addr, end_addr;

	switch (pdrv) {

#if defined(DEV_RAM)
	case DEV_RAM :

		// Process of the command for the RAM drive

		return res;
#endif

#if defined(DEV_MMC)
	case DEV_MMC :

		// Process of the command for the MMC/SD card
		switch(cmd)
		{
			case CTRL_SYNC:
				MMC_disk_ioctl_sync();
				res = RES_OK;
				break;
			case GET_SECTOR_COUNT:
				*(LBA_t*)buff = (LBA_t)MMC_disk_ioctl_get_sector_count();
				res = RES_OK;
				break;
			case GET_SECTOR_SIZE:
				*(WORD*)buff = (WORD)MMC_disk_ioctl_get_sector_size();
				res = RES_OK;
				break;
			case GET_BLOCK_SIZE:
				*(DWORD*)buff = (DWORD)MMC_disk_ioctl_get_block_size();
				res = RES_OK;
				break;
			case CTRL_TRIM:
				start_addr = *((LBA_t*)buff + 0);
				end_addr = *((LBA_t*)buff + 1);
				MMC_disk_ioctl_erase_blocks((uint32_t)start_addr, (uint32_t)end_addr);
				res = RES_OK;
				break;
			default:
				res = RES_ERROR;
				break;
		}

		return res;
#endif

#if defined(DEV_USB)
	case DEV_USB :

		// Process of the command the USB drive

		return res;
#endif

	}

	return RES_PARERR;
}

