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

#ifndef __HAL_FEATURE_CONFIG_H__
#define __HAL_FEATURE_CONFIG_H__


#ifdef __cplusplus
    extern "C" {
#endif


/*****************************************************************************
* module ON or OFF feature option,only option in this temple
*****************************************************************************/

//#define HAL_ACCDET_MODULE_ENABLED
#define HAL_ADC_MODULE_ENABLED
#define HAL_AES_MODULE_ENABLED          
//#define HAL_AUDIO_MODULE_ENABLED     
#define HAL_CACHE_MODULE_ENABLED    
#define HAL_DES_MODULE_ENABLED      
#define HAL_EINT_MODULE_ENABLED        
#define HAL_FLASH_MODULE_ENABLED       
#define HAL_GDMA_MODULE_ENABLED         
#define HAL_GPC_MODULE_ENABLED        
#define HAL_GPIO_MODULE_ENABLED         
#define HAL_GPT_MODULE_ENABLED          
#define HAL_I2C_MASTER_MODULE_ENABLED 
#define HAL_I2S_MODULE_ENABLED
#define HAL_IRRX_MODULE_ENABLED       
#define HAL_IRTX_MODULE_ENABLED
//#define HAL_ISINK_MODULE_ENABLED       
//#define HAL_KEYPAD_MODULE_ENABLED      
#define HAL_MD5_MODULE_ENABLED          
//#define HAL_MPU_MODULE_ENABLED  
#define HAL_NVIC_MODULE_ENABLED
#define HAL_PWM_MODULE_ENABLED         
#define HAL_RTC_MODULE_ENABLED         
//#define HAL_SD_MODULE_ENABLED           
//#define HAL_SDIO_MODULE_ENABLED         
#define HAL_SHA_MODULE_ENABLED         
#define HAL_SPI_MASTER_MODULE_ENABLED   
//#define HAL_SPI_SLAVE_MODULE_ENABLED
#define HAL_TRNG_MODULE_ENABLED 
#define HAL_UART_MODULE_ENABLED        
#define HAL_WDT_MODULE_ENABLED       
#define HAL_DWT_MODULE_ENABLED

#define MTK_HAL_PLAIN_LOG_ENABLE
/*****************************************************************************
* module sub features define
*****************************************************************************/

/*This definition determines whether the demo uses PWM functions, such as LCD backlight or other module  which need change frequency or duty via PWM.*/
#ifdef HAL_PWM_MODULE_ENABLED
    #define HAL_PWM_FEATURE_SINGLE_SOURCE_CLOCK        /*please not to modify*/
#endif	


/*This definition determines whether user can use the RTC mode feature. If it is not defined, then user cannot use the RTC mode feature.*/
#ifdef HAL_RTC_MODULE_ENABLED
    #define HAL_RTC_FEATURE_SLEEP        /*please not to modify*/
#endif	

/*This definition determines whether the demo can use UART module. If it is not defined, then the demo can't use the UART module to communicate with others or for logging and the UART driver will use default timeout value for RX notice mechanism.*/
#ifdef HAL_UART_MODULE_ENABLED
    #define HAL_UART_FEATURE_VFIFO_DMA_TIMEOUT        /*please not to modify*/
#endif

/*This definition determines whether the I2S supports VFIFO function. For MT7687 platform, the user must define this definition to let I2S work normally.*/
#ifdef HAL_I2S_MODULE_ENABLED
    #define HAL_I2S_EXTENDED                        /*please not to modify*/
    #define HAL_I2S_SUPPORT_VFIFO                   /*please not to modify*/
#endif

#ifdef __cplusplus
}
#endif

#endif /* __HAL_FEATURE_CONFIG_H__ */ 

