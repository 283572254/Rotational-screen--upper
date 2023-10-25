/**
  ******************************************************************************
  * @file bsp_i2c_ee.c
  * @author STMicroelectronics
  * @version V1.0
  * @date 2015-xx-xx
  * @brief Dedicated iic driver for capacitive touchscreens Software emulation IIC
  ******************************************************************************
  */ 
  #include "i2c_touch.h"
#include "stdint.h"
#include "Y6.h"
#include "Y6_rcc.h"
#include "lcdDriver.h"
#include "Y6_gpio.h"
#include "Y6_qspi.h"
#include "QspiDMA.h"
#include "Y6_tim.h"
#include "Y6_include_conf.h"
#include "pwm.h"


/* STM32 I2C ����ģʽ */
#define I2C_Speed              400000

/* �����ַֻҪ��STM32��ҵ�I2C������ַ��һ������ */
#define I2C_OWN_ADDRESS7      0x0A



static void Delay( uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}


/**
  * @brief  ʹ�ܴ������ж�
  * @param  ��
  * @retval ��
  */



 
int FT6236_RD_Reg(unsigned short int reg,unsigned char *buf,unsigned char len)
{     
	int32_t ret=-1;
	uint8_t regBuf[2] = {reg >> 8, reg & 0xff};    //�Ĵ�����ַ
	
	ret = I2C_WriteBytes(0x2a,  regBuf, 2);	//IICд������
	if(ret) //��ʧ��
		return -1;
	
	ret = I2C_ReadBytes(0x2a, buf, len);		//IIC��ȡ����
	if(ret) //��ʧ��
		return -1;
	else{
		return 0;
	}
	
//// 	if(I2C_DmaRead(FT_CMD_RD >> 1, (unsigned int)reg, 2, buf, len)<0){
//// 	if(I2C_DmaRead(FT_CMD_RD, (unsigned int)reg, 2, buf, len)<0){
// 	if(I2C_ReadBytes(FT_CMD_RD >> 1, (unsigned int)reg, 2, buf, len)<0){
//	 	printf("i2c get TP data fail!");
//		return -1;//read failed
//	}
//	else{
//	 	printf("I2C get OK !");
//		return 0;
//	}
}

/**
  * @brief  ������ I/O����
  * @param  ��
  * @retval ��
  */
static void I2C_GPIO_Config(void)
{

 
 //ʹ�����IIC
    /*����SCL���� */   
     GPIO_SetPinMux(GPIO1, GPIO_Pin_28, GPIO_FUNCTION_0);  /*SDA*/
	 GPIO_SetPinDir(GPIO1, GPIO_Pin_28,GPIO_Mode_OUT);  //SDA
	
    GPIO_SetPinMux(GPIO1, GPIO_Pin_29, GPIO_FUNCTION_0);  /*SCL*/
	GPIO_SetPinDir(GPIO1, GPIO_Pin_29,GPIO_Mode_OUT);  //SCL

		/*����RST���ţ�������� */   

}




///**
//  * @brief  I2C ����ģʽ����
//  * @param  ��
//  * @retval ��
//  */
//static void I2C_Mode_Config(void)
//{
//  I2C_InitTypeDef  I2C_InitStructure; 

//  /* I2C ģʽ���� */
//  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;	
//  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;		                    
//  I2C_InitStructure.I2C_OwnAddress1 =I2C_OWN_ADDRESS7;
//  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;	
//  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;	/* I2C��Ѱַģʽ */
//  I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;	                          /* ͨ������ */
//  I2C_Init(GTP_I2C, &I2C_InitStructure);	                                  /* I2C1 ��ʼ�� */
//  I2C_Cmd(GTP_I2C, ENABLE);  	                                              /* ʹ�� I2C1 */

//  I2C_AcknowledgeConfig(GTP_I2C, ENABLE);

//}

/*************************************************
  Function:       ��i2c����������Ϊ��������ģʽ
  Description:    ��ʼ��i2c��������
  Calls:          GPIO_Init();
  Called By:      i2c_WaitAck();
                  i2c_ReadByte();
  Input:          ��
  Output:         ��
  Return:         ��
*************************************************/
void SDA_In(void)
{

	 GPIO_SetPinDir(GPIO1, GPIO_Pin_28,GPIO_Mode_IN);  //SDA
	
}

