 

/* Includes ------------------------------------------------------------------*/
#include "Y6_rcc.h"

/** @addtogroup Y6_StdPeriph_Driver
  * @{
  */

/** @defgroup RCC 
  * @brief RCC driver modules
  * @{
  */ 

/** @defgroup RCC_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup RCC_Private_Defines
  * @{
  */

#define RCC_SYSPLLSTATE_TIMEOUT     0x10000
#define RCC_SYSPLLUEN_DISABLE        0
#define RCC_SYSPLLUEN_ENABLE        1
#define RCC_SYSPLLCTRL_CLEAR_Mask    0xFFE0
#define RCC_SYSPLLSTATE_LOCK        1

#define RCC_MAINCLKUEN_DISABLE      0
#define RCC_MAINCLKUEN_ENABLE        1

#define RCC_UARTCLKUEN_DISABLE      0
#define RCC_UARTCLKUEN_ENABLE        1

#define RCC_WDTCLKUEN_DISABLE        0
#define RCC_WDTCLKUEN_ENABLE        1

#define RCC_OUTCLKUEN_DISABLE        0
#define RCC_OUTCLKUEN_ENABLE        1

/**
  * @}
  */

/** @defgroup RCC_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup RCC_Private_Functions
  * @{
  */

/**
  * @brief  Set Peripheral clock on AHB
  * @param  AHBCLK: module clock enable signal bit. 
  *     @arg 1 << AHBCLK_BIT_ROM
  *     ...
  *     @arg 1 << AHBCLK_BIT_UART2
  * @param  NewState: the new state of the clock,ENABLE/DISABLE 
  * @retval None 
  */
void RCC_SetAHBCLK(uint32_t AHBCLK, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RCC->AHBCLKCTRL0_SET = AHBCLK;
  }
  else
  {
    RCC->AHBCLKCTRL0_CLR = AHBCLK;
  }
}

/**
  * @brief  Reset Peripheral module.
  * @param  PRESETCTRL: Module software reset signal bit.
  *     @arg 1 << PRESET_BIT_ROM
  *     ...
  *     @arg 1 << PRESET_BIT_UART2 
  * @param  NewState: the new state of reset,ENABLE/DISABLE. 
  * @retval None 
  */
void RCC_SetPRESETCTRL(uint32_t PRESETCTRL, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RCC->PRESETCTRL0_SET = PRESETCTRL;
  }
  else
  {
    RCC->PRESETCTRL0_CLR = PRESETCTRL;
  }
}

/**
  * @brief  Reset Peripheral clock on AHB
  * @param  AHBCLK: module clock enable signal bit. 
  *     @arg 1 << AHBCLK_BIT_ROM
  *     ...
  *     @arg 1 << AHBCLK_BIT_UART2
  * @retval None 
  */
void RCC_ResetAHBCLK(uint32_t AHBCLK)
{
  RCC_SetAHBCLK(AHBCLK, ENABLE);
  RCC_SetPRESETCTRL(AHBCLK, DISABLE);
  RCC_SetPRESETCTRL(AHBCLK, ENABLE);
}

/**
  * @brief  Select MAIN Clock Source 
  * @param  RCC_MAINCLKSource: specifies MAIN Clock Source .
  *   This parameter can be the following values:
  *     @arg RCC_MAINCLK_SOURCE_12MIRC
  *     @arg RCC_MAINCLK_SOURCE_SYSPLL
  *     @arg RCC_MAINCLK_SOURCE_12MOSC
  *     @arg RCC_MAINCLK_SOURCE_10KIRC
  *
  * @retval None
  */
void RCC_MAINCLKSel(uint8_t RCC_MAINCLKSource)
{
  assert_param(IS_RCC_MAINCLK_SOURCE(RCC_MAINCLKSource));
  RCC->MAINCLKSEL = RCC_MAINCLKSource;
  RCC->MAINCLKUEN = RCC_MAINCLKUEN_DISABLE;
  RCC->MAINCLKUEN = RCC_MAINCLKUEN_ENABLE;  
}

