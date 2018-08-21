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

/* System Header file */
#include "FreeRTOS.h"
#include "task.h"
#include "hal_uart.h"
#include "syslog.h"
#include "atci_adapter.h"
#include "atci_main.h"

#include "at_command.h"
#include "memory_attribute.h"
#include <string.h>
#include <stdio.h>

log_create_module(atci, PRINT_LEVEL_INFO);
#define LOGE(fmt,arg...)   LOG_E(atci, "ATCI main: "fmt,##arg)
#define LOGW(fmt,arg...)   LOG_W(atci, "ATCI main: "fmt,##arg)
#define LOGI(fmt,arg...)   LOG_I(atci ,"ATCI main: "fmt,##arg)

#define _unused(x) ((void)x)

/* ATCI main body related */
hal_uart_port_t g_atci_uart_port = HAL_UART_MAX;

uint8_t  g_atci_local_startup_flag = 0;
uint32_t g_atci_handler_mutex = NULL;
uint32_t g_atci_handler_semaphore = NULL;
uint32_t g_atci_input_command_queue = NULL;
uint32_t g_atci_resonse_command_queue = NULL;
uint32_t g_atci_registered_table_number = 0;
uint32_t atci_input_commad_in_processing = 0;

atci_cmd_hdlr_table_t g_atci_cm4_general_hdlr_tables[ATCI_MAX_GNENERAL_TABLE_NUM];

static uint32_t atci_input_commad_data_in_used = 0;
static atci_send_input_cmd_msg_t   g_input_command[1];




typedef struct {
    char    uart_rx_buff[ATCI_UART_RX_FIFO_BUFFER_SIZE];
    char    uart_tx_buff[ATCI_UART_TX_FIFO_BUFFER_SIZE];
} atci_uart_cntx_st;

typedef enum {
    CMD_FROM_NONE,
    CMD_FROM_UART,
    CMD_FROM_SPP,
} atci_cmd_source;


atci_cmd_source atci_input_command_data_source = CMD_FROM_NONE;
int32_t g_atci_spp_port = 0;
atci_send_data_by_spp_callback atci_send_data_cb = NULL;


static atci_uart_cntx_st  ATTR_ZIDATA_IN_NONCACHED_RAM_4BYTE_ALIGN  g_atci_uart_cntx;

static atci_status_t atci_uart_init(hal_uart_port_t port);
static uint32_t  atci_uart_read_data(hal_uart_port_t uart_index, uint8_t *buf, uint32_t buf_len);
static atci_status_t  atci_uart_write_data(hal_uart_port_t uart_index, uint8_t *buf, uint32_t buf_len);
static void atci_uart_irq(hal_uart_callback_event_t status, void *parameter);
atci_status_t atci_uart_response_callback(atci_response_t *resonse_msg);
atci_status_t atci_response_callback(atci_response_t *response_msg);
//atci_status_t atci_spp_deinit(int32_t port);
void atci_set_cmd_source(atci_cmd_source data_source);
atci_cmd_source atci_get_cmd_source(void);

atci_status_t atci_spp_response_callback(atci_response_t *response_msg);
atci_status_t atci_response_callback(atci_response_t *response_msg);
atci_status_t atci_local_deinit(void);


