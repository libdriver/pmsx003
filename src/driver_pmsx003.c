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
 * @file      driver_pmsx003.c
 * @brief     driver pmsx003 source file
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

#include "driver_pmsx003.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "PLANTOWER PMSX003"        /**< chip name */
#define MANUFACTURER_NAME         "PLANTOWER"                /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        4.5f                       /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                       /**< chip max supply voltage */
#define MAX_CURRENT               100.0f                     /**< chip max current */
#define TEMPERATURE_MIN           -10.0f                     /**< chip min operating temperature */
#define TEMPERATURE_MAX           60.0f                      /**< chip max operating temperature */
#define DRIVER_VERSION            1000                       /**< driver version */

/**
 * @brief chip command definition
 */
#define PMSX003_COMMAND_READ                       0xE2        /**< read command */
#define PMSX003_COMMAND_CHANGE_WORKING_MODE        0xE1        /**< change working mode */
#define PMSX003_COMMAND_CHANGE_CHIP_MODE           0xE4        /**< chip mode */

/**
 * @brief      make frame
 * @param[in]  command input command
 * @param[in]  data input data
 * @param[out] *output pointer to an output buffer
 * @return     status code
 *             - 0 success
 *             - 1 make frame failed
 * @note       none
 */
static uint8_t a_pmsx003_make_frame(uint8_t command, uint8_t data, uint8_t output[7])
{
    uint8_t i;
    uint16_t lrc;
    
    output[0] = 0x42;                     /* set 0x42 */
    output[1] = 0x4D;                     /* set 0x4D */
    output[2] = command;                  /* set command */
    output[3] = 0x00;                     /* set 0x00 */
    output[4] = data;                     /* set data */
    
    lrc = 0;                              /* init 0 */
    for (i = 0; i < 5; i++)               /* add all */
    {
        lrc += output[i];                 /* sum */
    }
    output[5] = (lrc >> 8) & 0xFF;        /* set lrc msb */
    output[6] = (lrc >> 0) & 0xFF;        /* set lrc lsb */
    
    return 0;                             /* success return 0 */
}

/**
 * @brief      parse frame
 * @param[in]  *handle pointer to a pmsx003 handle structure
 * @param[in]  *input pointer to an input buffer '
 * @param[in]  command input command
 * @param[out] *data pointer to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 parse frame failed
 * @note       none
 */
static uint8_t a_pmsx003_parse_frame(pmsx003_handle_t *handle, uint8_t input[8], uint8_t command, uint8_t *data)
{
    uint8_t i;
    uint16_t lrc;
    uint16_t lrc_check;
    
    lrc = 0;                                                       /* init 0 */
    for (i = 0; i < 6; i++)                                        /* add all */
    {
        lrc += input[i];                                           /* sum */
    }
    lrc_check = ((uint16_t)input[6] << 8) | input[7];              /* get lrc */
    if (lrc != lrc_check)                                          /* check lrc */
    {
        handle->debug_print("pmsx003: lrc check error.\n");        /* lrc check error */
        
        return 1;                                                  /* return error */
    }
    if ((input[0] == 0x42) && (input[1] == 0x4D))                  /* check header */
    {
        uint16_t len;
        
        len = ((uint16_t)input[2] << 8) | input[3];                /* get length */
        if (len != 4)                                              /* check length */
        {
            return 1;                                              /* return error */
        }
        if (input[4] != command)                                   /* check command */
        {
            return 1;                                              /* return error */
        }
        *data = input[5];                                          /* get data */
        
        return 0;                                                  /* success return 0 */
    }
    else
    {
        return 1;                                                  /* return error */
    }
}

/**
 * @brief      parse data
 * @param[in]  *handle pointer to a pmsx003 handle structure
 * @param[in]  *input pointer to an input buffer
 * @param[out] *data pointer to a data structure
 * @return     status code
 *             - 0 success
 *             - 1 parse frame failed
 * @note       none
 */
