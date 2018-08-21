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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mt25x3_hdk_lcd.h"
#include "hal_display_dsi_internal.h"
#include "hal_gpt.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HEIGHT 400
#define WIDTH 400

extern volatile LCD_REGISTER_T *lcd_register_ptr;
extern volatile LCD_DSI_REGISTER_T *lcd_dsi_register_ptr;

static lcm_config_para_t RM69080_para = {
    .type = LCM_INTERFACE_TYPE_DSI,
    .backlight_type = BACKLIGHT_TYPE_LCM_BRIGHTNESS,
    .main_command_address = LCD_SERIAL0_A0_LOW_ADDR,
    .main_data_address = LCD_SERIAL0_A0_HIGH_ADDR,
    .main_lcd_output = LCM_8BIT_24_BPP_RGB888_1,
    .output_pixel_width = 24,
#ifdef MTK_TE_ENABLE
    .te_enable = true,
#endif
};

void LCD_Init_Interface_RM69080(void)
{
    hal_display_dsi_dphy_timing_struct_t	timing;

    timing.da_hs_trail = 0x05;
    timing.da_hs_zero = 0x08;
    timing.da_hs_prep = 0x02;
    timing.lpx = 0x03;
    timing.da_hs_exit = 0x0C;
    timing.ta_get = 0x10;
    timing.ta_sure = 0x02;
    timing.ta_go = 0x0C;
    timing.clk_hs_trail = 0x03;
    timing.clk_hs_zero = 0x0C;
    timing.clk_hs_post = 0x09;
    timing.clk_hs_prep = 0x01;

    hal_display_dsi_set_dphy_timing(&timing);

    hal_display_dsi_set_clock(150, false);
} /* init_lcd_interface() */

/***********************RM69080********************************/

void LCD_Init_RM69080(uint16_t bkground)
{
    uint32_t data_array[16];

    // Do HW Reset
    hal_display_lcd_toggle_reset(10, 120);

    data_array[0] = 0x05FE1500;
    hal_display_dsi_set_command_queue(data_array, 1, true);

    data_array[0] = 0x13051500;
    hal_display_dsi_set_command_queue(data_array, 1, true);

    data_array[0] = 0x07FE1500;
    hal_display_dsi_set_command_queue(data_array, 1, true);

    data_array[0] = 0x6D071500;
    hal_display_dsi_set_command_queue(data_array, 1, true);

    data_array[0] = 0x0AFE1500;
    hal_display_dsi_set_command_queue(data_array, 1, true);

    data_array[0] = 0x1B1C1500;
    hal_display_dsi_set_command_queue(data_array, 1, true);

    data_array[0] = 0x00FE1500;
    hal_display_dsi_set_command_queue(data_array, 1, true);

    data_array[0] = 0x00351500;
    hal_display_dsi_set_command_queue(data_array, 1, true);

    data_array[0] = 0x00110500;
    hal_display_dsi_set_command_queue(data_array, 1, true);

    data_array[0] = 0x00003200;
    hal_display_dsi_set_command_queue(data_array, 1, true);

    hal_gpt_delay_ms(300);

    data_array[0] = 0x00290500;
    hal_display_dsi_set_command_queue(data_array, 1, true);

    data_array[0] = 0xFF510500;
    hal_display_dsi_set_command_queue(data_array, 1, true);

}

void LCD_EnterSleep_RM69080(void)
{
    uint32_t data_array[16];

    data_array[0] = 0x00280500;
    hal_display_dsi_set_command_queue(data_array, 1, true);
    hal_gpt_delay_ms(10);

    data_array[0] = 0x01000500;
    hal_display_dsi_set_command_queue(data_array, 1, true);
    hal_gpt_delay_ms(120);
}

void LCD_ExitSleep_RM69080(void)
{
    LCD_Init_RM69080(0);
}

void LCD_blockClear_RM69080(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t data)
{
}

void LCD_ClearAll_RM69080(uint16_t data)
{
    LCD_blockClear_RM69080(0, 0, HEIGHT - 1, WIDTH - 1, data);
}

void LCD_EnterIdle_RM69080(void)
{
    uint32_t data_array[16];

    data_array[0] = 0x00FE1500;
    hal_display_dsi_set_command_queue(data_array, 1, true);
    data_array[0] = 0x00390500;
    hal_display_dsi_set_command_queue(data_array, (uint8_t)1, true);
}

void LCD_ExitIdle_RM69080(void)
{
    uint32_t data_array[16];

    data_array[0] = 0x00FE1500;
    hal_display_dsi_set_command_queue(data_array, 1, true);
    data_array[0] = 0x00380500;
    hal_display_dsi_set_command_queue(data_array, (uint8_t)1, true);
}

