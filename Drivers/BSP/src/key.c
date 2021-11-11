
#include "key.h"

void key_init(void)
{
    GPIO_InitTypeDef gpio_cfg;

    //Clock
    __HAL_RCC_GPIOH_CLK_ENABLE();

    //User KEY
    gpio_cfg.Pin        = KEY_GPIO_PIN;
    gpio_cfg.Mode       = GPIO_MODE_INPUT;
    gpio_cfg.Pull       = GPIO_NOPULL;
    gpio_cfg.Speed      = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(KEY_GPIO_PORT, &gpio_cfg);
}
