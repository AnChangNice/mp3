
#include "stm32h7xx_hal.h"

#include "led.h"
#include "key.h"

int main(void)
{
    HAL_Init();

    led_init();
    key_init();

    LED_R_ON();

    while (1)
    {
        LED_B_TOGGLE();
        if (KEY_IS_ON())
        {
            LED_R_ON();
        }
        else
        {
            LED_R_OFF();
        }
        HAL_Delay(100);
    }

    return 0;
}