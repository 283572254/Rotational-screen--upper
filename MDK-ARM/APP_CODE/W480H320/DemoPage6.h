#ifndef _DemoPage6_h
#define _DemoPage6_h
#include "gWidgetInfo.h"
#include "gStdint.h"
#include "gReturn.h"
#include "gResMsg.h"
#define DPwID 0x6001
static const PAGE_INFO DialogPage={
	{.wType = WIDGET_TYPE_PAGE , .wId = 0x6001 , .wVscope = WIDGET_VS_PRIVATE},
	{.x = 0 , .y = 0 , .width = 480 , .height = 200},
	.backMode = WIDGET_BACKMODE_NULL, 
	.backColor = 0x0000,
	.picId = 7,
	.enterEvent = GUI_NULL,
	.leaveEvent = GUI_NULL,
	.pressEvent = GUI_NULL,
	.releaseEvent = GUI_NULL,
};
#define DPPicwID 0x6002
static const PICTUREBOX_INFO DialogPagePicBox={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = 0x6002 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 46 , .y = 43 , .width = 400 , .height = 240},    
 .picId = 7,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define DPTextBoxwID 0x6003
static const TEXTBOX_INFO DialogPageTextBox={
 {.wType = WIDGET_TYPE_TEXTBOX , .wId = 0x6003 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 118 , .y = 137 , .width = 18 , .height = 16},
 .backMode = WIDGET_BACKMODE_COLOR,                 
 .keyId = 255,                          
 .fontlibId = 0,                     
 .borderWidth = 0,                   
 .borderColor = 0x00FF,              
 .picId = 7,                         
 .backColor = 0xFFFF,
 .frontColor = 0x0000,
 .xAlign = 0,                        
 .yAlign = 1,                       
 .isPassword = 0,                  
 .isDr = 1,   
 .text = (char *)0x20,                 
 .maxLen = 3,                   
 .textLen = 0x0000,          
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL                
};
#define DPButtonYESwID 0x6004	
static const BUTTON_INFO DialogPageButtonYES={
 {.wType = WIDGET_TYPE_BUTTON , .wId = 0x6004 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 259 , .y = 186 , .width = 65 , .height = 28},
 .backMode = WIDGET_BACKMODE_COLOR,
 .fontlibId = 0,
 .borderWidth = 1,
 .borderColor = 0x0000,
 .pressPicId  = 7,
 .releasePicId = 7,
 .pressBackColor = 0x0000,
 .releaseBackColor = 0Xffff,
 .pressFontColor = 0Xffff,
 .releaseFontColor = 0x0000,
 .xAlign = 1,
 .yAlign = 1,
 .isDr = 1,
 .text = (char *)0x03,
 .maxLen = 0x05,
 .pressEvent = GUI_NULL,
 .releaseEvent = GUI_NULL,
 .updateEvent = GUI_NULL,
};
#define DPButtonNOwID 0x6005	
static const BUTTON_INFO DialogPageButtonNO={
 {.wType = WIDGET_TYPE_BUTTON , .wId = 0x6005 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 340 , .y = 186 , .width = 65 , .height = 28},
 .backMode = WIDGET_BACKMODE_COLOR,
 .fontlibId = 0,
 .borderWidth = 1,
 .borderColor = 0x0000,
 .pressPicId  = 7,
 .releasePicId = 7,
 .pressBackColor = 0x0000,
 .releaseBackColor = 0Xffff,
 .pressFontColor = 0Xffff,
 .releaseFontColor = 0x0000,
 .xAlign = 1,
 .yAlign = 1,
 .isDr = 1,
 .text = (char *)0x02,
 .maxLen = 0x05,
 .pressEvent = GUI_NULL,
 .releaseEvent = GUI_NULL,
 .updateEvent = GUI_NULL,
};
#define DPNumBox1wID 0x6006
static const NUMBERBOX_INFO DialogPageNumberBox1={
 {.wType = WIDGET_TYPE_NUMBERBOX , .wId = DPNumBox1wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 134 , .y = 137 , .width = 18 , .height = 16},
 .backMode = WIDGET_BACKMODE_COLOR,              
 .keyId = 1,                          
 .fontlibId = 0,                      
 .borderWidth = 0,                   
 .borderColor = 0xFFDC,              
 .picId = 0,                         
 .backColor = 0xFFFF,
 .frontColor = 0x0000,
 .xAlign = 1,                        
 .yAlign = 1, 
 .formatType = 0,                     
 .isDr = 0,                           
 .data = 20,
 .maxLen = 2,                      
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};
#define DPNumBox2wID 0x6007
static const NUMBERBOX_INFO DialogPageNumberBox2={
 {.wType = WIDGET_TYPE_NUMBERBOX , .wId = DPNumBox2wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 170 , .y = 137 , .width = 18 , .height = 16},
 .backMode = WIDGET_BACKMODE_COLOR,              
 .keyId = 1,                          
 .fontlibId = 0,                      
 .borderWidth = 0,                   
 .borderColor = 0xFFDC,              
 .picId = 0,                         
 .backColor = 0xFFFF,
 .frontColor = 0x0000,
 .xAlign = 1,                        
 .yAlign = 1, 
 .formatType = 0,                     
 .isDr = 0,                           
 .data = 04,
 .maxLen = 2,                      
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};
#define DPNumBox3wID 0x6008
static const NUMBERBOX_INFO DialogPageNumberBox3={
 {.wType = WIDGET_TYPE_NUMBERBOX , .wId = DPNumBox3wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 205 , .y = 137 , .width = 18 , .height = 16},
 .backMode = WIDGET_BACKMODE_COLOR,              
 .keyId = 1,                          
 .fontlibId = 0,                      
 .borderWidth = 0,                   
 .borderColor = 0xFFDC,              
 .picId = 0,                         
 .backColor = 0xFFFF,
 .frontColor = 0x0000,
 .xAlign = 1,                        
 .yAlign = 1, 
 .formatType = 0,                     
 .isDr = 0,                           
 .data = 27,
 .maxLen = 2,                      
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};
#define DPNumBox4wID 0x6009
static const NUMBERBOX_INFO DialogPageNumberBox4={
 {.wType = WIDGET_TYPE_NUMBERBOX , .wId = DPNumBox4wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 258 , .y = 137 , .width = 18 , .height = 16},
 .backMode = WIDGET_BACKMODE_COLOR,              
 .keyId = 1,                          
 .fontlibId = 0,                      
 .borderWidth = 0,                   
 .borderColor = 0xFFDC,              
 .picId = 0,                         
 .backColor = 0xFFFF,
 .frontColor = 0x0000,
 .xAlign = 1,                        
 .yAlign = 1, 
 .formatType = 0,                     
 .isDr = 0,                           
 .data = 15,
 .maxLen = 2,                      
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};
#define DPNumBox5wID 0x600A
static const NUMBERBOX_INFO DialogPageNumberBox5={
 {.wType = WIDGET_TYPE_NUMBERBOX , .wId = DPNumBox5wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 285 , .y = 137 , .width = 18 , .height = 16},
 .backMode = WIDGET_BACKMODE_COLOR,              
 .keyId = 1,                          
 .fontlibId = 0,                      
 .borderWidth = 0,                   
 .borderColor = 0xFFDC,              
 .picId = 0,                         
 .backColor = 0xFFFF,
 .frontColor = 0x0000,
 .xAlign = 1,                        
 .yAlign = 1, 
 .formatType = 0,                     
 .isDr = 0,                           
 .data = 25,
 .maxLen = 2,                      
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};
#define DPNumBox6wID 0x600B
static const NUMBERBOX_INFO DialogPageNumberBox6={
 {.wType = WIDGET_TYPE_NUMBERBOX , .wId = DPNumBox6wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 313 , .y = 137 , .width = 18 , .height = 16},
 .backMode = WIDGET_BACKMODE_COLOR,              
 .keyId = 1,                          
 .fontlibId = 0,                      
 .borderWidth = 0,                   
 .borderColor = 0xFFDC,              
 .picId = 0,                         
 .backColor = 0xFFFF,
 .frontColor = 0x0000,
 .xAlign = 1,                        
 .yAlign = 1, 
 .formatType = 0,                     
 .isDr = 0,                           
 .data = 25,
 .maxLen = 2,                      
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};
gui_Err DialogPageEnterEvent(gui_int32 argc , const char **argv);
gui_Err DialogPageLeaveEvent(gui_int32 argc , const char **argv);
static gui_Err BackToHome_releaseEvent(gui_int32 argc , const char **argv);
static gui_Err ModifyTime_releaseEvent(gui_int32 argc , const char **argv);

#endif
