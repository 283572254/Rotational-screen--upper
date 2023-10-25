#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Y6_uart.h" 
#include "Y6_gpio.h" 
#include "Y6_rcc.h"	 
#include "misc.h"
#include "Y6_dma.h"
#include "Y6_wdg.h"
#include "Y6_qspi.h"	 
#include "Y6_eval_qspi.h"
#include "Y6_xip_write.h"

//#define FLASH_4BYTES_ADDR   

static void xip_delay(volatile int time)
{
    while ( time )time--; 
}

FlagStatus xip_GetFlagStatus(QSPI_TypeDef *QSPIptr, uint32_t QSPI_FLAG)
{
  if ((QSPIptr->STATUS & QSPI_FLAG) != (uint32_t)RESET){
    return SET;
  }else{
    return RESET;
  }
}

void xip_DataConfig(QSPI_TypeDef *QSPIptr, QSPI_DataInitTypeDef *QSPI_DataInitStruct)
{
  uint32_t tmepReg;
  int curTransferDir;

  if(QSPIptr->CTRL0 & 0x04000000)
  	curTransferDir = QSPI_Transfer_Read;
  else
  	curTransferDir = QSPI_Transfer_Write;

  QSPIptr->XFER = QSPI_DataInitStruct->QSPI_DataLength;
  if(curTransferDir == QSPI_DataInitStruct->QSPI_TransferDir){
	  if (QSPIptr->CTRL0 & QSPI_CTRL0_LOCK_CS){
	    tmepReg = 0x20000000|QSPI_DataInitStruct->QSPI_DUPLEX | QSPI_DataInitStruct->QSPI_TransferDir | QSPI_CTRL0_LOCK_CS;
	  }
	  else{
	    tmepReg = 0x20000000|QSPI_DataInitStruct->QSPI_DUPLEX | QSPI_DataInitStruct->QSPI_TransferDir;
	  }
	  QSPIptr->CTRL0 = tmepReg;
  }
	else{
	  if (QSPIptr->CTRL0 & QSPI_CTRL0_LOCK_CS){
	    tmepReg = QSPI_DataInitStruct->QSPI_DUPLEX | QSPI_DataInitStruct->QSPI_TransferDir | QSPI_CTRL0_LOCK_CS;
	  }
	  else{
	    tmepReg = QSPI_DataInitStruct->QSPI_DUPLEX | QSPI_DataInitStruct->QSPI_TransferDir;
	  }
	  QSPIptr->CTRL0 = tmepReg;
	  QSPIptr->CTRL0 |= 0x20000000;
	}
}

int xipTX(QSPI_TypeDef *QSPIptr, uint8_t *data, uint32_t num)
{
	uint16_t i, j;
	QSPI_DataInitTypeDef QSPI_DataInitStruct;

	for (i = 0; i < num / 4; i++){
		QSPI_DataInitStruct.QSPI_DataLength = 4;
		QSPI_DataInitStruct.QSPI_DUPLEX = QSPI_HalfDuplex;
		QSPI_DataInitStruct.QSPI_TransferDir = QSPI_Transfer_Write;
		xip_DataConfig(QSPIptr, &QSPI_DataInitStruct);

		QSPIptr->DATA = *((uint32_t *)data + i);

		while (xip_GetFlagStatus(QSPIptr, QSPI_STATUS_XMIT_EMPTY) == RESET);
		while (xip_GetFlagStatus(QSPIptr, QSPI_STATUS_SPI_BUSY) == SET);
	}

	num %= 4;
	if(num){
		uint8_t* pData = (uint8_t*)((uint32_t)QSPIptr+0x40);

		QSPI_DataInitStruct.QSPI_DataLength = num;
		QSPI_DataInitStruct.QSPI_DUPLEX = QSPI_HalfDuplex;
		QSPI_DataInitStruct.QSPI_TransferDir = QSPI_Transfer_Write;
		xip_DataConfig(QSPIptr, &QSPI_DataInitStruct);
		for(j=0;j<num;j++){
			*pData = data[i*4+j];
		}
		while (xip_GetFlagStatus(QSPIptr, QSPI_STATUS_XMIT_EMPTY) == RESET);
		while (xip_GetFlagStatus(QSPIptr, QSPI_STATUS_SPI_BUSY) == SET);
	}
	return 0;
}

