#include "rtcDriver.h"
#include "Y6_i2c.h"
#include "Y6_utility_i2c.h"
#include "stdio.h"
#include "Y6_gpio.h"

#define ReadWriteBuff_Max               8//8 Bytes
static uint8_t ReadWriteBuff[ReadWriteBuff_Max];
/*
*********************************************************************************************************************
* Function: BcdToChar Convert a BCD code to hexadecimal
*Entry parameter: bcdData, BCD code
*Export parameter: hexadecimal
*********************************************************************************************************************
*/ 
static inline uint8_t BcdToChar(uint8_t bcdData)
{
	uint8_t rdata,zdata;
	zdata=(bcdData>>4)&0x0f;
	if(zdata>9)zdata=9;
	rdata=zdata*10;
	zdata=bcdData&0x0f;
	if(zdata>9)zdata=9;
	rdata+=zdata;
	return rdata;
}
/*
*********************************************************************************************************************
* Function: CharToBcd Convert a hexadecimal to BCD
*Entry parameter: charData Hexadecimal
*Export parameter: BCD code
*********************************************************************************************************************
*/ 
static uint8_t CharToBcd(uint8_t charData)
{
	uint8_t rdata,zdata;
	zdata=charData%100/10;
	rdata=zdata<<4;
	zdata=charData%10;
	rdata+=zdata;
	return rdata;
}
/*
*********************************************************************************************************************
* Function: RTC_Init clock initialization
*Entry parameter: None
*Exit parameter: -1 Failure 0 Success Other values are not defined
*********************************************************************************************************************
*/ 
int8_t RTC_Init(void)
{
	I2C_Configuration(I2C_SPEED_STD, I2C_GP7);
	return 0;
}
/*
*********************************************************************************************************************
* Function: RTC_WriteTime Write a time to the RTC
*Entry parameter: rtcTime The time to be written
*Exit parameter: -1 Failure 0 Success Other values are not defined
*********************************************************************************************************************
*/ 
static int8_t RTC_WriteTime(pRTC_TIME rtcTime)
{
	ReadWriteBuff[0]=CharToBcd(rtcTime->Second);
	ReadWriteBuff[1]=CharToBcd(rtcTime->Minute);
	ReadWriteBuff[2]=CharToBcd(rtcTime->Hour);
	
	if(I2C_DmaWrite(0xA2>>1, 2, 1, ReadWriteBuff, 3)<0){
		return -1;//read failed
	}
	else{
		return 0;
	}
}
/*
*********************************************************************************************************************
* Function: RTC_WriteDate Write a date to the RTC
*Entry parameter: rtcDate The date to be written
*Exit parameter: -1 Failure 0 Success Other values are not defined
*********************************************************************************************************************
*/ 
static int8_t RTC_WriteDate(pRTC_DATE rtcDate)
{
	ReadWriteBuff[0]=CharToBcd(rtcDate->Day);
	ReadWriteBuff[1]=CharToBcd(rtcDate->Weekday);
	ReadWriteBuff[2]=CharToBcd(rtcDate->Month);
	ReadWriteBuff[3]=CharToBcd(rtcDate->Year);
	
	if(I2C_DmaWrite(0xA2>>1, 5, 1, ReadWriteBuff, 4)<0){
		return -1;//read failed
	}
	else{
		return 0;
	}
}
/*
*********************************************************************************************************************
* Function: RTC_WriteDateTime Write a time and date to the RTC
*Entry parameter: dateTime The date and time to be written
*Exit parameter: -1 Failure 0 Success Other values are not defined
*********************************************************************************************************************
*/ 
static int8_t RTC_WriteDateTime(pRTC_TIMEDATE dateTime)
{
	ReadWriteBuff[0]=CharToBcd(dateTime->time.Second);
	ReadWriteBuff[1]=CharToBcd(dateTime->time.Minute);
	ReadWriteBuff[2]=CharToBcd(dateTime->time.Hour);
	ReadWriteBuff[3]=CharToBcd(dateTime->date.Day);
	ReadWriteBuff[4]=CharToBcd(dateTime->date.Weekday);
	ReadWriteBuff[5]=CharToBcd(dateTime->date.Month);
	ReadWriteBuff[6]=CharToBcd(dateTime->date.Year);
	
	if(I2C_DmaWrite(0xA2>>1, 2, 1, ReadWriteBuff, 7)<0){
		printf("write error\r\n");
		return -1;//read failed
	}
	else{
		return 0;
	}
}
/*
*********************************************************************************************************************
* Function: RTC_ReadTime Read time to buffer
*Entry parameter: buffer to be read
*Exit parameter: -1 Failure 0 Success Other values are not defined
*********************************************************************************************************************
*/ 
static int8_t RTC_ReadTime(pRTC_TIME rtcTime)
{
	uint8_t i;
	#define READ_TIME_COUNT       3
	if(I2C_DmaRead(0xA3>>1, 2, 1, ReadWriteBuff, READ_TIME_COUNT)<0){
		return -1;//read failed
	}
	else{
		ReadWriteBuff[0]&=0x7f;
		ReadWriteBuff[1]&=0x7f;
		ReadWriteBuff[2]&=0x3f;
		for(i=0;i<READ_TIME_COUNT;i++){
			ReadWriteBuff[i]=BcdToChar(ReadWriteBuff[i]);
		}
		rtcTime->Second=ReadWriteBuff[0];
		rtcTime->Minute=ReadWriteBuff[1];
		rtcTime->Hour=ReadWriteBuff[2];
		return 0;
	}
}
/*
*********************************************************************************************************************
* Function: RTC_ReadDate Read the date into the buffer
*Entry parameter: buffer to be read
*Exit parameter: -1 Failure 0 Success Other values are not defined
*********************************************************************************************************************
*/ 
static int8_t RTC_ReadDate(pRTC_DATE rtcDate)
{
	uint8_t i;
	#define READ_Date_COUNT       4
	if(I2C_DmaRead(0xA3>>1, 5, 1, ReadWriteBuff, READ_Date_COUNT)<0){
		return -1;//read failed
	}
	else{
		ReadWriteBuff[0]&=0x3f;
		ReadWriteBuff[1]&=0x07;
		ReadWriteBuff[2]&=0x1f;
		for(i=0;i<READ_Date_COUNT;i++){
			ReadWriteBuff[i]=BcdToChar(ReadWriteBuff[i]);
		}
		rtcDate->Day=ReadWriteBuff[0];
		rtcDate->Weekday=ReadWriteBuff[1];
		rtcDate->Month=ReadWriteBuff[2];
		rtcDate->Year=ReadWriteBuff[3];
		return 0;
	}
}
/*
*********************************************************************************************************************
* Function: RTC_ReadDateTime Read the date and time into the buffer
*Entry parameter: buffer to be read
*Exit parameter: -1 Failure 0 Success Other values are not defined
*********************************************************************************************************************
*/ 
static int8_t RTC_ReadDateTime(pRTC_TIMEDATE dateTime)
{
	uint8_t i;
	#define READ_DateTime_COUNT       7
	if(I2C_DmaRead(0xA3>>1, 2, 1, ReadWriteBuff, READ_DateTime_COUNT)<0){
		return -1;//read failed
	}
	else{
		ReadWriteBuff[0]&=0x7f;
		ReadWriteBuff[1]&=0x7f;
		ReadWriteBuff[2]&=0x3f;
		ReadWriteBuff[3]&=0x3f;
		ReadWriteBuff[4]&=0x07;
		ReadWriteBuff[5]&=0x1f;
		for(i=0;i<READ_DateTime_COUNT;i++){
			ReadWriteBuff[i]=BcdToChar(ReadWriteBuff[i]);
		}
		dateTime->time.Second=ReadWriteBuff[0];
		dateTime->time.Minute=ReadWriteBuff[1];
		dateTime->time.Hour=ReadWriteBuff[2];
		dateTime->date.Day=ReadWriteBuff[3];
		dateTime->date.Weekday=ReadWriteBuff[4];
		dateTime->date.Month=ReadWriteBuff[5];
		dateTime->date.Year=ReadWriteBuff[6];
		return 0;
	}
}
/*
*********************************************************************************************************************
* Function: Device descriptor on RTC operations, containing the interface to RTC operations
*********************************************************************************************************************
*/ 
const RTC_DES Rtc_Des={
	RTC_WriteTime,
	RTC_WriteDate,
	RTC_WriteDateTime,
	RTC_ReadTime,
	RTC_ReadDate,
	RTC_ReadDateTime
};


void systimread_config(void)
{	
		GPIO_SetPinMux(GPIO0, GPIO_Pin_0, GPIO_FUNCTION_2);  /*SDA*/
		GPIO_SetPinMux(GPIO0, GPIO_Pin_1, GPIO_FUNCTION_2);  /*SCL*/		
		GPIO_SetPinMux(GPIO1, GPIO_Pin_28, GPIO_FUNCTION_0);  /*SDA*/
		GPIO_SetPinMux(GPIO1, GPIO_Pin_29, GPIO_FUNCTION_0);  /*SCL*/
}
