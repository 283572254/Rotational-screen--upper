#include "Key.h"
#include <stdio.h>
#include <string.h>
#include "Y6.h"
#include "Y6_gpio.h"

void Key_init(void)
{	
	GPIO_SetPinMux(GPIO0, GPIO_Pin_28,GPIO_FUNCTION_0); // KEY  P3-4
	GPIO_SetPinDir(GPIO0, GPIO_Pin_28,GPIO_Mode_IN);//KEY   
	GPIO_ConfigPull(GPIO0, GPIO_Pin_28,GPIO_PULL_UP);			
}



