
#include "led.h"

void led_init(void)
{
    GPIO_InitTypeDef gpio_cfg;

    //Clock
    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    //LED Blue
    LED_B_OFF();

    gpio_cfg.Pin        = LED_B_GPIO_PIN;
    gpio_cfg.Mode       = GPIO_MODE_OUTPUT_PP;
    gpio_cfg.Speed      = GPIO_SPEED_FREQ_LOW;
    gpio_cfg.Pull       = GPIO_NOPULL;
    HAL_GPIO_Init(LED_B_GPIO_PORT, &gpio_cfg);

    //LED Red
    LED_R_OFF();

    gpio_cfg.Pin        = LED_R_GPIO_PIN;
    gpio_cfg.Mode       = GPIO_MODE_OUTPUT_PP;
    gpio_cfg.Speed      = GPIO_SPEED_FREQ_LOW;
    gpio_cfg.Pull       = GPIO_NOPULL;
    HAL_GPIO_Init(LED_R_GPIO_PORT, &gpio_cfg);
}