int xipRX(QSPI_TypeDef* QSPIptr,uint8_t *data,uint32_t num)
{
	uint16_t i;
	uint32_t temp32;
	QSPI_DataInitTypeDef QSPI_DataInitStruct;

	for(i=0; i<num/4; i++) {
		QSPI_DataInitStruct.QSPI_DataLength = 4;
		QSPI_DataInitStruct.QSPI_DUPLEX = QSPI_HalfDuplex;
		QSPI_DataInitStruct.QSPI_TransferDir = QSPI_Transfer_Read;
		xip_DataConfig(QSPIptr, &QSPI_DataInitStruct);

		while (xip_GetFlagStatus(QSPIptr, QSPI_STATUS_SPI_BUSY) == SET);
		*((uint32_t *)data + i) = QSPIptr->DATA;
	}

	num %= 4;
	if(num) {
		QSPI_DataInitStruct.QSPI_DataLength = num;
		QSPI_DataInitStruct.QSPI_DUPLEX = QSPI_HalfDuplex;
		QSPI_DataInitStruct.QSPI_TransferDir = QSPI_Transfer_Read;
		xip_DataConfig(QSPIptr, &QSPI_DataInitStruct);

		while (xip_GetFlagStatus(QSPIptr, QSPI_STATUS_SPI_BUSY) == SET);

		temp32 = QSPIptr->DATA;
		data[i*4] = temp32 & 0xff;
		if(num>1){
			data[i*4 + 1] = (temp32 >> 8) & 0xff;
		}
		if(num>2){
			data[i*4 + 2] = (temp32 >> 16) & 0xff;
		}
	}
    return 0;
}

__ALIGN4 static uint8_t xip_cmd[8];
static int xip_flash_send_cmd_addr(QSPI_TypeDef* QSPIptr,uint8_t cmd, uint32_t faddr)
{
#ifdef FLASH_4BYTES_ADDR
	xip_cmd[0] = cmd;
	xip_cmd[1] = ((faddr >> 24) & 0xff);
	xip_cmd[2] = ((faddr >> 16) & 0xff);
	xip_cmd[3] = ((faddr >> 8) & 0xff);
	xip_cmd[4] = (faddr & 0xff);
	return xipTX(QSPIptr, xip_cmd, 5);
#else
	xip_cmd[0] = cmd;
	xip_cmd[1] = ((faddr >> 16) & 0xff);
	xip_cmd[2] = ((faddr >> 8) & 0xff);
	xip_cmd[3] = (faddr & 0xff);
	return xipTX(QSPIptr, xip_cmd, 4);
#endif
}

int xip_flash_read(QSPI_TypeDef *QSPIptr, uint8_t *buf, uint32_t faddr, int count)
{
	int ret;
  	QSPIptr->CTRL0 |= QSPI_CTRL0_LOCK_CS;
#ifdef FLASH_4BYTES_ADDR
	xip_flash_send_cmd_addr(QSPIptr, QUAD_SPI_FLASH_CMD_READ_WITH_4BYTE_ADDR, faddr);
#else
	xip_flash_send_cmd_addr(QSPIptr, QUAD_SPI_FLASH_CMD_READ, faddr);
#endif
	ret = xipRX(QSPIptr, buf, count);
  	QSPIptr->CTRL0 &= ~QSPI_CTRL0_LOCK_CS;
	return ret;
}

void xip_flash_write_enable(QSPI_TypeDef* QSPIptr)
{
  	QSPIptr->CTRL0 |= QSPI_CTRL0_LOCK_CS;
    xip_cmd[0] = QUAD_SPI_FLASH_CMD_WRITE_ENABLE;
    xipTX(QSPIptr, xip_cmd,1);
  	QSPIptr->CTRL0 &= ~QSPI_CTRL0_LOCK_CS;
}

uint8_t xip_flash_read_status1(QSPI_TypeDef* QSPIptr)
{
  	QSPIptr->CTRL0 |= QSPI_CTRL0_LOCK_CS;
    xip_cmd[0] = QUAD_SPI_FLASH_CMD_READ_STATUS1;
    xipTX(QSPIptr, xip_cmd,1);
    xipRX(QSPIptr, xip_cmd,4);
  	QSPIptr->CTRL0 &= ~QSPI_CTRL0_LOCK_CS;

	return xip_cmd[0];
}

uint8_t xip_flash_read_status2(QSPI_TypeDef* QSPIptr)
{
  	QSPIptr->CTRL0 |= QSPI_CTRL0_LOCK_CS;
    xip_cmd[0] = QUAD_SPI_FLASH_CMD_READ_STATUS2;
    xipTX(QSPIptr, xip_cmd,1);
    xipRX(QSPIptr, xip_cmd,4);
  	QSPIptr->CTRL0 &= ~QSPI_CTRL0_LOCK_CS;

	return xip_cmd[0];
}

