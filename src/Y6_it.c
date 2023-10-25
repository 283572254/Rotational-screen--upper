
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "Y6_it.h"
#include "Y6.h"
#include "Y6_tim.h"
#include "Y6_gpio.h"
#include "Y6_uart.h"
#include "SystemUart.h"
#include "guiFunc.h"
#include "comInterface.h"
#include "Y6_include_conf.h"
#include "SystemHeart.h"
#include "guiFunc.h"
#include "guiConfig.h"
#include "ENCODER.h"

extern char Encoder_counter;
	
int circle_count;

uint8_t time=0;

void commonDelay(volatile unsigned long delay)
{
	while ( delay )delay--; 
}

void TIM16_IRQHandler(void)
{
	TIM16->SR=0;//Clear the interrupt flag bit
	guiTickHandle();//1ms at a time
	SystemTick_Handle();
}

void TIM17_IRQHandler(void)
{	
	TIM17->SR=0;//Clear the interrupt flag bit	
	time++;	

}
void TIM4_IRQHandler(void)
{	
		
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET)
	{
		circle_count = encoder_getCounter();		
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);//Clear the interrupt flag bit
	}		
}
void GPIO0_IRQHandler(void)
{
			
}
void GPIO1_IRQHandler(void)
{

}

#define UART_RXIFLSEL_max  14-1 //fifo depth value-1

void UART2_IRQHandler(void)
{
	
		if((UART2->INTR&UART_IT_RXIS)!=0)
		{
			for(int i=0;i<UART_RXIFLSEL_max;i++)      //fifo for 14 bytes into a receive interrupt, each read from fifo fifo depth minus a byte, need to leave a byte
			{
				Com_Des.inputChar(UART2->DATA);	 
			}
			UART2->INTR_CLR=UART_IT_RXIS;
		}

	if((UART2->INTR&UART_IT_RTIS)!=0)
		{
			while((UART2->STAT&UART_FLAG_RXFE)==0)
				Com_Des.inputChar(UART2->DATA);
				Com_Des.inputEnd();
			UART2->INTR_CLR=UART_IT_RTIS;
		}	
}
/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
// void NMI_Handler(void)
// {
// }

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
	printf("HardFault_Handler");
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  /* Decrement the TimingDelay variable */
}

/******************************************************************************/
/*            Y6 Peripherals Interrupt Handlers                        */
/******************************************************************************/

/******************************************************************************/
/*                 Y6 Peripherals Interrupt Handlers                        */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_Y6.s).                                                    */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

//Add the following code to support the printf function without having to select use MicroLIB	  
//#pragma import(__use_no_semihosting)                             
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef¡¯ d in stdio.h. */ 
//FILE __stdout;       
// Define _sys_exit() to avoid using semi-host mode   
int _sys_exit(int x) 
{ 
	x = x; 
	return 0;
} 
//__use_no_semihosting was requested, but _ttywrch was 
void _ttywrch(int ch) 
{ 
	ch = ch; 
} 
//Redirect fputc function 
//The output of printf, pointing to fputc, is output by fputc to the serial port

int fputc(int ch, FILE *f)
{   
	#if USE_PRINTF_DEBUG	

	while((UART2->STAT&UART_FLAG_TXFE)==0);//Wait for the last serial data transmission to finish 
	UART2->DATA = ch;//Write DR, serial port 2 will send data
	#endif
	return ch;
	
}

int fgetc(FILE *stream)
{
	return 0;
}


/******************* (C) COPYRIGHT 2013 TDO  *****END OF FILE****/
