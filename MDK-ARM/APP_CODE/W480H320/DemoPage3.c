#include "app.h"
#include "guiFunc.h"
#include "stdio.h"
#include "string.h"

static gui_uint32 Luminance,ColorTemp;
/*********************************�ػ�����**********************************/
gui_Err LightTempPageEnterEvent(gui_int32 argc , const char **argv)
{
	guiCreateWidget((const void *)&LightTempPage);//�����ĵ�һ���ؼ�һ����page
	guiCreateWidget((const void *)&LightTempPageBackButton);
	guiCreateWidget((const void *)&LightTempPageSwitchButton);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , LTPSwitchButtonwID , LightPageTurnON_releaseEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , LTPBackButtonwID , LightTempPageBack_releaseEvent);
	return GUI_EOK;
}
gui_Err LightTempPageLeaveEvent(gui_int32 argc , const char **argv)
{

	return GUI_EOK;
}
static gui_Err LightPageTurnON_releaseEvent(gui_int32 argc , const char **argv)//���뿪������
{
	guiJumpPage(LPwID,LightPageLeaveEvent,LightPageEnterEvent);
	return GUI_EOK;
}
static gui_Err LightTempPageBack_releaseEvent(gui_int32 argc , const char **argv)//����������
{
	guiJumpPage(MPwID,MainPageLeaveEvent,MainPageEnterEvent);
	return GUI_EOK;
}
/*********************************��������**********************************/

extern gui_uint32 LCD_Luminance;
gui_Err LightPageEnterEvent(gui_int32 argc , const char **argv)
{
	guiCreateWidget((const void *)&LightPage);//�����ĵ�һ���ؼ�һ����page
	guiCreateWidget((const void *)&LightPageSwitchButton);
	guiCreateWidget((const void *)&LightPageSleepButton);
	guiCreateWidget((const void *)&LightPageEveButton);
	guiCreateWidget((const void *)&LightPageReadButton);
	guiCreateWidget((const void *)&LightPageOfficeButton);
	guiCreateWidget((const void *)&LightPageSunButton);
	guiCreateWidget((const void *)&LightPageBackButton);
	guiCreateWidget((const void *)&LightPageOptionBox1);
	guiCreateWidget((const void *)&LightPageOptionBox2);
	guiCreateWidget((const void *)&LightPageOptionBox3);
	guiCreateWidget((const void *)&LightPageTextBox1);
	guiCreateWidget((const void *)&LightPageTextBox2);
	guiCreateWidget((const void *)&LightPageTextBox3);
	guiCreateWidget((const void *)&LightPageSlider1);
	guiCreateWidget((const void *)&LightPageSlider2);
	guiCreateWidget((const void *)&LightPageNumberBox1);
	guiCreateWidget((const void *)&LightPageNumberBox2);
	guiCreateWidget((const void *)&LightPageNumberBoxA);
	guiCreateWidget((const void *)&LightPageNumberBoxB);
	guiCreateWidget((const void *)&LightPageNumberBoxC);
	guiCreateWidget((const void *)&LightPageNumberBoxD);		
	if(LCD_Luminance) {
		guiSetWidgetValue(LPSlider1wID, LCD_Luminance); //��ס�ϴ��˳�ʱ���õ�����
		guiSetWidgetValue(LPNumBox1wID, LCD_Luminance); //�����������ֿ�		
	}
	if(ColorTemp) {
		guiSetWidgetValue(LPSlider2wID, (ColorTemp-3000)/35); //����ɫ�»�����
		guiSetWidgetValue(LPNumBox2wID, ColorTemp); //����ɫ�����ֿ�
	}
	
	guiAppendWidgetText(LPTextBox1wID,6,"�͵���");
	guiAppendWidgetText(LPTextBox2wID,6,"������");
	guiAppendWidgetText(LPTextBox3wID,4,"̨��");

//	if(Luminance) guiSetWidgetValue(GPSlider1wID, Luminance); 
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , LPBackButtonwID , BackToHome_releaseEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_RELEASE , LPSwitchButtonwID , LightPageOFF_releaseEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_PRESS , LPSleepButtonwID , LightPageBinaryS_pressEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_PRESS , LPEveButtonwID , LightPageBinaryE_pressEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_PRESS , LPReadButtonwID , LightPageBinaryR_pressEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_PRESS , LPOfficeButtonwID , LightPageBinaryO_pressEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_PRESS , LPSunButtonwID , LightPageBinaryL_pressEvent);
	
	guiRegisterEvent(EVENT_REGISTER_TYPE_PRESS , LPOptionBox1wID , LightPageOption1_pressEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_PRESS , LPOptionBox2wID , LightPageOption2_pressEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_PRESS , LPOptionBox3wID , LightPageOption3_pressEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_UPDATE , LPSlider1wID , GetLuminance_slideEvent);
	guiRegisterEvent(EVENT_REGISTER_TYPE_UPDATE , LPSlider2wID , GetColorTemp_slideEvent);	
	return GUI_EOK;
}