void xip_wait(QSPI_TypeDef* QSPIptr)
{
    volatile uint8_t status = 1;
    while (status & 1)
    {
        status = xip_flash_read_status1(QSPIptr);
        xip_delay(1000);
    }	
}

void xip_flash_write_status(QSPI_TypeDef* QSPIptr, uint8_t status1, uint8_t status2)
{
	xip_flash_write_enable(QSPIptr);
	
  	QSPIptr->CTRL0 |= QSPI_CTRL0_LOCK_CS;
    xip_cmd[0] = QUAD_SPI_FLASH_CMD_WRITE_STATUS;
    xip_cmd[1] = status1;
    xip_cmd[2] = status2;
    xipTX(QSPIptr, xip_cmd,3);
  	QSPIptr->CTRL0 &= ~QSPI_CTRL0_LOCK_CS;

	xip_wait(QSPIptr);
}

void xip_flash_global_unprotect(QSPI_TypeDef* QSPIptr)
{
    volatile uint8_t status1 = 1;
    volatile uint8_t status2 = 1;
	
    xip_flash_write_enable(QSPIptr);
    status1 = xip_flash_read_status1(QSPIptr);
    status2 = xip_flash_read_status2(QSPIptr);
	xip_flash_write_status(QSPIptr, status1&0xC3, status2);
}

int xip_flash_write(QSPI_TypeDef* QSPIptr, uint8_t * buf, uint32_t faddr, int count)
{
  volatile uint8_t status = 1;

  xip_flash_write_enable(QSPIptr);
  QSPIptr->CTRL0 |= QSPI_CTRL0_LOCK_CS;
#ifdef FLASH_4BYTES_ADDR
  xip_flash_send_cmd_addr(QSPIptr, QUAD_SPI_FLASH_CMD_WRITE_WITH_4BYTE_ADDR, faddr);
#else
  xip_flash_send_cmd_addr(QSPIptr, QUAD_SPI_FLASH_CMD_WRITE, faddr);
#endif
  xipTX(QSPIptr, buf,count);
  QSPIptr->CTRL0 &= ~QSPI_CTRL0_LOCK_CS;

	xip_wait(QSPIptr);

  return count;
}

void xip_flash_erase_block_64k(QSPI_TypeDef* QSPIptr, uint32_t faddr)
{
    xip_flash_write_enable(QSPIptr);	

  	QSPIptr->CTRL0 |= QSPI_CTRL0_LOCK_CS;
#ifdef FLASH_4BYTES_ADDR
    xip_flash_send_cmd_addr(QSPIptr, QUAD_SPI_FLASH_CMD_ERASE_64K_WITH_4BYTE_ADDR, faddr);
#else
    xip_flash_send_cmd_addr(QSPIptr, QUAD_SPI_FLASH_CMD_ERASE_64K, faddr);
#endif
  	QSPIptr->CTRL0 &= ~QSPI_CTRL0_LOCK_CS;

	xip_wait(QSPIptr);
}

void xip_flash_erase_block_4k(QSPI_TypeDef* QSPIptr, uint32_t faddr)
{
    xip_flash_write_enable(QSPIptr);	

  	QSPIptr->CTRL0 |= QSPI_CTRL0_LOCK_CS;
#ifdef FLASH_4BYTES_ADDR
    xip_flash_send_cmd_addr(QSPIptr, QUAD_SPI_FLASH_CMD_ERASE_4K_WITH_4BYTE_ADDR, faddr);
#else
    xip_flash_send_cmd_addr(QSPIptr, QUAD_SPI_FLASH_CMD_ERASE_4K, faddr);
#endif
  	QSPIptr->CTRL0 &= ~QSPI_CTRL0_LOCK_CS;

	xip_wait(QSPIptr);
}

#define TEST_IN_XIP

//#define TEST_SIZE	240
//__ALIGN4 uint8_t fakeCmd[TEST_SIZE];
////0x30000 on flash = 0x28000 in XIP
//#define XIP_WRITE_ADDR	0x400000
//#define XIP_READ_ADDR   0x3f8000
__ALIGN4 uint8_t fakeCmd[8];

