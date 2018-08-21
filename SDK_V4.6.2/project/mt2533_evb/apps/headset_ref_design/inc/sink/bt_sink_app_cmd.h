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

#ifndef BT_SINK_APP_CMD_H
#define BT_SINK_APP_CMD_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    BT_SINK_APP_CMD_RESULT_SUCCESS = 0,
    BT_SINK_APP_CMD_RESULT_UNKNOWN,
    BT_SINK_APP_CMD_RESULT_INVALID_FORMAT,
    BT_SINK_APP_CMD_RESULT_INVALID_KEY,
    BT_SINK_APP_CMD_RESULT_INVALID_ACT,
    BT_SINK_APP_CMD_RESULT_NO_MAPPING,
    BT_SINK_APP_CMD_RESULT_LINK_NOT_EXIST
} bt_sink_app_cmd_result_t;

typedef enum {
    BT_SINK_APP_IND_TYPE_NONE,
    BT_SINK_APP_IND_TYPE_STATE,
    BT_SINK_APP_IND_TYPE_CALLER,
    BT_SINK_APP_IND_TYPE_MISSED_CALL,
    BT_SINK_APP_IND_TYPE_LINK_LOST,
    BT_SINK_APP_IND_TYPE_VISIBILITY,
    BT_SINK_APP_IND_TYPE_PROFILE_CONN_STATE,
    BT_SINK_APP_IND_TYPE_HF_SCO_STATE,
    BT_SINK_APP_INT_TYPE_NOTI_NEW,
    BT_SINK_APP_IND_TYPE_NOTI_MISSED_CALL,
    BT_SINK_APP_INT_TYPE_NOTI_SMS
} bt_sink_app_indicate_type_t;

void bt_sink_app_atci_init(void);

void bt_sink_app_atci_indicate(bt_sink_app_indicate_type_t type, uint32_t params);

#endif /* BT_SINK_APP_CMD_H */

