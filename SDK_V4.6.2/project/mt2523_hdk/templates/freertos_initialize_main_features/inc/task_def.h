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

#ifndef __TASK_DEF_H__
#define __TASK_DEF_H__

#include "FreeRTOSConfig.h"

typedef enum {
    TASK_PRIORITY_IDLE = 0,                                 /* lowest, special for idle task */
    TASK_PRIORITY_SYSLOG,                                   /* special for syslog task */

    /* User task priority begin, please define your task priority at this interval */
    TASK_PRIORITY_LOW,                                      /* low */
    TASK_PRIORITY_BELOW_NORMAL,                             /* below normal */
    TASK_PRIORITY_NORMAL,                                   /* normal */
    TASK_PRIORITY_ABOVE_NORMAL,                             /* above normal */
    TASK_PRIORITY_HIGH,                                     /* high */
    TASK_PRIORITY_SOFT_REALTIME,                            /* soft real time */
    TASK_PRIORITY_HARD_REALTIME,                            /* hard real time */
    /* User task priority end */

    /*Be careful, the max-priority number can not be bigger than configMAX_PRIORITIES - 1, or kernel will crash!!! */
    TASK_PRIORITY_TIMER = configMAX_PRIORITIES - 1,         /* highest, special for timer task to keep time accuracy */
} task_priority_type_t;

/*The following is an example to define the XXXX task.
#define XXXX_TASK_NAME "XXXX"
#define XXXX_TASK_STACKSIZE 512
#define XXXX_TASK_PRIO TASK_PRIORITY_LOW
#define XXXX_QUEUE_LENGTH  16
*/

/* part_1: SDK tasks configure infomation, please don't modify */
/* ctp task definition*/
#define BSP_CTP_TASK_NAME       "CTP"
#define BSP_CTP_TASK_STACKSIZE  (1024*4) /* unit byte!*/
#define BSP_CTP_TASK_PRIO       TASK_PRIORITY_SOFT_REALTIME
#define BSP_CTP_QUEUE_LENGTH    20


/* battery_management */
#define BMT_TASK_NAME "BMT"
#define BMT_TASK_STACKSIZE 4096
#define BMT_TASK_PRIO TASK_PRIORITY_ABOVE_NORMAL
#define BMT_QUEUE_LENGTH  1



/* for wpa supplicant task */
#define WPA_SUPPLICANT_TASK_NAME        "wpa_supplicant"
#define WPA_SUPPLICANT_TASK_STACKSIZE   (2048*4) /*unit byte!*/
#define WPA_SUPPLICANT_TASK_PRIO        TASK_PRIORITY_NORMAL

/* for hostapd task */
#define HOSTAPD_TASK_NAME        "hostpad"
#define HOSTAPD_TASK_STACKSIZE   (2048*4) /*unit byte!*/
#define HOSTAPD_TASK_PRIO        TASK_PRIORITY_NORMAL

/* for wndrv task */
#define WNDRV_TASK_NAME        "wndrv"
#define WNDRV_TASK_STACKSIZE   (2048*4) /*unit byte!*/
#define WNDRV_TASK_PRIO        TASK_PRIORITY_ABOVE_NORMAL

#define WLAN_START_TASK_NAME        "wlan start"
#define WLAN_START_TASK_STACKSIZE   (2048*4) /*unit byte!*/
#define WLAN_START_TASK_PRIO        TASK_PRIORITY_NORMAL

/*for wifi loopback task*/
#define WIFI_LB_TASK_NAME        "loopback"
#define WIFI_LB_TASK_STACKSIZE   (2048*4) /*unit byte!*/
#define WIFI_LB_TASK_PRIO        TASK_PRIORITY_HIGH
/* syslog task definition */
#define SYSLOG_TASK_NAME "SYSLOG"
/*This definition determines whether the port service feature is enabled. If it is not defined, then the port service feature is not supported.*/
#if defined(MTK_PORT_SERVICE_ENABLE)
#define SYSLOG_TASK_STACKSIZE 1024
#else
#define SYSLOG_TASK_STACKSIZE 192
#endif
#define SYSLOG_TASK_PRIO TASK_PRIORITY_SYSLOG
/*MTK_NO_PSRAM_ENABLE: the definition of MTK_NO_PSRAM_ENABLE determines whether the demo uses PSRAM. If it is defined, means no PSRAM in this project.*/
#if (PRODUCT_VERSION == 7687) || (PRODUCT_VERSION == 7697) || defined(MTK_NO_PSRAM_ENABLE)
#define SYSLOG_QUEUE_LENGTH 8
#elif (PRODUCT_VERSION == 2523)
#define SYSLOG_QUEUE_LENGTH 512
#endif

/* part_1: Application and customer tasks configure information */
/* currently, only UI task and tasks to show example project function which define in apps/project/src/main.c */

/* for Application task */

/* BT example task */
#define BT_EXAMPLE_TASK_NAME          "bt_task"
#define BT_EXAMPLE_TASK_STACKSIZE     1024
#define BT_EXAMPLE_TASK_PRIO          TASK_PRIORITY_LOW

#endif

