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
 * @addtogroup mt7686_hdk mt7686_hdk
 * @{
 * @addtogroup mt7686_hdk_hal_examples hal_examples
 * @{
 * @addtogroup mt7686_hdk_hal_examples_eint_edge_falling eint_edge_falling
 * @{

@par Overview
  - Example description
    - This example is a reference application to demonstrate how to configure
      an EINT with edge falling trigger mode.
    - This example does not require FreeRTOS.
  - Results
    - The result is printed in the log.

@par Hardware and software environment
  - Supported platform
    - LinkIt 7686 HDK.
  - HDK switches and pin configuration
    - Select the pin function as EINT.
      |GPIOx    |PINx                             |
      |---------|---------------------------------|
      |  0      |              S2005              |
  - Environment configuration
    - The output logs are communicated through a type-A to micro-B USB cable
      to the PC from MK20 USB connector on the HDK.
    - Install the mbed serial driver according to the instructions at
      https://developer.mbed.org/handbook/Windows-serial-configuration. For
      more information, please refer to section "Installing the LinkIt 7686
      HDK drivers on Microsoft Windows" on the "LinkIt 7686 HDK User Guide"
      in [sdk_root]/doc folder.
    - Use a type-A to micro-B USB cable to connect type-A USB of the PC and
      MK20 micro-B USB connector on the LinkIt 7686 HDK. For more information
      about the connector cable, please refer to
      https://en.wikipedia.org/wiki/USB#Mini_and_micro_connectors.
    - Launch a terminal emulator program, such as Tera terminal on your PC
      for data logging through UART. For the installation details, please
      refer to section "Installing Tera terminal on Microsoft Windows" on the
      "LinkIt for RTOS Get Started Guide" in [sdk_root]/doc folder.
    - COM port settings. baudrate: 115200, data: 8bits, stop bit: 1, parity:
      none and flow control: off.

@par Directory contents
  - Source and header files
    - \b src/main.c:            Main program.
    - \b src/system_mt7686.c:   MT7686x clock configuration file.
    - \b inc/hal_feature_config.h:
                                MT7686x feature configuration file.
    - \b inc/memory_map.h:      MT7686x memory layout symbol file.
    - \b GCC/startup_mt7686.s:  MT7686x startup file for GCC.
    - \b GCC/syscalls.c:        MT7686x syscalls for GCC.
    - \b MDK-ARM/startup_mt7686.s:
                                MT7686x startup file for Keil IDE.
  - Project configuration files using GCC
    - \b GCC/feature.mk:  Feature configuration.
    - \b GCC/Makefile.:   Makefile.
    - \b GCC/flash.ld:    Linker script.
  - Project configuration files using Keil IDE
    - \b MDK-ARM/eint_edge_falling.uvprojx:
                             uVision5 project file. Contains the project
                             structure in XML format.
    - \b MDK-ARM/eint_edge_falling.uvoptx:
                             uVision5 project options. Contains the settings
                             for the debugger, trace configuration,
                             breakpoints, currently open files, etc.
    - \b MDK-ARM/flash.sct:  Linker script.

@par Run the example
  - Build the example project with a command "./build.sh mt7686_hdk
    eint_edge_falling bl" from the SDK root folder and download the binary
    file to LinkIt 7686 HDK.
  - Connect the HDK to the PC with a type-A to micro-B USB cable and specify
    the port on the terminal emulator software corresponding to "mbed Serial
    Port".
  - Connect J2013.1 with J2013.2 and J2014.1 with J2014.2 of Linkit 7686 HDK.
  - Run the example.
  - Press key S2005 of Linkit 7686 HDK.
  - The log will show "Received eint: 0!" to indicate a successful operation.
*/
/**
 * @}
 * @}
 * @}
 */
