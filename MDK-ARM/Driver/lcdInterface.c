#include "lcdInterface.h"
#include "Y6_gpio.h"
#include "guiConfig.h"
#include "lcdDriver.h"
#include "QspiDMA.h"
#include <stdio.h>
#include <string.h>
#include "Y6_include_conf.h"

#if BIGCOLOR
#define GETCOLOR(data)  (((data&0x00ff)<<8) + ((data&0xff00)>>8))
#else 
#define GETCOLOR(data)   (data)
#endif


#define  LCD_SENDBUF_BYTEMAX         508 //The maximum DMA transfer is 511 blocks.   This value is less than 511 and less than LCD_SENDBUF_HALFWORD_MAX*2
#define  LCD_SENDBUF_HALFWORD_MAX    320 //Size should be the same as the width of the LCD; easy for the driver to use line scan
static __align(4) uint16_t  lcdSendBuff[2][Lcd_SendBuf_HalfWord_Max+2];
/*
*********************************************************************************************************************
*Function: TransferData_FlashToLcd Transfer data from flash to LCD at specified location
* Entry parameter: flashAddr flash data address
* transferCount the number of bytes to be transferred in Byte
*Export parameter: None
*********************************************************************************************************************
*/
static int TransferData_FlashToLcd(uint32_t flashAddr, uint32_t transferCount)
{
	uint32_t operationCount = 0;
	uint32_t readBytes = 0;
	DATA_QSPI->CTRL0_SET = QSPI_CTRL0_LOCK_CS;
	flash_ConfigReadFlashMsg(DATA_QSPI, FLASH_QSPIDMA_WRITE_CHANNEL, flashAddr);
	if(transferCount >= LCD_SENDBUF_BYTEMAX)readBytes = LCD_SENDBUF_BYTEMAX;
	else                            				readBytes = transferCount;
	QSPIDMA_ReadBytes(DATA_QSPI, FLASH_QSPIDMA_READ_CHANNEL, (uint8_t *)(&lcdSendBuff[operationCount][0]),readBytes);
	transferCount -= readBytes;
	while(1){
			QSPIDMA_WaitEnd(DATA_QSPI , FLASH_QSPIDMA_READ_CHANNEL);
			operationCount++;
			if(operationCount>1)operationCount=0;
			QSPIDMA_ReadBytes(DATA_QSPI, FLASH_QSPIDMA_READ_CHANNEL, (uint8_t *)(&lcdSendBuff[operationCount][0]),    readBytes);
			QSPIDMA_SendBytes(LCD_QSPI , LCD_QSPIDMA_SEND_CHANNEL  , (uint8_t *)(&lcdSendBuff[1-operationCount][0]) , readBytes);
			QSPIDMA_WaitEnd(LCD_QSPI , LCD_QSPIDMA_SEND_CHANNEL);
			if(transferCount == 0)break;
			else{
				if(transferCount >= LCD_SENDBUF_BYTEMAX){
					readBytes = LCD_SENDBUF_BYTEMAX;
					transferCount -= readBytes;
				}
				else{
					readBytes = transferCount;
					transferCount=0;
				}
			}
	}
	QSPIDMA_WaitEnd(LCD_QSPI , LCD_QSPIDMA_SEND_CHANNEL);
	QSPIDMA_WaitEnd(DATA_QSPI , FLASH_QSPIDMA_READ_CHANNEL);
	DATA_QSPI->CTRL0_CLR = QSPI_CTRL0_LOCK_CS;
	return 0;
}
/*
*********************************************************************************************************************
* Function£ºTransferData_SramToLcd Transfer data from SRAM to LCD at specified location
* Entry parameter: flashAddr flash data address
* transferCount the number of bytes to be transferred in Byte
*Export parameter: None
*********************************************************************************************************************
*/
static int TransferData_SramToLcd(const uint8_t *dataAddr, uint32_t transferCount)
{
	uint8_t *data = (uint8_t *)dataAddr;
	uint32_t sendBytes = 0;
	while(1){
		if(transferCount == 0)break;
		if(transferCount >= LCD_SENDBUF_BYTEMAX)sendBytes = LCD_SENDBUF_BYTEMAX;
		else                                    sendBytes = transferCount;
		QSPIDMA_SendBytes(LCD_QSPI , LCD_QSPIDMA_SEND_CHANNEL , data , sendBytes);
		QSPIDMA_WaitEnd(LCD_QSPI , LCD_QSPIDMA_SEND_CHANNEL);
		transferCount -= sendBytes;
		data += sendBytes;
	}
	return 0;
}
/*
*********************************************************************************************************************
* Function: LCD_Fill_UseOneData Write a data to LCD memory N times.
* Commonly used for clearing the screen or area filling. Window opening is not done by this function, it is done by the calling function, this function is only responsible for writing data
* Entry parameters: sPos start point coordinates
* ePos end point coordinates
* Data The data to be written
* WriteCount The number of times to write
*Export parameter: None
*********************************************************************************************************************
*/
static void LCD_Fill_UseOneData(LCD_POSITION sPos , LCD_POSITION ePos , uint16_t Data , uint32_t WriteCount)
{
	Lcd_Driver.setcursor(sPos.x,sPos.y,ePos.x,ePos.y);
	Lcd_Driver.writeCMD(0x2c);//Sending a write GRAM command
	//Initialize the pending buffer, QSPI data stream SRAM->LCD and then keep refreshing this buffer
	for(uint32_t i=0;i<LCD_SENDBUF_HALFWORD_MAX;i++){
		lcdSendBuff[0][i] = GETCOLOR(Data);
	}
	LCD_CS_D();
	//Write to data
	uint32_t sendBytes = 0;
	uint32_t writeTotal = WriteCount*2;//RGB565    One dot occupies 2 bytes, SPI needs to send twice as many bytes
	while(1){
		if(writeTotal == 0)break;
		if(writeTotal >= LCD_SENDBUF_BYTEMAX)sendBytes = LCD_SENDBUF_BYTEMAX;
		else                                 sendBytes = writeTotal;
		QSPIDMA_SendBytes(LCD_QSPI , LCD_QSPIDMA_SEND_CHANNEL , (uint8_t *)(&lcdSendBuff[0][0]) , sendBytes);
		QSPIDMA_WaitEnd(LCD_QSPI , LCD_QSPIDMA_SEND_CHANNEL);
		writeTotal -= sendBytes;
	}
	LCD_CS_G();
}
/*
*********************************************************************************************************************
* Function: LCD_Fill_UseContinuousData Fill with a continuous piece of data
* Commonly used to display a complete image
* Entry parameter: sPos The coordinates of the starting point of the LCD to be written
* Data The data to be written
* dataWidth Data width
* dataHeight The height of the data.
* Export parameter: None
*********************************************************************************************************************
*/
static void LCD_Fill_UseContinuousData(LCD_POSITION sPos,const uint16_t* Data,uint16_t dataWidth,uint16_t dataHeight)
{
	uint32_t WriteCount=dataWidth*dataHeight;

	Lcd_Driver.setcursor(sPos.x,sPos.y,sPos.x+dataWidth-1,sPos.y+dataHeight-1);
	Lcd_Driver.writeCMD(0x2c);
	LCD_CS_D();
	
	if(((uint32_t)Data) & 0x20000000){
		
		TransferData_SramToLcd((uint8_t *)Data, WriteCount<<1);
	}
	else{
 		
		uint32_t flashAddr = (uint32_t)Data + READFLASH_ADDR_OFFSET;//The data address obtained in XIP mode needs to be restored to the flash physical address
		

		enter_XIPCritical();
 		TransferData_FlashToLcd(flashAddr, WriteCount<<1);
 		quit_XIPCritical();
	}
 	LCD_CS_G();
}
/*
*********************************************************************************************************************
* Function: LCD_Fill_UsePartContinuousData Use a specified part of a piece of continuous data to fill the LCD
* Commonly used for cutout display
* Entry parameter: DataBase The base address of the data, note that it is the starting address of the continuous data block, not the starting address of the area to be displayed
* WidthOffset The amount of data in each line of data (statistics based on uint16)
* dispLoc The location of the location to be displayed, the width height of the display
* dataPos The starting position of the data
* Export parameter: none
*********************************************************************************************************************
*/
static void LCD_Fill_UsePartContinuousData(const uint16_t* DataBase,uint16_t WidthOffset,WIDGET_LOCATION dispLoc,LCD_POSITION dataPos)
{
	
	uint16_t (* Data)[WidthOffset];
	Data=(uint16_t(*)[WidthOffset])DataBase;
	WidthOffset = WidthOffset*2;//Bytes
	uint32_t flashAddr = (uint32_t)DataBase + READFLASH_ADDR_OFFSET;
	flashAddr += (dataPos.y*WidthOffset);
	flashAddr += (dataPos.x<<1);

	Lcd_Driver.setcursor(dispLoc.x,dispLoc.y,dispLoc.x+dispLoc.width-1,dispLoc.y+dispLoc.height-1);
	Lcd_Driver.writeCMD(0x2c);
	LCD_CS_D();
	uint32_t x = 0;
	uint32_t y = 0;
	
	if(((uint32_t)DataBase) & 0x20000000){
		
		for(y=1;y<dispLoc.height;y++){  
			TransferData_SramToLcd((uint8_t *)(&Data[dataPos.y+y][dataPos.x]) , dispLoc.width*2);
		}
	}
	else{
		//Data in flash is not continuous and the amount of data per line is not large, 
		//so using DMA for data copy will lead to performance degradation, so DMA is not used for data copy.
		if(dispLoc.width <= LCD_SENDBUF_HALFWORD_MAX){
			for (x=0;x<dispLoc.width;x++)lcdSendBuff[0][x] = Data[dataPos.y+y][dataPos.x+x];
			for(y=1;y<dispLoc.height;y++){
				QSPIDMA_WaitEnd(LCD_QSPI , LCD_QSPIDMA_SEND_CHANNEL);
				QSPIDMA_SendBytes(LCD_QSPI , LCD_QSPIDMA_SEND_CHANNEL , (uint8_t *)(&lcdSendBuff[1-(y%2)][0]) , dispLoc.width*2);
				for (x=0;x<dispLoc.width;x++)lcdSendBuff[y%2][x] = Data[dataPos.y+y][dataPos.x+x];
			}
		}

		QSPIDMA_WaitEnd(LCD_QSPI , LCD_QSPIDMA_SEND_CHANNEL);
		QSPIDMA_SendBytes(LCD_QSPI , LCD_QSPIDMA_SEND_CHANNEL , (uint8_t *)(&lcdSendBuff[1-(y%2)][0]) , dispLoc.width*2);
		QSPIDMA_WaitEnd(LCD_QSPI , LCD_QSPIDMA_SEND_CHANNEL);
	}
	LCD_CS_G();
}

