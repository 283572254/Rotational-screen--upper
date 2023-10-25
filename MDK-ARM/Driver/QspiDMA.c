#include "QspiDMA.h"
#include "Y6.h"
#include "Y6_rcc.h"
#include "Y6_gpio.h"
#include "Y6_qspi.h"
#include "Y6_eval_qspi.h"
#include <stdio.h>
#include <string.h>

#define MAX_QSPI_DMA_BUSY_WATI	 0x00800000
__align(4) uint8_t flashOperationBuff[8];
// static uint8_t _4ByteAddrMode = 0;       //flash Whether to use 4-byte address   0 not used  1 used

/*
*********************************************************************************************************************
* Function: QSPIDMA_WaitEnd QSPI Wait for DMA channel transfer to complete
*Entry parameter: QSPIptr QSPI of the operation
					DMAchannel DMA channel 0-3
*Exit parameters: 0 Success
					-1 timeout
					-2 invalid channel
*********************************************************************************************************************
*/
int QSPIDMA_WaitEnd(QSPI_TypeDef *QSPIptr , uint8_t DMAchannel)
{
	int result = 0;
	if(DMAchannel > DMA_CHANNEL_MAX)return -2;
	else{
		int waitchannel = MAX_QSPI_DMA_BUSY_WATI;
		while (((DMA->ChEnReg & (1<<DMAchannel)) || ((QSPIptr->STATUS & QSPI_STATUS_SPI_BUSY)!=RESET)) && (waitchannel--));
		
		if(waitchannel <= 0)result = -1;
		QSPIptr->CTRL1_CLR = QSPI_CTRL1_DMA_ENABLE;
	}
	return result;
}
/*
*********************************************************************************************************************
* Function: QSPIDMA_SendBytes QSPI send using DMA
*Entry parameter: QSPIptr QSPI for operation
					DMAchannel DMA channel 0-3
					data Waiting to send data buffer
					len Length of bytes to be sent
*Exit parameters: 0 Success
					-1 timeout
					-2 invalid channel
*********************************************************************************************************************
*/
int QSPIDMA_SendBytes(QSPI_TypeDef *QSPIptr , uint8_t DMAchannel , const uint8_t *data , uint32_t len)
{
	if(DMAchannel > DMA_CHANNEL_MAX)return -2;
	
	uint32_t sendLen = 0;
	uint8_t  sendByte = 0;
	if(len>511){
		sendByte = 1;
		sendLen = len/2;
		if(len%2)sendLen++;
	}
	else {
		sendByte = 0;
		sendLen = len;
	}
	
	QSPIptr->CTRL1_SET = QSPI_CTRL1_DMA_ENABLE;//	
	//QSPIptr->CTRL0_CLR = 0x20000000;
	QSPIptr->XFER = sendLen;
	QSPIptr->CTRL0_SET = QSPI_HalfDuplex;
	QSPIptr->CTRL0_CLR = QSPI_Transfer_Read;
	QSPIptr->CTRL0_SET = 0x20000000;
	
	DMAChannel_TypeDef *sendChannel;
	sendChannel = (DMAChannel_TypeDef *)(DMA_BASE + DMAchannel*0x58);
	
	uint32_t temreg = 0x00000000+(0<<0)    //INT_EN, ch0 irq disable
		                       	  +(0<<1)      // DST_TR_WIDTH, des transfer width, should set to HSIZE, here is 000, means 8bit
                              +(sendByte<<4)      // SRC_TR_WIDTH, sor transfer width, should set to HSIZE, here is 000, means 8bit
                              +(2<<7)      // DINC, des addr increment, des is SPI, so should set to 1x, means no change
                              +(0<<9)      // SINC, sor addr increment, src is sram, so should set to 00, means to increase 
                              +(1<<11)     // DEST_MSIZE, des burst length, set to 001 means 4 DST_TR_WIDTH per burst transcation
                              +(1<<14)     // SRC_MSIZE, sor burst length, set to 001 means 4 SOR_TR_WIDTH per burst transcation
                              +(1<<20)     // TT_FC,transfer type and flow control,001 means memory to peripheral,dma is flow controller
                              +(0<<23)     // DMS, des master select, 0 means ahb master 0
                              +(0<<25)     // SMS, sor master select, 1 means ahb master 1
                              +(0<<27)     // LLP_DST_EN, des block chaining enable, set to 0 disable it
                              +(0<<28) ;   // LLP_SOR_EN, sor block chaining enable, set to 0 disable it	
	
	sendChannel->SAR = (uint32_t)(data);
	sendChannel->DAR = (uint32_t)(&QSPIptr->DATA);
	sendChannel->CTL_L = temreg;
	sendChannel->CTL_H = sendLen;//DMA Number of bytes transferred
	sendChannel->LLP =0;
	if(QSPIptr == QSPI0){
		sendChannel->CFG_H = 0x00000000 + (8 << 7) + (8 << 11);
		sendChannel->CFG_L = 7<<5;
	}
	else if(QSPIptr == QSPI1){
		sendChannel->CFG_H = 0x00000000 + (10 << 7) + (10 << 11);
		sendChannel->CFG_L = 6<<5;
	}
	else if(QSPIptr == QSPI2){
		sendChannel->CFG_H = 0x00000000 + (14 << 7) + (14 << 11);
		sendChannel->CFG_L = 5<<5;
	}
	DMA->DmaCfgReg = 1;
	DMA->ChEnReg = (1<<(DMAchannel + 8))|(1<<DMAchannel);
	return 0;
}
/*
*********************************************************************************************************************
* Function: QSPIDMA_ReadBytes QSPI using DMA Receive
*Entry parameter: QSPIptr QSPI for operation
					DMAchannel DMA channel 0-3
					data Waiting to send data buffer
					len Length of bytes to be sent
*Exit parameters: 0 success
					-1 timeout
					-2 invalid channel
					-3 first address of buffer No byte alignment (4-byte alignment)
*********************************************************************************************************************
*/
int QSPIDMA_ReadBytes(QSPI_TypeDef *QSPIptr , uint8_t DMAchannel , uint8_t *data , uint32_t len)
{
	if(DMAchannel > DMA_CHANNEL_MAX)return -2;
	if(((uint32_t)data)&0x03)return -3;

	QSPIptr->CTRL1_SET = QSPI_CTRL1_DMA_ENABLE;	
	//QSPIptr->CTRL0_CLR = 0x20000000;
	QSPIptr->XFER = len;
	QSPIptr->CTRL0_SET = QSPI_HalfDuplex;
	QSPIptr->CTRL0_SET = QSPI_Transfer_Read;
	QSPIptr->CTRL0_SET = 0x20000000;
	
	DMAChannel_TypeDef *readChannel;
	readChannel = (DMAChannel_TypeDef *)(DMA_BASE + DMAchannel*0x58);
	
	uint32_t temreg = 0x00000000+(0<<0)    //INT_EN, ch0 irq disable
       				    						+(2<<1)    // DST_TR_WIDTH, des transfer width, should set to HSIZE, here is 010, means 32bit
	                    				+(2<<4)    // SRC_TR_WIDTH, sor transfer width, should set to HSIZE, here is 010, means 32bit
					    								+(0<<7)    // DINC, des addr increment, des is sram, so should set to 00, means to increase
	                    				+(2<<9)    // SINC, sor addr increment, src is SPI, so should set to 1x, means no change 
					    								+(0<<11)   // DEST_MSIZE, des burst length, set to 000 means 1 DST_TR_WIDTH per burst transcation
					    								+(0<<14)   // SRC_MSIZE, sor burst length, set to 000 means 1 SOR_TR_WIDTH per burst transcation
	                    				+(2<<20)   // TT_FC,transfer type and flow control,010 means peripheral to memory,dma is flow controller
	                    				+(0<<23)   // DMS, des master select, 0 means ahb master 0
	                    				+(0<<25)   // SMS, sor master select, 1 means ahb master 1
	                    				+(0<<27)   // LLP_DST_EN, des block chaining enable, set to 0 disable it
	                    				+(0<<28);  // LLP_SOR_EN, sor block chaining enable, set to 0 disable it	

	readChannel->SAR = (uint32_t)(&QSPIptr->DATA);
	readChannel->DAR = (uint32_t)(data);
	readChannel->CTL_L = temreg;
	uint32_t readCount = len>>2;
	if((len%4)!=0)readCount++;
	readChannel->CTL_H = readCount;//DMA Number of bytes transferred
	readChannel->LLP =0;
	readChannel->CFG_L=0;
	if(QSPIptr == QSPI0){
		readChannel->CFG_H = 0x00000000 + (9 << 7) + (9 << 11);
		readChannel->CFG_L = 4<<5;//Channel Priority
	}
	else if(QSPIptr == QSPI1){
		readChannel->CFG_H = 0x00000000 + (11 << 7) + (11 << 11);
		readChannel->CFG_L = 3<<5;
	}
	else if(QSPIptr == QSPI2){
		readChannel->CFG_H = 0x00000000 + (15 << 7) + (15 << 11);
		readChannel->CFG_L = 2<<5;
	}
	DMA->DmaCfgReg = 1;
	DMA->ChEnReg = (1<<(DMAchannel + 8))|(1<<DMAchannel);
	return 0;
}
/*
*********************************************************************************************************************
* Function: enter_XIPCritical Enter XIP critical area.
					Exiting the MCU from XIP mode and running only the first 8K of the code.
					When to use this method.
					1, the user needs to read a large amount of data into the SRAM and then transfer it to the LCD by other means
					2, usually not needed for brushing monochrome.
					3. usually used for swiping.
					Users should ensure that.
					1, after calling the function, APP code does not call the code outside the 8K
					2. the interrupt service function will not call code outside of 8K.
*Entry parameter: none
*Exit parameter: 0 Success
*********************************************************************************************************************
*/
int enter_XIPCritical(void)
{
	CODE_QSPI->CTRL0_CLR = 0x22000000;					
  CODE_QSPI->CTRL1_SET = QSPI_CTRL1_DMA_ENABLE;	
	//Send 8 0x00, exit continuous read mode
	for(uint32_t i=0; i<8; i++){
		flashOperationBuff[i] = 0x00;
	}
	CODE_QSPI->CTRL0_SET = QSPI_CTRL0_LOCK_CS;	
  QSPIDMA_SendBytes(CODE_QSPI, FLASH_QSPIDMA_WRITE_CHANNEL, flashOperationBuff, 8);
	QSPIDMA_WaitEnd(CODE_QSPI, FLASH_QSPIDMA_WRITE_CHANNEL);
	CODE_QSPI->CTRL0_CLR = QSPI_CTRL0_LOCK_CS;

  CODE_QSPI->CTRL1 = (CODE_QSPI->CTRL1 & 0xfffffff8) | 0x00;
	PIO1->PIN0 = PIO1->PIN0 & 0xfffffffc;
	PIO1->PIN3 = PIO1->PIN3 & 0xfffffffc;
//__disable_irq();
	return 0;
}
/*
*********************************************************************************************************************
*Function£ºquit_XIPCritical       Exit XIP critical zone
*Parameters£ºnull
*return£º0  success
*********************************************************************************************************************
*/
int quit_XIPCritical(void)
{
	//D2D3 pinmux switch to QSPI, CTRL1 keep single line state, XIP automatically switch to 4 lines
	PIO1->PIN0 = (PIO1->PIN0 & 0xfffffffc) | 0x01;
	PIO1->PIN3 = (PIO1->PIN3 & 0xfffffffc) | 0x01;
	//disable DMA
  CODE_QSPI->CTRL1_CLR = QSPI_CTRL1_DMA_ENABLE;

	//MEMP:bit 25
	//RUN:bit 29
	CODE_QSPI->CTRL0_SET = 0x02000000;	//set MEMP/RUN
	//__enable_irq();
	return 0;
}
/*
*********************************************************************************************************************
*Function£ºflash_ConfigReadFlash  Configure data flash to read data information
* Parameters£ºQSPIptr : Operation of QSPI Peripherals
				DMAchannel :DMA channels for operation
				dataAddr :  Address of the data to be read
* return£º0  ok
*********************************************************************************************************************
*/
int flash_ConfigReadFlashMsg(QSPI_TypeDef *QSPIptr , uint8_t DMAchannel , uint32_t dataAddr)
{
	flashOperationBuff[0] = QUAD_SPI_FLASH_CMD_READ;
	QSPIDMA_SendBytes(QSPIptr, DMAchannel, flashOperationBuff, 1);//Send the read flash command
	QSPIDMA_WaitEnd(QSPIptr, DMAchannel);
	
	flashOperationBuff[0] = (dataAddr>>16)&0xff;
	flashOperationBuff[1] = (dataAddr>>8)&0xff;
	flashOperationBuff[2] = dataAddr&0xff;
	QSPIDMA_SendBytes(QSPIptr, DMAchannel, flashOperationBuff, 3);//Send flash data address
	QSPIDMA_WaitEnd(QSPIptr, DMAchannel);

	return 0;
}
