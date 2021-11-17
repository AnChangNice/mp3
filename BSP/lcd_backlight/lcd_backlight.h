#ifndef __LCD_BACKLIGHT_H
#define __LCD_BACKLIGHT_H

#define LCD_BACKLIGHT_BRIGHTNESS_MIN  (1)
#define LCD_BACKLIGHT_BRIGHTNESS_MAX  (16)

void lcd_backlight_on(int brightness);
void led_backlight_adjust(int brightness);
void led_backlight_off(void);

#endif //__LCD_BACKLIGHT_H