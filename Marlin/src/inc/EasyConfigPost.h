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

#include "EasyConfigPre.h"
#include "../../EasyConfig.h"

#ifndef ET_MODEL
    #error "You must define an ET_MODEL value among [ET_MODEL_ET4 ,ET_MODEL_ET4_PLUS, ET_MODEL_ET4X, ET_MODEL_ET4_PRO, ET_MODEL_ET5, ET_MODEL_ET5X, ET_MODEL_ET5_PRO]."
#endif

//
// Defaults per model
//

#ifndef ET_BOARD
    #if ET_MODEL & (ET_MODEL_ET4_PRO | ET_MODEL_ET5_PRO)
        #define ET_BOARD    ET_BOARD_SILENT
    #else
        #define ET_BOARD    ET_BOARD_NOISY
    #endif
#endif    

#ifndef ET_LEVELLING 
    #if (ET_MODEL & ET_MODEL_ET4)
        #define ET_LEVELLING    ET_LV_FILM_STRIP
    #elif (ET_MODEL & ET_MODEL_ET4X)
        #define ET_LEVELLING    ET_LV_NONE
    #else
        #define ET_LEVELLING    ET_LV_MOUNTED_PROBE
    #endif
#endif

#ifndef ET_MOD
    #define ET_MOD  ET_MOD_NONE
#endif

#ifndef ET_Z_HOMING_DIR
    #if (ET_MODEL & ET_MODEL_ET4) && !(ET_LEVELLING & ET_LV_BLTOUCH)
        #define ET_Z_HOMING_DIR    ET_Z_HOMING_DIR_UP
    #else
        #define ET_Z_HOMING_DIR    ET_Z_HOMING_DIR_DOWN
    #endif
#endif

#ifndef ET_Z_ENDSTOP_POSTION
    #if (ET_MODEL & ET_MODEL_ET4) && !(ET_LEVELLING & ET_LV_BLTOUCH)
        #define ET_Z_ENDSTOP_POSTION ET_Z_ENDSTOP_POSTION_TOP
    #elif (ET_MODEL & ET_MODEL_ET4X) && !(ET_LEVELLING & ET_LV_BLTOUCH)
        #define ET_Z_ENDSTOP_POSTION ET_Z_ENDSTOP_POSTION_BOTTOM
    #else
        #define ET_Z_ENDSTOP_POSTION ET_Z_ENDSTOP_POSTION_NONE
    #endif
#endif

#ifdef ET_CUSTOM_MACHINE_NAME
    #undef CUSTOM_MACHINE_NAME
    #define CUSTOM_MACHINE_NAME ET_CUSTOM_MACHINE_NAME
#endif
#if (ET_MODEL & ET_MODEL_ET4)
    #ifndef CUSTOM_MACHINE_NAME
        #define CUSTOM_MACHINE_MODEL_NAME   "4"
    #endif
#elif (ET_MODEL & ET_MODEL_ET4X)
    #ifndef CUSTOM_MACHINE_NAME
        #define CUSTOM_MACHINE_MODEL_NAME   "4X"
    #endif
#elif (ET_MODEL & ET_MODEL_ET4_PLUS)
    #ifndef CUSTOM_MACHINE_NAME
        #define CUSTOM_MACHINE_MODEL_NAME   "4+"
    #endif
#elif (ET_MODEL & ET_MODEL_ET4_PRO)
    #ifndef CUSTOM_MACHINE_NAME
        #define CUSTOM_MACHINE_MODEL_NAME   "4 PRO"
    #endif
#elif (ET_MODEL & ET_MODEL_ET5)
    #ifndef CUSTOM_MACHINE_NAME
        #define CUSTOM_MACHINE_MODEL_NAME   "5"
    #endif
#elif (ET_MODEL & ET_MODEL_ET5X)
    #ifndef CUSTOM_MACHINE_NAME
        #define CUSTOM_MACHINE_MODEL_NAME   "5X"
    #endif
#elif (ET_MODEL & ET_MODEL_ET5_PRO)
    #ifndef CUSTOM_MACHINE_NAME
        #define CUSTOM_MACHINE_MODEL_NAME   "5 PRO"
    #endif
#endif

#ifdef CUSTOM_MACHINE_MODEL_NAME
    #define CUSTOM_MACHINE_BASE_NAME "Anet ET"
    #define CUSTOM_MACHINE_NAME CUSTOM_MACHINE_BASE_NAME CUSTOM_MACHINE_MODEL_NAME 
#endif

//
// Endstops
//

