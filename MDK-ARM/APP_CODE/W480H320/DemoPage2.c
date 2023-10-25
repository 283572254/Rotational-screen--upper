#include "app.h"
#include "guiFunc.h"
#include "stdio.h"
#include "string.h"
static gui_uint8 Mode,WindSpeed,Dir,pic1,pic2,Count,add;
static gui_uint16 picid;
static gui_uint32 Val1,Val2;
gui_Err ACPageEnterEvent(gui_int32 argc , const char **argv)
{
	guiCreateWidget((const void *)&ACPage);//创建的第一个控件一定是page
	guiCreateWidget((const void *)&ACMenuButton1);
	guiCreateWidget((const void *)&ACMenuButton2);
	guiCreateWidget((const void *)&ACMenuButton3);
	guiCreateWidget((const void *)&ACMenuButton4);
	guiCreateWidget((const void *)&ACMenuButton5);
	guiCreateWidget((const void *)&ACPageNumBox1);
	guiCreateWidget((const void *)&ACPageNumBox2);
//	guiCreateWidget((const void *)&ACPageTextBox3);
	guiCreateWidget((const void *)&ACPBackButton);
	guiCreateWidget((const void *)&ACPModeButton);
	guiCreateWidget((const void *)&ACPWindButton);
	guiCreateWidget((const void *)&ACPWindButtonDIR);
	guiCreateWidget((const void *)&ACPageOptionBox1);
	guiCreateWidget((const void *)&ACPageOptionBox2);	
	guiCreateWidget((const void *)&ACPageModePIC);		
	guiCreateWidget((const void *)&ACPageWindDIR1PIC);	
	guiCreateWidget((const void *)&ACPageWindDIR2PIC);	
	guiCreateWidget((const void *)&ACPageWindSpeedPIC);	
	guiCreateWidget((const void *)&ACPTemp1PIC);	
	guiCreateWidget((const void *)&ACPTemp2PIC);
	guiCreateWidget((const void *)&ACPageGTimer);	

	guiAppendWidgetText(ACPModeButtonwID,4,"模式");
	guiAppendWidgetText(ACPWindButtonDIRwID,4,"风向");
	guiAppendWidgetText(ACPWindButtonwID,4,"风力");
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , ACPBackButtonwID , BackToHome_releaseEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_PRESS , ACPOptionBox1wID , ACPageOption1_pressEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_PRESS , ACPOptionBox2wID , ACPageOption2_pressEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , ACPModeButtonwID , ACPageSetMode_releaseEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , ACPWindButtonwID , ACPageSetWindSpeed_releaseEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , ACPWindButtonDIRwID , ACPageSetWindDir_releaseEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_TIMEOUT , ACPGTimerwID , ACPageTemp_timeoutEvent);
	
	Count=0;
	return GUI_EOK;
}
gui_Err ACPageLeaveEvent(gui_int32 argc , const char **argv)
{
	
	return GUI_EOK;
}

