#include "shell_port.h"

#include "usart.h"

Shell shell;
static char shell_buff[512];

static short shell_port_uart_write(char *data, unsigned short len)
{
    (void)HAL_UART_Transmit(&huart4, (uint8_t *)data, (uint16_t)len, HAL_MAX_DELAY);
    return len;
}

static short shell_port_uart_read(char *data, unsigned short len)
{
    (void)HAL_UART_Receive(&huart4, (uint8_t *)data, (uint16_t)len, HAL_MAX_DELAY);
    return len;
}

#if SHELL_USING_LOCK
static int shell_port_lock(Shell *shell)
{
    //To do.
    return 0;
}
#endif

#if SHELL_USING_LOCK
static int shell_port_unlock(Shell *shell)
{
    //To do.
    return 0;
}
#endif

void shell_port_init(void)
{
    shell.write = shell_port_uart_write;
    shell.read = shell_port_uart_read;
#if SHELL_USING_LOCK
    shell.lock = shell_port_lock;
    shell.unlock = shell_port_unlock;
#endif
    shellInit(&shell, shell_buff, 512);
}