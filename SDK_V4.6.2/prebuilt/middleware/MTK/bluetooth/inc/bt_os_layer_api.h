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

#ifndef __BT_OS_LAYER_API_H__
#define __BT_OS_LAYER_API_H__

/**
 * This header file describes the apis which might have different implementation if use differnt platform.
 * Once change the platform, these api need to be implemented by user.
 */

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    const uint8_t *buffer;  /**< Buffer pointer. */
    uint32_t length;  /**< Buffer length. */
} bt_os_layer_aes_buffer_t;

typedef struct {
    uint32_t total[2];
    uint32_t state[4];
    unsigned char buffer[64];
} bt_os_md5_context;

/**
 * @brief     Timer callback function pointer.
 * @return    None.
 */
typedef void (*bt_os_layer_timer_expired_t)(void);

/**
 * @brief     Timer initiation.
 * @return    None.
 */
void bt_os_layer_init_timer(void);

/**
 * @brief     Timer deinitiation.
 * @return    None.
 */
void bt_os_layer_deinit_timer(void);

/**
 * @brief     Task sleep the specific time.
 * @param[in] ms is the sleep time.
 * @return    None.
 */
void bt_os_layer_sleep_task(uint32_t ms);

/**
 * @brief     Get current task id.
 * @return    Current task id.
 */
uint32_t bt_os_layer_get_current_task_id(void);

/**
 * @brief     Create mutex.
 * @return    Mutex id.
 */
uint32_t bt_os_layer_create_mutex(void);

/**
 * @brief     Take mutex.
 * @param[in] mutex_id is the mutex id after create.
 * @return    None.
 */
void bt_os_layer_take_mutex(uint32_t mutex_id);

/**
 * @brief     Give mutex.
 * @param[in] mutex_id is the mutex id after create.
 * @return    None.
 */
void bt_os_layer_give_mutex(uint32_t mutex_id);

/**
 * @brief     Delete mutex.
 * @param[in] mutex_id is the mutex id after create.
 * @return    None.
 */
void bt_os_layer_delete_mutex(uint32_t mutex_id);

/**
 * @brief     Create semaphore.
 * @return    Semaphore id.
 */
uint32_t bt_os_layer_create_semaphore(void);

/**
 * @brief     Take semaphore from ISR.
 * @param[in] semaphore_id is the semaphore id after create.
 * @return    None.
 */
void bt_os_layer_take_semaphore_from_isr(uint32_t semaphore_id);

/**
 * @brief     Take semaphore.
 * @param[in] semaphore_id is the semaphore id after create.
 * @return    None.
 */
void bt_os_layer_take_semaphore(uint32_t semaphore_id);

/**
 * @brief     Give semaphore from ISR.
 * @param[in] semaphore_id is the semaphore id after create.
 * @return    None.
 */
void bt_os_layer_give_semaphore_from_isr(uint32_t semaphore_id);

/**
 * @brief     Give semaphore.
 * @param[in] semaphore_id is the semaphore id after create.
 * @return    None.
 */
void bt_os_layer_give_semaphore(uint32_t semaphore_id);

/**
 * @brief     Delete semaphore.
 * @param[in] semaphore_id is the semaphore id after create.
 * @return    None.
 */
void bt_os_layer_delete_semaphore(uint32_t semaphore_id);

/**
 * @brief     Get system tick.
 * @return    Tick count.
 */
uint32_t bt_os_layer_get_system_tick(void);

/**
 * @brief     Register the timer callback function.
 * @param[in] callback is the function pointer.
 * @return    None.
 */
void bt_os_layer_register_timer_callback(bt_os_layer_timer_expired_t callback);

/**
 * @brief     Check if the timer is active.
 * @return    1 means active while 0 is not active.
 */
uint32_t bt_os_layer_is_timer_active(void);

/**
 * @brief     Start the timer.
 * @param[in] ms is the timer expire time.
 * @return    None.
 */
void bt_os_layer_start_timer(uint32_t ms);

/**
 * @brief     Stop the timer.
 * @return    None.
 */
