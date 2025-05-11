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
 * @file      driver_pmsx003_basic.c
 * @brief     driver pmsx003 basic source file
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

#include "driver_pmsx003_basic.h"

static pmsx003_handle_t gs_handle;        /**< pmsx003 handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t pmsx003_basic_init(void)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_PMSX003_LINK_INIT(&gs_handle, pmsx003_handle_t);
    DRIVER_PMSX003_LINK_UART_INIT(&gs_handle, pmsx003_interface_uart_init);
    DRIVER_PMSX003_LINK_UART_DEINIT(&gs_handle, pmsx003_interface_uart_deinit);
    DRIVER_PMSX003_LINK_UART_READ(&gs_handle, pmsx003_interface_uart_read);
    DRIVER_PMSX003_LINK_UART_FLUSH(&gs_handle, pmsx003_interface_uart_flush);
    DRIVER_PMSX003_LINK_UART_WRITE(&gs_handle, pmsx003_interface_uart_write);
    DRIVER_PMSX003_LINK_RESET_GPIO_INIT(&gs_handle, pmsx003_interface_reset_gpio_init);
    DRIVER_PMSX003_LINK_RESET_GPIO_DEINIT(&gs_handle, pmsx003_interface_reset_gpio_deinit);
    DRIVER_PMSX003_LINK_RESET_GPIO_WRITE(&gs_handle, pmsx003_interface_reset_gpio_write);
    DRIVER_PMSX003_LINK_SET_GPIO_INIT(&gs_handle, pmsx003_interface_set_gpio_init);
    DRIVER_PMSX003_LINK_SET_GPIO_DEINIT(&gs_handle, pmsx003_interface_set_gpio_deinit);
    DRIVER_PMSX003_LINK_SET_GPIO_WRITE(&gs_handle, pmsx003_interface_set_gpio_write);
    DRIVER_PMSX003_LINK_DELAY_MS(&gs_handle, pmsx003_interface_delay_ms);
    DRIVER_PMSX003_LINK_DEBUG_PRINT(&gs_handle, pmsx003_interface_debug_print);
    
    /* pmsx003 init */
    res = pmsx003_init(&gs_handle);
    if (res != 0)
    {
        pmsx003_interface_debug_print("pmsx003: init failed.\n");
        
        return 1;
    }
    
    /* set normal mode */
    res = pmsx003_set_hard_mode(&gs_handle, PMSX003_HARD_MODE_NORMAL);
    if (res != 0)
    {
        pmsx003_interface_debug_print("pmsx003: set hard mode failed.\n");
        (void)pmsx003_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default mode */
    res = pmsx003_set_mode(&gs_handle, PMSX003_BASIC_DEFAULT_MODE);
    if (res != 0)
    {
        pmsx003_interface_debug_print("pmsx003: set mode failed.\n");
        (void)pmsx003_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *data pointer to a data structure
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t pmsx003_basic_read(pmsx003_data_t *data)
{
    uint8_t res;

    /* read */
    res = pmsx003_read(&gs_handle, data);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t pmsx003_basic_deinit(void)
{
    /* deinit pmsx003 */
    if (pmsx003_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic sleep
 * @return status code
 *         - 0 success
 *         - 1 sleep failed
 * @note   none
 */
uint8_t pmsx003_basic_sleep(void)
{
    /* sleep */
    if (pmsx003_sleep(&gs_handle) != 0)
    {
        return 1;
    }
    
    /* hard sleep */
    if (pmsx003_set_hard_mode(&gs_handle, PMSX003_HARD_MODE_SLEEP) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic wake up
 * @return status code
 *         - 0 success
 *         - 1 wake up failed
 * @note   none
 */
uint8_t pmsx003_basic_wake_up(void)
{
    
    /* hard normal */
    if (pmsx003_set_hard_mode(&gs_handle, PMSX003_HARD_MODE_NORMAL) != 0)
    {
        return 1;
    }
    
    /* 200ms */
    pmsx003_interface_delay_ms(200);
    
    /* wake up */
    if (pmsx003_wake_up(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}
