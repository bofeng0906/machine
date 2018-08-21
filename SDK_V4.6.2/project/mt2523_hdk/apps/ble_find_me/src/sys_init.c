/* Copyright Statement:
 *
 * (C) 2005-2016  MediaTek Inc. All rights reserved.
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. ("MediaTek") and/or its licensors.
 * Without the prior written permission of MediaTek and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) MediaTek Software
 * if you have agreed to and been bound by the applicable license agreement with
 * MediaTek ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of MediaTek Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT MEDIATEK SOFTWARE RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 */

#include <stdint.h>
#include <stdio.h>

#include "mt2523.h"
#include "system_mt2523.h"

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#include "hal.h"
#include "syslog.h"
#include "sys_init.h"
#include "hal_dcxo.h"

#include "memory_map.h"
#include "bsp_gpio_ept_config.h"
#include "hal_display_dsi.h"
/* Enable battery_management */
#ifdef MTK_SMART_BATTERY_ENABLE
#include "hal_charger.h"
#include "cust_battery_meter.h"
#include "battery_management.h"
#endif

/* Enable NVDM feature */
#ifdef MTK_NVDM_ENABLE
#include "nvdm.h"
#endif
#include "memory_attribute.h"
#include "task_def.h"
#include "bt_debug.h"


/* target system frequency selection */
/* Set system clock to 26M Hz */
#ifdef MTK_SYSTEM_CLOCK_26M
static const uint32_t target_freq = 26000;
#else
/* Set system clock to 104M Hz */
#ifdef MTK_SYSTEM_CLOCK_104M
static const uint32_t target_freq = 104000;
#else
static const uint32_t target_freq = 208000;
#endif
#endif


#define BLE_UART1_IO     /*defines if hci and bt command can be used*/

/* BT HCI log port */
#ifdef BLE_UART1_IO
#define VFIFO_SIZE_RX_BT (512)
#define VFIFO_SIZE_TX_BT (1024)
#define VFIFO_ALERT_LENGTH_BT (20)

ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN static uint8_t g_bt_cmd_tx_vfifo[VFIFO_SIZE_TX_BT];
ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN static uint8_t g_bt_cmd_rx_vfifo[VFIFO_SIZE_RX_BT];
static hal_uart_port_t      g_atci_bt_port;
static SemaphoreHandle_t    g_bt_io_semaphore = NULL;

bool bt_hci_log_enabled(void)
{
    return true;
}

static void ble_at_cmd_trix_space(char *cmd_buf)
{
    char *token = NULL;

    // remove '\n';
    token = strrchr(cmd_buf, '\n');
    while (token != NULL) {
        *token = '\0';
        token = strrchr(cmd_buf, '\n');
    }

    // remove '\r';
    token = strrchr(cmd_buf, '\r');
    while (token != NULL) {
        *token = '\0';
        token = strrchr(cmd_buf, '\r');
    }

}

static void ble_at_cmd_processing(void)
{
    while (1) {
        uint32_t    read_len;

        read_len = hal_uart_get_available_receive_bytes(g_atci_bt_port);

        if (read_len > 0) {
            hal_uart_receive_dma(g_atci_bt_port, g_bt_cmd_rx_vfifo, read_len);

            ble_at_cmd_trix_space((char *)g_bt_cmd_rx_vfifo);
            read_len = strlen((char *)g_bt_cmd_rx_vfifo);
            //ble_ancs_perform_action(g_bt_cmd_rx_vfifo);
        } else {
            xSemaphoreTake(g_bt_io_semaphore, portMAX_DELAY);
        }
    }

}

static void ble_cmd_task(void *param)
{
    while (1) {
        ble_at_cmd_processing();
    }
}

static void ble_io_uart_irq(hal_uart_callback_event_t event, void *parameter)
{

    BaseType_t  x_higher_priority_task_woken = pdFALSE;

    if (HAL_UART_EVENT_READY_TO_READ == event) {
        xSemaphoreGiveFromISR(g_bt_io_semaphore, &x_higher_priority_task_woken);
        portYIELD_FROM_ISR( x_higher_priority_task_woken );
    }
}