/*
*********************************************************************************************************************
* Function: LCD_Fill_UseContinuousDataSplitBit splits a piece of continuous data from bit to bit and fills the LCD with the background or foreground color respectively.
* Commonly used in the display of characters
* Entry parameter: DataBase The base address of the data, note that it is the starting address of the continuous data block, not the starting address of the area to be displayed
* CharWidthOffset The amount of data in each line of data (statistics based on uint16)
* dispLoc The starting position and height width of the display
* Export parameter: uint16_t Returns the coordinates of the last valid pixel point of each line, used to indicate the position offset of the next character
*********************************************************************************************************************
*/
static uint16_t LCD_Fill_UseContinuousDataSplitBit(const uint8_t* DataBase,uint16_t CharWidthOffset,WIDGET_LOCATION dispLoc)
{
	Lcd_Driver.setcursor(dispLoc.x,dispLoc.y,dispLoc.x+dispLoc.width-1,dispLoc.y+dispLoc.height-1);
	Lcd_Driver.writeCMD(0x2c);
	uint8_t (*charData)[CharWidthOffset];
	charData=(uint8_t(*)[CharWidthOffset])DataBase;//Convert a contiguous block of memory into a two-bit array to access
	uint16_t WriteData[2];
	uint16_t bytePos;
	uint16_t byteRemove;
	uint8_t  data;
	WriteData[0]=lcdPara.backColor;
	WriteData[1]=lcdPara.fontcolor;
	LCD_CS_D();	
		
	uint16_t maxWidth=0;
	uint32_t y = 0;
	uint32_t x = 0;
	if(dispLoc.width <= LCD_SENDBUF_HALFWORD_MAX){
		for (x=0;x<dispLoc.width;x++){
			bytePos=x/8;
			byteRemove=7-x%8;
			data=charData[y][bytePos];
			data>>=byteRemove;
			data&=0x01;
			if(data)if(maxWidth<x)maxWidth=x;
			
			lcdSendBuff[0][x] = GETCOLOR(WriteData[data]);//First read out the first row of data
		}
		for(y=1;y<dispLoc.height;y++){
			QSPIDMA_WaitEnd(LCD_QSPI , LCD_QSPIDMA_SEND_CHANNEL);
			QSPIDMA_SendBytes(LCD_QSPI , LCD_QSPIDMA_SEND_CHANNEL , (uint8_t *)(&lcdSendBuff[1-(y%2)][0]) , dispLoc.width*2);
			for (x=0;x<dispLoc.width;x++){
				bytePos=x/8;//The data of this bit is in that byte
				byteRemove=7-x%8;//Number of bits of data to be shifted
				data=charData[y][bytePos];
				data>>=byteRemove;
				data&=0x01;
				if(data)if(maxWidth<x)maxWidth=x;		
				lcdSendBuff[y%2][x] = GETCOLOR(WriteData[data]);
			}
		}
	}
	QSPIDMA_WaitEnd(LCD_QSPI , LCD_QSPIDMA_SEND_CHANNEL);
	QSPIDMA_SendBytes(LCD_QSPI , LCD_QSPIDMA_SEND_CHANNEL , (uint8_t *)(&lcdSendBuff[1-(y%2)][0]) , dispLoc.width*2);
	QSPIDMA_WaitEnd(LCD_QSPI , LCD_QSPIDMA_SEND_CHANNEL);//Sending the last data out
	
	LCD_CS_G();
	
 	return maxWidth;
}

