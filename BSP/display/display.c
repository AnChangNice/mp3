#include "display.h"

#include "ili9488.h"
#include "dma2d.h"

static uint8_t display_buff[480 * 320 * 3] __attribute__((section(".sdram")));
static uint16_t window_w = 0;
static uint16_t window_h = 0;
static uint32_t fill_color;

static void display_dma2d_rgb565_to_rgb888(uint8_t *in_data, uint8_t *out_data, uint32_t w, uint32_t h)
{
    hdma2d.Instance = DMA2D;
    hdma2d.Init.Mode = DMA2D_M2M_PFC;
    hdma2d.Init.ColorMode = DMA2D_OUTPUT_RGB888;
    hdma2d.Init.OutputOffset = 0;
    hdma2d.LayerCfg[1].InputOffset = 0;
    hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_RGB565;
    hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
    hdma2d.LayerCfg[1].InputAlpha = 0;
    hdma2d.LayerCfg[1].AlphaInverted = DMA2D_REGULAR_ALPHA;
    hdma2d.LayerCfg[1].RedBlueSwap = DMA2D_RB_SWAP;
    hdma2d.LayerCfg[1].ChromaSubSampling = DMA2D_NO_CSS;
    if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
    {
        while(1);
    }
    if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
    {
        while(1);
    }

    while(HAL_DMA2D_STATE_READY != HAL_DMA2D_GetState(&hdma2d));
    HAL_DMA2D_Start_IT(&hdma2d, (uint32_t)in_data, (uint32_t)out_data, w, h);
    while(HAL_DMA2D_STATE_READY != HAL_DMA2D_GetState(&hdma2d));
}
#if 0
static void display_dma2d_fill_rgb565(Display_Color_t *color, uint8_t *out_data, uint32_t w, uint32_t h)
{
    fill_color = (color->r<<16) | (color->g<<8) | color->b;

    hdma2d.Instance = DMA2D;
    hdma2d.Init.Mode = DMA2D_R2M;
    hdma2d.Init.ColorMode = DMA2D_OUTPUT_RGB565;
    hdma2d.Init.OutputOffset = 320 - w;
    hdma2d.Init.LineOffsetMode = DMA2D_LOM_PIXELS;
    hdma2d.LayerCfg[1].InputOffset = 0;
    hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_RGB888;
    hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
    hdma2d.LayerCfg[1].InputAlpha = 0;
    hdma2d.LayerCfg[1].AlphaInverted = DMA2D_REGULAR_ALPHA;
    hdma2d.LayerCfg[1].RedBlueSwap = DMA2D_RB_SWAP;
    hdma2d.LayerCfg[1].ChromaSubSampling = DMA2D_NO_CSS;
    if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
    {
        while(1);
    }
    if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
    {
        while(1);
    }

    while(HAL_DMA2D_STATE_READY != HAL_DMA2D_GetState(&hdma2d));
    HAL_DMA2D_Start_IT(&hdma2d, fill_color, (uint32_t)out_data, w, h);
    while(HAL_DMA2D_STATE_READY != HAL_DMA2D_GetState(&hdma2d));
}
#endif

static void display_dma2d_fill_rgb888(Display_Color_t *color, uint8_t *out_data, uint32_t w, uint32_t h)
{
    fill_color = (color->r<<16) | (color->g<<8) | color->b;

    hdma2d.Instance = DMA2D;
    hdma2d.Init.Mode = DMA2D_R2M;
    hdma2d.Init.ColorMode = DMA2D_OUTPUT_RGB888;
    hdma2d.Init.OutputOffset = 320 - w;
    hdma2d.LayerCfg[1].InputOffset = 0;
    hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_RGB888;
    hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
    hdma2d.LayerCfg[1].InputAlpha = 0;
    hdma2d.LayerCfg[1].AlphaInverted = DMA2D_REGULAR_ALPHA;
    hdma2d.LayerCfg[1].RedBlueSwap = DMA2D_RB_SWAP;
    hdma2d.LayerCfg[1].ChromaSubSampling = DMA2D_NO_CSS;
    if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
    {
        while(1);
    }
    if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
    {
        while(1);
    }

    while(HAL_DMA2D_STATE_READY != HAL_DMA2D_GetState(&hdma2d));
    HAL_DMA2D_Start_IT(&hdma2d, fill_color, (uint32_t)out_data, w, h);
    while(HAL_DMA2D_STATE_READY != HAL_DMA2D_GetState(&hdma2d));
}

void Display_Init(void)
{
    ILI9488_Init();
}

int Display_SetWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    if(ILI9488_IsBusy())
    {
        return -1;
    }

    window_w = w;
    window_h = h;

    ILI9488_SetWindow(x, y, w, h);

    return 0;
}

int Display_FillColor(Display_Color_t *color, void (*callback)(void))
{
    if(ILI9488_IsBusy())
    {
        return -1;
    }

    display_dma2d_fill_rgb888(color, display_buff, window_w, window_h);
    (void)ILI9488_Write(display_buff, window_w * window_h * 3, callback);

    return 0;
}

int Display_FillData(uint8_t *data, uint32_t size, Display_DataFromat_t format, void (*callback)(void))
{
    if(ILI9488_IsBusy())
    {
        return -1;
    }

    if(format == Display_Data_RGB888)
    {
        (void)ILI9488_Write(data, size, callback);
    }
    else if(format == Display_Data_RGB565)
    {
        display_dma2d_rgb565_to_rgb888(data, display_buff, window_w, window_h);

        (void)ILI9488_Write(display_buff, window_w * window_h * 3, callback);
    }

    return 0;
}

int Display_IsBusy(void)
{
    return ILI9488_IsBusy();
}

/* This function just for GPU speed up. */
#if 0
int Display_FillColorToBuffer(Display_Color_t *color, Display_DataFromat_t format, uint8_t *buffer, uint32_t w, uint32_t h, void (*callback)(void))
{
    if(format == Display_Data_RGB888)
    {
        display_dma2d_fill_rgb888(color, buffer, w, h);
    }
    else if(format == Display_Data_RGB565)
    {
        display_dma2d_fill_rgb565(color, buffer, w, h);
    }

    return 0;
}
#endif
