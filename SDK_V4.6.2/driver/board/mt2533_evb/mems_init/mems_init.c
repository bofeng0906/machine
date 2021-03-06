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

/* Kernel includes. */
#include "FreeRTOS.h"

/* syslog */
#define SENSOR_DEMO_LOGI(fmt,...) LOG_I(sensor,  (fmt), ##__VA_ARGS__)
/* printf*/
//#define SENSOR_DEMO_LOGI(fmt,arg...)   printf("SENSOR_DEMO:INFO: "fmt,##arg)

#include "hal_eint.h"
#include "hal_i2c_master.h"
#include "hal_spi_master.h"

#include "mems_bus.h"

#ifdef MTK_SENSOR_ACCELEROMETER_GYROSCOPE_USE_BMI160
#include "bmi160.h"
#elif defined(MTK_SENSOR_ACCELEROMETER_USE_BMA255)
#include "bma255_sensor_adaptor.h"
#endif

#ifdef MTK_SENSOR_BAROMETER_USE_BMP280
#include "bmp280.h"
#endif

#ifdef MTK_SENSOR_MAGNETIC_USE_YAS533
#include "yas533.h"
#endif

#ifdef MTK_SENSOR_PROXIMITY_USE_CM36672
#include "cm36672.h"
#endif

#ifdef MTK_SENSOR_BIO_USE_MT2511
#include "vsm_sensor_subsys_adaptor.h"
#endif

/**
* @brief  Sensor peripheral initialization (pinmux, EINT).
* @param  None.
* @retval None.
*/

void bsp_sensor_peripheral_init(void)
{
    SENSOR_DEMO_LOGI("\n\r sensorhub_peripheral_init ++\n\r");

    /* 2. Config I2C0 */
    mems_i2c_init(HAL_I2C_MASTER_0, HAL_I2C_FREQUENCY_400K);


    /*3. Config EINT*/
#ifdef MTK_SENSOR_ACCELEROMETER_USE_BMA255
    /* Config EINT*/
    /* GPIO[1] function1 for EINT1, BMA255 */
    hal_eint_config_t eint1_config;
    eint1_config.trigger_mode = HAL_EINT_EDGE_RISING;
    eint1_config.debounce_time = 1;
    hal_eint_init(HAL_EINT_NUMBER_1, &eint1_config);

    bma255_eint_set(HAL_EINT_NUMBER_1);
    hal_eint_register_callback(HAL_EINT_NUMBER_1, bma255_eint_handler, NULL);

#ifdef HAL_EINT_FEATURE_MASK
    hal_eint_unmask(HAL_EINT_NUMBER_1);
#endif
#endif

#ifdef MTK_SENSOR_PROXIMITY_USE_CM36672
    /* GPIO[11] function1 for EINT9, PS_EINT */
    hal_pinmux_set_function(HAL_GPIO_11, HAL_GPIO_11_EINT9);
    hal_eint_config_t eint3_config;
    eint3_config.trigger_mode = HAL_EINT_EDGE_FALLING;
    eint3_config.debounce_time = 1;
    cm36672_eint_set(HAL_EINT_NUMBER_9);
    hal_eint_init(HAL_EINT_NUMBER_9, &eint3_config);
    hal_eint_register_callback(HAL_EINT_NUMBER_9, cm36672_eint_handler, NULL);
#ifdef HAL_EINT_FEATURE_MASK
    hal_eint_unmask(HAL_EINT_NUMBER_9);
#endif
#endif

#ifdef MTK_SENSOR_ACCELEROMETER_GYROSCOPE_USE_BMI160
    /* Accelerometer, Gyro on the same HW component*/
    ags_init();
#elif defined(MTK_SENSOR_ACCELEROMETER_USE_BMA255)
    /* acc sensor */
    bma255_sensor_subsys_init();
#endif

#ifdef MTK_SENSOR_BAROMETER_USE
    /* Barometer*/
    baros_init();
#endif

#ifdef MTK_SENSOR_MAGNETIC_USE
    /* Magnetic sensor*/
    mag_init();
#endif

#ifdef MTK_SENSOR_PROXIMITY_USE
    /* Proximity sensor*/
    ps_init();
#endif

#ifdef MTK_SENSOR_BIO_USE_MT2511
    /* Bio sensor */
    vsm_driver_sensor_subsys_init();
#endif
    SENSOR_DEMO_LOGI("\n\r sensorhub_peripheral_init --\n\r");
}

