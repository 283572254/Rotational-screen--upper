

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup Y6_system
  * @{
  */  
  
/** @addtogroup Y6_System_Private_Includes
  * @{
  */

#include "Y6_rcc.h"
#include "Y6_wdg.h"

/*******************************************************************************
*  Clock Definitions
*******************************************************************************/


/**
  * @brief  Setup the microcontroller system
  *         Initialize the Embedded Flash Interface, the PLL and update the 
  *         SystemCoreClock variable.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
#if 1
void SystemInit (void)
{    
	
	uint32_t	timeout = 0;
	
  //RCC->OSC12_CTRL = 0x80000062;
	RCC->AHBCLKCTRL0_SET = (1<<AHBCLK_BIT_GPIO) | (1<<AHBCLK_BIT_DMA) | (1<<AHBCLK_BIT_IOCON);
	RCC->SYSAHBCLKDIV = 4;//FPGAÉÏ  96M/2=48M, ASICÉÏ 384M/4=96M

	/* open sys_pll clk */
	RCC->PDRUNCFG = RCC->PDRUNCFG & 0xFFFFFEEF;		//bit4=SYSPLL bit0=EXT12M

	/*set sys_pll clk to 480MHz*/
	RCC->SYSPLLCTRL = RCC_SYSPLLCTRL_FORCELOCK | (1 << 30) | (22 << 0);	//12M*(22+10)=384M		OSC:bit30=0

	while((RCC->SYSPLLSTAT) != RCC_SYSPLLSTAT_LOCK)
	{
		if((timeout++) >= 0x8000)
			break;
	}

 	commonDelay(1000);
	
	/*switch main clk source to syspll_out*/
	RCC->MAINCLKSEL = 1;
	/*make switch available*/
	RCC->MAINCLKUEN = 0;
	RCC->MAINCLKUEN = 1;	
}
#endif

/******************* (C) COPYRIGHT 2013 TDO *****END OF FILE****/
