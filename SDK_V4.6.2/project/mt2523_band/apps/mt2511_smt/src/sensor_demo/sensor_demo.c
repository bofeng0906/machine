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

 #include "sensor_demo.h"

 /* Kernel includes. */
#include "FreeRTOS.h"

#ifdef SENSOR_DEMO

#include "hal_eint.h"
#include "hal_i2c_master.h"
#include "hal_spi_master.h"
#include "hal_gpio.h"

/* sensor subsys includes */
#include "mems_bus.h"
#include "sensor_manager.h" /* sensor manager task */
#include "sensor_alg_interface.h"

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

#ifdef DEVICE_BAND
void sensor_peripheral_init()
{
    /* 1. Config I2C0 */
    mems_i2c_init(HAL_I2C_MASTER_0, HAL_I2C_FREQUENCY_400K);

    /*2. Config EINT*/
    #ifdef MTK_SENSOR_ACCELEROMETER_USE_BMA255
    /* GPIO[12] function1 for EINT10, BMA255 */
    hal_pinmux_set_function(HAL_GPIO_12, 1);
    hal_eint_config_t eint1_config;
    eint1_config.trigger_mode = HAL_EINT_EDGE_RISING;
    eint1_config.debounce_time = 0;
    hal_eint_init(HAL_EINT_NUMBER_10, &eint1_config);
    bma255_eint_set(HAL_EINT_NUMBER_10);
    hal_eint_register_callback(HAL_EINT_NUMBER_10, bma255_eint_handler, NULL);
#ifdef HAL_EINT_FEATURE_MASK
    hal_eint_unmask(HAL_EINT_NUMBER_10);
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
}

#elif defined(DEVICE_HDK)

