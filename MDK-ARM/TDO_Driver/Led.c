#include "Led.h"
//#include <stdio.h>
//#include <string.h>
 #include "Y6_gpio.h"
 #include "Y6_include_conf.h"

 
void Led_init(void)
{
		GPIO_SetPinMux(LED_PORT, LED_PIN,GPIO_FUNCTION_0);//   7-2
	    GPIO_SetPinDir(LED_PORT, LED_PIN,GPIO_Mode_OUT);// 
	
	#if defined(LCD_TY035QVC02_8MCU) || defined(LCD_TY028QVC01_8MCU)
		  GPIO_SetPin(LED_PORT, LED_PIN);   	
	#else
	      GPIO_ClearPin(LED_PORT, LED_PIN);
	#endif

	
 }
	
 
void led_flash_1s(void)
{
	
	if(GPIO_ReadPin(LED_PORT,LED_PIN) == 0)
		{
				GPIO_SetPin(LED_PORT, LED_PIN);  
		}
		else{
				GPIO_ClearPin(LED_PORT, LED_PIN); 
		}
			
}
