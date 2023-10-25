#include "SystemUart.h"
#include <stdio.h>
#include <string.h>
#include "Y6_uart.h"
#include "Y6_gpio.h"
#include "Y6_include_conf.h"


void PRINTF_UART_Init(uint32_t BaudRate)
{
 
	RCC_ResetAHBCLK(1 << AHBCLK_BIT_UART_PORT);
  GPIO_SetPinMux(PRINTF_GPIO, PRINTF_RX_PIN, GPIO_FUNCTION_Uart);
  GPIO_SetPinMux(PRINTF_GPIO, PRINTF_TX_PIN, GPIO_FUNCTION_Uart);

  GPIO_ConfigPull(PRINTF_GPIO, PRINTF_RX_PIN, GPIO_PULL_UP);			

	UART_InitTypeDef UART_InitStruct;
	UART_StructInit(&UART_InitStruct);
	UART_InitStruct.UART_BaudRate						 =  BaudRate;
	UART_InitStruct.UART_RXIFLSEL   				 = UART_RXIFLSEL_2;
	UART_InitStruct.UART_TXIFLSEL   				 = UART_TXIFLSEL_2;
	UART_InitStruct.UART_FEN        				 = UART_FEN_Enable;
	UART_InitStruct.UART_SoftwareFlowControl = UART_SoftwareFlowControl_None;
	UART_InitStruct.UART_HardwareFlowControl = UART_HardwareFlowControl_None;
	UART_InitStruct.UART_Mode                = UART_Mode_Rx|UART_Mode_Tx;
	UART_InitStruct.UART_Parity              = UART_Parity_No;
	UART_InitStruct.UART_StopBits 					 = UART_StopBits_1;
	UART_InitStruct.UART_WordLength 				 = UART_WordLength_8b;
	
	RCC_SetAHBCLK(1<<AHBCLK_BIT_UART_PORT,ENABLE);
	RCC_UARTCLKSel(RCC_UARTCLK_SOURCE_SYSPLL);
	RCC_SETCLKDivider(RCC_CLOCKFREQ_UARTCLK_PORT, 32);
	UART_Reset(PRINTF_IRC_Uart);
	UART_Init(PRINTF_IRC_Uart, &UART_InitStruct);
	UART_Cmd(PRINTF_IRC_Uart, ENABLE);	
}

void SystemUart_Init(uint32_t BaudRate)
{
		PRINTF_UART_Init(BaudRate);
		SystemUart2_Init(BaudRate);
}
void SystemUart2_Init(uint32_t BaudRate)
{
		RCC_ResetAHBCLK(1 << AHBCLK_BIT_UART2);
		GPIO_SetPinMux(GPIO0, GPIO_Pin_0, GPIO_FUNCTION_3);
		GPIO_SetPinMux(GPIO0, GPIO_Pin_1, GPIO_FUNCTION_3);//UART setup pin multiplexing
		GPIO_ConfigPull(GPIO0, GPIO_Pin_0, GPIO_PULL_UP);
		UART_InitTypeDef UART_InitStruct;
		UART_StructInit(&UART_InitStruct);
		UART_InitStruct.UART_BaudRate						 =BaudRate;
		UART_InitStruct.UART_RXIFLSEL   				 =UART_RXIFLSEL_14;
		UART_InitStruct.UART_TXIFLSEL   				 =UART_TXIFLSEL_2;
		UART_InitStruct.UART_FEN        				 =UART_FEN_Enable;
		UART_InitStruct.UART_SoftwareFlowControl =UART_SoftwareFlowControl_None;
		UART_InitStruct.UART_HardwareFlowControl =UART_HardwareFlowControl_None;
		UART_InitStruct.UART_Mode                =UART_Mode_Rx|UART_Mode_Tx;
		UART_InitStruct.UART_Parity              =UART_Parity_No;
		UART_InitStruct.UART_StopBits 					 = UART_StopBits_1;
		UART_InitStruct.UART_WordLength 				 = UART_WordLength_8b;
		
		RCC_SetAHBCLK(1<<AHBCLK_BIT_UART2,ENABLE);
		RCC_UARTCLKSel(RCC_UARTCLK_SOURCE_SYSPLL);
		RCC_SETCLKDivider(RCC_CLOCKFREQ_UART2CLK, 32);
		UART_Reset(UART2);
		UART_Init(UART2, &UART_InitStruct);
		
		NVIC_InitTypeDef NVIC_InitStruct;
		NVIC_InitStruct.NVIC_IRQChannel = UART2_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPriority = 1;
		NVIC_Init(&NVIC_InitStruct);
	
		/* set timeout to 8 uart clk cycle len */
		UART2->CTRL0_CLR = UART_CTRL0_RXTIMEOUT;
		UART2->CTRL0_SET = 16 << 16;

		UART_ITConfig(UART2, UART_IT_RXIEN | UART_IT_RTIEN, ENABLE);
		UART_Cmd(UART2, ENABLE);

}
 
void printString1(uint8_t *c,uint32_t len)
{
#if USE_PRINTF_DEBUG	

	for(int i=0;i<len;i++)
	{
		while((PRINTF_IRC_Uart->STAT&UART_FLAG_TXFE)==0);
		PRINTF_IRC_Uart->DATA = *(c+i);	
	}
#endif
}
void printChar1(uint8_t c)
{
	while((PRINTF_IRC_Uart->STAT&UART_FLAG_TXFE)==0);
	PRINTF_IRC_Uart->DATA = c;
}

void printString( uint8_t *c,uint32_t len)
{
	for(int i=0;i<len;i++)
	{
		while((UART2->STAT&UART_FLAG_TXFE)==0);
		UART2->DATA = *(c+i);
	}
}

void printChar(uint8_t c)
{
	while((UART2->STAT&UART_FLAG_TXFE)==0);
	UART2->DATA = c;
}

#include "comInterface.h"


const COM_DESCRIPTOR DebugCom_Des={
	printString,
	GUI_NULL,
};

