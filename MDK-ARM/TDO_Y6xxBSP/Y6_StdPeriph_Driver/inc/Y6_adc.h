/**
  ******************************************************************************
  * @file    Y6_adc.h
  * @author  TDO Application Team
  * @version V1.0.1
  * @date    20-April-2014
  * @brief   This file contains all the functions prototypes for the ADC firmware 
  *          library
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 TDO</center></h2>
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Y6_ADC_H
#define __Y6_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "Y6.h"

/** @addtogroup Y6_StdPeriph_Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  ADC Init structure definition
  */
  
typedef struct
{
  uint16_t ADC_Channel;                   /*!< ADC input channel number */
  uint32_t ADC_SingleTrigConvMode;/*!< Specifies whether the conversion that trigger channels 
                                             is performed in Continuous(all channles) or Single(one channel) mode.
                                             This parameter can be set to ENABLE or DISABLE. */
  uint32_t ADC_TrigConvSrcSel;       /*!< Selet the external/internal event used to trigger the start of conversion. 
                                          This parameter can be a value of @ref ADC_TriggerSourceSelect*/
  uint32_t ADC_TrigConvEdge;         /*!< Specifies ADC trigger edge.
                                         This parameter can be a value of @ref ADC_TriggerMode */
  uint8_t ADC_First_DisSampleNum;/*!< discard sample num when conversion at first time */
  uint8_t ADC_Exch_DisSampleNum;/*!< discard sample num when exchange ADC channel */
 
  uint32_t ADC_SampFrqSel;       /*!< Specifies ADC sample frequence.
                                     This parameter can be a value of @ref ADC_SampleFrequence */
  uint8_t ADC_ClkDiv;           /*!< Specifies ADC clock Frequency division value */
} ADC_InitTypeDef;

/** @addtogroup ADC_SingleTrigConvMode
  * @{
  */
#define ADC_SingleTrigConv_Enable   ((uint32_t)0x00001000)
#define ADC_SingleTrigConv_Disable  ((uint32_t)0x00000000)
#define IS_ADC_SINGLE_TRIG(singtrg) (((singtrg) == ADC_SingleTrigConv_Disable) || \
                                     ((singtrg) == ADC_SingleTrigConv_Enable))
/**
  * @}
  */

/** @addtogroup ADC_TriggerMode
  * @{
  */
#define ADC_TrigEdge_Software       ((uint32_t)0x00000000)
#define ADC_TrigEdge_Rising         ((uint32_t)0x00010000)
#define ADC_TrigEdge_Falling        ((uint32_t)0x00020000)
#define ADC_TrigEdge_RisingFalling  ((uint32_t)0x00030000)
#define IS_ADC_TRIG_EDGE(trigEdge)  (((trigEdge) == ADC_TrigEdge_Software) || \
                                     ((trigEdge) == ADC_TrigEdge_Rising) || \
                                     ((trigEdge) == ADC_TrigEdge_Falling) || \
                                     ((trigEdge) == ADC_TrigEdge_RisingFalling))
/**
  * @}
  */

/** @addtogroup ADC_TriggerSourceSelect
  * @{
  */
#define ADC_Internal_TrigSrc_TIM1_CH4    ((uint32_t)0x00000000)
#define ADC_Internal_TrigSrc_TIM4_CH1    ((uint32_t)0x00100000)
#define ADC_Internal_TrigSrc_TIM15_CH1   ((uint32_t)0x00200000)
#define ADC_Internal_TrigSrc_TIM16_CH1   ((uint32_t)0x00300000)
#define ADC_External_TrigSrc_GPIO2_2     ((uint32_t)0x00400000)
#define ADC_External_TrigSrc_GPIO2_3     ((uint32_t)0x00500000)
#define ADC_External_TrigSrc_GPIO5_2     ((uint32_t)0x00600000)
#define ADC_External_TrigSrc_GPIO5_3     ((uint32_t)0x00700000)
#define IS_ADC_TRIGSRC(trigsrc)  (((trigsrc) == ADC_Internal_TrigSrc_TIM1_CH4) || \
                                  ((trigsrc) == ADC_Internal_TrigSrc_TIM4_CH1) || \
                                  ((trigsrc) == ADC_Internal_TrigSrc_TIM15_CH1) || \
                                  ((trigsrc) == ADC_Internal_TrigSrc_TIM16_CH1) || \
                                  ((trigsrc) == ADC_External_TrigSrc_GPIO2_2) || \
                                  ((trigsrc) == ADC_External_TrigSrc_GPIO2_3) || \
                                  ((trigsrc) == ADC_External_TrigSrc_GPIO5_2) || \
                                  ((trigsrc) == ADC_External_TrigSrc_GPIO5_3)) 
/**
  * @}
  */

/** @addtogroup ADC_SampleFrequence
  * @{
  */
#define ADC_1140K_SampFrq ((uint32_t)0x00030000)
#define ADC_571K_SampFrq  ((uint32_t)0x00020000)
#define ADC_142K_SampFrq  ((uint32_t)0x00010000)
#define ADC_285K_SampFrq  ((uint32_t)0x00000000)
#define IS_ADC_SAMP_FRQ(sampFrq) ((sampFrq) == (ADC_1140K_SampFrq) || \
                                  (sampFrq) == (ADC_571K_SampFrq) || \
                                  (sampFrq) == (ADC_285K_SampFrq) || \
                                  (sampFrq) == (ADC_142K_SampFrq))
/**
  * @}
  */

/** @defgroup ADC_channels 
  * @{
  */ 
