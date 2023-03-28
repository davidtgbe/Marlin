/**
 * Author: David Terán
 * telegram: @davidtgbe
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

// ------------------
// 1. Pre-build steps
// ------------------

/** 
 * File organization:
 *  1. General file information / pre-build steps (this section)
 *  2. Basic Settings
 *  3. Post-build steps
 *  4. Configuration.h parameters overwritten by EasyConfig
 * 
 * NOTE: This file will try to define some parameters that are already defined on configuration.h. 
 * Take this into account and take also a look to the end of this file to see wich parameters could 
 * be overwritten by EasyConfig.
 * 
 * Pre-build instructions:
 * 
 * 1. Uncomment line "#define ET_EASY_CONFIG" in configuration.h for this file to take effect.
 * 2. Only mandatory parmeter is "ET_MODEL".
 * 3. Rest of parameters can be commented if they are the defaults for the printer model.
 *    You can refer to these defaults on the table below. Any modifications you have
 *    made to your specific printer model which doesn't match the defaults showed below in the
 *    table, must be defined uncommenting corresponding line.
 * 4. Build the FW with/without support for OpenBLT bootloader using the corresponding environment
 *    (Anet_ET4_OpenBLT/Anet_ET4_no_bootloader).
 * 
 *  ET series default specifications:
 *    +-------------------+-------------+------------+--------------+--------------+---------+
 *    |       Model       |    SIZE     | AUTOLEVEL  | HOMING Z-DIR | PHY ENDSTOPS | DRIVERS |
 *    +-------------------+-------------+------------+--------------+--------------+---------+
 *    | ET4               | 220X220X250 | FILM STRIP | UP           | X-L,Y-B,Z-T  | A4988   |
 *    | ET4X              | 220X220X250 | NONE       | DOWN         | X-L,Y-B,Z-B  | A4988   |
 *    | ET4+              | 220X220X250 | CAPACITIVE | DOWN         | X-L,Y-B      | A4988   |
 *    | ET4 PRO           | 220X220X250 | CAPACITIVE | DOWN         | X-L,Y-B      | TMC2208 |
 *    | ET5               | 300X300X400 | CAPACITIVE | DOWN         | X-L,Y-B      | A4988   |
 *    | ET5X              | 300X300X400 | CAPACITIVE | DOWN         | X-L,Y-B      | A4988   |
 *    | ET5 PRO           | 300X300X400 | CAPACITIVE | DOWN         | X-L,Y-B      | TMC2208 |
 *    +-------------------+-------------+------------+--------------+--------------+---------+
 *    PHY endstops legend: Axis + (Left, Right, Front, Back, Top, Bottom)
 *
 */

// -----------------
// 2. Basic settings
// -----------------

/**
 * Parameter: ET_MODEL
 * Description: ET base model.
 * Type: Mandatory.
 * Values: ET_MODEL_ET4 ,ET_MODEL_ET4_PLUS, ET_MODEL_ET4X, ET_MODEL_ET4_PRO, ET_MODEL_ET5, ET_MODEL_ET5X, ET_MODEL_ET5_PRO
 */

#define ET_MODEL                ET_MODEL_ET4

/**
 * Parameter: ET_BOARD
 * Description: ET board/drivers to be used if you have changed it from factory default.
 * Type: Optional.
 * Values: ET_BOARD_SILENT, ET_BOARD_NOISY
 */

//#define ET_BOARD              ET_BOARD_SILENT


/**
 * Parameter: ET_LEVELLING
 * Description: Define levelling method to be used if you have changed it from factory default.
 * Type: Optional.
 * Values: ET_LV_NONE, ET_LV_BLTOUCH, ET_LV_MOUNTED_PROBE, ET_LV_FILM_STRIP
 */

//#define ET_LEVELLING          ET_LV_BLTOUCH

/**
 * Parameter: ET_Z_HOMING_DIR
 * Description: Define homing direction if you have changed it from factory default.
 * Type: Optional.
 * Values: ET_Z_HOMING_DIR_UP, ET_Z_HOMING_DIR_DOWN
 */

//#define ET_Z_HOMING_DIR       ET_Z_HOMING_DIR_DOWN

/**
 * Parameter: ET_MOD
 * Description: Define custom mods you have made to your printer.
 * Type: Optional.
 * Values: ET_MOD_BMG, ET_MOD_BMG_MINI, ET_MOD_V6
 * Usage: To select multiple mods use '|' to join. ex: #define ET_MOD (ET_MOD_BMG | ET_MOD_V6)
 */

//#define ET_MOD                ET_MOD_BMG

/**
 * Parameter: ET_Z_ENDSTOP_POSTION 
 * Description: Define the Z endstop postion if you have changed or removed Z endstop position from factory default.
 * Type: Optional.
 * Values: ET_Z_ENDSTOP_POSTION_NONE, ET_Z_ENDSTOP_POSTION_TOP, ET_Z_ENDSTOP_POSTION_BOTTOM
 */

//#define ET_Z_ENDSTOP_POSTION  ET_Z_ENDSTOP_POSTION_NONE

