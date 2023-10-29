#ifndef _DemoTest01_h
#define _DemoTest01_h
#include "gWidgetInfo.h"
#include "gStdint.h"
#include "gReturn.h"
#include "gResMsg.h"
#include "rtcDriver.h"

/******************************************* Knob screen    Function interface**************************************************************/
#define Test01Page_wID 0x1501
static const PAGE_INFO DemoTest01_Page={
	{.wType = WIDGET_TYPE_PAGE , .wId = Test01Page_wID , .wVscope = WIDGET_VS_PRIVATE},
	{.x = 0 , .y = 0 , .width = 240 , .height = 240},
	.backMode = WIDGET_BACKMODE_PIC , 
	.backColor = 0xFFFF,
	.picId = 0,
	.enterEvent = GUI_NULL,
	.leaveEvent = GUI_NULL,
	.pressEvent = GUI_NULL,
	.releaseEvent = GUI_NULL,
};

#define Test01_PicwID 0x1502 //
static const PICTUREBOX_INFO DemoTest01_Pic={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = Test01_PicwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0 , .y = 0 , .width = 240 , .height = 240},    
 .picId = 0,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define Test01_GTimerwID 0x1503
static const GTIMER_INFO DemoTest01_GTimer={
 {.wType = WIDGET_TYPE_GTIMER , .wId = Test01_GTimerwID , .wVscope = WIDGET_VS_PRIVATE},
 .timeOut =50,
 .enable = 1,                         //Timer switch bit, 0 off, 1 on
 .timeValue = 0,                     //Timer current count value (period is 1MS) lower 16 bits are current counter value, higher 16 bits are timer overflow flag, or other identification
 .timeoutEvent = GUI_NULL
};
void DemoTestPage_Init(void);
gui_Err DemoMain_PageEnterEvent(gui_int32 argc , const char **argv);
static gui_Err DemoTest01_timeoutEvent (gui_int32 argc , const char **argv);
gui_Err DemoTest01_LeaveEvent(gui_int32 argc , const char **argv);
/****************************************************  red led page*************************************************/	
#define Tred_led_wID 0x1601
static const PAGE_INFO red_led_Page={
	{.wType = WIDGET_TYPE_PAGE , .wId = Tred_led_wID , .wVscope = WIDGET_VS_PRIVATE},
	{.x = 0 , .y = 0 , .width = 240 , .height = 240},
	.backMode = WIDGET_BACKMODE_PIC , 
	.backColor = 0xFFFF,
	.picId = 21,
	.enterEvent = GUI_NULL,
	.leaveEvent = GUI_NULL,
	.pressEvent = GUI_NULL,
	.releaseEvent = GUI_NULL,
};

#define red_led_PicwID 0x1602 //
static const PICTUREBOX_INFO red_led_Pic={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = red_led_PicwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0 , .y = 0 , .width = 240 , .height = 240},    
 .picId = 21,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define red_led_GTimerwID 0x1603
static const GTIMER_INFO red_led_GTimer={
 {.wType = WIDGET_TYPE_GTIMER , .wId = red_led_GTimerwID , .wVscope = WIDGET_VS_PRIVATE},
 .timeOut =50,
 .enable = 1,                         //Timer switch bit, 0 off, 1 on
 .timeValue = 0,                     //Timer current count value (period is 1MS) lower 16 bits are current counter value, higher 16 bits are timer overflow flag, or other identification
 .timeoutEvent = GUI_NULL
};
void DemoTestPage_Init(void);
gui_Err red_led_PageEnterEvent(gui_int32 argc , const char **argv);
static gui_Err red_led_timeoutEvent (gui_int32 argc , const char **argv);
gui_Err red_led_LeaveEvent(gui_int32 argc , const char **argv);
/****************************************************  red led page2*************************************************/	
#define Tred_led_wID2 0x1604
static const PAGE_INFO red_led_Page2={
	{.wType = WIDGET_TYPE_PAGE , .wId = Tred_led_wID2 , .wVscope = WIDGET_VS_PRIVATE},
	{.x = 0 , .y = 0 , .width = 240 , .height = 240},
	.backMode = WIDGET_BACKMODE_PIC , 
	.backColor = 0xFFFF,
 .picId = 0,
	.enterEvent = GUI_NULL,
	.leaveEvent = GUI_NULL,
	.pressEvent = GUI_NULL,
	.releaseEvent = GUI_NULL,
};

