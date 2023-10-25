 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Y6_GPIO_H
#define __Y6_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "Y6.h"

/** @addtogroup Y6_StdPeriph_Driver
  * @{
  */

/** @addtogroup GPIO
  * @{
  */

/** @defgroup GPIO_Exported_Constants
  * @{
  */
#define IS_GPIO_ALL_PERIPH(PERIPH) (((PERIPH) == GPIO0) || ((PERIPH) == GPIO1))

/** @defgroup GPIO_IT_Types
  * @{
  */

#define IS_GPIO_IT_ALL_PERIPH(IT)  (((IT) == GPIO0_IT) || (IT == GPIO1_IT))  
								                                      
/** 
  * @brief  function selection  
  */

typedef enum
{ 
  GPIO_FUNCTION_0 = 0,
  GPIO_FUNCTION_1 = 1,
  GPIO_FUNCTION_2 = 2,
  GPIO_FUNCTION_3 = 3,
  GPIO_FUNCTION_4 = 4,
  GPIO_FUNCTION_5 = 5,
  GPIO_FUNCTION_6 = 6,
  GPIO_FUNCTION_7 = 7
}GPIOFUNC_TypeDef;

#define IS_GPIO_FUNCTION(FUNCTION) (((FUNCTION) == GPIO_FUNCTION_0) || ((FUNCTION) == GPIO_FUNCTION_1) || \
									((FUNCTION) == GPIO_FUNCTION_2) || ((FUNCTION) == GPIO_FUNCTION_3) || \
									((FUNCTION) == GPIO_FUNCTION_4) || ((FUNCTION) == GPIO_FUNCTION_5) || \
									((FUNCTION) == GPIO_FUNCTION_6) || ((FUNCTION) == GPIO_FUNCTION_7))
         

/** 
  * @brief  Configuration Mode enumeration  
  */

typedef enum
{ GPIO_Mode_IN = 0x0,
  GPIO_Mode_OUT = 0x1
}GPIOMode_TypeDef;

#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_Mode_OUT) || ((MODE) == GPIO_Mode_IN))

/** 
  * @brief  Configuration Edge Action enumeration  
  */

typedef enum
{ 
  GPIO_IRQ_EDGE_FALLING = 0x0,
  GPIO_IRQ_EDGE_RISING,
  GPIO_IRQ_EDGE_DOUBLE
}EdgeAction;

#define IS_GPIO_EDGE_ACTION(ACTION) (((ACTION) == GPIO_IRQ_EDGE_FALLING) || ((ACTION) == GPIO_IRQ_EDGE_RISING)|| \
									 ((ACTION) == GPIO_IRQ_EDGE_DOUBLE))


/** 
  * @brief  Configuration Level Action enumeration  
  */

typedef enum
{ 
  GPIO_IRQ_LEVEL_LOW = 0x0,
  GPIO_IRQ_LEVEL_HIGH
}LevelAction;

#define IS_GPIO_LEVEL_ACTION(ACTION) (((ACTION) == GPIO_IRQ_LEVEL_LOW) || ((ACTION) == GPIO_IRQ_LEVEL_HIGH))

/** 
  * @brief  GPIO Init structure definition  
  */

typedef struct
{
  uint32_t GPIO_Pin;              /*!< Specifies the GPIO pins to be configured.
                                      This parameter can be any value of @ref GPIO_pins_define */

  GPIOFUNC_TypeDef GPIO_Function;  /*!< Specifies the function for the selected pins.
                                      This parameter can be a value of @ref PIOFUNC_TypeDef */

  GPIOMode_TypeDef GPIO_Mode;     /*!< Specifies the operating mode for the selected pins.
                                      This parameter can be a value of @ref GPIOMode_TypeDef */
}GPIO_InitTypeDef;

//bit[4:3]
typedef enum
{ GPIO_PULL_DISABLE = 0x00,
  GPIO_PULL_DOWN = 0x08,
  GPIO_PULL_UP = 0x10,
}GPIOPull_TypeDef;

//bit[8]
typedef enum
{ GPIO_DRIVER_0 = 0x000,
  GPIO_DRIVER_1 = 0x100,
}GPIODrive_TypeDef;

