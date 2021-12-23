/*
 * This file is part of the EasyLogger Library.
 *
 * Copyright (c) 2015, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: Portable interface for each platform.
 * Created on: 2015-04-28
 */
 
#include <elog.h>

#include "usart.h"
#include <stdio.h>

/**
 * EasyLogger port initialize
 *
 * @return result
 */
ElogErrCode elog_port_init(void) {
    ElogErrCode result = ELOG_NO_ERR;

    /* add your code here */
    
    return result;
}

/**
 * EasyLogger port deinitialize
 *
 */
void elog_port_deinit(void) {

    /* add your code here */

}

/**
 * output log port interface
 *
 * @param log output of log
 * @param size log size
 */
void elog_port_output(const char *log, size_t size) {
    
    /* add your code here */
    size_t len = 0;
    for(size_t i = 0; (i + 65535) < size; i += 65535)
    {
        HAL_UART_Transmit(&huart4, (uint8_t *)(log + i), 65535, HAL_MAX_DELAY);
        len += 65535;
    }
    HAL_UART_Transmit(&huart4, (uint8_t *)(log + len), (size - len), HAL_MAX_DELAY);
}

/**
 * output lock
 */
void elog_port_output_lock(void) {
    
    /* add your code here */
    
}

/**
 * output unlock
 */
void elog_port_output_unlock(void) {
    
    /* add your code here */
    
}

/**
 * get current time interface
 *
 * @return current time
 */
const char *elog_port_get_time(void) {
    
    /* add your code here */
    static char time_str[32];
    sprintf(time_str, "%d.%d", (int)(HAL_GetTick() / 1000), (int)(HAL_GetTick() % 1000));
    return time_str;
}

/**
 * get current process name interface
 *
 * @return current process name
 */
const char *elog_port_get_p_info(void) {
    
    /* add your code here */
    static char p_info_str[] = {'\0'};
    return p_info_str;
}

/**
 * get current thread name interface
 *
 * @return current thread name
 */
const char *elog_port_get_t_info(void) {
    
    /* add your code here */
    static char t_info_str[] = {'\0'};
    return t_info_str;
}