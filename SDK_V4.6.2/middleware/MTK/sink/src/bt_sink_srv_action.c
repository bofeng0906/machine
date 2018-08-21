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

#include "bt_gap.h"
#include "bt_sink_srv.h"
#include "bt_sink_srv_action.h"
#include "bt_sink_srv_conmgr.h"
#include "bt_sink_srv_hf.h"
#include "bt_sink_srv_avrcp.h"
#include "bt_sink_srv_a2dp.h"
#include "bt_sink_srv_pbapc.h"
#include "bt_sink_srv_spp.h"
#include "bt_sink_srv_utils.h"
#include "bt_sink_srv_action.h"
#include "bt_sink_srv_aws.h"
#include "bt_sink_srv_ami.h"
#include "bt_sink_srv_aws_a2dp.h"


const static bt_sink_srv_action_callback_table_t bt_sink_srv_action_callback_table[] = {
    {BT_SINK_SRV_ACTION_ALL, bt_sink_srv_cm_action_handler},
    {BT_SINK_SRV_ACTION_ALL, bt_sink_srv_hf_action_handler},
    {BT_SINK_SRV_ACTION_ALL, bt_sink_srv_music_a2dp_action_handler},
    {BT_SINK_SRV_ACTION_ALL, bt_sink_srv_music_avrcp_action_handler},
    {BT_SINK_SRV_ACTION_ALL, bt_sink_srv_pbapc_action_handler},
    #ifdef __BT_AWS_SUPPORT__
    {BT_SINK_SRV_ACTION_ALL, bt_sink_srv_aws_action_handler},
    {BT_SINK_SRV_ACTION_ALL, bt_sink_srv_music_aws_a2dp_action_handler},
    #endif
    {BT_SINK_SRV_ACTION_ALL, bt_sink_srv_spp_action_handler}
};

bt_sink_srv_status_t bt_sink_srv_action_send(bt_sink_srv_action_t action, void *parameters)
{
    bt_sink_srv_status_t result = BT_SINK_SRV_STATUS_SUCCESS;
    uint32_t index;

    bt_sink_srv_report("[Sink] bt_sink_srv_action_send, 0x%x", action);

    for (index = 0; index < sizeof(bt_sink_srv_action_callback_table) / sizeof(bt_sink_srv_action_callback_table_t); index++) {
        if (bt_sink_srv_action_callback_table[index].action == BT_SINK_SRV_ACTION_ALL) {
            if (NULL != bt_sink_srv_action_callback_table[index].callback) {
                result = bt_sink_srv_action_callback_table[index].callback(action, parameters);
                if (BT_SINK_SRV_STATUS_EVENT_STOP == result) {
                    // TRACE
                    break;
                }
            } else {
                // TRACE
            }
        } else if (bt_sink_srv_action_callback_table[index].action == action) {
            result = bt_sink_srv_action_callback_table[index].callback(action, parameters);
            if (BT_SINK_SRV_STATUS_EVENT_STOP == result) {
                // TRACE
                break;
            }
        } else {
            // TRACE
        }
    }
    return result;
}

