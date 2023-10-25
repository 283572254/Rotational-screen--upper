

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Y6_OTP_H
#define __Y6_OTP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "Y6.h"

void OTP_Reset(void);
uint32_t OTP_ReadSN(void);
uint32_t OTP_ReadADJ_12M(void);
uint32_t OTP_ReadADJ_10K(void);
uint32_t OTP_ReadADJ_LDO(void);
uint32_t OTP_ReadADJ_RTC_CAP(void);
uint32_t readReg(uint32_t addr);
void writeReg(uint32_t addr, uint32_t value);
#ifdef __cplusplus
}
#endif

#endif /*__Y6_OTP_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT TDO *****END OF FILE****/
