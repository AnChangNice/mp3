#include "ft6236.h"
#include "ft6236_reg.h"
#include <string.h> //memcpy()

#define SDA_WRITE(val)  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13, val)
#define SCL_WRITE(val)  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_15, val)
#define SDA_READ()      ((GPIO_PIN_SET == HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_13)) ? 1 : 0)

#define INPUT_MODE  0
#define OUTPUT_MODE 1

#define IIC_NACK    1
#define IIC_ACK     0
#define IIC_WRITE   0
#define IIC_READ    1

static void set_sda_pin_mode(int mode)
{
    //SDA pin is PH13
    uint32_t temp = GPIOH->MODER;
    temp &= ~(0x3 << (13*2)); //PH13
    temp |= mode << (13*2);
    GPIOH->MODER = temp;
}

static void iic_delay_us(int us)
{
    int cycles = us * 480 / 5;
    while (cycles--)
    {
        __NOP(); //This nop instruction used to prevent optimization.
    }
}

static void iic_start(void)
{
    set_sda_pin_mode(OUTPUT_MODE);
    SDA_WRITE(1);
    SCL_WRITE(1);
    iic_delay_us(2);
    SDA_WRITE(0);
    iic_delay_us(2);
    SCL_WRITE(0);
}

static void iic_stop(void)
{
    SCL_WRITE(1);
    iic_delay_us(2);
    SDA_WRITE(1);
}

static void iic_write_byte(uint8_t data)
{
    set_sda_pin_mode(OUTPUT_MODE);
    for (int i = 7; i >= 0; i--)
    {
        if (data & (1<<i))
        {
            SDA_WRITE(1);
        }
        else
        {
            SDA_WRITE(0);
        }
        iic_delay_us(1);
        SCL_WRITE(1);
        iic_delay_us(2);
        SCL_WRITE(0);
    }
    iic_delay_us(1);
    SCL_WRITE(0);
    SDA_WRITE(0);
}

static void iic_set_addr(uint8_t addr, uint8_t rw)
{
    uint8_t data = (addr << 1) | rw;

    iic_write_byte(data);
}

uint8_t iic_read_byte(void)
{
    uint8_t data = 0;

    set_sda_pin_mode(INPUT_MODE);

    for (int i = 7; i >= 0; i--)
    {
        SCL_WRITE(1);
        iic_delay_us(2);
        data |= SDA_READ() << i;
        SCL_WRITE(0);
        iic_delay_us(2);
    }

    return data;
}

int iic_get_ack(void)
{
    int ack = 0;

    set_sda_pin_mode(INPUT_MODE);

    SCL_WRITE(1);
    iic_delay_us(2);
    ack = SDA_READ();
    SCL_WRITE(0);
    iic_delay_us(2);

    return ack;
}

static void iic_give_ack(int ackmode)
{
    set_sda_pin_mode(OUTPUT_MODE);
    SDA_WRITE(ackmode);

    iic_delay_us(1);
    SCL_WRITE(1);
    iic_delay_us(2);
    SCL_WRITE(0);
    iic_delay_us(1);
    SDA_WRITE(1);
}

static int iic_write_bytes(uint8_t addr, uint8_t data_addr, uint8_t *data, uint8_t len)
{
    iic_start();

    iic_set_addr(addr, IIC_WRITE);

    if (IIC_ACK != iic_get_ack())
    {
        iic_stop();
        return -(1 + len);
    }

    iic_write_byte(data_addr);
    if (IIC_ACK != iic_get_ack())
    {
        iic_stop();
        return -(2 + len);
    }

    for (int i = 0; i < len; i++)
    {
        iic_write_byte(data[i]);
        if (IIC_ACK != iic_get_ack())
        {
            iic_stop();
            return i;
        }
    }

    iic_stop();

    return len;
}

static int iic_set_data_addr(uint8_t addr, uint8_t data_addr)
{
    iic_start();

    iic_set_addr(addr, IIC_WRITE);

    if (IIC_ACK != iic_get_ack())
    {
        iic_stop();
        return -1;
    }

    iic_write_byte(data_addr);
    if (IIC_ACK != iic_get_ack())
    {
        iic_stop();
        return -2;
    }

    iic_stop();

    return 0;
}

static int iic_read_bytes(uint8_t addr, uint8_t *data, uint8_t len)
{
    iic_start();

    iic_set_addr(addr, IIC_READ);

    if (IIC_ACK != iic_get_ack())
    {
        iic_stop();
        return -1;
    }

    for (int i = 0; i < len; i++)
    {
        data[i] = iic_read_byte();
        if (i < (len - 1))
        {
            iic_give_ack(IIC_ACK);
        }
        else
        {
            iic_give_ack(IIC_NACK);
        }
    }

    iic_stop();

    return len;
}

static FT6236_TouchPos_t touch_position;
static uint8_t data[4];

void FT6236_Init(void)
{
    uint8_t temp;

    //CTRL, keep active mode.
    temp = 0x00;
    iic_write_bytes(FT6236_IIC_ADDR, FT6236_REG_CTRL, &temp, 1);

    //Report rate in active mode.
    temp = 10;
    iic_write_bytes(FT6236_IIC_ADDR, FT6236_REG_PERIODACTIVE, &temp, 1);

    //G_MODE: Interrupt Trigger mode.
    temp = 0x01;
    iic_write_bytes(FT6236_IIC_ADDR, FT6236_REG_G_MODE, &temp, 1);
}

//Manually poll data from FT6236.
void FT6236_Update(void)
{
    uint16_t temp;
    iic_set_data_addr(FT6236_IIC_ADDR, FT6236_REG_P1_XH);
    iic_read_bytes(FT6236_IIC_ADDR, data, 4);
    //x
    temp  = (data[0] & 0x0f) << 8;
    temp |= data[1];
    touch_position.x = temp;
    //y
    temp  = (data[2] & 0x0f) << 8;
    temp |= data[3];
    touch_position.y = temp;
    //state
    temp = (data[0] & 0xC0) >> 6;
    switch(temp)
    {
        case 0: touch_position.state = FT6236_TOUCH_POS_STATE_PRESSED;   break;
        case 1: touch_position.state = FT6236_TOUCH_POS_STATE_RELEASED;  break;
        case 2: touch_position.state = FT6236_TOUCH_POS_STATE_PRESSED;   break;
        case 3: touch_position.state = FT6236_TOUCH_POS_STATE_RELEASED;  break;
    }
}

void FT6236_GetTouchPos(FT6236_TouchPos_t *touch_pos)
{
    memcpy(touch_pos, &touch_position, sizeof(FT6236_TouchPos_t));
}


