#include "lcdInit.h"
#include "Y6.h"
#include "Y6_rcc.h"
#include "lcdDriver.h"
#include "Y6_gpio.h"
#include "Y6_qspi.h"
#include "QspiDMA.h"
#include "Y6_tim.h"
#include "Y6_include_conf.h"
#include "pwm.h"



 static void Lcd_SPI_Driver(uint32_t rcc_clk_div,int internal_clk_div, int internal_clk_rate)
{
		QSPI_InitTypeDef QSPI_InitStructure;
		
		QSPI_InitStructure.QSPI_CPOL = QSPI_CPOL_Low;
		QSPI_InitStructure.QSPI_CPHA = QSPI_CPHA_1Edge;
		
		QSPI_InitStructure.QSPI_FirstBit = QSPI_FirstBit_MSB;
		QSPI_InitStructure.QSPI_ClockDiv = (internal_clk_div<<8);
		QSPI_InitStructure.QSPI_ClockRate = internal_clk_rate;
		QSPI_InitStructure.QSPI_SlaveMode = QSPI_MASTER_MODE;
		QSPI_InitStructure.QSPI_ModeSelect = QSPI_STD;
		QSPI_InitStructure.QSPI_FrameLength = QSPI_FRAME_LENGTH_8Bit;

		RCC->QUADSPI1CLKDIV = rcc_clk_div;
		GPIO_SetPinMux(GPIO0, GPIO_Pin_13, GPIO_FUNCTION_3);//SPI MOSI
		GPIO_SetPinMux(GPIO0, GPIO_Pin_7, GPIO_FUNCTION_3);//SPI CLK
		GPIO_SetPinMux(GPIO0, GPIO_Pin_4, GPIO_FUNCTION_0);
		GPIO_SetPinDir(GPIO0, GPIO_Pin_4,GPIO_Mode_OUT);// lcd CS
		GPIO_SetPin(GPIO0, GPIO_Pin_4);
		RCC_ResetAHBCLK(1 << AHBCLK_BIT_DMA);
	 
		QSPI_HwInit(LCD_QSPI, &QSPI_InitStructure);
		
		GPIO_SetPinMux(GPIO0, GPIO_Pin_5, GPIO_FUNCTION_0);
		GPIO_SetPinDir(GPIO0, GPIO_Pin_5,GPIO_Mode_OUT);//SD CS
		GPIO_SetPin(GPIO0, GPIO_Pin_5);	                         		 		
		GPIO_SetPinMux(GPIO1, GPIO_Pin_11, GPIO_FUNCTION_0);
		GPIO_SetPinDir(GPIO1, GPIO_Pin_11, GPIO_Mode_OUT);//RS
		
		LCD_RS_G();
}


	 
void LCD_Init(void)
{ 
		Lcd_SPI_Driver(4,2,0);    //384¡Â4¡Â2 = 48 MHz		
		LCD_SPI_Init( );  //Screen initialization code
																					
	  Lcd_Driver.scan_dir(Y6_LCD_DIR);//Switching between horizontal and vertical screens
	    Lcd_Des.clear();													
		_BG_OPEN = 0;//Backlight off   			
}