gui_Err LightPageLeaveEvent(gui_int32 argc , const char **argv)
{

	return GUI_EOK;
}
//����������
static gui_Err BackToHome_releaseEvent(gui_int32 argc , const char **argv)
{
	guiJumpPage(MPwID,MainPageLeaveEvent,MainPageEnterEvent);
	return GUI_EOK;
}
//���عػ�����
static gui_Err LightPageOFF_releaseEvent(gui_int32 argc , const char **argv)
{
	guiJumpPage(LTPwID,LightTempPageLeaveEvent,LightTempPageEnterEvent);
	return GUI_EOK;
}
//�жϲ�ȷ�����ֻ��һ��ģʽ�����²�������Ӧ�Ļ���ֵ������
static gui_Err LightPageBinaryS_pressEvent(gui_int32 argc , const char **argv)//˯��ģʽ
{
	guiSetWidgetValue(LPEveButtonwID , 0);
	guiSetWidgetValue(LPReadButtonwID , 0);
	guiSetWidgetValue(LPOfficeButtonwID , 0);
	guiSetWidgetValue(LPSunButtonwID , 0);
	
	guiSetWidgetValue(LPSlider1wID , 10);
	guiSetWidgetValue(LPSlider2wID , 6);
	guiSetWidgetValue(LPNumBox1wID , 10);
	guiSetWidgetValue(LPNumBox2wID , 3200);
	return GUI_EOK;
}
static gui_Err LightPageBinaryE_pressEvent(gui_int32 argc , const char **argv)//ҹ��ģʽ
{
	guiSetWidgetValue(LPSleepButtonwID , 0);
	guiSetWidgetValue(LPReadButtonwID , 0);
	guiSetWidgetValue(LPOfficeButtonwID , 0);
	guiSetWidgetValue(LPSunButtonwID , 0);
	
	guiSetWidgetValue(LPSlider1wID , 30);
	guiSetWidgetValue(LPSlider2wID , 6);
	guiSetWidgetValue(LPNumBox1wID , 30);
	guiSetWidgetValue(LPNumBox2wID , 3200);	
	return GUI_EOK;
}
static gui_Err LightPageBinaryR_pressEvent(gui_int32 argc , const char **argv)//�Ķ�ģʽ
{
	guiSetWidgetValue(LPSleepButtonwID , 0);
	guiSetWidgetValue(LPEveButtonwID , 0);
	guiSetWidgetValue(LPOfficeButtonwID , 0);
	guiSetWidgetValue(LPSunButtonwID , 0);

	guiSetWidgetValue(LPSlider1wID , 70);
	guiSetWidgetValue(LPSlider2wID , 58);
	guiSetWidgetValue(LPNumBox1wID , 70);
	guiSetWidgetValue(LPNumBox2wID , 5000);
	return GUI_EOK;
}
static gui_Err LightPageBinaryO_pressEvent(gui_int32 argc , const char **argv)//�칫ģʽ
{ 
	guiSetWidgetValue(LPSleepButtonwID , 0);
	guiSetWidgetValue(LPEveButtonwID , 0);
	guiSetWidgetValue(LPReadButtonwID , 0);
	guiSetWidgetValue(LPSunButtonwID , 0);
	
	guiSetWidgetValue(LPSlider1wID , 50);
	guiSetWidgetValue(LPSlider2wID , 43);
	guiSetWidgetValue(LPNumBox1wID , 50);
	guiSetWidgetValue(LPNumBox2wID , 4500);	
	return GUI_EOK;
}
static gui_Err LightPageBinaryL_pressEvent(gui_int32 argc , const char **argv)//����ģʽ
{
	guiSetWidgetValue(LPSleepButtonwID , 0);
	guiSetWidgetValue(LPEveButtonwID , 0);
	guiSetWidgetValue(LPReadButtonwID , 0);
	guiSetWidgetValue(LPOfficeButtonwID , 0);
	
	guiSetWidgetValue(LPSlider1wID , 100);
	guiSetWidgetValue(LPSlider2wID , 100);
	guiSetWidgetValue(LPNumBox1wID , 100);
	guiSetWidgetValue(LPNumBox2wID , 6500);
	return GUI_EOK;
}
//�жϲ�ȷ�����ֻ��һ��ѡ���ѡ��
static gui_Err LightPageOption1_pressEvent(gui_int32 argc , const char **argv)//ѡ��͵���
{
	guiSetWidgetValue(LPOptionBox2wID , 0);
	guiSetWidgetValue(LPOptionBox3wID , 0);
	return GUI_EOK;
}
static gui_Err LightPageOption2_pressEvent(gui_int32 argc , const char **argv)//ѡ��������
{
	guiSetWidgetValue(LPOptionBox1wID , 0);
	guiSetWidgetValue(LPOptionBox3wID , 0);
	return GUI_EOK;
}
static gui_Err LightPageOption3_pressEvent(gui_int32 argc , const char **argv)//ѡ��̨��
{
	guiSetWidgetValue(LPOptionBox1wID , 0);
	guiSetWidgetValue(LPOptionBox2wID , 0);
	return GUI_EOK;
}
//��ȡ���Ȼ���ֵ���������ȿ�
static gui_Err GetLuminance_slideEvent(gui_int32 argc , const char **argv) 
{
	guiGetWidgetValue(LPSlider1wID, &LCD_Luminance);
	guiSetWidgetValue(LPNumBox1wID , LCD_Luminance);
	if(20<=LCD_Luminance&&LCD_Luminance<=100){			
		Lcd_Driver.SetDim((gui_uint16)LCD_Luminance);
	}
	else
		Lcd_Driver.SetDim(20);
	return GUI_EOK;
}
//��ȡɫ�»���ֵ������ɫ�¿�
static gui_Err GetColorTemp_slideEvent(gui_int32 argc , const char **argv)
{
	guiGetWidgetValue(LPSlider2wID, &ColorTemp);
	ColorTemp=35*ColorTemp+3000;
	guiSetWidgetValue(LPNumBox2wID , ColorTemp);
	return GUI_EOK;
}


