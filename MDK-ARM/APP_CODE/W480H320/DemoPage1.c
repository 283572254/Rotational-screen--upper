#include "app.h"
#include "guiFunc.h"
#include "stdio.h"
#include "string.h"
static gui_uint8 Mode=0;
static gui_uint8 Flash=1;
static gui_uint8 flash_pic;
static gui_uint32 Val1,Val2,Val3;
static const char FP_text[] = "请设置:";
static const char FP_text2[] = "       ";
gui_Err FridgePageEnterEvent(gui_int32 argc , const char **argv)
{
	guiCreateWidget((const void *)&FridgePage);//创建的第一个控件一定是page
	guiCreateWidget((const void *)&FridgePageNumberBox1);//生鲜区温度
	guiCreateWidget((const void *)&FridgePageNumberBox2);//软冻区温度
    guiCreateWidget((const void *)&FridgePageNumberBox3);//冷冻区温度
	guiCreateWidget((const void *)&FridgePageSetButton);//设置
	guiCreateWidget((const void *)&FridgePageNewsButton);//资讯
	guiCreateWidget((const void *)&FridgePageMsgButton);//留言板
    guiCreateWidget((const void *)&FridgePageDateButton);//日历
	guiCreateWidget((const void *)&FridgePageMenuButton);//食谱大全
	guiCreateWidget((const void *)&FridgePageModeButton);//模式按钮
	guiCreateWidget((const void *)&FridgePageTextBox);//模式
	guiCreateWidget((const void *)&FridgePageTextBox2);//定位天气
	guiCreateWidget((const void *)&FridgePageGTimer);//定时器
	guiCreateWidget((const void *)&FridgePageOptionBox1);//生鲜选项框
	guiCreateWidget((const void *)&FridgePageOptionBox2);//软冻选项框
	guiCreateWidget((const void *)&FridgePageOptionBox3);//冷冻选项框
	guiCreateWidget((const void *)&FridgePageBackButton);//返回主界面按钮
	guiCreateWidget((const void *)&FridgePageTextBox3);//闪烁文本
	guiCreateWidget((const void *)&FridgePageTextBoxA);//生鲜室
	guiCreateWidget((const void *)&FridgePageTextBoxB);//软冻室
	guiCreateWidget((const void *)&FridgePageTextBoxC);//冷冻室
	guiCreateWidget((const void *)&FridgePagePicBox1);//生鲜室图
	guiCreateWidget((const void *)&FridgePagePicBox2);//软冻室图
	guiCreateWidget((const void *)&FridgePagePicBox3);//冷冻室图
	guiAppendWidgetText(FPTextBoxwID,4,"智能");	Mode=1;
	guiAppendWidgetText(FPTextBox2wID,15,"上海市 晴\n20℃");
	guiAppendWidgetText(FPTextBoxAwID,6,"生鲜室");
	guiAppendWidgetText(FPTextBoxBwID,6,"软冻室");
	guiAppendWidgetText(FPTextBoxCwID,6,"冷冻室");
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , FPBackButtonwID , BackToHome_releaseEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , FPModeButtonwID , FridgePageMode_releaseEvent);
//	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , FPMsgButtonwID , ButtonPageButton2_releaseEvent);
//	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , FPDateButtonwID , ButtonPageButton3_releaseEvent);
//	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , FPMenuButtonwID , ButtonPageButton4_releaseEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_TIMEOUT , FPGTimerwID , FridgePage_TimeOutEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_PRESS , FPOptionBox1wID , FridgePageOption1_pressEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , FPOptionBox1wID ,  FridgePageFlash_releaseEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_PRESS , FPOptionBox2wID , FridgePageOption2_pressEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , FPOptionBox2wID ,  FridgePageFlash_releaseEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_PRESS , FPOptionBox3wID , FridgePageOption3_pressEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , FPOptionBox3wID ,  FridgePageFlash_releaseEvent);
	return GUI_EOK;
}
gui_Err FridgePageLeaveEvent(gui_int32 argc , const char **argv)
{
	
	return GUI_EOK;
}
//设置模式
static gui_Err FridgePageMode_releaseEvent(gui_int32 argc , const char **argv)
{
	const char Mode_Text1[] = "智能";
	const char Mode_Text2[] = "珍品";
	const char Mode_Text3[] = "速冻";
	switch(Mode)
	{
    case 0:{guiSetWidgetText(FPTextBoxwID,strlen(Mode_Text1),Mode_Text1);Mode=1;break;}
    case 1:{guiSetWidgetText(FPTextBoxwID,strlen(Mode_Text2),Mode_Text2);Mode=2;break;}
    case 2:{guiSetWidgetText(FPTextBoxwID,strlen(Mode_Text3),Mode_Text3);Mode=0;break;}
		default:break;
	}
	return GUI_EOK;
}
//返回主界面
static gui_Err BackToHome_releaseEvent(gui_int32 argc , const char **argv)
{
	guiJumpPage(MPwID,MainPageLeaveEvent,MainPageEnterEvent);
	return GUI_EOK;
}
//当所有选项框取消选择时关闭定时器
static gui_Err FridgePageFlash_releaseEvent(gui_int32 argc , const char **argv)
{
	guiGetWidgetValue(FPOptionBox1wID , &Val1);
	guiGetWidgetValue(FPOptionBox2wID , &Val2);
	guiGetWidgetValue(FPOptionBox3wID , &Val3);
	if(Val1==0&&Val2==0&&Val3==0)
	{
		guiSetWidgetEnable(FPGTimerwID,0);
		guiSetWidgetText(FPTextBox3wID,strlen(FP_text2),FP_text2);
		printf("SetDisable ok\r\n");	
	}
	guiSetWidgetPictureID(FPPicBox1wID,95);
	guiSetWidgetPictureID(FPPicBox2wID,97);
	guiSetWidgetPictureID(FPPicBox3wID,99);
	return GUI_EOK;
}
//闪烁效果
static gui_Err FridgePage_TimeOutEvent(gui_int32 argc , const char **argv)
{
	Flash=!Flash;
	if(Flash)	guiSetWidgetText(FPTextBox3wID,strlen(FP_text),FP_text); 
	else	guiSetWidgetText(FPTextBox3wID,strlen(FP_text2),FP_text2);	
	switch (flash_pic)
	{
		case 1:{if(Flash) guiSetWidgetPictureID(FPPicBox1wID,95);else guiSetWidgetPictureID(FPPicBox1wID,96);} break;
		case 2:{if(Flash) guiSetWidgetPictureID(FPPicBox2wID,97);else guiSetWidgetPictureID(FPPicBox2wID,98);} break;
		case 3:{if(Flash) guiSetWidgetPictureID(FPPicBox3wID,99);else guiSetWidgetPictureID(FPPicBox3wID,100);} break;	
		default: break;
	}
	return GUI_EOK;
}
//判断并确保最多只有一个选项框被选择并开启定时器实现闪烁
static gui_Err FridgePageOption1_pressEvent(gui_int32 argc , const char **argv)
{
	guiSetWidgetValue(FPOptionBox2wID , 0);
	guiSetWidgetValue(FPOptionBox3wID , 0);
	guiSetWidgetEnable(FPGTimerwID,1);
	flash_pic=1;
	return GUI_EOK;
}
static gui_Err FridgePageOption2_pressEvent(gui_int32 argc , const char **argv)
{
	guiSetWidgetValue(FPOptionBox1wID , 0);
	guiSetWidgetValue(FPOptionBox3wID , 0);
	guiSetWidgetEnable(FPGTimerwID,1);	
	flash_pic=2;
	return GUI_EOK;
}
static gui_Err FridgePageOption3_pressEvent(gui_int32 argc , const char **argv)
{
	guiSetWidgetValue(FPOptionBox1wID , 0);
	guiSetWidgetValue(FPOptionBox2wID , 0);
	guiSetWidgetEnable(FPGTimerwID,1);	
	flash_pic=3;
	return GUI_EOK;
}
