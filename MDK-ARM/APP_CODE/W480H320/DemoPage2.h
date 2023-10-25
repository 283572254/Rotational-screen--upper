#ifndef _DemoPage2_h
#define _DemoPage2_h
#include "gWidgetInfo.h"
#include "gStdint.h"
#include "gReturn.h"
#include "gResMsg.h"
//**************************空调主界面*********************//
#define ACPwID 0x2001
static const PAGE_INFO ACPage={
	{.wType = WIDGET_TYPE_PAGE , .wId = ACPwID , .wVscope = WIDGET_VS_PRIVATE},
	{.x = 0 , .y = 0 , .width = 320 , .height = 480},
	.backMode = WIDGET_BACKMODE_PIC , 
	.backColor = 0x00FF,
	.picId = 25,
	.enterEvent = GUI_NULL,
	.leaveEvent = GUI_NULL,
	.pressEvent = GUI_NULL,
	.releaseEvent = GUI_NULL,
};
#define ACPMenuButton1wID 0x2002
static const BUTTON_INFO ACMenuButton1={
 {.wType = WIDGET_TYPE_BUTTON , .wId = ACPMenuButton1wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0 , .y = 260 , .width = 96 , .height = 60},
 .backMode = WIDGET_BACKMODE_CUTPIC,
 .fontlibId = 1,              
 .borderWidth = 1,              
 .borderColor = 0xFFDC,        
 .pressPicId  = 39,             
 .releasePicId = 25,             
 .pressBackColor = 0x0020,
 .releaseBackColor = 0xBDF7,   
 .pressFontColor = 0xFFFF,        
 .releaseFontColor = 0x0000,      
 .xAlign = 1,
 .yAlign = 1,
 .isDr = 1,                   
 .text = (char *)0x04,
 .maxLen = 0x06,
 .pressEvent = GUI_NULL,
 .releaseEvent = GUI_NULL,
 .updateEvent = GUI_NULL,
};
#define ACPMenuButton2wID 0x2003
static const BUTTON_INFO ACMenuButton2={
 {.wType = WIDGET_TYPE_BUTTON , .wId = ACPMenuButton2wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 96 , .y = 260 , .width = 96 , .height = 60},
 .backMode = WIDGET_BACKMODE_CUTPIC,
 .fontlibId = 1,              
 .borderWidth = 1,              
 .borderColor = 0xFFDC,        
 .pressPicId  = 39,             
 .releasePicId = 25,                  
 .pressBackColor = 0x0020,
 .releaseBackColor = 0xBDF7,   
 .pressFontColor = 0xFFFF,        
 .releaseFontColor = 0x0000,      
 .xAlign = 1,
 .yAlign = 1,
 .isDr = 1,                   
 .text = (char *)0x04,
 .maxLen = 0x06,
 .pressEvent = GUI_NULL,
 .releaseEvent = GUI_NULL,
 .updateEvent = GUI_NULL,
};
#define ACPMenuButton3wID 0x2004
static const BUTTON_INFO ACMenuButton3={
 {.wType = WIDGET_TYPE_BUTTON , .wId = ACPMenuButton3wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 192 , .y = 260 , .width = 96 , .height = 60},
 .backMode = WIDGET_BACKMODE_CUTPIC,
 .fontlibId = 1,              
 .borderWidth = 1,              
 .borderColor = 0xFFDC,        
 .pressPicId  = 39,             
 .releasePicId = 25,                  
 .pressBackColor = 0x0020,
 .releaseBackColor = 0xBDF7,   
 .pressFontColor = 0xFFFF,        
 .releaseFontColor = 0x0000,      
 .xAlign = 1,
 .yAlign = 1,
 .isDr = 1,                   
 .text = (char *)0x04,
 .maxLen = 0x06,
 .pressEvent = GUI_NULL,
 .releaseEvent = GUI_NULL,
 .updateEvent = GUI_NULL,
};
#define ACPMenuButton4wID 0x2005
static const BUTTON_INFO ACMenuButton4={
 {.wType = WIDGET_TYPE_BUTTON , .wId = ACPMenuButton4wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 288 , .y = 260 , .width = 96 , .height = 60},
 .backMode = WIDGET_BACKMODE_CUTPIC,
 .fontlibId = 1,              
 .borderWidth = 1,              
 .borderColor = 0xFFDC,        
 .pressPicId  = 39,             
 .releasePicId = 25,                  
 .pressBackColor = 0x0020,
 .releaseBackColor = 0xBDF7,   
 .pressFontColor = 0xFFFF,        
 .releaseFontColor = 0x0000,      
 .xAlign = 1,
 .yAlign = 1,
 .isDr = 1,                   
 .text = (char *)0x04,
 .maxLen = 0x06,
 .pressEvent = GUI_NULL,
 .releaseEvent = GUI_NULL,
 .updateEvent = GUI_NULL,
};
#define ACPMenuButton5wID 0x2006
static const BUTTON_INFO ACMenuButton5={
 {.wType = WIDGET_TYPE_BUTTON , .wId = ACPMenuButton5wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 384 , .y = 260 , .width = 96 , .height = 60},
 .backMode = WIDGET_BACKMODE_CUTPIC,
 .fontlibId = 1,              
 .borderWidth = 1,              
 .borderColor = 0xFFDC,        
 .pressPicId  = 39,             
 .releasePicId = 25,                   
 .pressBackColor = 0x0020,
 .releaseBackColor = 0xBDF7,   
 .pressFontColor = 0xFFFF,        
 .releaseFontColor = 0x0000,      
 .xAlign = 1,
 .yAlign = 1,
 .isDr = 1,                   
 .text = (char *)0x04,
 .maxLen = 0x06,
 .pressEvent = GUI_NULL,
 .releaseEvent = GUI_NULL,
 .updateEvent = GUI_NULL,
};
#define ACPNumBox1wID 0x2007
static const NUMBERBOX_INFO ACPageNumBox1={
 {.wType = WIDGET_TYPE_NUMBERBOX , .wId = ACPNumBox1wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 154 , .y = 193 , .width = 	50 , .height = 50},
 .backMode = WIDGET_BACKMODE_CUTPIC,                 
 .keyId = 255,                          
 .fontlibId = 1,                     
 .borderWidth = 26,                   
 .borderColor = 0x00FF,              
 .picId = 25,                         
 .backColor = 0x0000,
 .frontColor = 0xFFFF,
 .xAlign = 0,                        
 .yAlign = 1,                       
 .formatType = 0,                  
 .isDr = 0,   
 .data = 28,               
 .maxLen = 2,                                         
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL               
};
#define ACPNumBox2wID 0x2008
static const NUMBERBOX_INFO ACPageNumBox2={
 {.wType = WIDGET_TYPE_NUMBERBOX , .wId = ACPNumBox2wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 324 , .y = 193 , .width = 	50 , .height = 50},
 .backMode = WIDGET_BACKMODE_CUTPIC,                 
 .keyId = 255,                          
 .fontlibId = 1,                     
 .borderWidth = 0,                   
 .borderColor = 0x00FF,              
 .picId = 25,                         
 .backColor = 0x0000,
 .frontColor = 0xFFFF,
 .xAlign = 0,                        
 .yAlign = 1,                       
 .formatType = 0,                  
 .isDr = 0,   
 .data = 30,               
 .maxLen = 2,                                         
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL              
};
#define ACPTextBox3wID 0x2009
static const TEXTBOX_INFO ACPageTextBox3={
 {.wType = WIDGET_TYPE_TEXTBOX , .wId = ACPTextBox3wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 180 , .y = 100 , .width = 	60 , .height = 60},
 .backMode = WIDGET_BACKMODE_CUTPIC,                 
 .keyId = 255,                          
 .fontlibId = 2,                     
 .borderWidth = 0,                   
 .borderColor = 0x00FF,              
 .picId = 25,                         
 .backColor = 0x0000,
 .frontColor = 0xFFEF,
 .xAlign = 1,                        
 .yAlign = 1,                       
 .isPassword = 0,                  
 .isDr = 0,   
 .text = (char *)0x00,                 
 .maxLen = 4,                   
 .textLen = 0x0005,            
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL                
};
#define ACPBackButtonwID 0x200A
static const BUTTON_INFO ACPBackButton={
 {.wType = WIDGET_TYPE_BUTTON , .wId = ACPBackButtonwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0 , .y = 0 , .width = 50 , .height = 40},
 .backMode = WIDGET_BACKMODE_CUTPIC,
 .fontlibId = 1,              
 .borderWidth = 1,              
 .borderColor = 0xFFDC,        
 .pressPicId  = 39,             
 .releasePicId = 25,                  
 .pressBackColor = 0x0020,
 .releaseBackColor = 0xBDF7,   
 .pressFontColor = 0xFFFF,        
 .releaseFontColor = 0x0000,      
 .xAlign = 1,
 .yAlign = 1,
 .isDr = 1,                   
 .text = (char *)0x04,
 .maxLen = 0x06,
 .pressEvent = GUI_NULL,
 .releaseEvent = GUI_NULL,
 .updateEvent = GUI_NULL,
};
#define ACPModeButtonwID 0x200B
static const BUTTON_INFO ACPModeButton={
 {.wType = WIDGET_TYPE_BUTTON , .wId = ACPModeButtonwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 30 , .y = 200 , .width = 65 , .height = 35},
 .backMode = WIDGET_BACKMODE_COLOR,
 .fontlibId = 0,              
 .borderWidth = 1,              
 .borderColor = 0x0000,        
 .pressPicId  = 39,             
 .releasePicId = 25,                  
 .pressBackColor = 0x0000,
 .releaseBackColor = 0Xffff,
 .pressFontColor = 0Xffff,
 .releaseFontColor = 0x0000,     
 .xAlign = 1,
 .yAlign = 1,
 .isDr = 1,                   
 .text = (char *)0x04,
 .maxLen = 0x06,
 .pressEvent = GUI_NULL,
 .releaseEvent = GUI_NULL,
 .updateEvent = GUI_NULL,
};
#define ACPWindButtonDIRwID 0x200C
static const BUTTON_INFO ACPWindButtonDIR={
 {.wType = WIDGET_TYPE_BUTTON , .wId = ACPWindButtonDIRwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 390 , .y = 205 , .width = 65 , .height = 35},
 .backMode = WIDGET_BACKMODE_COLOR,
 .fontlibId = 0,              
 .borderWidth = 1,              
 .borderColor = 0x0000,        
 .pressPicId  = 39,             
 .releasePicId = 25,                   
 .pressBackColor = 0x0000,
 .releaseBackColor = 0Xffff,
 .pressFontColor = 0Xffff,
 .releaseFontColor = 0x0000,      
 .xAlign = 1,
 .yAlign = 1,
 .isDr = 1,                   
 .text = (char *)0x04,
 .maxLen = 0x06,
 .pressEvent = GUI_NULL,
 .releaseEvent = GUI_NULL,
 .updateEvent = GUI_NULL,
};
#define ACPOptionBox1wID 0x200D
static const OPTIONBOX_INFO ACPageOptionBox1={   
 {.wType = WIDGET_TYPE_OPTIONBOX , .wId = ACPOptionBox1wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 369 , .y = 123 , .width = 20 , .height = 20},
 .backMode = WIDGET_BACKMODE_COLOR ,  
 .optionType = OPTIONBOX_TYPE_CIRCLE,
 .backColor = 0x355E,
 .frontColor = 0xFFFF,
 .cPicId = 0,                      
 .nocPicId = 1,                    
 .value = OPTIONBOX_STATE_CHOOSE,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL       
};
#define ACPOptionBox2wID 0x200E
static const OPTIONBOX_INFO ACPageOptionBox2={   
 {.wType = WIDGET_TYPE_OPTIONBOX , .wId = ACPOptionBox2wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 433 , .y = 123 , .width = 20 , .height = 20},
 .backMode = WIDGET_BACKMODE_COLOR ,  
 .optionType = OPTIONBOX_TYPE_CIRCLE,
 .backColor = 0x355E,
 .frontColor = 0xFFFF,
 .cPicId = 0,                      
 .nocPicId = 1,                    
 .value = OPTIONBOX_STATE_NOCHOOSE,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL       
};
#define ACPWindButtonwID 0x200F
static const BUTTON_INFO ACPWindButton={
 {.wType = WIDGET_TYPE_BUTTON , .wId = ACPWindButtonwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 390 , .y = 165 , .width = 65 , .height = 35},
 .backMode = WIDGET_BACKMODE_COLOR,
 .fontlibId = 0,              
 .borderWidth = 1,              
 .borderColor = 0x0000,        
 .pressPicId  = 39,             
 .releasePicId = 25,                   
 .pressBackColor = 0x0000,
 .releaseBackColor = 0Xffff,
 .pressFontColor = 0Xffff,
 .releaseFontColor = 0x0000,     
 .xAlign = 1,
 .yAlign = 1,
 .isDr = 1,                   
 .text = (char *)0x04,
 .maxLen = 0x06,
 .pressEvent = GUI_NULL,
 .releaseEvent = GUI_NULL,
 .updateEvent = GUI_NULL,
};
#define ACPModePICwID 0x2010
static const PICTUREBOX_INFO  ACPageModePIC={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = ACPModePICwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 34 , .y = 57 , .width = 58 , .height = 81},    
 .picId = 14,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define ACPWindDIR1PICwID 0x2011   //风向上下
