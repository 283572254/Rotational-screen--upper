

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Y6_IT_H
#define __Y6_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "Y6.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
 
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void GPIO1_IRQHandler(void);
#ifdef __cplusplus
}
#endif

#endif /* __Y6_IT_H */

/******************* (C) COPYRIGHT 2011 TDO *****END OF FILE****/