/*
*********************************************************************************************************************
* Function: LCD_DrawPoint, LCD draws a point, using LCD descriptor foreground color
*Entry parameters: x,y:coordinates
*Exit parameter: None
*********************************************************************************************************************
*/ 
static void LCD_DrawPoint(uint16_t x,uint16_t y)
{
	LCD_POSITION sPos={x,y};
	LCD_POSITION ePos={x,y};
	LCD_Fill_UseOneData(sPos,ePos,lcdPara.fontcolor,1);
}
/*
*********************************************************************************************************************
* Function: LCD_ReadPoint, LCD reads a point
*Entry parameters: x,y:coordinates
*Exit parameter: uint32_t, the RGB value of the color of the point
*********************************************************************************************************************
*/
static uint16_t LCD_ReadPoint(uint16_t x,uint16_t y)
{
	uint16_t r=0,g=0,b=0;
	return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));
}
/*
*********************************************************************************************************************
* Function: LCD_Clear, lcd clear screen display, monochrome, background color of LCD descriptor, full screen
*Entry parameter: None
*Exit parameter: None
*********************************************************************************************************************
*/
static void LCD_Clear(void)
{ 
	uint32_t totalpoint=lcdPara.width;
	totalpoint*=lcdPara.height; 			
	LCD_POSITION sPos={0,0};
	LCD_POSITION ePos={lcdPara.width-1,lcdPara.height-1};
 	LCD_Fill_UseOneData(sPos,ePos,lcdPara.backColor,totalpoint);
	
}
/*
*********************************************************************************************************************
* Function: LCD_Fill, fills a specified part of the LCD using the foreground color of the LCD descriptor
*Entry parameter: sx sy starting coordinate
* ex ey end point coordinates    
*Exit parameter: None
*********************************************************************************************************************
*/
static void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey)
{          
	uint32_t xlen=ex-sx+1;
	uint32_t ylen=ey-sy+1; 
	LCD_POSITION sPos={sx,sy};
	LCD_POSITION ePos={ex,ey};
	LCD_Fill_UseOneData(sPos,ePos,lcdPara.fontcolor,xlen*ylen);
}

const LCD_DESCRIPTOR Lcd_Des={
	LCD_DrawPoint,
	LCD_ReadPoint,
	LCD_Fill,
	LCD_Fill_UseOneData,
	LCD_Fill_UseContinuousData,
	LCD_Fill_UsePartContinuousData,
	LCD_Fill_UseContinuousDataSplitBit,		//Split a continuous piece of data into bits and fill the LCD with the background or foreground color respectively, often used for character display
	LCD_Clear,														
};


