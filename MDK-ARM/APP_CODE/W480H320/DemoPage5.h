#ifndef _DemoPage5_h
#define _DemoPage5_h
#include "gWidgetInfo.h"
#include "gStdint.h"
#include "gReturn.h"
#include "gResMsg.h"


static gui_uint32 Speed_VAL;
static gui_uint32 Slider_VAL;

#define PointerPwID 0x5001
static const PAGE_INFO PointerPage={
	{.wType = WIDGET_TYPE_PAGE , .wId = 0x5001 , .wVscope = WIDGET_VS_PRIVATE},
	{.x = 0 , .y = 0 , .width = 480 , .height = 320},
	.backMode = WIDGET_BACKMODE_PIC , 
	.backColor = 0x00FF,
	.picId = 105,
	.enterEvent = GUI_NULL,
	.leaveEvent = GUI_NULL,
	.pressEvent = GUI_NULL,
	.releaseEvent = GUI_NULL,
};

//#define PointerPPointerLwID 0x5004
//static const POINTER_INFO PointerPagePointerL={
// {.wType = WIDGET_TYPE_POINTER , .wId = 0x5004 , .wVscope = WIDGET_VS_PRIVATE},
// {.x = 39 , .y = 110 , .width = 138 , .height = 138},
// .backMode = WIDGET_BACKMODE_CUTPIC,               
// .picId = 2,                          //图片或者切图模式下：图片ID
// .backColor = 0xFFFF,                       //单色模式下：背景颜色
// .frontColor = 0x00FF,                     //单色模式下：前景颜色
// .frontWidth = 8,                    //指针线宽
// .circleRadius = 5,                  //指针的圆心半径，像素单位
// .AngleValue = 240,                     //弧度值0-360，标识着指针显示的位置
// .pressEvent = GUI_NULL,               
// .releaseEvent = GUI_NULL,             
// .updateEvent = GUI_NULL 
//};
//#define PointerPPointerRwID 0x5005
//static const POINTER_INFO PointerPagePointerR={
// {.wType = WIDGET_TYPE_POINTER , .wId = 0x5005 , .wVscope = WIDGET_VS_PRIVATE},
// {.x = 305	 , .y = 110 , .width = 138 , .height = 138},
// .backMode = WIDGET_BACKMODE_CUTPIC,               
// .picId = 2,                          //图片或者切图模式下：图片ID
// .backColor = 0xFFFF,                       //单色模式下：背景颜色
// .frontColor = 0x00FF,                     //单色模式下：前景颜色
// .frontWidth = 8,                    //指针线宽
// .circleRadius = 5,                  //指针的圆心半径，像素单位
// .AngleValue = 240,                     //弧度值0-360，标识着指针显示的位置
// .pressEvent = GUI_NULL,               
// .releaseEvent = GUI_NULL,             
// .updateEvent = GUI_NULL 
//};
//#define PointerPGTimerwID 0x5006
//static const GTIMER_INFO PointerPageGTimer={
// {.wType = WIDGET_TYPE_GTIMER , .wId = 0x5006 , .wVscope = WIDGET_VS_PRIVATE},
// .timeOut = 100,
// .enable = 1,                         //定时器开关位，0关，1开
// .timeValue = 0,                     //定时器当前计数值（周期是1MS）低16位是当前计数器值，高16位是定时器溢出标志，或者其他标识
// .timeoutEvent = GUI_NULL
//}; 

#define PPButton1wID 0x5007
static const BUTTON_INFO PointerPageButton1={
 {.wType = WIDGET_TYPE_BUTTON , .wId = PPButton1wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 28 , .y = 9 , .width = 32 , .height = 38},
 .backMode = WIDGET_BACKMODE_CUTPIC,
 .fontlibId = 1,              
 .borderWidth = 1,              
 .borderColor = 0xFFDC,        
 .pressPicId  = 106,             
 .releasePicId = 105,            
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
#define PPButton2wID 0x5008
static const BUTTON_INFO PointerPageButton2={
 {.wType = WIDGET_TYPE_BUTTON , .wId = PPButton2wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 405 , .y = 162 , .width = 37 , .height = 35},
 .backMode = WIDGET_BACKMODE_CUTPIC,
 .fontlibId = 1,              
 .borderWidth = 1,              
 .borderColor = 0xFFDC,        
 .pressPicId  = 106,             
 .releasePicId = 105,            
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
#define PPButton3wID 0x5009
static const BUTTON_INFO PointerPageButton3={
 {.wType = WIDGET_TYPE_BUTTON , .wId = PPButton3wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 405 , .y = 209 , .width = 37 , .height = 35},
 .backMode = WIDGET_BACKMODE_CUTPIC,
 .fontlibId = 1,              
 .borderWidth = 1,              
 .borderColor = 0xFFDC,        
 .pressPicId  = 106,             
 .releasePicId = 105,            
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
#define PPButton4wID 0x5010
static const BUTTON_INFO PointerPageButton4={
 {.wType = WIDGET_TYPE_BUTTON , .wId = PPButton4wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 405 , .y = 256 , .width = 37 , .height = 35},
 .backMode = WIDGET_BACKMODE_CUTPIC,
 .fontlibId = 1,              
 .borderWidth = 1,              
 .borderColor = 0xFFDC,        
 .pressPicId  = 106,             
 .releasePicId = 105,            
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
#define PPageRoundSliderwID 0x5002
static const ROUNDSLIDER_INFO PointerPageRoundSlider={    
 {.wType = WIDGET_TYPE_ROUNDSLIDER , .wId = PPageRoundSliderwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 229 , .y = 188 , .width = 62 , .height = 62},  
 .backMode = WIDGET_BACKMODE_PIC,
 .backColor = 0xFF00,
 .outerRadius=0,
 .insideRadius=0,
 .backPicId = 104,
 .vernierMode = WIDGET_BACKMODE_PIC,
 .vernierColor = 0xF800,
 .vernierPicId = 107,
 .vernierWidth = 13,
 .value = 220,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL, 
 .slidEvent = GUI_NULL, 
 .updateEvent = GUI_NULL  
};
#define PointerPPointerwID 0x5003
static const POINTER_INFO PointerPagePointer={
 {.wType = WIDGET_TYPE_POINTER , .wId = 0x5003 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 184 , .y = 100 , .width = 112 , .height = 112},
 .backMode = WIDGET_BACKMODE_CUTPIC,               
 .picId = 105,                          //图片或者切图模式下：图片ID
 .backColor = 0xFFFF,                       //单色模式下：背景颜色
 .frontColor = 0xFFFF,                     //单色模式下：前景颜色
 .frontWidth = 3,                    //指针线宽
 .circleRadius = 3,                  //指针的圆心半径，像素单位
 .AngleValue = 125,                     //弧度值0-360，标识着指针显示的位置
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};

gui_Err PointerPageEnterEvent(gui_int32 argc , const char **argv);
gui_Err PointerPageLeaveEvent(gui_int32 argc , const char **argv);
//static gui_Err PointerPage_TimeOut_Event(gui_int32 argc , const char **argv);
static gui_Err BackToHome_releaseEvent(gui_int32 argc , const char **argv);
static gui_Err PointerPage_RoundSlider_slideEvent(gui_int32 argc , const char **argv);



#endif
