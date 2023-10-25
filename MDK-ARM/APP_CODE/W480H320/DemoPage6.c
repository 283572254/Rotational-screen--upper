#include "app.h"
#include "guiFunc.h"
#include "stdio.h"
#include "string.h"
extern RTC_TIMEDATE SystemDateTime;
static gui_uint32 Year,Mon,Date,Hour,Min,Sec;
gui_Err DialogPageEnterEvent(gui_int32 argc , const char **argv)
{
	guiCreateWidget((const void *)&DialogPage);//创建的第一个控件一定是page
	guiCreateWidget((const void *)&DialogPagePicBox);
	guiCreateWidget((const void *)&DialogPageTextBox);
	guiCreateWidget((const void *)&DialogPageButtonYES);
	guiCreateWidget((const void *)&DialogPageButtonNO);
	guiCreateWidget((const void *)&DialogPageNumberBox1);//年
	guiCreateWidget((const void *)&DialogPageNumberBox2);//月
	guiCreateWidget((const void *)&DialogPageNumberBox3);//日
	guiCreateWidget((const void *)&DialogPageNumberBox4);//时
	guiCreateWidget((const void *)&DialogPageNumberBox5);//分
	guiCreateWidget((const void *)&DialogPageNumberBox6);//秒
	guiAppendWidgetText(DPTextBoxwID,2,"20");
	guiAppendWidgetText(DPButtonYESwID,3,"YES");
	guiAppendWidgetText(DPButtonNOwID,2,"NO");	

	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , DPButtonYESwID , ModifyTime_releaseEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , DPButtonNOwID , BackToHome_releaseEvent);
	//读取现在日期时间给对话框
//	Rtc_Des.readDateTime(&SystemDateTime);
	guiSetWidgetValue(DPNumBox1wID,SystemDateTime.date.Year);
	guiSetWidgetValue(DPNumBox2wID,SystemDateTime.date.Month);
	guiSetWidgetValue(DPNumBox3wID,SystemDateTime.date.Day);
	guiSetWidgetValue(DPNumBox4wID,SystemDateTime.time.Hour);
	guiSetWidgetValue(DPNumBox5wID,SystemDateTime.time.Minute);
	guiSetWidgetValue(DPNumBox6wID,SystemDateTime.time.Second);
	return GUI_EOK;
}
gui_Err DialogPageLeaveEvent(gui_int32 argc , const char **argv)
{
	
	return GUI_EOK;
}
//返回主界面
static gui_Err BackToHome_releaseEvent(gui_int32 argc , const char **argv)
{
	guiJumpPage(MPwID,MainPageLeaveEvent,MainPageEnterEvent);
	return GUI_EOK;
}
//修改日期时间并返回
static gui_Err ModifyTime_releaseEvent(gui_int32 argc , const char **argv)
{
	guiGetWidgetValue(DPNumBox1wID,&Year);
	guiGetWidgetValue(DPNumBox2wID,&Mon);
	guiGetWidgetValue(DPNumBox3wID,&Date);
	guiGetWidgetValue(DPNumBox4wID,&Hour);
	guiGetWidgetValue(DPNumBox5wID,&Min);
	guiGetWidgetValue(DPNumBox6wID,&Sec);
	SystemDateTime.date.Year=Year;
	if(1<=Mon&&Mon<=12)	SystemDateTime.date.Month=Mon;
	if(1<=Date&&Date<=31) SystemDateTime.date.Day=Date;
	if(Hour<=24) SystemDateTime.time.Hour=Hour;
	if(Min<=59)	SystemDateTime.time.Minute=Min;
	if(Sec<=59)	SystemDateTime.time.Second=Sec;
//	Rtc_Des.writeDateTime(&SystemDateTime);
	guiJumpPage(MPwID,MainPageLeaveEvent,MainPageEnterEvent);
	return GUI_EOK;
}



