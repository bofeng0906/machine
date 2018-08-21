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

#ifndef __BT_SINK_SRV_AVRCP_H__
#define __BT_SINK_SRV_AVRCP_H__

#include "stdint.h"
#include "bt_sink_srv_conmgr.h"
#include "bt_avrcp.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    BT_SINK_SRV_AVRCP_DISCONNECTED,
    BT_SINK_SRV_AVRCP_CONNECTING,
    BT_SINK_SRV_AVRCP_CONNECTED,
    BT_SINK_SRV_AVRCP_PLAY,
    BT_SINK_SRV_AVRCP_STOP,

    BT_SINK_SRV_AVRCP_TOTAL
} bt_sink_srv_avrcp_state_t;

typedef enum {
    BT_SINK_SRV_AVRCP_EVENT_CONNECT,
    BT_SINK_SRV_AVRCP_EVENT_DISCONNECT,

    /* add before this event */
    BT_SINK_SRV_AVRCP_EVENT_ALL
} bt_sink_srv_avrcp_event_type_t;

typedef struct {
    bt_sink_srv_avrcp_event_type_t event;
    void *param;
} bt_sink_srv_avrcp_event_t;

typedef struct {
    int32_t ret;
    bool ind;
    uint32_t handle;
    bt_bd_addr_t dev_addr;
} bt_sink_srv_avrcp_connect_t;

typedef struct {
    int32_t ret;
    bool ind;
    uint32_t handle;
    bt_bd_addr_t dev_addr;
} bt_sink_srv_avrcp_disconnect_t;

typedef enum {
    BT_SINK_SRV_PARTYMODE_INTERRUPT,            /**< partymode barge in */
    BT_SINK_SRV_PARTYMODE_DROP,
    BT_SINK_SRV_PARTYMODE_TOTAL
} bt_sink_srv_partymode_t;

bt_sink_srv_status_t bt_sink_srv_avrcp_action_handler(bt_sink_srv_action_t action, void *param);

int32_t bt_sink_srv_avrcp_play_music(uint32_t handle);

int32_t bt_sink_srv_avrcp_stop_music(uint32_t handle);

int32_t bt_sink_srv_avrcp_change_ntrack(uint32_t handle);

int32_t bt_sink_srv_avrcp_change_ptrack(uint32_t handle);

bt_status_t bt_sink_srv_avrcp_common_callback(bt_msg_type_t msg, bt_status_t status, void *buffer);

bt_sink_srv_status_t bt_sink_srv_music_avrcp_action_handler(bt_sink_srv_action_t action, void *param);

uint8_t bt_sink_srv_avrcp_get_volume_value(uint8_t vol_level);
uint8_t bt_sink_srv_avrcp_get_volume_level(uint8_t volume);
bt_status_t bt_sink_srv_avrcp_volume_notification(uint32_t handle, uint8_t vol_level);
#ifdef __cplusplus
}
#endif

#endif