#define red_led_PicwID2 0x1605 //
static const PICTUREBOX_INFO red_led_Pic2={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = red_led_PicwID2 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0 , .y = 0 , .width = 240 , .height = 240},    
 .picId = 0,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define red_led_ID1 0x1606 //
static const PICTUREBOX_INFO red_led_1={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = red_led_ID1 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 10 , .y = 102 , .width = 36 , .height = 36},    
 .picId = 20,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define red_led_ID2 0x1607 //
static const PICTUREBOX_INFO red_led_2={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = red_led_ID2 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 50 , .y = 102 , .width = 36 , .height = 36},    
 .picId = 20,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define red_led_ID5 0x1608 //
static const PICTUREBOX_INFO red_led_5={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = red_led_ID5 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 90 , .y = 102 , .width = 36 , .height = 36},    
 .picId = 20,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define red_led_ID8 0x1609//
static const PICTUREBOX_INFO red_led_8={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = red_led_ID8 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 130 , .y = 102 , .width = 36 , .height = 36},    
 .picId = 20,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define red_led_ID10 0x1610 //
static const PICTUREBOX_INFO red_led_10={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = red_led_ID10 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 170 , .y = 102 , .width = 36 , .height = 36},    
 .picId = 20,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define red_led_ID10_1 0x1623 //
static const PICTUREBOX_INFO red_led_10_1={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = red_led_ID10_1 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 200 , .y = 102 , .width = 36 , .height = 36},    
 .picId = 20,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};

#define red_led_location_ID 0x1624 //
static const PICTUREBOX_INFO red_led_location={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = red_led_location_ID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0 , .y = 120 , .width = 36 , .height = 36},    
 .picId = 20,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define red_led_onoff_ID 0x1611 //
static const PICTUREBOX_INFO red_led_onoff={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = red_led_onoff_ID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 90 , .y = 160 , .width = 60 , .height = 60},    
 .picId = 22,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};

#define red_led_GTimerwID2 0x1612
static const GTIMER_INFO red_led_GTimer2={
 {.wType = WIDGET_TYPE_GTIMER , .wId = red_led_GTimerwID2 , .wVscope = WIDGET_VS_PRIVATE},
 .timeOut =50,
 .enable = 1,                         //Timer switch bit, 0 off, 1 on
 .timeValue = 0,                     //Timer current count value (period is 1MS) lower 16 bits are current counter value, higher 16 bits are timer overflow flag, or other identification
 .timeoutEvent = GUI_NULL
};

gui_Err red_led_PageEnterEvent2(gui_int32 argc , const char **argv);
static gui_Err red_led_timeoutEvent2 (gui_int32 argc , const char **argv);
gui_Err red_led_LeaveEvent2(gui_int32 argc , const char **argv);

/****************************************************  infrared led page*************************************************/	
#define infrared_led_wID 0x1613
static const PAGE_INFO infrared_led_Page={
	{.wType = WIDGET_TYPE_PAGE , .wId = infrared_led_wID , .wVscope = WIDGET_VS_PRIVATE},
	{.x = 0 , .y = 0 , .width = 240 , .height = 240},
	.backMode = WIDGET_BACKMODE_PIC , 
	.backColor = 0xFFFF,
 .picId = 0,
	.enterEvent = GUI_NULL,
	.leaveEvent = GUI_NULL,
	.pressEvent = GUI_NULL,
	.releaseEvent = GUI_NULL,
};

#define infrared_led_PicwID 0x1614 //
static const PICTUREBOX_INFO infrared_led_Pic={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = infrared_led_PicwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0 , .y = 0 , .width = 240 , .height = 240},    
 .picId = 0,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define infrared_led_GTimerwID 0x1615
static const GTIMER_INFO infrared_led_GTimer={
 {.wType = WIDGET_TYPE_GTIMER , .wId = infrared_led_GTimerwID, .wVscope = WIDGET_VS_PRIVATE},
 .timeOut =50,
 .enable = 1,                         //Timer switch bit, 0 off, 1 on
 .timeValue = 0,                     //Timer current count value (period is 1MS) lower 16 bits are current counter value, higher 16 bits are timer overflow flag, or other identification
 .timeoutEvent = GUI_NULL
};
#define infrared_led_ID1 0x1616 //
static const PICTUREBOX_INFO infrared_led_1={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = infrared_led_ID1 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 66 , .y = 102 , .width = 34 , .height = 46},    
 .picId = 24,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define infrared_led_ID2 0x1617 //
static const PICTUREBOX_INFO infrared_led_2={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = infrared_led_ID2 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 102 , .y = 102 , .width = 34 , .height = 46},    
 .picId = 24,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};

