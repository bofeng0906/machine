MBEDTLS module usage guide

Brief:          This module is an implementation of TLS.
Usage:          GCC: In your GCC project mk file, such as feature.mk, please set MTK_MBEDTLS_CONFIG_FILE to the configuration file
                     wanted, for example "MTK_MBEDTLS_CONFIG_FILE = config-mtk-basic.h".
                     In your GCC project Makefile, please add the following:
                     include $(SOURCE_DIR)/middleware/third_party/mbedtls/module.mk
                KEIL: Drag the middleware/third_party/mbedtls folder to your project. Define SUPPORT_MBEDTLS macro and define MBEDTLS_CONFIG_FILE
                      macro to the configuration file wanted, such as MBEDTLS_CONFIG_FILE=<config-mtk-basic.h>. Add the following to include paths:
                      middleware/third_party/mbedtls/include
                      middleware/third_party/mbedtls/include/mbedtls
                      the path of the configuration file
                IAR: Drag the middleware/third_party/mbedtls folder to your project. Define SUPPORT_MBEDTLS macro and define MBEDTLS_CONFIG_FILE
                     macro to the configuration file wanted, such as MBEDTLS_CONFIG_FILE=<config-mtk-basic.h>. Add the following to include paths:
                     middleware/third_party/mbedtls/include
                     middleware/third_party/mbedtls/include/mbedtls
                     the path of the configuration file
Dependency:     Please also include LWIP since this module uses it.
Notice:         Configuration file, such as config-mtk-basic.h, is used to enable the mbedtls features needed.
Relative doc:   Please refer to internet and open source software guide under the doc folder for more detail.
Example project:Please find mbedtls project under project folder.