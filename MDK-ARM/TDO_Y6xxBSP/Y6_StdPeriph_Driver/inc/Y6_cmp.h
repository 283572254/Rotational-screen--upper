

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Y6_CMP_H
#define __Y6_CMP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "Y6.h"

/** @addtogroup Y6_StdPeriph_Driver
  * @{
  */  

/** @defgroup CMP 
  * @brief CMP driver modules
  * @{
  */
typedef struct
{
  uint8_t Channel;            /*!< Select CMP0/CMP1     
                                This parameter can be a value of @ref CMP_channels  */
	uint8_t SelectNegitave;     /*!< Select internel VBG(DISABLE) or external cmp_neg(ENABLE) as reference voltage */
	uint8_t Hysen;              /*!< Specifies whether add 100mV delay for CMP or not,set ENABLE/DISABLE */
}CMP_InitTypeDef;

/** @defgroup CMP_channels
  * @{
  */ 
#define CMP_Channel_0			((uint8_t) 0x01)
#define CMP_Channel_1			((uint8_t) 0x02)
/**
  * @}
  */


/** @defgroup CMP_PERIPH 
  * @{
  */
#define IS_CMP_CHANNEL(PERIPH)	((PERIPH & CMP_Channel_0) || \
																 (PERIPH & CMP_Channel_1))
/**
  * @}
  */


/*  Function used to set the CMP configuration to the default reset state *****/
void CMP_Reset(void);
void CMP_CLKSET(FunctionalState NewState);
void CMP_Init(CMP_InitTypeDef* CMP_InitStruct);
void CMP_ITConfig(uint8_t channel,FunctionalState NewState);
ITStatus CMP_GetITStatus(uint8_t channel);
void CMP_ClearITFlag(uint8_t channel);
uint8_t CMP_GetCompareResult(uint8_t channel);

#ifdef __cplusplus
}
#endif

#endif /*__Y6_CMP_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT TDO *****END OF FILE****/
