#include "w9825g6kh6.h"
#include "fmc.h"

static void delay_us(int us)
{
    int cycles = us * 480 / 5;
    while (cycles--)
    {
        __NOP();
    }
}

void W9825G6KH6_Init(void)
{
    FMC_SDRAM_CommandTypeDef Cmd;

    //Enable CLK
    Cmd.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
    Cmd.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
    Cmd.AutoRefreshNumber = 1;
    Cmd.ModeRegisterDefinition = 0;
    HAL_SDRAM_SendCommand(&hsdram1, &Cmd, HAL_MAX_DELAY);

    //Delay 100us
    delay_us(100);

    //Precharge all banks
    Cmd.CommandMode = FMC_SDRAM_CMD_PALL;
    Cmd.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
    Cmd.AutoRefreshNumber = 1;
    Cmd.ModeRegisterDefinition = 0;
    HAL_SDRAM_SendCommand(&hsdram1, &Cmd, HAL_MAX_DELAY);

    //Auto refresh twice
    Cmd.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
    Cmd.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
    Cmd.AutoRefreshNumber = 2;
    Cmd.ModeRegisterDefinition = 0;
    HAL_SDRAM_SendCommand(&hsdram1, &Cmd, HAL_MAX_DELAY);

    //Program Mode register
    Cmd.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
    Cmd.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
    Cmd.AutoRefreshNumber = 1;
    //Burst Length 1
    //Addressing Mode Interleave
    //CAS Latency 3
    //Burst read and single write
    Cmd.ModeRegisterDefinition = (0 << 0) \
                               | (1 << 3) \
                               | (3 << 4) \
                               | (1 << 9);
    HAL_SDRAM_SendCommand(&hsdram1, &Cmd, HAL_MAX_DELAY);

    //SDRAM refresh timer
    // 64ms/8192 = 7.81us
    // 7.81us * 120MHz - 20 = 917.2us
    FMC_SDRAM_ProgramRefreshRate(&hsdram1, 917);
}