void bt_os_layer_stop_timer(void);

/**
 * @brief     Enable the interrupt.
 * @return    None.
 */
void bt_os_layer_enable_interrupt(void);

/**
 * @brief     Disable the interrupt.
 * @return    None.
 */
void bt_os_layer_disable_interrupt(void);

/**
 * @brief     Disable the system sleep.
 * @return    None.
 */
void bt_os_layer_disable_system_sleep(void);

/**
 * @brief     Enable the system sleep.
 * @return    None.
 */
void bt_os_layer_enable_system_sleep(void);

/**
 * @brief     Generate a random number.
 * @return    Random value.
 */
uint16_t bt_os_layer_generate_random(void);

/**
 * @brief      AES encrypt function.
 * @param[out] encrypted_data is the text data after encrypted, refer to bt_os_layer_aes_buffer_t for more details.
 * @param[in]  plain_text is the original text data, refer to bt_os_layer_aes_buffer_t for more details.
 * @param[in]  key is the structure of key, refer to bt_os_layer_aes_buffer_t for more details. 
 * @return     None.
 */
void bt_os_layer_aes_encrypt(bt_os_layer_aes_buffer_t* encrypted_data, bt_os_layer_aes_buffer_t* plain_text, bt_os_layer_aes_buffer_t* key);

/**
 * @brief      Memory copy from source buffer to destination buffer.
 * @param[out] dest is destination buffer.
 * @param[in]  src is source buffer.
 * @param[in]  size is buffer size. 
 * @return     Buffer pointer which is same as dest.
 */
void* bt_os_layer_memcpy(void* dest, const void* src, uint32_t size);

/**
 * @brief     Memory compare between buffer1 and buffer2.
 * @param[in] buf1 is first buffer.
 * @param[in] buf2 is second buffer.
 * @param[in] size is buffer size. 
 * @return    0 means both buffers are same and other value means both buffers are different.
 */
int bt_os_layer_memcmp(const void* buf1, const void* buf2, uint32_t size);

/**
 * @brief     Set the memory to a same value.
 * @param[in] buf is first buffer.
 * @param[in] ch is the value which want to set.
 * @param[in] size is buffer size which want to set. 
 * @return    Buffer pointer which is same as buf.
 */
void* bt_os_layer_memset(void* buf, uint8_t ch, uint32_t size);

/**
 * @brief      Memory move from source buffer to destination buffer.
 * @param[out] dest is destination buffer.
 * @param[in]  src is source buffer.
 * @param[in]  size is buffer size which want to move. 
 * @return     Buffer pointer which is same as dest.
 */
void* bt_os_layer_memmove(void* dest, const void* src, uint32_t size);

/**
 * @brief     Initialize MD5 algorithm.
 * @param[in] ctx is the context of the MD5.
 * @return    None.
 */
void bt_os_layer_md5_init(bt_os_md5_context *ctx);

/**
 * @brief     Reset the MD5 context.
 * @param[in] ctx is the context of the MD5.
 * @return    None.
 */
void bt_os_layer_md5_free(bt_os_md5_context *ctx);

/**
 * @brief     Clone the MD5 context from source to destination.
 * @param[in] dst is the destination context pointer.
 * @param[in] src is the source context pointer.
 * @return    None.
 */
void bt_os_layer_md5_clone(bt_os_md5_context *dst, const bt_os_md5_context *src);

/**
 * @brief     Start MD5 algorithm, set initial value.
 * @param[in] ctx is the context of the MD5.
 * @return    None.
 */
void bt_os_layer_md5_starts(bt_os_md5_context *ctx); 

/**
 * @brief     Perform MD5 algorithm.
 * @param[in] ctx is the context of the MD5.
 * @param[in] data is used for the process.
 * @return    None.
 */
void bt_os_layer_md5_process(bt_os_md5_context *ctx, const unsigned char data[64]);

/**
 * @brief     Add string to the calculation.
 * @param[in] ctx is the context of the MD5.
 * @param[in] input is the pointer of added string.
 * @param[in] ilen is the length of the added string.
 * @return    None.
 */