static uint8_t a_pmsx003_parse_data(pmsx003_handle_t *handle, uint8_t input[32], pmsx003_data_t *data)
{
    uint8_t i;
    uint16_t lrc;
    uint16_t lrc_check;
    
    lrc = 0;                                                                      /* init 0 */
    for (i = 0; i < 30; i++)                                                      /* add all */
    {
        lrc += input[i];                                                          /* sum */
    }
    lrc_check = ((uint16_t)input[30] << 8) | input[31];                           /* get lrc */
    if (lrc != lrc_check)                                                         /* check lrc */
    {
        handle->debug_print("pmsx003: lrc check error.\n");                       /* lrc check error */
        
        return 1;                                                                 /* return error */
    }
    if ((input[0] == 0x42) && (input[1] == 0x4D))                                 /* check header */
    {
        uint16_t len;
        
        len = ((uint16_t)input[2] << 8) | input[3];                               /* get length */
        if (len != 28)                                                            /* check length */
        {
            return 1;                                                             /* return error */
        }
        
        data->pm1p0_standard_ug_m3 = ((uint16_t)input[4] << 8) | input[5];        /* set pm1p0 standard ug/m3 */
        data->pm2p5_standard_ug_m3 = ((uint16_t)input[6] << 8) | input[7];        /* set pm2p5 standard ug/m3 */
        data->pm10_standard_ug_m3 = ((uint16_t)input[8] << 8) | input[9];         /* set pm10 standard ug/m3 */
        data->pm1p0_atmospheric_ug_m3 = ((uint16_t)input[10] << 8) | input[11];   /* set pm1p0 atmospheric ug/m3 */
        data->pm2p5_atmospheric_ug_m3 = ((uint16_t)input[12] << 8) | input[13];   /* set pm2p5 atmospheric ug/m3 */
        data->pm10_atmospheric_ug_m3 = ((uint16_t)input[14] << 8) | input[15];    /* set pm10 atmospheric ug/m3 */
        data->beyond_0p3um = ((uint16_t)input[16] << 8) | input[17];              /* set beyond 0p3um */
        data->beyond_0p5um = ((uint16_t)input[18] << 8) | input[19];              /* set beyond 0p5um */
        data->beyond_1p0um = ((uint16_t)input[20] << 8) | input[21];              /* set beyond 1p0um */
        data->beyond_2p5um = ((uint16_t)input[22] << 8) | input[23];              /* set beyond 2p5um */
        data->beyond_5p0um = ((uint16_t)input[24] << 8) | input[25];              /* set beyond 5p0um */
        data->beyond_10um = ((uint16_t)input[26] << 8) | input[27];               /* set beyond 10um */
        data->version = input[28];                                                /* set version */
        data->error_code = input[29];                                             /* set error code */
        
        return 0;                                                                 /* success return 0 */
    }
    else
    {
        return 1;                                                                 /* return error */
    }
}

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to a pmsx003 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 uart or gpio initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t pmsx003_init(pmsx003_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->debug_print == NULL)                                        /* check debug_print */
    {
        return 3;                                                           /* return error */
    }
    if (handle->uart_init == NULL)                                          /* check uart_init */
    {
        handle->debug_print("pmsx003: uart_init is null.\n");               /* uart_init is null */
        
        return 3;                                                           /* return error */
    }
    if (handle->uart_deinit == NULL)                                        /* check uart_deinit */
    {
        handle->debug_print("pmsx003: uart_deinit is null.\n");             /* uart_deinit is null */
        
        return 3;                                                           /* return error */
    }
    if (handle->uart_read == NULL)                                          /* check uart_read */
    {
        handle->debug_print("pmsx003: uart_read is null.\n");               /* uart_read is null */
        
        return 3;                                                           /* return error */
    }
    if (handle->uart_flush == NULL)                                         /* check uart_flush */
    {
        handle->debug_print("pmsx003: uart_flush is null.\n");              /* uart_flush is null */
        
        return 3;                                                           /* return error */
    }
    if (handle->uart_write == NULL)                                         /* check uart_write */
    {
        handle->debug_print("pmsx003: uart_write is null.\n");              /* uart_write is null */
        
        return 3;                                                           /* return error */
    }
    if (handle->reset_gpio_init == NULL)                                    /* check reset_gpio_init */
    {
        handle->debug_print("pmsx003: reset_gpio_init is null.\n");         /* reset_gpio_init is null */
        
        return 3;                                                           /* return error */
    }
    if (handle->reset_gpio_deinit == NULL)                                  /* check reset_gpio_deinit */
    {
        handle->debug_print("pmsx003: reset_gpio_deinit is null.\n");       /* reset_gpio_deinit is null */
        
        return 3;                                                           /* return error */
    }
    if (handle->reset_gpio_write == NULL)                                   /* check reset_gpio_write */
    {
        handle->debug_print("pmsx003: reset_gpio_write is null.\n");        /* reset_gpio_write is null */
        
        return 3;                                                           /* return error */
    }
    if (handle->set_gpio_init == NULL)                                      /* check set_gpio_init */
    {
        handle->debug_print("pmsx003: set_gpio_init is null.\n");           /* set_gpio_init is null */
        
        return 3;                                                           /* return error */
    }
    if (handle->set_gpio_deinit == NULL)                                    /* check set_gpio_deinit */
    {
        handle->debug_print("pmsx003: set_gpio_deinit is null.\n");         /* set_gpio_deinit is null */
        
        return 3;                                                           /* return error */
    }
    if (handle->set_gpio_write == NULL)                                     /* check set_gpio_write */
    {
        handle->debug_print("pmsx003: set_gpio_write is null.\n");          /* set_gpio_write is null */
        
        return 3;                                                           /* return error */
    }
    if (handle->delay_ms == NULL)                                           /* check delay_ms */
    {
        handle->debug_print("pmsx003: delay_ms is null.\n");                /* delay_ms is null */
        
        return 3;                                                           /* return error */
    }
    
    if (handle->reset_gpio_init() != 0)                                     /* reset gpio init */
    {
        handle->debug_print("pmsx003: reset gpio init failed.\n");          /* reset gpio init failed */
        
        return 1;                                                           /* return error */
    }
    if (handle->set_gpio_init() != 0)                                       /* set gpio init */
    {
        handle->debug_print("pmsx003: set gpio init failed.\n");            /* set gpio init failed */
        (void)handle->reset_gpio_deinit();                                  /* reset gpio deinit */
        
        return 1;                                                           /* return error */
    }
    if (handle->uart_init() != 0)                                           /* uart init */
    {
        handle->debug_print("pmsx003: uart init failed.\n");                /* uart init failed */
        (void)handle->reset_gpio_deinit();                                  /* reset gpio deinit */
        (void)handle->set_gpio_deinit();                                    /* set gpio deinit */
        
        return 1;                                                           /* return error */
    }
    if (handle->set_gpio_write(1) != 0)                                     /* normal working */
    {
        handle->debug_print("pmsx003: set gpio write failed.\n");           /* set gpio write failed */
        (void)handle->reset_gpio_deinit();                                  /* reset gpio deinit */
        (void)handle->set_gpio_deinit();                                    /* set gpio deinit */
        (void)handle->uart_deinit();                                        /* uart deinit */
        
        return 1;                                                           /* return error */
    }
    handle->delay_ms(100);                                                  /* delay 100ms */
    if (handle->reset_gpio_write(0) != 0)                                   /* set low */
    {
        handle->debug_print("pmsx003: set gpio write failed.\n");           /* set gpio write failed */
        (void)handle->reset_gpio_deinit();                                  /* reset gpio deinit */
        (void)handle->set_gpio_deinit();                                    /* set gpio deinit */
        (void)handle->uart_deinit();                                        /* uart deinit */
        
        return 1;                                                           /* return error */
    }
    handle->delay_ms(100);                                                  /* delay 100ms */
    if (handle->reset_gpio_write(1) != 0)                                   /* set high */
    {
        handle->debug_print("pmsx003: set gpio write failed.\n");           /* set gpio write failed */
        (void)handle->reset_gpio_deinit();                                  /* reset gpio deinit */
        (void)handle->set_gpio_deinit();                                    /* set gpio deinit */
        (void)handle->uart_deinit();                                        /* uart deinit */
        
        return 1;                                                           /* return error */
    }
    handle->delay_ms(300);                                                  /* delay 300ms */
    res = handle->uart_flush();                                             /* uart flush */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("pmsx003: uart flush failed.\n");               /* uart flush failed */
        (void)handle->reset_gpio_deinit();                                  /* reset gpio deinit */
        (void)handle->set_gpio_deinit();                                    /* set gpio deinit */
        (void)handle->uart_deinit();                                        /* uart deinit */
        
        return 1;                                                           /* return error */
    }
    handle->mode = (uint8_t)PMSX003_MODE_ACTIVE;                            /* init 1 */
    handle->inited = 1;                                                     /* flag finish initialization */
    
    return 0;                                                               /* success return 0 */
}