/**
  * @brief  Select UART Clock Source 
  * @param  RCC_UARTCLKSource: specifies UART Clock Source .
  *   This parameter can be the following values:
  *     @arg RCC_UARTCLK_SOURCE_12MIRC
  *     @arg RCC_UARTCLK_SOURCE_SYSPLL
  *     @arg RCC_UARTCLK_SOURCE_12MOSC
  *     @arg RCC_UARTCLK_SOURCE_10KIRC
  * @retval None
  */
void RCC_UARTCLKSel(uint8_t RCC_UARTCLKSource)
{
  assert_param(IS_RCC_UARTCLK_SOURCE(RCC_UARTCLKSource));
  RCC->UARTCLKSEL = RCC_UARTCLKSource;
  RCC->UARTCLKUEN = RCC_UARTCLKUEN_DISABLE;
  RCC->UARTCLKUEN = RCC_UARTCLKUEN_ENABLE;
}

/**
  * @brief  Select OUT Clock Source 
  * @param  RCC_OUTCLKSource: specifies OUT Clock Source .
  *   This parameter can be the following values:
  *     @arg RCC_OUTCLK_SOURCE_12MIRC
  *     @arg RCC_OUTCLK_SOURCE_SYSPLL
  *     @arg RCC_OUTCLK_SOURCE_10KIRC
  *     @arg RCC_OUTCLK_SOURCE_12MOSC
  *     @arg RCC_OUTCLK_SOURCE_32KOSC
  *     @arg RCC_OUTCLK_SOURCE_USBPLL
  * @retval None
  */
void RCC_OUTCLKSel(uint8_t RCC_OUTCLKSource)
{
  assert_param(IS_RCC_OUTCLK_SOURCE(RCC_OUTCLKSource));
  RCC->OUTCLKSEL = RCC_OUTCLKSource;
  RCC->OUTCLKUEN = RCC_OUTCLKUEN_DISABLE;
  RCC->OUTCLKUEN = RCC_OUTCLKUEN_ENABLE;  
}

/**
  * @brief  Select WDT Clock Source 
  * @param  RCC_WDTCLKSource: specifies WDT Clock Source .
  *   This parameter can be the following values:
  *     @arg RCC_WDTCLK_SOURCE_12MIRC
  *     @arg RCC_WDTCLK_SOURCE_SYSPLL
  *     @arg RCC_WDTCLK_SOURCE_12MOSC
  *     @arg RCC_WDTCLK_SOURCE_10KIRC
  * @retval None
  */
void RCC_WDTCLKSel(uint8_t RCC_WDTCLKSource)
{
  assert_param(IS_RCC_WDTCLK_SOURCE(RCC_WDTCLKSource));
  RCC->WDTCLKSEL = RCC_WDTCLKSource;
  RCC->WDTCLKUEN = RCC_WDTCLKUEN_DISABLE;
  RCC->WDTCLKUEN = RCC_WDTCLKUEN_ENABLE;
}


/**
  * @brief  Set Clock divider factor .
  * @param  RCC_Peripheral: specifies the Peripheral.
  *   This parameter can be one of the following values:
  *     @arg RCC_CLOCKFREQ_SYSAHBCLK  
  *     @arg RCC_CLOCKFREQ_UART0CLK      
  *     @arg RCC_CLOCKFREQ_UART1CLK      
  *     @arg RCC_CLOCKFREQ_UART2CLK      
  *     @arg RCC_CLOCKFREQ_SYSTICKCLK      
  *     @arg RCC_CLOCKFREQ_QSPICLK        
  *     @arg RCC_CLOCKFREQ_WDTCLK      
  *     @arg RCC_CLOCKFREQ_CLKOUTCLK    
  *     @arg RCC_CLOCKFREQ_USBCLK    
  *     @arg RCC_CLOCKFREQ_ADCCLK    
  *     @arg RCC_CLOCKFREQ_PWMCLK    
  * @param  RCC_CLKDIV: specifies the Clock divider factor.
  *   This parameter can be RCC_CLKDIV_x where x:[0,255].
  * @retval None
  */
