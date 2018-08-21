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
 * @addtogroup mt7686_hdk_hal_examples_sleep_manager_power_mode sleep_manager_power_mode
 * @{

@par Overview
  - Example project description
    - This project is a reference application to use the sleep manager APIs
      to force the system to enter sleep mode for power saving operations.
      - Power monitor equipment is optional to verify the system status.
    - Results
      - The system will enter sleep mode in the specified order:
      - Idle
      - Sleep
      - It remains in each state for five seconds.

@par Hardware and software environment
  - Supported platform
    - LinkIt 7686 HDK.
  - Power monitor (optional)    
  - Note:
    - For more details about using sleep manager APIs, please refer to LinkIt
      7686 API Reference Manual.      
  - HDK switches and pin configuration
  - Environment configuration
    - The output logs are communicated through a type-A to micro-B USB cable
      to the PC from USB (CON5) connector on the HDK.
    - Install the mbed serial driver according to the instructions at
      https://developer.mbed.org/handbook/Windows-serial-configuration. For
      more information, please refer to section "Installing the LinkIt 7686
      HDK drivers on Microsoft Windows" on the "LinkIt 7686 HDK User Guide"
      in [sdk_root]/doc folder.
    - Use a type-A to micro-B USB cable to connect type-A USB of the PC and
      CON5 micro-B USB connector on the LinkIt 7686 HDK. For more information
      about the connector cable, please refer to
      https://en.wikipedia.org/wiki/USB#Mini_and_micro_connectors.
    - Launch a terminal emulator program, such as Tera terminal on your PC
      for data logging through UART. For the installation details, please
      refer to section "Installing Tera terminal on Microsoft Windows" on the
      "LinkIt for RTOS Get Started Guide" in [sdk_root]/doc folder.
    - COM port settings. baudrate: 115200, data bits: 8, stop bit: 1, parity:
      none and flow control: off.

@par Directory contents
  - Source and header files
    - \b src/main.c:            Main program.
    - \b src/system_mt7686.c:   mt7686 clock configuration file.
    - \b inc/hal_feature_config.h:
                                mt7686 feature configuration file.
    - \b inc/memory_map.h:      mt7686 memory layout symbol file.
    - \b GCC/startup_mt7686.s:  mt7686 startup file for GCC.
    - \b GCC/syscalls.c:        mt7686 syscalls for GCC.
    - \b MDK-ARM/startup_mt7686.s:
                                mt7686 startup file for Keil IDE.
  - Project configuration files using GCC
    - \b GCC/feature.mk:       Feature configuration.
    - \b GCC/Makefile.:        Makefile.
    - \b GCC/mt7686_flash.ld:  Linker script.
  - Project configuration files using Keil IDE
    - \b MDK-ARM/sleep_manager_power_mode.uvprojx:
                             uVision5 project file. Contains the project
                             structure in XML format.
    - \b MDK-ARM/sleep_manager_power_mode.uvoptx:
                             uVision5 project options. Contains the settings
                             for the debugger, trace configuration,
                             breakpoints, currently open files, etc.
    - \b MDK-ARM/flash.sct:  Linker script.

@par Run the example   
  - Build the example project with the command "./build.sh mt7686_hdk
    sleep_manager_power_mode" from the SDK root folder and download the
    binary file to the LinkIt 7686 HDK.
  - Connect the HDK to the PC with a type-A to micro-B USB cable and specify
    the port on Tera terminal corresponding to "mbed Serial Port".
  - Run the application. The transaction result is displayed in the log,
    similar to the description below.
  - "Example:Enter Idle.", "Example:Wakeup form Idle.", the device will
    enter Idle mode then wake up after 5 seconds.
  - "Example:Enter Sleep.","Example:Wakeup form Sleep.", the device will enter
    sleep mode again and wake up after 5 seconds, which indicates the 
    application completed successfully.
*/
/**
 * @}
 * @}
 * @}
 */
