#include "ili9488.h"

#include "spi.h"

#define ILI9488_DCX_CMD_LOW()   HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET)
#define ILI9488_DCX_DATA_HIGH() HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET)

#define ILI9488_RESET_LOW()     HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET)
#define ILI9488_RESET_HIGH()    HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET)

static void write_cmd(uint8_t cmd)
{
    ILI9488_DCX_CMD_LOW();

    (void)HAL_SPI_Transmit_DMA(&hspi2, &cmd, 1);

    while(HAL_SPI_STATE_READY != HAL_SPI_GetState(&hspi2));
}

static void write_data(uint8_t data)
{
    ILI9488_DCX_DATA_HIGH();

    (void)HAL_SPI_Transmit_DMA(&hspi2, &data, 1);

    while(HAL_SPI_STATE_READY != HAL_SPI_GetState(&hspi2));
}

static void start_send_bytes(uint8_t *data, uint16_t len)
{
    ILI9488_DCX_DATA_HIGH();

    (void)HAL_SPI_Transmit_DMA(&hspi2, data, len);
}

static void fill_window(uint8_t r, uint8_t g, uint8_t b)
{
    int32_t pixels = 320 * 480;
    uint8_t pixcel_buff[] = {r, g, b};

    ILI9488_SetWindow(0, 0, 320, 480);

    for (int32_t i = 0; i < pixels; i++)
    {
        ILI9488_Write(pixcel_buff, 3, NULL);
        while(ILI9488_IsBusy());
    }
}

static void ili9488_reset(void)
{
    // Init to high
    ILI9488_RESET_HIGH();
    HAL_Delay(1);

    // Reset pulse duration
    ILI9488_RESET_LOW();
    HAL_Delay(1);

    // Reset cancel
    ILI9488_RESET_HIGH();
    HAL_Delay(120);
}

void ILI9488_Init(void)
{
    ili9488_reset();

    //************* Start Initial Sequence **********//
    write_cmd(0xE0); //PGAMCTRL(Positive Gamma Control)
    write_data(0x00);
    write_data(0x07);
    write_data(0x0f);
    write_data(0x0D);
    write_data(0x1B);
    write_data(0x0A);
    write_data(0x3c);
    write_data(0x78);
    write_data(0x4A);
    write_data(0x07);
    write_data(0x0E);
    write_data(0x09);
    write_data(0x1B);
    write_data(0x1e);
    write_data(0x0f);

    write_cmd(0xE1); //NGAMCTRL(Negative Gamma Control)
    write_data(0x00);
    write_data(0x22);
    write_data(0x24);
    write_data(0x06);
    write_data(0x12);
    write_data(0x07);
    write_data(0x36);
    write_data(0x47);
    write_data(0x47);
    write_data(0x06);
    write_data(0x0a);
    write_data(0x07);
    write_data(0x30);
    write_data(0x37);
    write_data(0x0f);

    write_cmd(0xC0); //Power Control 1
    write_data(0x10);
    write_data(0x10);

    write_cmd(0xC1); //Power Control 2
    write_data(0x41);

    write_cmd(0xC5); //VCOM Control 1
    write_data(0x00);
    write_data(0x22);
    write_data(0x80);

    write_cmd(0x36); //MADCTL (Memory Access Control)
                     //This command defines read/write scanning direction of the frame memory
#ifndef LCD_HOR_SCREEN
    write_data(0x48);
#else
    write_data(0x28);
#endif

    write_cmd(0x3A); //COLMOD (Interface Pixel Format)
    write_data(0x66); //18bits/pixel

    write_cmd(0XB0); //IFMODE (Interface Mode Control)
    write_data(0x00);
/*
    EPL: ENABLE polarity (0 = High enable for RGB interface, 1 = Low enable for RGB interface)
    DPL: DOTCLK polarity set (0 = data fetched at the rising time, 1 = data fetched at the falling time)
    HSPL: HSYNC polarity (0 = Low level sync clock, 1 = High level sync clock)
    VSPL: VSYNC polarity (0 = Low level sync clock, 1 = High level sync clock)
    SDA_EN: 3/4 wire serial interface selection
        SDA_EN = 0, DIN and SDO pins are used for 3/4 wire serial interface.
        SDA_EN = 1, DIN/SDA pin is used for 3/4 wire serial interface and SDO pin is not used.
*/
    write_cmd(0xB5); //PRCTR (Blanking Porch)
    write_data(0x02); //VFP=2
    write_data(0x02); //VBP=2
    write_data(0x02); //HFP=2
    write_data(0x02); //HBP=2

    write_cmd(0xB1); //FRMCTR1 (Frame Rate Control (In Normal Mode/Full colors))
    write_data(0xD1); //96.8FPS
    write_data(0x10);

    write_cmd(0xB4); //INVTR (Display Inversion Control)
    write_data(0x02);

    write_cmd(0xB6); //DISCTRL (Display Function Control)
    write_data(0x02);
    write_data(0x02);

    write_cmd(0xB7); //ETMOD (Entry Mode Set)
    write_data(0x06);

    write_cmd(0xE9); //SETIMAGE (Set Image Function)
    write_data(0x00);

    write_cmd(0XF7); //Adjust Control 3
    write_data(0xA9);
    write_data(0x51);
    write_data(0x2C);
    write_data(0x82);

    fill_window(0, 0, 0);

    write_cmd(0x11); //Sleep OUT
    HAL_Delay(120);
    write_cmd(0x29); //Display ON
}

