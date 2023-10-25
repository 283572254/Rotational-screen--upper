#include "app.h"
#include "guiFunc.h"
#include "stdio.h"
#include "string.h"
static gui_uint8 Mode=0;
static gui_uint8 Flash=1;
static gui_uint8 flash_pic;
static gui_uint32 Val1,Val2,Val3;
static const char FP_text[] = "������:";
static const char FP_text2[] = "       ";
gui_Err FridgePageEnterEvent(gui_int32 argc , const char **argv)
{
	guiCreateWidget((const void *)&FridgePage);//�����ĵ�һ���ؼ�һ����page
	guiCreateWidget((const void *)&FridgePageNumberBox1);//�������¶�
	guiCreateWidget((const void *)&FridgePageNumberBox2);//�����¶�
    guiCreateWidget((const void *)&FridgePageNumberBox3);//�䶳���¶�
	guiCreateWidget((const void *)&FridgePageSetButton);//����
	guiCreateWidget((const void *)&FridgePageNewsButton);//��Ѷ
	guiCreateWidget((const void *)&FridgePageMsgButton);//���԰�
    guiCreateWidget((const void *)&FridgePageDateButton);//����
	guiCreateWidget((const void *)&FridgePageMenuButton);//ʳ�״�ȫ
	guiCreateWidget((const void *)&FridgePageModeButton);//ģʽ��ť
	guiCreateWidget((const void *)&FridgePageTextBox);//ģʽ
	guiCreateWidget((const void *)&FridgePageTextBox2);//��λ����
	guiCreateWidget((const void *)&FridgePageGTimer);//��ʱ��
	guiCreateWidget((const void *)&FridgePageOptionBox1);//����ѡ���
	guiCreateWidget((const void *)&FridgePageOptionBox2);//��ѡ���
	guiCreateWidget((const void *)&FridgePageOptionBox3);//�䶳ѡ���
	guiCreateWidget((const void *)&FridgePageBackButton);//���������水ť
	guiCreateWidget((const void *)&FridgePageTextBox3);//��˸�ı�
	guiCreateWidget((const void *)&FridgePageTextBoxA);//������
	guiCreateWidget((const void *)&FridgePageTextBoxB);//����
	guiCreateWidget((const void *)&FridgePageTextBoxC);//�䶳��
	guiCreateWidget((const void *)&FridgePagePicBox1);//������ͼ
	guiCreateWidget((const void *)&FridgePagePicBox2);//����ͼ
	guiCreateWidget((const void *)&FridgePagePicBox3);//�䶳��ͼ
	guiAppendWidgetText(FPTextBoxwID,4,"����");	Mode=1;
	guiAppendWidgetText(FPTextBox2wID,15,"�Ϻ��� ��\n20��");
	guiAppendWidgetText(FPTextBoxAwID,6,"������");
	guiAppendWidgetText(FPTextBoxBwID,6,"����");
	guiAppendWidgetText(FPTextBoxCwID,6,"�䶳��");
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
//����ģʽ
static gui_Err FridgePageMode_releaseEvent(gui_int32 argc , const char **argv)
{
	const char Mode_Text1[] = "����";
	const char Mode_Text2[] = "��Ʒ";
	const char Mode_Text3[] = "�ٶ�";
	switch(Mode)
	{
    case 0:{guiSetWidgetText(FPTextBoxwID,strlen(Mode_Text1),Mode_Text1);Mode=1;break;}
    case 1:{guiSetWidgetText(FPTextBoxwID,strlen(Mode_Text2),Mode_Text2);Mode=2;break;}
    case 2:{guiSetWidgetText(FPTextBoxwID,strlen(Mode_Text3),Mode_Text3);Mode=0;break;}
		default:break;
	}
	return GUI_EOK;
}
//����������
static gui_Err BackToHome_releaseEvent(gui_int32 argc , const char **argv)
{
	guiJumpPage(MPwID,MainPageLeaveEvent,MainPageEnterEvent);
	return GUI_EOK;
}
//������ѡ���ȡ��ѡ��ʱ�رն�ʱ��
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
//��˸Ч��
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
//�жϲ�ȷ�����ֻ��һ��ѡ���ѡ�񲢿�����ʱ��ʵ����˸
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
