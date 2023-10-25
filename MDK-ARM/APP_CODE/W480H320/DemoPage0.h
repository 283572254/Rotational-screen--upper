#ifndef _DemoPage0_h
#define _DemoPage0_h
#include "gWidgetInfo.h"
#include "gStdint.h"
#include "gReturn.h"
#include "gResMsg.h"
#include "rtcDriver.h"

static gui_uint32 readTimeCount;
static gui_uint32 readTouchTime;
static const char WeekDays[7][16]={
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};
static gui_uint8 date;
static char RollDate_text[25];
#define MPwID 0x0001
static const PAGE_INFO MainPage={
	{.wType = WIDGET_TYPE_PAGE , .wId = 0x0001 , .wVscope = WIDGET_VS_PRIVATE},
	{.x = 0 , .y = 0 , .width = 480 , .height = 320},
	.backMode = WIDGET_BACKMODE_PIC , 
	.backColor = 0x0000,
	.picId = 0,
	.enterEvent = GUI_NULL,
	.leaveEvent = GUI_NULL,
	.pressEvent = GUI_NULL,
	.releaseEvent = GUI_NULL,
};
#define MPB1wID 0x0002
static const BUTTON_INFO MainPageButton1={
 {.wType = WIDGET_TYPE_BUTTON , .wId = 0x0002 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0x001C , .y = 0x002A , .width = 0x0050 , .height = 0x0050},
 .backMode = WIDGET_BACKMODE_CUTPIC,
 .fontlibId = 0x0000,
 .borderWidth = 0,
 .borderColor = 0x0000,
 .pressPicId  = 1,
 .releasePicId = 0,
 .pressBackColor = 0,
 .releaseBackColor = 0,
 .pressFontColor = 0,
 .releaseFontColor = 0,
 .xAlign = 0,
 .yAlign = 0,
 .isDr = 0,
 .text = (char *)0x00,
 .maxLen = 0x0a,
 .pressEvent = GUI_NULL,
 .releaseEvent = GUI_NULL,
 .updateEvent = GUI_NULL,
};
#define MPB2wID 0x0003
static const BUTTON_INFO MainPageButton2={
 {.wType = WIDGET_TYPE_BUTTON , .wId = 0x0003 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0x0091 , .y = 0x002A , .width = 0x0050 , .height = 0x0050},
 .backMode = WIDGET_BACKMODE_CUTPIC,
 .fontlibId = 0x0000,
 .borderWidth = 0,
 .borderColor = 0x0000,
 .pressPicId  = 1,
 .releasePicId = 0,
 .pressBackColor = 0,
 .releaseBackColor = 0,
 .pressFontColor = 0,
 .releaseFontColor = 0,
 .xAlign = 0,
 .yAlign = 0,
 .isDr = 0,
 .text = (char *)0x00,
 .maxLen = 0x0a,
 .pressEvent = GUI_NULL,
 .releaseEvent = GUI_NULL,
 .updateEvent = GUI_NULL,
};
#define MPB3wID 0x0004
static const BUTTON_INFO MainPageButton3={
 {.wType = WIDGET_TYPE_BUTTON , .wId = 0x0004 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0x0102 , .y = 0x002A , .width = 0x0050 , .height = 0x0050},
 .backMode = WIDGET_BACKMODE_CUTPIC,
 .fontlibId = 0x0000,
 .borderWidth = 0,
 .borderColor = 0x0000,
 .pressPicId  = 1,
 .releasePicId = 0,
 .pressBackColor = 0,
 .releaseBackColor = 0,
 .pressFontColor = 0,
 .releaseFontColor = 0,
 .xAlign = 0,
 .yAlign = 0,
 .isDr = 0,
 .text = (char *)0x00,
 .maxLen = 0x0a,
 .pressEvent = GUI_NULL,
 .releaseEvent = GUI_NULL,
 .updateEvent = GUI_NULL,
};
#define MPB4wID 0x0005
static const BUTTON_INFO MainPageButton4={
 {.wType = WIDGET_TYPE_BUTTON , .wId = 0x0005 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0x0173 , .y = 0x002A , .width = 0x0050 , .height = 0x0050},
 .backMode = WIDGET_BACKMODE_CUTPIC,
 .fontlibId = 0x0000,
 .borderWidth = 0,
 .borderColor = 0x0000,
 .pressPicId  = 1,
 .releasePicId = 0,
 .pressBackColor = 0,
 .releaseBackColor = 0,
 .pressFontColor = 0,
 .releaseFontColor = 0,
 .xAlign = 0,
 .yAlign = 0,
 .isDr = 0,
 .text = (char *)0x00,
 .maxLen = 0x0a,
 .pressEvent = GUI_NULL,
 .releaseEvent = GUI_NULL,
 .updateEvent = GUI_NULL,
};
#define MPB5wID 0x0006
static const BUTTON_INFO MainPageButton5={
 {.wType = WIDGET_TYPE_BUTTON , .wId = 0x0006 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0x001C , .y = 0x00AB , .width = 0x0050 , .height = 0x0050},
 .backMode = WIDGET_BACKMODE_CUTPIC,
 .fontlibId = 0x0000,
 .borderWidth = 0,
 .borderColor = 0x0000,
 .pressPicId  = 1,
 .releasePicId = 0,
 .pressBackColor = 0,
 .releaseBackColor = 0,
 .pressFontColor = 0,
 .releaseFontColor = 0,
 .xAlign = 0,
 .yAlign = 0,
 .isDr = 0,
 .text = (char *)0x00,
 .maxLen = 0x0a,
 .pressEvent = GUI_NULL,
 .releaseEvent = GUI_NULL,
 .updateEvent = GUI_NULL,
};
#define MPB6wID 0x0007
static const BUTTON_INFO MainPageButton6={
 {.wType = WIDGET_TYPE_BUTTON , .wId = 0x0007 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0x008F , .y = 0x00AB , .width = 0x0050 , .height = 0x0050},
 .backMode = WIDGET_BACKMODE_CUTPIC,
 .fontlibId = 0x0000,
 .borderWidth = 0,
 .borderColor = 0x0000,
 .pressPicId  = 1,
 .releasePicId = 0,
 .pressBackColor = 0,
 .releaseBackColor = 0,
 .pressFontColor = 0,
 .releaseFontColor = 0,
 .xAlign = 0,
 .yAlign = 0,
 .isDr = 0,
 .text = (char *)0x00,
 .maxLen = 0x0a,
 .pressEvent = GUI_NULL,
 .releaseEvent = GUI_NULL,
 .updateEvent = GUI_NULL,
};
#define MPB7wID 0x0008
static const BUTTON_INFO MainPageButton7={
 {.wType = WIDGET_TYPE_BUTTON , .wId = 0x0008 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0x0102 , .y = 0x00AB , .width = 0x0050 , .height = 0x0050},
 .backMode = WIDGET_BACKMODE_CUTPIC,
 .fontlibId = 0x0000,
 .borderWidth = 0,
 .borderColor = 0x0000,
 .pressPicId  = 1,
 .releasePicId = 0,
 .pressBackColor = 0,
 .releaseBackColor = 0,
 .pressFontColor = 0,
 .releaseFontColor = 0,
 .xAlign = 0,
 .yAlign = 0,
 .isDr = 0,
 .text = (char *)0x00,
 .maxLen = 0x0a,
 .pressEvent = GUI_NULL,
 .releaseEvent = GUI_NULL,
 .updateEvent = GUI_NULL,
};
#define MPB8wID 0x0009
static const BUTTON_INFO MainPageButton8={
 {.wType = WIDGET_TYPE_BUTTON , .wId = 0x0009 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0x0173 , .y = 0x00AB , .width = 0x0050 , .height = 0x0050},
 .backMode = WIDGET_BACKMODE_CUTPIC,
 .fontlibId = 0x0000,
 .borderWidth = 0,
 .borderColor = 0x0000,
 .pressPicId  = 1,
 .releasePicId = 0,
 .pressBackColor = 0,
 .releaseBackColor = 0,
 .pressFontColor = 0,
 .releaseFontColor = 0,
 .xAlign = 0,
 .yAlign = 0,
 .isDr = 0,
 .text = (char *)0x00,
 .maxLen = 0x0a,
 .pressEvent = GUI_NULL,
 .releaseEvent = GUI_NULL,
 .updateEvent = GUI_NULL,
};
#define MPRollTBwID 0x000A
static const ROLLTEXTBOX_INFO MainPageRollTextBox={
 {.wType = WIDGET_TYPE_ROLLTEXTBOX , .wId = 0x000A , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0x0000 , .y = 0x0120 , .width = 480 , .height = 32},
 .backMode = WIDGET_BACKMODE_CUTPIC,
 .keyId = 255,
 .fontlibId = 0,
 .borderWidth = 2,
 .borderColor = 0x00ff,
 .picId = 0,
 .backColor = 0x0000,
 .frontColor = 0xFFFF,
 .xAlign = 0,
 .yAlign = 1,
 .isPassword = 1,
 .isDr = 0,
 .text = (char *)20, 
 .maxLen = 25,
 .dir = 1,                         
 .dis = 2,                        
 .timeOut = 200,                        
 .enable = 1,                   
 .textLen =  0,                     
 .count_st = (char *)0x00,							  			
 .start_x =	0x0000,					 					  
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL,                         
};
#define MPGTimerwID 0x000B
static const GTIMER_INFO MainPageGTimer={
 {.wType = WIDGET_TYPE_GTIMER , .wId = MPGTimerwID , .wVscope = WIDGET_VS_PRIVATE},
 .timeOut = 50,
 .enable = 1,                         //定时器开关位，0关，1开
 .timeValue = 0,                     //定时器当前计数值（周期是1MS）低16位是当前计数器值，高16位是定时器溢出标志，或者其他标识
 .timeoutEvent = GUI_NULL
};
#define MPNumBox1wID 0x000C
static const NUMBERBOX_INFO MainPageNumberBox1={
 {.wType = WIDGET_TYPE_NUMBERBOX , .wId = MPNumBox1wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 210 , .y = 2 , .width = 18 , .height = 16},
 .backMode = WIDGET_BACKMODE_CUTPIC,              
 .keyId = 255,                          
 .fontlibId = 0,                      
 .borderWidth = 0,                   
 .borderColor = 0xFFDC,              
 .picId = 0,                         
 .backColor = 0x00FF,
 .frontColor = 0xFFFF,
 .xAlign = 1,                        
 .yAlign = 1, 
 .formatType = 0,                     
 .isDr = 0,                           
 .data = 0,
 .maxLen = 2,                      
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};
#define MPNumBox2wID 0x000D
static const NUMBERBOX_INFO MainPageNumberBox2={
 {.wType = WIDGET_TYPE_NUMBERBOX , .wId = MPNumBox2wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 234 , .y = 2 , .width = 18 , .height = 16},
 .backMode = WIDGET_BACKMODE_CUTPIC,              
 .keyId = 255,                          
 .fontlibId = 0,                      
 .borderWidth = 0,                   
 .borderColor = 0xFFDC,              
 .picId = 0,                         
 .backColor = 0x00FF,
 .frontColor = 0xFFFF,
 .xAlign = 1,                        
 .yAlign = 1, 
 .formatType = 0,                     
 .isDr = 0,                           
 .data = 0,
 .maxLen = 2,                      
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};
#define MPNumBox3wID 0x000E
static const NUMBERBOX_INFO MainPageNumberBox3={
 {.wType = WIDGET_TYPE_NUMBERBOX , .wId = MPNumBox3wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 257 , .y = 2 , .width = 18 , .height = 16},
 .backMode = WIDGET_BACKMODE_CUTPIC,              
 .keyId = 255,                          
 .fontlibId = 0,                      
 .borderWidth = 0,                   
 .borderColor = 0xFFDC,              
 .picId = 0,                         
 .backColor = 0x00FF,
 .frontColor = 0xFFFF,
 .xAlign = 1,                        
 .yAlign = 1, 
 .formatType = 0,                     
 .isDr = 0,                           
 .data = 0,
 .maxLen = 2,                      
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};
#define MPTextBoxwID 0x000F
static const TEXTBOX_INFO MainPageTextBox={
 {.wType = WIDGET_TYPE_TEXTBOX , .wId = MPTextBoxwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 228 , .y = 2 , .width = 	32 , .height = 16},
 .backMode = WIDGET_BACKMODE_CUTPIC,                 
 .keyId = 255,                          
 .fontlibId = 0,                     
 .borderWidth = 0,                   
 .borderColor = 0x00FF,              
 .picId = 0,                         
 .backColor = 0x0000,
 .frontColor = 0xFFFF,
 .xAlign = 0,                        
 .yAlign = 1,                       
 .isPassword = 0,                  
 .isDr = 0,   
 .text = (char *)0x00,                 
 .maxLen = 6,                   
 .textLen = 0,            
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL                
};
gui_Err MainPageLeaveEvent(gui_int32 argc , const char **argv);
gui_Err MainPageEnterEvent(gui_int32 argc , const char **argv);

static gui_Err MainPageButton1_releaseEvent(gui_int32 argc , const char **argv);
static gui_Err MainPageButton2_releaseEvent(gui_int32 argc , const char **argv);
static gui_Err MainPageButton3_releaseEvent(gui_int32 argc , const char **argv);
static gui_Err MainPageButton4_releaseEvent(gui_int32 argc , const char **argv);
static gui_Err MainPageButton5_releaseEvent(gui_int32 argc , const char **argv);
static gui_Err MainPageButton6_releaseEvent(gui_int32 argc , const char **argv);
static gui_Err MainPageButton7_releaseEvent(gui_int32 argc , const char **argv);
static gui_Err MainPageButton8_releaseEvent(gui_int32 argc , const char **argv);
static gui_Err MainPageRTC_timeoutEvent(gui_int32 argc , const char **argv);

	








#endif