/* ATCI main body related */
atci_status_t atci_local_init(void)
{
    uint16_t i;
    atci_status_t ret =  ATCI_STATUS_ERROR;
    /* Init Mutex */

    if (g_atci_local_startup_flag == 1) {

        return ATCI_STATUS_OK;
    }

    if (NULL == (void *)g_atci_handler_mutex) {

        g_atci_handler_mutex = atci_mutex_create();
        if (NULL == (void *)g_atci_handler_mutex) {
            return ret;
        }
    }

    if (NULL == (void *)g_atci_handler_semaphore) {

        g_atci_handler_semaphore = atci_semaphore_create(10, 0);
        if (NULL == (void *)g_atci_handler_semaphore) {
            return ret;
        }
    }

    g_atci_registered_table_number = 0;
    for (i = 0; i < ATCI_MAX_GNENERAL_TABLE_NUM; i++) {
        g_atci_cm4_general_hdlr_tables[i].item_table = NULL;
        g_atci_cm4_general_hdlr_tables[i].item_table_size = 0;
    }

    /* Init Queue */
    if (NULL == (void *)g_atci_input_command_queue) {
        g_atci_input_command_queue = atci_queue_create(ATCI_LOCAL_QUEUE_LENGTH, sizeof(atci_general_msg_t));
        if (NULL == (void *)g_atci_input_command_queue) {
            return ret;
        }
    }

    if (NULL == (void *)g_atci_resonse_command_queue) {
        g_atci_resonse_command_queue = atci_queue_create(ATCI_LOCAL_QUEUE_LENGTH, sizeof(atci_general_msg_t));
        if (NULL == (void *)g_atci_resonse_command_queue) {
            return ret;
        }
    }

    atci_input_commad_data_in_used = 0;
    atci_input_commad_in_processing = 0;
    atci_set_cmd_source(CMD_FROM_NONE);

    g_atci_local_startup_flag = 1;

    ret =  ATCI_STATUS_OK;
    LOGI("atci_local_init() success \r\n");
    return ret;
}


/* This function can't be reentry. It should be executed completely and than invoke this function again. */
void atci_processing(void)
{
    /* Queue number */
    uint16_t            common_queue_msg_num = 0;
    uint16_t            notify_queue_msg_num = 0;
    atci_general_msg_t msg_queue_data;

    LOGW("atci_processing() flag:%d\r\n", g_atci_local_startup_flag);

    if (g_atci_local_startup_flag == 0) {

        return;
    }

    while (1) {

        atci_semaphore_take(g_atci_handler_semaphore);
		memset(&msg_queue_data, 0, sizeof(atci_general_msg_t));

        common_queue_msg_num = atci_queue_get_item_num(g_atci_input_command_queue);

        LOGW("atci_processing() common_queus_msg_num:%d atci_input_commad_in_processing=%d\r\n", common_queue_msg_num, atci_input_commad_in_processing);

        /*
         * We are handling AT command one by one. Need to wait the previous AT command response and then handle the next one.
         * atci_input_commad_in_processing means the response of AT command was resonse or not.
         * When atci_input_commad_in_processing = 0, we could handle the next AT command
         *
         * atci_input_commad_data_in_used means g_input_command is using. In atci_uart_irq(), using this varaible to read AT command
         */
        if ((0 == atci_input_commad_in_processing) &&
                (common_queue_msg_num > 0)) {

            atci_queue_receive_no_wait(g_atci_input_command_queue, &msg_queue_data);

            /* message handling */
            if (MSG_ID_ATCI_LOCAL_SEND_CMD_IND == msg_queue_data.msg_id) {

                /* handling someone AT command. Need to wait the response and then could handle the next AT command */
                LOGW("atci_processing() handle AT input\r\n");
                atci_input_commad_in_processing = 1;
                atci_input_command_handler((atci_send_input_cmd_msg_t *)(msg_queue_data.msg_data));
                /* g_input_command is available now */
                memset(&g_input_command, 0, sizeof(atci_send_input_cmd_msg_t));
            }
            common_queue_msg_num--;
        }

        notify_queue_msg_num = atci_queue_get_item_num(g_atci_resonse_command_queue);
		LOGW("atci_processing() notify_queue_msg_num:%d atci_input_commad_in_processing=%d\r\n", notify_queue_msg_num, atci_input_commad_in_processing);

        while (notify_queue_msg_num > 0) {
			memset(&msg_queue_data, 0, sizeof(atci_general_msg_t));
			LOGW("atci_processing() notify_queue_msg_num:%d \r\n", notify_queue_msg_num);
			
            if( atci_queue_receive_no_wait(g_atci_resonse_command_queue, &msg_queue_data))
            {
				if(msg_queue_data.msg_data != NULL && 
					(msg_queue_data.msg_id == MSG_ID_ATCI_LOCAL_URC_NOTIFY_IND || msg_queue_data.msg_id == MSG_ID_ATCI_LOCAL_RSP_NOTIFY_IND))
				{
					atci_response_t* response_buf = (atci_response_t *)(msg_queue_data.msg_data);
					/* the message handling. Sending response or URC to UART */
					atci_response_callback((atci_response_t *)(msg_queue_data.msg_data));
					/* free the message content */

					if(response_buf->response_buf != NULL && response_buf->response_len != 0)
					{
						atci_mem_free(msg_queue_data.msg_data);
						msg_queue_data.msg_data = NULL;
					}

					if (MSG_ID_ATCI_LOCAL_RSP_NOTIFY_IND == msg_queue_data.msg_id) {
						/* the response resonse of handling AT command is finished . allow to handle the next AT command */
						atci_input_commad_in_processing = 0;
						atci_input_commad_data_in_used = 0;
						LOGW("atci_processing() handle AT response, addr:0x%x\r\n", msg_queue_data.msg_data);
					}
					else
						LOGW("atci_processing() handle AT urc, addr:0x%x\r\n", msg_queue_data.msg_data);
				}

				notify_queue_msg_num--;
			}
        }
    }

}

