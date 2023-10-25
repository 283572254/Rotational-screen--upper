#include "SystemHeart.h"
#include <stdio.h>
#include <string.h>
#include "Y6.h"
#include "Y6_tim.h"

volatile uint32_t systemTick=0;

void SystemHeart_Init(void)
{
	//Initialize Timer 16      System Heartbeat
	RCC->AHBCLKCTRL0_SET|=(1<<19);
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler=95;//96Mhz/(95+1)=1Mhz
	TIM_TimeBaseStructure.TIM_Period=1000;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM16, &TIM_TimeBaseStructure);
	
	TIM_SelectOutputTrigger(TIM16, TIM_TRGOSource_Enable);
	TIM_ClearITPendingBit(TIM16, TIM_IT_Update);     			
	TIM_ITConfig(TIM16, TIM_IT_Update, ENABLE);       		 
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=TIM16_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPriority=0;
	NVIC_Init(&NVIC_InitStruct);
	TIM_Cmd(TIM16,ENABLE);
}

void TouchScanTimer_Init(void)
{
	//Initialize Timer 17      CTP
	RCC->AHBCLKCTRL0_SET|=(1<<20);
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler=95;//96Mhz/(95+1)=1Mhz
	TIM_TimeBaseStructure.TIM_Period=2000;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM17, &TIM_TimeBaseStructure);
	TIM_SelectOutputTrigger(TIM17, TIM_TRGOSource_Enable);
	TIM_ClearITPendingBit(TIM17, TIM_IT_Update);     			
	TIM_ITConfig(TIM17, TIM_IT_Update, ENABLE);       		
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=TIM17_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPriority=0;
	NVIC_Init(&NVIC_InitStruct);
	TIM_Cmd(TIM17,ENABLE);
}
uint32_t Get_SystemTick(void)
{	
	return systemTick;
}


#ifndef USE_HAL_DELAY

void Delay_ms(unsigned int delay)
{
	uint32_t tickstart = Get_SystemTick();
  uint32_t wait = delay;

  /* Add a freq to guarantee minimum wait */
  if (wait < SYSTEM_MAX_DELAY){
    wait += (uint32_t)(1);
  }	
	while(wait!=0){
		if(Get_SystemTick()!=tickstart){
			wait--;
			
			tickstart=Get_SystemTick();
		}
	}
}


#endif
