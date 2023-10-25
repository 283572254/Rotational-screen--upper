#ifndef _DemoPage8_h
#define _DemoPage8_h
#include "gWidgetInfo.h"
#include "gStdint.h"
#include "gReturn.h"
#include "gResMsg.h"
#include "rtcDriver.h"

#define AnimPwID 0x1261
static const PAGE_INFO AnimPage={
	{.wType = WIDGET_TYPE_PAGE , .wId = AnimPwID , .wVscope = WIDGET_VS_PRIVATE},
	{.x = 0 , .y = 0 , .width = 480 , .height = 320},
	.backMode = WIDGET_BACKMODE_PIC , 
	.backColor = 0x0000,
	.picId = 3,
	.enterEvent = GUI_NULL,
	.leaveEvent = GUI_NULL,
	.pressEvent = GUI_NULL,
	.releaseEvent = GUI_NULL,
};

#define AnimPPICANIMATIONwID 0x1262
static const PICANIMATION_INFO AnimPagePICANIMATION={
 {.wType = WIDGET_TYPE_PICANIMATION , .wId = AnimPPICANIMATIONwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0 , .y = 0 , .width = 480 , .height = 320},
 .beforePicId = 108,
 .afterPicId = 111,
 .playTime = 50,
 .pattern  = 0,
 .dis = 7,
 .enable=1,
 .replayEnable=1
};
#define AnimGTimerwID 0x1263
static const GTIMER_INFO AnimPageGTimer={
 {.wType = WIDGET_TYPE_GTIMER , .wId = AnimGTimerwID , .wVscope = WIDGET_VS_PRIVATE},
 .timeOut = 5000,
 .enable = 1,                         //定时器开关位，0关，1开
 .timeValue = 0,                     //定时器当前计数值（周期是1MS）低16位是当前计数器值，高16位是定时器溢出标志，或者其他标识
 .timeoutEvent = GUI_NULL
};

gui_Err AnimPageEnterEvent(gui_int32 argc , const char **argv);
gui_Err AnimPageLeaveEvent(gui_int32 argc , const char **argv);
static gui_Err BackToHome_releaseEvent(gui_int32 argc , const char **argv);
static gui_Err AnimPage_timeoutEvent(gui_int32 argc , const char **argv);

#endif