static hal_uart_status_t ble_io_uart_init(hal_uart_port_t port)
{
    hal_uart_status_t ret;
    /* Configure UART PORT */
    hal_uart_config_t uart_config = {
        .baudrate = HAL_UART_BAUDRATE_115200,
        .word_length = HAL_UART_WORD_LENGTH_8,
        .stop_bit = HAL_UART_STOP_BIT_1,
        .parity = HAL_UART_PARITY_NONE
    };

    g_atci_bt_port = port;

    ret = hal_uart_init(port, &uart_config);

    if (HAL_UART_STATUS_OK == ret) {

        hal_uart_dma_config_t   dma_config = {
            .send_vfifo_buffer              = g_bt_cmd_tx_vfifo,
            .send_vfifo_buffer_size         = VFIFO_SIZE_TX_BT,
            .send_vfifo_threshold_size      = 128,
            .receive_vfifo_buffer           = g_bt_cmd_rx_vfifo,
            .receive_vfifo_buffer_size      = VFIFO_SIZE_RX_BT,
            .receive_vfifo_threshold_size   = 128,
            .receive_vfifo_alert_size       = VFIFO_ALERT_LENGTH_BT
        };

        g_bt_io_semaphore = xSemaphoreCreateBinary();

        ret = hal_uart_set_dma(port, &dma_config);

        ret = hal_uart_register_callback(port, ble_io_uart_irq, NULL);

    }

    LOG_E(common, "ble_io_uart_init--port: %d, ret: %d\n", port, ret);

    return ret;
}
#endif

/**
* @brief       This function is low-level libc implementation, which is used for printf family.
* @param[in]   ch: the character that will be put into uart port.
* @return      The character as input.
*/
/* Predefined MACRO of gcc */
#ifdef __GNUC__
int __io_putchar(int ch)
#else
int fputc(int ch, FILE *f)
#endif
{
/* Enable port service feature */
#ifdef MTK_PORT_SERVICE_ENABLE
    log_write((char*)&ch, 1);
    return ch;
#else
    /* Place your implementation of fputc here */
    /* e.g. write a character to the uart port configured in log_uart_init() */
    log_putchar(ch);
    return ch;
#endif
}

/**
* @brief       This function is to config system clock.
* @param[in]   None.
* @return      None.
*/
static void SystemClock_Config(void)
{
    hal_clock_init();

    /* Initialize the Dynamic Voltage Frequency Switch(DVFS) and switch the target freqeuncy. */
    hal_dvfs_init();
    hal_dvfs_target_cpu_frequency(target_freq, HAL_DVFS_FREQ_RELATION_H);
}

/**
* @brief       This function is to initialize cache controller.
* @param[in]   None.
* @return      None.
*/
static void cache_init(void)
{
    hal_cache_region_t region, region_number;

    /* Max region number is 16 */
    hal_cache_region_config_t region_cfg_tbl[] = {
        /* cacheable address, cacheable size(both MUST be 4k bytes aligned) */
/* UBIN length */
#ifdef CM4_UBIN_LENGTH
        {BL_BASE, BL_LENGTH + CM4_LENGTH + CM4_UBIN_LENGTH},
#else
        {BL_BASE, BL_LENGTH + CM4_LENGTH},
#endif
        /* virtual memory */
        {VRAM_BASE, VRAM_LENGTH}
    };

    region_number = (hal_cache_region_t) (sizeof(region_cfg_tbl) / sizeof(region_cfg_tbl[0]));

    hal_cache_init();
    hal_cache_set_size(HAL_CACHE_SIZE_32KB);
    for (region = HAL_CACHE_REGION_0; region < region_number; region++) {
        hal_cache_region_config(region, &region_cfg_tbl[region]);
        hal_cache_region_enable(region);
    }
    for ( ; region < HAL_CACHE_REGION_MAX; region++) {
        hal_cache_region_disable(region);
    }
    hal_cache_enable();
}

/**
* @brief       caculate actual bit value of region size.
* @param[in]   region_size: actual region size.
* @return      corresponding bit value of region size for MPU setting.
*/
static uint32_t caculate_mpu_region_size( uint32_t region_size )
{
    uint32_t count;

    if (region_size < 32) {
        return 0;
    }
    for (count = 0; ((region_size  & 0x80000000) == 0); count++, region_size  <<= 1);
    return 30 - count;
}

