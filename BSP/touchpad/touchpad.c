
#include "touchpad.h"

void Touchpad_Init(void)
{
    FT6236_Init();
}
void Touchpad_GetPoint(Touchpad_Point_t *point)
{
    FT6236_GetTouchPos((FT6236_TouchPos_t *)point);
}
void Touchpad_Update(void)
{
    FT6236_Update();
}