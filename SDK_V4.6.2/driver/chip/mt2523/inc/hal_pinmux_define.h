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

#ifndef __HAL_PINMUX_DEFINE_H__
#define __HAL_PINMUX_DEFINE_H__

#include "hal_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAL_GPIO_MODULE_ENABLED

#define HAL_GPIO_0_GPIO0   0
#define HAL_GPIO_0_EINT0   1
#define HAL_GPIO_0_AUXADCIN_0   2
#define HAL_GPIO_0_U2RXD   3
#define HAL_GPIO_0_PWM0   4
#define HAL_GPIO_0_MA_SPI1_A_CS   5
#define HAL_GPIO_0_MA_EDIDO   6
#define HAL_GPIO_0_MA_SPI0_A_CS   7
#define HAL_GPIO_0_DEBUGMON11   8
#define HAL_GPIO_0_BTJTDO   9
#define HAL_GPIO_1_GPIO1   0
#define HAL_GPIO_1_EINT1   1
#define HAL_GPIO_1_AUXADCIN_1   2
#define HAL_GPIO_1_U2TXD   3
#define HAL_GPIO_1_PWM1   4
#define HAL_GPIO_1_MA_SPI1_A_SCK   5
#define HAL_GPIO_1_MA_EDIDI   6
#define HAL_GPIO_1_MA_SPI0_A_SCK   7
#define HAL_GPIO_1_DEBUGMON12   8
#define HAL_GPIO_1_BTDBGACKN   9
#define HAL_GPIO_2_GPIO2   0
#define HAL_GPIO_2_EINT2   1
#define HAL_GPIO_2_AUXADCIN_2   2
#define HAL_GPIO_2_U3RXD   3
#define HAL_GPIO_2_U0CTS   4
#define HAL_GPIO_2_MA_SPI1_A_MOSI   5
#define HAL_GPIO_2_MA_EDIWS   6
#define HAL_GPIO_2_MA_SPI0_A_MOSI   7
#define HAL_GPIO_2_DEBUGMON13   8
#define HAL_GPIO_2_BT_BUCK_EN_HW   9
#define HAL_GPIO_3_GPIO3   0
#define HAL_GPIO_3_EINT14   1
#define HAL_GPIO_3_AUXADCIN_3   2
#define HAL_GPIO_3_U3TXD   3
#define HAL_GPIO_3_U0RTS   4
#define HAL_GPIO_3_MA_SPI1_A_MISO   5
#define HAL_GPIO_3_MA_EDICK   6
#define HAL_GPIO_3_MA_SPI0_A_MISO   7
#define HAL_GPIO_3_DEBUGMON14   8
#define HAL_GPIO_3_BTPRI   9
#define HAL_GPIO_4_GPIO4   0
#define HAL_GPIO_4_EINT3   1
#define HAL_GPIO_4_MC1_A_CK   2
#define HAL_GPIO_4_SLA_EDIDO   3
#define HAL_GPIO_4_U1RXD   6
#define HAL_GPIO_4_MA_SPI0_B_CS   7
#define HAL_GPIO_5_GPIO5   0
#define HAL_GPIO_5_EINT4   1
#define HAL_GPIO_5_MC1_A_CM0   2
#define HAL_GPIO_5_SLA_EDIDI   3
#define HAL_GPIO_5_U1TXD   6
#define HAL_GPIO_5_MA_SPI0_B_SCK   7
#define HAL_GPIO_6_GPIO6   0
#define HAL_GPIO_6_EINT5   1
#define HAL_GPIO_6_MC1_A_DA0   2
#define HAL_GPIO_6_SLA_EDIWS   3
#define HAL_GPIO_6_U2RXD   4
#define HAL_GPIO_6_MA_SPI0_B_MOSI   7
#define HAL_GPIO_7_GPIO7   0
#define HAL_GPIO_7_EINT6   1
#define HAL_GPIO_7_MC1_A_DA1   2
#define HAL_GPIO_7_SLA_EDICK   3
#define HAL_GPIO_7_U2TXD   4
#define HAL_GPIO_7_BT_BUCK_EN_HW   6
#define HAL_GPIO_7_MA_SPI0_B_MISO   7
#define HAL_GPIO_8_GPIO8   0
#define HAL_GPIO_8_EINT7   1
#define HAL_GPIO_8_MC1_A_DA2   2
#define HAL_GPIO_8_SCL2   6
#define HAL_GPIO_9_GPIO9   0
#define HAL_GPIO_9_EINT8   1
#define HAL_GPIO_9_MC1_A_DA3   2
#define HAL_GPIO_9_SDA2   6
#define HAL_GPIO_10_GPIO10   0
#define HAL_GPIO_10_EINT15   1
#define HAL_GPIO_10_AUXADCIN_4   2
#define HAL_GPIO_10_DEBUGMON15   8
#define HAL_GPIO_10_BTPRI   9
#define HAL_GPIO_11_GPIO11   0
#define HAL_GPIO_11_EINT9   1
#define HAL_GPIO_11_BT_BUCK_EN_HW   2
#define HAL_GPIO_11_MA_EDIDO   3
#define HAL_GPIO_11_MA_SPI1_B_CS   4
#define HAL_GPIO_11_PWM0   5
#define HAL_GPIO_11_SLA_EDIDO   6
#define HAL_GPIO_12_GPIO12   0
#define HAL_GPIO_12_EINT10   1
#define HAL_GPIO_12_MA_EDIDI   3
#define HAL_GPIO_12_MA_SPI1_B_SCK   4
#define HAL_GPIO_12_PWM1   5
#define HAL_GPIO_12_SLA_EDIDI   6
#define HAL_GPIO_13_GPIO13   0
#define HAL_GPIO_13_EINT11   1
#define HAL_GPIO_13_CLKO3   2
#define HAL_GPIO_13_MA_EDIWS   3
#define HAL_GPIO_13_MA_SPI1_B_MOSI   4
#define HAL_GPIO_13_PWM2   5
#define HAL_GPIO_13_SLA_EDIWS   6
#define HAL_GPIO_14_GPIO14   0
#define HAL_GPIO_14_EINT12   1
#define HAL_GPIO_14_CLKO4   2
#define HAL_GPIO_14_MA_EDICK   3
#define HAL_GPIO_14_MA_SPI1_B_MISO   4
#define HAL_GPIO_14_PWM3   5
#define HAL_GPIO_14_SLA_EDICK   6
#define HAL_GPIO_15_GPIO15   0
#define HAL_GPIO_15_EINT13   1
#define HAL_GPIO_15_PWM4   5
#define HAL_GPIO_16_GPIO16   0
#define HAL_GPIO_16_U0RXD   1
#define HAL_GPIO_16_EINT16   3
#define HAL_GPIO_16_DEBUGMIN0   6
#define HAL_GPIO_16_DEBUGMON0   7
#define HAL_GPIO_17_GPIO17   0
#define HAL_GPIO_17_U0TXD   1
#define HAL_GPIO_17_EINT17   3
#define HAL_GPIO_17_DEBUGMIN_CK   6
#define HAL_GPIO_18_GPIO18   0
#define HAL_GPIO_18_KCOL2   1
#define HAL_GPIO_18_U1RXD   2
#define HAL_GPIO_18_U3RXD   3
#define HAL_GPIO_18_TRACEDATA0   5
#define HAL_GPIO_18_LSCE1_B1   6
#define HAL_GPIO_18_DEBUGMON6   7
#define HAL_GPIO_18_JTDI   8
#define HAL_GPIO_18_BTJTDI   9
#define HAL_GPIO_19_GPIO19   0
#define HAL_GPIO_19_KCOL1   1
#define HAL_GPIO_19_EINT18   2
#define HAL_GPIO_19_U0RTS   3
#define HAL_GPIO_19_SCL2   4
#define HAL_GPIO_19_TRACEDATA1   5
#define HAL_GPIO_19_DEBUGMON2   7
#define HAL_GPIO_19_JTMS   8
#define HAL_GPIO_19_BTJTMS   9
#define HAL_GPIO_20_GPIO20   0
#define HAL_GPIO_20_KCOL0   1
#define HAL_GPIO_20_GPSFSYNC   2
#define HAL_GPIO_20_U0CTS   3
#define HAL_GPIO_20_SDA2   4
#define HAL_GPIO_20_MA_SPI2_CS1   6
#define HAL_GPIO_20_DEBUGMON7   7
#define HAL_GPIO_21_GPIO21   0
#define HAL_GPIO_21_KROW2   1
#define HAL_GPIO_21_GPCOUNTER_0   3
#define HAL_GPIO_21_U1RTS   4
#define HAL_GPIO_21_TRACECLK   5
#define HAL_GPIO_21_DEBUGMON4   7
#define HAL_GPIO_21_JTCK   8
#define HAL_GPIO_21_BTJTCK   9
#define HAL_GPIO_22_GPIO22   0
#define HAL_GPIO_22_KROW1   1
#define HAL_GPIO_22_U1TXD   2
#define HAL_GPIO_22_U3TXD   3
#define HAL_GPIO_22_TRACEDATA2   5
#define HAL_GPIO_22_TRACE_SWV   6
#define HAL_GPIO_22_DEBUGMON5   7
#define HAL_GPIO_22_JTDO   8
#define HAL_GPIO_22_BTDBGIN   9
#define HAL_GPIO_23_GPIO23   0
#define HAL_GPIO_23_KROW0   1
#define HAL_GPIO_23_EINT19   2
#define HAL_GPIO_23_CLKO0   3
#define HAL_GPIO_23_U1CTS   4
#define HAL_GPIO_23_TRACEDATA3   5
#define HAL_GPIO_23_MC_RST   6
#define HAL_GPIO_23_DEBUGMON9   7
#define HAL_GPIO_23_JTRST_B   8
#define HAL_GPIO_23_BTJTRSTB   9
#define HAL_GPIO_24_GPIO24   0
#define HAL_GPIO_24_CMRST   1
#define HAL_GPIO_24_LSRSTB   2
#define HAL_GPIO_24_CLKO1   3
#define HAL_GPIO_24_EINT9   4
#define HAL_GPIO_24_GPCOUNTER_0   5
#define HAL_GPIO_24_JTDI   6
#define HAL_GPIO_24_DEBUGMON10   7
#define HAL_GPIO_24_MC1_B_DA3   8
#define HAL_GPIO_25_GPIO25   0
#define HAL_GPIO_25_CMPDN   1
#define HAL_GPIO_25_LSCK1   2
#define HAL_GPIO_25_DAICLK   3
#define HAL_GPIO_25_MA_SPI2_A_CS   4
#define HAL_GPIO_25_MA_SPI3_A_CS   5
#define HAL_GPIO_25_JTMS   6
#define HAL_GPIO_25_DEBUGMON11   7
#define HAL_GPIO_25_MC1_B_DA2   8
#define HAL_GPIO_25_SLV_SPI0_CS   9
#define HAL_GPIO_26_GPIO26   0
#define HAL_GPIO_26_CMCSD0   1
#define HAL_GPIO_26_LSCE_B1   2
#define HAL_GPIO_26_DAIPCMIN   3
#define HAL_GPIO_26_MA_SPI2_A_SCK   4
#define HAL_GPIO_26_MA_SPI3_A_SCK   5
#define HAL_GPIO_26_JTCK   6
#define HAL_GPIO_26_DEBUGMON12   7
#define HAL_GPIO_26_MC1_B_CM0   8
#define HAL_GPIO_26_SLV_SPI0_SCK   9
#define HAL_GPIO_27_GPIO27   0
#define HAL_GPIO_27_CMCSD1   1
#define HAL_GPIO_27_LSDA1   2
#define HAL_GPIO_27_DAIPCMOUT   3
#define HAL_GPIO_27_MA_SPI2_A_MOSI   4
#define HAL_GPIO_27_MA_SPI3_A_MOSI   5
#define HAL_GPIO_27_JTRST_B   6
#define HAL_GPIO_27_DEBUGMON13   7
#define HAL_GPIO_27_MC1_B_CK   8
#define HAL_GPIO_27_SLV_SPI0_MOSI   9
#define HAL_GPIO_28_GPIO28   0
#define HAL_GPIO_28_CMMCLK   1
#define HAL_GPIO_28_LSA0DA1   2
#define HAL_GPIO_28_DAISYNC   3
#define HAL_GPIO_28_MA_SPI2_A_MISO   4
#define HAL_GPIO_28_MA_SPI3_A_MISO   5
#define HAL_GPIO_28_JTDO   6
#define HAL_GPIO_28_DEBUGMON14   7
#define HAL_GPIO_28_MC1_B_DA0   8
#define HAL_GPIO_28_SLV_SPI0_MISO   9
#define HAL_GPIO_29_GPIO29   0
#define HAL_GPIO_29_CMCSK   1
#define HAL_GPIO_29_LPTE   2
#define HAL_GPIO_29_CMCSD2   4
#define HAL_GPIO_29_EINT10   5
#define HAL_GPIO_29_DEBUGMON15   7
#define HAL_GPIO_29_MC1_B_DA1   8
#define HAL_GPIO_29_BT_RGPIO2   9
#define HAL_GPIO_30_GPIO30   0
#define HAL_GPIO_30_SCL0   1
#define HAL_GPIO_30_EINT11   2
#define HAL_GPIO_30_PWM0   3
#define HAL_GPIO_30_U1RXD   4
#define HAL_GPIO_30_MC0_CK   5
#define HAL_GPIO_30_BT_RGPIO0   6
#define HAL_GPIO_30_DEBUGMON0   7
#define HAL_GPIO_30_SCL2   9
#define HAL_GPIO_31_GPIO31   0
#define HAL_GPIO_31_SDA0   1
#define HAL_GPIO_31_EINT12   2
#define HAL_GPIO_31_PWM1   3
#define HAL_GPIO_31_U1TXD   4
#define HAL_GPIO_31_MC0_CM0   5
#define HAL_GPIO_31_DEBUGMIN1   6
#define HAL_GPIO_31_DEBUGMON1   7
#define HAL_GPIO_31_BT_RGPIO1   8
#define HAL_GPIO_31_SDA2   9
#define HAL_GPIO_32_GPIO32   0
#define HAL_GPIO_32_SLV_SPI0_CS   1
#define HAL_GPIO_32_EINT13   2
#define HAL_GPIO_32_PWM2   3
#define HAL_GPIO_32_DAISYNC   4
#define HAL_GPIO_32_MC0_DA0   5
#define HAL_GPIO_32_DEBUGMIN2   6
#define HAL_GPIO_32_DEBUGMON2   7
#define HAL_GPIO_32_MA_SPI3_B_CS   9
#define HAL_GPIO_33_GPIO33   0
#define HAL_GPIO_33_SLV_SPI0_SCK   1
#define HAL_GPIO_33_EINT14   2
#define HAL_GPIO_33_PWM3   3
#define HAL_GPIO_33_DAIPCMIN   4
#define HAL_GPIO_33_MC0_DA1   5
#define HAL_GPIO_33_BT_RGPIO3   6
#define HAL_GPIO_33_DEBUGMON3   7
#define HAL_GPIO_33_MA_SPI3_B_SCK   9
#define HAL_GPIO_34_GPIO34   0
#define HAL_GPIO_34_SLV_SPI0_MOSI   1
#define HAL_GPIO_34_EINT15   2
#define HAL_GPIO_34_PWM4   3
#define HAL_GPIO_34_DAICLK   4
#define HAL_GPIO_34_MC0_DA2   5
#define HAL_GPIO_34_BT_RGPIO4   6
#define HAL_GPIO_34_DEBUGMON4   7
#define HAL_GPIO_34_MA_SPI3_B_MOSI   9
#define HAL_GPIO_35_GPIO35   0
#define HAL_GPIO_35_SLV_SPI0_MISO   1
#define HAL_GPIO_35_EINT3   2
#define HAL_GPIO_35_PWM5   3
#define HAL_GPIO_35_DAIPCMOUT   4
#define HAL_GPIO_35_MC0_DA3   5
#define HAL_GPIO_35_CLKO2   6
#define HAL_GPIO_35_BT_RGPIO5   7
#define HAL_GPIO_35_MA_SPI3_B_MISO   9
#define HAL_GPIO_36_GPIO36   0
#define HAL_GPIO_36_SCL0   1
#define HAL_GPIO_36_SCL1   2
#define HAL_GPIO_36_DEBUGMIN3   6
#define HAL_GPIO_36_DEBUGMON3   7
#define HAL_GPIO_37_GPIO37   0
#define HAL_GPIO_37_SDA0   1
#define HAL_GPIO_37_SDA1   2
#define HAL_GPIO_37_DEBUGMIN4   6
#define HAL_GPIO_37_DEBUGMON4   7
#define HAL_GPIO_38_GPIO38   0
#define HAL_GPIO_38_LSRSTB   1
#define HAL_GPIO_38_CMRST   3
#define HAL_GPIO_38_CLKO3   4
#define HAL_GPIO_38_SFSWP   5
#define HAL_GPIO_38_DEBUGMON9   7
#define HAL_GPIO_38_SCL1   9
#define HAL_GPIO_39_GPIO39   0
#define HAL_GPIO_39_LSCE_B0   1
#define HAL_GPIO_39_EINT4   2
#define HAL_GPIO_39_CMCSD0   3
#define HAL_GPIO_39_CLKO4   4
#define HAL_GPIO_39_SFSCS0   5
#define HAL_GPIO_39_DEBUGMIN5   6
#define HAL_GPIO_39_DEBUGMON5   7
#define HAL_GPIO_39_SCL1   8
#define HAL_GPIO_39_MA_SPI2_B_CS   9
#define HAL_GPIO_40_GPIO40   0
#define HAL_GPIO_40_LSCK0   1
#define HAL_GPIO_40_CMPDN   3
#define HAL_GPIO_40_SFSHOLD   5
#define HAL_GPIO_40_DEBUGMON10   7
#define HAL_GPIO_40_MA_SPI2_B_SCK   9
#define HAL_GPIO_41_GPIO41   0
#define HAL_GPIO_41_LSDA0   1
#define HAL_GPIO_41_EINT5   2
#define HAL_GPIO_41_CMCSD1   3
#define HAL_GPIO_41_WIFITOBT   4
#define HAL_GPIO_41_SFSCK   5
#define HAL_GPIO_41_DEBUGMIN6   6
#define HAL_GPIO_41_DEBUGMON6   7
#define HAL_GPIO_41_SDA1   8
#define HAL_GPIO_41_MA_SPI2_B_MOSI   9
#define HAL_GPIO_42_GPIO42   0
#define HAL_GPIO_42_LSA0DA0   1
#define HAL_GPIO_42_LSCE1_B0   2
#define HAL_GPIO_42_CMMCLK   3
#define HAL_GPIO_42_SFSOUT   5
#define HAL_GPIO_42_DEBUGMON8   7
#define HAL_GPIO_42_CLKO5   8
#define HAL_GPIO_42_MA_SPI2_B_MISO   9
#define HAL_GPIO_43_GPIO43   0
#define HAL_GPIO_43_LPTE   1
#define HAL_GPIO_43_EINT6   2
#define HAL_GPIO_43_CMCSK   3
#define HAL_GPIO_43_CMCSD2   4
#define HAL_GPIO_43_SFSIN   5
#define HAL_GPIO_43_DEBUGMON7   7
#define HAL_GPIO_43_DEBUGMIN7   8
#define HAL_GPIO_43_SDA1   9
#define HAL_GPIO_44_GPIO44   0
#define HAL_GPIO_44_LSCE1_B1   1
#define HAL_GPIO_44_DISP_PWM   2
#define HAL_GPIO_44_DEBUGMON0   7
#define HAL_GPIO_44_DEBUGMON6   8
#define HAL_GPIO_45_GPIO45   0
#define HAL_GPIO_45_SRCLKENAI   1
#define HAL_GPIO_46_GPIO46   0
#define HAL_GPIO_46_MA_SPI0_CS1   1
#define HAL_GPIO_46_DEBUGMON1   7
#define HAL_GPIO_47_GPIO47   0
#define HAL_GPIO_47_MA_SPI1_CS1   1
#define HAL_GPIO_47_DEBUGMON2   7
#define HAL_GPIO_48_GPIO48   0
#define HAL_GPIO_48_MA_SPI3_CS1   1
#define HAL_GPIO_48_DEBUGMON5   7


#ifdef __cplusplus
}
#endif

#endif /*HAL_GPIO_MODULE_ENABLED*/

#endif /*__HAL_PINMUX_DEFINE_H__*/

