#include "app.h"
#include "guiFunc.h"
#include "stdio.h"
#include "string.h"
static gui_uint8 pic,anim;
gui_Err AnimPageEnterEvent(gui_int32 argc , const char **argv)
{
	guiCreateWidget((const void *)&AnimPage);//创建的第一个控件一定是page
	guiCreateWidget((const void *)&AnimPagePICANIMATION);
	guiCreateWidget((const void *)&AnimPageGTimer);
	guiRegisterEvent(EVENT_REGISTER_TYPE_TIMEOUT , AnimGTimerwID , AnimPage_timeoutEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , AnimPPICANIMATIONwID , BackToHome_releaseEvent);
	pic=1;
	anim=1;
	
	return GUI_EOK;
}

static gui_Err AnimPage_timeoutEvent (gui_int32 argc , const char **argv)
{

	guiSetWidgetPicanimationpattern(AnimPPICANIMATIONwID,anim);		
	anim++;
	if(anim == 7) anim = 16;
	if(anim == 21) anim = 0;
	switch(pic)
	{
		case 0:guiSetWidgetPictureID(AnimPPICANIMATIONwID,108);break;
		case 1:guiSetWidgetPictureID(AnimPPICANIMATIONwID,109);break;
		case 2:guiSetWidgetPictureID(AnimPPICANIMATIONwID,110);break;
		case 3:guiSetWidgetPictureID(AnimPPICANIMATIONwID,111);break;
		default:break;
	}
	pic++;
	if(pic==4) pic=0;
	return GUI_EOK;

}
gui_Err AnimPageLeaveEvent(gui_int32 argc , const char **argv)
{
	
	return GUI_EOK;
}

static gui_Err BackToHome_releaseEvent(gui_int32 argc , const char **argv)
{
	guiJumpPage(MPwID,MainPageLeaveEvent,MainPageEnterEvent);
	return GUI_EOK;
}


