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

#ifdef __cplusplus
extern "C" {
#endif

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

/* part_1: SDK tasks configure infomation, please don't modify */

/* example only */
/* if module is lib release, please remind: these tasks are lib release, if changed task configure info, please remember to update library !!!*/
/* for xxxx task */
/*
#define XXXX_TASK_NAME "XXXX"
#define XXXX_TASK_STACKSIZE 512
#define XXXX_TASK_PRIO TASK_PRIORITY_LOW
#define XXXX_QUEUE_LENGTH  16
*/

/* battery_management */
#define BMT_TASK_NAME "BMT"
#define BMT_TASK_STACKSIZE 4096
#define BMT_TASK_PRIO TASK_PRIORITY_ABOVE_NORMAL
#define BMT_QUEUE_LENGTH  1


/* syslog task definition */
#define SYSLOG_TASK_NAME "SYSLOG"
#if defined(MTK_PORT_SERVICE_ENABLE)
#define SYSLOG_TASK_STACKSIZE 1024
#else
#define SYSLOG_TASK_STACKSIZE 192
#endif
#define SYSLOG_TASK_PRIO TASK_PRIORITY_SYSLOG
#if (PRODUCT_VERSION == 7687) || (PRODUCT_VERSION == 7697) || defined(MTK_NO_PSRAM_ENABLE)
#define SYSLOG_QUEUE_LENGTH 8
#elif (PRODUCT_VERSION == 2523)
#define SYSLOG_QUEUE_LENGTH 512
#endif

/* ATCI task definition */
#define ATCI_TASK_NAME              "ATCI"
#ifdef MTK_AUDIO_TUNING_ENABLED
#define ATCI_TASK_STACKSIZE         (5000*4) /*unit byte!*/
#else
#define ATCI_TASK_STACKSIZE         (1024*4) /*unit byte!*/
#endif
#define ATCI_TASK_PRIO              TASK_PRIORITY_NORMAL

/* Sensor task definition */
#define SENSOR_MGR_TASK_NAME "SensorMgr"
#define SENSOR_MGR_STACKSIZE 2048 /* unit byte!*/
#define SENSOR_MGR_TASK_PRIO TASK_PRIORITY_SOFT_REALTIME

#define SENSOR_FUSION_TASK_NAME "SensorFusion"
#define SENSOR_FUSION_STACKSIZE 6144 /* unit byte!*/
#define SENSOR_FUSION_TASK_PRIO TASK_PRIORITY_NORMAL

/* atci keypad task*/
#define ATCI_KEYPAD_TASK_NAME "KEYPAD_atci"
#define ATCI_KEYPAD_TASK_STACKSIZE (512*4) /* unit byte!*/
#define ATCI_KEYPAD_TASK_PRIO TASK_PRIORITY_NORMAL
#define ATCI_KEYPAD_QUEUE_LENGTH  100

/* ATCI MSDC task definition */
#define ATCI_MSDC_TASK_NAME              "MSDC_atci"
#define ATCI_MSDC_TASK_STACKSIZE         (200*4) /*unit byte!*/
#define ATCI_MSDC_TASK_PRIO              TASK_PRIORITY_NORMAL

/* ATCI BIO_UI task definition */
#define ATCI_BIO_TASK_NAME              "BIO_atci"
#define ATCI_BIO_TASK_STACKSIZE         4096 /*unit byte!*/
#define ATCI_BIO_TASK_PRIO              TASK_PRIORITY_NORMAL

/* ATCI  task definition */
#define ATCI_BIO_SMT_TASK_NAME              "BIO_SMT_atci"
#define ATCI_BIO_SMT_TASK_STACKSIZE         4096 /*unit byte!*/
#define ATCI_BIO_SMT_TASK_PRIO              TASK_PRIORITY_NORMAL

/* ctp task definition*/
#define BSP_CTP_TASK_NAME       "CTP"
#define BSP_CTP_TASK_STACKSIZE  (1024*4) /* unit byte!*/
#define BSP_CTP_TASK_PRIO       TASK_PRIORITY_SOFT_REALTIME
#define BSP_CTP_QUEUE_LENGTH    20

/* part_2: Application and customer tasks configure information */
/* currently, only UI task and tasks to show example project function which define in apps/project/src/main.c */

/* watch face task definition */
#define WF_APP_TASK_NAME            "wf_task"
#define WF_APP_TASK_STACKSIZE       1024
#define WF_APP_TASK_PRIO            TASK_PRIORITY_NORMAL



/* demo ui task definition */
#define DEMO_UI_TASK_NAME "UI_DEMO"
#define DEMO_UI_TASK_STACK_SIZE 4800
#define DEMO_UI_TASK_PRIO TASK_PRIORITY_NORMAL

/* gnss task definition */
#define GNSS_DEMO_TASK_NAME "gnss_t"
#define GNSS_DEMO_TASK_STACK_SIZE 2500
#define GNSS_DEMO_TASK_PRIO TASK_PRIORITY_HIGH

/* SPPS_ATCI task definition */
#define SPPS_ATCI_TASK_NAME "spps_atci_task"
#define SPPS_ATCI_TASK_STACK_SIZE (2048*4)
#define SPPS_ATCI_TASK_PRIO TASK_PRIORITY_NORMAL

/* keypad task definition */
#define KEYPAD_TASK_NAME "KEYPAD"
#define KEYPAD_TASK_STACK_SIZE 2048
#define KEYPAD_TASK_PRIO TASK_PRIORITY_NORMAL

/* lcd manager task definition */
#define LCDMGR_TASK_NAME "LCDMgr"
#define LCDMGR_TASK_STACK_SIZE 4096
#define LCDMGR_TASK_PRIO TASK_PRIORITY_NORMAL

/* app manager task definition */
#define APPMGR_TASK_NAME "appMgr"
#define APPMGR_TASK_STACK_SIZE 4096
#define APPMGR_TASK_PRIO TASK_PRIORITY_ABOVE_NORMAL

/* app statusbar task definition */
#define APP_STATUSBAR_TASK_NAME "appStatusBar"
#define APP_STATUSBAR_TASK_STACK_SIZE 4096
#define APP_STATUSBAR_TASK_PRIO TASK_PRIORITY_ABOVE_NORMAL

/* app key proc task definition */
#define APP_KEYPROC_TASK_NAME "appKeyProc"
#define APP_KEYPROC_TASK_STACK_SIZE (280 * 4)
#define APP_KEYPROC_TASK_PRIO TASK_PRIORITY_LOW

/* mode task definition */
#define MODE_TASK_NAME "modeTask"
#define MODE_TASK_STACK_SIZE (280 * 4)
#define MODE_TASK_PRIO TASK_PRIORITY_LOW

/* UI main task definition */
#define UI_MAIN_TASK_NAME "UI_MAIN"
#define UI_MAIN_TASK_STACK_SIZE 4096
#define UI_MAIN_TASK_PRIO TASK_PRIORITY_NORMAL

#ifdef GT_PROJECT_ENABLE
/* APP main task definition */
#define APP_MAIN_TASK_NAME "vGTMain"
#define APP_MAIN_TASK_STACK_SIZE 4096
#define APP_MAIN_TASK_PRIO TASK_PRIORITY_BELOW_NORMAL
#endif

#ifdef MTK_USB_DEMO_ENABLED
/* USB */
#define USB_TASK_NAME "USB"
#define USB_TASK_STACKSIZE 4096
#define USB_TASK_PRIO TASK_PRIORITY_HIGH
#define USB_QUEUE_LENGTH  500
#endif


// #define MTK_MINICLI_ENABLE
/*****************************************************************************
 * API Functions
 *****************************************************************************/

void task_def_init(void);

void task_def_create(void);

void task_def_delete_wo_curr_task(void);
#ifdef __cplusplus
}
#endif

#endif /* __TASK_DEF_H__ */
