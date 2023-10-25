#ifndef __PWM_H
#define __PWM_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <string.h>
#include "Y6.h"
#include "Y6_tim.h" 
#include "Y6_gpio.h"
#include "Y6_rcc.h"
#include "Y6_gpio.h"
  
 void SetPwm(uint8_t value);	
 void SetPwm_TIM4(uint8_t value);	

 extern uint8_t _BG_OPEN ;
	
void TIM15_PWMInit(uint16_t arr,uint16_t psc,uint16_t pulse);

#ifdef __cplusplus
}
#endif

#endif /*__PWM_H */