/**
 * @brief     close the chip
 * @param[in] *handle pointer to a pmsx003 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 uart or gpio deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pmsx003_deinit(pmsx003_handle_t *handle)
{
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    if (handle->reset_gpio_deinit() != 0)                                  /* reset gpio deinit */
    {
        handle->debug_print("pmsx003: reset gpio deinit failed.\n");       /* reset gpio deinit failed */
        
        return 1;                                                          /* return error */
    }
    if (handle->set_gpio_deinit() != 0)                                    /* set gpio deinit */
    {
        handle->debug_print("pmsx003: set gpio deinit failed.\n");         /* set gpio deinit failed */
        
        return 1;                                                          /* return error */
    }  
    if (handle->uart_deinit() != 0)                                        /* uart deinit */
    {
        handle->debug_print("pmsx003: uart deinit failed.\n");             /* uart deinit failed */
        
        return 1;                                                          /* return error */
    }         
    handle->inited = 0;                                                    /* flag close */
    
    return 0;                                                              /* success return 0 */ 
}

/**
 * @brief     reset
 * @param[in] *handle pointer to a pmsx003 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pmsx003_reset(pmsx003_handle_t *handle)
{
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    
    if (handle->reset_gpio_write(0) != 0)                                /* set low */
    {
        handle->debug_print("pmsx003: set gpio write failed.\n");        /* set gpio write failed */
        
        return 1;                                                        /* return error */
    }
    handle->delay_ms(100);                                               /* delay 100ms */
    if (handle->reset_gpio_write(1) != 0)                                /* set high */
    {
        handle->debug_print("pmsx003: set gpio write failed.\n");        /* set gpio write failed */
        
        return 1;                                                        /* return error */
    }
    handle->delay_ms(300);                                               /* delay 300ms */
    
    return 0;                                                            /* success return 0 */ 
}

