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
#ifndef PPG_CONTROL_LIB_H
#define PPG_CONTROL_LIB_H
/**
 * @file    ppg_control.h
 * @brief   Automatic PPG configuration control
 * @author  Mediatek
 * @version 1.0.1.1
 * @date    2016.04.17
 */

/** 
 * @addtogroup PPG_CONTROL 
 * @{
 * This section introduces the PPG control APIs including terms and acronyms, control flow, supported features, PPG function groups, enums, structures and functions. The PPG control library is applied to enhance the PPG signal quality acquired from MediaTek MT2511.
 * 
 * @section Terms_Chapter Terms and acronyms
 * 
 * |Terms                   |Details                                                                 |
 * |------------------------------|------------------------------------------------------------------------|
 * |\b PPG  | Photoplethysmogram. For more information, please refer to <a href="https://en.wikipedia.org/wiki/Photoplethysmogram"> Photoplethysmogram in Wikipedia </a>.|
 *
 * @section Function_Block_Diagram Control Flow: PPG control
 * Initialization
 * @image html Initial.png
 * Measurement
 * @image html Measurement.png
 *
 * @section PPG_Control_Usage_Chapter How to use PPG APIs
 * 
 * Step1: Call #ppg_control_init() to initialize the PPG control library. \n
 * Step2: Call #ppg_control_process() to analyze the incoming PPG data and adjust the setting of analog front-end on MediaTek MT2511. \n
 * 
 *  - sample code:
 *    @code 
 *
 * void example(int32_t state)
 * {
 *     // Initialization 
 *     ppg_control_init(); // Initialize the library.
 *     ppg_control_set_app(PPG_CONTROL_APP_OHRM);  // Set the target MT2511 bio-application.
 *     int32_t ppg_control_fs = 125;            // The sampling frequency of PPG input (Support 125Hz only).
 *     int32_t ppg_control_bit_width = 23;      // The PPG signal bit width.
 *     int32_t ppg_control_cfg = 1;             // The input configuration, default value is 1.
 *     int32_t ppg_control_src = 1;             // The input source, default value is 1 (PPG channel 1).
 *     int32_t ppg_control_mode = PPG_CONTROL_MODE_DUAL1; // The PPG control mode.
 *     ppg_control_t ppg1_control_input;           // Input structure for the #ppg_control_process().
 *     int32_t ppg_control_flag;
 *     int32_t *ppg_control_output;    // Pointer to the result for debugging.
 *
 *     switch(state)
 *     { 
 * 	      case PPG_DATA_READY:
 *            ppg1_control_input.input = data_input_ppg_buf;
 *            ppg1_control_input.input_fs = ppg_control_in_fs;
 *            ppg1_control_input.input_length = 250; // max length = ppg_control_in_fs *2 = 250.
 *            ppg1_control_input.input_bit_width = ppg_control_in_bit_width;
 *            ppg1_control_input.input_config = ppg_control_in_cfg;
 *            ppg1_control_input.input_source = ppg_control_in_src;
 *
 *            ppg_control_flag = ppg_control_process( 
 *                &ppg1_control_input,        // The input signal data.
 *                ppg_control_mode,           // The control mode.
 *                ppg_control_output,         // Pointer to the result for debugging.
 *            );
 *
 *        break; 
 *      }
 * }
 *    @endcode
 *
 */

/** @defgroup ppg_control_define Define
  * @{
  */

#include <stdint.h>
#define INT32 int32_t
#define INT16 int16_t
#define UINT32 uint32_t
#define UINT16 uint16_t

/**
  * @}
  */

/** @defgroup ppg_control_enum Enum
  * @{
  */

/** @brief  This enum defines the return type of PPG control library.  */
typedef enum {
    PPG_CONTROL_STATUS_ERROR        = -2,  /**<  The function call failed. */
    PPG_CONTROL_STATUS_INVALID_PARAMETER   = -1,  /**<  Invalid parameter is given. */
    PPG_CONTROL_STATUS_OK           = 0    /**<  This function call is successful. */
} ppg_control_status_t;

/** @brief This enum defines the PPG control mode. */
typedef enum{
    PPG_CONTROL_MODE_LED1 = 1, /**< Based on the analysis of PPG1, the PPG control API sets the LED channel 1 (LED1). */
    PPG_CONTROL_MODE_DUAL1 = 4 /**< Based on the analysis of PPG1, the PPG control API sets the LED channel 1 (LED1) and LED channel 2 (LED2) with the same value. */
} ppg_control_mode_t;

