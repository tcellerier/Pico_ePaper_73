/*****************************************************************************
* | File      	:   DEV_Config.h
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master
*                and enhance portability
*----------------
* |	This version:   V2.0
* | Date        :   2018-10-30
* | Info        :
* 1.add:
*   UBYTE\UWORD\UDOUBLE
* 2.Change:
*   EPD_RST -> EPD_RST_PIN
*   EPD_DC -> EPD_DC_PIN
*   EPD_CS -> EPD_CS_PIN
*   EPD_BUSY -> EPD_BUSY_PIN
* 3.Remote:
*   EPD_RST_1\EPD_RST_0
*   EPD_DC_1\EPD_DC_0
*   EPD_CS_1\EPD_CS_0
*   EPD_BUSY_1\EPD_BUSY_0
* 3.add:
*   #define DEV_Digital_Write(_pin, _value) bcm2835_GPIOI_write(_pin, _value)
*   #define DEV_Digital_Read(_pin) bcm2835_GPIOI_lev(_pin)
*   #define DEV_SPI_WriteByte(__value) bcm2835_spi_transfer(__value)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "hardware/watchdog.h"
#include "stdio.h"

/**
 * data
**/
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

#define EPD_SPI_PORT 	spi1
#define SD_SPI_PORT 	spi0
#define RTC_I2C_PORT    i2c1
#define RTC_I2C_Address 0x51

/**
 * GPIOI config
**/
#define EPD_RST_PIN     12
#define EPD_DC_PIN      8
#define EPD_CS_PIN      9
#define EPD_BUSY_PIN    13
#define EPD_CLK_PIN     10  
#define EPD_MOSI_PIN    11

#define RTC_SDA         14
#define RTC_SCL         15
#define RTC_INT         6

#define EPD_POWER_EN    16
#define CHARGE_STATE    17  // V2
#define BAT_OFF         18
#define BAT_STATE       19

#define LED_ACT         25
#define LED_PWR         26  // V2

#define SD_CS_PIN       5
#define SD_CLK_PIN      2
#define SD_MOSI_PIN     3
#define SD_MISO_PIN     4

#define VBUS            24
#define Power_Mode      23
#define VBAT            29

/*------------------------------------------------------------------------------------------------------*/
void DEV_Digital_Write(UWORD Pin, UBYTE Value);
UBYTE DEV_Digital_Read(UWORD Pin);

void DEV_SPI_WriteByte(UBYTE Value);
void DEV_SPI_Write_nByte(UBYTE *pData, UDOUBLE Len);

void I2C_Write_Byte(UBYTE Reg, UBYTE Value);
UBYTE I2C_Read_Byte(UBYTE Reg);

void DEV_Delay_ms(UDOUBLE xms);

UBYTE DEV_Module_Init(void);
void DEV_Module_Exit(void);

#endif
