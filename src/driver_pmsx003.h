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
 * @file      driver_pmsx003.h
 * @brief     driver pmsx003 header file
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

#ifndef DRIVER_PMSX003_H
#define DRIVER_PMSX003_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup pmsx003_driver pmsx003 driver function
 * @brief    pmsx003 driver modules
 * @{
 */

/**
 * @addtogroup pmsx003_basic_driver
 * @{
 */

/**
 * @brief pmsx003 hard mode enumeration definition
 */
typedef enum
{
    PMSX003_HARD_MODE_SLEEP  = 0x00,        /**< sleep mode */
    PMSX003_HARD_MODE_NORMAL = 0x01,        /**< normal mode */
} pmsx003_hard_mode_t;

/**
 * @brief pmsx003 mode enumeration definition
 */
typedef enum
{
    PMSX003_MODE_PASSIVE = 0x00,        /**< passive mode */
    PMSX003_MODE_ACTIVE  = 0x01,        /**< active mode */
} pmsx003_mode_t;

/**
 * @brief pmsx003 data structure definition
 */
typedef struct pmsx003_data_s
{
    uint16_t pm1p0_standard_ug_m3;           /**< pm1.0 concentration unit, standard particle */
    uint16_t pm2p5_standard_ug_m3;           /**< pm2.5 concentration unit, standard particle */
    uint16_t pm10_standard_ug_m3;            /**< pm10 concentration unit, standard particle */
    uint16_t pm1p0_atmospheric_ug_m3;        /**< pm1.0 concentration unit, under atmospheric environment */
    uint16_t pm2p5_atmospheric_ug_m3;        /**< pm2.5 concentration unit, under atmospheric environment */
    uint16_t pm10_atmospheric_ug_m3;         /**< pm10 concentration unit, under atmospheric environment */
    uint16_t beyond_0p3um;                   /**< beyond 0.3 um in 0.1 L of air */
    uint16_t beyond_0p5um;                   /**< beyond 0.5 um in 0.1 L of air */
    uint16_t beyond_1p0um;                   /**< beyond 1.0 um in 0.1 L of air */
    uint16_t beyond_2p5um;                   /**< beyond 2.5 um in 0.1 L of air */
    uint16_t beyond_5p0um;                   /**< beyond 5.0 um in 0.1 L of air */
    uint16_t beyond_10um;                    /**< beyond 10 um in 0.1 L of air */
    uint8_t version;                         /**< version */
    uint8_t error_code;                      /**< error code */
} pmsx003_data_t;

/**
 * @brief pmsx003 handle structure definition
 */
typedef struct pmsx003_handle_s
{
    uint8_t (*reset_gpio_init)(void);                         /**< point to a reset_gpio_init function address */
    uint8_t (*reset_gpio_deinit)(void);                       /**< point to a reset_gpio_deinit function address */
    uint8_t (*reset_gpio_write)(uint8_t level);               /**< point to a reset_gpio_write function address */
    uint8_t (*set_gpio_init)(void);                           /**< point to a set_gpio_init function address */
    uint8_t (*set_gpio_deinit)(void);                         /**< point to a set_gpio_deinit function address */
    uint8_t (*set_gpio_write)(uint8_t level);                 /**< point to a set_gpio_write function address */
    uint8_t (*uart_init)(void);                               /**< point to an uart_init function address */
    uint8_t (*uart_deinit)(void);                             /**< point to an uart_deinit function address */
    uint16_t (*uart_read)(uint8_t *buf, uint16_t len);        /**< point to an uart_read function address */
    uint8_t (*uart_flush)(void);                              /**< point to an uart_flush function address */
    uint8_t (*uart_write)(uint8_t *buf, uint16_t len);        /**< point to an uart_write function address */
    void (*delay_ms)(uint32_t ms);                            /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);          /**< point to a debug_print function address */
    uint8_t inited;                                           /**< inited flag */
    uint8_t mode;                                             /**< mode */
} pmsx003_handle_t;

/**
 * @brief pmsx003 information structure definition
 */
typedef struct pmsx003_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} pmsx003_info_t;

/**
 * @}
 */

/**
 * @defgroup pmsx003_link_driver pmsx003 link driver function
 * @brief    pmsx003 link driver modules
 * @ingroup  pmsx003_driver
 * @{
 */

/**
 * @brief     initialize pmsx003_handle_t structure
 * @param[in] HANDLE pointer to a pmsx003 handle structure
 * @param[in] STRUCTURE pmsx003_handle_t
 * @note      none
 */
#define DRIVER_PMSX003_LINK_INIT(HANDLE, STRUCTURE)            memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link uart_init function
 * @param[in] HANDLE pointer to a pmsx003 handle structure
 * @param[in] FUC pointer to an uart_init function address
 * @note      none
 */
#define DRIVER_PMSX003_LINK_UART_INIT(HANDLE, FUC)            (HANDLE)->uart_init = FUC

/**
 * @brief     link uart_deinit function
 * @param[in] HANDLE pointer to a pmsx003 handle structure
 * @param[in] FUC pointer to an uart_deinit function address
 * @note      none
 */
