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

#include "bt_sink_srv.h"
#include "bt_sink_srv_utils.h"
#include "bt_sink_srv_state_notify.h"

static bt_sink_srv_state_t bt_sink_srv_state = BT_SINK_SRV_STATE_NONE;
static bt_sink_srv_state_flags_t bt_sink_srv_state_flag = BT_SINK_SRV_STATE_FLAG_NONE;

static void bt_sink_srv_state_change_notify(bt_sink_srv_state_t previous, bt_sink_srv_state_t now)
{
    bt_sink_srv_event_param_t *params = bt_sink_srv_memory_alloc(sizeof(*params));

    params->state_change.previous = previous;
    params->state_change.now = now;

    bt_sink_srv_event_callback(BT_SINK_SRV_EVENT_STATE_CHANGE, params);
    bt_sink_srv_memory_free(params);
}

void bt_sink_srv_state_set(bt_sink_srv_state_t state)
{
    if (BT_SINK_SRV_STATE_CONNECTED == state) {
        bt_sink_srv_state_flag |=  BT_SINK_SRV_STATE_FLAG_CONNECTED;
    } else if (BT_SINK_SRV_STATE_POWER_ON == state ||BT_SINK_SRV_STATE_NONE == state ) {
        bt_sink_srv_state_flag &= ~BT_SINK_SRV_STATE_FLAG_CONNECTED;
    }
    bt_sink_srv_report("[Sink][State] set prev:0x%x, next:0x%x", bt_sink_srv_state, state);

    /*local player is playing then stop immediately for call interrupt mp3 case .*/
    if ( state == BT_SINK_SRV_STATE_LOCAL_PLAYING ) {
        if (bt_sink_srv_state >= BT_SINK_SRV_STATE_INCOMING && bt_sink_srv_state <= BT_SINK_SRV_STATE_MULTIPARTY) {
            return;
        }
    }

    if (bt_sink_srv_state !=state) {
        bt_sink_srv_state_change_notify(bt_sink_srv_state, state);
        /*Special case for connected when local player is playing*/
        if ((state == BT_SINK_SRV_STATE_CONNECTED || state == BT_SINK_SRV_STATE_POWER_ON ) && 
            bt_sink_srv_state == BT_SINK_SRV_STATE_LOCAL_PLAYING ) {
             bt_sink_srv_state_change_notify(state, bt_sink_srv_state);
             state = BT_SINK_SRV_STATE_LOCAL_PLAYING;
        }
        bt_sink_srv_state = state;
    }
}

void bt_sink_srv_state_reset(bt_sink_srv_state_t state)
{
    bt_sink_srv_report("[Sink][State] reset prev:0x%x, next:0x%x", bt_sink_srv_state, state);

   if (state == BT_SINK_SRV_STATE_STREAMING  || state == BT_SINK_SRV_STATE_LOCAL_PLAYING) {
        if (bt_sink_srv_state >= BT_SINK_SRV_STATE_INCOMING && bt_sink_srv_state <= BT_SINK_SRV_STATE_MULTIPARTY) {
            return;
        }
        if (bt_sink_srv_state_flag & BT_SINK_SRV_STATE_FLAG_CONNECTED) {
            state = BT_SINK_SRV_STATE_CONNECTED;
        } else {
            state = BT_SINK_SRV_STATE_POWER_ON;
        }
   }
    if (bt_sink_srv_state !=state) {
        bt_sink_srv_state_change_notify(bt_sink_srv_state, state);
        bt_sink_srv_state = state;
    }
    bt_sink_srv_report("[Sink][State] final :0x%x", bt_sink_srv_state);
}

bt_sink_srv_state_t bt_sink_srv_state_query(void)
{
    return bt_sink_srv_state;
}

