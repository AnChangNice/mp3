#ifndef __KEY_H
#define __KEY_H

#include "stm32h7xx_hal.h"

#define KEY_ON      GPIO_PIN_RESET
#define KEY_OFF     GPIO_PIN_SET

//USER KEY
#define KEY_GPIO_PORT GPIOH
#define KEY_GPIO_PIN  GPIO_PIN_4

#define KEY_IS_ON()     (KEY_ON == HAL_GPIO_ReadPin(KEY_GPIO_PORT, KEY_GPIO_PIN))
#define KEY_IS_OFF()    (KEY_OFF == HAL_GPIO_ReadPin(KEY_GPIO_PORT, KEY_GPIO_PIN))
#define KEY_STATE()     HAL_GPIO_ReadPin(KEY_GPIO_PORT, LED_B_GPIO_PIN)

void key_init(void);

#endif //__KEY_H