// Undefine to overwrite
#undef USE_XMIN_PLUG
#undef USE_YMIN_PLUG
#undef USE_ZMIN_PLUG
#undef USE_XMAX_PLUG
#undef USE_YMAX_PLUG
#undef USE_ZMAX_PLUG 

#undef X_MIN_ENDSTOP_HIT_STATE
#undef Y_MIN_ENDSTOP_HIT_STATE
#undef Z_MIN_ENDSTOP_HIT_STATE
#undef Z_MAX_ENDSTOP_HIT_STATE
#undef Z_MIN_PROBE_ENDSTOP_HIT_STATE

// Redefine
#define USE_XMIN_PLUG
#define USE_YMIN_PLUG
#define USE_ZMIN_PLUG

#define X_MIN_ENDSTOP_HIT_STATE LOW
#define Y_MIN_ENDSTOP_HIT_STATE LOW
#define Z_MIN_ENDSTOP_HIT_STATE LOW
#define Z_MAX_ENDSTOP_HIT_STATE LOW
#define Z_MIN_PROBE_ENDSTOP_HIT_STATE LOW

#if (ET_Z_ENDSTOP_POSTION & ET_Z_ENDSTOP_POSTION_TOP)
    #define USE_ZMAX_PLUG
#endif

//
// Levelling
//

// Undefine to overwrite
#undef NOZZLE_AS_PROBE
#undef BLTOUCH
#undef FIX_MOUNTED_PROBE
#undef Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN
#undef USE_PROBE_FOR_Z_HOMING
#undef Z_SAFE_HOMING
#undef Z_MIN_PROBE_REPEATABILITY_TEST
#undef BABYSTEP_ZPROBE_OFFSET
#undef BED_TRAMMING_USE_PROBE
#undef ASSISTED_TRAMMING

// Redefine
#if (ET_LEVELLING & ET_LV_FILM_STRIP)
    #define NOZZLE_AS_PROBE
#elif (ET_LEVELLING & (ET_LV_BLTOUCH | ET_LV_MOUNTED_PROBE))
    #define Z_SAFE_HOMING
    #define Z_MIN_PROBE_REPEATABILITY_TEST
    #define BABYSTEP_ZPROBE_OFFSET
    #define ASSISTED_TRAMMING
    #define BED_TRAMMING_USE_PROBE
    #if (ET_LEVELLING & ET_LV_BLTOUCH)
        #define BLTOUCH
        #define Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN        
        #undef Z_MIN_ENDSTOP_HIT_STATE
        #undef Z_MIN_PROBE_ENDSTOP_HIT_STATE        
        #define Z_MIN_ENDSTOP_HIT_STATE         HIGH
        #define Z_MIN_PROBE_ENDSTOP_HIT_STATE   HIGH
    #elif (ET_LEVELLING & ET_LV_MOUNTED_PROBE)
        #define FIX_MOUNTED_PROBE
    #endif
    #if (ET_Z_ENDSTOP_POSTION & ET_Z_ENDSTOP_POSTION_NONE)
        #define USE_PROBE_FOR_Z_HOMING
    #endif
#elif (ET_LEVELLING & ET_LV_NONE)
    #undef LCD_BED_LEVELING
    #undef G26_MESH_VALIDATION
    #undef ENABLE_LEVELING_FADE_HEIGHT
    #undef SEGMENT_LEVELED_MOVES
    #undef LEVELED_SEGMENT_LENGTH     
    #undef AUTO_BED_LEVELING_BILINEAR
    #undef PROBING_MARGIN
    #undef NOZZLE_TO_PROBE_OFFSET
#else
    #error "You must define an ET_LEVELLING value among [ET_LV_NONE, ET_LV_BLTOUCH, ET_LV_MOUNTED_PROBE, ET_LV_FILM_STRIP]."
#endif

//
// Z homing
//

// Undefine to overwrite
#undef X_HOME_DIR
#undef Y_HOME_DIR
#undef Z_HOME_DIR

// Redefine
#define X_HOME_DIR -1
#define Y_HOME_DIR -1

#if (ET_Z_HOMING_DIR & ET_Z_HOMING_DIR_UP)
    #define Z_HOME_DIR  1
#else
    #define Z_HOME_DIR -1
#endif

//
// Temp sensors
//

// Undefine to overwrite
#undef TEMP_SENSOR_0

// Redefine
#if (ET_MOD & ET_MOD_V6)
    #define TEMP_SENSOR_0 5
#else 
    #define TEMP_SENSOR_0 1
#endif

//
// Drivers
//