//bit[9]
typedef enum
{ GPIO_SLEWRATE_FAST = 0x000,
  GPIO_SLEWRATE_SLOW = 0x200,
}GPIOSLEWRATE_TypeDef;

/** 
  * @brief  Bit_SET and Bit_RESET enumeration  
  */

typedef enum
{ Bit_RESET = 0,
  Bit_SET
}BitAction;

#define IS_GPIO_BIT_ACTION(ACTION) (((ACTION) == Bit_RESET) || ((ACTION) == Bit_SET))

/**
  * @}
  */



/** @defgroup GPIO_pins_define 
  * @{
  */

#define GPIO_Pin_0                 ((uint32_t)0x00000001)  /*!< Pin 0 selected */
#define GPIO_Pin_1                 ((uint32_t)0x00000002)  /*!< Pin 1 selected */
#define GPIO_Pin_2                 ((uint32_t)0x00000004)  /*!< Pin 2 selected */
#define GPIO_Pin_3                 ((uint32_t)0x00000008)  /*!< Pin 3 selected */
#define GPIO_Pin_4                 ((uint32_t)0x00000010)  /*!< Pin 4 selected */
#define GPIO_Pin_5                 ((uint32_t)0x00000020)  /*!< Pin 5 selected */
#define GPIO_Pin_6                 ((uint32_t)0x00000040)  /*!< Pin 6 selected */
#define GPIO_Pin_7                 ((uint32_t)0x00000080)  /*!< Pin 7 selected */
#define GPIO_Pin_8                 ((uint32_t)0x00000100)  /*!< Pin 8 selected */
#define GPIO_Pin_9                 ((uint32_t)0x00000200)  /*!< Pin 9 selected */
#define GPIO_Pin_10                ((uint32_t)0x00000400)  /*!< Pin 10 selected */
#define GPIO_Pin_11                ((uint32_t)0x00000800)  /*!< Pin 11 selected */
#define GPIO_Pin_12                ((uint32_t)0x00001000)  /*!< Pin 12 selected */
#define GPIO_Pin_13                ((uint32_t)0x00002000)  /*!< Pin 13 selected */
#define GPIO_Pin_14                ((uint32_t)0x00004000)  /*!< Pin 14 selected */
#define GPIO_Pin_15                ((uint32_t)0x00008000)  /*!< Pin 15 selected */
#define GPIO_Pin_16                ((uint32_t)0x00010000)  /*!< Pin 16 selected */
#define GPIO_Pin_17                ((uint32_t)0x00020000)  /*!< Pin 17 selected */
#define GPIO_Pin_18                ((uint32_t)0x00040000)  /*!< Pin 18 selected */
#define GPIO_Pin_19                ((uint32_t)0x00080000)  /*!< Pin 19 selected */
#define GPIO_Pin_20                ((uint32_t)0x00100000)  /*!< Pin 20 selected */
#define GPIO_Pin_21                ((uint32_t)0x00200000)  /*!< Pin 21 selected */
#define GPIO_Pin_22                ((uint32_t)0x00400000)  /*!< Pin 22 selected */
#define GPIO_Pin_23                ((uint32_t)0x00800000)  /*!< Pin 23 selected */
#define GPIO_Pin_24                ((uint32_t)0x01000000)  /*!< Pin 24 selected */
#define GPIO_Pin_25                ((uint32_t)0x02000000)  /*!< Pin 25 selected */
#define GPIO_Pin_26                ((uint32_t)0x04000000)  /*!< Pin 26 selected */
#define GPIO_Pin_27                ((uint32_t)0x08000000)  /*!< Pin 27 selected */
#define GPIO_Pin_28                ((uint32_t)0x10000000)  /*!< Pin 28 selected */
#define GPIO_Pin_29                ((uint32_t)0x20000000)  /*!< Pin 29 selected */
#define GPIO_Pin_30                ((uint32_t)0x40000000)  /*!< Pin 30 selected */
#define GPIO_Pin_31                ((uint32_t)0x80000000)  /*!< Pin 31 selected */
#define GPIO_Pin_All               ((uint32_t)0xFFFFFFFF)  /*!< All pins selected */