atci_status_t atci_init(hal_uart_port_t port)
{
    /* Init */
    atci_status_t ret = ATCI_STATUS_ERROR;

    if ((ATCI_STATUS_OK == atci_local_init()) && (ATCI_STATUS_OK == atci_uart_init(port))) {

        ret = ATCI_STATUS_OK;
        if (ATCI_STATUS_ERROR == at_command_init()) {
            LOGW("at_command_init() register fail \r\n");
        }
    }

    if (ret == ATCI_STATUS_OK) {

        LOGW("atci_init() success \r\n");
    } else {

        ret = ATCI_STATUS_ERROR;
        atci_local_deinit();
        LOGW("atci_init() fail \r\n");

    }

    return ret;
}

uint8_t atci_check_startup_finish(void)
{
    uint8_t is_finish = 0;

    if (g_atci_local_startup_flag) {
        is_finish = 1;
    }
    return is_finish;
}

atci_status_t atci_response_callback(atci_response_t *response_msg)
{
    atci_status_t ret = ATCI_STATUS_ERROR;
	LOGW("atci_response_callback() enter len:%d, msg_ptr:0x%x \r\n", response_msg->response_len, response_msg->response_buf);
	if(response_msg->response_buf == NULL || response_msg->response_len == 0)
	{
		LOGW("atci_response_callback() invaild input param, drop it! \r\n");
		return ret;
	}

    if (atci_get_cmd_source() == CMD_FROM_UART) {

        ret = atci_uart_response_callback(response_msg);
        atci_set_cmd_source(CMD_FROM_NONE);

    } else if (atci_get_cmd_source() == CMD_FROM_SPP) {

        ret = atci_spp_response_callback(response_msg);
        atci_set_cmd_source(CMD_FROM_NONE);

    } else {

        // for urc type data only
        if (g_atci_uart_port != HAL_UART_MAX) {

            ret = atci_uart_response_callback(response_msg);
        }

        if (atci_send_data_cb != NULL) {

            ret = atci_spp_response_callback(response_msg);
        }

    }
    return ret;
}

/* UART related */
atci_status_t atci_uart_response_callback(atci_response_t *response_msg)
{
    atci_status_t ret = ATCI_STATUS_ERROR;

    /* write resonse data from atci_response_t to UART  */
    ret = atci_uart_write_data(g_atci_uart_port, response_msg->response_buf, response_msg->response_len);

    //LOGW("call atci_uart_response_callback, ret=%d \r\n", ret);
    if (ret == ATCI_STATUS_OK) {

        LOGW("uart_response_callback() success \r\n");
    } else {
        LOGW("uart_response_callback() fail \r\n");
    }
    return ret;
}


