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

#ifndef __CMUX_PROT_H__
#define __CMUX_PROT_H__

#include "cmux_porting.h"
#include "cmux_def.h"

#define CMUX_FLAG_BASIC 0xF9
#define GET_DLCI_OF_ADDR(addr)  ((addr) >> 2)
#define GET_CR_OF_ADDR(addr) (((addr) &0x02)>>1)
#define GET_EA_OF_ADDR(addr) ((addr) &0x01)
#define CONSTRUCT_ADDRESS(dlci,cr,ea)  (((dlci)<<2)| ((cr)<<1) |(ea))
#define CONSTRUCT_LENGTH_1(length)  (1 | (length) << 1)
#define CONSTRUCT_LENGTH_1_of_2(length)  (0 | (length) << 1)
#define CONSTRUCT_LENGTH_2_of_2(length)  ( (length) >>7)

#define IS_SINGLE_LENGTH_OCTET(len)  (((len)&1)!=0)
#define LENGTH_TWO_OCTET(len1,len2)  ( ((len2) << 7) | ((len1) >>1 ))
#define LENGTH_ONE_OCTET(len)  ((len) >>1)

#define CR_UE_COMMAND    0
#define CR_UE_RESPONSE   1
#define CR_TE_COMMAND    1
#define CR_TE_RESPONSE   0

#define MAX_CTRL_FRAME_SIZE 6
#define INVALID_LENGTH_PATTERN 0xFFFF
#define MAX_ONE_BYTE_LENGTH  0x7F

#define CMUX_V24_EA_BIT     0x01
#define CMUX_V24_FC_BIT     0x02
#define CMUX_V24_RTC_BIT    0x04
#define CMUX_V24_RTR_BIT    0x08
#define CMUX_V24_IC_BIT     0x40
#define CMUX_V24_DV_BIT     0x80
#define CMUX_V24_BIT_ISON(b,bit)    (((b) & (bit))!=0)
#define CMUX_V24_BIT_ISOFF(b,bit)   (((b) & (bit))==0)

#define CMUX_INITIAL_FCS 0xFF
#define CMUX_CALCULATE_FCS(fcs,byte) cmux_crctable[(fcs) ^ (byte)]
#define CMUX_IS_FCS_CORRECT(fcs,recFcs)  ((cmux_crctable[(fcs) ^ (recFcs)] \
                                           ==0xCF)? KAL_TRUE : KAL_FALSE)
#define CMUX_OUTPUT_FCS(fcs)  (0xFF -(fcs))

extern const unsigned char cmux_crctable[];

extern void cmux_processUartData(kal_uint8 *pU1Buff, kal_uint32 u4Length);
extern void cmux_sendCtrlFrame(kal_uint32 dlci, CmuxControlByteE frameType);
extern void cmux_scheduleWrite(void);
extern void cmux_closeDownProcedure(void);
extern void cmux_sendSabmProcedure(cmux_channel_id_t channel_id);
extern void cmux_restoreTask( void );

extern void cmux_protocol_decodeV24( CmuxDlcT *pDlc, kal_uint8 signal );
extern kal_uint8 cmux_protocol_encodeV24( CmuxDlcT *pDlc );

extern void cmux_suspendPeerDlc(kal_uint32 dlci);
extern void cmux_resumePeerDlc(kal_uint32 dlci);
#ifdef __CMUX_MODEM_STATUS_SUPPORT__
extern void cmux_sendDlcMscStatus(kal_uint32 dlci);
#endif

#endif /* __CMUX_PROT_H__ */

