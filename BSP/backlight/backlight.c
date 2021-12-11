
#include "backlight.h"
#include "aw9364.h"

#define BACKLIGHT_GET_LEVEL_FROM(persent)   (persent * 16 / 100)  
#define IS_BACKLIGHT_BRIGHTNESS_VALID(val)  ((0 <= val) && (val <= 100))

void Backlight_On(uint8_t brightness)
{
    if(IS_BACKLIGHT_BRIGHTNESS_VALID(brightness))
    {
        AW9364_on(BACKLIGHT_GET_LEVEL_FROM(brightness));
    }
    else
    {
        AW9364_on(BACKLIGHT_GET_LEVEL_FROM(100));
    }
}
void Backlight_Update(uint8_t brightness)
{
    if(IS_BACKLIGHT_BRIGHTNESS_VALID(brightness))
    {
        AW9364_adjust(BACKLIGHT_GET_LEVEL_FROM(brightness));
    }
}
void Backlight_Off(void)
{
    AW9364_off();
}