static const PICTUREBOX_INFO  ACPageWindDIR1PIC={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = ACPWindDIR1PICwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 442 , .y = 88 , .width = 30 , .height = 30},    
 .picId = 47,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define ACPWindDIR2PICwID 0x2012   //风向左右
static const PICTUREBOX_INFO  ACPageWindDIR2PIC={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = ACPWindDIR2PICwID  , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 349 , .y = 102 , .width = 60 , .height = 15},    
 .picId = 51,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define ACPWSPICwID 0x2013
static const PICTUREBOX_INFO  ACPageWindSpeedPIC={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = ACPWSPICwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 375 , .y = 30 , .width = 85 , .height = 30},    
 .picId = 40,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define ACPTemp1PICwID 0x2014  //个位
static const PICTUREBOX_INFO  ACPTemp1PIC={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = ACPTemp1PICwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 186 , .y = 74 , .width = 60 , .height = 100},    
 .picId = 75,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define ACPTemp2PICwID 0x2015    //十位
static const PICTUREBOX_INFO  ACPTemp2PIC={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = ACPTemp2PICwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 126 , .y = 74 , .width = 60 , .height = 100},    
 .picId = 85,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define ACPGTimerwID 0x2016
static const GTIMER_INFO ACPageGTimer={
 {.wType = WIDGET_TYPE_GTIMER , .wId = ACPGTimerwID , .wVscope = WIDGET_VS_PRIVATE},
 .timeOut = 80,
 .enable = 1,                         //定时器开关位，0关，1开
 .timeValue = 0,                     //定时器当前计数值（周期是1MS）低16位是当前计数器值，高16位是定时器溢出标志，或者其他标识
 .timeoutEvent = GUI_NULL
};
gui_Err ACPageEnterEvent(gui_int32 argc , const char **argv);
gui_Err ACPageLeaveEvent(gui_int32 argc , const char **argv);
static gui_Err ACPage_pressEvent(gui_int32 argc , const char **argv);
static gui_Err BackToHome_releaseEvent(gui_int32 argc , const char **argv);
static gui_Err ACPageOption1_pressEvent(gui_int32 argc , const char **argv);
static gui_Err ACPageOption2_pressEvent(gui_int32 argc , const char **argv);
static gui_Err ACPageSetMode_releaseEvent(gui_int32 argc , const char **argv);
static gui_Err ACPageSetWindSpeed_releaseEvent(gui_int32 argc , const char **argv);
static gui_Err ACPageSetWindDir_releaseEvent(gui_int32 argc , const char **argv);
static gui_Err ACPageTemp_timeoutEvent(gui_int32 argc , const char **argv);

#endif