void bt_os_layer_md5_update(bt_os_md5_context *ctx, const unsigned char *input, unsigned int ilen);


/**
 * @brief     Perform MD5 algorithm.
 * @param[in] ctx is the context of the MD5.
 * @param[in] output is the result of the MD5 calculation.
 * @return    None.
 */
void bt_os_layer_md5_finish(bt_os_md5_context *ctx, unsigned char output[16]);

/**
 * @brief This function initializes the specific device such as UART or USB.
 * @param[in] device is the Serial Port Service device. 
 * @param[in] para specifies the callback function. It cannot be NULL.
 * @param[out] handle is the serial port handle for the Serial Port Service.
 * @return    int16_t
 */
int16_t bt_os_layer_serial_port_open(uint16_t device, void *para, uint32_t *handle);

/**
 * @brief This function de-initializes a specific device after
 *        using the device to release the resources for other users.
 * @param[in] handle is the serial port handle for the Serial Port Service.
 * @return    int16_t
*/
int16_t bt_os_layer_serial_port_close(uint32_t handle);

/**
 * @brief This function controls a specific device to read or write data or
 *        perform other operations supported by the device. This API must be called
 *        after bt_os_layer_serial_port_open(). User should specify the device with serial port handle.
 *        User must also define its callback to handle events reported by the Serial Port Service.
 * @param[in] handle is the serial port handle for the Serial Port Service.
 * @param[in] command is the command corresponding to a specific parameter. 
 * @param[in] para specifies the parameter corresponding to a specific command.
 * @return    int16_t
 */
int16_t bt_os_layer_serial_port_control(uint32_t handle, uint8_t command, void *para);

/**
 * @brief       This function sets up a sleep handle to control the sleep state of the system. \n
 *              This handle enables the Sleep Manager to identify the sleep states based on the sleep handles assigned.
 * @param[in]   handle_name is the name of the sleep handle of type string.
 * @return      The sleep handle index, if the operation is successful. If (0xFF) is returned, the operation failed.
 */
uint8_t bt_os_layer_sleep_manager_set_sleep_handle(const char *handle_name);

/**
 * @brief       This function releases the sleep handle if it is no longer in use. \n
 * @param[in]   handle_index is the sleep handle index returned from #bt_os_layer_sleep_manager_set_sleep_handle(). \n
 * @return      #HAL_SLEEP_MANAGER_OK, if this function completed successfully.
 * @note        Call #bt_os_layer_sleep_manager_set_sleep_handle() to set up the sleep handle, before calling this function.
 */
uint8_t bt_os_layer_sleep_manager_release_sleep_handle(uint8_t handle);

/**
 * @brief       This function prevents the MCU from getting into sleep mode.
 * @param[in]   handle_index is the sleep handle index, returned from #bt_os_layer_sleep_manager_set_sleep_handle().
 * @return      #HAL_SLEEP_MANAGER_OK, Sleep Lock is locked.
 * @note        Call #bt_os_layer_sleep_manager_set_sleep_handle() to set up the sleep handle, before calling this function.
 */
uint8_t bt_os_layer_sleep_manager_lock_sleep(uint8_t handle_index);

/**
 * @brief       This function unlocks the specific Sleep Lock and permits the MCU going into sleep mode when needed if all Sleep Locks are unlocked.
 * @param[in]   handle_index is the sleep handle index returned from #bt_os_layer_sleep_manager_set_sleep_handle().
 * @return      #HAL_SLEEP_MANAGER_OK, sleep lock is unlocked.
 * @note         Call #bt_os_layer_sleep_manager_set_sleep_handle() to set up the sleep handle, before calling this function.
 */
uint8_t bt_os_layer_sleep_manager_unlock_sleep(uint8_t handle_index);

/**
 * @brief       This function checks if the isr is running.
 * @param[in]   void.
 * @return      bool.
 */
bool bt_os_layer_is_isr_active(void);
#endif /* __BT_OS_LAYER_API_H__ */