/** @brief This enum defines the target MediaTek MT2511 bio-application. */
typedef enum{
    PPG_CONTROL_APP_OHRM = 0, /**< The application of optical heart rate monitor. */
    PPG_CONTROL_APP_BP = 1 /**< The application of blood pressure monitor. */
} ppg_control_app_t;

/**
  * @}
  */

/** @defgroup ppg_control_struct Struct
  * @{
  */

/** @struct ppg_control_t
* @brief This structure defines the data input structure for PPG control library.
*/
typedef struct
{	
    INT32 *input;           /**< A pointer to the input PPG signal. */
    INT32 input_fs;         /**< The sampling frequency (fs) of the input data. (supports 125Hz only). */
    INT32 input_length;     /**< The number of input samples. The maximum length = input_fs * 2= 250.*/
    INT32 input_bit_width;  /**< The bit width of the input data. If the data is already converted to signed representation, set bit width to 32. */
    INT32 input_config;     /**< Configuration of the input signal (Please set to 1). */
    INT32 input_source;     /**< 1: this is the data from MT2511 PPG channel 1 (PPG1). 2: this is the data from MT2511 PPG channel 2 (PPG2). */
} ppg_control_t;

/**
  * @}
  */

// Function definition
/** 
 * @brief Call this function to get the library version code. 
 * @return The return value of 0xAABBCCDD corresponds to version AA.BB.CC.DD. The integer value should be converted to heximal representation to get the version number. For example, 0x01000000 is for verion 1.0.0.0.
*/
UINT32 ppg_control_get_version(void);
const char* ppg_control_get_version_string(void);

/** 
 * @brief This function should be called at the initialization stage.
 * @return #PPG_CONTROL_STATUS_ERROR, if the operation failed. \n
 *         #PPG_CONTROL_STATUS_INVALID_PARAMETER, if an invalid parameter was given. \n
 *         #PPG_CONTROL_STATUS_OK, if the operation completed successfully. \n
*/
ppg_control_status_t ppg_control_init(void);

 /** 
 * @brief Call this function to analyze the incoming PPG data and automatically adjust the setting of analog front-end on MediaTek MT2511. 
 * @param[in] *ppg_control_input is the input data structure containing the actual data to be processed by this API, in order to adjust the setting of the the analog front-end on MediaTek MT2511.
 * @param[in] ppg_control_mode is to set the library according to the LED/PPG configuration. \n
 *            #PPG_CONTROL_MODE_LED1: Adjust only LED1, according to PPG1. \n
 *            #PPG_CONTROL_MODE_DUAL1: Adjust both LED1 and LED2 with equal current, according to PPG1.
 * @param[out] *ppg_control_output is the output signal data buffer
 * @return    Return the flag to indicate whether the setting of the MT2511 analog front-end is adjusted. \n 
 *            #PPG_CONTROL_STATUS_ERROR, if the operation failed. \n
 *            #PPG_CONTROL_STATUS_INVALID_PARAMETER, if an invalid parameter was given. \n
 *            #PPG_CONTROL_STATUS_OK, if the operation completed successfully. \n
 *  
*/
INT32 ppg_control_process(      	
    ppg_control_t *ppg_control_input,    // The input signal data.
    INT32 ppg_control_mode,              // The PPG control mode.
    INT32 *ppg_control_output            // The output signal data.
);

/** 
 * @brief This function sets the target PPG application.
 * @param[in] ppg_control_app is to specify the target PPG application.
 * @return #PPG_CONTROL_STATUS_ERROR, if the operation failed. \n
 *         #PPG_CONTROL_STATUS_INVALID_PARAMETER, if an invalid parameter was given. \n
 *         #PPG_CONTROL_STATUS_OK, if the operation completed successfully. \n
*/
ppg_control_status_t ppg_control_set_app(ppg_control_app_t ppg_control_app);

/**
 * @brief This function acesses the internal status of the PPG control library.
 * @param[in] ppg_control_internal_config is to select the internal status of target module.
 * @return 32-bit internal status of library for debugging.
*/
INT32 ppg_control_get_status(INT32 ppg_control_internal_config);

/**
* @}
* @}
*/





#endif //PPG_CONTROL_LIB_H




