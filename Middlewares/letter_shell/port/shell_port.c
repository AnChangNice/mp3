#include "shell_port.h"

#include "usart.h"
#include "elog.h"

#include "FreeRTOS.h"
#include "task.h"
#include "stream_buffer.h"

Shell shell;
static char shell_buff[512];

static short shell_port_uart_write(char *data, unsigned short len)
{
    (void)HAL_UART_Transmit(&huart4, (uint8_t *)data, (uint16_t)len, HAL_MAX_DELAY);
    return len;
}

//static short shell_port_uart_read(char *data, unsigned short len)
//{
//    (void)HAL_UART_Receive(&huart4, (uint8_t *)data, (uint16_t)len, HAL_MAX_DELAY);
//    return len;
//}

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

StreamBufferHandle_t shell_rx_stream_buff;
static uint8_t uart_rx_byte;

static void shell_task(void *pvParameters)
{
    size_t xReceivedBytes, tryToReceiveBytes;
    char receive_buff[32];

    //Create stream buffer for uart data receive in ISR.
    shell_rx_stream_buff = xStreamBufferCreate(sizeof(receive_buff), 1);

    if(shell_rx_stream_buff == NULL)
    {
        log_e("shell_rx_stream_buff create failed!");
        vTaskDelete(xTaskGetCurrentTaskHandle());
        return;
    }

    if(HAL_OK != HAL_UART_Receive_IT(&huart4, &uart_rx_byte, sizeof(uart_rx_byte)))
    {
        log_e("shell start uart interrupt receive failed!");
    }

    for(;;)
    {
        tryToReceiveBytes = xStreamBufferBytesAvailable(shell_rx_stream_buff);
        tryToReceiveBytes = (tryToReceiveBytes == 0) ? 1 : tryToReceiveBytes;
        xReceivedBytes = xStreamBufferReceive(shell_rx_stream_buff, receive_buff, tryToReceiveBytes, portMAX_DELAY);
        
        for(int i = 0; i < xReceivedBytes; i++)
        {
            shellHandler(&shell, receive_buff[i]);
        }
    }
}

void shell_port_init(void)
{
    shell.write = shell_port_uart_write;
    //shell.read = shell_port_uart_read;
#if SHELL_USING_LOCK
    shell.lock = shell_port_lock;
    shell.unlock = shell_port_unlock;
#endif
    shellInit(&shell, shell_buff, 512);

    //Create shell_task
    BaseType_t xReturned;
    TaskHandle_t xHandle = NULL;

    xReturned = xTaskCreate(
                    shell_task,
                    "shell_task",
                    1024/4,
                    NULL,
                    tskIDLE_PRIORITY+1,
                    &xHandle);

    if(xReturned != pdPASS)
    {
        log_e("shell_task create failed!");
    }
}

static void shell_port_input_isr(char *data, int len)
{
    size_t xBytesSent;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xBytesSent = xStreamBufferSendFromISR(shell_rx_stream_buff, data, len, &xHigherPriorityTaskWoken);

    if(xBytesSent != len)
    {
        log_e("shell_rx_stream_buff is full, loss %d bytes!", len - xBytesSent);
    }
    //taskYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart == &huart4)
    {
        shell_port_input_isr((char *)&uart_rx_byte, 1);
        if(HAL_OK != HAL_UART_Receive_IT(&huart4, &uart_rx_byte, sizeof(uart_rx_byte)))
        {
            log_e("shell start uart interrupt receive failed!");
        }
    }
}
