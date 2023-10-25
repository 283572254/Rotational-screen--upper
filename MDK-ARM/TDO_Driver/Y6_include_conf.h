#ifndef _Y6_include_conf_h
#define _Y6_include_conf_h
#include "stdint.h"

#define LCD_TL0128QVC_SPI   		//1.28"   240 * 240

//--------------------------------------------
#define USE_PRINTF_DEBUG                    1  
#define _SPI_LCD

//------------------------------------------------
typedef enum _Y6_LCD_SCAN{
	//LCD scan direction definition
	Y6_DIR_HORIZONTAL = 0x01,//Horizontal scan
	Y6_HOR_DOWN_SCR,
	Y6_DIR_VERTICAL,//VERTICAL scan
	Y6_VER_DOWN_SCR,	 
}Y6_LCD_SCAN;

#define Y6_LCD_DIR Y6_DIR_VERTICAL


#define READFLASH_SECTOR_START            8      //Resource base address sector number
#define READ_TEA_ADDR			 258                     


#define OK_Y6 				0
#define FAILE_Y6 			-1
 
//------------------CTP/RTP---------------------------------

//------------------------------------------------------
   
	#define 	VALUE_HOR    		0x68
	#define		VALUE_HOR_DOWN  	0xA8  
	#define 	VALUE_VER    		0x08  			
	#define		VALUE_VER_DOWN  	0xc8	

#if defined(LCD_TL0128QVC_SPI) 
 
	#define PRINTF_IRC_Uart       	UART0
	#define PRINTF_GPIO         	GPIO1
	#define UART_IRC_GP        		UART0_GP7
	#define UART_IRC_IRQn       	UART0_IRQn
	#define PRINTF_RX_PIN        	GPIO_Pin_24
	#define PRINTF_TX_PIN        	GPIO_Pin_25
	#define GPIO_FUNCTION_Uart    	GPIO_FUNCTION_2
	#define AHBCLK_BIT_UART_PORT  	AHBCLK_BIT_UART0
	#define RCC_CLOCKFREQ_UARTCLK_PORT        RCC_CLOCKFREQ_UART0CLK

	#define LED_PIN   GPIO_Pin_10
	#define LED_PORT  GPIO1
	#define KEY_ENABLE  
	
	#define BG_PIN   GPIO_Pin_24
	#define BG_PORT  GPIO0

	#define CS_PIN   GPIO_Pin_4
	#define CS_PORT  GPIO0
	
	#define BIGCOLOR  0
	
	#define WIDTH_DEF   240
	#define HEIGHT_DEF  240
	
#endif

#endif

