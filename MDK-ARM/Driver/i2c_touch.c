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


/* STM32 I2C 快速模式 */
#define I2C_Speed              400000

/* 这个地址只要与STM32外挂的I2C器件地址不一样即可 */
#define I2C_OWN_ADDRESS7      0x0A



static void Delay( uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}


/**
  * @brief  使能触摸屏中断
  * @param  无
  * @retval 无
  */



 
int FT6236_RD_Reg(unsigned short int reg,unsigned char *buf,unsigned char len)
{     
	int32_t ret=-1;
	uint8_t regBuf[2] = {reg >> 8, reg & 0xff};    //寄存器地址
	
	ret = I2C_WriteBytes(0x2a,  regBuf, 2);	//IIC写入数据
	if(ret) //若失败
		return -1;
	
	ret = I2C_ReadBytes(0x2a, buf, len);		//IIC读取数据
	if(ret) //若失败
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
  * @brief  触摸屏 I/O配置
  * @param  无
  * @retval 无
  */
static void I2C_GPIO_Config(void)
{

 
 //使用软件IIC
    /*配置SCL引脚 */   
     GPIO_SetPinMux(GPIO1, GPIO_Pin_28, GPIO_FUNCTION_0);  /*SDA*/
	 GPIO_SetPinDir(GPIO1, GPIO_Pin_28,GPIO_Mode_OUT);  //SDA
	
    GPIO_SetPinMux(GPIO1, GPIO_Pin_29, GPIO_FUNCTION_0);  /*SCL*/
	GPIO_SetPinDir(GPIO1, GPIO_Pin_29,GPIO_Mode_OUT);  //SCL

		/*配置RST引脚，推挽输出 */   

}




///**
//  * @brief  I2C 工作模式配置
//  * @param  无
//  * @retval 无
//  */
//static void I2C_Mode_Config(void)
//{
//  I2C_InitTypeDef  I2C_InitStructure; 

//  /* I2C 模式配置 */
//  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;	
//  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;		                    
//  I2C_InitStructure.I2C_OwnAddress1 =I2C_OWN_ADDRESS7;
//  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;	
//  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;	/* I2C的寻址模式 */
//  I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;	                          /* 通信速率 */
//  I2C_Init(GTP_I2C, &I2C_InitStructure);	                                  /* I2C1 初始化 */
//  I2C_Cmd(GTP_I2C, ENABLE);  	                                              /* 使能 I2C1 */

//  I2C_AcknowledgeConfig(GTP_I2C, ENABLE);

//}

/*************************************************
  Function:       将i2c的引脚配置为上拉输入模式
  Description:    初始化i2c引脚配置
  Calls:          GPIO_Init();
  Called By:      i2c_WaitAck();
                  i2c_ReadByte();
  Input:          无
  Output:         无
  Return:         无
*************************************************/
void SDA_In(void)
{

	 GPIO_SetPinDir(GPIO1, GPIO_Pin_28,GPIO_Mode_IN);  //SDA
	
}

/*************************************************
  Function:       将i2c的DATA引脚配置为推挽输出模式
  Description:    初始化i2c引脚配置
  Calls:          GPIO_Init();
  Called By:      i2c_Start();
                  i2c_Stop();
				  i2c_SendByte();
				  i2c_Ack();
				  i2c_NAck();
  Input:          无
  Output:         无
  Return:         无
*************************************************/
void SDA_Out(void)
{
		 GPIO_SetPinDir(GPIO1, GPIO_Pin_28,GPIO_Mode_OUT);  //SDA

}


/**
  * @brief  I2C 外设(GT1xx)初始化
  * @param  无
  * @retval 无
  */
void I2C_Touch_Init(void)
{
					
  I2C_GPIO_Config(); 

//	I2C_GTP_IRQEnable(); //使能中断
//	I2C_GTP_IRQDisable(); //关闭中断

}


/*
*********************************************************************************************************
*	函 数 名: i2c_Delay
*	功能说明: I2C总线位延迟，最快400KHz
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void i2c_Delay(void)
{
	uint16_t i;

	/*　
	 	下面的时间是通过逻辑分析仪测试得到的。
    工作条件：CPU主频72MHz ，MDK编译环境，1级优化
      
		循环次数为5时，约延时5.3us 
		循环次数为10时，约延时8.6~8.8 us ，  
		循环次数为100时，约延时71.6~71.8 us ，  
  */
	for (i = 0; i < 50; i++);
}

/*
*********************************************************************************************************
*	函 数 名: i2c_Start
*	功能说明: CPU发起I2C总线启动信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_Start(void)
{
	SDA_Out();    //设置成推挽输出
	/* 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号 */
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
*	函 数 名: i2c_Start
*	功能说明: CPU发起I2C总线停止信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_Stop(void)
{
	SDA_Out();    //设置成推挽输出
	/* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */
	I2C_SDA_0();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SDA_1();
	i2c_Delay();
}

/*
*********************************************************************************************************
*	函 数 名: i2c_SendByte
*	功能说明: CPU向I2C总线设备发送8bit数据
*	形    参：_ucByte ： 等待发送的字节
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_SendByte(uint8_t _ucByte)
{
	uint8_t i;

	SDA_Out();    //设置成推挽输出
	/* 先发送字节的高位bit7 */
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
		_ucByte <<= 1;	/* 左移一个bit */
		I2C_SCL_1();
		i2c_Delay();	
		I2C_SCL_0();
		if (i == 7)
		{
//			 I2C_SDA_1(); // 释放总线
			SDA_In();	/* SDA设置为上拉输入 */
		}
		i2c_Delay();
	}
}

