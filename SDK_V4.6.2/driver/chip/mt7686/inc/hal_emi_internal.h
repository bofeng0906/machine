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

#ifndef HAL_EMI_INTERNAL_H
#define HAL_EMI_INTERNAL_H

#include <memory_attribute.h>

typedef enum emi_clock_enum_t
{
    EMI_CLK_LOW_TO_HIGH = 0,
    EMI_CLK_HIGH_TO_LOW  = 1,
} emi_clock;

typedef struct {
    uint32_t EMI_RDCT_VAL;
    uint32_t EMI_DSRAM_VAL;
    uint32_t EMI_MSRAM0_VAL;
	uint32_t EMI_MSRAM1_VAL;
    uint32_t EMI_IDL_C_VAL;
    uint32_t EMI_IDL_D_VAL;
    uint32_t EMI_IDL_E_VAL;
    uint32_t EMI_ODL_C_VAL;
    uint32_t EMI_ODL_D_VAL;
    uint32_t EMI_ODL_E_VAL;
    uint32_t EMI_ODL_F_VAL;
    uint32_t EMI_IO_A_VAL;
    uint32_t EMI_IO_B_VAL;

} EMI_SETTINGS;


typedef enum{
    FILTER_LENGTH_521T = 0,
	FILTER_LENGTH_1024T = 1,
	FILTER_LENGTH_2048T = 2,
	FILTER_LENGTH_4096T = 3,
}bandwidth_filter_length_t;



ATTR_TEXT_IN_TCM int32_t EMI_DynamicClockSwitch(emi_clock clock);
ATTR_TEXT_IN_TCM void mtk_psram_half_sleep_enter(void);
ATTR_TEXT_IN_TCM void mtk_psram_half_sleep_exit(void);
ATTR_TEXT_IN_TCM void EMI_Setting_restore(void);
ATTR_TEXT_IN_TCM void EMI_Setting_Save(void);
ATTR_TEXT_IN_TCM int8_t custom_setEMI(void);
ATTR_TEXT_IN_TCM int8_t custom_setAdvEMI(void);
ATTR_TEXT_IN_TCM void emi_mask_master(void);
ATTR_TEXT_IN_TCM void emi_unmask_master(void);


ATTR_TEXT_IN_TCM uint32_t __EMI_GetSR(uint32_t bank_no);
ATTR_TEXT_IN_TCM void __EMI_SetSR(uint32_t bank_no, uint32_t value);


#endif
