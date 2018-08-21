/* Copyright Statement:
 *
 * (C) 2005-2017 MediaTek Inc. All rights reserved.
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. ("MediaTek") and/or its
 * licensors. Without the prior written permission of MediaTek and/or its
 * licensors, any reproduction, modification, use or disclosure of MediaTek
 * Software, and information contained herein, in whole or in part, shall be
 * strictly prohibited. You may only use, reproduce, modify, or distribute
 * (as applicable) MediaTek Software if you have agreed to and been bound by
 * the applicable license agreement with MediaTek ("License Agreement") and
 * been granted explicit permission to do so within the License Agreement
 * ("Permitted User"). If you are not a Permitted User, please cease any
 * access or use of MediaTek Software immediately.
 */

/**
 * @addtogroup mt7682_hdk mt7682_hdk
 * @{
 * @addtogroup mt7682_hdk_hal_examples hal_examples
 * @{
 * @addtogroup mt7682_hdk_hal_examples_spi_slave_from_master spi_slave_from_master
 * @{

@par Overview
  - Example description
    - This example is a reference application to demonstrate how to use SPI
      slave API to communicate with an SPI master with two LinkIt 7682 HDKs.
    - This example does not require FreeRTOS.
  - Results
    - The result is in the log.
  - Features of the example project
    - The example project has two parts: 1. LinkIt 7682 HDK operates as SPI
      Slave device (spi_master_to_slave). 2. LinkIt 7682 HDK operates as SPI
      Master device (spi_slave_from_master). The communication between master
      and slave devices is shown below.
      \code
      __________________________                       __________________________
      |          _______________|                     |______________            |
      |         |SPI Master     |                     |     SPI Slave|           |
      |         |               |                     |              |           |
      |         |      J2101 G14|_____________________|J2101 G14     |           |
      |         |               |                     |              |           |
      |         |      J2101 G15|_____________________|J2101 G15     |           |
      |         |               |                     |              |           |
      |         |      J2101 G16|_____________________|J2101 G16     |           |
      |         |               |                     |              |           |
      |         |      J2101 G17|_____________________|J2101 G17     |           |
      |         |_______________|                     |______________|           |
      |                         |                     |                          |
      |                         |                     |                          |
      |                J2111 GND|_____________________|J2111 GND                 |
      |                         |                     |                          |
      |_MT7682__________________|                     |_MT7682___________________|
      \endcode

@par Hardware and software environment
  - Supported platform
    - LinkIt 7682 HDK.
  - HDK switches and pin configuration
    - Connect J2101.G14 to J2101.G14
    - Connect J2101.G15 to J2101.G15
    - Connect J2101.G16 to J2101.G16
    - Connect J2101.G17 to J2101.G17
    - SPI slave module pin mapping table is shown below.
      | SPI Pin | GPIOx     |    PINx          |
      |-------  |---------  |-----------  |
      |  CS     | GPIO_17   | J2101.G17   |
      |  SCK    | GPIO_16   | J2101.G16   |
      |  SIO0   | GPIO_15   | J2101.G15   |
      |  SIO1   | GPIO_14   | J2101.G14   |
  - Environment configuration
    - The output logs are communicated through a type-A to micro-B USB cable
      to the PC from MK20 USB connector on the HDK.
    - Install the mbed serial driver according to the instructions at
      https://developer.mbed.org/handbook/Windows-serial-configuration. For
      more information, please refer to section "Installing the LinkIt 7682
      HDK drivers on Microsoft Windows" on the "LinkIt 7682 HDK User Guide"
      in [sdk_root]/doc folder.
    - Use a type-A to micro-B USB cable to connect type-A USB of the PC and
      MK20 micro-B USB connector on the LinkIt 7682 HDK. For more information
      about the connector cable, please refer to
      https://en.wikipedia.org/wiki/USB#Mini_and_micro_connectors.
    - Launch a terminal emulator program, such as Tera terminal on your PC
      for data logging through UART. For the installation details, please
      refer to section "Installing Tera terminal on Microsoft Windows" on the
      "LinkIt for RTOS Get Started Guide" in [sdk_root]/doc folder.
    - COM port settings. baudrate: 115200, data: 8 bits, stop bit: 1, parity:
      none and flow control: off.

@par Directory contents
  - Source and header files
    - \b src/main.c:            Main program.
    - \b src/system_mt7682.c:   MT7682 system clock configuration file.
    - \b inc/hal_feature_config.h:
                                MT7682 feature configuration file.
    - \b inc/memory_map.h:      MT7682 memory layout symbol file.
    - \b GCC/startup_mt7682.s:  MT7682 startup file for GCC.
    - \b GCC/syscalls.c:        MT7682 syscalls for GCC.
    - \b MDK-ARM/startup_mt7682.s:
                                MT7682 startup file for Keil IDE.
  - Project configuration files using GCC
    - \b GCC/feature.mk:        Feature configuration file.
    - \b GCC/Makefile:          Makefile.
    - \b GCC/mt7682_flash.ld:   Linker script.
  - Project configuration files using Keil IDE
    - \b MDK-ARM/spi_slave_from_master.uvprojx:
                             uVision5 Project File. Contains the project
                             structure in XML format.
    - \b MDK-ARM/spi_slave_from_master.uvoptx:
                             uVision5 project options. Contains the settings
                             for the debugger, trace configuration,
                             breakpoints, currently open files, etc.
    - \b MDK-ARM/flash.sct:  Linker script.
  - Project configuration files using IAR
    - \b EWARM/spi_slave_from_master.ewd:
                           IAR project options. Contains the settings for the
                           debugger.
    - \b EWARM/spi_slave_from_master.ewp:
                           IAR project file. Contains the project structure in
                           XML format.
    - \b EWARM/spi_slave_from_master.eww:
                           IAR workspace file. Contains project information.
    - \b EWARM/flash.icf:  Linker script.

@par Run the example
  - Build the example project for Master with a command "./build.sh
    mt7682_hdk spi_master_to_slave bl" from the SDK root folder and download
    the binary file to the LinkIt 7682 HDK that operates as SPI Master.
  - Build the example project for Slave with a command "./build.sh mt7682_hdk
    spi_slave_from_master bl" from the SDK root folder and download the
    binary file to the 7682 HDK that operates as SPI Slave.
  - Connect the related pins of the two LinkIt 7682 HDKs as shown in the
    "Features of the example project" and "HDK switches and pin
    configuration" sections.
  - Connect the HDK to the PC with a type-A to micro-B USB cable and specify
    the port on Tera terminal corresponding to "mbed Serial Port".
  - Run the example. The log will show the communication result with the SPI
    Slave. The log of "spi_master_send_data_two_boards_example ends" for
    master board and "spi_slave_receive_data_two_boards_example ends" for
    slave board indicates a successful communication. Please make sure the
    two LinkIt 7682 HDK boards (Master and Slave) are powered up at the same
    time, no more than 2 seconds apart.
*/
/**
 * @}
 * @}
 * @}
 */
