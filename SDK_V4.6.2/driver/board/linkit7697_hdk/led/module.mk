
LED_BSP_SRC = driver/board

C_FILES  += $(LED_BSP_SRC)/component/led/src/bsp_led.c
C_FILES  += $(LED_BSP_SRC)/linkit7697_hdk/led/src/bsp_led_internal.c


#################################################################################
#include path
CFLAGS  += -I$(SOURCE_DIR)/driver/board/component/led/inc
CFLAGS  += -I$(SOURCE_DIR)/driver/board/linkit7697_hdk/led/inc

#################################################################################
#Enable the feature by configuring
COM_CFLAGS         += -DMTK_LED_ENABLE