//faddr: Real physical address
//count: Number of sectors
void XIP_EraseFlash_Block_4K(uint32_t faddr,uint32_t count)
{
	int i;
	QSPI0->CTRL0_CLR = 0x22000000;	//clear MEMP/RUN
	
  QSPI0->CTRL1_SET = QSPI_CTRL1_DMA_ENABLE;

	//Exit continuous reading mode
	for(i=0;i<8;i++){
		fakeCmd[i] = 0x00;
	}
  QSPI0->CTRL0 |= QSPI_CTRL0_LOCK_CS;
  xipTX(QSPI0, fakeCmd,8);
	QSPI0->CTRL0 &= ~QSPI_CTRL0_LOCK_CS;
	
  QSPI0->CTRL1 = (QSPI0->CTRL1 & 0xfffffff8) | 0x00;
	PIO1->PIN0 = PIO1->PIN0 & 0xfffffffc;
	PIO1->PIN3 = PIO1->PIN3 & 0xfffffffc;
	
	xip_flash_global_unprotect(QSPI0);
	for(i=0;i<count;i++){
		xip_flash_erase_block_4k(QSPI0, faddr+(i*4096));
	}
	
	//D2D3 pinmux switch to QSPI,CTRL1 keep single line state,XIP automatically switch to 4 lines
	PIO1->PIN0 = (PIO1->PIN0 & 0xfffffffc) | 0x01;
	PIO1->PIN3 = (PIO1->PIN3 & 0xfffffffc) | 0x01;

	//disable DMA
  QSPI0->CTRL1_CLR = QSPI_CTRL1_DMA_ENABLE;
	//MEMP:bit 25
	//RUN:bit 29
	QSPI0->CTRL0_SET = 0x02000000;	//set MEMP/RUN
}

//pBuffer              data pointer
//WriteAddr            real physical address
//NumByteToWrite       Number of bytes
void XIP_WriteFlash_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint32_t NumByteToWrite) 
{
	int i;
	QSPI0->CTRL0_CLR = 0x22000000;	//clear MEMP/RUN

  QSPI0->CTRL1_SET = QSPI_CTRL1_DMA_ENABLE;

	
	for(i=0;i<8;i++){
		fakeCmd[i] = 0x00;
	}
  QSPI0->CTRL0 |= QSPI_CTRL0_LOCK_CS;
  xipTX(QSPI0, fakeCmd,8);
	QSPI0->CTRL0 &= ~QSPI_CTRL0_LOCK_CS;

	//CTRL1 switch to single line, D2D3 pinmux switch to GPIO
  QSPI0->CTRL1 = (QSPI0->CTRL1 & 0xfffffff8) | 0x00;
	PIO1->PIN0 = PIO1->PIN0 & 0xfffffffc;
	PIO1->PIN3 = PIO1->PIN3 & 0xfffffffc;
	
	xip_flash_global_unprotect(QSPI0);
	//When you write, you need to determine if the address and number of pages are crossed, if they are, you need to write the data on the previous page first and then write the rest to the next page.
	//Note that flash cannot write across pages
	uint16_t pageremain;	   
	pageremain=256-WriteAddr%256; 
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;
	while(1){
		xip_flash_write(QSPI0, pBuffer, WriteAddr, pageremain);
		if(NumByteToWrite==pageremain)break;
		else //NumByteToWrite>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	

			NumByteToWrite-=pageremain;			     
			if(NumByteToWrite>256)pageremain=256; 
			else pageremain=NumByteToWrite; 	    
		}
	}
	//D2D3 pinmux switch to QSPI,CTRL1 keep single line state,XIP automatically switch to 4 lines
	PIO1->PIN0 = (PIO1->PIN0 & 0xfffffffc) | 0x01;
	PIO1->PIN3 = (PIO1->PIN3 & 0xfffffffc) | 0x01;

	//disable DMA
  QSPI0->CTRL1_CLR = QSPI_CTRL1_DMA_ENABLE;
	//MEMP:bit 25
	//RUN:bit 29
	QSPI0->CTRL0_SET = 0x02000000;	//set MEMP/RUN
}

//This function must be run in SRAM
void loadData8FromQspi0(uint32_t addr, uint8_t* buf, uint32_t count)
{
	uint32_t i;
	uint8_t* pRead = (uint8_t*)addr;
	
	for(i=0;i<count;i++){
		buf[i] = pRead[i];
	}
}


void loadData16FromQspi0(uint32_t addr, uint16_t* buf, uint32_t count)
{
	uint32_t i;
	uint16_t* pRead = (uint16_t*)addr;
	
	for(i=0;i<count;i++){
		buf[i] = pRead[i];
	}
}


void loadData32FromQspi0(uint32_t addr, uint32_t* buf, uint32_t count)
{
	uint32_t i;
	uint32_t* pRead = (uint32_t*)addr;
	
	for(i=0;i<count;i++){
		buf[i] = pRead[i];
	}
}

