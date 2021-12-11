#ifndef __BACKLIGHT_H
#define __BACKLIGHT_H

#include "main.h"

void Backlight_On(uint8_t brightness);
void Backlight_Update(uint8_t brightness);
void Backlight_Off(void);

#endif