/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      raspberrypi4b_driver_pmsx003_interface.c
 * @brief     raspberrypi4b driver pmsx003 interface source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2025-05-15
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2025/05/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_pmsx003_interface.h"
#include "uart.h"
#include "wire.h"
#include <stdarg.h>

/**
 * @brief uart device name definition
 */
#define UART_DEVICE_NAME "/dev/ttyS0"        /**< uart device name */

/**
 * @brief uart device handle definition
 */
static int gs_fd;                           /**< uart handle */

/**
 * @brief  interface uart init
 * @return status code
 *         - 0 success
 *         - 1 uart init failed
 * @note   none
 */
uint8_t pmsx003_interface_uart_init(void)
{
    return uart_init(UART_DEVICE_NAME, &gs_fd, 9600, 8, 'N', 1);
}

/**
 * @brief  interface uart deinit
 * @return status code
 *         - 0 success
 *         - 1 uart deinit failed
 * @note   none
 */
uint8_t pmsx003_interface_uart_deinit(void)
{
    return uart_deinit(gs_fd);
}

/**
 * @brief      interface uart read
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint16_t pmsx003_interface_uart_read(uint8_t *buf, uint16_t len)
{
    uint32_t l = len;

    if (uart_read(gs_fd, buf, (uint32_t *)&l))
    {
        return 0;
    }
    else
    {
        return l;
    }
}

/**
 * @brief  interface uart flush
 * @return status code
 *         - 0 success
 *         - 1 uart flush failed
 * @note   none
 */
uint8_t pmsx003_interface_uart_flush(void)
{
    return uart_flush(gs_fd);
}

/**
 * @brief     interface uart write
 * @param[in] *buf pointer to a data buffer
 * @param[in] len length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t pmsx003_interface_uart_write(uint8_t *buf, uint16_t len)
{
    return uart_write(gs_fd, buf, len);
}

/**
 * @brief  interface reset gpio init
 * @return status code
 *         - 0 success
 *         - 1 reset gpio init failed
 * @note   none
 */
uint8_t pmsx003_interface_reset_gpio_init(void)
{
    return wire_init();
}

/**
 * @brief  interface reset gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 reset gpio deinit failed
 * @note   none
 */
uint8_t pmsx003_interface_reset_gpio_deinit(void)
{
    return wire_deinit();
}

/**
 * @brief     interface reset gpio write
 * @param[in] level gpio level
 * @return    status code
 *            - 0 success
 *            - 1 reset gpio write failed
 * @note      none
 */
uint8_t pmsx003_interface_reset_gpio_write(uint8_t level)
{
    return wire_write(level);
}

/**
 * @brief  interface set gpio init
 * @return status code
 *         - 0 success
 *         - 1 set gpio init failed
 * @note   none
 */
uint8_t pmsx003_interface_set_gpio_init(void)
{
    return wire_clock_init();
}

/**
 * @brief  interface set gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 set gpio deinit failed
 * @note   none
 */
uint8_t pmsx003_interface_set_gpio_deinit(void)
{
     return wire_clock_deinit();
}

/**
 * @brief     interface set gpio write
 * @param[in] level gpio level
 * @return    status code
 *            - 0 success
 *            - 1 set gpio write failed
 * @note      none
 */
uint8_t pmsx003_interface_set_gpio_write(uint8_t level)
{
    return wire_clock_write(level);
}

/**
 * @brief     interface delay ms
 * @param[in] ms time
 * @note      none
 */
void pmsx003_interface_delay_ms(uint32_t ms)
{
    usleep(1000 * ms);
}

/**
 * @brief     interface print format data
 * @param[in] fmt format data
 * @note      none
 */
void pmsx003_interface_debug_print(const char *const fmt, ...)
{
    char str[256];
    uint16_t len;
    va_list args;
    
    memset((char *)str, 0, sizeof(char) * 256); 
    va_start(args, fmt);
    vsnprintf((char *)str, 255, (char const *)fmt, args);
    va_end(args);
    
    len = strlen((char *)str);
    (void)printf((uint8_t *)str, len);
}
