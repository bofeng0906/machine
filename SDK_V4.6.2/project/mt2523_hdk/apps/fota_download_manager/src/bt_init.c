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
#include "FreeRTOS.h"
#include "task.h"
#include "nvdm.h"
#include "bt_system.h"
#include "hal_trng.h"
#include "syslog.h"

#include "project_config.h"
#include <string.h>
#include <stdlib.h>
#include "bt_gap.h"

#include "task_def.h"

extern bt_gap_config_t bt_custom_config;

#define BT_TIMER_BUF_SIZE (BT_TIMER_NUM * BT_CONTROL_BLOCK_SIZE_OF_TIMER)
#define BT_CONNECTION_BUF_SIZE (BT_CONNECTION_MAX* BT_CONTROL_BLOCK_SIZE_OF_EDR_CONNECTION)

BT_ALIGNMENT4(
static char timer_cb_buf[BT_TIMER_BUF_SIZE]//one timer control block is 20 bytes
);
BT_ALIGNMENT4(
static char le_connection_cb_buf[BT_LE_CONNECTION_BUF_SIZE]
);

BT_ALIGNMENT4(
static char bt_connection_cb_buf[BT_CONNECTION_BUF_SIZE]
);

BT_ALIGNMENT4(
static char tx_buf[BT_TX_BUF_SIZE]
);

BT_ALIGNMENT4(
static char rx_buf[BT_RX_BUF_SIZE]
);

BT_ALIGNMENT4(
static char bt_rfcomm_link_cb_buf[BT_RFCOMM_LINK_BUF_SIZE]
);
BT_ALIGNMENT4(
static char bt_hfp_link_cb_buf[BT_HFP_LINK_BUF_SIZE]
);
BT_ALIGNMENT4(
static char bt_avrcp_link_cb_buf[BT_AVRCP_LINK_BUF_SIZE]
);

BT_ALIGNMENT4(

static char bt_a2dp_sep_cb_buf[BT_A2DP_SEP_BUF_SIZE]
);

BT_ALIGNMENT4(
static char bt_a2dp_link_cb_buf[BT_A2DP_LINK_BUF_SIZE]
);

BT_ALIGNMENT4(
static char bt_spp_connection_cb_buf[BT_SPP_CONNECTION_BUF_SIZE]
);

BT_ALIGNMENT4(
static char bt_pbapc_connection_cb_buf[BT_PBAPC_CONNECTION_BUF_SIZE]
);

static bt_bd_addr_t local_public_addr;
// for fota to ble set random address, in order to auto reconnection.
bt_bd_addr_t local_ble_random_addr;

extern void bt_task(void * arg);

/**
 * @brief             Common function to print address
 * @param[in] addr    is the address of bluetooth
 * @return            None.
 */

static void bt_show_address(bt_bd_addr_t addr)
{
 
    LOG_I(common, "[BT addr] [%02X:%02X:%02X:%02X:%02X:%02X]\n", addr[0],
          addr[1], addr[2], addr[3], addr[4], addr[5]);
}

/**
 * @brief             Generate random address for bt static address
 * @param[in]         is the buff to save generated static address
 * @return            None.
 */
