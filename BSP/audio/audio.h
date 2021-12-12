#ifndef __AUDIO_H
#define __AUDIO_H

#include "main.h"

void Audio_Init(void);
int  Audio_SetFormat(uint32_t sample_rate, uint32_t channels, uint32_t bits);
void Audio_SetVolume(uint8_t vol);
int  Audio_Play(uint8_t *data, uint32_t size, void (*callback)(void));
int  Audio_Stop(void);
int  Audio_IsBusy(void);

#endif