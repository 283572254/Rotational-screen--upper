#include "DemoTest01.h"
#include "guiFunc.h"
#include "stdio.h"
#include "string.h"
#include "pwm.h"
gui_uint16 NUM=0 ;
extern char IMG;
extern char Logo;
extern uint8_t red_img[5],red_img2;
extern char Enter_click;

char menu[4]={8,0,0,0};      //menu[0]: text image                  menu[1]: whether to make an appointment
							// menu[2]: set appointment time     menu[3]: running time (minutes)

char img_id[]={0,1,2,3,4};
char img_id1[]={21,5,6,7,8,9,10};
char img_id2[]={20,11,12,13,14,15,16,17,18,19};
char img_id3[]={22,23};
void DemoTestPage_Init(void)
{ 
	guiJumpPage(GUI_NULL,GUI_NULL,DemoMain_PageEnterEvent);
}

gui_Err DemoMain_PageEnterEvent(gui_int32 argc , const char **argv)
{
	guiCreateWidget((const void *)&DemoTest01_Page);
	guiCreateWidget((const void *)&DemoTest01_Pic);
	guiCreateWidget((const void *)&DemoTest01_GTimer);
	Enter_click = 0;
	guiRegisterEvent(EVENT_REGISTER_TYPE_TIMEOUT , Test01_GTimerwID , DemoTest01_timeoutEvent);	
	return GUI_EOK;
}

static gui_Err DemoTest01_timeoutEvent (gui_int32 argc , const char **argv)
{    			

	 menu[1] = 0;
	if(Logo){	
	    guiSetWidgetPictureID(Test01_PicwID,0);	
//			IMG=0;
	}
	else
	{ 
		guiSetWidgetPictureID(Test01_PicwID,img_id[IMG]);
		menu[0] = IMG+7;
	}
	return GUI_EOK;
}
gui_Err DemoTest01_LeaveEvent(gui_int32 argc , const char **argv)
{	
	return GUI_EOK;
}
/**************************************************red led to enter the page**********************************************/
gui_Err red_led_PageEnterEvent(gui_int32 argc , const char **argv)
{
	guiCreateWidget((const void *)&red_led_Page);
	guiCreateWidget((const void *)&red_led_Pic);
	guiCreateWidget((const void *)&red_led_GTimer);
	Enter_click = 0;
	guiRegisterEvent(EVENT_REGISTER_TYPE_TIMEOUT , red_led_GTimerwID , red_led_timeoutEvent);	
	return GUI_EOK;
}

static gui_Err red_led_timeoutEvent (gui_int32 argc , const char **argv)
{    			

	guiSetWidgetPictureID(red_led_PicwID,img_id1[IMG]);
	return GUI_EOK;
}
gui_Err red_led_LeaveEvent(gui_int32 argc , const char **argv)
{	
	return GUI_EOK;
}

/**************************************************red led to enter the page2**********************************************/
gui_Err red_led_PageEnterEvent2(gui_int32 argc , const char **argv)
{
	guiCreateWidget((const void *)&red_led_Page2);
	guiCreateWidget((const void *)&red_led_Pic2);
	
	guiCreateWidget((const void *)&red_led_1);
	guiCreateWidget((const void *)&red_led_2);
	guiCreateWidget((const void *)&red_led_5);
	guiCreateWidget((const void *)&red_led_8);
	guiCreateWidget((const void *)&red_led_10);
	guiCreateWidget((const void *)&red_led_onoff);

	
	
	guiCreateWidget((const void *)&red_led_GTimer2);
	Enter_click = 0;
	guiRegisterEvent(EVENT_REGISTER_TYPE_TIMEOUT , red_led_GTimerwID2 , red_led_timeoutEvent2);	
	return GUI_EOK;
}

static gui_Err red_led_timeoutEvent2 (gui_int32 argc , const char **argv)
{    			

	guiSetWidgetPictureID(red_led_ID1,img_id2[red_img[0]]);
	guiSetWidgetPictureID(red_led_ID2,img_id2[red_img[1]]);
	guiSetWidgetPictureID(red_led_ID5,img_id2[red_img[2]]);
	guiSetWidgetPictureID(red_led_ID8,img_id2[red_img[3]]);
	guiSetWidgetPictureID(red_led_ID10,img_id2[red_img[4]]);
	guiSetWidgetPictureID(red_led_onoff_ID,img_id3[IMG]);
	return GUI_EOK;
}
gui_Err red_led_LeaveEvent2(gui_int32 argc , const char **argv)
{	
	return GUI_EOK;
}

