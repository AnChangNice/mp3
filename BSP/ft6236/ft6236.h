#ifndef __FT6236_H
#define __FT6236_H

#include "main.h"

#define FT6236_POINT_STATE_RELEASED     0
#define FT6236_POINT_STATE_PRESSED      1

#define FT6236_IIC_ADDR 0x38

typedef struct _ft6236_data
{
    uint8_t state;
    uint16_t x;
    uint16_t y;
} FT6236_Point_t;

void FT6236_Init(void);
void FT6236_PollOnce(void); //Manually poll data from FT6236.
void FT6236_GetPoint(FT6236_Point_t *point);

/* This API should be used in interrupt trigger mode. */
void FT6236_DataUpdateISR(void);

/* This API should be defined by user to get data for every update. */
extern void FT6236_DataUpdateCallback(FT6236_Point_t *point);

#endif //__FT6236_H