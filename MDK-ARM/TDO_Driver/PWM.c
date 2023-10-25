
#include "pwm.h"
  
uint8_t _BG_OPEN = 0;//Backlight open mark
 
void TIM15_PWMInit(uint16_t arr,uint16_t psc,uint16_t pulse)
{
	
	RCC->AHBCLKCTRL0_SET|=(1<<18);
	RCC->AHBCLKCTRL0_SET|=(1<<3);
	RCC->PWMCLKDIV = 0X01;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	GPIO_InitTypeDef GPIO_InitStructure; 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_24;
	GPIO_InitStructure.GPIO_Function = GPIO_FUNCTION_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIO0, &GPIO_InitStructure);
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler=psc;//96Mhz/(95+1)=96Mhz
	TIM_TimeBaseStructure.TIM_Period=arr ;//fpwm=9600/(1199+1)=80Khz
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM15, &TIM_TimeBaseStructure);
	//SYSAHBCLKDIV=4  The AHB clock 96Mhz has been initialized in SystemInit
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = pulse; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC1Init(TIM15, &TIM_OCInitStructure);  
	
	TIM_BDTRInitTypeDef TIM_BDTRInitStruct;
	TIM_BDTRStructInit(&TIM_BDTRInitStruct);
	TIM_BDTRConfig(TIM15,&TIM_BDTRInitStruct);
	
	TIM_CtrlPWMOutputs(TIM15,ENABLE);
	TIM_OC1PreloadConfig(TIM15,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM15,ENABLE);
	TIM_Cmd(TIM15,ENABLE);
	
}
	
void SetPwm(uint8_t value)
{
	 TIM_SetCompare1(TIM15,value);
}
 


  
 
