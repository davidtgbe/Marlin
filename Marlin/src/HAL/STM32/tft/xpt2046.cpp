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

#include "../../platforms.h"

#ifdef HAL_STM32

#include "../../../inc/MarlinConfig.h"

#if HAS_TFT_XPT2046 || HAS_RES_TOUCH_BUTTONS

#include "xpt2046.h"
#include "pinconfig.h"

uint16_t delta(uint16_t a, uint16_t b) { return a > b ? a - b : b - a; }

SPI_HandleTypeDef XPT2046::SPIx;

void XPT2046::init() {
  SPI_TypeDef *spiInstance;

  OUT_WRITE(TOUCH_CS_PIN, HIGH);

  #if PIN_EXISTS(TOUCH_INT)
    // Optional Pendrive interrupt pin
    SET_INPUT(TOUCH_INT_PIN);
  #endif

  spiInstance      = (SPI_TypeDef *)pinmap_peripheral(digitalPinToPinName(TOUCH_SCK_PIN),  PinMap_SPI_SCLK);
  if (spiInstance != (SPI_TypeDef *)pinmap_peripheral(digitalPinToPinName(TOUCH_MOSI_PIN), PinMap_SPI_MOSI)) spiInstance = NP;
  if (spiInstance != (SPI_TypeDef *)pinmap_peripheral(digitalPinToPinName(TOUCH_MISO_PIN), PinMap_SPI_MISO)) spiInstance = NP;

  SPIx.Instance                = spiInstance;

  if (SPIx.Instance) {
    SPIx.State                   = HAL_SPI_STATE_RESET;
    SPIx.Init.NSS                = SPI_NSS_SOFT;
    SPIx.Init.Mode               = SPI_MODE_MASTER;
    SPIx.Init.Direction          = SPI_DIRECTION_2LINES;
    SPIx.Init.BaudRatePrescaler  = SPI_BAUDRATEPRESCALER_8;
    SPIx.Init.CLKPhase           = SPI_PHASE_2EDGE;
    SPIx.Init.CLKPolarity        = SPI_POLARITY_HIGH;
    SPIx.Init.DataSize           = SPI_DATASIZE_8BIT;
    SPIx.Init.FirstBit           = SPI_FIRSTBIT_MSB;
    SPIx.Init.TIMode             = SPI_TIMODE_DISABLE;
    SPIx.Init.CRCCalculation     = SPI_CRCCALCULATION_DISABLE;
    SPIx.Init.CRCPolynomial      = 10;

    pinmap_pinout(digitalPinToPinName(TOUCH_SCK_PIN), PinMap_SPI_SCLK);
    pinmap_pinout(digitalPinToPinName(TOUCH_MOSI_PIN), PinMap_SPI_MOSI);
    pinmap_pinout(digitalPinToPinName(TOUCH_MISO_PIN), PinMap_SPI_MISO);

    #ifdef SPI1_BASE
      if (SPIx.Instance == SPI1) {
        __HAL_RCC_SPI1_CLK_ENABLE();
        SPIx.Init.BaudRatePrescaler  = SPI_BAUDRATEPRESCALER_16;
      }
    #endif
    #ifdef SPI2_BASE
      if (SPIx.Instance == SPI2) {
        __HAL_RCC_SPI2_CLK_ENABLE();
      }
    #endif
    #ifdef SPI3_BASE
      if (SPIx.Instance == SPI3) {
        __HAL_RCC_SPI3_CLK_ENABLE();
      }
    #endif
  }
  else {
    SPIx.Instance = nullptr;
    SET_INPUT(TOUCH_MISO_PIN);
    SET_OUTPUT(TOUCH_MOSI_PIN);
    SET_OUTPUT(TOUCH_SCK_PIN);
  }

  getRawData(XPT2046_Z1);
}

bool XPT2046::isTouched() {
  return isBusy() ? false : (
    #if PIN_EXISTS(TOUCH_INT)
      READ(TOUCH_INT_PIN) != HIGH
    #else
      getRawData(XPT2046_Z1) >= XPT2046_Z1_THRESHOLD
    #endif
  );
}

/* 20220202 rmm
bool XPT2046::getRawPoint(int16_t *x, int16_t *y) {
  if (isBusy()) return false;
  if (!isTouched()) return false;
  *x = getRawData(XPT2046_X);
  *y = getRawData(XPT2046_Y);
  return isTouched();
}

uint16_t XPT2046::getRawData(const XPTCoordinate coordinate) {
  uint16_t data[3];
uint32_t now = millis() ;

  dataTransferBegin();

  for (uint16_t i = 0; i < 3 ; i++) {
    IO(coordinate);
    data[i] = (IO() << 4) | (IO() >> 4);
  }

  dataTransferEnd();

  uint16_t delta01 = delta(data[0], data[1]);
  uint16_t delta02 = delta(data[0], data[2]);
  uint16_t delta12 = delta(data[1], data[2]);

  if (delta01 > delta02 || delta01 > delta12) {
    if (delta02 > delta12)
      data[0] = data[2];
    else
      data[1] = data[2];
  }

  return (data[0] + data[1]) >> 1;
}
 rmm */


//---- 20220202 rmm

#define BUFFER_LENGTH 16  // > ( FILTER_TIME + END_TRANSIENT_TIME  ) / MIN_SAMPLING_TIME
#define MIN_SAMPLING_TIME 3
#define START_TRANSIENT_TIME ( 10 * MIN_SAMPLING_TIME )
#define END_TRANSIENT_TIME ( 5 * MIN_SAMPLING_TIME )
#define FILTER_TIME ( 5 * MIN_SAMPLING_TIME )


