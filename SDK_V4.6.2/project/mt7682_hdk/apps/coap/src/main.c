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

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "sys_init.h"
#include "wifi_api.h"
#include "lwip/netif.h"
#include "lwip/tcpip.h"
#include "lwip/sockets.h"
#include "ethernetif.h"
#include "lwip/sockets.h"
#include "netif/etharp.h"
#include "portmacro.h"
#include "wifi_lwip_helper.h"
#include "task_def.h"
#include "syslog.h"

#define WIFI_SSID                ("SQA_TEST_AP")
#define WIFI_PASSWORD            ("77777777")

extern int coap_client();
extern int coap_server();

/**
  * Create the log control block for lwip socket example.
  * User needs to define their own log control blocks as project needs.
  * Please refer to the log dev guide under /doc folder for more details.
  */
log_create_module(coap_example, PRINT_LEVEL_INFO);

/**
  * @brief    server test entry
  * @param[in] void *not_used:Not used
  * @return    None
  */
static void server_test_thread(void *not_used)
{
    coap_server();
    //Keep the task alive
    while (1) {
        vTaskDelay(1000 / portTICK_RATE_MS); // release CPU
    }
}

/**
  * @brief     client test entry
  * @param[in] void *not_used:Not used
  * @return    None
  */
static void client_test_thread(void *not_used)
{
    vTaskDelay(1000 / portTICK_RATE_MS);
    coap_client();
    //Keep the task alive
    while (1) {
        vTaskDelay(1000 / portTICK_RATE_MS); // release CPU
    }
}

/**
  * @brief     Create a task for tcp/udp test
  * @param[in] void *args:Not used
  * @return    None
  */
static void user_entry(void *args)
{
    lwip_net_ready();
    LOG_I(coap_example, "Begin to create test_thread");
    //xTaskHandle xHandle;

    if (pdPASS != xTaskCreate(server_test_thread,
                              COAP_SERVER_EXAMPLE_TASK_NAME,
                              COAP_EXAMPLE_TASK_STACKSIZE / sizeof(portSTACK_TYPE),
                              NULL,
                              COAP_EXAMPLE_TASK_PRIO,
                              NULL)) {
        LOG_I(coap_example, "Cannot create server_test_thread");
    }

    if (pdPASS != xTaskCreate(client_test_thread,
                              COAP_CLINET_EXAMPLE_TASK_NAME,
                              COAP_EXAMPLE_TASK_STACKSIZE / sizeof(portSTACK_TYPE),
                              NULL,
                              COAP_EXAMPLE_TASK_PRIO,
                              NULL)) {
        LOG_I(coap_example, "Cannot create client_test_thread");
    }

    LOG_I(coap_example, "Finish to create test_thread");
    while (1) {
        vTaskDelay(1000 / portTICK_RATE_MS); // release CPU
    }
}

/**
  * @brief  Main program
  * @param  None
  * @retval int
  */
int main(void)
{
    /* Do system initialization, eg: hardware, nvdm, logging and random seed. */
    system_init();

    /* system log initialization.
        * This is the simplest way to initialize system log, that just inputs three NULLs
        * as input arguments. User can use advanved feature of system log along with NVDM.
        * For more details, please refer to the log dev guide under /doc folder or projects
        * under project/mtxxxx_hdk/apps/.
        */
    log_init(NULL, NULL, NULL);

    LOG_I(coap_example, "start to create task.");

    /* User initial the parameters for wifi initial process,  system will determin which wifi operation mode
        * will be started , and adopt which settings for the specific mode while wifi initial process is running
        */
    wifi_config_t config = {0};
    config.opmode = WIFI_MODE_STA_ONLY;
    strcpy((char *)config.sta_config.ssid, WIFI_SSID);
    strcpy((char *)config.sta_config.password, WIFI_PASSWORD);
    config.sta_config.ssid_length = strlen(WIFI_SSID);
    config.sta_config.password_length = strlen(WIFI_PASSWORD);

    /* Initialize wifi stack and register wifi init complete event handler,
        * notes:  the wifi initial process will be implemented and finished while system task scheduler is running.
        */
    wifi_init(&config, NULL);

    /* Tcpip stack and net interface initialization,  dhcp client, dhcp server process initialization. */
    lwip_network_init(config.opmode);
    lwip_net_start(config.opmode);


    /* Create a user task for demo when and how to use wifi config API  to change WiFI settings,
        * Most WiFi APIs must be called in task scheduler, the system will work wrong if called in main(),
        * For which API must be called in task, please refer to wifi_api.h or WiFi API reference.
        * xTaskCreate(user_wifi_app_entry,
        *       UNIFY_USR_DEMO_TASK_NAME,
        *       UNIFY_USR_DEMO_TASK_STACKSIZE / 4,
        *       NULL, UNIFY_USR_DEMO_TASK_PRIO, NULL);
        */
    if (pdPASS != xTaskCreate(user_entry,
                              USER_ENTRY_TASK_NAME,
                              USER_ENTRY_TASK_STACKSIZE / sizeof(portSTACK_TYPE),
                              NULL,
                              USER_ENTRY_TASK_PRIO,
                              NULL)) {
        LOG_E(coap_example, "create user task fail");
        return -1;
    }


    /* Call this function to indicate the system initialize done. */
    SysInitStatus_Set();

    /* Start the scheduler. */
    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following line
        * will never be reached.  If the following line does execute, then there was
        * insufficient FreeRTOS heap memory available for the idle and/or timer tasks
        * to be created.  See the memory management section on the FreeRTOS web site
        * for more details.
        */
    for ( ;; );
}