/*------ Extern function Entity ------*/
static atci_status_t atci_uart_init(hal_uart_port_t port)
{
    hal_uart_config_t uart_config;
    hal_uart_dma_config_t dma_config;
    atci_status_t ret = ATCI_STATUS_ERROR;

    LOGW("atci_uart_init, port=%d \r\n", port);

    if (port == HAL_UART_MAX) {
        return ret;
    }

    //LOGW("atci_uart_init \r\n");

    /* Configure UART PORT */
    uart_config.baudrate = HAL_UART_BAUDRATE_115200;
    uart_config.parity = HAL_UART_PARITY_NONE;
    uart_config.stop_bit = HAL_UART_STOP_BIT_1;
    uart_config.word_length = HAL_UART_WORD_LENGTH_8;

    g_atci_uart_port = port;
    LOGW("call hal_uart_init,port=%d \r\n", port);
    if (HAL_UART_STATUS_OK != hal_uart_init(port, &uart_config)) {
        // log: uart init success
        LOGW("hal_uart_init fail\r\n");
        ret = ATCI_STATUS_ERROR;
    } else {
        // log: uart init fail
        LOGW("hal_uart_init success \n");
        ret = ATCI_STATUS_OK;
        dma_config.receive_vfifo_alert_size = ATCI_UART_RX_FIFO_ALERT_SIZE;
        dma_config.receive_vfifo_buffer = (uint8_t *)g_atci_uart_cntx.uart_rx_buff;
        dma_config.receive_vfifo_buffer_size = ATCI_UART_RX_FIFO_BUFFER_SIZE;
        dma_config.receive_vfifo_threshold_size = ATCI_UART_RX_FIFO_THRESHOLD_SIZE;
        dma_config.send_vfifo_buffer = (uint8_t *)g_atci_uart_cntx.uart_tx_buff;
        dma_config.send_vfifo_buffer_size = ATCI_UART_TX_FIFO_BUFFER_SIZE;
        dma_config.send_vfifo_threshold_size = ATCI_UART_TX_FIFO_THRESHOLD_SIZE;

        hal_uart_set_dma(port, &dma_config);
        hal_uart_register_callback(port, atci_uart_irq, NULL);
    }

    return ret;
}


static uint32_t atci_uart_read_data(hal_uart_port_t uart_index, uint8_t *buf, uint32_t buf_len)
{
#define EARLY_ACCESS_7687EVB_TEST
#ifdef EARLY_ACCESS_7687EVB_TEST
    uint32_t available_data_len = 0;
    available_data_len = hal_uart_get_available_receive_bytes(uart_index);
    if (available_data_len > buf_len) {
        available_data_len = buf_len;
    }
    hal_uart_receive_dma(uart_index, (uint8_t *)buf, available_data_len);
    return available_data_len;
#else
    return hal_uart_receive_dma(uart_index, (uint8_t *)buf, (uint32_t) buf_len);
#endif
}


static atci_status_t atci_uart_write_data(hal_uart_port_t uart_index, uint8_t *buf, uint32_t buf_len)
{
    uint32_t ret_len = 0;
    uint32_t send_len = 0;
    atci_status_t ret = ATCI_STATUS_ERROR;

    if (uart_index == HAL_UART_MAX) {
        return ret;
    }

    if (buf_len > ATCI_UART_TX_FIFO_BUFFER_SIZE) {
        send_len = ATCI_UART_TX_FIFO_BUFFER_SIZE;
    } else {
        send_len = buf_len;
    }

    ret_len = hal_uart_send_dma(uart_index, buf, send_len);

    if (((buf_len > ATCI_UART_TX_FIFO_BUFFER_SIZE) && (ret_len == ATCI_UART_TX_FIFO_BUFFER_SIZE)) ||
            (ret_len == buf_len)) {

        ret = ATCI_STATUS_OK;
    }

    return ret;
}