#define infrared_led_ID3 0x1618 //
static const PICTUREBOX_INFO infrared_led_3={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = infrared_led_ID3 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 138 , .y = 102 , .width = 34 , .height = 46},    
 .picId = 24,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};

gui_Err infrared_PageEnterEvent(gui_int32 argc , const char **argv);
static gui_Err infrared_timeoutEvent (gui_int32 argc , const char **argv);
gui_Err infrared_LeaveEvent(gui_int32 argc , const char **argv);
/****************************************************  infrared_led2 page*************************************************/	
#define infrared_led_wID2 0x1619
static const PAGE_INFO infrared_led_Page2={
	{.wType = WIDGET_TYPE_PAGE , .wId = infrared_led_wID2 , .wVscope = WIDGET_VS_PRIVATE},
	{.x = 0 , .y = 0 , .width = 240 , .height = 240},
	.backMode = WIDGET_BACKMODE_PIC , 
	.backColor = 0xFFFF,
 .picId = 0,
	.enterEvent = GUI_NULL,
	.leaveEvent = GUI_NULL,
	.pressEvent = GUI_NULL,
	.releaseEvent = GUI_NULL,
};

#define infrared_led_PicwID2 0x1620 //
static const PICTUREBOX_INFO infrared_led_Pic2={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = infrared_led_PicwID2 , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0 , .y = 0 , .width = 240 , .height = 240},    
 .picId = 0,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define infrared_led_GTimerwID2 0x1621
static const GTIMER_INFO infrared_led_GTimer2={
 {.wType = WIDGET_TYPE_GTIMER , .wId = infrared_led_GTimerwID2, .wVscope = WIDGET_VS_PRIVATE},
 .timeOut =50,
 .enable = 1,                         //Timer switch bit, 0 off, 1 on
 .timeValue = 0,                     //Timer current count value (period is 1MS) lower 16 bits are current counter value, higher 16 bits are timer overflow flag, or other identification
 .timeoutEvent = GUI_NULL
};

gui_Err infrared_PageEnterEvent2(gui_int32 argc , const char **argv);
static gui_Err infrared_timeoutEvent2(gui_int32 argc , const char **argv);
gui_Err infrared_LeaveEvent2(gui_int32 argc , const char **argv);

/****************************************************  Pump page*************************************************/	
#define infrared_led_pump_ID 0x1622 //
static const PICTUREBOX_INFO infrared_led_pump={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = infrared_led_pump_ID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0 , .y = 0 , .width = 240 , .height = 240},    
 .picId = 33,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
//ID 0x1623
/****************************************************  shortKey page*************************************************/	
#define Short_Key_PwID 0x1504
static const PAGE_INFO Encoder_shortKey={
	{.wType = WIDGET_TYPE_PAGE , .wId = Short_Key_PwID , .wVscope = WIDGET_VS_PRIVATE},
	{.x = 0 , .y = 0 , .width = 240 , .height = 240},
	.backMode = WIDGET_BACKMODE_NULL , 
	.backColor = 0xFFFF,
	.picId = 56,
	.enterEvent = GUI_NULL,
	.leaveEvent = GUI_NULL,
	.pressEvent = GUI_NULL,
	.releaseEvent = GUI_NULL,
};

#define ShortKey_PicwID 0x1505 //
static const PICTUREBOX_INFO ShortKey_Pic={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = ShortKey_PicwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0 , .y = 0 , .width = 240 , .height = 240},    
 .picId = 56,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define ShortKey_GTimerwID 0x1506
static const GTIMER_INFO ShortKey_GTimer={
 {.wType = WIDGET_TYPE_GTIMER , .wId = ShortKey_GTimerwID , .wVscope = WIDGET_VS_PRIVATE},
 .timeOut=50,
 .enable = 1,                       
 .timeValue = 0,                    
 .timeoutEvent = GUI_NULL
};
#define Hours1_PicwID 0x1510
static const PICTUREBOX_INFO Hour1_Pic={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = Hours1_PicwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 35 , .y = 97, .width = 34 , .height = 46},    
 .picId = 18,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define Hours2_PicwID 0x1511 
static const PICTUREBOX_INFO Hour2_Pic={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = Hours2_PicwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 70 , .y = 97 , .width = 34 , .height = 46},    
 .picId = 18,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define Colon_PicwID 0x1512 //��
static const PICTUREBOX_INFO Colon_Pic={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = Colon_PicwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 105 , .y = 97 , .width = 34 , .height = 46},    
 .picId = 28,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define Minutes1_PicwID 0x1513 //
