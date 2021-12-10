#ifndef __TOUCHPAD_H
#define __TOUCHPAD_H

#include "ft6236.h"

typedef FT6236_TouchPos_t Touchpad_Point_t;

void Touchpad_Init(void);
void Touchpad_Update(void);
void Touchpad_GetPoint(Touchpad_Point_t *point);

#endif