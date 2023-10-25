#ifndef _systemhear_h
#define _systemhear_h
#include "stdint.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Functional module: System heartbeat (provides time base for message loop of all subsequent events)
 * Realization of functions: 1. Incremental realization of the system heartbeat count (1KHZ)
 * 2. Get the current system heartbeat value
 * 3. MS level system delay function (through USE_HAL_DELAY macro you can define whether to use the delay function of the 
		HAL library compatible with the HAL library)
 *
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*Maximum heartbeat count value*/
#define  SYSTEMTICK_MAX      0xFFFFFFFFU
/*
 *ms level system delay function, based on the implementation of the systemTick counter, us system does not provide, need to use when their own internal implementation
 * refuse to use delay, delay_us and other function names, the delay function will lead to system blocking, please use caution 
 */
//#define USE_HAL_DELAY//Time delay functions using the HAL library
#ifdef USE_HAL_DELAY
	#include "stm32f1xx_hal.h"
	#define Delay_ms(delay)   HAL_Delay(delay)
#else 
	#define SYSTEM_MAX_DELAY      0xFFFFFFFFU
	void Delay_ms(unsigned int delay);
#endif


/*The system heartbeat count increment is implemented by creating a 1MS 
interrupt when porting, and then calling the following interface function*/
extern volatile uint32_t systemTick;
#define  SystemTick_Handle() systemTick++

/*Get the current heartbeat value of the system*/
uint32_t Get_SystemTick(void);

void SystemHeart_Init(void);
void TouchScanTimer_Init(void);
void TIM6_IRQHandler(void);
#endif