#define DRIVER_PMSX003_LINK_UART_DEINIT(HANDLE, FUC)          (HANDLE)->uart_deinit = FUC

/**
 * @brief     link uart_read function
 * @param[in] HANDLE pointer to a pmsx003 handle structure
 * @param[in] FUC pointer to an uart_read function address
 * @note      none
 */
#define DRIVER_PMSX003_LINK_UART_READ(HANDLE, FUC)            (HANDLE)->uart_read = FUC

/**
 * @brief     link uart_write function
 * @param[in] HANDLE pointer to a pmsx003 handle structure
 * @param[in] FUC pointer to an uart_write function address
 * @note      none
 */
#define DRIVER_PMSX003_LINK_UART_WRITE(HANDLE, FUC)           (HANDLE)->uart_write = FUC

/**
 * @brief     link uart_flush function
 * @param[in] HANDLE pointer to a pmsx003 handle structure
 * @param[in] FUC pointer to an uart_flush function address
 * @note      none
 */
#define DRIVER_PMSX003_LINK_UART_FLUSH(HANDLE, FUC)           (HANDLE)->uart_flush = FUC

/**
 * @brief     link reset_gpio_init function
 * @param[in] HANDLE pointer to a pmsx003 handle structure
 * @param[in] FUC pointer to a reset_gpio_init function address
 * @note      none
 */
#define DRIVER_PMSX003_LINK_RESET_GPIO_INIT(HANDLE, FUC)      (HANDLE)->reset_gpio_init = FUC

/**
 * @brief     link reset_gpio_deinit function
 * @param[in] HANDLE pointer to a pmsx003 handle structure
 * @param[in] FUC pointer to a reset_gpio_deinit function address
 * @note      none
 */
#define DRIVER_PMSX003_LINK_RESET_GPIO_DEINIT(HANDLE, FUC)    (HANDLE)->reset_gpio_deinit = FUC

/**
 * @brief     link reset_gpio_write function
 * @param[in] HANDLE pointer to a pmsx003 handle structure
 * @param[in] FUC pointer to a reset_gpio_write function address
 * @note      none
 */
#define DRIVER_PMSX003_LINK_RESET_GPIO_WRITE(HANDLE, FUC)     (HANDLE)->reset_gpio_write = FUC

/**
 * @brief     link set_gpio_init function
 * @param[in] HANDLE pointer to a pmsx003 handle structure
 * @param[in] FUC pointer to a set_gpio_init function address
 * @note      none
 */
#define DRIVER_PMSX003_LINK_SET_GPIO_INIT(HANDLE, FUC)        (HANDLE)->set_gpio_init = FUC

/**
 * @brief     link set_gpio_deinit function
 * @param[in] HANDLE pointer to a pmsx003 handle structure
 * @param[in] FUC pointer to a set_gpio_deinit function address
 * @note      none
 */
#define DRIVER_PMSX003_LINK_SET_GPIO_DEINIT(HANDLE, FUC)      (HANDLE)->set_gpio_deinit = FUC

/**
 * @brief     link set_gpio_write function
 * @param[in] HANDLE pointer to a pmsx003 handle structure
 * @param[in] FUC pointer to a set_gpio_write function address
 * @note      none
 */
#define DRIVER_PMSX003_LINK_SET_GPIO_WRITE(HANDLE, FUC)       (HANDLE)->set_gpio_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to a pmsx003 handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_PMSX003_LINK_DELAY_MS(HANDLE, FUC)             (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to a pmsx003 handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_PMSX003_LINK_DEBUG_PRINT(HANDLE, FUC)          (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup pmsx003_basic_driver pmsx003 basic driver function
 * @brief    pmsx003 basic driver modules
 * @ingroup  pmsx003_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a pmsx003 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t pmsx003_info(pmsx003_info_t *info);

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
uint8_t pmsx003_init(pmsx003_handle_t *handle);

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
uint8_t pmsx003_deinit(pmsx003_handle_t *handle);

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
uint8_t pmsx003_read(pmsx003_handle_t *handle, pmsx003_data_t *data);

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
uint8_t pmsx003_reset(pmsx003_handle_t *handle);

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
uint8_t pmsx003_set_hard_mode(pmsx003_handle_t *handle, pmsx003_hard_mode_t mode);

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
uint8_t pmsx003_set_mode(pmsx003_handle_t *handle, pmsx003_mode_t mode);

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
uint8_t pmsx003_sleep(pmsx003_handle_t *handle);

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
uint8_t pmsx003_wake_up(pmsx003_handle_t *handle);

/**
 * @}
 */

/**
 * @defgroup pmsx003_extern_driver pmsx003 extern driver function
 * @brief    pmsx003 extern driver modules
 * @ingroup  pmsx003_driver
 * @{
 */

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
uint8_t pmsx003_set_buffer(pmsx003_handle_t *handle, uint8_t *buf, uint16_t len);

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
uint8_t pmsx003_get_buffer(pmsx003_handle_t *handle, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
