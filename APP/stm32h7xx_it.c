#include "stm32h7xx_hal.h"

void SysTick_Handler(void)
{
    HAL_IncTick();
}