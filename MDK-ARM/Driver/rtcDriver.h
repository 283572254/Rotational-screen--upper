#ifndef _rtcDriver_h
#define _rtcDriver_h
#include "gStdint.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Functional module: RTC real-time clock module
 * Realized functions: 1. Time type definition
 * 2、Date type definition
 * 3. Date-time type definition
 * 4. RTC device descriptor definition
 *          
 *
 * Writer: TDO LCD Application development team
 * Writing time: 2019-11-05
 * Test by: TDO LCD Application development team
 * Testing time��2019-11-05
 * Version No.: V1.01_2019-11-05
 *Version Description.
 *                              
 * Function list
 *
 *V1.01: Function Implementation
 *
 *V1.02.
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//1, time type definition
typedef struct _RTC_TIME{
	gui_uint8 mSecond;
	gui_uint8 Second;
	gui_uint8 Minute;
	gui_uint8 Hour;
}RTC_TIME;
typedef RTC_TIME*  pRTC_TIME;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//2、Date Type Definition
typedef struct _RTC_DATE{
	gui_uint8 Day;
	gui_uint8 Weekday;//0-6 Sunday---Saturday
	gui_uint8 Month;
	gui_uint8 Year;   //00-99
}RTC_DATE;
typedef RTC_DATE*  pRTC_DATE;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//3、Date Time Type Definition
typedef struct _RTC_TIMEDATE{
	RTC_TIME time;
	RTC_DATE date;
}RTC_TIMEDATE;
typedef RTC_TIMEDATE*  pRTC_TIMEDATE;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//4、RTC Device Descriptor Definition
typedef struct _RTC_DES{
	gui_int8 (*writeTime)(pRTC_TIME rtcTime);
	gui_int8 (*writeDate)(pRTC_DATE rtcDate);
	gui_int8 (*writeDateTime)(pRTC_TIMEDATE dateTime);
	gui_int8 (*readTime)(pRTC_TIME rtcTime);
	gui_int8 (*readDate)(pRTC_DATE rtcDate);
	gui_int8 (*readDateTime)(pRTC_TIMEDATE dateTime);
}RTC_DES;
extern const RTC_DES Rtc_Des;
gui_int8 RTC_Init(void);
void systimread_config(void);
#endif