/**
 * @brief     set hard mode
 * @param[in] *handle pointer to a pmsx003 handle structure
 * @param[in] mode hard mode
 * @return    status code
 *            - 0 success
 *            - 1 set hard mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pmsx003_set_hard_mode(pmsx003_handle_t *handle, pmsx003_hard_mode_t mode)
{
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    if ((uint8_t)mode != 0)                                                  /* normal */
    {
        if (handle->set_gpio_write(1) != 0)                                  /* normal working */
        {
            handle->debug_print("pmsx003: set gpio write failed.\n");        /* set gpio write failed */
            
            return 1;                                                        /* return error */
        }
    }
    else                                                                     /* sleep */
    {
        if (handle->set_gpio_write(0) != 0)                                  /* sleep working */
        {
            handle->debug_print("pmsx003: set gpio write failed.\n");        /* set gpio write failed */
            
            return 1;                                                        /* return error */
        }
    }
    handle->delay_ms(300);                                                   /* delay 300ms */
    
    return 0;                                                                /* success return 0 */ 
}

/**
 * @brief     set mode
 * @param[in] *handle pointer to a pmsx003 handle structure
 * @param[in] mode chip mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 frame error
 * @note      none
 */
uint8_t pmsx003_set_mode(pmsx003_handle_t *handle, pmsx003_mode_t mode)
{
    uint8_t res;
    uint8_t data;
    uint8_t output[7];
    uint8_t input[8];
    uint16_t len;
    
    if (handle == NULL)                                                                            /* check handle */
    {
        return 2;                                                                                  /* return error */
    }
    if (handle->inited != 1)                                                                       /* check handle initialization */
    {
        return 3;                                                                                  /* return error */
    }
    
    (void)a_pmsx003_make_frame(PMSX003_COMMAND_CHANGE_WORKING_MODE, (uint8_t)mode, output);        /* make frame */
    res = handle->uart_flush();                                                                    /* uart flush */
    if (res != 0)                                                                                  /* check result */
    {
        handle->debug_print("pmsx003: uart flush failed.\n");                                      /* uart flush failed */
        
        return 1;                                                                                  /* return error */
    }
    res = handle->uart_write(output, 7);                                                           /* uart write */
    if (res != 0)                                                                                  /* check result */
    {
        handle->debug_print("pmsx003: uart write failed.\n");                                      /* uart write failed */
        
        return 1;                                                                                  /* return error */
    }
    handle->delay_ms(100);                                                                         /* delay 100ms */
    len = handle->uart_read(input, 8);                                                             /* uart read */
    if (len != 8)                                                                                  /* check length */
    {
        handle->debug_print("pmsx003: uart read failed.\n");                                       /* uart read failed */
        
        return 1;                                                                                  /* return error */
    }
    res = a_pmsx003_parse_frame(handle, input, PMSX003_COMMAND_CHANGE_WORKING_MODE, &data);        /* parse frame */
    if (res != 0)                                                                                  /* check result */
    {
        handle->debug_print("pmsx003: frame error.\n");                                            /* frame error */
        
        return 4;                                                                                  /* return error */
    }
    if (data != (uint8_t)mode)                                                                     /* check data */
    {
        handle->debug_print("pmsx003: set mode failed.\n");                                        /* set mode failed */
        
        return 1;                                                                                  /* return error */
    }
    handle->mode = (uint8_t)mode;                                                                  /* save mode */
    
    return 0;                                                                                      /* success return 0 */ 
}