// Undefine to overwrite
#undef X_DRIVER_TYPE
#undef Y_DRIVER_TYPE
#undef Z_DRIVER_TYPE
#undef E0_DRIVER_TYPE
#undef MOTHERBOARD

// Redefine
#if (ET_BOARD & ET_BOARD_SILENT)
      #define MOTHERBOARD BOARD_ANET_ET4P
    #define X_DRIVER_TYPE TMC2208_STANDALONE
    #define Y_DRIVER_TYPE TMC2208_STANDALONE
    #define Z_DRIVER_TYPE TMC2208_STANDALONE
    #define E0_DRIVER_TYPE TMC2208_STANDALONE
#elif (ET_BOARD & ET_BOARD_NOISY)
    #define MOTHERBOARD BOARD_ANET_ET4
    #define X_DRIVER_TYPE A4988
    #define Y_DRIVER_TYPE A4988
    #define Z_DRIVER_TYPE A4988
    #define E0_DRIVER_TYPE A4988
#else
    #error "You must define an ET_BOARD value among [ET_BOARD_NOISY, ET_BOARD_SILENT]."
#endif

//
// Steps / Extruder dir
//

// Undefine to overwrite
#undef INVERT_E0_DIR
#undef DEFAULT_AXIS_STEPS_PER_UNIT

// Redefine
#if (ET_MOD & ET_MOD_BMG)
    #define INVERT_E0_DIR true
    #define DEFAULT_AXIS_STEPS_PER_UNIT   { 80, 80, 400, 415 }
#elif (ET_MOD & ET_MOD_BMG_MINI)
    #define INVERT_E0_DIR false
    #define DEFAULT_AXIS_STEPS_PER_UNIT   { 80, 80, 400, 140 }
#else
    #define INVERT_E0_DIR false
    #define DEFAULT_AXIS_STEPS_PER_UNIT   { 80, 80, 400, 100 }
#endif

//
// Size and endstop offsets
//

// Undefine to overwrite
#undef X_BED_SIZE
#undef Y_BED_SIZE
#undef X_MIN_POS
#undef Y_MIN_POS
#undef Z_MIN_POS
#undef X_MAX_POS
#undef Y_MAX_POS
#undef Z_MAX_POS

#if(ET_MOD & ET_MOD_V6)
    #define ET_Z_MAX_POS_EXTRA    3
#else
    #define ET_Z_MAX_POS_EXTRA    0
#endif

// Redefine
#if (ET_MODEL & ET_SERIES_5)
    #define X_BED_SIZE 300
    #define Y_BED_SIZE 300
    #define X_MIN_POS 0
    #define Y_MIN_POS -15
    #define Z_MIN_POS 0
    #define X_MAX_POS (X_BED_SIZE + 50)
    #define Y_MAX_POS Y_BED_SIZE
    #define Z_MAX_POS (400 + ET_Z_MAX_POS_EXTRA)
#elif (ET_MODEL & ET_SERIES_4)
    #define X_BED_SIZE 220
    #define Y_BED_SIZE 220
    #define X_MIN_POS -1
    #define Y_MIN_POS -11
    #define Z_MIN_POS 0
    #define X_MAX_POS (X_BED_SIZE + 50)
    #define Y_MAX_POS Y_BED_SIZE
    #define Z_MAX_POS (250 + ET_Z_MAX_POS_EXTRA)
#endif

//
// TFT
//

// Undefine to overwrite
#undef TFT_GENERIC
#undef TFT_DRIVER
#undef TFT_INTERFACE_FSMC
#undef TFT_COLOR_UI
#undef TFT_RES_480x320
#undef TFT_RES_320x240
#undef TFT_ROTATION
#undef ANET_ET4_TFT28
#undef ANET_ET5_TFT35

// Redefine
#define TFT_COLOR_UI

#if (ET_MODEL & ET_SERIES_5)
    #define ANET_ET5_TFT35
#elif (ET_MODEL & ET_SERIES_4)
    #define ANET_ET4_TFT28
#endif

//
// Touch Calibration
//

// Undefine to overwrite
#undef XPT2046_X_CALIBRATION
#undef XPT2046_Y_CALIBRATION
#undef XPT2046_X_OFFSET
#undef XPT2046_Y_OFFSET
#undef XPT2046_ORIENTATION

// Redefine

#ifndef TOUCH_SCREEN
    #define TOUCH_SCREEN
#endif

#ifndef TOUCH_SCREEN_CALIBRATION
    #define TOUCH_SCREEN_CALIBRATION
#endif