/**************************************************Short press action to enter the page**********************************************/
void Set_time(gui_int16 hours1,gui_int16 hours2,gui_int16 minutes1,gui_int16 minutes2)
{   	
		guiSetWidgetPictureID(Hours1_PicwID,hours1+18);
		guiSetWidgetPictureID(Hours2_PicwID,hours2+18);
		guiSetWidgetPictureID(Minutes1_PicwID,minutes1+18);
		guiSetWidgetPictureID(Minutes2_PicwID,minutes2+18);
}
void Enter_ShortKey_Init(void)
{ 
	guiJumpPage(GUI_NULL,GUI_NULL,ShortKey_PageEnterEvent);
}
gui_Err ShortKey_PageEnterEvent(gui_int32 argc , const char **argv)
{
	guiCreateWidget((const void *)&Encoder_shortKey);
	guiCreateWidget((const void *)&ShortKey_GTimer);
	guiCreateWidget((const void *)&ShortKey_Pic);
	guiCreateWidget((const void *)&Char_Pic);
	guiCreateWidget((const void *)&Hour1_Pic);
	guiCreateWidget((const void *)&Hour2_Pic);
	guiCreateWidget((const void *)&Colon_Pic);
	guiCreateWidget((const void *)&Minutes1_Pic);
	guiCreateWidget((const void *)&Minutes2_Pic);	
	Enter_click=0;
	if(menu[1] == 0)
		guiCreateWidget((const void *)&FireGIF);	
	else
		guiCreateWidget((const void *)&HourglassGIF);
	
	guiRegisterEvent(EVENT_REGISTER_TYPE_TIMEOUT , ShortKey_GTimerwID , ShortKey_timeoutEvent);
	//guiRegisterEvent(EVENT_REGISTER_TYPE_PRESS , ShortKey_PicwID , ShortKey_PressEvent);
	NUM=0;
	return GUI_EOK;
}


static gui_Err ShortKey_timeoutEvent (gui_int32 argc , const char **argv)
{    
	guiSetWidgetPictureID(Char_PicwID,menu[0]);
	if(menu[1]==0)
	{
		switch(menu[0])
		{
			
			case 8:Set_time(0,0,3,0);break;     //rice  
			case 9:Set_time(0,0,3,0);break;	 //gruel 
			case 10:Set_time(0,2,0,0);break;	 //soup  
			case 11:Set_time(0,1,0,0);break;	 //steam 		
			case 12:Set_time(2,3,5,9);break;	 //keep warm  
			case 13:Set_time(0,0,0,3);break;     //yogurt 
			default : Set_time(0,0,5,9);break;				
		}	
	}
	else
	{
	   Set_time(menu[2]/10,menu[2]%10,0,0);								
	}
	if(NUM%20==0)
	{
	   if(NUM%40==0)
		guiSetWidgetPictureID(Colon_PicwID,28);
	   else
		guiSetWidgetPictureID(Colon_PicwID,29);	
	}

    NUM++;	
	
	if(NUM == 1200)  {	
		NUM = 0;
		menu[3]+=1;
		//guiJumpPage(TL013GIFPwID,AnimPageLeaveEvent,GIF013PageEnterEvent);
	}	
	return GUI_EOK;
}

gui_Err ShortKey_LeaveEvent(gui_int32 argc , const char **argv)
{	
	return GUI_EOK;
}


/**************************************************Long press action to enter the page**********************************************/

void Enter_LongKey_Init(void)
{ 
	guiJumpPage(GUI_NULL,GUI_NULL,LongKey_PageEnterEvent);
}
gui_Err LongKey_PageEnterEvent(gui_int32 argc , const char **argv)
{
	guiCreateWidget((const void *)&Encoder_LongKey);
	guiCreateWidget((const void *)&LongKey_GTimer);
	guiCreateWidget((const void *)&ARC_Pic);
	guiCreateWidget((const void *)&MenuChar_Pic);
	
	guiSetWidgetPictureID(ARC_PicwID,IMG+33);
	guiSetWidgetPictureID(MenuChar_PicwID,menu[0]);	
	
	guiRegisterEvent(EVENT_REGISTER_TYPE_TIMEOUT , LongKey_GTimerwID , LongKey_timeoutEvent);
	
	Enter_click = 1;
	menu[1] = 1;
	NUM = 0;
	return GUI_EOK;
}

static gui_Err LongKey_timeoutEvent (gui_int32 argc , const char **argv)
{    
	static char last_img=0;
	
	NUM++;	
	if(IMG!=last_img){
	    guiSetWidgetPictureID(ARC_PicwID,IMG+33);
		guiSetWidgetPictureID(MenuChar_PicwID,menu[0]);
		last_img = IMG;
		menu[2] = IMG;
	}
	
	if(NUM==960)  {	
		NUM=0;
		//guiJumpPage(TL013GIFPwID,AnimPageLeaveEvent,GIF013PageEnterEvent);
	}	

	return GUI_EOK;
}
gui_Err LongKey_LeaveEvent(gui_int32 argc , const char **argv)
{	
	return GUI_EOK;
}



