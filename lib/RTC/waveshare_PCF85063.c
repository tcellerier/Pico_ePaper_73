/*****************************************************************************
* | File      	:   waveshare_PCF85063.c
* | Author      :   Waveshare team
* | Function    :   PCF85063 driver
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-02-02
* | Info        :   Basic version
*
******************************************************************************/
#include "DEV_Config.h"
#include "waveshare_PCF85063.h"

/******************************************************************************
function:	Read one byte of data to EMC2301 via I2C
parameter:  
            Addr: Register address
Info:
******************************************************************************/
static UBYTE PCF85063_Read_Byte(UBYTE Addr)
{
	return I2C_Read_Byte(Addr);
}

/******************************************************************************
function:	Send one byte of data to EMC2301 via I2C
parameter:
            Addr: Register address
           Value: Write to the value of the register
Info:
******************************************************************************/
static void PCF85063_Write_Byte(UBYTE Addr, UBYTE Value)
{
	I2C_Write_Byte(Addr, Value);
}

int DecToBcd(int val)
{
	return ((val/10)*16 + (val%10)); 
}

int BcdToDec(int val)
{
	return ((val/16)*10 + (val%16));
}

void PCF85063_init()
{
	int inspect = 0;
	PCF85063_Write_Byte(CONTROL_1_REG,0x58);
	DEV_Delay_ms(500);
	PCF85063_Write_Byte(SECONDS_REG,PCF85063_Read_Byte(SECONDS_REG)|0x80);
	PCF85063_Write_Byte(CONTROL_2_REG,0x80);
	while(1)
	{
		PCF85063_Write_Byte(SECONDS_REG,PCF85063_Read_Byte(SECONDS_REG)&0x7F);
		if((PCF85063_Read_Byte(SECONDS_REG)&0x80) == 0)
		break;
		DEV_Delay_ms(500);
		inspect  = inspect+1;
		if(inspect>5)
		{
			printf("Clock stability unknown\r\n");
			break;
		}
	}
}

void PCF85063_SetTime_YMD(int Years,int Months,int Days)
{
	if(Years>99)
		Years = 99;
	if(Months>12)
		Months = 12;
	if(Days>31)
		Days = 31;	
	PCF85063_Write_Byte(YEARS_REG  ,DecToBcd(Years));
	PCF85063_Write_Byte(MONTHS_REG ,DecToBcd(Months)&0x1F);
	PCF85063_Write_Byte(DAYS_REG   ,DecToBcd(Days)&0x3F);
}

void PCF85063_SetTime_HMS(int hour,int minute,int second)
{
	if(hour>23)
		hour = 23;
	if(minute>59)
		minute = 59;
	if(second>59)
		second = 59;
	PCF85063_Write_Byte(HOURS_REG  ,DecToBcd(hour)&0x3F);
	PCF85063_Write_Byte(MINUTES_REG,DecToBcd(minute)&0x7F);
	PCF85063_Write_Byte(SECONDS_REG,DecToBcd(second)&0x7F);
}

Time_data PCF85063_GetTime()
{
	Time_data time;
	time.years = BcdToDec(PCF85063_Read_Byte(YEARS_REG));
	time.months = BcdToDec(PCF85063_Read_Byte(MONTHS_REG)&0x1F);
	time.days = BcdToDec(PCF85063_Read_Byte(DAYS_REG)&0x3F);
	time.hours = BcdToDec(PCF85063_Read_Byte(HOURS_REG)&0x3F);
	time.minutes = BcdToDec(PCF85063_Read_Byte(MINUTES_REG)&0x7F);
	time.seconds = BcdToDec(PCF85063_Read_Byte(SECONDS_REG)&0x7F);
	return time;
}

void PCF85063_alarm_Time_Enabled(Time_data time)
{
	PCF85063_Write_Byte(CONTROL_2_REG, PCF85063_Read_Byte(CONTROL_2_REG)|0x80);	// Alarm on
	PCF85063_Write_Byte(HOUR_ARARM_REG, DecToBcd(time.hours) & 0x7F);
	PCF85063_Write_Byte(MINUTES_ALARM_REG, DecToBcd(time.minutes) & 0x7F);
	PCF85063_Write_Byte(SECOND_ALARM_REG, DecToBcd(time.seconds) & 0x7F);
}

void PCF85063_alarm_Time_Disable() 
{
	PCF85063_Write_Byte(HOUR_ARARM_REG   ,PCF85063_Read_Byte(HOUR_ARARM_REG)|0x80);
	PCF85063_Write_Byte(MINUTES_ALARM_REG,PCF85063_Read_Byte(MINUTES_ALARM_REG)|0x80);
	PCF85063_Write_Byte(SECOND_ALARM_REG ,PCF85063_Read_Byte(SECOND_ALARM_REG)|0x80);
	PCF85063_Write_Byte(CONTROL_2_REG   ,PCF85063_Read_Byte(CONTROL_2_REG)&0x7F);	// Alarm OFF
}

int PCF85063_get_alarm_flag()
{
	if(PCF85063_Read_Byte(CONTROL_2_REG)&0x40 == 0x40)
		return 1;
	else 
		return 0;
}

void PCF85063_clear_alarm_flag()
{
	PCF85063_Write_Byte(CONTROL_2_REG   ,PCF85063_Read_Byte(CONTROL_2_REG)&0xBF);
}

void PCF85063_test()
{
    int count = 0;
	
	PCF85063_SetTime_YMD(21,2,28);
	PCF85063_SetTime_HMS(23,59,58);
	while(1)
	{
		Time_data T;
		T = PCF85063_GetTime();
		printf("%d-%d-%d %d:%d:%d\r\n",T.years,T.months,T.days,T.hours,T.minutes,T.seconds);
		count+=1;
		DEV_Delay_ms(1000);
		if(count>6)
		break;
	}
}

void rtcRunAlarm(Time_data time, Time_data alarmTime)
{
	PCF85063_SetTime_YMD(time.years, time.months, time.days);
	PCF85063_SetTime_HMS(time.hours, time.minutes, time.seconds);
    
    PCF85063_alarm_Time_Enabled(alarmTime);
}