void RCC_SETCLKDivider(uint32_t RCC_Peripheral_Clock, uint8_t RCC_CLKDIV)
{
  assert_param(IS_RCC_CLKDIV_PER(RCC_Peripheral_Clock));
  (*((__IO uint8_t *)(RCC_BASE + RCC_Peripheral_Clock))) = RCC_CLKDIV;    
}

/**
  * @brief  Configures the SYSPLL multiplication factor .
  * @param  RCC_SYSPLL: specifies the SYSPLL multiplication factor.
  *         PLL_CLK = 12MHZ *(RCC_SYSPLL+10)
  *     @arg RCC_SYSPLL_VAL_120
  *     @arg RCC_SYSPLL_VAL_130
  *     @arg RCC_SYSPLL_VAL_144
  *     @arg RCC_SYSPLL_VAL_156
  *     @arg RCC_SYSPLL_VAL_168
  *     @arg RCC_SYSPLL_VAL_180
  *     @arg RCC_SYSPLL_VAL_192
  *     @arg RCC_SYSPLL_VAL_204
  *     @arg RCC_SYSPLL_VAL_216
  *     @arg RCC_SYSPLL_VAL_228
  *     @arg RCC_SYSPLL_VAL_240
  * @retval None
  */
void RCC_SYSPLLConfig( uint32_t RCC_SYSPLL)
{
  uint32_t tmpreg = 0;
  uint32_t timeout = 0;
  assert_param(IS_RCC_SYSPLL_VAL(RCC_SYSPLL));

  tmpreg = RCC->SYSPLLCTRL;
  tmpreg &= RCC_SYSPLLCTRL_CLEAR_Mask;
  tmpreg |= RCC_SYSPLL | RCC_SYSPLLCTRL_FORCELOCK;
  RCC->SYSPLLCTRL = tmpreg;

  while((RCC->SYSPLLSTAT) != RCC_SYSPLLSTATE_LOCK)
  {
    if((timeout++) >= RCC_SYSPLLSTATE_TIMEOUT)
      break;
  }
}

/**
  * @brief  Capture PIO value whether it is 1 or 0.
  * @param  RCC_PortNum: specifies the number of Port.
  *   This parameter can be RCC_PortNum_x where x:[0,1].
  * @param  RCC_PinNum: specifies the number of Pin.
  *   This parameter can be RCC_PinNum_x where x:[0,7].
  * @retval The new state of PIO (SET(1) or RESET(0)).
  */
FlagStatus RCC_CAPPIO(uint32_t RCC_PortNum, uint32_t RCC_PinNum)
{
  FlagStatus bitstatus = RESET;
  assert_param(IS_RCC_CAPPIO_PortNum(RCC_PortNum));
  assert_param(IS_RCC_CAPPIO_PinNum(RCC_PinNum));

  if(((RCC->PIOPORCAP0) & (1<<(RCC_PinNum + (RCC_PortNum * 8)))) == 0)
    bitstatus = RESET;
  else
    bitstatus = SET;

  return bitstatus;   
}

/**
  * @brief  Controls the start logic inputs of GPIO0,1.
  * @param  RCC_GPIOxPINy: specifies the number of pin.
  *   This parameter can be RCC_GPIOx_PINy where x:[0,1] y[0,7].
  * @param  RCC_APRP_MODE: specifies a falling or rising edge.
  *   This parameter can be one of the following values:
  *     @arg RCC_APRP_MODE_RisingEdge
  *     @arg RCC_APRP_MODE_FallingEdge
  * @retval None
  */