#define ADC_CHANNEL0 ((uint16_t)0x01)
#define ADC_CHANNEL1 ((uint16_t)0x02)
#define ADC_CHANNEL2 ((uint16_t)0x04)
#define ADC_CHANNEL3 ((uint16_t)0x08)
#define ADC_CHANNEL4 ((uint16_t)0x10)
#define ADC_CHANNEL5 ((uint16_t)0x20)
#define ADC_CHANNEL6 ((uint16_t)0x40)
#define ADC_CHANNEL7 ((uint16_t)0x80)
#define ADC_CHANNEL8 ((uint16_t)0x100)
#define ADC_CHANNEL9 ((uint16_t)0x200)
#define ADC_CHANNEL_ALL ((uint16_t)0x3ff)
/**
  * @}
  */ 


/** @defgroup ADC_PERIPH 
  * @{
  */
#define IS_ADC_CHANNEL(PERIPH) ((PERIPH) < 0x400)

/**
  * @}
  */ 

#define ADC_ANAFUC_EN  ((uint32_t)0x00000080)   /* enable analog function */

/* ADC channel irq enable */
#define ADC_Irq ((uint32_t)(1<<16))

/* ADC channel dispatch */
#define ADC_Dispatch_Channel0 ((uint32_t)(1<<0))
#define ADC_Dispatch_Channel1 ((uint32_t)(1<<1))
#define ADC_Dispatch_Channel2 ((uint32_t)(1<<2))
#define ADC_Dispatch_Channel3 ((uint32_t)(1<<3))
#define ADC_Dispatch_Channel4 ((uint32_t)(1<<4))
#define ADC_Dispatch_Channel5 ((uint32_t)(1<<5))
#define ADC_Dispatch_Channel6 ((uint32_t)(1<<6))
#define ADC_Dispatch_Channel7 ((uint32_t)(1<<7))
#define ADC_Dispatch_Channel8 ((uint32_t)(1<<8))
#define ADC_Dispatch_Channel9 ((uint32_t)(1<<9))

/* ADC channel it status */
#define ADC_ItStatus_Channel0 (ITStatus)(ADCx->CTRL1 & (1<<0))
#define ADC_ItStatus_Channel1 (ITStatus)((ADCx->CTRL1 & (1 << 1)) >> 1)
#define ADC_ItStatus_Channel2 (ITStatus)((ADCx->CTRL1 & (1 << 2)) >> 2)
#define ADC_ItStatus_Channel3 (ITStatus)((ADCx->CTRL1 & (1 << 3)) >> 3)
#define ADC_ItStatus_Channel4 (ITStatus)((ADCx->CTRL1 & (1 << 4)) >> 4)
#define ADC_ItStatus_Channel5 (ITStatus)((ADCx->CTRL1 & (1 << 5)) >> 5)
#define ADC_ItStatus_Channel6 (ITStatus)((ADCx->CTRL1 & (1 << 6)) >> 6)
#define ADC_ItStatus_Channel7 (ITStatus)((ADCx->CTRL1 & (1 << 7)) >> 7)
#define ADC_ItStatus_Channel8 (ITStatus)((ADCx->CTRL1 & (1 << 8)) >> 8)
#define ADC_ItStatus_Channel9 (ITStatus)((ADCx->CTRL1 & (1 << 9)) >> 9)

/* Clear ADC channel it flag */
#define ADC_ItClear_Channel0 ((uint32_t)(1 << 0))
#define ADC_ItClear_Channel1 ((uint32_t)(1 << 1))
#define ADC_ItClear_Channel2 ((uint32_t)(1 << 2))
#define ADC_ItClear_Channel3 ((uint32_t)(1 << 3))
#define ADC_ItClear_Channel4 ((uint32_t)(1 << 4))
#define ADC_ItClear_Channel5 ((uint32_t)(1 << 5))
#define ADC_ItClear_Channel6 ((uint32_t)(1 << 6))
#define ADC_ItClear_Channel7 ((uint32_t)(1 << 7))
#define ADC_ItClear_Channel8 ((uint32_t)(1 << 8))
#define ADC_ItClear_Channel9 ((uint32_t)(1 << 9))

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 

  /*  Function used to set the ADC configuration to the default reset state *****/
void ADC_RCC_Init(ADC_TypeDef *ADCx, uint8_t ClkDiv);
void ADC_Init(ADC_TypeDef *ADCx, ADC_InitTypeDef *ADC_InitStruct);
void ADC_DeInit(ADC_TypeDef *ADCx, ADC_InitTypeDef *ADC_InitStruct);
void ADC_AnaEn(uint16_t channel);

/* Channels Configuration functions *******************************************/
void ADC_SetConvChannel(ADC_TypeDef *ADCx, uint16_t channel, FunctionalState NewState);
uint32_t ADC_GetConvValue(ADC_TypeDef *ADCx, uint16_t channel);

/* Interrupts and flags management functions **********************************/
void ADC_ITConfig(ADC_TypeDef *ADCx, FunctionalState NewState);
void ADC_ClearITFlag(ADC_TypeDef *ADCx, uint16_t channel);
ITStatus ADC_GetITStatus(ADC_TypeDef *ADCx, uint16_t channel);
void ADC_SetAccumulate(ADC_TypeDef *ADCx, uint16_t channel, uint8_t sampleNum);

/* Software trigger conversion function **********************************/
void ADC_StartSoftwareTrigConv(ADC_TypeDef *ADCx);
void ADC_Run(ADC_TypeDef *ADCx, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /*__Y6_ADC_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT TDO *****END OF FILE****/