//返回主界面
static gui_Err BackToHome_releaseEvent(gui_int32 argc , const char **argv)
{
	guiJumpPage(MPwID,MainPageLeaveEvent,MainPageEnterEvent);
	return GUI_EOK;
}
//判断并确保最多只有一个选项框被选择
static gui_Err ACPageOption1_pressEvent(gui_int32 argc , const char **argv)
{
	guiSetWidgetValue(ACPOptionBox2wID , 0);
	return GUI_EOK;
}
static gui_Err ACPageOption2_pressEvent(gui_int32 argc , const char **argv)
{
  guiSetWidgetValue(ACPOptionBox1wID , 0);
	return GUI_EOK;
}
//设置模式
static gui_Err ACPageSetMode_releaseEvent(gui_int32 argc , const char **argv)
{
  switch(Mode)
	{
		case 0:{guiSetWidgetPictureID(ACPModePICwID  , 15);guiGetWidgetPictureID(ACPModePICwID  , &picid);Mode=1;printf("ModePIC_ID:%d\r\n",picid);break;}
		case 1:{guiSetWidgetPictureID(ACPModePICwID  , 16);guiGetWidgetPictureID(ACPModePICwID  , &picid);Mode=2;printf("ModePIC_ID:%d\r\n",picid);break;}
		case 2:{guiSetWidgetPictureID(ACPModePICwID  , 17);guiGetWidgetPictureID(ACPModePICwID  , &picid);Mode=3;printf("ModePIC_ID:%d\r\n",picid);break;}
		case 3:{guiSetWidgetPictureID(ACPModePICwID  , 14);guiGetWidgetPictureID(ACPModePICwID  , &picid);Mode=0;printf("ModePIC_ID:%d\r\n",picid);break;}
		default:break;
	}
	return GUI_EOK;
}
//设置风速
static gui_Err ACPageSetWindSpeed_releaseEvent(gui_int32 argc , const char **argv)
{
  switch(WindSpeed)
	{
		case 0:{guiSetWidgetPictureID(ACPWSPICwID  , 41);guiGetWidgetPictureID(ACPWSPICwID  , &picid);WindSpeed=1;printf("ModePIC_ID:%d\r\n",picid);break;}
		case 1:{guiSetWidgetPictureID(ACPWSPICwID  , 42);guiGetWidgetPictureID(ACPWSPICwID  , &picid);WindSpeed=2;printf("ModePIC_ID:%d\r\n",picid);break;}
		case 2:{guiSetWidgetPictureID(ACPWSPICwID  , 43);guiGetWidgetPictureID(ACPWSPICwID  , &picid);WindSpeed=3;printf("ModePIC_ID:%d\r\n",picid);break;}
		case 3:{guiSetWidgetPictureID(ACPWSPICwID  , 40);guiGetWidgetPictureID(ACPWSPICwID  , &picid);WindSpeed=0;printf("ModePIC_ID:%d\r\n",picid);break;}
		default:break;
	}
	return GUI_EOK;
}
//设置风向
static gui_Err ACPageSetWindDir_releaseEvent(gui_int32 argc , const char **argv)
{
  guiGetWidgetValue(ACPOptionBox1wID , &Val1);
	guiGetWidgetValue(ACPOptionBox2wID , &Val2);
	if(Val1)
	{
		switch(Dir)
		{
			case 0:{guiSetWidgetPictureID(ACPWindDIR2PICwID  , 48);guiGetWidgetPictureID(ACPWindDIR2PICwID  , &picid);Dir=1;printf("ModePIC_ID:%d\r\n",picid);break;}
			case 1:{guiSetWidgetPictureID(ACPWindDIR2PICwID  , 49);guiGetWidgetPictureID(ACPWindDIR2PICwID  , &picid);Dir=2;printf("ModePIC_ID:%d\r\n",picid);break;}
			case 2:{guiSetWidgetPictureID(ACPWindDIR2PICwID  , 50);guiGetWidgetPictureID(ACPWindDIR2PICwID  , &picid);Dir=3;printf("ModePIC_ID:%d\r\n",picid);break;}
			case 3:{guiSetWidgetPictureID(ACPWindDIR2PICwID  , 51);guiGetWidgetPictureID(ACPWindDIR2PICwID  , &picid);Dir=0;printf("ModePIC_ID:%d\r\n",picid);break;}
			default:break;
		}	
	}
	if(Val2)
	{
		switch(Dir)
		{
			case 0:{guiSetWidgetPictureID(ACPWindDIR1PICwID  , 44);guiGetWidgetPictureID(ACPWindDIR1PICwID  , &picid);Dir=1;printf("ModePIC_ID:%d\r\n",picid);break;}
			case 1:{guiSetWidgetPictureID(ACPWindDIR1PICwID  , 45);guiGetWidgetPictureID(ACPWindDIR1PICwID  , &picid);Dir=2;printf("ModePIC_ID:%d\r\n",picid);break;}
			case 2:{guiSetWidgetPictureID(ACPWindDIR1PICwID  , 46);guiGetWidgetPictureID(ACPWindDIR1PICwID  , &picid);Dir=3;printf("ModePIC_ID:%d\r\n",picid);break;}
			case 3:{guiSetWidgetPictureID(ACPWindDIR1PICwID  , 47);guiGetWidgetPictureID(ACPWindDIR1PICwID  , &picid);Dir=0;printf("ModePIC_ID:%d\r\n",picid);break;}
			default:break;
		}	
	}
	return GUI_EOK;
}
//温度切换
static gui_Err ACPageTemp_timeoutEvent(gui_int32 argc , const char **argv)
{
	if(Count==100) add=0;
	if(Count==0)	add=1;
	if(add)		Count+=1;	
	else		Count-=1;	
	pic1=Count/10;
	pic2=Count%10;
	switch(pic1)//十位
	{
		case 0:{guiSetWidgetPictureID(ACPTemp2PICwID , 85);break;}
		case 1:{guiSetWidgetPictureID(ACPTemp2PICwID , 86);break;}
		case 2:{guiSetWidgetPictureID(ACPTemp2PICwID , 87);break;}
		case 3:{guiSetWidgetPictureID(ACPTemp2PICwID , 88);break;}
		case 4:{guiSetWidgetPictureID(ACPTemp2PICwID , 89);break;}
		case 5:{guiSetWidgetPictureID(ACPTemp2PICwID , 90);break;}
		case 6:{guiSetWidgetPictureID(ACPTemp2PICwID , 91);break;}
		case 7:{guiSetWidgetPictureID(ACPTemp2PICwID , 92);break;}
		case 8:{guiSetWidgetPictureID(ACPTemp2PICwID , 93);break;}
		case 9:{guiSetWidgetPictureID(ACPTemp2PICwID , 94);break;}
		default:break;
	}
	switch(pic2)//个位
	{
		case 0:{guiSetWidgetPictureID(ACPTemp1PICwID , 75);break;}
		case 1:{guiSetWidgetPictureID(ACPTemp1PICwID , 76);break;}
		case 2:{guiSetWidgetPictureID(ACPTemp1PICwID , 77);break;}
		case 3:{guiSetWidgetPictureID(ACPTemp1PICwID , 78);break;}
		case 4:{guiSetWidgetPictureID(ACPTemp1PICwID , 79);break;}
		case 5:{guiSetWidgetPictureID(ACPTemp1PICwID , 80);break;}
		case 6:{guiSetWidgetPictureID(ACPTemp1PICwID , 81);break;}
		case 7:{guiSetWidgetPictureID(ACPTemp1PICwID , 82);break;}
		case 8:{guiSetWidgetPictureID(ACPTemp1PICwID , 83);break;}
		case 9:{guiSetWidgetPictureID(ACPTemp1PICwID , 84);break;}
		default:break;
	}
	return GUI_EOK;
}


