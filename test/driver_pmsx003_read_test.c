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
 * @file      driver_pmsx003_read_test.c
 * @brief     driver pmsx003 read test source file
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

#include "driver_pmsx003_read_test.h"

static pmsx003_handle_t gs_handle;        /**< pmsx003 handle */

/**
 * @brief     read test
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t pmsx003_read_test(uint32_t times)
{
    uint8_t res;
    uint32_t i;
    pmsx003_info_t info;
    
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
    
    /* get pmsx003 information */
    res = pmsx003_info(&info);
    if (res != 0)
    {
        pmsx003_interface_debug_print("pmsx003: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        pmsx003_interface_debug_print("pmsx003: chip is %s.\n", info.chip_name);
        pmsx003_interface_debug_print("pmsx003: manufacturer is %s.\n", info.manufacturer_name);
        pmsx003_interface_debug_print("pmsx003: interface is %s.\n", info.interface);
        pmsx003_interface_debug_print("pmsx003: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        pmsx003_interface_debug_print("pmsx003: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        pmsx003_interface_debug_print("pmsx003: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        pmsx003_interface_debug_print("pmsx003: max current is %0.2fmA.\n", info.max_current_ma);
        pmsx003_interface_debug_print("pmsx003: max temperature is %0.1fC.\n", info.temperature_max);
        pmsx003_interface_debug_print("pmsx003: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start read test */
    pmsx003_interface_debug_print("pmsx003: start read test.\n");
    
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
    
    /* set active mode */
    res = pmsx003_set_mode(&gs_handle, PMSX003_MODE_ACTIVE);
    if (res != 0)
    {
        pmsx003_interface_debug_print("pmsx003: set mode failed.\n");
        (void)pmsx003_deinit(&gs_handle);
        
        return 1;
    }
    
    /* active read test */
    pmsx003_interface_debug_print("pmsx003: active read test.\n");
    
    for (i = 0; i < times; i++)
    {
        pmsx003_data_t data;
        
        /* delay 2000ms */
        pmsx003_interface_delay_ms(2000);
        
        /* read */
        res = pmsx003_read(&gs_handle, &data);
        if (res != 0)
        {
            pmsx003_interface_debug_print("pmsx003: read failed.\n");
            (void)pmsx003_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        pmsx003_interface_debug_print("pmsx003: pm1p0 standard is %d ug/m3.\n", data.pm1p0_standard_ug_m3);
        pmsx003_interface_debug_print("pmsx003: pm2p5 standard is %d ug/m3.\n", data.pm2p5_standard_ug_m3);
        pmsx003_interface_debug_print("pmsx003: pm10 standard is %d ug/m3.\n", data.pm10_standard_ug_m3);
        pmsx003_interface_debug_print("pmsx003: pm1p0 atmospheric is %d ug/m3.\n", data.pm1p0_atmospheric_ug_m3);
        pmsx003_interface_debug_print("pmsx003: pm2p5 atmospheric is %d ug/m3.\n", data.pm2p5_atmospheric_ug_m3);
        pmsx003_interface_debug_print("pmsx003: pm10 atmospheric is %d ug/m3.\n", data.pm10_atmospheric_ug_m3);
        pmsx003_interface_debug_print("pmsx003: beyond 0p3 um is %d.\n", data.beyond_0p3um);
        pmsx003_interface_debug_print("pmsx003: beyond 0p5 um is %d.\n", data.beyond_0p5um);
        pmsx003_interface_debug_print("pmsx003: beyond 1p0 um is %d.\n", data.beyond_1p0um);
        pmsx003_interface_debug_print("pmsx003: beyond 2p5 um is %d.\n", data.beyond_2p5um);
        pmsx003_interface_debug_print("pmsx003: beyond 5p0 um is %d.\n", data.beyond_5p0um);
        pmsx003_interface_debug_print("pmsx003: beyond 10 um is %d.\n", data.beyond_10um);
        pmsx003_interface_debug_print("pmsx003: version is 0x%02X.\n", data.version);
        pmsx003_interface_debug_print("pmsx003: error code is 0x%02X.\n", data.error_code);
    }
    
    /* set passive mode */
    res = pmsx003_set_mode(&gs_handle, PMSX003_MODE_PASSIVE);
    if (res != 0)
    {
        pmsx003_interface_debug_print("pmsx003: set mode failed.\n");
        (void)pmsx003_deinit(&gs_handle);
        
        return 1;
    }
    
    /* passive read test */
    pmsx003_interface_debug_print("pmsx003: passive read test.\n");
    
    for (i = 0; i < times; i++)
    {
        pmsx003_data_t data;
        
        /* delay 2000ms */
        pmsx003_interface_delay_ms(2000);
        
        /* read */
        res = pmsx003_read(&gs_handle, &data);
        if (res != 0)
        {
            pmsx003_interface_debug_print("pmsx003: read failed.\n");
            (void)pmsx003_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        pmsx003_interface_debug_print("pmsx003: pm1p0 standard is %d ug/m3.\n", data.pm1p0_standard_ug_m3);
        pmsx003_interface_debug_print("pmsx003: pm2p5 standard is %d ug/m3.\n", data.pm2p5_standard_ug_m3);
        pmsx003_interface_debug_print("pmsx003: pm10 standard is %d ug/m3.\n", data.pm10_standard_ug_m3);
        pmsx003_interface_debug_print("pmsx003: pm1p0 atmospheric is %d ug/m3.\n", data.pm1p0_atmospheric_ug_m3);
        pmsx003_interface_debug_print("pmsx003: pm2p5 atmospheric is %d ug/m3.\n", data.pm2p5_atmospheric_ug_m3);
        pmsx003_interface_debug_print("pmsx003: pm10 atmospheric is %d ug/m3.\n", data.pm10_atmospheric_ug_m3);
        pmsx003_interface_debug_print("pmsx003: beyond 0p3 um is %d.\n", data.beyond_0p3um);
        pmsx003_interface_debug_print("pmsx003: beyond 0p5 um is %d.\n", data.beyond_0p5um);
        pmsx003_interface_debug_print("pmsx003: beyond 1p0 um is %d.\n", data.beyond_1p0um);
        pmsx003_interface_debug_print("pmsx003: beyond 2p5 um is %d.\n", data.beyond_2p5um);
        pmsx003_interface_debug_print("pmsx003: beyond 5p0 um is %d.\n", data.beyond_5p0um);
        pmsx003_interface_debug_print("pmsx003: beyond 10 um is %d.\n", data.beyond_10um);
        pmsx003_interface_debug_print("pmsx003: version is 0x%02X.\n", data.version);
        pmsx003_interface_debug_print("pmsx003: error code is 0x%02X.\n", data.error_code);
    }
    
    /* sleep */
    res = pmsx003_sleep(&gs_handle);
    if (res != 0)
    {
        pmsx003_interface_debug_print("pmsx003: sleep failed.\n");
        (void)pmsx003_deinit(&gs_handle);
        
        return 1;
    }
    
    /* sleep */
    pmsx003_interface_debug_print("pmsx003: sleep.\n");
    
    /* delay 1000ms */
    pmsx003_interface_delay_ms(1000);
    
    /* wake up */
    res = pmsx003_wake_up(&gs_handle);
    if (res != 0)
    {
        pmsx003_interface_debug_print("pmsx003: wake up failed.\n");
        (void)pmsx003_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wake up */
    pmsx003_interface_debug_print("pmsx003: wake up.\n");
    
    /* finish read test */
    pmsx003_interface_debug_print("pmsx003: finish read test.\n");
    (void)pmsx003_deinit(&gs_handle);

    return 0;
}
