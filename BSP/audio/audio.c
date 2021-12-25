#include "audio.h"

#include "wm8988.h"
#include "wm8988_sai.h"

//There is a limit size for each transfer.
#define DMA_ONCE_TRANSFER_LIMIT (65534)

static uint32_t current_sample_rate;
static uint32_t current_channels;
static uint32_t current_bits;

void Audio_Init(void)
{
    (void)WM8988_Init();

    (void)Audio_SetFormat(44100, 2, 8);
    (void)Audio_SetVolume(50);
}

int Audio_SetFormat(uint32_t sample_rate, uint32_t channels, uint32_t bits)
{
    //Format should not change in playing.
    if(Audio_IsBusy())
    {
        return -1;
    }

    if(WM8988_OK != WM8988_SetSampleRate(sample_rate))
    {
        return -1;
    }

    if(WM8988_OK != WM8988_SetChannels(channels))
    {
        return -1;
    }

    if(WM8988_OK != WM8988_SetBits(bits))
    {
        return -1;
    }

    SAI2_SetSampleRateAndBits(sample_rate, bits);
    SAI2_SetChannels(channels);

    current_sample_rate = sample_rate;
    current_channels    = channels;
    current_bits        = bits;

    return 0;
}

void Audio_SetVolume(uint8_t vol)
{
    //Here we remaped the vol from 0-100 to 66-100, to improve user experience.
    int db;
    vol = (vol <= 100) ? vol : 100;
    db = (vol != 0) ? (vol/3 + 66) : 0;
    (void)WM8988_SetVolume(db);
}

static void (*play_complete_callback)(void);
static uint32_t remain_size = 0;
static uint8_t *pdata = NULL;
static volatile uint32_t is_busy = 0;

int Audio_Play(uint8_t *data, uint32_t size, void (*callback)(void))
{
    //Play is not allowed in playing.
    if(Audio_IsBusy())
    {
        return -1;
    }

    //Update size to transfer DMA size.
    switch(current_bits)
    {
        case 8:  size /= 1; break;
        case 16: size /= 2; break;
        case 20: size /= 4; break; //This may not right
        case 24: size /= 4; break; //This may not right
        case 32: size /= 4; break;
    }

    play_complete_callback = callback;
    is_busy = 1;

    if(size <= DMA_ONCE_TRANSFER_LIMIT)
    {
        remain_size = 0;
        if(HAL_OK != HAL_SAI_Transmit_DMA(&hsai_BlockA2, data, (uint16_t)size))
        {
            is_busy = 0; //clear state is not start a transmit.
            return -1;
        }
    }
    else
    {
        remain_size = size - DMA_ONCE_TRANSFER_LIMIT;
        pdata = data + DMA_ONCE_TRANSFER_LIMIT;
        if(HAL_OK != HAL_SAI_Transmit_DMA(&hsai_BlockA2, data, DMA_ONCE_TRANSFER_LIMIT))
        {
            is_busy = 0; //clear state is not start a transmit.
            return -1;
        }
    }

    return 0;
}

int Audio_Stop(void)
{
    if(HAL_OK != HAL_SAI_DMAStop(&hsai_BlockA2))
    {
        return -1;
    }

    is_busy = 0;
    play_complete_callback = NULL;
    remain_size = 0;
    pdata = NULL;

    return 0;
}

int Audio_IsBusy(void)
{
    return is_busy;
}

void HAL_SAI_TxCpltCallback(SAI_HandleTypeDef *hsai)
{
    uint32_t temp_size = 0;
    uint8_t *temp_pdata = NULL;
    void (*temp_callback)(void);

    if(hsai == &hsai_BlockA2)
    {
        if(remain_size == 0)
        {
            is_busy = 0; //clear busy first to prevent be used in callback.
            temp_callback = play_complete_callback;
            play_complete_callback = NULL;
            pdata = NULL;
            if(temp_callback != NULL)
            {
                temp_callback();
            }
        }
        else
        {
            if(remain_size <= DMA_ONCE_TRANSFER_LIMIT)
            {
                temp_pdata = pdata;
                temp_size  = remain_size;
                remain_size = 0;
                pdata = NULL;
                if(HAL_OK != HAL_SAI_Transmit_DMA(&hsai_BlockA2, temp_pdata, (uint16_t)temp_size))
                {
                    is_busy = 0; //clear state is not start a transmit.
                }
            }
            else
            {
                remain_size -= DMA_ONCE_TRANSFER_LIMIT;
                temp_pdata = pdata;
                pdata += DMA_ONCE_TRANSFER_LIMIT;
                if(HAL_OK != HAL_SAI_Transmit_DMA(&hsai_BlockA2, temp_pdata, DMA_ONCE_TRANSFER_LIMIT))
                {
                    is_busy = 0; //clear state is not start a transmit.
                }
            }
        }
    }
}