void atci_uart_irq(hal_uart_callback_event_t event, void *parameter)
{
    char     temp[16];
    uint32_t  length;
    uint32_t find_valid_command = 0;
    atci_general_msg_t msg_queue_item;
    atci_response_t   response = {{0}};
    atci_send_input_cmd_msg_t   g_receive_command[1];

    LOGW("atci_uart_irq, hal_uart_cb_event: %d \r\n", event);
    _unused(find_valid_command);
    memset(&g_receive_command, 0, sizeof(atci_send_input_cmd_msg_t));

    if (g_atci_uart_port == 0) {

        LOGW("atci_read_data_via_spp, invaild uart port:%d\r\n", g_atci_uart_port);
        return;
    }

    if (HAL_UART_EVENT_READY_TO_READ == event) {
        /* atci_input_commad_data_in_used = 0; g_input_command is available */
        if (1 == atci_input_commad_data_in_used) {
            /* drop the data */
            do {
                length = atci_uart_read_data(g_atci_uart_port, (uint8_t *)temp, sizeof(temp));
            } while (length == sizeof(temp));

            /* input AT command is too fast and returns "ERROR" directly. Set Output Buffer Param */
            sprintf((char *)response.response_buf, "ERROR, need wait the response of previous AT cmd to input the next cmd!\r\n");
            response.response_len = strlen((char *)response.response_buf);
            atci_uart_response_callback(&response);

        } else {

            if (atci_get_cmd_source() == CMD_FROM_SPP) {

                /* drop the data */

                /* current receiving input AT command just for uart, so returns "ERROR" directly.*/
                sprintf((char *)response.response_buf, "ERROR, please wait for finishing the cmd from SPP!\r\n");
                response.response_len = strlen((char *)response.response_buf);
                atci_uart_response_callback(&response);
                return;

            } else if (atci_get_cmd_source() == CMD_FROM_NONE) {

                atci_set_cmd_source(CMD_FROM_UART);

            }

            g_receive_command->input_len = (uint16_t)atci_uart_read_data(g_atci_uart_port, (uint8_t *)g_receive_command->input_buf, ATCI_UART_RX_FIFO_BUFFER_SIZE);

            /* append current receive data to the input buffer*/
            if ((g_receive_command->input_len + g_input_command->input_len) < ATCI_UART_RX_FIFO_BUFFER_SIZE) {

                memcpy((g_input_command->input_buf + g_input_command->input_len), (char *)g_receive_command->input_buf, g_receive_command->input_len);
                g_input_command->input_len += g_receive_command->input_len;
                LOGW("current input cmd (len:%d):%s\r\n", g_input_command->input_len, g_input_command->input_buf);

            } else {

                /*invild command, input cmd is larger then max len, need drop this cmd*/
                atci_input_commad_data_in_used = 0;
                memset(&g_input_command, 0, sizeof(atci_send_input_cmd_msg_t));
                //printf("atci_uart_irq, receive data len (%d) is larger than max len, drop this cmd\r\n", g_receive_command->input_len);

                sprintf((char *)response.response_buf, "ERROR, Input data len(%d) is larger than max len, drop this cmd!\r\n", g_input_command->input_len);
                response.response_len = strlen((char *)response.response_buf);
                atci_uart_response_callback(&response);

                return;
            }

            /* find '\0'/CR/LF to be the end of AT command */
            for (length = 0; length < g_input_command->input_len; length++) {
                if (('\0' == g_input_command->input_buf[length]) ||
                        (ATCI_CR_C == g_input_command->input_buf[length]) ||
                        (ATCI_LF_C == g_input_command->input_buf[length])) {

                    find_valid_command = 1;
                    break;
                }
            }

            if (find_valid_command == 1) {

                /* find "AT" to be the beginning of AT command */
                if (('A' == g_input_command->input_buf[0] && 'T' == g_input_command->input_buf[1]) ||
                        ('a' == g_input_command->input_buf[0] && 't' == g_input_command->input_buf[1])) {

                    atci_input_commad_data_in_used = 1;

                } else {

                    atci_input_commad_data_in_used = 0;
                    memset(&g_input_command, 0, sizeof(atci_send_input_cmd_msg_t));
                    //printf("atci_uart_irq, receive data is not AT cmd, drop this cmd\r\n");

                    sprintf((char *)response.response_buf, "ERROR, receive data is not AT cmd type, drop this cmd!\r\n");
                    response.response_len = strlen((char *)response.response_buf);
                    atci_uart_response_callback(&response);

                    return;
                }

            }

            /* send the message to g_atci_local_common_queue */
            if (atci_input_commad_data_in_used == 1) {

                msg_queue_item.msg_id = MSG_ID_ATCI_LOCAL_SEND_CMD_IND;
                msg_queue_item.msg_data = (void *)g_input_command;
                atci_queue_send_from_isr(g_atci_input_command_queue, (void *)&msg_queue_item);
                atci_semaphore_give(g_atci_handler_semaphore);

            }
        }
    } else if (HAL_UART_EVENT_READY_TO_WRITE == event) {
        // do nothing
    }
}