bool XPT2046::getRawPoint(int16_t *x, int16_t *y) {
  static uint32_t buf_t[ BUFFER_LENGTH ] ;
  static int16_t buf_x[ BUFFER_LENGTH ] ;
  static int16_t buf_y[ BUFFER_LENGTH ] ;
  static uint16_t n_samples = 0 ;
  static uint16_t buf_ind = 0 ;
  static uint32_t t_start = 0 ;

  static int16_t x_lp, y_lp ;
  static uint32_t t_lp = 0 ;
  static bool valid_lp = false ; // Last point valid.

  uint32_t now ;
  if (isBusy()) return false;

  now = millis() ;
  // If not enough time, return last point.
  if ( (now - t_lp) >= MIN_SAMPLING_TIME )
  {
    t_lp = now ;

    // Calculate current point.

    // If not touched, not point.
    if ( !isTouched() )
    {
      x_lp = 0 ;
      y_lp = 0 ;
      valid_lp = false ;

      // Clear buffer.
      n_samples = 0 ;
      t_start = 0 ;
    }
    else
    {
      int16_t sample_x, sample_y ;
      bool valid_sample ;

      sample_x = getRawData(XPT2046_X);
      valid_sample = isTouched() ;
      sample_y = getRawData(XPT2046_Y);
      valid_sample = isTouched() ;

      if ( !valid_sample )
      {
        x_lp = 0 ;
        y_lp = 0 ;
        valid_lp = false ;

        // Clear buffer.
        n_samples = 0 ;
        t_start = 0 ;
      }
      else
      {
        // Is this first touching event?
        if ( !t_start )
        {
          t_start = now ;  // If now is 0 then this event will be discarded...
          n_samples = 0 ;
        }

        // Add sample to buffer if not in transient time.

        if ( (now - t_start) > START_TRANSIENT_TIME )
        {
          buf_x[ buf_ind ] = sample_x ;
          buf_y[ buf_ind ] = sample_y ;
          buf_t[ buf_ind ] = now ;
          n_samples = ( n_samples + 1 ) % BUFFER_LENGTH ;  // discard too many samples...


          // Valid point if elapsed transient time + average time + end transient time
          if ( ( now - t_start ) > ( START_TRANSIENT_TIME + FILTER_TIME + END_TRANSIENT_TIME ) )
          {
            // Filter the samples between now-transient_time-filter_time and now-transient_time
            // Lets take the average but maybe median would be better (but cpu expensive).
            uint32_t t1, t2 ;
            int32_t sx, sy, ns ;
            sx = 0 ;
            sy = 0 ;
            ns = 0 ;
            t1 = now - START_TRANSIENT_TIME - FILTER_TIME ;
            t2 = now - END_TRANSIENT_TIME ;
            for ( uint16_t i = 0 ; i < n_samples ; ++i )
            {
              uint16_t j ;
              uint32_t t ;
              j = ( buf_ind + BUFFER_LENGTH - i ) % BUFFER_LENGTH ;
              t = buf_t[ j ] ;
              if ( ( t > t1 ) && ( t < t2 ) )
              {
                sx += buf_x[ j ] ;
                sy += buf_y[ j ] ;
                ++ns ;
              }
            }

            if ( ns )
            {
              x_lp = sx / ns ;
              y_lp = sy / ns ;
              valid_lp = true ;

//              SERIAL_ECHOLNPGM( "t ", now, " x_lp ", x_lp, " y_lp ", y_lp ) ;
            }
          }
          buf_ind = ( buf_ind + 1 ) % BUFFER_LENGTH ;
        }
        // else not needed to add 
      }
    }
  }

  *x = x_lp ;
  *y = y_lp ;
  return valid_lp ;
}

uint16_t XPT2046::getRawData(const XPTCoordinate coordinate) {
  uint16_t data ;

  DataTransferBegin();
  IO(coordinate);
  data = (IO() << 5) | (IO() >> 3);
  DataTransferEnd();

  return data ;
}

//---- 20220202 rmm


uint16_t XPT2046::hardwareIO(uint16_t data) {
  __HAL_SPI_ENABLE(&SPIx);
  while ((SPIx.Instance->SR & SPI_FLAG_TXE) != SPI_FLAG_TXE) {}
  SPIx.Instance->DR = data;
  while ((SPIx.Instance->SR & SPI_FLAG_RXNE) != SPI_FLAG_RXNE) {}
  __HAL_SPI_DISABLE(&SPIx);

  return SPIx.Instance->DR;
}

uint16_t XPT2046::softwareIO(uint16_t data) {
  uint16_t result = 0;

  for (uint8_t j = 0x80; j > 0; j >>= 1) {
    WRITE(TOUCH_SCK_PIN, LOW);
    __DSB();
    WRITE(TOUCH_MOSI_PIN, data & j ? HIGH : LOW);
    __DSB();
    if (READ(TOUCH_MISO_PIN)) result |= j;
    __DSB();
    WRITE(TOUCH_SCK_PIN, HIGH);
    __DSB();
  }
  WRITE(TOUCH_SCK_PIN, LOW);
  __DSB();

  return result;
}

#endif // HAS_TFT_XPT2046
#endif // HAL_STM32