void RCC_APRPConfig(uint32_t RCC_GPIOxPINy, uint32_t RCC_APRP_MODE)
{
  assert_param(IS_RCC_GPIOX_PINY(RCC_GPIOxPINy));
  assert_param(IS_RCC_APRP_MODE(RCC_APRP_MODE));
  if(RCC_APRP_MODE == RCC_APRP_MODE_RisingEdge)
  {
    RCC->STARTAPRP0 |= (1 << RCC_GPIOxPINy);
  }
  else
  {
    RCC->STARTAPRP0 &= ~(1 << RCC_GPIOxPINy);
  }
}

/**
  * @brief  Enable start signal for start logic input GPIO0,1.
  * @param  RCC_GPIOxPINy: specifies the number of pin.
  *   This parameter can be RCC_GPIOx_PINy where x:[0,1] y[0,7]  .
  * @param  NewState: new state of the logic input. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_ERPCmd(uint32_t RCC_GPIOxPINy, FunctionalState NewState)
{
  assert_param(IS_RCC_GPIOX_PINY(RCC_GPIOxPINy));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if(NewState != DISABLE)
  {
    RCC->STARTERP0 |= (1 << RCC_GPIOxPINy);

  }
  else
  {
    RCC->STARTERP0 &= ~(1 << RCC_GPIOxPINy);

  }
}

/**
  * @brief  Start signal reset for start logic input GPIO0,1.
  * @param  RCC_GPIOxPINy: specifies the number of pin.
  *   This parameter can be RCC_GPIOx_PINy where x:[0,1] y[0,7]  .
  * @retval None
  */
void RCC_RSRPCmd(uint32_t RCC_GPIOxPINy)
{
  assert_param(IS_RCC_GPIOX_PINY(RCC_GPIOxPINy));
  RCC->STARTRSRP0 |= (1 << RCC_GPIOxPINy);

}

/**
  * @brief  Checks whether the logic input flag is set or not.
  * @param  RCC_GPIOxPINy: specifies the number of pin.
  *   This parameter can be RCC_GPIOx_PINy where x:[0,1] y[0,7]  .
  * @retval The new state of GPIO_PIN logic input (SET or RESET).
  */
FlagStatus RCC_GETSRP(uint32_t RCC_GPIOxPINy)
{
  FlagStatus bitstatus = RESET;
  assert_param(IS_RCC_GPIOX_PINY(RCC_GPIOxPINy));
  
  if((RCC->STARTSRP0 & (1 << RCC_GPIOxPINy)) != 0)
    bitstatus = SET;
  else
    bitstatus = RESET;

  return bitstatus;  
}

/**
  * @brief  Configures the state the chip must enter when the Deep-sleep mode is asserted by the ARM.
  * @param  RCC_Analog_Block: specifies Module which will be power on or down.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_PDCFG_EXT12M        
  *     @arg RCC_PDCFG_10KIRC        
  *     @arg RCC_PDCFG_RTC          
  *     @arg RCC_PDCFG_ADC0      
  *     @arg RCC_PDCFG_SYSPLL      
  *     @arg RCC_PDCFG_BOD        
  *     @arg RCC_PDCFG_BOR        
  *     @arg RCC_PDCFG_12MIRC      
  *     @arg RCC_PDCFG_USB      
  *     @arg RCC_PDCFG_32KOSC      
  *
  * @param  PD_MODE: new mode of the Oscillator.
  *   This parameter can be one of the following values:
  *     @arg RCC_PDCFG_POWER_ON
  *     @arg RCC_PDCFG_POWER_DOWN
  * @retval None
  */
void RCC_PDSLEEPConfig(uint16_t RCC_Analog_Block, uint8_t PD_MODE)
{
  assert_param(IS_RCC_PDCFG_ANALOG_BLOCK(RCC_Analog_Block));
  assert_param(IS_RCC_PDCFG_MODE(PD_MODE));
  if(PD_MODE != RCC_PDCFG_POWER_DOWN)
  {
    RCC->PDSLEEPCFG &= ~RCC_Analog_Block;
  }
  else
  {
    RCC->PDSLEEPCFG |= RCC_Analog_Block;
  }
}