/**
 * Parameter: ET_CUSTOM_MACHINE_NAME
 * Description: Define a custom machine name to display on the information screen if desired.
 * Type: Optional 
 */

#define ET_CUSTOM_MACHINE_NAME  "Anet ET4" 

// ----------------------------------------------
// 3. Basic Post-installation configuration steps
// ----------------------------------------------

/**
 * Below steps must be performed to finish Marlin configuration and set parameters which are dependant 
 * on your current setup/printer. You can use pronterface to send gcodes.
 *
 * 1. EEPROM initialization -> https://marlinfw.org/docs/gcode/M502.html
 * 
 *         > M502
 *         > M500
 *
 * 2. Hotend PID autotune -> https://marlinfw.org/docs/gcode/M303.html ; https://marlinfw.org/docs/gcode/M301.html
 * 
 *         > M303 E0 S200 C3 U
 * 
 * 3. Bed PID autotune -> https://marlinfw.org/docs/gcode/M303.html ; https://marlinfw.org/docs/gcode/M304.html
 *
 *         > M303 E-1 S60 C3 U 
 *         
 * 4. Calibrate motors steps -> https://marlinfw.org/docs/gcode/M092.html | Guide: https://www.instructables.com/Calibrating-your-3D-printer-using-minimal-filament/
 *
 *         > M92 E<value> X<value> Y<value> Z<value>
 *         
 * 5. Nozzle to probe offset. Only in case of mounted probe autolevel feature -> https://marlinfw.org/docs/gcode/M851.html | Guide: https://www.thingiverse.com/thing:3700194
 *
 *         > M851 X<value> Y<value> Z<value> 
 *
 * 6. Save EEPROM -> https://marlinfw.org/docs/gcode/M500.html 
 *
 *         > M500 
 *
 * Other useful commands:
 * - Bltouch test
 *
 *         > M43 S P0
 *
 * Other guides:
 * https://marlinfw.org/docs/configuration/configuration.html
 * https://teachingtechyt.github.io/calibration.html
 * 
 * Marlin recommended:
 * https://reprap.org/wiki/Calibration
 * https://youtu.be/wAL9d7FgInk
 * http://calculator.josefprusa.cz
 * https://reprap.org/wiki/Triffid_Hunter%27s_Calibration_Guide
 * https://www.thingiverse.com/thing:5573
 * https://sites.google.com/site/repraplogphase/calibration-of-your-reprap
 * https://www.thingiverse.com/thing:298812
 */

// -------------------------------------------------------------
// 4. Info: Configuration.h parameters overwritten by EasyConfig
// -------------------------------------------------------------

/* 

These parameters below are overwritten by easyconfig.h. This means
that any change to any of these parameters on configuration.h
file won't be effective. 
If you need to modify these parameters, you can configure Marlin 
from scratch (not using EasyConfig) or editing this file:
"<RepoBasePath>/Marlin/src/inc/EasyConfigPost.h"

List of overwritten parameters:

-- Misc --
CUSTOM_MACHINE_MODEL_NAME

-- Levelling --
NOZZLE_AS_PROBE
BLTOUCH
FIX_MOUNTED_PROBE
Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN
USE_PROBE_FOR_Z_HOMING
Z_SAFE_HOMING
LCD_BED_LEVELING
G26_MESH_VALIDATION
ENABLE_LEVELING_FADE_HEIG
SEGMENT_LEVELED_MOVES
LEVELED_SEGMENT_LENGTH   
AUTO_BED_LEVELING_BILINEAR
Z_MIN_PROBE_REPEATABILITY_TEST
Z_MIN_PROBE_ENDSTOP_HIT_STATE
BABYSTEP_ZPROBE_OFFSET
BED_TRAMMING_USE_PROBE
ASSISTED_TRAMMING

-- Z_Homing dir --
X_HOME_DIR
Y_HOME_DIR
Z_HOME_DIR

-- Endstops --
USE_XMIN_PLUG
USE_YMIN_PLUG
USE_ZMIN_PLUG
USE_XMAX_PLUG
USE_YMAX_PLUG
USE_ZMAX_PLUG

X_MIN_ENDSTOP_HIT_STATE
Y_MIN_ENDSTOP_HIT_STATE
Z_MIN_ENDSTOP_HIT_STATE
Z_MAX_ENDSTOP_HIT_STATE

-- Temp sensors --
TEMP_SENSOR_0

-- Drivers --
X_DRIVER_TYPE
Y_DRIVER_TYPE
Z_DRIVER_TYPE
E0_DRIVER_TYPE

-- Steps / Extruder dir --
INVERT_E0_DIR
DEFAULT_AXIS_STEPS_PER_UNIT

-- Size and endstop offsets --
X_BED_SIZE
Y_BED_SIZE
X_MIN_POS
Y_MIN_POS
Z_MIN_POS
X_MAX_POS
Y_MAX_POS
Z_MAX_POS

-- TFT -- 
TFT_GENERIC
TFT_DRIVER
TFT_INTERFACE_FSMC
TFT_COLOR_UI
TFT_RES_480x320
TFT_RES_320x240
TFT_ROTATION

*/
