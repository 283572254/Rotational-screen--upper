#include "app.h"
#include "guiFunc.h"
#include "stdio.h"
#include "string.h"

static gui_uint8 add;
/*****************************************开机进度**************************************/
gui_Err ProgressPageEnterEvent(gui_int32 argc , const char **argv)
{
	guiCreateWidget((const void *)&ProgressPage);//创建的第一个控件一定是page
	guiCreateWidget((const void *)&ProgressPageBar);
	guiCreateWidget((const void *)&ProgressPagePicBox1);
	guiCreateWidget((const void *)&ProgressPagePicBox2);
	guiCreateWidget((const void *)&ProgressPageGTimer);
	guiCreateWidget((const void *)&ProgressPagePicBox);

	guiRegisterEvent(EVENT_REGISTER_TYPE_TIMEOUT , PPGTimerwID , PP_SetValue_timeoutEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , PPwID , BackToHome_releaseEvent);

	Bar_Val=0;
	return GUI_EOK;
}

gui_Err ProgressPageLeaveEvent(gui_int32 argc , const char **argv)
{

	return GUI_EOK;
}
static gui_Err PP_SetValue_timeoutEvent(gui_int32 argc , const char **argv)
{	
	if(Bar_Val==0)	add=1;
	if(Bar_Val==100)
	{
		add=0;
	}
	if(add)
		Bar_Val++;	
	else
		Bar_Val-=1;	
	pic1=Bar_Val/10;
	pic2=Bar_Val%10;
	switch(pic1)
	{
		case 0:{guiSetWidgetPictureID(PPPic1wID , 53);break;}
		case 1:{guiSetWidgetPictureID(PPPic1wID , 54);break;}
		case 2:{guiSetWidgetPictureID(PPPic1wID , 55);break;}
		case 3:{guiSetWidgetPictureID(PPPic1wID , 56);break;}
		case 4:{guiSetWidgetPictureID(PPPic1wID , 57);break;}
		case 5:{guiSetWidgetPictureID(PPPic1wID , 58);break;}
		case 6:{guiSetWidgetPictureID(PPPic1wID , 59);break;}
		case 7:{guiSetWidgetPictureID(PPPic1wID , 60);break;}
		case 8:{guiSetWidgetPictureID(PPPic1wID , 61);break;}
		case 9:{guiSetWidgetPictureID(PPPic1wID , 62);break;}
		case 10:{guiSetWidgetPictureID(PPPic1wID , 73);break;}
		default:break;
	}
	switch(pic2)
	{
		case 0:{guiSetWidgetPictureID(PPPic2wID , 63);break;}
		case 1:{guiSetWidgetPictureID(PPPic2wID , 64);break;}
		case 2:{guiSetWidgetPictureID(PPPic2wID , 65);break;}
		case 3:{guiSetWidgetPictureID(PPPic2wID , 66);break;}
		case 4:{guiSetWidgetPictureID(PPPic2wID , 67);break;}
		case 5:{guiSetWidgetPictureID(PPPic2wID , 68);break;}
		case 6:{guiSetWidgetPictureID(PPPic2wID , 69);break;}
		case 7:{guiSetWidgetPictureID(PPPic2wID , 70);break;}
		case 8:{guiSetWidgetPictureID(PPPic2wID , 71);break;}
		case 9:{guiSetWidgetPictureID(PPPic2wID , 72);break;}
		default:break;
	}
	guiSetWidgetValue(PPBarwID,Bar_Val);
	return GUI_EOK;
}
static gui_Err BackToHome_releaseEvent(gui_int32 argc , const char **argv)
{
	guiJumpPage(MPwID,MainPageLeaveEvent,MainPageEnterEvent);
	return GUI_EOK;
}
