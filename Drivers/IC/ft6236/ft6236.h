#ifndef __FT6236_H
#define __FT6236_H

#include "main.h"

#define FT6236_TOUCH_POS_STATE_RELEASED     0
#define FT6236_TOUCH_POS_STATE_PRESSED      1

#define FT6236_IIC_ADDR 0x38

typedef struct _ft6236_touch_pos
{
    uint8_t state;
    uint16_t x;
    uint16_t y;
} FT6236_TouchPos_t;

void FT6236_Init(void);
void FT6236_Update(void); //Manually poll data from FT6236.
void FT6236_GetData(FT6236_TouchPos_t *pos);

#endif //__FT6236_H