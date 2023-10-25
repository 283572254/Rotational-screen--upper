/**
  ******************************************************************************
  * @file    Y6_adc.c
  * @author  TDO Application Team
  * @version V1.0.1
  * @date    20-April-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Analog to Digital Convertor (ADC) peripheral:
  *           + Initialization and Configuration
  *           + Power saving
  *           + Analog Watchdog configuration
  *           + Temperature Sensor, Vrefint (Internal Reference Voltage) and 
  *             Vbat (Voltage battery) management 
  *           + ADC Channels Configuration
  *           + ADC Channels DMA Configuration
  *           + Interrupts and flags management
  *
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 TDO</center></h2>
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "Y6_adc.h"
#include "Y6_rcc.h"

/** @addtogroup M1130_StdPeriph_Driver
  * @{
  */
/** @addtogroup ADC
  * @brief ADC driver modules
  * @{
  */

/**
  * @brief  Power_off the ADC peripheral
  * @param  ADCx:pointer to an ADC_InitTypeDef structure that contains 
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure that contains 
  *         the configuration information for the specified ADC peripheral.
  * @retval None 
  */
void ADC_DeInit(ADC_TypeDef *ADCx, ADC_InitTypeDef *ADC_InitStruct)
{
  /* Check the parameters */
  assert_param(IS_ADC_CHANNEL(ADC_InitStruct->ADC_Channel));
  assert_param(IS_ADC_SAMP_FRQ(ADC_InitStruct->ADC_SampFrqSel));
  assert_param(IS_ADC_TRIG_EDGE(ADC_InitStruct->ADC_TrigConvEdge));
  assert_param(IS_ADC_TRIGSRC(ADC_InitStruct->ADC_TrigConvSrcSel));

  if (ADCx == ADC0)
  {
    /* ADC peripheral registers to their default reset values*/	
    RCC_SetPRESETCTRL(1 << PRESET_BIT_ADC0, DISABLE);
    RCC_SetPRESETCTRL(1 << PRESET_BIT_ADC0, ENABLE);
    /* ADC Periph clock disable */
    RCC_SetAHBCLK(1 << AHBCLK_BIT_ADC0,	DISABLE);
    /* power-offer ADC */
    RCC_PDRUNConfig(RCC_PDCFG_ADC0, RCC_PDCFG_POWER_DOWN);
  }
}

/**
 * @brief  Power-on the ADC peripheral,initializes the ADC clock and reset
 *		   the ADC registers to their default value. 
 * @param  ADCx: pointer to an ADC_InitTypeDef structure that contains  
 * @param  ClkDiv:Specifies ADC clock Frequency division value 
 * @retval None
 */
void ADC_RCC_Init(ADC_TypeDef *ADCx, uint8_t ClkDiv)
{
  if (ADCx == ADC0)
  {
    /* power-on ADC */
    RCC_PDRUNConfig(RCC_PDCFG_ADC0, RCC_PDCFG_POWER_ON);
    /* ADC Periph clock enable */
    RCC_ResetAHBCLK(1 << AHBCLK_BIT_ADC0);
    RCC_SETCLKDivider(RCC_CLOCKFREQ_ADCCLK, ClkDiv);
    /* ADC peripheral registers to their default reset values*/	
  }
}

/**
  * @brief  Initializes the ADC peripheral according to the specified parameters
  *         in the ADC_InitStruct.
  * @note   This function is used to configure the global features of the ADC ( 
  *         Resolution, Data Alignment, continuous mode activation, External 
  *         trigger source and edge, Sequence Scan Direction).   
 * @param   ADCx: pointer to an ADC_InitTypeDef structure that contains  
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure that contains 
  *         the configuration information for the specified ADC peripheral.
  * @retval None
  */
void ADC_Init(ADC_TypeDef *ADCx, ADC_InitTypeDef *ADC_InitStruct)
{
  /* Check the parameters */
  assert_param(IS_ADC_CHANNEL(ADC_InitStruct->ADC_Channel));
  assert_param(IS_ADC_SAMP_FRQ(ADC_InitStruct->ADC_SampFrqSel));
  assert_param(IS_ADC_SINGLE_TRIG(ADC_InitStruct->ADC_SingleTrigConvMode));
  assert_param(IS_ADC_TRIG_EDGE(ADC_InitStruct->ADC_TrigConvEdge));
  assert_param(IS_ADC_TRIGSRC(ADC_InitStruct->ADC_TrigConvSrcSel));

  ADC_RCC_Init(ADCx, ADC_InitStruct->ADC_ClkDiv);
  /* config the ADC sample frequence */
  ADCx->CTRL3 |= ADC_InitStruct->ADC_SampFrqSel;

  ADCx->CTRL5 |= ADC_InitStruct->ADC_First_DisSampleNum | ADC_InitStruct->ADC_Exch_DisSampleNum | \
                 ADC_InitStruct->ADC_SingleTrigConvMode | ADC_InitStruct->ADC_TrigConvEdge | \
                 ADC_InitStruct->ADC_TrigConvSrcSel;

  /* set conversion channel */
  ADC_SetConvChannel(ADCx, ADC_InitStruct->ADC_Channel, ENABLE);

  /* set anoalog pin */
  ADC_AnaEn(ADC_InitStruct->ADC_Channel);
}

