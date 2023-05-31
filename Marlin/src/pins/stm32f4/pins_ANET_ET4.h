/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include "env_validate.h"

#if HAS_MULTI_HOTEND || E_STEPPERS > 1
  #error "Anet ET4 only supports 1 hotend / E stepper."
#endif

#ifndef BOARD_INFO_NAME
  #define BOARD_INFO_NAME "Anet ET4 1.x"
#endif

//
// EEPROM
//

/**
 *  Status: Working (FLASH EEPROM EMULATION).
 *  Hardware: AT24C04C (ATMLH744 04CM) 4 Kb => http://ww1.microchip.com/downloads/en/DeviceDoc/AT24C04C-AT24C08C-I2C-Compatible-%20Two-Wire-Serial-EEPROM-4-Kbit-8-Kbit-20006127A.pdf
 */

// Use one of these or SDCard-based Emulation will be used
// FLASH_EEPROM_EMULATION is the recommended and working option.
#if NO_EEPROM_SELECTED
  //#define SRAM_EEPROM_EMULATION                 // Use BackSRAM-based EEPROM emulation
  #define FLASH_EEPROM_EMULATION                  // Use Flash-based EEPROM emulation                
  //#define I2C_EEPROM                            // Use I2C EEPROM onboard IC
#endif

#if ENABLED(FLASH_EEPROM_EMULATION)
  // Decrease delays and flash wear by spreading writes across the
  // 128 kB sector allocated for EEPROM emulation.
  #define FLASH_EEPROM_LEVELING
#elif ENABLED(I2C_EEPROM)
  // AT24C04C, Size 4Kb/512B, PageSize 16B
  // Not working. 512 Bytes are not enough to store all config settings. Tested: Replaced with AT24C256 IC and it works fine. 
  #define I2C_SDA_PIN                       PB11
  #define I2C_SCL_PIN                       PB10
  #define MARLIN_EEPROM_SIZE                0x200                // 4Kb (From Datasheet)
#endif

//
// Limit Switches
//
#define X_STOP_PIN                          PC13
#define Y_STOP_PIN                          PE12
#define Z_STOP_PIN                          PE11

//
// Z Probe
//
#if ENABLED(BLTOUCH)
  // You will need to use 24V to 5V converter and remove one resistor and capacitor from the motherboard. See https://github.com/davidtgbe/Marlin/blob/bugfix-2.0.x/docs/Tutorials/bltouch-en.md for more information.
  #define SERVO0_PIN                        PC3
#elif !defined(Z_MIN_PROBE_PIN)
  #define Z_MIN_PROBE_PIN                   PC3
#endif

//
// Filament Runout Sensor
//
#ifndef FIL_RUNOUT_PIN
  #define FIL_RUNOUT_PIN                    PA2
#endif

//
// Power Loss Detection
//

/**
 *  Status: Working. Specially thanks to Zhiniukas and SidDrP for their contributions.
 *  Hardware: Two pins needed. One for powerloss detection and another to enable aux power from supercap.
 */

#ifndef POWER_LOSS_PIN
  #define POWER_LOSS_PIN                    PA8
#endif

#ifndef POWER_LOSS_PIN_2
  #define POWER_LOSS_PIN_2                  PA3   // Switch to HIGH state to enable SuperCapacitor and supply backup energy. (Zhiniukas & SidDrP)
#endif

//
// LED PIN
//
#define LED_PIN                             PD12

//
// Steppers
//
#define X_STEP_PIN                          PB6
#define X_DIR_PIN                           PB5
#define X_ENABLE_PIN                        PB7

#define Y_STEP_PIN                          PB3
#define Y_DIR_PIN                           PD6
#define Y_ENABLE_PIN                        PB4

#define Z_STEP_PIN                          PA12
#define Z_DIR_PIN                           PA11
#define Z_ENABLE_PIN                        PA15

#define E0_STEP_PIN                         PB9
#define E0_DIR_PIN                          PB8
#define E0_ENABLE_PIN                       PE0

//
// Temperature Sensors
//
#define TEMP_0_PIN                          PA1
#define TEMP_BED_PIN                        PA4

//
// Heaters
//
#define HEATER_0_PIN                        PA0
#define HEATER_BED_PIN                      PE2

//
// Fans
//
#define FAN0_PIN                            PE3   // Layer fan
#define FAN1_PIN                            PE1   // Hotend fan

#ifndef E0_AUTO_FAN_PIN
  #define E0_AUTO_FAN_PIN               FAN1_PIN