/* pin mux setting of HDK */
void sensor_peripheral_init()
{
    int32_t ret = 0;

    SENSOR_DEMO_LOGI("\n\r sensorhub_peripheral_init ++\n\r");

    /* 1. Config SPI3 */
    hal_spi_master_config_t spi_config;
    spi_config.clock_frequency = 0x400000;
    spi_config.slave_port = HAL_SPI_MASTER_SLAVE_0;
    spi_config.bit_order = HAL_SPI_MASTER_MSB_FIRST;
    spi_config.polarity = HAL_SPI_MASTER_CLOCK_POLARITY0;
    spi_config.phase = HAL_SPI_MASTER_CLOCK_PHASE0;

    mems_spi_init(SPI_SELECT_BMI160, HAL_SPI_MASTER_3, &spi_config, HAL_SPI_MASTER_MACRO_GROUP_B);

    /* 2. Config I2C2 */
    mems_i2c_init(HAL_I2C_MASTER_0, HAL_I2C_FREQUENCY_400K);

    /*3. Config EINT*/
  #ifdef MTK_SENSOR_ACCELEROMETER_GYROSCOPE_USE_BMI160
    /* GPIO[5] function1 for EINT4, BMI160 */
    hal_eint_config_t eint1_config;
    eint1_config.trigger_mode = HAL_EINT_EDGE_RISING;
    eint1_config.debounce_time = 10;
    hal_eint_init(HAL_EINT_NUMBER_4, &eint1_config);
    hal_eint_register_callback(HAL_EINT_NUMBER_4, bmi160_eint_handler, NULL);
#ifdef HAL_EINT_FEATURE_MASK
    hal_eint_unmask(HAL_EINT_NUMBER_4);
#endif
  #elif defined(MTK_SENSOR_ACCELEROMETER_USE_BMA255)
    /* GPIO[12] function1 for EINT10, BMA255 */
    hal_pinmux_set_function(HAL_GPIO_5, 1);
    hal_eint_config_t eint1_config;
    eint1_config.trigger_mode = HAL_EINT_EDGE_RISING;
    eint1_config.debounce_time = 10;
    hal_eint_init(HAL_EINT_NUMBER_4, &eint1_config);
    bma255_eint_set(HAL_EINT_NUMBER_4);
    hal_eint_register_callback(HAL_EINT_NUMBER_4, bma255_eint_handler, NULL);
#ifdef HAL_EINT_FEATURE_MASK
    hal_eint_unmask(HAL_EINT_NUMBER_4);
#endif
  #endif

  #ifdef MTK_SENSOR_PROXIMITY_USE_CM36672
    /* GPIO[6] function1 for EINT5, PS_EINT */
    hal_eint_config_t eint3_config;
    eint3_config.trigger_mode = HAL_EINT_EDGE_FALLING;
    eint3_config.debounce_time = 10;
    hal_eint_init(HAL_EINT_NUMBER_5, &eint3_config);
    hal_eint_register_callback(HAL_EINT_NUMBER_5, cm36672_eint_handler, NULL);
#ifdef HAL_EINT_FEATURE_MASK
    hal_eint_unmask(HAL_EINT_NUMBER_5);
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

#else

/* pin mux setting of EVB */
void sensor_peripheral_init()
{
    int32_t ret = 0;

    SENSOR_DEMO_LOGI("\n\r sensorhub_peripheral_init ++\n\r");

    /* 1. Config SPI3 */
    hal_pinmux_set_function(HAL_GPIO_32, 9);
    hal_pinmux_set_function(HAL_GPIO_33, 9);
    hal_pinmux_set_function(HAL_GPIO_34, 9);
    hal_pinmux_set_function(HAL_GPIO_35, 9);

    hal_spi_master_config_t spi_config;
    spi_config.clock_frequency = 0x400000;
    spi_config.slave_port = HAL_SPI_MASTER_SLAVE_0;
    spi_config.bit_order = HAL_SPI_MASTER_MSB_FIRST;
    spi_config.polarity = HAL_SPI_MASTER_CLOCK_POLARITY0;
    spi_config.phase = HAL_SPI_MASTER_CLOCK_PHASE0;

    mems_spi_init(SPI_SELECT_BMI160, HAL_SPI_MASTER_3, &spi_config, HAL_SPI_MASTER_MACRO_GROUP_B);

    /* 2. Config I2C0 */
    mems_i2c_init(HAL_I2C_MASTER_0, HAL_I2C_FREQUENCY_400K);

    /*3. Config EINT*/
  #ifdef MTK_SENSOR_ACCELEROMETER_GYROSCOPE_USE_BMI160
    /* GPIO[14] function1 for EINT12, BMI160 */
    hal_pinmux_set_function(HAL_GPIO_14, 1);
    hal_eint_config_t eint1_config;
    eint1_config.trigger_mode = HAL_EINT_EDGE_RISING;
    eint1_config.debounce_time = 10;
    hal_eint_init(HAL_EINT_NUMBER_12, &eint1_config);
    hal_eint_register_callback(HAL_EINT_NUMBER_12, bmi160_eint_handler, NULL);
#ifdef HAL_EINT_FEATURE_MASK
    hal_eint_unmask(HAL_EINT_NUMBER_12);
#endif
  #elif defined(MTK_SENSOR_ACCELEROMETER_USE_BMA255)
    /* GPIO[12] function1 for EINT10, BMA255 */
    hal_pinmux_set_function(HAL_GPIO_12, 1);
    hal_eint_config_t eint1_config;
    eint1_config.trigger_mode = HAL_EINT_EDGE_RISING;
    eint1_config.debounce_time = 10;
    hal_eint_init(HAL_EINT_NUMBER_10, &eint1_config);
    hal_eint_register_callback(HAL_EINT_NUMBER_10, bma255_eint_handler, NULL);
#ifdef HAL_EINT_FEATURE_MASK
    hal_eint_unmask(HAL_EINT_NUMBER_10);
#endif
  #endif

  #ifdef MTK_SENSOR_PROXIMITY_USE_CM36672
    /* GPIO[11] function1 for EINT9, PS_EINT */
    hal_pinmux_set_function(HAL_GPIO_11, 1);
    hal_eint_config_t eint3_config;
    eint3_config.trigger_mode = HAL_EINT_EDGE_FALLING;
    eint3_config.debounce_time = 10;
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
#endif /* not defined DEVICE_BAND && not defined DEVICE_HDK*/

#endif /*SENSOR_DEMO*/

