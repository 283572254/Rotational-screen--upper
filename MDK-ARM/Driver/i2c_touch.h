#ifndef __I2C_TOUCH_H
#define	__I2C_TOUCH_H

#include "y6.h"
extern  void Delay_ms(unsigned int delay);

/*设定使用的电容屏IIC设备地址*/
#define GTP_ADDRESS            0x70

#define I2CT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT         ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))

#define GTP_I2C_SDA_GPIO_PORT  GPIO1
#define GTP_I2C_SDA_PIN GPIO_Pin_28
#define GTP_I2C_SCL_PIN GPIO_Pin_29
#define I2C_SDA_1()  GPIO_SetPin(GTP_I2C_SDA_GPIO_PORT, GTP_I2C_SDA_PIN)		/* SDA = 1 */
#define I2C_SDA_0()  GPIO_ClearPin(GTP_I2C_SDA_GPIO_PORT, GTP_I2C_SDA_PIN)		/* SDA = 0 */

#define I2C_SCL_1()  GPIO_SetPin(GTP_I2C_SDA_GPIO_PORT, GTP_I2C_SCL_PIN)		/* SCL = 1 */
#define I2C_SCL_0()  GPIO_ClearPin(GTP_I2C_SDA_GPIO_PORT, GTP_I2C_SCL_PIN)		/* SCL = 0 */

#define I2C_SDA_READ()  GPIO_ReadPin(GTP_I2C_SDA_GPIO_PORT, GTP_I2C_SDA_PIN)	/* 读SDA口线状态 */

/*I2C引脚*/
#define GTP_I2C                          I2C2
#define GTP_I2C_CLK                      RCC_APB1Periph_I2C2
#define GTP_I2C_CLK_INIT								RCC_APB1PeriphClockCmd	


//软件IIC使用的宏


//函数接口

int FT6236_RD_Reg(unsigned short int reg,unsigned char *buf,unsigned char len);
void I2C_Touch_Init(void);
uint32_t I2C_WriteBytes(uint8_t ClientAddr,uint8_t* pBuffer,  uint8_t NumByteToWrite);
uint32_t I2C_ReadBytes(uint8_t ClientAddr,uint8_t* pBuffer, uint16_t NumByteToRead);





#endif /* __I2C_TOUCH_H */
