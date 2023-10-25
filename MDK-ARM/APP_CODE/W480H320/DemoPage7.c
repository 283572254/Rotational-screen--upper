#include "app.h"
#include "guiFunc.h"
#include "stdio.h"
#include "string.h"
static gui_uint16 dat=0;
gui_uint32 LCD_Luminance=0;
gui_Err GraphPageEnterEvent(gui_int32 argc , const char **argv)
{
	guiCreateWidget((const void *)&GraphPage);//创建的第一个控件一定是page
	guiCreateWidget((const void *)&GraphPagePicBox1);
	guiCreateWidget((const void *)&GraphPagePicBox2);
	guiCreateWidget((const void *)&GraphPageSlider1);
	if(LCD_Luminance) guiSetWidgetValue(GPSlider1wID, LCD_Luminance); //记住上次退出时设置的亮度
	guiCreateWidget((const void *)&GraphPageSlider2);
	guiCreateWidget((const void *)&GraphPageGraphBox);
	guiCreateWidget((const void *)&GPGTimer);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , GPPic1wID , BackToHome_releaseEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , GPPic2wID , BackToHome_releaseEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_UPDATE , GPSlider1wID , GraphPage_Slider1_slideEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_TIMEOUT , GPGTimerwID , GraphPage_Graph_timeoutEvent);
	return GUI_EOK;
}
gui_Err GraphPageLeaveEvent(gui_int32 argc , const char **argv)
{
	
	return GUI_EOK;
}

static gui_Err BackToHome_releaseEvent(gui_int32 argc , const char **argv)
{
	guiJumpPage(MPwID,MainPageLeaveEvent,MainPageEnterEvent);
	return GUI_EOK;
}
static gui_Err GraphPage_Slider1_slideEvent(gui_int32 argc , const char **argv)
{
	guiGetWidgetValue(GPSlider1wID, &LCD_Luminance);
	//printf("Get Luminance:     %d\r\n",LCD_Luminance);
	if(20<=LCD_Luminance&&LCD_Luminance<=100)
	{
		//printf("Lcd_Driver.SetDim: %d\r\n",LCD_Luminance);
		Lcd_Driver.SetDim((gui_uint16)LCD_Luminance);
	}
	return GUI_EOK;
}

static gui_Err GraphPage_Graph_timeoutEvent(gui_int32 argc , const char **argv)
{
	
	guiSetWidgetGraphValue(GPGraphBoxwID,1,sin_data[dat]/2);
	guiSetWidgetGraphValue(GPGraphBoxwID,2,cos_data[dat]/2);
	guiSetWidgetGraphValue(GPGraphBoxwID,3,dat/2);
	guiRefreshWidget(GPGraphBoxwID);
	dat++;
	if(dat==256) dat=0;
	return GUI_EOK;
}