/*************************************************
  Function:       ��i2c��DATA��������Ϊ�������ģʽ
  Description:    ��ʼ��i2c��������
  Calls:          GPIO_Init();
  Called By:      i2c_Start();
                  i2c_Stop();
				  i2c_SendByte();
				  i2c_Ack();
				  i2c_NAck();
  Input:          ��
  Output:         ��
  Return:         ��
*************************************************/
void SDA_Out(void)
{
		 GPIO_SetPinDir(GPIO1, GPIO_Pin_28,GPIO_Mode_OUT);  //SDA

}


/**
  * @brief  I2C ����(GT1xx)��ʼ��
  * @param  ��
  * @retval ��
  */
void I2C_Touch_Init(void)
{
					
  I2C_GPIO_Config(); 

//	I2C_GTP_IRQEnable(); //ʹ���ж�
//	I2C_GTP_IRQDisable(); //�ر��ж�

}


/*
*********************************************************************************************************
*	�� �� ��: i2c_Delay
*	����˵��: I2C����λ�ӳ٣����400KHz
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void i2c_Delay(void)
{
	uint16_t i;

	/*��
	 	�����ʱ����ͨ���߼������ǲ��Եõ��ġ�
    ����������CPU��Ƶ72MHz ��MDK���뻷����1���Ż�
      
		ѭ������Ϊ5ʱ��Լ��ʱ5.3us 
		ѭ������Ϊ10ʱ��Լ��ʱ8.6~8.8 us ��  
		ѭ������Ϊ100ʱ��Լ��ʱ71.6~71.8 us ��  
  */
	for (i = 0; i < 50; i++);
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_Start
*	����˵��: CPU����I2C���������ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_Start(void)
{
	SDA_Out();    //���ó��������
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C���������ź� */
	I2C_SDA_1();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SDA_0();
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_Start
*	����˵��: CPU����I2C����ֹͣ�ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_Stop(void)
{
	SDA_Out();    //���ó��������
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź� */
	I2C_SDA_0();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SDA_1();
	i2c_Delay();
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_SendByte
*	����˵��: CPU��I2C�����豸����8bit����
*	��    �Σ�_ucByte �� �ȴ����͵��ֽ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_SendByte(uint8_t _ucByte)
{
	uint8_t i;

	SDA_Out();    //���ó��������
	/* �ȷ����ֽڵĸ�λbit7 */
	for (i = 0; i < 8; i++)
	{		
		if (_ucByte & 0x80)
		{
			I2C_SDA_1();
		}
		else
		{
			I2C_SDA_0();
		}
		i2c_Delay();
		_ucByte <<= 1;	/* ����һ��bit */
		I2C_SCL_1();
		i2c_Delay();	
		I2C_SCL_0();
		if (i == 7)
		{
//			 I2C_SDA_1(); // �ͷ�����
			SDA_In();	/* SDA����Ϊ�������� */
		}
		i2c_Delay();
	}
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_ReadByte
*	����˵��: CPU��I2C�����豸��ȡ8bit����
*	��    �Σ���
*	�� �� ֵ: ����������
*********************************************************************************************************
*/
uint8_t i2c_ReadByte(void)
{
	uint8_t i;
	uint8_t value;

	SDA_In();	/* SDA����Ϊ�������� */
	
	/* ������1��bitΪ���ݵ�bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		I2C_SCL_1();
		i2c_Delay();
		value <<= 1;
		if (I2C_SDA_READ())
		{
			value++;
		}
		I2C_SCL_0();
		i2c_Delay();
	}
	return value;
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_WaitAck
*	����˵��: CPU����һ��ʱ�ӣ�����ȡ������ACKӦ���ź�
*	��    �Σ���
*	�� �� ֵ: ����0��ʾ��ȷӦ��1��ʾ��������Ӧ
*********************************************************************************************************
*/
uint8_t i2c_WaitAck(void)
{
	uint8_t re, i;
I2C_SDA_1();
	SDA_In();	/* SDA����Ϊ�������� */
	i2c_Delay();
	I2C_SCL_1();	/* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
	i2c_Delay();
//	while (I2C_SDA_READ() != 0);	/* CPU��ȡSDA����״̬ */
//		re = 0;
	i = 5;
	while (i){	/* CPU��ȡSDA����״̬ */
		if (I2C_SDA_READ())
		{
			i--;
			re = 1;
		}
		else
		{
			re = 0;
			break;
		}
	}
	I2C_SCL_0();
	i2c_Delay();
	return re;
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_Ack
*	����˵��: CPU����һ��ACK�ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_Ack(void)
{
	SDA_Out();    //���ó��������
	
	I2C_SDA_0();	/* CPU����SDA = 0 */
	i2c_Delay();
	I2C_SCL_1();	/* CPU����1��ʱ�� */
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
	I2C_SDA_1();	/* CPU�ͷ�SDA���� */
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_NAck
*	����˵��: CPU����1��NACK�ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_NAck(void)
{
	SDA_Out();    //���ó��������
	I2C_SDA_1();	/* CPU����SDA = 1 */
	i2c_Delay();
	I2C_SCL_1();	/* CPU����1��ʱ�� */
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();	
}



#define I2C_DIR_WR	0		/* д����bit */
#define I2C_DIR_RD	1		/* ������bit */

/**
  * @brief   ʹ��IIC��ȡ����
  * @param   
  * 	@arg ClientAddr:���豸��ַ
  *		@arg pBuffer:����ɴӻ���ȡ�����ݵĻ�����ָ��
  *		@arg NumByteToRead:��ȡ�����ݳ���
  * @retval  ��
  */
uint32_t I2C_ReadBytes(uint8_t ClientAddr,uint8_t* pBuffer, uint16_t NumByteToRead)
{
	
	/* ��1��������I2C���������ź� */
	i2c_Start();
	
	/* ��2������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
	i2c_SendByte(ClientAddr | I2C_DIR_RD);	/* �˴��Ƕ�ָ�� */
	
	/* ��3�����ȴ�ACK */
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* ������Ӧ�� */
	}

	while(NumByteToRead) 
  {
    
   *pBuffer = i2c_ReadByte();
    
   if(NumByteToRead == 1)
    {
			i2c_NAck();	/* ���1���ֽڶ����CPU����NACK�ź�(����SDA = 1) */
      
      break;
    }
    /* ��ָ������ */
    pBuffer++; 
      
    /*�������Լ� */
    NumByteToRead--;
    
    i2c_Ack();	/* �м��ֽڶ����CPU����ACK�ź�(����SDA = 0) */  
  }

	/* ����I2C����ֹͣ�ź� */
	i2c_Stop();
	return 0;	/* ִ�гɹ� */

cmd_fail: /* ����ִ��ʧ�ܺ��мǷ���ֹͣ�źţ�����Ӱ��I2C�����������豸 */
	/* ����I2C����ֹͣ�ź� */
	i2c_Stop();
	return 1;
}

/**
  * @brief   ʹ��IICд������
  * @param   
  * 	@arg ClientAddr:���豸��ַ
  *		@arg pBuffer:������ָ��
  *     @arg NumByteToWrite:д���ֽ���
  * @retval  ��
  */
uint32_t I2C_WriteBytes(uint8_t ClientAddr,uint8_t* pBuffer,  uint8_t NumByteToWrite)
{
	uint16_t m;	

  /*����0������ֹͣ�źţ������ڲ�д������*/
  i2c_Stop();
  
  /* ͨ���������Ӧ��ķ�ʽ���ж��ڲ�д�����Ƿ����, һ��С�� 10ms 			
    CLKƵ��Ϊ200KHzʱ����ѯ����Ϊ30������
  */
  for (m = 0; m < 1000; m++)
  {				
    /* ��1��������I2C���������ź� */
    i2c_Start();
    
    /* ��2������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
    i2c_SendByte(ClientAddr | I2C_DIR_WR);	/* �˴���дָ�� */
    
    /* ��3��������һ��ʱ�ӣ��ж������Ƿ���ȷӦ�� */
    if (i2c_WaitAck() == 0)
    {
      break;
    }
  }
  if (m  == 1000)
  {
    goto cmd_fail;	/* EEPROM����д��ʱ */
  }	
	
  while(NumByteToWrite--)
  {
  /* ��4������ʼд������ */
  i2c_SendByte(*pBuffer);

  /* ��5�������ACK */
  if (i2c_WaitAck() != 0)
  {
    goto cmd_fail;	/* ������Ӧ�� */
  }
  
      pBuffer++;	/* ��ַ��1 */		
  }
	
	/* ����ִ�гɹ�������I2C����ֹͣ�ź� */
	i2c_Stop();
	return 0;

cmd_fail: /* ����ִ��ʧ�ܺ��мǷ���ֹͣ�źţ�����Ӱ��I2C�����������豸 */
	/* ����I2C����ֹͣ�ź� */
	i2c_Stop();
	return 1;
}



/*********************************************END OF FILE**********************/