/**
  * @brief  Start ADC Trigger Conversion.
  * @param  ADCx: pointer to an ADC_InitTypeDef structure that contains  
  * @param  NewState: new state of ADC trigger conversion. 
  *   This parameter can be: ENABLE or DISABLE. 
  * @retval None. 
  */
void ADC_Run(ADC_TypeDef *ADCx, FunctionalState NewState)
{
	if(NewState == ENABLE){
	  /* start ADC trigger conversion */
	  ADCx->CTRL5_CLR = (uint32_t)1 << 31;
	}else{
	  /* stop ADC trigger conversion */
	  ADCx->CTRL5_SET = (uint32_t)1 << 31;
	}
}

/**
  * @brief  select pin mux and enable analog function.
  * @param  channel: ADC channel number,channel0~channel7
  * @retval None 
  */
void ADC_AnaEn(uint16_t channel)
{
  /* Check the parameters */
  assert_param(IS_ADC_CHANNEL(channel));

  /* Enable Channel0 Analog Function */
  //GP5_4 ~ GP5_7
  if (channel & ADC_CHANNEL0)
    PIO1->PIN12 = ADC_ANAFUC_EN;

  if (channel & ADC_CHANNEL1)
    PIO1->PIN13 = ADC_ANAFUC_EN;

  if (channel & ADC_CHANNEL2)
    PIO1->PIN14 = ADC_ANAFUC_EN;

  if (channel & ADC_CHANNEL3)
    PIO1->PIN15 = ADC_ANAFUC_EN;

  //GP6_1 GP6_2
  if (channel & ADC_CHANNEL4)
    PIO1->PIN17 = ADC_ANAFUC_EN;

  if (channel & ADC_CHANNEL5)
    PIO1->PIN18 = ADC_ANAFUC_EN;

  //GP7_0 ~ GP7_3(等待改为10通道)
  if (channel & ADC_CHANNEL6)
    PIO1->PIN24 = ADC_ANAFUC_EN;

  if (channel & ADC_CHANNEL7)
    PIO1->PIN25 = ADC_ANAFUC_EN;

  if (channel & ADC_CHANNEL8)
    PIO1->PIN26 = ADC_ANAFUC_EN;

  if (channel & ADC_CHANNEL9)
    PIO1->PIN27 = ADC_ANAFUC_EN;
}

/**
  * @brief  Enables or disables the specified ADC interrupts.
  * @param  ADCx: pointer to an ADC_InitTypeDef structure that contains 
  * @param  channel: ADC channel number,channel0~channel7 
  * @param  NewState: new state of the specified ADC interrupts.
  *          This parameter can be: ENABLE or DISABLE. 
  * @retval None 
  */
void ADC_ITConfig(ADC_TypeDef *ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState == ENABLE)
  {
    /* Enable Interrupt */
    ADCx->CTRL1_SET = ADC_Irq;
  }
  else
  {
    /* Disable Interrupt */
    ADCx->CTRL1_CLR = ADC_Irq;
  }
}

 /**
   * @brief  Returns the last ADC conversion result data for ADC channel.
   * @param  ADCx: pointer to an ADC_InitTypeDef structure that contains 
   * @param  channel: ADC channel number,channel0~channel7 
   * @retval None 
   */
uint32_t ADC_GetConvValue(ADC_TypeDef *ADCx, uint16_t channel)
{
  uint32_t AdcVal;

  /* Check the parameters */
  assert_param(IS_ADC_CHANNEL(channel));

  /* get channel0 converted num */
  if (channel == ADC_CHANNEL0)
    AdcVal = ADCx->CH0 & 0x3ffff;

  /* get channel1 converted num */
  if (channel == ADC_CHANNEL1)
    AdcVal = ADCx->CH1 & 0x3ffff;

  /* get channel2 converted num */
  if (channel == ADC_CHANNEL2)
    AdcVal = ADCx->CH2 & 0x3ffff;

  /* get channel3 converted num */
  if (channel == ADC_CHANNEL3)
    AdcVal = ADCx->CH3 & 0x3ffff;

  /* get channel4 converted num */
  if (channel == ADC_CHANNEL4)
    AdcVal = ADCx->CH4 & 0x3ffff;

  /* get channel5 converted num */
  if (channel == ADC_CHANNEL5)
    AdcVal = ADCx->CH5 & 0x3ffff;

  /* get channel6 converted num */
  if (channel == ADC_CHANNEL6)
    AdcVal = ADCx->CH6 & 0x3ffff;

  /* get channel7 converted num */
  if (channel == ADC_CHANNEL7)
    AdcVal = ADCx->CH7 & 0x3ffff;
  
  /* get channel8 converted num */
  if (channel == ADC_CHANNEL8)
    AdcVal = ADCx->CH8 & 0x3ffff;
  
  /* get channel9 converted num */
  if (channel == ADC_CHANNEL9)
    AdcVal = ADCx->CH9 & 0x3ffff;

  /* Return the selected ADC conversion value */
  return AdcVal;
}

