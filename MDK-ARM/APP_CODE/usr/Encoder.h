#ifndef  _ENCODER_H
#define  _ENCODER_H
#include "stdint.h"

#define TIM4_CHA_PIN   		GPIO_Pin_2       //0_2
#define TIM4_CHA_PORT  		GPIO0

#define TIM4_CHB_PORT       GPIO1       //7_2
#define TIM4_CHB_PIN        GPIO_Pin_26

#define GPIO_Pin_A()      GPIO_GetOriginalITStatus(GPIO0_IT,GPIO_Pin_2)
#define GPIO_Pin_B()      GPIO_GetOriginalITStatus(GPIO1_IT,GPIO_Pin_26)

#define TIM4_Encoder_Line_Number                                 15//Number of encoder lines, how many pulses per turn
extern  int32_t TIM4_Count,TIM4_Circle_Count,TIM4_Encoder_Line_Multiple;//Total count, lap count, pulse multiplication factor
																		//(Number of pulses per turn=TIM1_Encoder_Line_Number*TIM1_Encoder_Line_Multiple) 
void Encoder_Init(void);

int16_t encoder_getCounter(void);
void TIM4_EncoderInit(void);

#endif