/**
  * @brief  Configures the state the chip must enter when it is waking up from Deep-sleep mode.
  * @param  RCC_Analog_Block: specifies Module which will be power on or down.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_PDCFG_EXT12M        
  *     @arg RCC_PDCFG_10KIRC        
  *     @arg RCC_PDCFG_RTC          
  *     @arg RCC_PDCFG_ADC0      
  *     @arg RCC_PDCFG_SYSPLL      
  *     @arg RCC_PDCFG_BOD        
  *     @arg RCC_PDCFG_BOR        
  *     @arg RCC_PDCFG_12MIRC      
  *     @arg RCC_PDCFG_USB      
  *     @arg RCC_PDCFG_32KOSC      
  *
  * @param  PD_MODE: new mode of the Oscillator.
  *   This parameter can be one of the following values:
  *     @arg RCC_PDCFG_POWER_ON
  *     @arg RCC_PDCFG_POWER_DOWN
  * @retval None
  */
void RCC_PDAWAKEConfig(uint16_t RCC_Analog_Block, uint8_t PD_MODE)
{
  assert_param(IS_RCC_PDCFG_ANALOG_BLOCK(RCC_Analog_Block));
  assert_param(IS_RCC_PDCFG_MODE(PD_MODE));
  if(PD_MODE != RCC_PDCFG_POWER_DOWN)
  {
    RCC->PDAWAKECFG &= ~RCC_Analog_Block;
  }
  else
  {
    RCC->PDAWAKECFG |= RCC_Analog_Block;
  }
}

/**
  * @brief  Configures the power to the various analog blocks.
  * @param  RCC_Analog_Block: specifies Module which will be power on or down.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_PDCFG_EXT12M        
  *     @arg RCC_PDCFG_10KIRC        
  *     @arg RCC_PDCFG_ADC0      
  *     @arg RCC_PDCFG_SYSPLL      
  *     @arg RCC_PDCFG_BOD        
  *     @arg RCC_PDCFG_BOR        
  *     @arg RCC_PDCFG_RTC          
  *     @arg RCC_PDCFG_12MIRC      
  *     @arg RCC_PDCFG_CMP0
  *     @arg RCC_PDCFG_CMP1
  *     @arg RCC_PDCFG_USB      
  *
  * @param  PD_MODE: new mode of the Oscillator.
  *   This parameter can be one of the following values:
  *     @arg RCC_PDCFG_POWER_ON
  *     @arg RCC_PDCFG_POWER_DOWN
  * @retval None
  */
void RCC_PDRUNConfig(uint16_t RCC_Analog_Block, uint8_t PD_MODE)
{
  assert_param(IS_RCC_PDCFG_ANALOG_BLOCK(RCC_Analog_Block));
  assert_param(IS_RCC_PDCFG_MODE(PD_MODE));
  if(PD_MODE != RCC_PDCFG_POWER_DOWN)
  {
    RCC->PDRUNCFG &= ~RCC_Analog_Block;
  }
  else
  {
    RCC->PDRUNCFG |= RCC_Analog_Block;
  }
}

/**
  * @brief  Set low power mode:sleep/power-down.
  * @param  LOW_POWER_MODE: low power mode. 
  *   This parameter can be one of the following values:
  *       @arg LOW_POWER_SLEEP_MODE
  *       @arg LOW_POWER_POWER_DOWN_MODE
  * @retval NOne 
  */
void RCC_LowPowerCmd(uint8_t LOW_POWER_MODE)
{
  assert_param(IS_LOW_POWER_MODE(LOW_POWER_MODE));
  if (LOW_POWER_MODE == LOW_POWER_POWER_DOWN_MODE)
  {
    RCC->PCON |= RCC_DPDEN;
  }
  else
  {
    RCC->PCON &= ~RCC_DPDEN;
  }
}