/**
 * @brief     sleep
 * @param[in] *handle pointer to a pmsx003 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 sleep failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 frame error
 * @note      none
 */
uint8_t pmsx003_sleep(pmsx003_handle_t *handle)
{
    uint8_t res;
    uint8_t data;
    uint8_t output[7];
    uint8_t input[8];
    uint16_t len;
    
    if (handle == NULL)                                                                         /* check handle */
    {
        return 2;                                                                               /* return error */
    }
    if (handle->inited != 1)                                                                    /* check handle initialization */
    {
        return 3;                                                                               /* return error */
    }
    
    (void)a_pmsx003_make_frame(PMSX003_COMMAND_CHANGE_CHIP_MODE, (uint8_t)0x00, output);        /* make frame */
    res = handle->uart_flush();                                                                 /* uart flush */
    if (res != 0)                                                                               /* check result */
    {
        handle->debug_print("pmsx003: uart flush failed.\n");                                   /* uart flush failed */
        
        return 1;                                                                               /* return error */
    }
    res = handle->uart_write(output, 7);                                                        /* uart write */
    if (res != 0)                                                                               /* check result */
    {
        handle->debug_print("pmsx003: uart write failed.\n");                                   /* uart write failed */
        
        return 1;                                                                               /* return error */
    }
    handle->delay_ms(100);                                                                      /* delay 100ms */
    len = handle->uart_read(input, 8);
    if (len != 8)                                                                               /* check length */
    {                                                                                           /* uart read */
        handle->debug_print("pmsx003: uart read failed.\n");                                    /* uart read failed */
        
        return 1;                                                                               /* return error */
    }
    res = a_pmsx003_parse_frame(handle, input, PMSX003_COMMAND_CHANGE_CHIP_MODE, &data);        /* parse frame */
    if (res != 0)                                                                               /* check result */
    {
        handle->debug_print("pmsx003: frame error.\n");                                         /* frame error */
        
        return 4;                                                                               /* return error */
    }
    if (data != (uint8_t)0x00)                                                                  /* check data */
    {
        handle->debug_print("pmsx003: sleep failed.\n");                                        /* sleep failed */
        
        return 1;                                                                               /* return error */
    }
    
    return 0;                                                                                   /* success return 0 */ 
}

/**
 * @brief     wake up
 * @param[in] *handle pointer to a pmsx003 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 wake up failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 frame error
 * @note      none
 */
uint8_t pmsx003_wake_up(pmsx003_handle_t *handle)
{
    uint8_t res;
    uint8_t output[7];
    
    if (handle == NULL)                                                                         /* check handle */
    {
        return 2;                                                                               /* return error */
    }
    if (handle->inited != 1)                                                                    /* check handle initialization */
    {
        return 3;                                                                               /* return error */
    }
    
    (void)a_pmsx003_make_frame(PMSX003_COMMAND_CHANGE_CHIP_MODE, (uint8_t)0x01, output);        /* make frame */
    res = handle->uart_flush();                                                                 /* uart flush */
    if (res != 0)                                                                               /* check result */
    {
        handle->debug_print("pmsx003: uart flush failed.\n");                                   /* uart flush failed */
        
        return 1;                                                                               /* return error */
    }
    res = handle->uart_write(output, 7);                                                        /* uart write */
    if (res != 0)                                                                               /* check result */
    {
        handle->debug_print("pmsx003: uart write failed.\n");                                   /* uart write failed */
        
        return 1;                                                                               /* return error */
    }
    handle->delay_ms(300);                                                                      /* delay 300ms */
    
    return 0;                                                                                   /* success return 0 */ 
}

/**
 * @brief      read the data
 * @param[in]  *handle pointer to a pmsx003 handle structure
 * @param[out] *data pointer to a data structure
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 frame error
 *             - 5 data error
 * @note       none
 */