#define IS_GPIO_PIN(PIN) ((((PIN) & (uint32_t)0x00) == 0x00) && ((PIN) != (uint32_t)0x00))

#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_Pin_0) || \
                              ((PIN) == GPIO_Pin_1) || \
                              ((PIN) == GPIO_Pin_2) || \
                              ((PIN) == GPIO_Pin_3) || \
                              ((PIN) == GPIO_Pin_4) || \
                              ((PIN) == GPIO_Pin_5) || \
                              ((PIN) == GPIO_Pin_6) || \
                              ((PIN) == GPIO_Pin_7) || \
                              ((PIN) == GPIO_Pin_8) || \
                              ((PIN) == GPIO_Pin_9) || \
                              ((PIN) == GPIO_Pin_10) || \
                              ((PIN) == GPIO_Pin_11) || \
                              ((PIN) == GPIO_Pin_12) || \
                              ((PIN) == GPIO_Pin_13) || \
                              ((PIN) == GPIO_Pin_14) || \
							                ((PIN) == GPIO_Pin_15) || \
                              ((PIN) == GPIO_Pin_16) || \
                              ((PIN) == GPIO_Pin_17) || \
                              ((PIN) == GPIO_Pin_18) || \
                              ((PIN) == GPIO_Pin_19) || \
                              ((PIN) == GPIO_Pin_20) || \
                              ((PIN) == GPIO_Pin_21) || \
                              ((PIN) == GPIO_Pin_22) || \
                              ((PIN) == GPIO_Pin_23) || \
                              ((PIN) == GPIO_Pin_24) || \
                              ((PIN) == GPIO_Pin_25) || \
                              ((PIN) == GPIO_Pin_26) || \
                              ((PIN) == GPIO_Pin_27) || \
                              ((PIN) == GPIO_Pin_28) || \
                              ((PIN) == GPIO_Pin_29) || \
							                ((PIN) == GPIO_Pin_30) || \
							                ((PIN) == GPIO_Pin_31) || \
                              ((PIN) == GPIO_Pin_All))

/**
  * @}
  */
                                               
/**
  * @}
  */

void GPIO_Reset(void);
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_SetPinMux(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, GPIOFUNC_TypeDef GPIO_Function);
void GPIO_SetPinDir(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode);
void GPIO_WritePort(GPIO_TypeDef* GPIOx, uint32_t PortVal);
uint32_t GPIO_ReadPort(GPIO_TypeDef *GPIOx);
void GPIO_WritePin(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, BitAction BitVal);
uint8_t GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin);
void GPIO_SetPin(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
void GPIO_ClearPin(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
void GPIO_PinMask(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
void GPIO_PinUnmask(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
/******************interrupt config****************************************/
void GPIO_EdgeITEnable(GPIO_IT_TypeDef* GPIOx_IT, uint32_t GPIO_Pin, EdgeAction GPIO_Irq);
void GPIO_LevelITEnable(GPIO_IT_TypeDef* GPIOx_IT, uint32_t GPIO_Pin, LevelAction GPIO_Irq);
void GPIO_MaskIT(GPIO_IT_TypeDef* GPIOx_IT, uint32_t GPIO_Pin);
void GPIO_UnmaskIT(GPIO_IT_TypeDef* GPIOx_IT, uint32_t GPIO_Pin);
void GPIO_EdgeITClear(GPIO_IT_TypeDef* GPIOx_IT, uint32_t GPIO_Pin);
uint8_t GPIO_GetOriginalITStatus(GPIO_IT_TypeDef* GPIOx_IT, uint32_t GPIO_Pin);
uint8_t GPIO_GetMaskITStatus(GPIO_IT_TypeDef* GPIOx_IT, uint32_t GPIO_Pin);
void GPIO_ConfigAna(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin, FunctionalState NewState);
void GPIO_ConfigPull(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin, GPIOPull_TypeDef NewPull);
void GPIO_ConfigDriver(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin, GPIODrive_TypeDef NewDriver);
void GPIO_ConfigSlewRate(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin, GPIOSLEWRATE_TypeDef NewSlewRate);

#ifdef __cplusplus
}
#endif

#endif /* __Y6_GPIO_H */
/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 TDO *****END OF FILE****/

