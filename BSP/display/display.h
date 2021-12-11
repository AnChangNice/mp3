#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "main.h"

typedef struct _display_color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Display_Color_t;

typedef enum
{
    Display_Data_RGB888,
    Display_Data_RGB565
} Display_DataFromat_t;

void Display_Init(void);
int  Display_SetWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
int  Display_FillColor(Display_Color_t *color, void (*callback)(void));
int  Display_FillData(uint8_t *data, uint32_t size, Display_DataFromat_t format, void (*callback)(void));
int  Display_IsBusy(void);

/* This function just for GPU speed up. */
#if 0
int Display_FillColorToBuffer(Display_Color_t *color, Display_DataFromat_t format, uint8_t *buffer, uint32_t w, uint32_t h, void (*callback)(void));
#endif

#endif