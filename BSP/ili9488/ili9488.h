#ifndef __ILI9488_H
#define __ILI9488_H

#include "main.h"

void ILI9488_Init(void);
void ILI9488_SetWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void ILI9488_Write(uint8_t *data, uint32_t size);
void ILI9488_FillWindow(uint16_t w, uint16_t h, uint8_t r, uint8_t g, uint8_t b);

#endif //__ILI9488_H