void LCD_BlockWrite_RM69080(uint16_t startx, uint16_t starty, uint16_t endx, uint16_t endy)
{
    uint32_t data_array[16];

    unsigned int x0 = startx;
    unsigned int y0 = starty;
    unsigned int x1 = endx;
    unsigned int y1 = endy;

    unsigned char x0_MSB = (x0 >> 8) & 0xFF;
    unsigned char x0_LSB = x0 & 0xFF;
    unsigned char x1_MSB = (x1 >> 8) & 0xFF;
    unsigned char x1_LSB = x1 & 0xFF;
    unsigned char y0_MSB = (y0 >> 8) & 0xFF;
    unsigned char y0_LSB = y0 & 0xFF;
    unsigned char y1_MSB = (y1 >> 8) & 0xFF;
    unsigned char y1_LSB = y1 & 0xFF;

    data_array[0] = 0x00053902;
    data_array[1] = (x1_MSB << 24) | (x0_LSB << 16) | (x0_MSB << 8) | 0x2A;
    data_array[2] = x1_LSB;
    hal_display_dsi_set_command_queue(data_array, 3, true);

    data_array[0] = 0x00053902;
    data_array[1] = (y1_MSB << 24) | (y0_LSB << 16) | (y0_MSB << 8) | 0x2B;
    data_array[2] = y1_LSB;
    hal_display_dsi_set_command_queue(data_array, 3, true);

    hal_display_dsi_set_transfer_mode(HAL_DISPLAY_DSI_TRANSFER_MODE_HS);

    hal_display_lcd_start_dma(0);

#ifdef MTK_TE_ENABLE
    if(RM69080_para.te_enable) {

        hal_display_dsi_start_bta_transfer(0x2C3909);
    }
    else
#endif
    {
        data_array[0] = 0x2C3909;
        hal_display_dsi_set_command_queue(data_array, 1, 0);
    }
}


/***************************** Take Notice *******************************
*************************************************************************/

void LCD_IOCTRL_RM69080(LCM_IOCTRL_ID_ENUM ID, void *Parameters)
{
    switch (ID) {
        case LCM_IOCTRL_QUERY__FRAME_RATE:
            *((uint32_t *)(Parameters)) = 60;
            break;

        case LCM_IOCTRL_QUERY__BACK_PORCH:
            *(uint32_t *)(Parameters) = 12;
            break;

        case LCM_IOCTRL_QUERY__FRONT_PORCH:
            *(uint32_t *)(Parameters) = 12;
            break;

        case LCM_IOCTRL_QUERY__IF_CS_NUMBER:
            *(uint32_t *)(Parameters) = HAL_DISPLAY_LCD_INTERFACE_SERIAL_0;
            break;

        case LCM_IOCTRL_QUERY__LCM_WIDTH:
            *((unsigned long *)(Parameters)) = 400; // physical, not use app's LCD_WIDTH
            break;

        case LCM_IOCTRL_QUERY__LCM_HEIGHT:
            *((unsigned long *)(Parameters)) = 400; //320;// physical, not use app's LCD_HEIGHT
            break;

        case LCM_IOCTRL_QUERY__LCM_SETTING_PARAM:
            *((lcm_config_para_t *)(Parameters)) = RM69080_para; // return LCM_para
            break;

#if 0
        //#ifdef __LCD_ESD_RECOVERY__
        /** LCM ESD feature control, Check LCD ESD is happend or not **/
        case LCM_IOCTRL_ESD_CHECK: {
            LCM_ESD_INFO_STRUCT *pESDInfo = (LCM_ESD_INFO_STRUCT *)Parameters;
            kal_bool lcm_esd_test = KAL_FALSE;

            lcm_esd_test = LCD_Read_ESD_RM69080();

            if (pESDInfo) {
                //TODO: add ESD real check function here
                // If happend, must take lcm_esd_test = KAL_TURE;
                if (lcm_esd_test) {
                    lcm_esd_test = KAL_FALSE;
                    pESDInfo->bEsdHappened = KAL_TRUE;
                } else {
                    pESDInfo->bEsdHappened = KAL_FALSE;
                }
            }

            return LCM_IOCTRL_OK;
            break;
        }

        /** LCM ESD feature control, If LCD ESD is happend, We should do something here like resetLCM. **/
        case LCM_IOCTRL_ESD_RESET:
            //TODO: add LCM reset function here
            //Example
            LCD_Init_RM69080(0);

            break;
#endif
#ifdef MTK_TE_ENABLE
        case LCM_IOCTRL_SET_TE:
            RM69080_para.te_enable = *((bool *)(Parameters));
            break;
#endif

        default:
            break;
    }
}

void LCD_ClearScreen_RM69080(uint16_t color)
{
    LCD_ClearAll_RM69080(color);
}

void LCD_ClearScreenBW_RM69080(void)
{
}

bool LCD_CheckID_RM69080(void)
{
    uint32_t data_array[16];
    uint8_t buffer[3] = { 0 };

    data_array[0] = 0x00033700;
    hal_display_dsi_set_command_queue(data_array, 1, 1);

    hal_display_dsi_read_register(0x04, buffer, 3);

    if((0x05 == buffer[0]) && (0x00 == buffer[1]) && (0x00 == buffer[2]))
        return true;

     return false;
}

LCD_Funcs LCD_func_RM69080 = {
    LCD_Init_RM69080,
    LCD_Init_Interface_RM69080,
    LCD_BlockWrite_RM69080,
    LCD_EnterSleep_RM69080,
    LCD_ExitSleep_RM69080,
    LCD_EnterIdle_RM69080,
    LCD_ExitIdle_RM69080,
    LCD_ClearScreen_RM69080,
    LCD_ClearScreenBW_RM69080,
    LCD_IOCTRL_RM69080,
    LCD_CheckID_RM69080
};

#ifdef __cplusplus
}
#endif

