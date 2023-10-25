#include "app.h"
#include "guiFunc.h"
#include "stdio.h"
#include "string.h"
#include "pwm.h"
#include "lcdInit.h"
void guiMainPageInit(void)
{
	guiJumpPage(NULL,NULL,MainPageEnterEvent);//进入主界面
}
//                           ms s m  h  d  w  y  y
RTC_TIMEDATE SystemDateTime={0,30,30,13,26,0,04,20};
gui_uint8 Shutflag=0;
gui_Err MainPageEnterEvent(gui_int32 argc , const char **argv)
{
	
	guiCreateWidget((const void *)&MainPage);//创建的第一个控件一定是page
	guiCreateWidget((const void *)&MainPageButton1);
	guiCreateWidget((const void *)&MainPageButton2);
    guiCreateWidget((const void *)&MainPageButton3);
	guiCreateWidget((const void *)&MainPageButton4);
	guiCreateWidget((const void *)&MainPageButton5);
	guiCreateWidget((const void *)&MainPageButton6);
    guiCreateWidget((const void *)&MainPageButton7);
	guiCreateWidget((const void *)&MainPageButton8);
	guiCreateWidget((const void *)&MainPageRollTextBox);
	guiCreateWidget((const void *)&MainPageGTimer);
	guiCreateWidget((const void *)&MainPageNumberBox1);//时
	guiCreateWidget((const void *)&MainPageNumberBox2);//分
	guiCreateWidget((const void *)&MainPageNumberBox3);//秒
	guiCreateWidget((const void *)&MainPageTextBox);//：：

	guiRegisterEvent(EVENT_REGISTER_TYPE_TIMEOUT , MPGTimerwID , MainPageRTC_timeoutEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , MPB1wID , MainPageButton1_releaseEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , MPB2wID , MainPageButton2_releaseEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , MPB3wID , MainPageButton3_releaseEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , MPB4wID , MainPageButton4_releaseEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , MPB5wID , MainPageButton5_releaseEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , MPB6wID , MainPageButton6_releaseEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , MPB7wID , MainPageButton7_releaseEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , MPB8wID , MainPageButton8_releaseEvent);
	
	//初始化参数
//	Rtc_Des.writeDateTime(&SystemDateTime);
	sprintf(RollDate_text,"20%02d年%02d月%02d日 %s",SystemDateTime.date.Year,SystemDateTime.date.Month,SystemDateTime.date.Day,&WeekDays[SystemDateTime.date.Weekday][0]);
	guiSetWidgetText(MPRollTBwID,strlen(RollDate_text),RollDate_text);
	guiAppendWidgetText(MPTextBoxwID,5,":   :");
	date=0;Shutflag=1;
	return GUI_EOK;
}
gui_Err MainPageLeaveEvent(gui_int32 argc , const char **argv)
{
	return GUI_EOK;
}

static gui_Err MainPageButton1_releaseEvent(gui_int32 argc , const char **argv)
{
	guiJumpPage(FPwID,FridgePageLeaveEvent,FridgePageEnterEvent);
	return GUI_EOK;
}

static gui_Err MainPageButton2_releaseEvent(gui_int32 argc , const char **argv)
{
	guiJumpPage(ACPwID,ACPageLeaveEvent,ACPageEnterEvent);
	return GUI_EOK;
}

static gui_Err MainPageButton3_releaseEvent(gui_int32 argc , const char **argv)
{
	guiJumpPage(LTPwID,LightTempPageLeaveEvent,LightTempPageEnterEvent);
	return GUI_EOK;
}

static gui_Err MainPageButton4_releaseEvent(gui_int32 argc , const char **argv)
{
	guiJumpPage(PPwID,ProgressPageLeaveEvent,ProgressPageEnterEvent);
	return GUI_EOK;
}

static gui_Err MainPageButton5_releaseEvent(gui_int32 argc , const char **argv)
{
	guiJumpPage(PointerPwID,PointerPageLeaveEvent,PointerPageEnterEvent);
	return GUI_EOK;
}

static gui_Err MainPageButton6_releaseEvent(gui_int32 argc , const char **argv)
{
	guiJumpPage(DPwID,DialogPageLeaveEvent,DialogPageEnterEvent);
	return GUI_EOK;
}

static gui_Err MainPageButton7_releaseEvent(gui_int32 argc , const char **argv)
{
	guiJumpPage(GPwID,GraphPageLeaveEvent,GraphPageEnterEvent);
	return GUI_EOK;
}

static gui_Err MainPageButton8_releaseEvent(gui_int32 argc , const char **argv)
{
	guiJumpPage(AnimPwID,AnimPageLeaveEvent,AnimPageEnterEvent);
	return GUI_EOK;
}
static gui_Err MainPageRTC_timeoutEvent(gui_int32 argc , const char **argv)
{
//	Rtc_Des.readDateTime(&SystemDateTime);
	date++;
	if(date == 1 &&(!_BG_OPEN))// 
	{
		_BG_OPEN = 1;
		TIM15_PWMInit(100,95,100);// fpwm = 9600 / 96Mhz/(95+1)=1Mhz 10Khz 100占空比 
	}
	
	guiSetWidgetValue(MPNumBox1wID,SystemDateTime.time.Hour);
	guiSetWidgetValue(MPNumBox2wID,SystemDateTime.time.Minute);
	guiSetWidgetValue(MPNumBox3wID,SystemDateTime.time.Second);

	
	if(date==140)
	{
		sprintf(RollDate_text,"20%02d年%02d月%02d日 %s",SystemDateTime.date.Year,SystemDateTime.date.Month,SystemDateTime.date.Day,&WeekDays[SystemDateTime.date.Weekday][0]);
		guiSetWidgetText(MPRollTBwID,strlen(RollDate_text),RollDate_text);
		date=0;		
	}
	return GUI_EOK;
}





