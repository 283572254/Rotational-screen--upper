 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Y6_EVAL_QSPI_H
#define __Y6_EVAL_QSPI_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include "Y6.h"
#include "core_cm0.h"
#include "system_Y6.h"

/* Includes ------------------------------------------------------------------*/
/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup M407_EVAL
  * @{
  */
  
/** @addtogroup M407_EVAL_QSPI
  * @{
  */  


  
/** @defgroup M407_EVAL_QSPI_Flash_Macros
  * @{
  */ 
#define QUAD_SPI_FLASH_CMD_WRITE_STATUS  0x01
#define QUAD_SPI_FLASH_CMD_READ          0x03
#define QUAD_SPI_FLASH_CMD_WRITE         0x02
#define QUAD_SPI_FLASH_CMD_WRITE_ENABLE  0x06
#define QUAD_SPI_FLASH_CMD_WRITE_DISABLE 0x04
#define QUAD_SPI_FLASH_CMD_READ_STATUS1   0x05
#define QUAD_SPI_FLASH_CMD_READ_STATUS2   0x35
#define QUAD_SPI_FLASH_CMD_WRITE_STATUS2  0x31
#define QUAD_SPI_FLASH_CMD_READ_STATUS3   0x15
#define QUAD_SPI_FLASH_CMD_WRITE_STATUS3  0x11

#define QUAD_SPI_FLASH_CMD_READ_ID       0x9F

#define QUAD_SPI_FLASH_CMD_ERASE_4K      0x20
#define QUAD_SPI_FLASH_CMD_ERASE_32K     0x52
#define QUAD_SPI_FLASH_CMD_ERASE_64K     0xD8
#define QUAD_SPI_FLASH_CMD_ERASE_ALL     0x60 // 0xC7

#define QUAD_SPI_CMD_FAST_READ_DUAL_OUTPUT      0x3B 
#define QUAD_SPI_CMD_FAST_READ_DUAL_IO			0xBB
#define QUAD_SPI_CMD_FAST_READ_OCTAL_QUAD_IO	0xEB
#define QUAD_SPI_FLASH_CMD_EQPI      	0x38
#define QUAD_SPI_FLASH_CMD_FAST_READ    0x0B

#define QUAD_SPI_CMD_ENTER_4BYTE_ADDR_MODE	      0xB7
#define QUAD_SPI_CMD_EXIT_4BYTE_ADDR_MODE	        0xE9
#define QUAD_SPI_FLASH_CMD_READ_WITH_4BYTE_ADDR          0x13
#define QUAD_SPI_FLASH_CMD_ERASE_4K_WITH_4BYTE_ADDR     0x21
#define QUAD_SPI_FLASH_CMD_WRITE_WITH_4BYTE_ADDR         0x12

#define QSPI_FLASH_PAGESHIFT  8 // 256 Byte


#define	__ALIGN4				__align(4)

/**
  * @}
  */ 
  

/** @defgroup M407_EVAL_QSPI_Flash_Types
  * @{
  */ 
typedef enum {QUAD_ENABLE, QUAD_DISABLE} QUADfuncSelect;
/**
  * @}
  */

/** @defgroup M407_EVAL_QSPI_FLASH_Functions
  * @{
  */
int quad_spi_flash_init(QSPI_TypeDef* QSPIptr,uint32_t rcc_clk_div,int internal_clk_div, int internal_clk_rate);
void qspi_flash_read_status1(QSPI_TypeDef *QSPIptr, char *status);
void qspi_flash_read_status2(QSPI_TypeDef *QSPIptr, char *status);
void qspi_flash_global_unprotect(QSPI_TypeDef *QSPIptr);
void qspi_flash_write_enable(QSPI_TypeDef *QSPIptr, int enable);
int qspi_flash_read(QSPI_TypeDef *QSPIptr, uint8_t *buf, uint32_t faddr, int count);
int qspi_flash_erase_block_4k(QSPI_TypeDef *QSPIptr, uint32_t faddr);
int qspi_flash_write(QSPI_TypeDef *QSPIptr, uint8_t *buf, uint32_t faddr, int count);
void qspi_flash_enableQE(QSPI_TypeDef *QSPIptr, uint8_t qeMask);
void qspi_flash_4Byte_address_enable(QSPI_TypeDef *QSPIptr, uint8_t enable);
void qspi_flash_SetDriverStrength(QSPI_TypeDef *QSPIptr, uint8_t dsMask);
#ifdef __cplusplus
}
#endif

#endif /* __Y6_EVAL_QSPI_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2013 TDO *****END OF FILE****/