static void bt_preread_local_address(bt_bd_addr_t addr)
{
    nvdm_status_t status;
    int8_t i;
    uint32_t random_seed;
    uint32_t size = 12;
    uint8_t buffer[18] = {0};
    uint8_t tmp_buf[3] = {0};
    bt_bd_addr_t tempaddr = {0};
    hal_trng_status_t ret = HAL_TRNG_STATUS_ERROR;
    if (memcmp(addr, &tempaddr, sizeof(bt_bd_addr_t)) == 0) {
        LOG_I(common, "[BT]Empty bt address after bt_gap_le_get_local_address()\n");
        LOG_I(common, "[BT]Try to read from NVDM.\n");
        status = nvdm_read_data_item("BT", "address", buffer, &size);
        if (NVDM_STATUS_OK == status) {
            LOG_I(common, "[BT]Read from NVDM:%s\n", buffer);
            for (i = 0; i < 6; ++i) {
                tmp_buf[0] = buffer[2 * i];
                tmp_buf[1] = buffer[2 * i + 1];
                addr[i] = (uint8_t)strtoul((char *)tmp_buf, NULL, 16);
            }

            LOG_I(common, "[BT]Read address from NVDM"); 
            bt_show_address(addr);
            return;
        } else {
            LOG_I(common, "[BT]Failed to Read from NVDM:%d.\n", status);
            ret = hal_trng_init();
            if (HAL_TRNG_STATUS_OK != ret) {
                LOG_I(common, "[BT]generate_random_address--error 1");
            }
            for (i = 0; i < 30; ++i) {
                ret = hal_trng_get_generated_random_number(&random_seed);
                if (HAL_TRNG_STATUS_OK != ret) {
                    LOG_I(common, "[BT]generate_random_address--error 2");
                }
                LOG_I(common, "[BT]generate_random_address--trn: 0x%x", random_seed);
            }
            /* randomly generate address */
            ret = hal_trng_get_generated_random_number(&random_seed);
            if (HAL_TRNG_STATUS_OK != ret) {
                LOG_I(common, "[BT]generate_random_address--error 3");
            }
            LOG_I(common, "[BT]generate_random_address--trn: 0x%x", random_seed);
            addr[0] = random_seed & 0xFF;
            addr[1] = (random_seed >> 8) & 0xFF;
            addr[2] = (random_seed >> 16) & 0xFF;
            addr[3] = (random_seed >> 24) & 0xFF;
            ret = hal_trng_get_generated_random_number(&random_seed);
            if (HAL_TRNG_STATUS_OK != ret) {
                LOG_I(common, "[BT]generate_random_address--error 3");
            }
            LOG_I(common, "[BT]generate_random_address--trn: 0x%x", random_seed);
            addr[4] = random_seed & 0xFF;
            addr[5] = (random_seed >> 8) & 0xCF;
            hal_trng_deinit();
        }
    }
    /* save address to NVDM */
    for (i = 0; i < 6; ++i) {
        snprintf((char *)buffer + 2 * i, 3, "%02X", addr[i]);
    }
    LOG_I(common, "[BT]address to write:%s len:%d\n", buffer, strlen((char *)buffer));
    status = nvdm_write_data_item("BT", "address", NVDM_DATA_ITEM_TYPE_STRING, buffer, strlen((char *)buffer));
    if (NVDM_STATUS_OK != status) {
        LOG_I(common, "[BT]Failed to store address.\n");
    } else {
        LOG_I(common, "[BT]Successfully store address to NVDM");
        bt_show_address(addr);
    }
}


// FOTA set ble random address, to suport auto reconnection with smart device application.
static void bt_preread_ble_random_address(bt_bd_addr_t addr)
{
    nvdm_status_t status;
    int8_t i;
    uint32_t random_seed;
    uint32_t size = 12;
    uint8_t buffer[18] = {0};
    uint8_t tmp_buf[3] = {0};
    bt_bd_addr_t tempaddr = {0};
    hal_trng_status_t ret = HAL_TRNG_STATUS_ERROR;
    if (memcmp(addr, &tempaddr, sizeof(bt_bd_addr_t)) == 0) {
        LOG_I(common, "[BLE]Try to read from NVDM.\n");
        status = nvdm_read_data_item("BLE", "random_address", buffer, &size);
        if (NVDM_STATUS_OK == status) {
            LOG_I(common, "[BLE]Read from NVDM:%s\n", buffer);
            for (i = 0; i < 6; ++i) {
                tmp_buf[0] = buffer[2 * i];
                tmp_buf[1] = buffer[2 * i + 1];
                addr[i] = (uint8_t)strtoul((char *)tmp_buf, NULL, 16);
            }

            LOG_I(common, "[BLE]Read address from NVDM"); 
            bt_show_address(addr);
            return;
        } else {
            LOG_I(common, "[BLE]Failed to Read from NVDM:%d.\n", status);
            ret = hal_trng_init();
            if (HAL_TRNG_STATUS_OK != ret) {
                LOG_I(common, "[BLE]generate_random_address--error 1");
            }
            for (i = 0; i < 30; ++i) {
                ret = hal_trng_get_generated_random_number(&random_seed);
                if (HAL_TRNG_STATUS_OK != ret) {
                    LOG_I(common, "[BLE]generate_random_address--error 2");
                }
                LOG_I(common, "[BLE]generate_random_address--trn: 0x%x", random_seed);
            }
            /* randomly generate address */
            ret = hal_trng_get_generated_random_number(&random_seed);
            if (HAL_TRNG_STATUS_OK != ret) {
                LOG_I(common, "[BLE]generate_random_address--error 3");
            }
            LOG_I(common, "[BLE]generate_random_address--trn: 0x%x", random_seed);
            addr[0] = random_seed & 0xFF;
            addr[1] = (random_seed >> 8) & 0xFF;
            addr[2] = (random_seed >> 16) & 0xFF;
            addr[3] = (random_seed >> 24) & 0xFF;
            ret = hal_trng_get_generated_random_number(&random_seed);
            if (HAL_TRNG_STATUS_OK != ret) {
                LOG_I(common, "[BLE]generate_random_address--error 3");
            }
            LOG_I(common, "[BLE]generate_random_address--trn: 0x%x", random_seed);
            addr[4] = random_seed & 0xFF;
            addr[5] = (random_seed >> 8) & 0xCF;
            hal_trng_deinit();
        }
    }
    /* save address to NVDM */
    for (i = 0; i < 6; ++i) {
        snprintf((char *)buffer + 2 * i, 3, "%02X", addr[i]);
    }
    LOG_I(common, "[BLE]address to write:%s len:%d\n", buffer, strlen((char *)buffer));
    status = nvdm_write_data_item("BLE", "random_address", NVDM_DATA_ITEM_TYPE_STRING, buffer, strlen((char *)buffer));
    if (NVDM_STATUS_OK != status) {
        LOG_I(common, "[BLE]Failed to store address.\n");
    } else {
        LOG_I(common, "[BLE]Successfully store address to NVDM");
        bt_show_address(addr);
    }
}




