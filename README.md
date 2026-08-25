# Marlin for ET4/5 series 3D printers
![counter](https://enoreg85bg22wzz.m.pipedream.net)

This project is an effort to try to adapt the Anet ET4/ET5 motherboard and display for use with Marlin.
Anyone can contribute to completing this project. Feedback is also welcome.

# Context

As I don't have a blog, I would like to leave a personal opinion here related with this project experience. To whom it may concern.

I started this project as a hobby, on the one hand in response to the demand from the Anet ET series user community (including myself) for a quality and versatile firmware for their printers, and on the other hand, of Anet's refusal to provide solutions to problems and shortcomings of the stock firmware (a [change.org](https://www.change.org/p/anet-open-firmware-for-the-anet-et4) was even launched)

Without much knowledge of either Marlin or the closed ET hardware, and with help from the community, we have Marlin in the ET series from some time now. It is hard to believe that a company that claims to be a leader in the 3D printing industry will not be able to employ some engineering resources to port Marlin. Or even to improve its own firmware, which most remarkable milestone on recent released V3.0.0 (jump from V1.x), is to support some new languages... 

It was also a surprise (or not so much seeing it in perspective) that, in a very timely manner, Anet contacted me to get on the open source bandwagon and offer me a paid collaboration, which, although it never took place, they rushed to make it public along with an open source campaign, providing Anet a kind of reconciliation with the community appearing to be involved in this project, and a way of selling more printers. Objective accomplished.

In summary, after some time dealing with Anet, my personal experience has been regrettable. The lack of seriousness shown by the company (even the CEO) is hard to believe. The only concern in this whole project has been from the marketing and sales point of view, never from their users needing, as they want to do see. Anet's style is more in line with the "let them solve it themselves, and we will take advantage of it" of a mediocre company of the heap than with the innovative company, concerned about the user experience that they want to pretend to be (or show).

## Current status

### Working:
  - XYZ Steppers
  - Extruder
  - SD Card
  - USB comunication / pronterface
  - TFT
  - Filament runout detector
  - EEPROM (Flash emulation)
  - Powerloss (Thanks to Zhiniukas & SidDrP)
  - [Bltouch](/docs/Tutorials/bltouch-en.md)
  - PC/SD firmware load/update
    - I've managed to get working OpenBLT, (PC-USB / SD / DFU) updates. ~~I'm still looking for a way to do a first time flash without flasher~~. A hardware flasher is very recommended for its price.
  - Onboard EEPROM I2C (4Kb/512B)
    - Adapted and working, but not usable. Onboard EEPROM IC is too small to store marlin config, so, expect EEPROM errors if used. Use FLASH_EEPROM_EMULATION instead or solder another 24CXX EEPROM IC (24C32 or above recommended).
  - Onboard FLASH (128Mb/16MB)
    - Ready. Tested LVGL from MKS (ET5 TFT). Not used, as not dedicated or universal LVGL UI has been designed AFAIK.
### On progress:
  - No work in progress
### Known bugs:

I have enabled issues tab. Please, try to be detailed regarding use cases and other useful information like hardware and software context. 
To get help on creating an issue see [this](https://docs.github.com/en/enterprise/2.15/user/articles/creating-an-issue).

## Build/Installation

  DISCLAIMER: Not for production use. This is an unfinished project and under development. I am not responsible for what may happen to the motherboard or printer. Use only at your own risk.

Currently you can only flash this firmware using a flasher (stlink, jlink, bmp etc), **unless** you already have flashed the openblt bootloader (BL).

## Before flashing this firmware (optional, but recommended):  

First time, I recommend making a backup of your firmware. At least your bootloader (addresses from 0x08000000 to 0x08010000). This way, you can always recover/return to stock firmware by:  
  1. flashing the bootloader backup, from address 0x08000000 to 0x8010000.  
  2. flashing any of the available Anet firmwares from address 0x08010000 onwards.  

If you don't perform this step, and, just in case of brick, there are copies of stock firmware ET4 releases and bootloader below on [resources](#resources) section.

## Considerations

Despite of using "ET4" naming, this firmware is valid for both ET4 and ET5 printers. Both printers mount the same board up until now.

You have two options to install/update this firmware:
- **Option A** > ***Not using a bootloader (BL)*** 
  - Firmware (Marlin) starts directly when you switch on the printer.
  - You need the flasher to perform firmware installation/updates.
  - Environment needs to be set to **Anet_ET4_no_bootloader**.
- **Option B** > ***Using a bootloader along with this firmware***
  - When you switch on the printer, bootloader (BL) starts first, and, if there are not any firmware updates incomming (on SD or through PC-USB), it loads the firmware (Marlin).
  - You need the flasher to **flash the BL** the first time. Once it is flashed, you **MUST** install/update your FW through your **BL**, either by **SD card or USB-PC**. You **MUST NOT** use the **flasher** to install/update the FW, as it will not work.
  - Environment needs to be set to **Anet_ET4_OpenBLT**.

## Step One: Building from sources

1. Download or clone this [repo](https://github.com/davidtgbe/Marlin/archive/master.zip). Ensure you build the firmware with **latest sources**, as firmware.srec file will not be built with older sources.

2. You have two options to configure your own Marlin build:
- a) **Recommended**. Use [EasyConfig](/Marlin/EasyConfig.h) for a simple configuration experience.
    - Make sure you read the whole EasyConfig.h file carefully. It contains instructions to configure it.
    - EasyConfig will override some paremeters of configuration.h and configuration_adv.h.
- b) Configure your build from scratch.
    - [User configurations](/config) **are neither updated nor maintaned**. Please, read the readme.md inside the config folder. **Don't copy paste these files.**
    - [Marlin configurations](https://github.com/MarlinFirmware/Configurations/tree/import-2.1.x/config/examples/Anet) can also be a place to take a look. **Don't copy paste these files** as there could be a version mismatch between them and this repo.
    - Make sure to modify your config.h and config_adv.h according to your ET4/5 model (ET4, ET5, ET4 PRO, ET4+, ...)
    - Settings as driver model (A4988/TMC2208), Z endstop position (UP/DOWN), TFT resolution, XYZ size, homming offsets, auto bed levelling sensor, etc, need to be defined according to your model.
    - Fine tunning could be needed (e.g. XYZE [steps](https://marlinfw.org/docs/gcode/M092.html) or offsets, Jerks, JD, LA, etc).

4. Build project with platform.io on VS code is recommended. Default environment to build is set to **Anet_ET4_OpenBLT**.
   There are many tutorials on the web. You can follow them, **ADAPTING** steps to build this project. This one [here](/docs/Tutorials/build-es.md) in spanish made by me, and just another one [here](https://3daddict.com/marlin-2-0-beginner-guide-for-3d-printer-firmware/).
5. If everything went well, you will find marlin binary files with extension **.[elf|bin|srec]**, generated in the build output folder:
```
<src_code_base_folder>\.pio\build\ET4\
```

## Step two Flashing/Installing the firmware  

There are several tutorials available for [stlink](https://www.cnx-software.com/2020/02/04/how-to-recover-from-a-bad-firmware-upgrade-on-anet-et4-3d-printer/)/[j-link](https://danielabalo.wordpress.com/flasear-anet-et4/) flashers. Take a look to them.

You have two options to install/update this firmware:
- **Option A >** If you are going to use the firmware **without** bootloader (environment Anet_ET4_no_bootloader):
  -  It is assumed you have built your firmware with no offset.
  -  As the firmware has been built without offset, and lacks of a bootloader, you have to just flash your firmware binary file (step 1.5) with your preferred flasher from address **0x8000000**.
- **Option B >** If you are going to use the firmware **with** bootloader (environment Anet_ET4_OpenBLT):
  - You need to flash the bootloader from address **0x08000000**. This step needs to be performed just once, so, you can skip this step if you have already done so. You can download the precompiled bootloader [binary](https://github.com/davidtgbe/openblt/releases), or, you can build it yourself from source code using [STM32 Cube IDE](https://www.st.com/en/development-tools/stm32cubeide.html).
  - After flashing the BL, you can disconnect your flasher, it will not be used anymore.
  - Now it is time to install de firmware. BL will assist us in this task, so, you must use a SD-CARD **OR** USB-PC/microboot to flash perform this step.
    - SD-CARD -> Copy file **firmware.srec** from build folder (step 1.5) in the root folder of the SD-CARD.
    - USB-PC/microboot -> 
      - Download microboot software. It is uploaded to github and you can download it from [here](https://github.com/davidtgbe/openblt/archive/master.zip).
      - Extract the .zip file you have just downloaded and browse to the folder **openblt/Host/**. You will find the **microboot.exe** executable.
      - Connect your printer via USB to your PC and get the COM port number.
      - Open **microboot.exe** executable and configure COM port number and speed (115200) through **settings** button. Then, click **browse** and search for the file **firmware.srec**. You will find it in the output build folder (step 1.5).
  - Switch off and then switch on the printer to begin the installation/update process.
  - ~~Screen will be white during the process, and, after 3 or 4 minutes, Marlin will appear on the screen.~~ If you have latest OpenBLT release, you will see the update process on screen and Marlin will start after flashing process.

You can connect with pronterface to corresponding COM port @250000bps.

### Flashing considerations

If you use bootloader, you **must not use the flasher to install/update the FW**. The bootloader inserts a special **checksum** in the firmware during the install/update process. Bootloader **checks** for this checksum before jumping to the firmware. If you use your **flasher** to install the firmware, this **checksum is not written**, and, therefore, bootloader **will not boot** the firmware ~~, and **your screen will be white**.~~ and OpenBLT will ask you to flash a firmware.

**DFU** mode (Device Firmware Upgrade) has been added to the bootloader. You can enter to it just by **pressing touchscreen while switching printer on**. By using DFU mode you can even update your bootloader without needing a hardware flasher, just using the PC-USB and the right [tool](https://www.st.com/en/development-tools/flasher-stm32.html).


*More info:*  
[SD-CARD update process](https://www.feaser.com/openblt/doku.php?id=manual:sdcard_demo)  
[PC-USB update process](https://www.feaser.com/openblt/doku.php?id=manual:microboot)
[OpenBLT project](https://github.com/davidtgbe/openblt)

## Hardware

![Board](docs/Tutorials/media/et4board.jpg)

MCU: [STM32F407VGT6 ARM CORTEX M4](https://www.st.com/resource/en/datasheet/dm00037051.pdf)  
DRIVERS: [TMC2208 (silent)](https://www.trinamic.com/fileadmin/assets/Products/ICs_Documents/TMC220x_TMC2224_datasheet_Rev1.09.pdf) / [A4988 (noisy)](https://www.pololu.com/file/0J450/a4988_DMOS_microstepping_driver_with_translator.pdf)  
USB TO SERIAL CONVERTER: [CH340G](https://www.mpja.com/download/35227cpdata.pdf)  
SERIAL FLASH MEMORY: [WINBOND W25Q128JVSQ (128M-bit)](https://www.winbond.com/resource-files/w25q128jv%20revf%2003272018%20plus.pdf)  
EEPROM: [AT24C04C (ATMLH744 04CM) 4 Kb](https://datasheet.lcsc.com/szlcsc/1809192313_Microchip-Tech-AT24C04C-SSHM-T_C6205.pdf)  
LCD ET4: [ST7789 @ 320x240 | STP320240_0280E2T (40P/1,5): ST7789 (YT280S008)](https://a.aliexpress.com/_dV4Bghv) | [ST7789V](https://www.crystalfontz.com/controllers/Sitronix/ST7789V/470/)  
LCD ET5: [ST7796S @ 480x320](https://www.displayfuture.com/Display/datasheet/controller/ST7796s.pdf)  
TOUCH: [XPT2046](https://ldm-systems.ru/f/doc/catalog/HY-TFT-2,8/XPT2046.pdf)  
MOSFETS (BED/HOTEND): [G90N04](https://datasheet.lcsc.com/szlcsc/1811281041_GOFORD-G90N04_C337510.pdf)  
CLK: JF8.000 (8MHZ MCU EXT CLK)  
CLK: JF12.000 (12 MHZ USB-UART CLK)  
SCHOTTKY DIODE: [SS56](https://www.taitroncomponents.com/catalog/Datasheet/SS52.pdf)  
REGULATOR: [AMS1117 3.3 DN811](http://www.advanced-monolithic.com/pdf/ds1117.pdf)  
MOSFET: [030N06](https://www.alldatasheet.es/view.jsp?Searchword=030N06&sField=3)  
MOSFET: [A19T](https://datasheetspdf.com/pdf/1401820/UMW/A19T/1)  
STEP DOWN DC CONVERTER: [XL2596S -5.0E1 83296 ](https://datasheetspdf.com/datasheet/XL2596.html)  
VOLTAGE COMPARATOR: [293 STG9834 / LM293DT](https://www.st.com/resource/en/datasheet/lm193.pdf)  

## Pin mapping

E-STEP => PB9  
E-DIR => PB8  
E-ENABLE => PE0  
  
X-STEP => PB6  
X-DIR => PB5  
X-ENABLE => PB7  
  
Y-STEP => PB3  
Y-DIR => PD6  
Y-ENABLE => PB4  
  
Z-STEP => PA12  
Z-DIR => PA11  
Z-ENABLE => PA15  
  
Y-LIMIT => PE12  
X-LIMIT => PC13  
Z-LIMIT => PE11  
  
TEMP_BED => PA4  
TEMP_EXB1 => PA1  
  
END_FAN => PE1  
LAY_FAN => PE3  
  
END_CONTROL => PA0  
BED_CONTROL => PE2  
  
LV_DET => PC3  
MAT_DET1 => PA2  
POWER_LOSS_DET => PA8 (PANET)  
POWER_LOSS_SUPERCAP_SWITCH => PA3 (Zhiniukas & SidDrP)
  
SDIO_D2 => PC10  
SDIO_D3 => PC11  
SDIO_CMD => PD2  
SDIO_CLK => PC12  
SDIO_D0 => PC8  
SDIO_D1 => PC9  
TF_DET => PD3  
  
USB_USART1_TX => PA9  
USB_USART1_RX => PA10  
  
RESET_BTN => NRST (14)  
LED_D2 => PD12  
  
WINBOND_CS => PB12  
WINBOND_DO => PB14  
WINBOND_DI => PB15  
WINBOND_CLK => PB13  
  
EEPROM_A1 => GND  
EEPROM_A2 => GND  
EEPROM_SDA => PB11  
EEPROM_SCL => PB10  
  
P1_1_LCD_9_CSX => PD7  
P1_2_LCD_11_WRX => PD5  
P1_3_TOUCH_15_/CS => PB2  
P1_4_TOUCH_14_DIN => PE5  
P1_5_TOUCH_12_DOUT => PE4  
P1_6_TOUCH_16_DCLK => PB0  
P1_7_TOUCH_11_/PENIRQ => PB1  
P1_8_LCD_12_RDX => PD4  
P1_9 => GND  
P1_10 => 3.3V  
  
P2_1_LCD_15_RESX => PE6  
P2_2_LCD_10_DCX => PD13  
P2_3_LCD_26_DB9 => PD15  
P2_4_LCD_25_DB8 => PD14  
P2_5_LCD_28_DB11 => PD1  
P2_6_LCD_27_DB10 => PD0  
P2_7_LCD_30_DB13 => PE8  
P2_8_LCD_29_DB12 => PE7  
P2_9_LCD_32_DB15 => PE10  
P2_10_LCD_31_DB14 => PE9  

## Resources

- [ET4 Telegram Spanish Group Resources](https://drive.google.com/drive/folders/1bVusF9dMh1H7c2JM5ZWlbn2tWRGKsHre)  
- [ET4 Board and specs](https://es.aliexpress.com/item/4000571722465.html?spm=a2g0o.productlist.0.0.5c647634dDFWSV&algo_pvid=9a06cdcd-c1f2-45a0-adcf-36da50fefff7&algo_expid=9a06cdcd-c1f2-45a0-adcf-36da50fefff7-2&btsid=0ab6f83115911132482433653e39a1&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_)
- [Bltouch installation](/docs/Tutorials/bltouch-en.md)
- [Change boot image](/docs/Tutorials/change-marlin-imgs-en.md)
- [Build Marlin (ES)](/docs/Tutorials/build-es.md)
- [EasyConfig.h](/Marlin/EasyConfig.h)
- [OpenBLT project](https://github.com/davidtgbe/openblt)

## Acknowledgements

- To the mates of the [Telegram Anet ET4 spanish group](https://t.me/anetet4esp), specially to @Solidnon, who lent his board for testing when the project was not even started.
- To @uwe and @mubes from Black Magic Probe team, and to Ebiroll (BMP/ESP32).
- To all contributors and testers of this branch and, specially, of Marlin master branch.


# Marlin 3D Printer Firmware

<p align="center"><img src="buildroot/share/pixmaps/logo/marlin-outrun-nf-500.png" height="250" alt="MarlinFirmware's logo" /></p>

<h1 align="center">Marlin 3D Printer Firmware</h1>

<p align="center">
    <a href="/LICENSE"><img alt="GPL-V3.0 License" src="https://img.shields.io/github/license/marlinfirmware/marlin.svg"></a>
    <a href="//github.com/MarlinFirmware/Marlin/graphs/contributors"><img alt="Contributors" src="https://img.shields.io/github/contributors/marlinfirmware/marlin.svg"></a>
    <a href="//github.com/MarlinFirmware/Marlin/releases"><img alt="Last Release Date" src="https://img.shields.io/github/release-date/MarlinFirmware/Marlin"></a>
    <a href="//github.com/MarlinFirmware/Marlin/actions/workflows/ci-build-tests.yml"><img alt="CI Status" src="https://github.com/MarlinFirmware/Marlin/actions/workflows/ci-build-tests.yml/badge.svg"></a>
    <a href="//github.com/sponsors/thinkyhead"><img alt="GitHub Sponsors" src="https://img.shields.io/github/sponsors/thinkyhead?color=db61a2"></a>
    <br />
    <a href="//bsky.app/profile/marlinfw.org"><img alt="Follow marlinfw.org on Bluesky" src="https://img.shields.io/badge/Follow%20@marlinfw.org-0085ff?logo=bluesky&logoColor=white"></a>
    <a href="//fosstodon.org/@marlinfirmware"><img alt="Follow MarlinFirmware on Mastodon" src="https://img.shields.io/mastodon/follow/109450200866020466?domain=https%3A%2F%2Ffosstodon.org&logoColor=%2300B&style=social"></a>
</p>

### 🌍 Translations

<table>
<tr>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=an">Aragonés</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=bg">Български</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=ca">Català</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=cs">Čeština</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=da">Dansk</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=de">Deutsch</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=el">Ελληνικά</a></td>
</tr>
<tr>
  <td><a href="//github.com/MarlinFirmware/Marlin">English</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=es">Español</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=eu">Euskara</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=fi">Suomi</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=fr">Français</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=gl">Galego</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=hr">Hrvatski</a></td>
</tr>
<tr>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=hu">Magyar</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=it">Italiano</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=ja">にほんご</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=ko">한국어</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=nl">Nederlands</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=pl">Polski</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=pt">Português</a></td>
</tr>
<tr>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=pt-BR">Português (Brasil)</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=ro">Română</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=ru">Русский</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=sk">Slovenčina</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=sv">Svenska</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=tr">Türkçe</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=uk">Українська</a></td>
</tr>
<tr>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=vi">Tiếng Việt</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=zh-CN">简体中文</a></td>
  <td><a href="//translate.google.com/translate?u=github.com/MarlinFirmware/Marlin&sl=auto&tl=zh-TW">繁體中文</a></td>
  <td></td>
  <td></td>
  <td></td>
  <td></td>
</tr>
</table>

Official documentation can be found at the [Marlin Home Page](//marlinfw.org/).

Please test this firmware and let us know if it misbehaves in any way. Volunteers are standing by!

---

## Marlin 2.1.3 Beta 3

**Not for production use. Use with caution!**

Marlin 2.1 supports both 32-bit ARM and 8-bit AVR boards while adding support for up to 9 coordinated axes and to up to 8 extruders.

## Configuration Migration

There are a lot of configuration changes in Marlin 2.1.3. We're working on automated tools to migrate configurations, so if you want to help us test those get in touch on the [Marlin Discord](//discord.com/servers/marlin-firmware-461605380783472640). If you need help migrating your configurations to Marlin 2.1.3, we'll have a dedicated channel for this purpose. Post your configurations there and we'll send back updated configurations. We can also send a built `firmware.bin` file if you need it.

## Example Configurations

Before you can build Marlin for your machine you'll need a configuration for your specific hardware. Upon request, your vendor will be happy to provide you with the complete source code and configurations for your machine, but you'll need to get updated configuration files if you want to install a newer version of Marlin. Fortunately, Marlin users have contributed hundreds of tested configurations to get you started. Visit the [MarlinFirmware/Configurations](//github.com/MarlinFirmware/Configurations) repository to find the right configuration for your hardware. Make sure to select a compatible branch! [The Marlin Download Page](//marlinfw.org/meta/download/) matches compatible software and configuration packages.

## Marlin Builds

We now publish builds for all our posted example configurations. See the [MarlinBuilds](//github.com/MarlinFirmware/MarlinBuilds) repository for details. This is a new process so bear with us while we work out all the best variants. If you like the way an example configuration works but think it could be better, please submit your suggested improvements in a **Pull Request**.

## Building Marlin 2.1

To build and upload Marlin you will use one of these tools:

- The free [Visual Studio Code](//code.visualstudio.com/download) using the [Auto Build Marlin](//marlinfw.org/docs/basics/auto_build_marlin.html) extension.
- Marlin is optimized to build with the [PlatformIO IDE](//platformio.org/) extension for Visual Studio Code.
- You can also use VSCode with devcontainer : See [Installing Marlin (VSCode devcontainer)](https://marlinfw.org/docs/basics/install_devcontainer_vscode.html).
- You can still build Marlin with [Arduino IDE](//www.arduino.cc/en/main/software) : See [Building Marlin with Arduino](//marlinfw.org/docs/basics/install_arduino.html). We hope to improve the Arduino build experience, but at this time, PlatformIO is the preferred choice.

## 32-bit ARM boards

Marlin is compatible with a plethora of 32-bit ARM boards, which offer ample computational power and memory and allows Marlin to deliver state-of-the-art performance and features we like to see in modern 3d printers. Some of the newer features in Marlin will require use of a 32-bit ARM board.

## 8-Bit AVR Boards

Marlin originates from the era of Arduino based 8-bit boards, and we aim to support 8-bit AVR boards in perpetuity. Both 32-bit and 8-bit boards are covered by a single code base that can apply to all machines. Our goal is to support casual hobbyists, tinkerers, and owners of older machines and boards, striving to allow them to benefit from the community's innovations just as much as those with fancier machines and newer boards. In addition, these venerable AVR-based machines are often the best for testing and feedback!

## Hardware Abstraction Layer (HAL)

Marlin's Hardware Abstraction Layer provides a common API for all the platforms it targets. This allows Marlin code to address the details of motion and user interface tasks at the lowest and highest levels with no system overhead, tying all events directly to the hardware clock.

Every new HAL opens up a world of hardware. Marlin currently has HALs for more than a dozen platforms. While AVR and STM32 are the most well known and popular ones, others like ESP32 and LPC1768 support a variety of less common boards. At this time, an HAL for RP2040 is available in beta; we would like to add one for the Duet3D family of boards. A HAL that wraps an RTOS is an interesting concept that could be explored.

Did you know that Marlin includes a Simulator that can run on Windows, macOS, and Linux? Join the Discord to help move these sub-projects forward!

### Supported Platforms

| Platform | MCU | Example Boards |
| --- | --- | --- |
| [Arduino AVR](//www.arduino.cc/) | ATmega | RAMPS, Melzi, RAMBo |
| [Teensy++ 2.0](//www.microchip.com/en-us/product/AT90USB1286) | AT90USB1286 | Printrboard |
| [Arduino Due](//www.arduino.cc/en/Guide/ArduinoDue) | SAM3X8E | RAMPS-FD, RADDS, RAMPS4DUE |
| [ESP32](//github.com/espressif/arduino-esp32) | ESP32 | FYSETC E4, E4d@BOX, MRR |
| [GD32](//www.gigadevice.com/) | GD32 ARM Cortex-M4 | Creality MFL GD32 V4.2.2 |
| [HC32](//www.huazhoucn.com/) | HC32 | Ender-2 Pro, Voxelab Aquila |
| [LPC1768](//www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/lpc1700-cortex-m3/512-kb-flash-64-kb-sram-ethernet-usb-lqfp100-package:LPC1768FBD100) | ARM® Cortex-M3 | MKS SBASE, Re-ARM, Selena Compact |
| [LPC1769](//www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/lpc1700-cortex-m3/512-kb-flash-64-kb-sram-ethernet-usb-lqfp100-package:LPC1769FBD100) | ARM® Cortex-M3 | Smoothieboard, Azteeg X5 mini, TH3D EZBoard |
| [Pico RP2040](//www.raspberrypi.com/documentation/microcontrollers/pico-series.html) | Dual Cortex M0+ | BigTreeTech SKR Pico |
| [STM32F103](//www.st.com/en/microcontrollers-microprocessors/stm32f103.html) | ARM® Cortex-M3 | Malyan M200, GTM32 Pro, MKS Robin, BTT SKR Mini |
| [STM32F401](//www.st.com/en/microcontrollers-microprocessors/stm32f401.html) | ARM® Cortex-M4 | ARMED, Rumba32, SKR Pro, Lerdge, FYSETC S6, Artillery Ruby |
| [STM32F7x6](//www.st.com/en/microcontrollers-microprocessors/stm32f7x6.html) | ARM® Cortex-M7 | The Borg, RemRam V1 |
| [STM32G0B1RET6](//www.st.com/en/microcontrollers-microprocessors/stm32g0x1.html) | ARM® Cortex-M0+ | BigTreeTech SKR mini E3 V3.0 |
| [STM32H743xIT6](//www.st.com/en/microcontrollers-microprocessors/stm32h743-753.html) | ARM® Cortex-M7 | BigTreeTech SKR V3.0, SKR EZ V3.0, SKR SE BX V2.0/V3.0 |
| [SAMD21P20A](//www.adafruit.com/product/4064) | ARM® Cortex-M0+ | Adafruit Grand Central M4 |
| [SAMD51P20A](//www.adafruit.com/product/4064) | ARM® Cortex-M4 | Adafruit Grand Central M4 |
| [Teensy 3.2/3.1](//www.pjrc.com/teensy/teensy31.html) | MK20DX256VLH7 ARM® Cortex-M4 |
| [Teensy 3.5](//www.pjrc.com/store/teensy35.html) | MK64FX512-VMD12 ARM® Cortex-M4 |
| [Teensy 3.6](//www.pjrc.com/store/teensy36.html) | MK66FX1MB-VMD18 ARM® Cortex-M4 |
| [Teensy 4.0](//www.pjrc.com/store/teensy40.html) | MIMXRT1062-DVL6B ARM® Cortex-M7 |
| [Teensy 4.1](//www.pjrc.com/store/teensy41.html) | MIMXRT1062-DVJ6B ARM® Cortex-M7 |
| Linux Native | x86 / ARM / RISC-V | Raspberry Pi GPIO |
| Simulator | Windows, macOS, Linux | Desktop OS |
| [All supported boards](//marlinfw.org/docs/hardware/boards.html#boards-list) | All platforms | All boards |

## Marlin Discord

The [Marlin Firmware Discord](//discord.gg/marlin-firmware-461605380783472640) is a great place to discuss issues with Marlin users and developers, get interactive help with troubleshooting, and build on your best ideas to improve to Marlin in tandem with the most active members of the development team.

<p align="center">
  <a target="_blank" href="https://discord.gg/marlin-firmware-461605380783472640">
    <img src="https://dcbadge.limes.pink/api/server/https://discord.gg/marlin-firmware-461605380783472640">
  </a>
</p>

## Other Marlin Support

The Issue Queue is reserved for Bug Reports and Feature Requests. Please use the following resources for help with configuration and troubleshooting:

- [Marlin Documentation](//marlinfw.org) - Official Marlin documentation
- ["Marlin Firmware"](//www.facebook.com/groups/1049718498464482/) Facebook Group
- [Marlin Forum](//forums.reprap.org/list.php?415) at RepRap.org
- ["Marlin Firmware for 3D Printers"](//www.facebook.com/groups/3Dtechtalk/) Facebook Group
- [Marlin Configuration](//www.youtube.com/results?search_query=marlin+configuration) playlist on YouTube

## Contributing Patches

Contribute your patches to Marlin by submitting a Pull Request to the ([bugfix-2.1.x](//github.com/MarlinFirmware/Marlin/tree/bugfix-2.1.x)) branch.

- We use the `bugfix-2.1.x` branch to fix bugs and integrate new features into the latest firmware. Use with caution!
- We maintain `lts-x.x.x` branches, mainly for vendors, so that older versions of Marlin can be patched as-needed to stay functional and fix bugs.
- Follow the [Coding Standards](//marlinfw.org/docs/development/coding_standards.html) to gain points with the maintainers.
- Please submit Feature Requests and Bug Reports to the [Issue Queue](//github.com/MarlinFirmware/Marlin/issues/new/choose). See above for user support.
- Whenever you add new features, be sure to add one or more build tests to `buildroot/tests`. Any tests added to a PR will be run within that PR on GitHub servers as soon as they are pushed. To minimize iteration be sure to run your new tests locally, if possible.
  - Local build tests:
    - All: `make tests-config-all-local`
    - Single: `make tests-config-single-local TEST_TARGET=...`
  - Local build tests in Docker:
    - All: `make tests-config-all-local-docker`
    - Single: `make tests-config-all-local-docker TEST_TARGET=...`
  - To run all unit test suites:
    - Using PIO: `platformio run -t test-marlin`
    - Using Make: `make unit-test-all-local`
    - Using Docker + make: `make unit-test-all-local-docker`
  - To run a single unit test suite:
    - Using PIO: `platformio run -t marlin_<test-suite-name>`
    - Using make: `make unit-test-single-local TEST_TARGET=<test-suite-name>`
    - Using Docker + make: `make unit-test-single-local-docker TEST_TARGET=<test-suite-name>`
- If your feature can be unit tested, add one or more unit tests. For more information see our documentation on [Unit Tests](test).

## Contributors

Marlin is constantly improving thanks to a huge number of contributors from all over the world bringing their specialties and talents. Huge thanks are due to [all the contributors](//github.com/MarlinFirmware/Marlin/graphs/contributors) who regularly patch up bugs, help direct traffic, and basically keep Marlin from falling apart. Marlin's continued existence would not be possible without them.

Marlin Firmware original logo design by Ahmet Cem TURAN [@ahmetcemturan](//github.com/ahmetcemturan).

## Project Leadership

| Name | Role | Link | Donate |
| --- | --- | --- | --- |
| 🇺🇸 Scott Lahteine | Project Lead | [[@thinkyhead](//github.com/thinkyhead)] | [❤️ Donate](//marlinfw.org/docs/development/contributing.html#donate) |
| 🇳🇿 Peter Ellens | Admin | [[@ellensp](//github.com/ellensp)] | [❤️ Donate](//ko-fi.com/ellensp) |
| 🇬🇧 Chris Pepper | Admin | [[@p3p](//github.com/p3p)] |
| 🇺🇸 Keith Bennett | Admin | [[@thisiskeithb](//github.com/thisiskeithb)] | [❤️ Donate](//github.com/sponsors/thisiskeithb) |
| 🇺🇸 Roxanne Neufeld | Admin | [[@Roxy-3D](//github.com/Roxy-3D)] |
| 🇺🇸 Jason Smith | Admin | [[@sjasonsmith](//github.com/sjasonsmith)] |
| 🇧🇷 Victor Oliveira | Admin | [[@rhapsodyv](//github.com/rhapsodyv)] |
| 🇺🇸 Bob Kuhn | Admin | [[@Bob-the-Kuhn](//github.com/Bob-the-Kuhn)] |
| 🇳🇱 Erik van der Zalm | Founder | [[@ErikZalm](//github.com/ErikZalm)] |

## Star History

<a id="starchart" href="//star-history.com/#MarlinFirmware/Marlin&Date">
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="https://api.star-history.com/svg?repos=MarlinFirmware/Marlin&type=Date&theme=dark" />
    <source media="(prefers-color-scheme: light)" srcset="https://api.star-history.com/svg?repos=MarlinFirmware/Marlin&type=Date" />
    <img alt="Star History Chart" src="https://api.star-history.com/svg?repos=MarlinFirmware/Marlin&type=Date" />
  </picture>
</a>

## License

Marlin is published under the [GPL license](/LICENSE) because we believe in open development. The GPL comes with both rights and obligations. Whether you use Marlin firmware as the driver for your open or closed-source product, you must keep Marlin open, and you must provide your compatible Marlin source code to end users upon request. The most straightforward way to comply with the Marlin license is to make a fork of Marlin on GitHub, perform your modifications, and direct users to your modified fork.