uint8_t pmsx003_read(pmsx003_handle_t *handle, pmsx003_data_t *data)
{
    uint8_t res;
    uint8_t output[7];
    uint8_t input[32];
    uint16_t len;
    
    if (handle == NULL)                                                                 /* check handle */
    {
        return 2;                                                                       /* return error */
    }
    if (handle->inited != 1)                                                            /* check handle initialization */
    {
        return 3;                                                                       /* return error */
    }
    
    if (handle->mode != 0)                                                              /* active mode */
    {
        len = handle->uart_read(input, 32);                                             /* uart read */
        if (len != 32)                                                                  /* check length */
        {
            handle->debug_print("pmsx003: uart read failed.\n");                        /* uart read failed */
            
            return 1;                                                                   /* return error */
        }
        res = handle->uart_flush();                                                     /* uart flush */
        if (res != 0)                                                                   /* check result */
        {
            handle->debug_print("pmsx003: uart flush failed.\n");                       /* uart flush failed */
            
            return 1;                                                                   /* return error */
        }
        res = a_pmsx003_parse_data(handle, input, data);                                /* parse data */
        if (res != 0)                                                                   /* check result */
        {
            handle->debug_print("pmsx003: frame error.\n");                             /* frame error */
            
            return 4;                                                                   /* return error */
        }
        if (data->error_code != 0)                                                      /* check error code */
        {
            handle->debug_print("pmsx003: data error.\n");                              /* data error */
            
            return 5;                                                                   /* return error */
        }
    }
    else                                                                                /* passive mode */
    {
        (void)a_pmsx003_make_frame(PMSX003_COMMAND_READ, (uint8_t)0x00, output);        /* make frame */
        res = handle->uart_flush();                                                     /* uart flush */
        if (res != 0)                                                                   /* check result */
        {
            handle->debug_print("pmsx003: uart flush failed.\n");                       /* uart flush failed */
            
            return 1;                                                                   /* return error */
        }
        res = handle->uart_write(output, 7);                                            /* uart write */
        if (res != 0)                                                                   /* check result */
        {
            handle->debug_print("pmsx003: uart write failed.\n");                       /* uart write failed */
            
            return 1;                                                                   /* return error */
        }
        handle->delay_ms(100);                                                          /* delay 100ms */
        len = handle->uart_read(input, 32);                                             /* uart read */
        if (len != 32)                                                                  /* check length */
        {
            handle->debug_print("pmsx003: uart read failed.\n");                        /* uart read failed */
            
            return 1;                                                                   /* return error */
        }
        res = a_pmsx003_parse_data(handle, input, data);                                /* parse data */
        if (res != 0)                                                                   /* check result */
        {
            handle->debug_print("pmsx003: frame error.\n");                             /* frame error */
            
            return 4;                                                                   /* return error */
        }
        if (data->error_code != 0)                                                      /* check error code */
        {
            handle->debug_print("pmsx003: data error.\n");                              /* data error */
            
            return 5;                                                                   /* return error */
        }
    }
    
    return 0;                                                                           /* success return 0 */ 
}

/**
 * @brief     set buffer
 * @param[in] *handle pointer to a pmsx003 handle structure
 * @param[in] *buf pointer to a data buffer
 * @param[in] len buffer length
 * @return    status code
 *            - 0 success
 *            - 1 set buffer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pmsx003_set_buffer(pmsx003_handle_t *handle, uint8_t *buf, uint16_t len)
{
    uint8_t res;

    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    res = handle->uart_flush();                                      /* uart flush */
    if (res != 0)                                                    /* check result */
    {
        handle->debug_print("pmsx003: uart flush failed.\n");        /* uart flush failed */
        
        return 1;                                                    /* return error */
    }
    res = handle->uart_write(buf, len);                              /* uart write */
    if (res != 0)                                                    /* check result */
    {
        handle->debug_print("pmsx003: uart write failed.\n");        /* uart write failed */
        
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */ 
}

/**
 * @brief      get buffer
 * @param[in]  *handle pointer to a pmsx003 handle structure
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len buffer length
 * @return     status code
 *             - 0 success
 *             - 1 get buffer failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pmsx003_get_buffer(pmsx003_handle_t *handle, uint8_t *buf, uint16_t len)
{
    uint16_t l;

    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    }
    
    l = handle->uart_read((uint8_t *)buf, len);                     /* uart read */
    if (l != len)                                                   /* check result */
    {
        handle->debug_print("pmsx003: uart read failed.\n");        /* uart read failed */
       
        return 1;                                                   /* return error */
    }
    
    return 0;                                                       /* success return 0 */ 
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a pmsx003 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t pmsx003_info(pmsx003_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(pmsx003_info_t));                        /* initialize pmsx003 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "UART", 8);                            /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