/**
* @brief       This function is to initialize MPU.
* @param[in]   None.
* @return      None.
*/
static void mpu_init(void)
{
    hal_mpu_region_t region, region_number;
    hal_mpu_region_config_t region_config;
    typedef struct {
        uint32_t mpu_region_base_address;/**< MPU region start address */
        uint32_t mpu_region_end_address;/**< MPU region end address */
        hal_mpu_access_permission_t mpu_region_access_permission; /**< MPU region access permission */
        uint8_t mpu_subregion_mask; /**< MPU sub region mask*/
        bool mpu_xn;/**< XN attribute of MPU, if set TRUE, execution of an instruction fetched from the corresponding region is not permitted */
    } mpu_region_information_t;

#if defined (__GNUC__) || defined (__CC_ARM)

    //RAM: VECTOR TABLE+RAM CODE+RO DATA
    extern uint32_t Image$$RAM_TEXT$$Base;
    extern uint32_t Image$$RAM_TEXT$$Limit;
    //TCM: TCM CODE+RO DATA
    extern uint32_t Image$$TCM$$RO$$Base;
    extern uint32_t Image$$TCM$$RO$$Limit;
    //STACK END
    extern unsigned int Image$$STACK$$ZI$$Base[];

    /* MAX region number is 8 */
    mpu_region_information_t region_information[] = {
        /* mpu_region_start_address, mpu_region_end_address, mpu_region_access_permission, mpu_subregion_mask, mpu_xn */
        {(uint32_t) &Image$$RAM_TEXT$$Base, (uint32_t) &Image$$RAM_TEXT$$Limit, HAL_MPU_READONLY, 0x0, FALSE}, //Vector table+RAM code+RAM rodata
        {(uint32_t) &Image$$RAM_TEXT$$Base + VRAM_BASE, (uint32_t) &Image$$RAM_TEXT$$Limit + VRAM_BASE, HAL_MPU_NO_ACCESS, 0x0, TRUE}, //Virtual memory
        {(uint32_t) &Image$$TCM$$RO$$Base, (uint32_t) &Image$$TCM$$RO$$Limit, HAL_MPU_READONLY, 0x0, FALSE},//TCM code+TCM rodata
        {(uint32_t) &Image$$STACK$$ZI$$Base, (uint32_t) &Image$$STACK$$ZI$$Base + 32, HAL_MPU_READONLY, 0x0, TRUE} //Stack end check for stack overflow
    };

#elif defined (__ICCARM__)

#pragma section = ".intvec"
#pragma section = ".ram_rodata"
#pragma section = ".tcm_code"
#pragma section = ".tcm_rwdata"
#pragma section = "CSTACK"

    /* MAX region number is 8, please DO NOT modify memory attribute of this structure! */
    _Pragma("location=\".ram_rodata\"") static mpu_region_information_t region_information[] = {
        /* mpu_region_start_address, mpu_region_end_address, mpu_region_access_permission, mpu_subregion_mask, mpu_xn */
        {(uint32_t)__section_begin(".intvec"), (uint32_t)__section_end(".ram_rodata"), HAL_MPU_READONLY, 0x0, FALSE},//Vector table+RAM code+RAM rodata
        {(uint32_t)__section_begin(".intvec") + VRAM_BASE, (uint32_t)__section_end(".ram_rodata") + VRAM_BASE, HAL_MPU_NO_ACCESS, 0x0, TRUE}, //Virtual memory
        {(uint32_t)__section_begin(".tcm_code"), (uint32_t)__section_begin(".tcm_rwdata"), HAL_MPU_READONLY, 0x0, FALSE},//TCM code+TCM rodata
        {(uint32_t)__section_begin("CSTACK"), (uint32_t)__section_begin("CSTACK") + 32, HAL_MPU_READONLY, 0x0, TRUE} //Stack end check for stack overflow
    };

#endif

    hal_mpu_config_t mpu_config = {
        /* PRIVDEFENA, HFNMIENA */
        TRUE, TRUE
    };

    region_number = (hal_mpu_region_t)(sizeof(region_information) / sizeof(region_information[0]));

    hal_mpu_init(&mpu_config);
    for (region = HAL_MPU_REGION_0; region < region_number; region++) {
        /* Updata region information to be configured */
        region_config.mpu_region_address = region_information[region].mpu_region_base_address;
        region_config.mpu_region_size = (hal_mpu_region_size_t) caculate_mpu_region_size(region_information[region].mpu_region_end_address - region_information[region].mpu_region_base_address);
        region_config.mpu_region_access_permission = region_information[region].mpu_region_access_permission;
        region_config.mpu_subregion_mask = region_information[region].mpu_subregion_mask;
        region_config.mpu_xn = region_information[region].mpu_xn;

        hal_mpu_region_configure(region, &region_config);
        hal_mpu_region_enable(region);
    }
    /* make sure unused regions are disabled */
    for (; region < HAL_MPU_REGION_MAX; region++) {
        hal_mpu_region_disable(region);
    }
    hal_mpu_enable();
}

