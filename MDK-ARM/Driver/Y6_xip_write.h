

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Y6_XIP_WRITE_H
#define __Y6_XIP_WRITE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "Y6.h"
  
void xipWriteTest(void);
int xipTX(QSPI_TypeDef *QSPIptr, uint8_t *data, uint32_t num);
int xipRX(QSPI_TypeDef* QSPIptr,uint8_t *data,uint32_t num);
void XIP_EraseFlash_Block_4K(uint32_t faddr,uint32_t count);
void XIP_WriteFlash_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint32_t NumByteToWrite);
void loadData8FromQspi0(uint32_t addr, uint8_t* buf, uint32_t count);
void loadData16FromQspi0(uint32_t addr, uint16_t* buf, uint32_t count);
void loadData32FromQspi0(uint32_t addr, uint32_t* buf, uint32_t count);

#ifdef __cplusplus
}
#endif

#endif /*__Y6_XIP_WRITE_H */
