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
 * @file      main.c
 * @brief     main source file
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
#include "driver_pmsx003_read_test.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "getopt.h"
#include <ctype.h>
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
volatile uint16_t g_len;   /**< uart buffer length */

/**
 * @brief     pmsx003 full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t pmsx003(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"times", required_argument, NULL, 1},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* times */
            case 1 :
            {
                /* set times */
                times = atoi(optarg);
                
                break;
            }
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_read", type) == 0)
    {
        /* run read test */
        if (pmsx003_read_test(times) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        
        res = pmsx003_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        for (i = 0; i < times; i++)
        {
            pmsx003_data_t data;
            
            /* delay 1000ms */
            pmsx003_interface_delay_ms(1000);
            
            /* read data */
            res = pmsx003_basic_read(&data);
            if (res != 0)
            {
                (void)pmsx003_basic_deinit();
                
                return 1;
            }
            
            /* output */
            pmsx003_interface_debug_print("pmsx003: %d/%d.\n", i + 1, times);
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
        
        /* deinit */
        (void)pmsx003_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_sleep", type) == 0)
    {
        uint8_t res;
        
        /* init */
        res = pmsx003_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* sleep */
        res = pmsx003_basic_sleep();
        if (res != 0)
        {
            (void)pmsx003_basic_deinit();
            
            return 1;
        }
        
        /* sleep */
        pmsx003_interface_debug_print("pmsx003: sleep.\n");
        
        /* deinit */
        (void)pmsx003_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_wake-up", type) == 0)
    {
        uint8_t res;
        
        /* init */
        res = pmsx003_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* wake up */
        res = pmsx003_basic_wake_up();
        if (res != 0)
        {
            (void)pmsx003_basic_deinit();
            
            return 1;
        }
        
        /* sleep */
        pmsx003_interface_debug_print("pmsx003: wake up.\n");
        
        /* deinit */
        (void)pmsx003_basic_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        pmsx003_interface_debug_print("Usage:\n");
        pmsx003_interface_debug_print("  pmsx003 (-i | --information)\n");
        pmsx003_interface_debug_print("  pmsx003 (-h | --help)\n");
        pmsx003_interface_debug_print("  pmsx003 (-p | --port)\n");
        pmsx003_interface_debug_print("  pmsx003 (-t read | --test=read) [--times=<num>]\n");
        pmsx003_interface_debug_print("  pmsx003 (-e read | --example=read) [--times=<num>]\n");
        pmsx003_interface_debug_print("  pmsx003 (-e sleep | --example=sleep)\n");
        pmsx003_interface_debug_print("  pmsx003 (-e wake-up | --example=wake-up)\n");
        pmsx003_interface_debug_print("\n");
        pmsx003_interface_debug_print("Options:\n");
        pmsx003_interface_debug_print("  -e <read | sleep | wake-up>, --example=<read | sleep | wake-up>\n");
        pmsx003_interface_debug_print("                                  Run the driver example.\n");
        pmsx003_interface_debug_print("  -h, --help                      Show the help.\n");
        pmsx003_interface_debug_print("  -i, --information               Show the chip information.\n");
        pmsx003_interface_debug_print("  -p, --port                      Display the pins used by this device to connect the chip.\n");
        pmsx003_interface_debug_print("  -t <read>, --test=<read>        Run the driver test.\n");
        pmsx003_interface_debug_print("      --times=<num>               Set the running times.([default: 3])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        pmsx003_info_t info;
        
        /* print pmsx003 info */
        pmsx003_info(&info);
        pmsx003_interface_debug_print("pmsx003: chip is %s.\n", info.chip_name);
        pmsx003_interface_debug_print("pmsx003: manufacturer is %s.\n", info.manufacturer_name);
        pmsx003_interface_debug_print("pmsx003: interface is %s.\n", info.interface);
        pmsx003_interface_debug_print("pmsx003: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        pmsx003_interface_debug_print("pmsx003: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        pmsx003_interface_debug_print("pmsx003: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        pmsx003_interface_debug_print("pmsx003: max current is %0.2fmA.\n", info.max_current_ma);
        pmsx003_interface_debug_print("pmsx003: max temperature is %0.1fC.\n", info.temperature_max);
        pmsx003_interface_debug_print("pmsx003: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        pmsx003_interface_debug_print("pmsx003: TX connected to GPIOA PIN3.\n");
        pmsx003_interface_debug_print("pmsx003: RX connected to GPIOA PIN2.\n");
        pmsx003_interface_debug_print("pmsx003: RESET connected to GPIOA PIN8.\n");
        pmsx003_interface_debug_print("pmsx003: SET connected to GPIOA PIN0.\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register pmsx003 function */
    shell_init();
    shell_register("pmsx003", pmsx003);
    uart_print("pmsx003: welcome to libdriver pmsx003.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("pmsx003: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("pmsx003: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("pmsx003: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("pmsx003: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("pmsx003: param is invalid.\n");
            }
            else
            {
                uart_print("pmsx003: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
