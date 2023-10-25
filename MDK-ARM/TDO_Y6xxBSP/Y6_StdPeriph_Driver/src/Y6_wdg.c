 

/* Includes ------------------------------------------------------------------*/

#include "Y6.h"
#include "Y6_rcc.h"
#include "Y6_wdg.h"

/** @addtogroup Y6_StdPeriph_Driver
  * @{
  */

/** @defgroup WDG 
  * @brief WDG driver modules
  * @{
  */ 

/** @defgroup WDG_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup WDG_Private_Defines
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup WDG_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup WDG_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup WDG_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup WDG_Private_Functions
  * @{
  */

/**
  * @brief  Open or close the WDT Clock.
  * @param  NewState: new state of WDT Clock. 
  *   This parameter can be: ENABLE or DISABLE. 
  * @retval None
  */
void WDT_CLKSET(FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		/* Open WDT Clock */
		RCC_SetAHBCLK(1<<AHBCLK_BIT_WDT,ENABLE);
	}
	else
	{
		/* Close WDT Clock */
		RCC_SetAHBCLK(1<<AHBCLK_BIT_WDT,DISABLE);
	}
}

/**
  * @brief  Deinitializes the WDT peripheral registers to their default reset values.
  * @param  None. 
  * @retval None
  */
void WDT_Reset(void)
{
	RCC_ResetAHBCLK(1<<PRESET_BIT_WDT);
}

/**
  * @brief  Sets WDG mode.
  * @param  Mode: specifies the WDG work mode.
  *   This parameter can be one of the following values.
  *     @arg WDG_SETMODE_DEBUG: Debug mode.
  *     @arg WDG_SETMODE_IT: Watchdog interrupt mode.
  *     @arg WDG_SETMODE_RESET: Watchdog reset mode.
  * @retval None
  */
void WDG_SetMode(uint32_t Mode)
{
	/* Check the parameters */
	assert_param(IS_WDG_MODE(Mode));
	WDG->WDMOD = Mode;
}


/**
  * @brief  Sets WDG Reload value.
  * @param  Reload: specifies the IWDG Reload value.
  *   This parameter must be a number between 0 and 0x0FFF.
  * @retval None
  */
void WDG_SetReload(uint32_t Reload)
{
	/* Check the parameters */
	assert_param(IS_WDG_RELOAD(Reload));
	WDG->WDTC = Reload;
}


/**
  * @brief  Reloads WDG counter with value defined in the WDTC register
  * @param  None
  * @retval None
  */
void WDG_ReloadCounter(void)
{
	WDG->WDFEED = (uint32_t)0xAA;
	WDG->WDFEED = (uint32_t)0x55;
}

/**
  * @brief  Checks whether the specified WDG flag is set or not.
  * @param  WDG_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg WDG_FLAG_WDTOF: Watchdog timeout flag.
  *     @arg WDG_FLAG_WDINT: Watchdog interrupt flag.
  * @retval The new state of WDG_FLAG (SET or RESET).
  */
FlagStatus WDG_GetFlagStatus(uint32_t WDG_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_WDG_FLAG(WDG_FLAG));
  if ((WDG->WDMOD & WDG_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the flag status */
  return bitstatus;
}

/**
  * @brief  Clear the specified WDG timeout flag.
  * @param  None
  * @retval None.
  */
void WDG_ClearTimeOutFlag(void)
{
	WDG->WDMOD &= ~WDG_FLAG_WDTOF;
}

/**
  * @brief  Clear the specified WDG Interrupt flag.
  * @param  None
  * @retval None
  */
void WDG_ClearITFlag(void)
{
	WDG->WDMOD &= ~WDG_FLAG_WDINT;
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