void ADC_SetAccumulate(ADC_TypeDef *ADCx, uint16_t channel, uint8_t sampleNum)
{
	sampleNum &= 0x1F;	//[28:24]
	sampleNum |= 0x20;	//[29]

	if (channel & ADC_CHANNEL0){
		ADCx->CH0 &= 0xE0FFFFFF;
		ADCx->CH0 |= (sampleNum<<24);
	}
	if (channel & ADC_CHANNEL1){
		ADCx->CH1 &= 0xE0FFFFFF;
		ADCx->CH1 |= (sampleNum<<24);
	}
	if (channel & ADC_CHANNEL2){
		ADCx->CH2 &= 0xE0FFFFFF;
		ADCx->CH2 |= (sampleNum<<24);
	}
	if (channel & ADC_CHANNEL3){
		ADCx->CH3 &= 0xE0FFFFFF;
		ADCx->CH3 |= (sampleNum<<24);
	}
	if (channel & ADC_CHANNEL4){
		ADCx->CH4 &= 0xE0FFFFFF;
		ADCx->CH4 |= (sampleNum<<24);
	}
	if (channel & ADC_CHANNEL5){
		ADCx->CH5 &= 0xE0FFFFFF;
		ADCx->CH5 |= (sampleNum<<24);
	}
	if (channel & ADC_CHANNEL6){
		ADCx->CH6 &= 0xE0FFFFFF;
		ADCx->CH6 |= (sampleNum<<24);
	}
	if (channel & ADC_CHANNEL7){
		ADCx->CH7 &= 0xE0FFFFFF;
		ADCx->CH7 |= (sampleNum<<24);
	}
	if (channel & ADC_CHANNEL8){
		ADCx->CH8 &= 0xE0FFFFFF;
		ADCx->CH8 |= (sampleNum<<24);
	}
	if (channel & ADC_CHANNEL9){
		ADCx->CH9 &= 0xE0FFFFFF;
		ADCx->CH9 |= (sampleNum<<24);
	}
}

/**
  * @brief  Set the ADC conversion channels.
  * @param  ADCx: pointer to an ADC_InitTypeDef structure that contains 
  * @param  channel: ADC channel number,channel0~channel7 
  * @param  NewState: new state of the specified ADC channels.
  *          This parameter can be: ENABLE or DISABLE. 
  * @retval None 
  */
void ADC_SetConvChannel(ADC_TypeDef *ADCx, uint16_t channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_CHANNEL(channel));

  if (NewState == ENABLE)
  {
    /* start channel0 convertion */
    if (channel & ADC_CHANNEL0)
      ADCx->CTRL0_SET = ADC_Dispatch_Channel0;
    if (channel & ADC_CHANNEL1)
      ADCx->CTRL0_SET = ADC_Dispatch_Channel1;
    if (channel & ADC_CHANNEL2)
      ADCx->CTRL0_SET = ADC_Dispatch_Channel2;
    if (channel & ADC_CHANNEL3)
      ADCx->CTRL0_SET = ADC_Dispatch_Channel3;
    if (channel & ADC_CHANNEL4)
      ADCx->CTRL0_SET = ADC_Dispatch_Channel4;
    if (channel & ADC_CHANNEL5)
      ADCx->CTRL0_SET = ADC_Dispatch_Channel5;
    if (channel & ADC_CHANNEL6)
      ADCx->CTRL0_SET = ADC_Dispatch_Channel6;
    if (channel & ADC_CHANNEL7)
      ADCx->CTRL0_SET = ADC_Dispatch_Channel7; 
    if (channel & ADC_CHANNEL8)
      ADCx->CTRL0_SET = ADC_Dispatch_Channel8;
    if (channel & ADC_CHANNEL9)
      ADCx->CTRL0_SET = ADC_Dispatch_Channel9;
  }else
  {
    /* stop channel0 convertion */
    if (channel & ADC_CHANNEL0)
      ADCx->CTRL0_CLR = ADC_Dispatch_Channel0;
    if (channel & ADC_CHANNEL1)
      ADCx->CTRL0_CLR = ADC_Dispatch_Channel1;
    if (channel & ADC_CHANNEL2)
      ADCx->CTRL0_CLR = ADC_Dispatch_Channel2;
    if (channel & ADC_CHANNEL3)
      ADCx->CTRL0_CLR = ADC_Dispatch_Channel3;
    if (channel & ADC_CHANNEL4)
      ADCx->CTRL0_CLR = ADC_Dispatch_Channel4;
    if (channel & ADC_CHANNEL5)
      ADCx->CTRL0_CLR = ADC_Dispatch_Channel5;
    if (channel & ADC_CHANNEL6)
      ADCx->CTRL0_CLR = ADC_Dispatch_Channel6;
    if (channel & ADC_CHANNEL7)
      ADCx->CTRL0_CLR = ADC_Dispatch_Channel7;
    if (channel & ADC_CHANNEL8)
      ADCx->CTRL0_CLR = ADC_Dispatch_Channel8;
    if (channel & ADC_CHANNEL9)
      ADCx->CTRL0_CLR = ADC_Dispatch_Channel9;
  }
}

