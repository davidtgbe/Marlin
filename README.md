# Marlin for ET4

This project is an effort to try to adapt the Anet ET4 motherboard and display for use with Marlin.
Anyone can contribute to completing this project. Feedback is also welcome.

## Current status

### Working:
  - XYZ Steppers
  - Extruder
  - SD Card
  - USB comunication / pronterface
  - TFT
  - Filament runout detector.
  - EEPROM
  - Powerloss. See issues tab. 
  
### On progress:
  - PC/SD firmware load/update: There is no bootloader currently. Best option would be use stock ET4 bootloader.
 
### To take a look:
  - All files on path "Marlin\buildroot\share\PlatformIO\variants\ET4\" should be adapted to ET4 Board. Specially peripheralPins.c, variant.cpp, variant.h etc..
 
### Known bugs:

I have enabled issues tab. Please, try to be detailed regarding use cases and other useful information like hardware and software context. 
To get help on creating an issue see [this](https://docs.github.com/en/enterprise/2.15/user/articles/creating-an-issue).

## BUILD/INSTALLATION

  DISCLAIMER: Not for production use. This is an unfinished project and under development. I am not responsible for what may happen to the motherboard or printer. Use only at your own risk.

Currently you can only flash this firmware using a flasher (stlink, jlink, bmp etc).

### Before flashing this firmware (optional, but recommended):</br>

I recommend making a backup of your firmware. At least your bootlaoder (addresses from 0x08000000 to 0x08010000). This way, you can always recover/return to stock firmware by:</br>
  1. flashing the bootloader backup on the same addresses (0x08000000 - 0x8010000)</br>
  2. flashing any of the available Anet firmwares from address 0x08010000.</br>

If you don't perform this step, and, just in case of brick, there are copies of stock firmware ET4 releases and bootloader below on resources section.

### Flashing this firmware:</br>

There are several tutorials available for [stlink](https://www.cnx-software.com/2020/02/04/how-to-recover-from-a-bad-firmware-upgrade-on-anet-et4-3d-printer/)/[j-link](https://danielabalo.wordpress.com/flasear-anet-et4/) flashers. 

This firmware lacks of bootloader, so you have to flash it from address 0x8000000.
  1. Download or clone this repo.
  2. Make sure to modify your config.h and config_adv.h according to your ET4 model (ET4, ET4 PRO, ET4+, ...)
     - Settings as driver model (A4988/TMC2208), Z endstop position (UP/DOWN), bed size, auto bed levelling sensor, etc, need to be defined.
     - Provided config is for ET4/TM2208 model with attachable bed levelling sensor.
  3. Build project with platform io on VS code is recommended.
  4. Burn firmware with your flasher (.elf or .bin starting from 0x08000000 address).

You can connect with pronterface to corresponding com port @115200bps.

## HARDWARE

MCU: STM32F407VGT6 ARM CORTEX M4 => https://www.st.com/resource/en/datasheet/dm00037051.pdf</br>
DRIVERS: TMC2208 (silent) / A4988 (noisy)</br>
USB TO SERIAL CONVERTER: CH340G => https://www.mpja.com/download/35227cpdata.pdf</br>
FLASH: WINBOND W25Q128JVSQ (128M-bit) Serial Flash memory => https://www.winbond.com/resource-files/w25q128jv%20revf%2003272018%20plus.pdf</br>
EEPROM: AT24C04C (ATMLH744 04CM) 4 Kb =>https://datasheet.lcsc.com/szlcsc/1809192313_Microchip-Tech-AT24C04C-SSHM-T_C6205.pdf</br>
LCD: ST7789V | STP320240_0280E2T (40P/1,5): ST7789 (YT280S008)  => https://a.aliexpress.com/_dV4Bghv | https://www.crystalfontz.com/controllers/Sitronix/ST7789V/470/</br>
TOUCH: XPT2046 => https://ldm-systems.ru/f/doc/catalog/HY-TFT-2,8/XPT2046.pdf</br>
MOSFETS (BED/HOTEND): G90N04</br>
CLK: JF8.000 (8MHZ MCU EXT CLK)</br>
CLK: JF12.000 (12 MHZ USB-UART CLK)</br>
SS56: SCHOTTKY DIODE</br>
AMS1117 3.3 DN811: REGULATOR</br>
030N06: MOSFETs</br>
A19T: TRANSISTOR</br>
XL2596S -5.0E1 83296: STEP DOWN DC CONVERTER 3A/150KHZ</br>
293 STG9834 / LM293DT: 2x Voltage comparators => https://www.st.com/resource/en/datasheet/lm193.pdf</br>

## PIN MAPPING

E-STEP => PB9</br>
E-DIR => PB8</br>
E-ENABLE => PE0</br>
</br>
X-STEP => PB6</br>
X-DIR => PB5</br>
X-ENABLE => PB7</br>
</br>
Y-STEP => PB3</br>
Y-DIR => PD6</br>
Y-ENABLE => PB4</br>
</br>
Z-STEP => PA12</br>
Z-DIR => PA11</br>
Z-ENABLE => PA15</br>
</br>
Y-LIMIT => PE12</br>
X-LIMIT => PC13</br>
Z-LIMIT => PE11</br>
</br>
TEMP_BED => PA4</br>
TEMP_EXB1 => PA1</br>
</br>
END_FAN => PE1</br>
LAY_FAN => PE3</br>
</br>
END_CONTROL => PA0</br>
BED_CONTROL => PE2</br>
</br>
LV_DET => PC3</br>
MAT_DET1 => PA2</br>
POWER_LOSS_DET => PA8 (provided by ANET)</br>
</br>
SDIO_D2 => PC10</br>
SDIO_D3 => PC11</br>
SDIO_CMD => PD2</br>
SDIO_CLK => PC12</br>
SDIO_D0 => PC8</br>
SDIO_D1 => PC9</br>
TF_DET => PD3</br>
</br>
USB_USART1_TX => PA9</br>
USB_USART1_RX => PA10</br>
</br>
RESET_BTN => NRST (14)</br>
LED_D2 => PD12</br>
</br>
WINBOND_CS => PB12</br>
WINBOND_DO => PB14</br>
WINBOND_DI => PB15</br>
WINBOND_CLK => PB13</br>
</br>
EEPROM_A1 => GND</br>
EEPROM_A2 => GND</br>
EEPROM_SDA => PB11</br>
EEPROM_SCL => PB10</br>
</br>
P1_1_LCD_9_CSX => PD7</br>
P1_2_LCD_11_WRX => PD5</br>
P1_3_TOUCH_15_/CS => PB2</br>
P1_4_TOUCH_14_DIN => PE5</br>
P1_5_TOUCH_12_DOUT => PE4</br>
P1_6_TOUCH_16_DCLK => PB0</br>
P1_7_TOUCH_11_/PENIRQ => PB1</br>
P1_8_LCD_12_RDX => PD4</br>
P1_9 => GND</br>
P1_10 => 3.3V</br>
</br>
P2_1_LCD_15_RESX => PE6</br>
P2_2_LCD_10_DCX => PD13</br>
P2_3_LCD_26_DB9 => PD15</br>
P2_4_LCD_25_DB8 => PD14</br>
P2_5_LCD_28_DB11 => PD1</br>
P2_6_LCD_27_DB10 => PD0</br>
P2_7_LCD_30_DB13 => PE8</br>
P2_8_LCD_29_DB12 => PE7</br>
P2_9_LCD_32_DB15 => PE10</br>
P2_10_LCD_31_DB14 => PE9</br>

## Resources

[ET4 Telegram Spanish Group Resources](https://drive.google.com/drive/folders/1bVusF9dMh1H7c2JM5ZWlbn2tWRGKsHre)</br>
[ET4 Board and specs](https://es.aliexpress.com/item/4000571722465.html?spm=a2g0o.productlist.0.0.5c647634dDFWSV&algo_pvid=9a06cdcd-c1f2-45a0-adcf-36da50fefff7&algo_expid=9a06cdcd-c1f2-45a0-adcf-36da50fefff7-2&btsid=0ab6f83115911132482433653e39a1&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_)

## Acknowledgements

- To the mates of the [Telegram Anet ET4 spanish group](https://t.me/anetet4esp), specially to @Solidnon, who lent his board for testing when the project was not even started.
- To @uwe and @mubes from Black Magic Probe team, and to Ebiroll (BMP/ESP32).
- To all contributors and testers of this branch and, specially, of Marlin master branch.

# Marlin 3D Printer Firmware

![GitHub](https://img.shields.io/github/license/marlinfirmware/marlin.svg)
![GitHub contributors](https://img.shields.io/github/contributors/marlinfirmware/marlin.svg)
![GitHub Release Date](https://img.shields.io/github/release-date/marlinfirmware/marlin.svg)
[![Build Status](https://github.com/MarlinFirmware/Marlin/workflows/CI/badge.svg?branch=bugfix-2.0.x)](https://github.com/MarlinFirmware/Marlin/actions)

<img align="right" width=175 src="buildroot/share/pixmaps/logo/marlin-250.png" />

Additional documentation can be found at the [Marlin Home Page](https://marlinfw.org/).
Please test this firmware and let us know if it misbehaves in any way. Volunteers are standing by!

## Marlin 2.0 Bugfix Branch

__Not for production use. Use with caution!__

Marlin 2.0 takes this popular RepRap firmware to the next level by adding support for much faster 32-bit and ARM-based boards while improving support for 8-bit AVR boards. Read about Marlin's decision to use a "Hardware Abstraction Layer" below.

This branch is for patches to the latest 2.0.x release version. Periodically this branch will form the basis for the next minor 2.0.x release.

Download earlier versions of Marlin on the [Releases page](https://github.com/MarlinFirmware/Marlin/releases).

## Building Marlin 2.0

To build Marlin 2.0 you'll need [Arduino IDE 1.8.8 or newer](https://www.arduino.cc/en/main/software) or [PlatformIO](https://docs.platformio.org/en/latest/ide.html#platformio-ide). We've posted detailed instructions on [Building Marlin with Arduino](https://marlinfw.org/docs/basics/install_arduino.html) and [Building Marlin with PlatformIO for ReArm](https://marlinfw.org/docs/basics/install_rearm.html) (which applies well to other 32-bit boards).

## Hardware Abstraction Layer (HAL)

Marlin 2.0 introduces a layer of abstraction so that all the existing high-level code can be built for 32-bit platforms while still retaining full 8-bit AVR compatibility. Retaining AVR compatibility and a single code-base is important to us, because we want to make sure that features and patches get as much testing and attention as possible, and that all platforms always benefit from the latest improvements.

### Current HALs

  #### AVR (8-bit)

  board|processor|speed|flash|sram|logic|fpu
  ----|---------|-----|-----|----|-----|---
  [Arduino AVR](https://www.arduino.cc/)|ATmega, ATTiny, etc.|16-20MHz|64-256k|2-16k|5V|no

  #### DUE

  boards|processor|speed|flash|sram|logic|fpu
  ----|---------|-----|-----|----|-----|---
  [Arduino Due](https://www.arduino.cc/en/Guide/ArduinoDue), [RAMPS-FD](https://www.reprap.org/wiki/RAMPS-FD), etc.|[SAM3X8E ARM-Cortex M3](https://www.microchip.com/wwwproducts/en/ATsam3x8e)|84MHz|512k|64+32k|3.3V|no

  #### ESP32

  board|processor|speed|flash|sram|logic|fpu
  ----|---------|-----|-----|----|-----|---
  [ESP32](https://www.espressif.com/en/products/hardware/esp32/overview)|Tensilica Xtensa LX6|240MHz|---|---|3.3V|---

  #### LPC1768 / LPC1769

  boards|processor|speed|flash|sram|logic|fpu
  ----|---------|-----|-----|----|-----|---
  [Re-ARM](https://www.kickstarter.com/projects/1245051645/re-arm-for-ramps-simple-32-bit-upgrade)|[LPC1768 ARM-Cortex M3](https://www.nxp.com/products/microcontrollers-and-processors/arm-based-processors-and-mcus/lpc-cortex-m-mcus/lpc1700-cortex-m3/512kb-flash-64kb-sram-ethernet-usb-lqfp100-package:LPC1768FBD100)|100MHz|512k|32+16+16k|3.3-5V|no
  [MKS SBASE](https://reprap.org/forum/read.php?13,499322)|LPC1768 ARM-Cortex M3|100MHz|512k|32+16+16k|3.3-5V|no
  [Selena Compact](https://github.com/Ales2-k/Selena)|LPC1768 ARM-Cortex M3|100MHz|512k|32+16+16k|3.3-5V|no
  [Azteeg X5 GT](https://www.panucatt.com/azteeg_X5_GT_reprap_3d_printer_controller_p/ax5gt.htm)|LPC1769 ARM-Cortex M3|120MHz|512k|32+16+16k|3.3-5V|no
  [Smoothieboard](https://reprap.org/wiki/Smoothieboard)|LPC1769 ARM-Cortex M3|120MHz|512k|64k|3.3-5V|no

  #### SAMD51

  boards|processor|speed|flash|sram|logic|fpu
  ----|---------|-----|-----|----|-----|---
  [Adafruit Grand Central M4](https://www.adafruit.com/product/4064)|[SAMD51P20A ARM-Cortex M4](https://www.microchip.com/wwwproducts/en/ATSAMD51P20A)|120MHz|1M|256k|3.3V|yes

  #### STM32F1

  boards|processor|speed|flash|sram|logic|fpu
  ----|---------|-----|-----|----|-----|---
  [Arduino STM32](https://github.com/rogerclarkmelbourne/Arduino_STM32)|[STM32F1](https://www.st.com/en/microcontrollers-microprocessors/stm32f103.html) ARM-Cortex M3|72MHz|256-512k|48-64k|3.3V|no
  [Geeetech3D GTM32](https://github.com/Geeetech3D/Diagram/blob/master/Rostock301/Hardware_GTM32_PRO_VB.pdf)|[STM32F1](https://www.st.com/en/microcontrollers-microprocessors/stm32f103.html) ARM-Cortex M3|72MHz|256-512k|48-64k|3.3V|no

  #### STM32F4

  boards|processor|speed|flash|sram|logic|fpu
  ----|---------|-----|-----|----|-----|---
  [STEVAL-3DP001V1](https://www.st.com/en/evaluation-tools/steval-3dp001v1.html)|[STM32F401VE Arm-Cortex M4](https://www.st.com/en/microcontrollers-microprocessors/stm32f401ve.html)|84MHz|512k|64+32k|3.3-5V|yes

  #### Teensy++ 2.0

  boards|processor|speed|flash|sram|logic|fpu
  ----|---------|-----|-----|----|-----|---
  [Teensy++ 2.0](https://www.microchip.com/wwwproducts/en/AT90USB1286)|[AT90USB1286](https://www.microchip.com/wwwproducts/en/AT90USB1286)|16MHz|128k|8k|5V|no

  #### Teensy 3.1 / 3.2

  boards|processor|speed|flash|sram|logic|fpu
  ----|---------|-----|-----|----|-----|---
  [Teensy 3.2](https://www.pjrc.com/store/teensy32.html)|[MK20DX256VLH7](https://www.mouser.com/ProductDetail/NXP-Freescale/MK20DX256VLH7) ARM-Cortex M4|72MHz|256k|32k|3.3V-5V|yes

  #### Teensy 3.5 / 3.6

  boards|processor|speed|flash|sram|logic|fpu
  ----|---------|-----|-----|----|-----|---
  [Teensy 3.5](https://www.pjrc.com/store/teensy35.html)|[MK64FX512VMD12](https://www.mouser.com/ProductDetail/NXP-Freescale/MK64FX512VMD12) ARM-Cortex M4|120MHz|512k|192k|3.3-5V|yes
  [Teensy 3.6](https://www.pjrc.com/store/teensy36.html)|[MK66FX1M0VMD18](https://www.mouser.com/ProductDetail/NXP-Freescale/MK66FX1M0VMD18) ARM-Cortex M4|180MHz|1M|256k|3.3V|yes

## Submitting Patches

Proposed patches should be submitted as a Pull Request against the ([bugfix-2.0.x](https://github.com/MarlinFirmware/Marlin/tree/bugfix-2.0.x)) branch.

- This branch is for fixing bugs and integrating any new features for the duration of the Marlin 2.0.x life-cycle.
- Follow the [Coding Standards](https://marlinfw.org/docs/development/coding_standards.html) to gain points with the maintainers.
- Please submit your questions and concerns to the [Issue Queue](https://github.com/MarlinFirmware/Marlin/issues).

### [RepRap.org Wiki Page](https://reprap.org/wiki/Marlin)

## Credits

The current Marlin dev team consists of:

 - Scott Lahteine [[@thinkyhead](https://github.com/thinkyhead)] - USA &nbsp; [Donate](https://www.thinkyhead.com/donate-to-marlin) / Flattr: [![Flattr Scott](https://api.flattr.com/button/flattr-badge-small.png)](https://flattr.com/submit/auto?user_id=thinkyhead&url=https://github.com/MarlinFirmware/Marlin&title=Marlin&language=&tags=github&category=software)
 - Roxanne Neufeld [[@Roxy-3D](https://github.com/Roxy-3D)] - USA
 - Chris Pepper [[@p3p](https://github.com/p3p)] - UK
 - Bob Kuhn [[@Bob-the-Kuhn](https://github.com/Bob-the-Kuhn)] - USA
 - João Brazio [[@jbrazio](https://github.com/jbrazio)] - Portugal
 - Erik van der Zalm [[@ErikZalm](https://github.com/ErikZalm)] - Netherlands &nbsp; [![Flattr Erik](https://api.flattr.com/button/flattr-badge-large.png)](https://flattr.com/submit/auto?user_id=ErikZalm&url=https://github.com/MarlinFirmware/Marlin&title=Marlin&language=&tags=github&category=software)

## License

Marlin is published under the [GPL license](/LICENSE) because we believe in open development. The GPL comes with both rights and obligations. Whether you use Marlin firmware as the driver for your open or closed-source product, you must keep Marlin open, and you must provide your compatible Marlin source code to end users upon request. The most straightforward way to comply with the Marlin license is to make a fork of Marlin on Github, perform your modifications, and direct users to your modified fork.

While we can't prevent the use of this code in products (3D printers, CNC, etc.) that are closed source or crippled by a patent, we would prefer that you choose another firmware or, better yet, make your own.
