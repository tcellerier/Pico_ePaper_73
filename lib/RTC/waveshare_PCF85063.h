#ifndef WAVESHARE_PCF85063_H_
#define WAVESHARE_PCF85063_H_

#include "DEV_Config.h"

#define PCF85063_ADDRESS   0x51

#define		CONTROL_1_REG         0x00  
#define 	CONTROL_2_REG         0x01 
#define 	OFFSET_REG            0x02 
#define 	RAM_BYTE_REG          0x03 
#define		SECONDS_REG           0x04 
#define 	MINUTES_REG           0x05 
#define 	HOURS_REG             0x06 
#define 	DAYS_REG              0x07 
#define		WEEKDAYS_REG          0x08 
#define		MONTHS_REG            0x09 
#define 	YEARS_REG             0x0A 
#define 	SECOND_ALARM_REG      0x0B 
#define 	MINUTES_ALARM_REG     0x0C 
#define 	HOUR_ARARM_REG        0x0D  
#define 	DAY_ALARM_REG         0x0E
#define 	WEEKDAY_ALARM_REG     0x0F
#define 	TIMER_VALUE_REG       0x10
#define 	TIMER_MODE_REG        0x11

typedef struct{
  UWORD years;
  UWORD months;
  UWORD days;
  UWORD hours;
  UWORD minutes;
  UWORD seconds;
}Time_data;

int DecToBcd(int val);
int BcdToDec(int val);
void PCF85063_init();
void PCF85063_SetTime_YMD(int Years,int Months,int Days);
void PCF85063_SetTime_HMS(int hour,int minute,int second);
Time_data PCF85063_GetTime();
void PCF85063_alarm_Time_Enabled(Time_data time);
void PCF85063_alarm_Time_Disable();
int PCF85063_get_alarm_flag();
void PCF85063_clear_alarm_flag();
void PCF85063_test();
void rtcRunAlarm(Time_data time, Time_data alarmTime);


#endif
