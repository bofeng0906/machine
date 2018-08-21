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

#include "bsp_lcd.h"

//#define SERIAL_LCM_3WIRE_2_DATA_LANE
//#define SERIAL_LCM_3WIRE_1_DATA_LANE
#define SERIAL_LCM_4WIRE_1_DATA_LANE


#if (defined(SERIAL_LCM_3WIRE_2_DATA_LANE))
#define SERIAL_LCM_2_DATA_LINE_PROTOCOL
#endif

#define MAIN_LCD_8BIT_MODE  
#define MAIN_LCD_8BIT_MODE_RGB565

#define MAIN_LCD_CMD_ADDR		LCD_SERIAL0_A0_LOW_ADDR
#define MAIN_LCD_DATA_ADDR		LCD_SERIAL0_A0_HIGH_ADDR

#if (defined(MAIN_LCD_8BIT_MODE_RGB444))
#define MAIN_LCD_OUTPUT_FORMAT	LCM_8BIT_12_BPP_RGB444_1
#elif (defined(MAIN_LCD_8BIT_MODE_RGB565))
#define MAIN_LCD_OUTPUT_FORMAT	LCM_8BIT_16_BPP_RGB565_1
#elif (defined(MAIN_LCD_8BIT_MODE_RGB666))
#define MAIN_LCD_OUTPUT_FORMAT	LCM_8BIT_18_BPP_RGB666_1
#elif (defined(MAIN_LCD_16BIT_MODE_RGB444))
#define MAIN_LCD_OUTPUT_FORMAT	LCM_16BIT_12_BPP_RGB444_3
#elif (defined(MAIN_LCD_16BIT_MODE_RGB565))
#define MAIN_LCD_OUTPUT_FORMAT	LCM_16BIT_16_BPP_RGB565_1
#elif (defined(MAIN_LCD_16BIT_MODE_RGB666))
#define MAIN_LCD_OUTPUT_FORMAT	LCM_16BIT_18_BPP_RGB666_3
#elif (defined(MAIN_LCD_16BIT_MODE_RGB888))
#define MAIN_LCD_OUTPUT_FORMAT	LCM_16BIT_24_BPP_RGB888_1
#elif (defined(MAIN_LCD_18BIT_MODE_RGB666))
#define MAIN_LCD_OUTPUT_FORMAT LCM_18BIT_18_BPP_RGB666_1
#else
#error please check LCD TestCase define_error!!! 
#endif
/***********************ST7789S********************************/
/*Himax, Color LCD, Serial Interface,*/

extern LCD_Funcs LCD_func_SH1107;