/*
*********************************************************************************************************
*	函 数 名: i2c_ReadByte
*	功能说明: CPU从I2C总线设备读取8bit数据
*	形    参：无
*	返 回 值: 读到的数据
*********************************************************************************************************
*/
uint8_t i2c_ReadByte(void)
{
	uint8_t i;
	uint8_t value;

	SDA_In();	/* SDA设置为上拉输入 */
	
	/* 读到第1个bit为数据的bit7 */
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
*	函 数 名: i2c_WaitAck
*	功能说明: CPU产生一个时钟，并读取器件的ACK应答信号
*	形    参：无
*	返 回 值: 返回0表示正确应答，1表示无器件响应
*********************************************************************************************************
*/
uint8_t i2c_WaitAck(void)
{
	uint8_t re, i;
I2C_SDA_1();
	SDA_In();	/* SDA设置为上拉输入 */
	i2c_Delay();
	I2C_SCL_1();	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	i2c_Delay();
//	while (I2C_SDA_READ() != 0);	/* CPU读取SDA口线状态 */
//		re = 0;
	i = 5;
	while (i){	/* CPU读取SDA口线状态 */
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
*	函 数 名: i2c_Ack
*	功能说明: CPU产生一个ACK信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_Ack(void)
{
	SDA_Out();    //设置成推挽输出
	
	I2C_SDA_0();	/* CPU驱动SDA = 0 */
	i2c_Delay();
	I2C_SCL_1();	/* CPU产生1个时钟 */
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
	I2C_SDA_1();	/* CPU释放SDA总线 */
}

/*
*********************************************************************************************************
*	函 数 名: i2c_NAck
*	功能说明: CPU产生1个NACK信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_NAck(void)
{
	SDA_Out();    //设置成推挽输出
	I2C_SDA_1();	/* CPU驱动SDA = 1 */
	i2c_Delay();
	I2C_SCL_1();	/* CPU产生1个时钟 */
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();	
}



#define I2C_DIR_WR	0		/* 写控制bit */
#define I2C_DIR_RD	1		/* 读控制bit */

/**
  * @brief   使用IIC读取数据
  * @param   
  * 	@arg ClientAddr:从设备地址
  *		@arg pBuffer:存放由从机读取的数据的缓冲区指针
  *		@arg NumByteToRead:读取的数据长度
  * @retval  无
  */
uint32_t I2C_ReadBytes(uint8_t ClientAddr,uint8_t* pBuffer, uint16_t NumByteToRead)
{
	
	/* 第1步：发起I2C总线启动信号 */
	i2c_Start();
	
	/* 第2步：发起控制字节，高7bit是地址，bit0是读写控制位，0表示写，1表示读 */
	i2c_SendByte(ClientAddr | I2C_DIR_RD);	/* 此处是读指令 */
	
	/* 第3步：等待ACK */
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* 器件无应答 */
	}

	while(NumByteToRead) 
  {
    
   *pBuffer = i2c_ReadByte();
    
   if(NumByteToRead == 1)
    {
			i2c_NAck();	/* 最后1个字节读完后，CPU产生NACK信号(驱动SDA = 1) */
      
      break;
    }
    /* 读指针自增 */
    pBuffer++; 
      
    /*计数器自减 */
    NumByteToRead--;
    
    i2c_Ack();	/* 中间字节读完后，CPU产生ACK信号(驱动SDA = 0) */  
  }

	/* 发送I2C总线停止信号 */
	i2c_Stop();
	return 0;	/* 执行成功 */

cmd_fail: /* 命令执行失败后，切记发送停止信号，避免影响I2C总线上其他设备 */
	/* 发送I2C总线停止信号 */
	i2c_Stop();
	return 1;
}

/**
  * @brief   使用IIC写入数据
  * @param   
  * 	@arg ClientAddr:从设备地址
  *		@arg pBuffer:缓冲区指针
  *     @arg NumByteToWrite:写的字节数
  * @retval  无
  */
uint32_t I2C_WriteBytes(uint8_t ClientAddr,uint8_t* pBuffer,  uint8_t NumByteToWrite)
{
	uint16_t m;	

  /*　第0步：发停止信号，启动内部写操作　*/
  i2c_Stop();
  
  /* 通过检查器件应答的方式，判断内部写操作是否完成, 一般小于 10ms 			
    CLK频率为200KHz时，查询次数为30次左右
  */
  for (m = 0; m < 1000; m++)
  {				
    /* 第1步：发起I2C总线启动信号 */
    i2c_Start();
    
    /* 第2步：发起控制字节，高7bit是地址，bit0是读写控制位，0表示写，1表示读 */
    i2c_SendByte(ClientAddr | I2C_DIR_WR);	/* 此处是写指令 */
    
    /* 第3步：发送一个时钟，判断器件是否正确应答 */
    if (i2c_WaitAck() == 0)
    {
      break;
    }
  }
  if (m  == 1000)
  {
    goto cmd_fail;	/* EEPROM器件写超时 */
  }	
	
  while(NumByteToWrite--)
  {
  /* 第4步：开始写入数据 */
  i2c_SendByte(*pBuffer);

  /* 第5步：检查ACK */
  if (i2c_WaitAck() != 0)
  {
    goto cmd_fail;	/* 器件无应答 */
  }
  
      pBuffer++;	/* 地址增1 */		
  }
	
	/* 命令执行成功，发送I2C总线停止信号 */
	i2c_Stop();
	return 0;

cmd_fail: /* 命令执行失败后，切记发送停止信号，避免影响I2C总线上其他设备 */
	/* 发送I2C总线停止信号 */
	i2c_Stop();
	return 1;
}



/*********************************************END OF FILE**********************/