/**
  * @brief  Checks whether the specified RCC flag is set or not.
  * @param  RCC_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg RCC_SYSRSTSTATE_POR
  *     @arg RCC_SYSRSTSTATE_EXERSTN
  *     @arg RCC_SYSRSTSTATE_WDT
  *     @arg RCC_SYSRSTSTATE_BOD     
  *     @arg RCC_SYSRSTSTATE_SYSRST                        
  * @retval The new state of RCC_FLAG (SET or RESET).
  */
FlagStatus RCC_GetSYSRSTFlagStatus(uint16_t RCC_FLAG)
{
  FlagStatus bitstatus = RESET;
  assert_param(IS_RCC_SYSRST_FLAG(RCC_FLAG));
    if ((RCC->SYSRSTSTAT & RCC_FLAG)!= (uint8_t)RESET)
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
  * @brief  Checks whether the specified RCC flag is set or not.
  * @param  RCC_FLAG: specifies the flag to check. 
  *   This parameter can be one of the following values:
  *     @arg RCC_DPDEN
  *     @arg RCC_SLEEPFLAG
  *     @arg RCC_DPDFLAG
  * @retval  The new state of RCC_FLAG (SET or RESET).
  */
FlagStatus RCC_GetPCONFlagStatus(uint16_t RCC_FLAG)
{
  FlagStatus bitstatus = RESET;
  assert_param(IS_RCC_PCON_FLAG(RCC_FLAG));
    if ((RCC->PCON & RCC_FLAG)!= (uint16_t)RESET)
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
  * @brief  Clears the RCC reset flags.
  * @param  RCC_FLAG: specifies the flag to clear.
  *   This parameter can be one of the following values:
  *     @arg RCC_SYSRSTSTATE_POR
  *     @arg RCC_SYSRSTSTATE_EXERSTN
  *     @arg RCC_SYSRSTSTATE_WDT
  *     @arg RCC_SYSRSTSTATE_BOD     
  *     @arg RCC_SYSRSTSTATE_SYSRST                        
  * @retval None
  */
void RCC_ClearSYSRSTFlag(uint16_t RCC_FLAG)
{
  assert_param(IS_RCC_SYSRST_FLAG(RCC_FLAG));
  RCC->SYSRSTSTAT |= RCC_FLAG;
}

/**
  * @brief  Clears the RCC power config flags.
  * @param  RCC_FLAG: specifies the flag to clear.
  *   This parameter can be one of the following values:
  *     @arg RCC_SLEEPFLAG
  *     @arg RCC_DPDFLAG
  * @retval None
  */
void RCC_ClearPCONFlag(uint16_t RCC_FLAG)
{
  assert_param(IS_RCC_PCON_FLAG(RCC_FLAG));
  RCC->PCON |= RCC_FLAG;
}

/**
  * @brief  Set the systick Calibration.
  * @param  SystickCalibration: specifies the Calibration.
  *   This parameter can be any value of 26 bits data.
  * @retval None
  */
void RCC_SetSystickCal(uint32_t SystickCalibration)
{
  assert_param(IS_RCC_SYSTICK_CAL(SystickCalibration));
  RCC->SYSTICKCAL = SystickCalibration;
}

/**
  * @brief  Configures the BOD interrupt electrical level.
  * @param  BODINTVal: specifies BOD interrupt electrical level.
  *   This parameter can be one of the following values:
  *     @arg RCC_BODINT_VAL_2_56
  *     @arg RCC_BODINT_VAL_2_65
  *     @arg RCC_BODINT_VAL_2_74
  *     @arg RCC_BODINT_VAL_2_85
  * @param  NewState: new mode of the BOD reset.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_BODConfig(uint8_t BODINTVal, FunctionalState NewState)
{    
  uint8_t tmpreg;
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_RCC_BODINT_VAL(BODINTVal));

  tmpreg = RCC->BODCTRL;
  tmpreg &= RCC_BODCTRL_CLEAR_Mask;
  tmpreg |= BODINTVal;
  
  if(NewState != DISABLE)
  {
    RCC->BODCTRL |= RCC_BODRSTENA_SET_Mask;  
  }
  else
  {
    RCC->BODCTRL &= RCC_BODRSTENA_RESET_Mask;  
  }
}

/**
  * @brief  Get clock frequence
  * @param  RCC_Clocks: specifies the clock.
  *   This parameter can be one of the following values:
  *     @arg RCC_CLOCKFREQ_SYSAHBCLK  
  *     @arg RCC_CLOCKFREQ_UART0CLK      
  *     @arg RCC_CLOCKFREQ_UART1CLK      
  *     @arg RCC_CLOCKFREQ_UART2CLK      
  *     @arg RCC_CLOCKFREQ_SYSTICKCLK      
  *     @arg RCC_CLOCKFREQ_WDTCLK      
  *     @arg RCC_CLOCKFREQ_CLKOUTCLK    
  * @retval the clock frequence.
  */
uint32_t RCC_GetClocksFreq(uint32_t RCC_Clocks)
{
   uint32_t tmpclk, syspll, mainclk, hclk, uartclk, wdtclk, outclk;
  uint8_t mainclk_sel, uartclk_sel, wdtclk_sel, outclk_sel;
  
  mainclk_sel = RCC->MAINCLKSEL;
  uartclk_sel = RCC->UARTCLKSEL;
  wdtclk_sel = RCC->WDTCLKSEL;

#ifdef EXECUTE_ON_FPGA
  syspll = 96000000;
#else
  syspll = ((RCC->SYSPLLCTRL & RCC_SYSPLLCTRL_FREQ) + 10) * 12000000;
#endif
  if (mainclk_sel == RCC_MAINCLK_SOURCE_12MIRC)
    mainclk = 12000000;  
  else if (mainclk_sel == RCC_MAINCLK_SOURCE_SYSPLL)
    mainclk  = syspll;
  else if (mainclk_sel == RCC_MAINCLK_SOURCE_12MOSC)
    mainclk  = 12000000;
  else if (mainclk_sel == RCC_MAINCLK_SOURCE_10KIRC)
    mainclk  = 10000;

  hclk = mainclk / RCC->SYSAHBCLKDIV;

  if (RCC_Clocks == RCC_CLOCKFREQ_SYSAHBCLK)
    tmpclk = hclk;

  else if ((RCC_Clocks == RCC_CLOCKFREQ_UART0CLK) || (RCC_Clocks == RCC_CLOCKFREQ_UART1CLK)|| (RCC_Clocks == RCC_CLOCKFREQ_UART2CLK))
  {
    if ((*((__IO uint8_t *)(RCC_BASE + RCC_Clocks))) == 0)
      return 0;

    if (uartclk_sel == RCC_UARTCLK_SOURCE_12MIRC)
    {
      uartclk = 12000000 / (*((__IO uint8_t *)(RCC_BASE + RCC_Clocks)));
    }
    else if (uartclk_sel == RCC_UARTCLK_SOURCE_SYSPLL)
    {
      uartclk = syspll / (*((__IO uint8_t *)(RCC_BASE + RCC_Clocks)));
    }
    else if (uartclk_sel == RCC_UARTCLK_SOURCE_12MOSC)
    {
      uartclk = 12000000 / (*((__IO uint8_t *)(RCC_BASE + RCC_Clocks)));
    }
    else if (uartclk_sel == RCC_UARTCLK_SOURCE_10KIRC)
    {
      uartclk = 10000 / (*((__IO uint8_t *)(RCC_BASE + RCC_Clocks)));
    }

    tmpclk = uartclk;
  }
  else if (RCC_Clocks == RCC_CLOCKFREQ_WDTCLK)
  {
    if (RCC->WDTCLKDIV == 0)
      return 0;

    if (wdtclk_sel == RCC_WDTCLK_SOURCE_12MIRC)
      wdtclk = 12000000 / RCC->WDTCLKDIV;
    else if (wdtclk_sel == RCC_WDTCLK_SOURCE_SYSPLL)
      wdtclk = syspll / RCC->WDTCLKDIV;
    else if (wdtclk_sel == RCC_WDTCLK_SOURCE_12MOSC)
      wdtclk = 12000000 / RCC->WDTCLKDIV;

    tmpclk = wdtclk;  
  }
  else if (RCC_Clocks == RCC_CLOCKFREQ_CLKOUTCLK)
  {
    if (RCC->OUTCLKDIV == 0)
      return 0;

    if (outclk_sel == RCC_OUTCLK_SOURCE_12MIRC)
      outclk = 12000000 / RCC->OUTCLKDIV;
    else if (outclk_sel == RCC_OUTCLK_SOURCE_SYSPLL)
      outclk = mainclk / RCC->OUTCLKDIV;
    else if (outclk_sel == RCC_OUTCLK_SOURCE_10KIRC)
      outclk = 10000 / RCC->OUTCLKDIV;
    else if (outclk_sel == RCC_OUTCLK_SOURCE_12MOSC)
      outclk = 12000000 / RCC->OUTCLKDIV;
    else if (outclk_sel == RCC_OUTCLK_SOURCE_32KOSC)
      outclk = 32000 / RCC->OUTCLKDIV;
    else if (outclk_sel == RCC_OUTCLK_SOURCE_USBPLL)
      outclk = 48000000 / RCC->OUTCLKDIV;

    tmpclk = outclk;  
  }
  else if (outclk_sel == RCC_CLOCKFREQ_SYSTICKCLK)
  {
    if ((*((__IO uint8_t *)(RCC_BASE + RCC_Clocks))) == 0)
      return 0;

    tmpclk = mainclk / (*((__IO uint8_t *)(RCC_BASE + RCC_Clocks)));
  }
  else
  { 
    /*can't get clock*/
    while(1);
  }

  return tmpclk;
}

/**
  * @brief  Configure seed to generate random number.
  * @param  seed: specifies seed value.
  * @retval none. 
  */
void RCC_ConfRandomSeed(uint32_t seed)
{
  RCC->PRNG_DEBUG_SEED = seed;
  RCC->PRNG_DEBUG_EN = 0x1;
}

/**
  * @brief  Get random value.
  * @retval one random value.  
  */
uint32_t RCC_GetRandomData(void)
{
  while((RCC->PRNG_STATUS & 0x1) != 0x1);
  return RCC->PRNG_DATA;
}

/**
  * @brief  Set sleep mode.
  * @param  mode: specifies sleep mode value 
  *   This parameter can be one of the following values:
  *     @arg SM_SLEEP: sleep mode  
  *     @arg SM_DEEPSLEEP: deep sleep mode  
  *     @arg SM_POWERDOWN: power down mode  
  * @retval none. 
  */
void goSleep(SleepMode mode)
{
  if(mode==SM_SLEEP){
    uint32_t scr = *((uint32_t*)0xE000ED10);
    scr &= 0xFFFFFFFB;
    *((uint32_t*)0xE000ED10) = scr;

    RCC->PCON = 0x900;		//0x900«ÂµÙSLEEPFLAG∫ÕDPDFLAG
  }else if(mode==SM_DEEPSLEEP){
    uint32_t scr = *((uint32_t*)0xE000ED10);
    scr |= 0x00000004;
    *((uint32_t*)0xE000ED10) = scr;

    RCC->PCON = 0x900;
  }else if(mode==SM_POWERDOWN){
    uint32_t scr = *((uint32_t*)0xE000ED10);
    scr |= 0x00000004;
    *((uint32_t*)0xE000ED10) = scr;
    RCC->PCON = 0x902;		//…Ë÷√DPDEN
  }
  commonDelay(100);
  //__asm("wfi");
  __WFI();
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

/******************* (C) COPYRIGHT 2010 TDO *****END OF FILE****/

