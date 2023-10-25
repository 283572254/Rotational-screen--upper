
/* Includes ------------------------------------------------------------------*/
#include "misc.h"
#include "Y6_cmp.h"
#include "Y6_rcc.h"
/** @addtogroup Y6_StdPeriph_Driver
  * @{
  */

/** @defgroup CMP 
  * @brief CMP driver modules
  * @{
  */

/** @defgroup CMP_Private_Functions
  * @{
  */

/**
  * @brief  Open or close the CMP Clock.
  * @param  NewState: new state of CMP Clock. 
  *   This parameter can be: ENABLE or DISABLE. 
  * @retval None
  */
void CMP_CLKSET(FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		/* Open CMP Clock */
		RCC_SetAHBCLK(1 << AHBCLK_BIT_CMP, ENABLE);
	}
	else
	{
		/* Close CMP Clock */
		RCC_SetAHBCLK(1 << AHBCLK_BIT_CMP, DISABLE);
	}
}

/**
  * @brief  Enable CMP clock and Reset CMP peripheral registers to 
	* 				their default reset values.
  * @retval None.  
  */
void CMP_Reset(void)
{
	RCC_ResetAHBCLK(1<<PRESET_BIT_CMP);
}

/**
  * @brief  Enable/Disable CMP interrupt.
  * @param  channel: CMP channel
	* 				@arg CMP_Channel_0: cmp0 
	*					@arg CMP_Channel_1: cmp1
  * @param  NewState:  set ENABLE/DISABLE to enable/disable.
  * @retval None. 
  */
void CMP_ITConfig(uint8_t channel,FunctionalState NewState)
{
	assert_param(IS_CMP_CHANNEL(channel));
	if(channel & CMP_Channel_0)
	{
		if(NewState == ENABLE)
			CMP->CTRL0_SET = CMP_CTRL0_CMPIE;
		else
			CMP->CTRL0_CLR = CMP_CTRL0_CMPIE;
	}
	
	if(channel & CMP_Channel_1)
	{
		if(NewState == ENABLE)
			CMP->CTRL1_SET = CMP_CTRL1_CMPIE;
		else
			CMP->CTRL1_CLR = CMP_CTRL1_CMPIE;
	}
}

/**
  * @brief  Initialize the CMP peripheral according to the specified 
  *         parameters in the CMP_InitStruct.
  * @param  CMP_InitStruct: pointer to a CMP_InitTypeDef structure that contains 
  *         the configuration information for the specified CMP peripheral. 
  * @retval None 
  */
void CMP_Init(CMP_InitTypeDef* CMP_InitStruct)
{
	uint32_t tmpreg = 0;
	NVIC_InitTypeDef NVIC_InitStruct;
	assert_param(IS_CMP_CHANNEL(CMP_InitStruct->Channel));

	RCC_PDRUNConfig(RCC_PDRUNCFG_CMP0_PD, RCC_PDCFG_POWER_ON);
	RCC_PDRUNConfig(RCC_PDRUNCFG_CMP1_PD, RCC_PDCFG_POWER_ON);
	CMP_Reset();
	CMP_CLKSET(ENABLE);

	if (CMP_InitStruct->Hysen == ENABLE)
		tmpreg |= CMP_CTRL0_HYSEN;
	if (CMP_InitStruct->SelectNegitave == ENABLE)
		tmpreg |= CMP_CTRL0_SELNG;
	tmpreg |= CMP_CTRL0_CMPEN;

	if (CMP_InitStruct->Channel & CMP_Channel_0)
	{
		PIO1->PIN24 = 0x0080;
		if (tmpreg & CMP_CTRL0_SELNG)
			PIO1->PIN25 = 0x0080;
		CMP->CTRL0_SET = tmpreg;
	}
	if (CMP_InitStruct->Channel & CMP_Channel_1)
	{
		PIO1->PIN26 = 0x0080;
		if (tmpreg & CMP_CTRL1_SELNG)
			PIO1->PIN27 = 0x0080;
		CMP->CTRL1_SET = tmpreg;
	}

	NVIC_InitStruct.NVIC_IRQChannel = CMP_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPriority = 2;
	NVIC_Init(&NVIC_InitStruct);
	CMP_ITConfig(CMP_InitStruct->Channel, ENABLE);
}

/**
  * @brief  Get the interrupt flag of the CMP comparison result.
  * @param  channel: CMP channel
	* 				@arg CMP_Channel_0: cmp0 
	*					@arg CMP_Channel_1: cmp1
  * @retval the state of ITFlag, SET or RESET.
  */
ITStatus CMP_GetITStatus(uint8_t channel)
{
	if(channel == CMP_Channel_0)
		return (ITStatus)(CMP->STATUS & CMP_STATUS_FLAG0);
	else
		return (ITStatus)(CMP->STATUS & CMP_STATUS_FLAG1);
}

/**
  * @brief  Clear the interrupt flag of the CMP comparison result.
  * @param  channel: CMP channel
	* 				@arg CMP_Channel_0: cmp0 
	*					@arg CMP_Channel_1: cmp1 
  * @retval None 
  */
void CMP_ClearITFlag(uint8_t channel)
{
	assert_param(IS_CMP_CHANNEL(channel));
	if(channel & CMP_Channel_0)
		CMP->STATUS_SET = CMP_STATUS_FLAG0;
	if(channel & CMP_Channel_1)
		CMP->STATUS_SET = CMP_STATUS_FLAG1;
}

/**
  * @brief  Get CMP Compare result.
  * @param  channel: CMP channel
	* 				@arg CMP_Channel_0: cmp0 
	*					@arg CMP_Channel_1: cmp1  
  * @retval 1: Vpos > Vneg,0: Vpos <= Vneg 
  */
uint8_t CMP_GetCompareResult(uint8_t channel)
{
	if(channel == CMP_Channel_0)
		return (CMP->STATUS & CMP_STATUS_CO0) != 0;
	else
		return (CMP->STATUS & CMP_STATUS_CO1) != 0;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2013 TDO *****END OF FILE****/
