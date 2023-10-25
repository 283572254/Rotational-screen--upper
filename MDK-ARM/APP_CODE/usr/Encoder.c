#include "ENCODER.h"
#include <stdio.h>
#include <string.h>
#include "Y6.h"
#include "Y6_tim.h"
#include "Y6_gpio.h"
#include "systemHeart.h"

int16_t Encoder_counter=0 ;

char LastStatus_PinA = 1;
char LastStatus_PinB = 1;

void Encoder_Init(void)
{
	TIM4_EncoderInit();	
}	

void TIM4_EncoderInit(void)
{
	GPIO_InitTypeDef         GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef        TIM_ICInitStructure;   	
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);  
	TIM_ICStructInit(&TIM_ICInitStructure);        

	RCC->AHBCLKCTRL0_SET|=(1<<24);//Turn on the timer clock
	RCC->AHBCLKCTRL0_SET|=(1<<3); //Turn on the GPIO clock
	
	GPIO_InitStructure.GPIO_Pin = TIM4_CHA_PIN ;  //    0-2   tim4 ch1
	GPIO_InitStructure.GPIO_Function = GPIO_FUNCTION_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIO0, &GPIO_InitStructure); 
	GPIO_InitStructure.GPIO_Pin = TIM4_CHB_PIN ; // 7-2   tim4 ch2
	GPIO_InitStructure.GPIO_Function = GPIO_FUNCTION_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIO1, &GPIO_InitStructure); 
	
	
	/*- TIM4 encoder mode configuration -*/
	TIM_Reset(TIM4);
	TIM_TimeBaseStructure.TIM_Period =15*4-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);              
                 
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge ,TIM_ICPolarity_BothEdge);	//Configure encoder mode trigger source and polarity
	
	TIM_ICStructInit(&TIM_ICInitStructure);	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 |TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 6;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
		
	TIM4->CNT = 0;
	TIM_Cmd(TIM4, ENABLE);   //Start Timer

}

int16_t encoder_getCounter(void)
{
   int Encoder_TIM;
	Encoder_TIM =TIM_GetCounter(TIM4);
	return Encoder_TIM/2;    
}