/**
* @brief       This function use for check power on battery voltage and pre-charging battery.
* @param[in]   None.
* @return      None.
*/
/* Enable battery_management */
#ifdef MTK_SMART_BATTERY_ENABLE
static void check_battery_voltage(void)
{
    /* Check power on battery voltage and pre-charging battery sample code */
    hal_charger_init();
    while (1) {
        int32_t battery_voltage = 0;
        bool charger_status;

        hal_charger_meter_get_battery_voltage_sense(&battery_voltage);
        LOG_I(common, "Check battery_voltage = %d mV", battery_voltage);
        /* Check battery voltage  > SHUTDOWN_SYSTEM_VOLTAGE (3400mV)  + 100mV */
        if (battery_voltage >= SHUTDOWN_SYSTEM_VOLTAGE + 100) {
            break;
        } else {
            hal_charger_get_charger_detect_status(&charger_status);
            if (charger_status == true) {
                LOG_I(common, "SW charging battery_voltage = %d mV", battery_voltage);
                hal_charger_init();
                /* Setup pre-charging current. It depends on the battery specifications */
                hal_charger_set_charging_current(HAL_CHARGE_CURRENT_70_MA);
                hal_charger_enable(true);
                /* Reset watchdog timer */
                hal_charger_reset_watchdog_timer();
                hal_gpt_delay_ms(1 * 1000);
            } else {
                LOG_I(common, "Low battery power off !! battery_voltage = %d mV", battery_voltage);
                hal_sleep_manager_enter_power_off_mode();
            }

        }
    }

}
#endif

/**
* @brief       This function is to setup system hardware, such as increase system clock, uart init etc.
* @param[in]   None.
* @return      None.
*/
static void prvSetupHardware(void)
{
    /* system HW init */
    cache_init();
    mpu_init();

    /* peripherals init */
    hal_flash_init();
    hal_nvic_init();
    /* bsp_ept_gpio_setting_init() under driver/board/mt25x3_hdk/ept will initialize the GPIO settings
     * generated by easy pinmux tool (ept). ept_*.c and ept*.h are the ept files and will be used by
     * bsp_ept_gpio_setting_init() for GPIO pinumux setup.
     */
    bsp_ept_gpio_setting_init();
    hal_rtc_init();
    hal_dcxo_init();

    /* low power init */
    hal_sleep_manager_init();
/* Enable battery_management */
#ifdef MTK_SMART_BATTERY_ENABLE
    /* Check battery voltage */
    check_battery_voltage();
    battery_management_init();
#endif

    /* turn off MIPI TX analog power */
    hal_display_dsi_init(false);
    hal_display_dsi_deinit();
}

/**
* @brief       This function is to do system initialization, eg: system clock, hardware and logging port.
* @param[in]   None.
* @return      None.
*/
void system_init(void)
{
    /* config system clock */
    SystemClock_Config();
    SystemCoreClockUpdate();

    /* initialize UART2 as logging port */
    log_uart_init(HAL_UART_2);

    /* do infrastructure initialization */
    prvSetupHardware();

/* Enable NVDM feature */
#ifdef MTK_NVDM_ENABLE
    nvdm_init();
#endif

/* BT HCI log port */
#ifdef BLE_UART1_IO
    ble_io_uart_init(HAL_UART_1);
    xTaskCreate(ble_cmd_task, BLE_CMD_TASK_NAME, BLE_CMD_TASK_STACKSIZE/sizeof(StackType_t), NULL, BLE_CMD_TASK_PRIORITY, NULL);
#endif

}
