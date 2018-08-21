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

#ifndef __HAL_UART_INTERNAL_PLATFORM_H__
#define __HAL_UART_INTERNAL_PLATFORM_H__

#ifdef HAL_UART_MODULE_ENABLED

#ifdef __cplusplus
extern "C" {
#endif

#define UART_INPUT_CLOCK_DCXO 26000000

#define UART_IIR_NONE      (0x1<<UART_IIR_ID_OFFSET) /* No interrupt pending */
#define UART_IIR_LSR       (0x6<<UART_IIR_ID_OFFSET) /* Line Status Interrupt */
#define UART_IIR_RDT       (0x0C<<UART_IIR_ID_OFFSET) /* RX Data Timeout */
#define UART_IIR_RDR       (0x4<<UART_IIR_ID_OFFSET) /* RX Data Received */
#define UART_IIR_THRE      (0x2<<UART_IIR_ID_OFFSET) /* TX Holding Register Empty */
#define UART_IIR_RCVXOFF   (0x10<<UART_IIR_ID_OFFSET) /* Software Flow Control */
#define UART_IIR_CTSRTS    (0x20<<UART_IIR_ID_OFFSET) /* Hardware Flow Control */
#define UART_FCR_RXTRIG_1           (0x0<<UART_FCR_RFTL1_RFTL0_OFFSET) /* RX FIFO trigger = 1 */
#define UART_FCR_RXTRIG_6       (0x1<<UART_FCR_RFTL1_RFTL0_OFFSET) /* RX FIFO trigger = 6 */
#define UART_FCR_RXTRIG_12      (0x2<<UART_FCR_RFTL1_RFTL0_OFFSET) /* RX FIFO trigger = 12 */
#define UART_FCR_RXTRIG_USER    (0x3<<UART_FCR_RFTL1_RFTL0_OFFSET) /* RX FIFO trigger = RXTRIG */
#define UART_FCR_TXTRIG_1       (0x0<<UART_FCR_TFTL1_TFTL0_OFFSET) /* RX FIFO trigger = 1 */
#define UART_FCR_TXTRIG_4       (0x1<<UART_FCR_TFTL1_TFTL0_OFFSET) /* RX FIFO trigger = 4 */
#define UART_FCR_TXTRIG_8       (0x2<<UART_FCR_TFTL1_TFTL0_OFFSET) /* RX FIFO trigger = 8 */
#define UART_FCR_TXTRIG_14      (0x3<<UART_FCR_TFTL1_TFTL0_OFFSET) /* RX FIFO trigger = 14 */
#define UART_EFR_SW_FLOW_TX_ON      (0x2<<UART_EFR_SW_FLOW_TX_OFFSET)
#define UART_EFR_SW_FLOW_TX_OFF     (0x0<<UART_EFR_SW_FLOW_TX_OFFSET)
#define UART_EFR_SW_FLOW_RX_ON      (0x2<<UART_EFR_SW_FLOW_RX_OFFSET)
#define UART_EFR_SW_FLOW_RX_OFF     (0x0<<UART_EFR_SW_FLOW_RX_OFFSET)
#define UART_LCR_EPS_ODD    (0x0<<UART_LCR_EPS_OFFSET) /* Odd Even Parity */
#define UART_LCR_EPS_EVEN   (0x1<<UART_LCR_EPS_OFFSET) /* Even Parity Select */
#define UART_LCR_STB_1      (0x0<<UART_LCR_STB_OFFSET) /* 1 STOP bits */
#define UART_LCR_STB_2      (0x1<<UART_LCR_STB_OFFSET) /* 2 STOP bits */
#define UART_LCR_WORD_5BITS (0x0<<UART_LCR_WORD_OFFSET) /* Word Length = 5BITS */
#define UART_LCR_WORD_6BITS (0x1<<UART_LCR_WORD_OFFSET) /* Word Length = 6BITS */
#define UART_LCR_WORD_7BITS (0x2<<UART_LCR_WORD_OFFSET) /* Word Length = 7BITS */
#define UART_LCR_WORD_8BITS (0x3<<UART_LCR_WORD_OFFSET) /* Word Length = 8BITS */
#define UART_HIGHSPEED_SPEED_MODE0  (0x0<<UART_HIGHSPEED_SPEED_OFFSET)  /* baud_rate = system clock frequency/16/{DLH, DLL} */
#define UART_HIGHSPEED_SPEED_MODE1  (0x1<<UART_HIGHSPEED_SPEED_OFFSET)  /* baud_rate = system clock frequency/8/{DLH, DLL} */
#define UART_HIGHSPEED_SPEED_MODE2  (0x2<<UART_HIGHSPEED_SPEED_OFFSET)  /* baud_rate = system clock frequency/14/{DLH, DLL} */
#define UART_HIGHSPEED_SPEED_MODE3  (0x3<<UART_HIGHSPEED_SPEED_OFFSET)  /* baud_rate = system clock frequency/(sampe_count+1)/{DLM, DLL} */
#define UART_AUTOBAUD_DETECTING             (0x0<<UART_AUTOBAUD_REG_BAUD_STAT_OFFSET)
#define UART_AUTOBAUD_DETECT_AT_7N1 (0x1<<UART_AUTOBAUD_REG_BAUD_STAT_OFFSET)
#define UART_AUTOBAUD_DETECT_AT_7O1 (0x2<<UART_AUTOBAUD_REG_BAUD_STAT_OFFSET)
#define UART_AUTOBAUD_DETECT_AT_7E1 (0x3<<UART_AUTOBAUD_REG_BAUD_STAT_OFFSET)
#define UART_AUTOBAUD_DETECT_AT_8N1 (0x4<<UART_AUTOBAUD_REG_BAUD_STAT_OFFSET)
#define UART_AUTOBAUD_DETECT_AT_8O1 (0x5<<UART_AUTOBAUD_REG_BAUD_STAT_OFFSET)
#define UART_AUTOBAUD_DETECT_AT_8E1 (0x6<<UART_AUTOBAUD_REG_BAUD_STAT_OFFSET)
#define UART_AUTOBAUD_DETECT_at_7N1 (0x7<<UART_AUTOBAUD_REG_BAUD_STAT_OFFSET)
#define UART_AUTOBAUD_DETECT_at_7E1 (0x8<<UART_AUTOBAUD_REG_BAUD_STAT_OFFSET)
#define UART_AUTOBAUD_DETECT_at_7O1 (0x9<<UART_AUTOBAUD_REG_BAUD_STAT_OFFSET)
#define UART_AUTOBAUD_DETECT_at_8N1 (0x0A<<UART_AUTOBAUD_REG_BAUD_STAT_OFFSET)
#define UART_AUTOBAUD_DETECT_at_8E1 (0x0B<<UART_AUTOBAUD_REG_BAUD_STAT_OFFSET)
#define UART_AUTOBAUD_DETECT_at_8O1 (0x0C<<UART_AUTOBAUD_REG_BAUD_STAT_OFFSET)
#define UART_AUTOBAUD_DETECT_FAIL   (0x0D<<UART_AUTOBAUD_REG_BAUD_STAT_OFFSET)
#define UART_AUTOBAUD_DETECT_115200         (0x0<<UART_AUTOBAUD_REG_BAUD_RATE_OFFSET)
#define UART_AUTOBAUD_DETECT_57600          (0x1<<UART_AUTOBAUD_REG_BAUD_RATE_OFFSET)
#define UART_AUTOBAUD_DETECT_38400  (0x2<<UART_AUTOBAUD_REG_BAUD_RATE_OFFSET)
#define UART_AUTOBAUD_DETECT_19200  (0x3<<UART_AUTOBAUD_REG_BAUD_RATE_OFFSET)
#define UART_AUTOBAUD_DETECT_9600   (0x4<<UART_AUTOBAUD_REG_BAUD_RATE_OFFSET)
#define UART_AUTOBAUD_DETECT_4800   (0x5<<UART_AUTOBAUD_REG_BAUD_RATE_OFFSET)
#define UART_AUTOBAUD_DETECT_2400   (0x6<<UART_AUTOBAUD_REG_BAUD_RATE_OFFSET)
#define UART_AUTOBAUD_DETECT_1200   (0x7<<UART_AUTOBAUD_REG_BAUD_RATE_OFFSET)
#define UART_AUTOBAUD_DETECT_300    (0x8<<UART_AUTOBAUD_REG_BAUD_RATE_OFFSET)
#define UART_AUTOBAUD_DETECT_110    (0x9<<UART_AUTOBAUD_REG_BAUD_RATE_OFFSET)
#define UART_RATEFIX_AD_AUTOBAUD_13M    (0x1<<UART_RATEFIX_AD_AUTOBAUD_OFFSET) /* Use 52MHZ as system clock for auto baud detect */
#define UART_RATEFIX_AD_AUTOBAUD_26M    (0x0<<UART_RATEFIX_AD_AUTOBAUD_OFFSET) /* Use 26MHZ/13MHZ as system clock for auto baud detect */
#define UART_RATEFIX_AD_RATE_FIX_13M    (0x1<<UART_RATEFIX_AD_RATE_FIX_OFFSET) /* Use 52MHZ as system clock for UART TX/RX */
#define UART_RATEFIX_AD_RATE_FIX_26M    (0x0<<UART_RATEFIX_AD_RATE_FIX_OFFSET) /* Use 26MHZ/13MHZ as system clock for UART TX/RX */
#define UART_AUTOBAUDSAMPLE_STANDARD_26M    (0x0D<<UART_AUTOBAUDSAMPLE_OFFSET) /* system clk = 26M for autobaud rate detection */
#define UART_AUTOBAUDSAMPLE_STANDARD_13M    (0x6<<UART_AUTOBAUDSAMPLE_OFFSET) /* system clk = 13M for autobaud rate detection */
#define UART_AUTOBAUDSAMPLE_NON_STANDARD    (0x0F<<UART_AUTOBAUDSAMPLE_OFFSET) /* for non-standard baud rate detection. */
#define UART_FCR_RD_RXFIFO_TRIGGER_1        (0x0<<UART_FCR_RD_RXFIFO_TRIGGER_OFFSET) /* RX FIFO trigger threshold = 1 */
#define UART_FCR_RD_RXFIFO_TRIGGER_6        (0x1<<UART_FCR_RD_RXFIFO_TRIGGER_OFFSET) /* RX FIFO trigger threshold = 6 */
#define UART_FCR_RD_RXFIFO_TRIGGER_12       (0x2<<UART_FCR_RD_RXFIFO_TRIGGER_OFFSET) /* RX FIFO trigger threshold = 12 */
#define UART_FCR_RD_RXFIFO_TRIGGER_RXTRIG   (0x3<<UART_FCR_RD_RXFIFO_TRIGGER_OFFSET) /* RX FIFO trigger threshold = RXTRIG */
#define UART_FCR_RD_TXFIFO_TRIGGER_1    (0x0<<UART_FCR_RD_TXFIFO_TRIGGER_OFFSET) /* TX FIFO trigger threshold = 1 */
#define UART_FCR_RD_TXFIFO_TRIGGER_4    (0x1<<UART_FCR_RD_TXFIFO_TRIGGER_OFFSET) /* TX FIFO trigger threshold = 4 */
#define UART_FCR_RD_TXFIFO_TRIGGER_8    (0x2<<UART_FCR_RD_TXFIFO_TRIGGER_OFFSET) /* TX FIFO trigger threshold = 8 */
#define UART_FCR_RD_TXFIFO_TRIGGER_14   (0x3<<UART_FCR_RD_TXFIFO_TRIGGER_OFFSET) /* TX FIFO trigger threshold = 14 */

#ifdef HAL_UART_FEATURE_SOFT_DTE_SUPPORT
void uart_dte_init_config(uart_dte_config_t *uart_dte_config);
#endif
vdma_channel_t uart_port_to_dma_channel(hal_uart_port_t uart_port, int32_t is_rx);
void uart_dma_channel_to_callback_data(vdma_channel_t dma_channel, uart_dma_callback_data_t *user_data);
void uart_enable_dma(UART_REGISTER_T *uartx);
void uart_interrupt_handler(hal_nvic_irq_t irq_number);

#ifdef __cplusplus
}
#endif

#endif
#endif