/*
    0 --------W-------> X
    |
    |
    H
    |
    \/
    Y
*/
void ILI9488_SetWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    uint16_t SC = x;
    uint16_t EC = x+w-1;
    uint16_t SP = y;
    uint16_t EP = y+h-1;

    write_cmd(0x2A); //CASET (Column Address Set)
    write_data((uint8_t)(SC >> 8));
    write_data((uint8_t)(SC &  0xFF));
    write_data((uint8_t)(EC >> 8));
    write_data((uint8_t)(EC &  0xFF));

    write_cmd(0x2B); //PASET (Page Address Set)
    write_data((uint8_t)(SP >> 8));
    write_data((uint8_t)(SP &  0xFF));
    write_data((uint8_t)(EP >> 8));
    write_data((uint8_t)(EP &  0xFF));
    
    write_cmd(0x2C);
}

static volatile int is_busy = 0;
static volatile void (*write_complete_callback)(void);
static volatile uint32_t remain_size = 0;
static uint8_t *pdata = NULL;

int ILI9488_Write(uint8_t *data, uint32_t size, void (*callback)(void))
{
    if(is_busy)
    {
        return -1;
    }

    is_busy = 1;
    write_complete_callback = callback;

    if(size <= 65535)
    {
        pdata = NULL;
        remain_size = 0;
        start_send_bytes(data, size);
    }
    else
    {
        pdata = data + 65535;
        remain_size = size - 65535;
        start_send_bytes(data, 65535);
    }
    
    return 0;
}

int ILI9488_IsBusy(void)
{
    return is_busy;
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    uint8_t *temp_pdata;
    uint32_t temp_remain_size;

    if(hspi == &hspi2)
    {
        if(remain_size == 0)
        {
            is_busy = 0; //Clear busy flag first, because this flag may be used in callback.
            pdata = NULL;
            remain_size = 0;
            if(NULL != write_complete_callback)
            {
                write_complete_callback();
                write_complete_callback = NULL;
            }
        }
        else
        {
            if(remain_size <= 65535)
            {
                temp_remain_size = remain_size; //Update the status before start transfer.
                temp_pdata = pdata;
                remain_size = 0;
                pdata = NULL;
                start_send_bytes(temp_pdata, temp_remain_size);
            }
            else
            {
                temp_pdata = pdata;  //Update the status before start transfer.
                remain_size -= 65535;
                pdata += 65535;
                start_send_bytes(temp_pdata, 65535);
            }
        }
    }
}
