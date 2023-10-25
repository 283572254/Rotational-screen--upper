#ifndef _QspiDMA_h
#define _QspiDMA_h
//#include "typedefine.h"
#include "gStdint.h"

#include "Y6.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Functional module: Lcd SPI interface driver
 *Implemented functions: 1. LCD SPI interface driver
 *                           
 *
 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define QUAD_SPI_FLASH_CMD_WRITE_STATUS       0x01
#define QUAD_SPI_FLASH_CMD_READ               0x03
#define QUAD_SPI_FLASH_CMD_WRITE              0x02
#define QUAD_SPI_FLASH_CMD_WRITE_ENABLE       0x06
#define QUAD_SPI_FLASH_CMD_WRITE_DISABLE      0x04
#define QUAD_SPI_FLASH_CMD_READ_STATUS1       0x05
#define QUAD_SPI_FLASH_CMD_READ_STATUS2       0x35
#define QUAD_SPI_FLASH_CMD_WRITE_STATUS2      0x31
#define QUAD_SPI_FLASH_CMD_READ_STATUS3       0x15
#define QUAD_SPI_FLASH_CMD_WRITE_STATUS3      0x11
#define QUAD_SPI_FLASH_CMD_READ_ID            0x9F
#define QUAD_SPI_FLASH_CMD_ERASE_4K           0x20
#define QUAD_SPI_FLASH_CMD_ERASE_32K          0x52
#define QUAD_SPI_FLASH_CMD_ERASE_64K          0xD8
#define QUAD_SPI_FLASH_CMD_ERASE_ALL          0x60 // 0xC7
#define QUAD_SPI_CMD_FAST_READ_DUAL_OUTPUT    0x3B 
#define QUAD_SPI_CMD_FAST_READ_DUAL_IO			  0xBB
#define QUAD_SPI_CMD_FAST_READ_OCTAL_QUAD_IO	0xEB
#define QUAD_SPI_FLASH_CMD_EQPI       	      0x38
#define QUAD_SPI_FLASH_CMD_FAST_READ          0x0B

#define QUAD_SPI_CMD_ENTER_4BYTE_ADDR_MODE	  0xB7
#define QUAD_SPI_CMD_EXIT_4BYTE_ADDR_MODE	    0xE9
#define QUAD_SPI_FLASH_CMD_READ_WITH_4BYTE_ADDR         0x13
#define QUAD_SPI_FLASH_CMD_ERASE_4K_WITH_4BYTE_ADDR     0x21
#define QUAD_SPI_FLASH_CMD_WRITE_WITH_4BYTE_ADDR        0x12

#define QSPI_FLASH_PAGESHIFT  8 // 256 Byte

#define DMA_CHANNEL_MAX             3

#define LCD_QSPIDMA_SEND_CHANNEL    3
#define FLASH_QSPIDMA_READ_CHANNEL  2
#define FLASH_QSPIDMA_WRITE_CHANNEL 2

#define  LCD_QSPI                QSPI1
#define  DATA_QSPI               QSPI0
#define  CODE_QSPI               QSPI0

int QSPIDMA_WaitEnd(QSPI_TypeDef *QSPIptr , uint8_t DMAchannel);
int QSPIDMA_SendBytes(QSPI_TypeDef *QSPIptr , uint8_t DMAchannel , const uint8_t *data , uint32_t len);
int QSPIDMA_ReadBytes(QSPI_TypeDef *QSPIptr , uint8_t DMAchannel , uint8_t *data , uint32_t len);
int enter_XIPCritical(void);
int quit_XIPCritical(void);
int flash_ConfigReadFlashMsg(QSPI_TypeDef *QSPIptr , uint8_t DMAchannel , uint32_t dataAddr);


#endif
