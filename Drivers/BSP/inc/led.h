#ifndef __LED_H
#define __LED_H

#include "stm32h7xx_hal.h"

#define LED_ON      GPIO_PIN_RESET
#define LED_OFF     GPIO_PIN_SET

//LED_B
#define LED_B_GPIO_PORT GPIOI
#define LED_B_GPIO_PIN  GPIO_PIN_8

#define LED_B_ON()      HAL_GPIO_WritePin(LED_B_GPIO_PORT, LED_B_GPIO_PIN, LED_ON)
#define LED_B_OFF()     HAL_GPIO_WritePin(LED_B_GPIO_PORT, LED_B_GPIO_PIN, LED_OFF)
#define LED_B_TOGGLE()  HAL_GPIO_TogglePin(LED_B_GPIO_PORT, LED_B_GPIO_PIN)
#define LED_B_STATE()   HAL_GPIO_ReadPin(LED_B_GPIO_PORT, LED_B_GPIO_PIN)

//LED_R
#define LED_R_GPIO_PORT GPIOC
#define LED_R_GPIO_PIN  GPIO_PIN_15
#define LED_R_ON()      HAL_GPIO_WritePin(LED_R_GPIO_PORT, LED_R_GPIO_PIN, LED_ON)
#define LED_R_OFF()     HAL_GPIO_WritePin(LED_R_GPIO_PORT, LED_R_GPIO_PIN, LED_OFF)
#define LED_R_TOGGLE()  HAL_GPIO_TogglePin(LED_R_GPIO_PORT, LED_R_GPIO_PIN)
#define LED_R_STATE()   HAL_GPIO_ReadPin(LED_R_GPIO_PORT, LED_R_GPIO_PIN)

void led_init(void);

#endif //__LED_H