static atci_status_t atci_uart_deinit(hal_uart_port_t port)
{
    hal_uart_status_t uart_ret = HAL_UART_STATUS_ERROR;
    atci_status_t ret = ATCI_STATUS_ERROR;

    if (port == HAL_UART_MAX) {
        return ret;
    }

    uart_ret = hal_uart_deinit(port);

    LOGW("atci_uart_deinit() uart_ret = %d \r\n", uart_ret);

    if (uart_ret == HAL_UART_STATUS_OK) {

        ret = ATCI_STATUS_OK;
    }

    g_atci_uart_port = HAL_UART_MAX;
    return ret;
}

void atci_processing_for_deinit()
{
    /* Queue number */
  //  uint16_t            common_queue_msg_num = 0;
    uint16_t            notify_queue_msg_num = 0;
    atci_general_msg_t msg_queue_data;

    if (g_atci_local_startup_flag == 0) {

        return;
    }

    notify_queue_msg_num = atci_queue_get_item_num(g_atci_resonse_command_queue);

    while (notify_queue_msg_num > 0) {
        atci_queue_receive_no_wait(g_atci_resonse_command_queue, &msg_queue_data);

        /* the message handling. Sending response or URC to UART */
        atci_response_callback((atci_response_t *)(msg_queue_data.msg_data));
        /* free the message content */
        atci_mem_free(msg_queue_data.msg_data);

        if (MSG_ID_ATCI_LOCAL_RSP_NOTIFY_IND == msg_queue_data.msg_id) {
            /* the response resonse of handling AT command is finished . allow to handle the next AT command */
            atci_input_commad_in_processing = 0;
            LOGW("atci_local_deinit() handle AT response\r\n");
        }

        notify_queue_msg_num--;

    }

}


atci_status_t atci_local_deinit(void)
{
    /* Queue number */
    atci_status_t ret =  ATCI_STATUS_ERROR;
    uint16_t i;
	LOGW("atci_local_deinit() enter \r\n");

    if (g_atci_local_startup_flag == 0) {

        return ATCI_STATUS_OK;
    }

    atci_input_commad_data_in_used  = 0;
    atci_input_commad_in_processing = 0;

    g_atci_registered_table_number = 0;
    for (i = 0; i < ATCI_MAX_GNENERAL_TABLE_NUM; i++) {
        g_atci_cm4_general_hdlr_tables[i].item_table = NULL;
        g_atci_cm4_general_hdlr_tables[i].item_table_size = 0;
    }

	atci_queue_delete(g_atci_input_command_queue);
	atci_queue_delete(g_atci_resonse_command_queue);
	g_atci_input_command_queue   = 0;
	g_atci_resonse_command_queue = 0;

	atci_semaphore_delete(g_atci_handler_semaphore);
	g_atci_handler_semaphore = 0;

    g_atci_local_startup_flag = 0;
    atci_set_cmd_source(CMD_FROM_NONE);

    ret = ATCI_STATUS_OK;
    LOGW("atci_local_deinit() done \r\n");
    return ret;
}


atci_status_t atci_deinit(hal_uart_port_t port)
{
    /* Init */
    atci_status_t ret = ATCI_STATUS_ERROR;

    LOGW("atci_deinit() enter (flag:%d)\r\n", g_atci_local_startup_flag);

    if ((g_atci_local_startup_flag == 0) || (g_atci_uart_port == HAL_UART_MAX)) {

        return ATCI_STATUS_OK;
    }

    atci_processing_for_deinit();

    if (atci_send_data_cb == NULL) {
        ret = atci_local_deinit();
    }

    ret = atci_uart_deinit(g_atci_uart_port);

    g_atci_uart_port = HAL_UART_MAX;

    if (ret == ATCI_STATUS_OK) {

        LOGW("atci_deinit() success \r\n");
    } else {

        ret = ATCI_STATUS_ERROR;
        LOGW("atci_deinit() fail \r\n");

    }

    return ret;
}