#endif

//
// LCD / Controller
//

/**
 * Status: Working. Merged FSMC/DMA implementation for stm32f4 from jmz52 fork.
 * Hardware: IC ST7789V | STP320240_0280E2T (40P/1,5): ST7789 (YT280S008)  => https://a.aliexpress.com/_dV4Bghv
 * Notes: 
 *  - Defined PINS: CSX, DCX, WRX, RESX, RDX, DB[8:15]
 *  - FSMC/DMA and 8080-8 interface
 */

#if HAS_SPI_TFT || HAS_FSMC_TFT
  #define TFT_RESET_PIN                     PE6
  #define TFT_CS_PIN                        PD7
  #define TFT_RS_PIN                        PD13

  #if HAS_FSMC_TFT
    #define LCD_USE_DMA_FSMC                      // Use DMA transfers to send data to the TFT
    #define FSMC_CS_PIN               TFT_CS_PIN
    #define FSMC_RS_PIN               TFT_RS_PIN
    #define TFT_INTERFACE_FSMC_8BIT
  #endif
#endif

//
// Touch Screen
//

/**
 * Status: Working. Merged implementation from jmz52 fork.
 * Hardware: TOUCH: XPT2046 => https://ldm-systems.ru/f/doc/catalog/HY-TFT-2,8/XPT2046.pdf
 */

#if NEED_TOUCH_PINS
  #define TOUCH_CS_PIN                      PB2
  #define TOUCH_SCK_PIN                     PB0
  #define TOUCH_MOSI_PIN                    PE5
  #define TOUCH_MISO_PIN                    PE4
  #define TOUCH_INT_PIN                     PB1
#endif

#if ENABLED(ANET_ET5_TFT35)
  #ifndef TOUCH_CALIBRATION_X
    #define TOUCH_CALIBRATION_X            17125
  #endif
  #ifndef TOUCH_CALIBRATION_Y
    #define TOUCH_CALIBRATION_Y           -11307
  #endif
  #ifndef TOUCH_OFFSET_X
    #define TOUCH_OFFSET_X                   -26
  #endif
  #ifndef TOUCH_OFFSET_Y
    #define TOUCH_OFFSET_Y                   337
  #endif
  #ifndef TOUCH_ORIENTATION
    #define TOUCH_ORIENTATION     TOUCH_PORTRAIT
  #endif
#elif ENABLED(ANET_ET4_TFT28)
  #ifndef TOUCH_CALIBRATION_X
    #define TOUCH_CALIBRATION_X           -11838
  #endif
  #ifndef TOUCH_CALIBRATION_Y
    #define TOUCH_CALIBRATION_Y             8776
  #endif
  #ifndef TOUCH_OFFSET_X
    #define TOUCH_OFFSET_X                   333
  #endif
  #ifndef TOUCH_OFFSET_Y
    #define TOUCH_OFFSET_Y                   -17
  #endif
  #ifndef TOUCH_ORIENTATION
    #define TOUCH_ORIENTATION     TOUCH_PORTRAIT
  #endif
#endif

//
// SD Card
//
//#define ONBOARD_SDIO

#ifndef SDCARD_CONNECTION
  #define SDCARD_CONNECTION         CUSTOM_CABLE
#endif

#if HAS_MEDIA

  #if DISABLED(ONBOARD_SDIO)
    #define SOFTWARE_SPI
    #define SDSS                            PC11
    #define SD_SS_PIN                       SDSS
    #define SD_SCK_PIN                      PC12
    #define SD_MISO_PIN                     PC8
    #define SD_MOSI_PIN                     PD2
  #endif

  #ifndef SD_DETECT_PIN
    #define SD_DETECT_PIN                   PD3
  #endif

#endif

//
// SPI Flash
//

/**
 * Status: Working. Tested with MKS LVGL (needs 480x320 ET5 TFT). Not used.
 * Hardware: https://www.winbond.com/resource-files/w25q128jv%20revf%2003272018%20plus.pdf
 */

// SPI Flash
#define HAS_SPI_FLASH                          1
#if HAS_SPI_FLASH
  #define SPI_FLASH_SIZE               0x1000000  // 16MB
#endif

// SPI 2
#define SPI_FLASH_CS_PIN                       PB12
#define SPI_FLASH_MOSI_PIN                     PB15
#define SPI_FLASH_MISO_PIN                     PB14
#define SPI_FLASH_SCK_PIN                      PB13