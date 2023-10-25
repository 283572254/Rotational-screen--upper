#include "app.h"
#include "guiFunc.h"
#include "stdio.h"
#include "string.h"

gui_Err PointerPageEnterEvent(gui_int32 argc , const char **argv)
{
	guiCreateWidget((const void *)&PointerPage);//创建的第一个控件一定是page
	guiCreateWidget((const void *)&PointerPageRoundSlider);
	guiCreateWidget((const void *)&PointerPagePointer);
	guiCreateWidget((const void *)&PointerPageButton1);//创建图片框控件
	guiCreateWidget((const void *)&PointerPageButton2);//创建图片框控件
	guiCreateWidget((const void *)&PointerPageButton3);//创建图片框控件
	guiCreateWidget((const void *)&PointerPageButton4);//创建图片框控件
	

	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , PPButton1wID ,  BackToHome_releaseEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_UPDATE , PPageRoundSliderwID , PointerPage_RoundSlider_slideEvent);
	guiSetWidgetRoundSliderBound( PPageRoundSliderwID,330, 210);
	guiGetWidgetValue(PointerPPointerwID,&Speed_VAL);
	guiGetWidgetValue(PPageRoundSliderwID,&Slider_VAL);
	guiSetWidgetValue(PointerPPointerwID,300);
	guiSetWidgetValue(PPageRoundSliderwID,210);
	return GUI_EOK;
}
gui_Err PointerPageLeaveEvent(gui_int32 argc , const char **argv)
{
	
	return GUI_EOK;
}

static gui_Err BackToHome_releaseEvent(gui_int32 argc , const char **argv)
{
	guiJumpPage(MPwID,MainPageLeaveEvent,MainPageEnterEvent);
	return GUI_EOK;
}

static gui_Err PointerPage_RoundSlider_slideEvent(gui_int32 argc , const char **argv)
{
	guiGetWidgetValue(PPageRoundSliderwID,&Slider_VAL);
	guiGetWidgetValue(PointerPPointerwID,&Speed_VAL);
	if(Slider_VAL>=210) Speed_VAL=Slider_VAL+90;
	if(Slider_VAL==270) Speed_VAL=0;
	if(Slider_VAL>=270) Speed_VAL=Slider_VAL-270;
	if(Slider_VAL==330) Speed_VAL=60;
	guiSetWidgetValue(PointerPPointerwID,Speed_VAL);
	return GUI_EOK;
}