/* spp related */
atci_status_t atci_spp_response_callback(atci_response_t *response_msg)
{
    int32_t real_sent_size = -1;
//    uint32_t total_size = 0;
    // uint8_t app_data[TOTAL_SIZE] = {1};
    atci_status_t ret = ATCI_STATUS_ERROR;
	LOGW("atci_spp_response_callback() add:0x%x (len:%d) \r\n", response_msg, response_msg->response_len);

    if (atci_send_data_cb != NULL) {
        real_sent_size = atci_send_data_cb(response_msg->response_len, response_msg->response_buf);
    }


    if (real_sent_size == 0) {
        ret = ATCI_STATUS_OK;
        LOGW("atci_spp_response_callback() success \r\n");
    } else {
        LOGW("atci_spp_response_callback() fail \r\n");
        ret = ATCI_STATUS_ERROR;
    }
    return ret;
}




/*------ Extern function Entity ------*/
atci_status_t atci_init_by_spp(atci_send_data_by_spp_callback cb)
{
    /* Init */
    atci_status_t ret = ATCI_STATUS_ERROR;

    if (atci_send_data_cb != NULL) {
        return ATCI_STATUS_OK;
    }

    if ((ATCI_STATUS_OK == atci_local_init()) && (cb != NULL)) {

        atci_send_data_cb = cb;
        ret = ATCI_STATUS_OK;
        //ret = at_command_init();
        if (ATCI_STATUS_ERROR == at_command_init()) {
            LOGW("at_command_init() register fail \r\n");
        }
    }

    if (ret == ATCI_STATUS_OK) {

        LOGW("atci_init_by_spp() success \r\n");
    } else {

        ret = ATCI_STATUS_ERROR;
        LOGW("atci_init_by_spp() fail \r\n");

    }

    return ret;
}


void atci_set_cmd_source(atci_cmd_source data_source)
{
    atci_input_command_data_source = data_source;
}

atci_cmd_source atci_get_cmd_source(void)
{
    return atci_input_command_data_source;
}

