#ifndef _DemoPage4_h
#define _DemoPage4_h
#include "gWidgetInfo.h"
#include "gStdint.h"
#include "gReturn.h"
#include "gResMsg.h"

static gui_uint32 Bar_Val = 0;
static gui_uint8 pic1,pic2;

#define PPwID 0x4001
static const PAGE_INFO ProgressPage={
	{.wType = WIDGET_TYPE_PAGE , .wId = PPwID , .wVscope = WIDGET_VS_PRIVATE},
	{.x = 0 , .y = 0 , .width = 480 , .height = 320},
	.backMode = WIDGET_BACKMODE_PIC , 
	.backColor = 0x00FF,
	.picId = 3,
	.enterEvent = GUI_NULL,
	.leaveEvent = GUI_NULL,
	.pressEvent = GUI_NULL,
	.releaseEvent = GUI_NULL,
};
#define PPPic1wID 0x4002  //ʮλ��λ
static const PICTUREBOX_INFO  ProgressPagePicBox1={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = PPPic1wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 196 , .y = 50 , .width = 44 , .height = 35},    
 .picId = 53,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define PPPic2wID 0x4003  //��λ�ٷֺ�
static const PICTUREBOX_INFO  ProgressPagePicBox2={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = PPPic2wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 240 , .y = 50 , .width = 60 , .height = 35},    
 .picId = 63,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define PPBarwID 0x4004
static const PROGRESSBAR_INFO ProgressPageBar={
 {.wType = WIDGET_TYPE_PROGRESSBAR , .wId = PPBarwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 85 , .y = 138 , .width = 310 , .height = 45},    
 .backMode = WIDGET_BACKMODE_PIC, 
 .dir = PROGRESSBAR_DIR_H,                           
 .value = 0,
 .backPicId = 37,                     
 .frontPicId = 38,                   
 .backColor = 0xBDF7,
 .frontColor = 0x0400,              
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};
#define PPGTimerwID 0x4005
static const GTIMER_INFO ProgressPageGTimer={
 {.wType = WIDGET_TYPE_GTIMER , .wId = PPGTimerwID , .wVscope = WIDGET_VS_PRIVATE},
 .timeOut = 80,
 .enable = 1,                         //��ʱ������λ��0�أ�1��
 .timeValue = 0,                     //��ʱ����ǰ����ֵ��������1MS����16λ�ǵ�ǰ������ֵ����16λ�Ƕ�ʱ�������־������������ʶ
 .timeoutEvent = GUI_NULL
}; 
#define PPPicwID 0x4006  
static const PICTUREBOX_INFO  ProgressPagePicBox={
 {.wType = WIDGET_TYPE_PICTUREBOX , .wId = PPPicwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 203 , .y = 187 , .width = 75 , .height = 40},    
 .picId = 35,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL  
};

gui_Err ProgressPageEnterEvent(gui_int32 argc , const char **argv);
gui_Err ProgressPageLeaveEvent(gui_int32 argc , const char **argv);
static gui_Err PP_SetValue_timeoutEvent(gui_int32 argc , const char **argv);
static gui_Err BackToHome_releaseEvent(gui_int32 argc , const char **argv);

#endif