static const PICTUREBOX_INFO Minutes1_Pic={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = Minutes1_PicwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 140 , .y = 97 , .width = 34 , .height = 46},    
 .picId = 19,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define Minutes2_PicwID 0x1514 //
static const PICTUREBOX_INFO Minutes2_Pic={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = Minutes2_PicwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 175 , .y = 97 , .width = 34 , .height = 46},    
 .picId = 20,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define Char_PicwID 0x1515
static const PICTUREBOX_INFO Char_Pic={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = Char_PicwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 66 , .y = 50 , .width = 108 , .height = 43},    
 .picId = 8,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define Fire_PicwID 0x1516 
static const PICTUREBOX_INFO Fire_Pic={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = Fire_PicwID, .wVscope = WIDGET_VS_PRIVATE},
 {.x = 68 , .y = 152 , .width = 105 , .height = 35},    
 .picId = 14,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define FireGIF_PicwID 0x1517 
static const VIRTUALGIF_INFO FireGIF={
 {.wType = WIDGET_TYPE_VIRTUALGIF , .wId = FireGIF_PicwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 68 , .y = 152 , .width = 105 , .height = 35},    
 .startPicId = 14,
 .endPicId = 17,
 .playTime = 300,
 .enable=1,
 .replayEnable=1,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL ,
 .timeoutEvent = GUI_NULL ,
};
#define HourglassGIF_PicwID 0x1517 
static const VIRTUALGIF_INFO HourglassGIF={
 {.wType = WIDGET_TYPE_VIRTUALGIF , .wId = HourglassGIF_PicwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 96 , .y = 152 , .width = 48 , .height = 48},    
 .startPicId = 30,
 .endPicId = 33,
 .playTime = 300,
 .enable=1,
 .replayEnable=1,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL ,
 .timeoutEvent = GUI_NULL ,
};
gui_Err ShortKey_PageEnterEvent(gui_int32 argc , const char **argv);
static gui_Err ShortKey_timeoutEvent (gui_int32 argc , const char **argv);
gui_Err ShortKey_LeaveEvent(gui_int32 argc , const char **argv);

void Enter_ShortKey_Init(void);
/*******************************************************longkey page**********************************************************/
#define Long_Key_PwID 0x1507
static const PAGE_INFO Encoder_LongKey={
	{.wType = WIDGET_TYPE_PAGE , .wId = Long_Key_PwID , .wVscope = WIDGET_VS_PRIVATE},
	{.x = 0 , .y = 0 , .width = 240 , .height = 240},
	.backMode = WIDGET_BACKMODE_NULL , 
	.backColor = 0xFFFF,
	.picId = 34,
	.enterEvent = GUI_NULL,
	.leaveEvent = GUI_NULL,
	.pressEvent = GUI_NULL,
	.releaseEvent = GUI_NULL,
};

#define ARC_PicwID 0x1508 //
static const PICTUREBOX_INFO ARC_Pic={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = ARC_PicwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0 , .y = 0 , .width = 240 , .height = 240},    
 .picId = 34,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};

#define LongKey_GTimerwID 0x1509
static const GTIMER_INFO LongKey_GTimer={
 {.wType = WIDGET_TYPE_GTIMER , .wId = LongKey_GTimerwID , .wVscope = WIDGET_VS_PRIVATE},
 .timeOut =50,
 .enable = 1,                         
 .timeValue = 0,                     
 .timeoutEvent = GUI_NULL
};
#define Charge013wID 0x150C
static const VIRTUALGIF_INFO ChargeGIF={
 {.wType = WIDGET_TYPE_VIRTUALGIF , .wId = Charge013wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 12 , .y = 10 , .width = 215 , .height = 185},    
 .startPicId = 34,
 .endPicId = 49,
 .playTime = 50,
 .enable=1,
 .replayEnable=1,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL ,
 .timeoutEvent = GUI_NULL ,
};
#define MenuChar_PicwID 0x1518
static const PICTUREBOX_INFO MenuChar_Pic={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = MenuChar_PicwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 66 , .y = 172 , .width = 108 , .height = 43},    
 .picId = 58,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
gui_Err LongKey_LeaveEvent(gui_int32 argc , const char **argv);
static gui_Err LongKey_timeoutEvent (gui_int32 argc , const char **argv);
gui_Err LongKey_PageEnterEvent(gui_int32 argc , const char **argv);

void Enter_LongKey_Init(void);
#endif