/**
 * @brief     This function is prepare all fix memory for BT SDK use.
 * @return    None.
 */
static void bt_mm_init()
{
    bt_memory_init_packet(BT_MEMORY_TX_BUFFER, tx_buf, BT_TX_BUF_SIZE);
    bt_memory_init_packet(BT_MEMORY_RX_BUFFER, rx_buf, BT_RX_BUF_SIZE);
    bt_memory_init_control_block(BT_MEMORY_CONTROL_BLOCK_TIMER, timer_cb_buf, BT_TIMER_BUF_SIZE);
    bt_memory_init_control_block(BT_MEMORY_CONTROL_BLOCK_LE_CONNECTION, le_connection_cb_buf, BT_LE_CONNECTION_BUF_SIZE);
    bt_memory_init_control_block(BT_MEMORY_CONTROL_BLOCK_EDR_CONNECTION, bt_connection_cb_buf, BT_CONNECTION_BUF_SIZE);
    bt_memory_init_control_block(BT_MEMORY_CONTROL_BLOCK_RFCOMM, bt_rfcomm_link_cb_buf, BT_RFCOMM_LINK_BUF_SIZE);
    bt_memory_init_control_block(BT_MEMORY_CONTROL_BLOCK_HFP, bt_hfp_link_cb_buf, BT_HFP_LINK_BUF_SIZE);
    bt_memory_init_control_block(BT_MEMORY_CONTROL_BLOCK_AVRCP, 
                       bt_avrcp_link_cb_buf, BT_AVRCP_LINK_BUF_SIZE);
    bt_memory_init_control_block(BT_MEMORY_CONTROL_BLOCK_A2DP_SEP, bt_a2dp_sep_cb_buf, BT_A2DP_SEP_BUF_SIZE);
    bt_memory_init_control_block(BT_MEMORY_CONTROL_BLOCK_A2DP, bt_a2dp_link_cb_buf, BT_A2DP_LINK_BUF_SIZE);
    bt_memory_init_control_block(BT_MEMORY_CONTROL_BLOCK_SPP, bt_spp_connection_cb_buf, BT_SPP_CONNECTION_BUF_SIZE);
    bt_memory_init_control_block(BT_MEMORY_CONTROL_BLOCK_PBAPC, bt_pbapc_connection_cb_buf, BT_PBAPC_CONNECTION_BUF_SIZE);

}

/**
 * @brief     This function is to config BT SDK fix memory and create task for BT SDK.
 * @return    None.
 */
void bt_create_task(void)
{
    bt_mm_init();
    /* bt address should send to BT SDK when create BT task */
    bt_preread_local_address(local_public_addr);
    sprintf(bt_custom_config.device_name, "Duo_%02x%02x%02x%02x%02x%02x",
        local_public_addr[5],
        local_public_addr[4],
        local_public_addr[3],
        local_public_addr[2],
        local_public_addr[1],
        local_public_addr[0]
    );
    bt_show_address(local_public_addr);
    
    bt_preread_ble_random_address(local_ble_random_addr);
    bt_show_address(local_ble_random_addr);
    
        
    LOG_I(common, "local_public_addr: 0x%x\r\n", local_public_addr);
    /* create task for BT SDK use */
    if (pdPASS != xTaskCreate(bt_task, BT_TASK_NAME, BT_TASK_STACKSIZE/sizeof(StackType_t), (void *)local_public_addr, BT_TASK_PRIORITY, NULL)) {
        LOG_E(common, "cannot create bt_task.");
    }
}