/**
  * @brief  Checks whether the specified ADC channel conversion completed interrupt
  *     has occurred or not.
  * @param  ADCx: pointer to an ADC_InitTypeDef structure that contains 
  * @param  channel: ADC channel number,channel0~channel7 
  * @retval  
  */
ITStatus ADC_GetITStatus(ADC_TypeDef *ADCx, uint16_t channel)
{
  ITStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_ADC_CHANNEL(channel));

  /* Get the ADC_IT enable bit status */
  if (channel == ADC_CHANNEL0)
    bitstatus = ADC_ItStatus_Channel0;
  if (channel == ADC_CHANNEL1)
    bitstatus = ADC_ItStatus_Channel1;
  if (channel == ADC_CHANNEL2)
    bitstatus = ADC_ItStatus_Channel2;
  if (channel == ADC_CHANNEL3)
    bitstatus = ADC_ItStatus_Channel3;
  if (channel == ADC_CHANNEL4)
    bitstatus = ADC_ItStatus_Channel4;
  if (channel == ADC_CHANNEL5)
    bitstatus = ADC_ItStatus_Channel5;
  if (channel == ADC_CHANNEL6)
    bitstatus = ADC_ItStatus_Channel6;
  if (channel == ADC_CHANNEL7)
    bitstatus = ADC_ItStatus_Channel7;
  if (channel == ADC_CHANNEL8)
    bitstatus = ADC_ItStatus_Channel8;
  if (channel == ADC_CHANNEL9)
    bitstatus = ADC_ItStatus_Channel9;

  /* Return the ADC_IT status */
  return bitstatus;
}

/**
  * @brief  Clears the ADC channel conversion completed interrupt flags.
  * @param  ADCx: pointer to an ADC_InitTypeDef structure that contains 
  * @param  channel: ADC channel number,channel0~channel7 
  * @retval None 
  */
void ADC_ClearITFlag(ADC_TypeDef *ADCx, uint16_t channel)
{
  /* Check the parameters */
  assert_param(IS_ADC_CHANNEL(channel));

  /* Clear the selected ADC flags */
  if (channel & ADC_CHANNEL0)
    ADCx->CTRL1_CLR = ADC_ItClear_Channel0;
  if (channel & ADC_CHANNEL1)
    ADCx->CTRL1_CLR = ADC_ItClear_Channel1;
  if (channel & ADC_CHANNEL2)
    ADCx->CTRL1_CLR = ADC_ItClear_Channel2;
  if (channel & ADC_CHANNEL3)
    ADCx->CTRL1_CLR = ADC_ItClear_Channel3;
  if (channel & ADC_CHANNEL4)
    ADCx->CTRL1_CLR = ADC_ItClear_Channel4;
  if (channel & ADC_CHANNEL5)
    ADCx->CTRL1_CLR = ADC_ItClear_Channel5;
  if (channel & ADC_CHANNEL6)
    ADCx->CTRL1_CLR = ADC_ItClear_Channel6;
  if (channel & ADC_CHANNEL7)
    ADCx->CTRL1_CLR = ADC_ItClear_Channel7;
  if (channel & ADC_CHANNEL8)
    ADCx->CTRL1_CLR = ADC_ItClear_Channel8;
  if (channel & ADC_CHANNEL9)
    ADCx->CTRL1_CLR = ADC_ItClear_Channel9;
}

/**
  * @brief  Start ADC software trigger conversion when select @ADC_TrigEdge_Software
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure that contains 
  *         the configuration information for the specified ADC peripheral. 
  * @retval None 
  */
void ADC_StartSoftwareTrigConv(ADC_TypeDef *ADCx)
{
  /* start software trigger conversion mode  */
  ADCx->CTRL5_SET = 1 << 30;
}
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT TDO *****END OF FILE****/
