#include "lcd_backlight.h"
#include "main.h"

#define LCD_BL_HIGH() HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_SET)
#define LCD_BL_LOW()  HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_RESET);

static int current_brightness = 0;

static void delay_us(int us)
{
    int delay_cycles = us * 480 / 5;
    while (delay_cycles--);
}

void lcd_backlight_on(int brightness)
{
    int positive_pulses = 17 - brightness;

    //Error check.
    if ((brightness < LCD_BACKLIGHT_BRIGHTNESS_MIN) || (LCD_BACKLIGHT_BRIGHTNESS_MAX < brightness))
    {
        return;
    }

    current_brightness = brightness;

    //Ton
    LCD_BL_HIGH();
    delay_us(25);

    //Set brightness for 1~16
    for (int i = 0; i < (positive_pulses - 1); i++)
    {
        LCD_BL_LOW();
        delay_us(1);
        LCD_BL_HIGH();
        delay_us(1);
    }
}

void led_backlight_adjust(int brightness)
{
    int tartget_positive_pulses = 17 - brightness;
    int current_positive_pulses = 17 - current_brightness;
    int pulses_num = 0;

    //Error check.
    if ((brightness < LCD_BACKLIGHT_BRIGHTNESS_MIN) || (LCD_BACKLIGHT_BRIGHTNESS_MAX < brightness))
    {
        return;
    }

    current_brightness = brightness;

    if (current_positive_pulses <= tartget_positive_pulses)
    {
        pulses_num = tartget_positive_pulses - current_positive_pulses;
    }
    else
    {
        pulses_num = (tartget_positive_pulses + 16 - current_positive_pulses) % 16;
    }

    for (int i = 0; i < pulses_num; i++)
    {
        LCD_BL_LOW();
        delay_us(1);
        LCD_BL_HIGH();
        delay_us(1);
    }
}

void led_backlight_off(void)
{
    //Update brightness to 0.
    current_brightness = 0;
    //Hold low more than 2.5ms to off.
    LCD_BL_LOW();
    delay_us(2500);
}

