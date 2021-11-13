/*
 * wm8988.h
 *
 *  Created on: Oct 12, 2021
 *      Author: AnChangNice
 */

#ifndef WM8988_H_
#define WM8988_H_

#include "wm8988_regs.h"

#include "main.h"

#define WM8988_OK 	  (0)
#define WM8988_ERROR  (-1)

/* High Level API */
int WM8988_Init(void);

int WM8988_SetSampleRate(int sampleRate);
int WM8988_SetChannels(int channels);
int WM8988_SetBits(int bits);
int WM8988_SetVolume(int volume);

/* Low Level API */
int WM8988_IIC_Write(uint8_t reg, uint16_t reg_val);

#endif /* WM8988_H_ */