void atci_receive_data_by_spp(uint8_t *data_buf, uint32_t data_len)
{
//    char     temp[16];
    int32_t  length;
    uint32_t find_valid_command = 0;
    atci_general_msg_t msg_queue_item;
    atci_response_t   response = {{0}};


    LOGW("atci_receive_data_by_spp, input cmd (len:%d):%s\r\n", data_len, data_buf);
    _unused(find_valid_command);

    if (atci_send_data_cb == 0) {

        LOGW("atci_receive_data_by_spp, atci_init_by_spp init fail\r\n");
        return;
    }

    /* atci_input_commad_data_in_used = 0; g_input_command is available */
    if (1 == atci_input_commad_data_in_used) {
        /* drop the data */

        /* input AT command is too fast and returns "ERROR" directly. Set Output Buffer Param */
		LOGW("atci_receive_data_by_spp, ERROR, need wait previous AT cmd\r\n");
        sprintf((char *)response.response_buf, "ERROR, need wait the response of previous AT cmd (from:%d)!\r\n", atci_get_cmd_source());
        response.response_len = strlen((char *)response.response_buf);
        atci_spp_response_callback(&response);

    } else {

        if (atci_get_cmd_source() == CMD_FROM_UART) {

            /* drop the data */

            /* current receiving input AT command just for uart, so returns "ERROR" directly.*/
            sprintf((char *)response.response_buf, "ERROR, please wait for finishing the cmd from UART!\r\n");
            response.response_len = strlen((char *)response.response_buf);
            atci_spp_response_callback(&response);
            return;

        } else if (atci_get_cmd_source() == CMD_FROM_NONE) {

            atci_set_cmd_source(CMD_FROM_SPP);

        }


        /* append current receive data to the input buffer*/
        if ((data_len + g_input_command->input_len) < ATCI_UART_RX_FIFO_BUFFER_SIZE) {

            memcpy((char *)g_input_command->input_buf + g_input_command->input_len, (uint8_t *)data_buf, data_len);
            g_input_command->input_len += data_len;
            LOGW("atci_receive_data_by_spp() current input cmd (len:%d):%s\r\n", g_input_command->input_len, g_input_command->input_buf);

        } else {

            /*invild command, input cmd is larger then max len, need drop this cmd*/
            atci_input_commad_data_in_used = 0;
            memset(&g_input_command, 0, sizeof(atci_send_input_cmd_msg_t));
            //printf("atci_uart_irq, receive data len (%d) is larger than max len, drop this cmd\r\n", g_receive_command->input_len);
			LOGW("atci_receive_data_by_spp, ERROR, Input data len larger \r\n");

            sprintf((char *)response.response_buf, "ERROR, Input data len(%d) is larger than max len, drop this cmd!\r\n", g_input_command->input_len);
            response.response_len = strlen((char *)response.response_buf);
            atci_spp_response_callback(&response);

            return;
        }

        /* find '\0'/CR/LF to be the end of AT command */
        for (length = 0; length < g_input_command->input_len; length++) {
            if (('\0' == g_input_command->input_buf[length]) ||
                    (ATCI_CR_C == g_input_command->input_buf[length]) ||
                    (ATCI_LF_C == g_input_command->input_buf[length])) {

                find_valid_command = 1;
                break;
            }
        }
        LOGW("atci_receive_data_by_spp, parse the tail of cmd(%d)\r\n", find_valid_command);

        if (find_valid_command == 1) {

            /* find "AT" to be the beginning of AT command */
            if (('A' == g_input_command->input_buf[0] && 'T' == g_input_command->input_buf[1]) ||
                    ('a' == g_input_command->input_buf[0] && 't' == g_input_command->input_buf[1])) {

                atci_input_commad_data_in_used = 1;

            } else {
                LOGW("atci_receive_data_by_spp, not a AT CMD return(%d)\r\n", atci_input_commad_data_in_used);

                atci_input_commad_data_in_used = 0;
                memset(&g_input_command, 0, sizeof(atci_send_input_cmd_msg_t));
                //printf("atci_uart_irq, receive data is not AT cmd, drop this cmd\r\n");

                sprintf((char *)response.response_buf, "ERROR, receive data is not AT cmd type, drop this cmd!\r\n");
                response.response_len = strlen((char *)response.response_buf);
                atci_spp_response_callback(&response);

                return;
            }

        }
        LOGW("atci_receive_data_by_spp, send msg to atci task(%d)\r\n", atci_input_commad_data_in_used);
        /* send the message to g_atci_local_common_queue */
        if (atci_input_commad_data_in_used == 1) {

            msg_queue_item.msg_id = MSG_ID_ATCI_LOCAL_SEND_CMD_IND;
            msg_queue_item.msg_data = (void *)g_input_command;
            atci_queue_send_from_isr(g_atci_input_command_queue, (void *)&msg_queue_item);
            atci_semaphore_give(g_atci_handler_semaphore);
        }
    }
}


atci_status_t atci_deinit_by_spp(void)
{
    atci_status_t ret =  ATCI_STATUS_ERROR;

    if ((atci_send_data_cb == NULL) || (g_atci_local_startup_flag == 0)) {
        return ATCI_STATUS_OK;
    }


    atci_processing_for_deinit();

    //if(g_atci_uart_port == HAL_UART_MAX)
    ret = atci_local_deinit();

    atci_send_data_cb = NULL;

    //atci_set_cmd_source(CMD_FROM_NONE);

    if (ret == ATCI_STATUS_OK) {

        LOGW("atci_deinit_by_spp() success \r\n");
    } else {

        ret = ATCI_STATUS_ERROR;
        LOGW("atci_deinit_by_spp() fail \r\n");

    }

    return ret;
}



