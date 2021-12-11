#ifndef __ILI9488_H
#define __ILI9488_H

#include "main.h"

void ILI9488_Init(void);
void ILI9488_SetWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
int  ILI9488_Write(uint8_t *data, uint32_t size, void (*callback)(void));
int  ILI9488_IsBusy(void);

#endif //__ILI9488_H