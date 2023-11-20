#include "led.h"
#include "DEV_Config.h"

void ledPowerOn(void)
{
    for(int i=0; i<3; i++) {
        DEV_Digital_Write(LED_ACT, 1);
        DEV_Delay_ms(200);
        DEV_Digital_Write(LED_ACT, 0);
        DEV_Delay_ms(100);
    }
}

void ledLowPower(void)
{
    for(int i=0; i<5; i++) {
        DEV_Digital_Write(LED_PWR, 1);
        DEV_Delay_ms(200);
        DEV_Digital_Write(LED_PWR, 0);
        DEV_Delay_ms(100);
    }
}

void ledCharging(void)
{
    DEV_Digital_Write(LED_PWR, 1);
}

void ledCharged(void)
{
    DEV_Digital_Write(LED_PWR, 0);
}

void powerOff(void)
{
    DEV_Digital_Write(BAT_OFF, 0);
}