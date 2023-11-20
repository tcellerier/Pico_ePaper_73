/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*----------------
* |	This version:   V3.0
* | Date        :   2019-07-31
* | Info        :   
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of theex Software, and to permit persons to  whom the Software is
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
#include "DEV_Config.h"


/**
 * GPIO read and write
**/
void DEV_Digital_Write(UWORD Pin, UBYTE Value)
{
	gpio_put(Pin, Value);
}

UBYTE DEV_Digital_Read(UWORD Pin)
{
	return gpio_get(Pin);
}

/**
 * SPI
**/
void DEV_SPI_WriteByte(UBYTE Value)
{
    spi_write_blocking(EPD_SPI_PORT, &Value, 1);
}

void DEV_SPI_Write_nByte(UBYTE *pData, uint32_t Len)
{
    spi_write_blocking(EPD_SPI_PORT, pData, Len);
}

/**
 * @brief I2C write byte
 * 
 * @param Reg 
 * @param Value 
 */
void I2C_Write_Byte(UBYTE Reg, UBYTE Value)
{
	UBYTE wbuff[2] = {Reg, Value};
	i2c_write_blocking(RTC_I2C_PORT, RTC_I2C_Address, wbuff, 2, false);
}

/**
 * @brief I2C read byte
 * 
 * @param Reg 
 * @return UBYTE 
 */
UBYTE I2C_Read_Byte(UBYTE Reg)
{
	UBYTE Value;
	i2c_write_blocking(RTC_I2C_PORT, RTC_I2C_Address, &Reg, 1, false);
	i2c_read_blocking(RTC_I2C_PORT, RTC_I2C_Address, &Value, 1, false);
	return Value;
}

/**
 * GPIO Mode
**/
void DEV_GPIO_Mode(UWORD Pin, UWORD Mode)
{
    gpio_init(Pin);
	if(Mode == 0 || Mode == GPIO_IN) {
		gpio_set_dir(Pin, GPIO_IN);
	} else {
		gpio_set_dir(Pin, GPIO_OUT);
	}
}

/**
 * delay x ms
**/
void DEV_Delay_ms(UDOUBLE xms)
{
	sleep_ms(xms);
	watchdog_update();
}

void DEV_GPIO_Init(void)
{
	// EPD
	DEV_GPIO_Mode(EPD_RST_PIN, 1);
	DEV_GPIO_Mode(EPD_DC_PIN, 1);
	DEV_GPIO_Mode(EPD_CS_PIN, 1);
	DEV_GPIO_Mode(EPD_BUSY_PIN, 0);
	// LED
	DEV_GPIO_Mode(LED_ACT, 1);
	DEV_GPIO_Mode(LED_PWR, 1);
	// SDCARD
	DEV_GPIO_Mode(SD_CS_PIN, 1);
	// RTC
	DEV_GPIO_Mode(RTC_INT, 0);
	gpio_pull_up(RTC_INT);
	// BAT
	DEV_GPIO_Mode(BAT_OFF, 1);
	DEV_GPIO_Mode(BAT_STATE, 0);
	gpio_pull_up(BAT_STATE);
	DEV_GPIO_Mode(CHARGE_STATE, 0);
	gpio_pull_up(CHARGE_STATE);
	// POWER
	DEV_GPIO_Mode(EPD_POWER_EN, 1);
	DEV_GPIO_Mode(VBUS, 0);
	

	DEV_Digital_Write(LED_ACT, 0);	// LED off
	DEV_Digital_Write(LED_PWR, 0);	// LED off
	DEV_Digital_Write(EPD_CS_PIN, 1);
	DEV_Digital_Write(BAT_OFF, 1);	// BAT on
	DEV_Digital_Write(EPD_POWER_EN, 1);	// EPD power on
}
/******************************************************************************
function:	Module Initialize, the library and initialize the pins, SPI protocol
parameter:
Info:
******************************************************************************/
UBYTE DEV_Module_Init(void)
{
    stdio_init_all();
	
    spi_init(EPD_SPI_PORT, 8000 * 1000);
    gpio_set_function(EPD_CLK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(EPD_MOSI_PIN, GPIO_FUNC_SPI);
	
	spi_init(SD_SPI_PORT, 12500 * 1000);
	gpio_set_function(SD_CLK_PIN, GPIO_FUNC_SPI);
	gpio_set_function(SD_MOSI_PIN, GPIO_FUNC_SPI);
	gpio_set_function(SD_MISO_PIN, GPIO_FUNC_SPI);

	i2c_init(RTC_I2C_PORT, 100 * 1000); 
	gpio_set_function(RTC_SDA, GPIO_FUNC_I2C);
    gpio_set_function(RTC_SCL, GPIO_FUNC_I2C);

	adc_init();
	adc_gpio_init(VBAT);
	adc_select_input(3);

	// GPIO Config
	DEV_GPIO_Init();

    printf("DEV_Module_Init OK \r\n");
	return 0;
}

/******************************************************************************
function:	Module exits, closes SPI and BCM2835 library
parameter:
Info:
******************************************************************************/
void DEV_Module_Exit(void)
{
	printf("Module exit \r\n");
}
