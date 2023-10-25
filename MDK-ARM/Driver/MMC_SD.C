#include "mmc_sd.h"			   
#include "Y6.h"
#include "Y6_gpio.h"
#include "Y6_qspi.h"
#include "Y6_xip_write.h"
#include "stdio.h"

uint8_t  SD_Type=0;
__align(4) static uint8_t SD_WriteReadBuf[32];


void SD_SPI_Init(void)
{
	//QSPI_InitTypeDef QSPI_InitStructure;
	GPIO_SetPinMux(GPIO0, GPIO_Pin_5,GPIO_FUNCTION_0);//QSPI1_TF_CS 
	GPIO_SetPinDir(GPIO0, GPIO_Pin_5,GPIO_Mode_OUT);  //QSPI1_TF_CS 
	GPIO_SetPinMux(GPIO1, GPIO_Pin_28,GPIO_FUNCTION_0);//QSPI1_XPT_CS 
	GPIO_SetPinDir(GPIO1, GPIO_Pin_28,GPIO_Mode_OUT);  //QSPI1_XPT_CS 
	GPIO_SetPin(GPIO0, GPIO_Pin_5);//QSPI1_TF_CS 
	GPIO_SetPin(GPIO1, GPIO_Pin_28);//QSPI1_XPT_CS 
	
	RCC->AHBCLKCTRL0_SET=1<<14;
	RCC->PRESETCTRL0_CLR=1<<14;
	RCC->PRESETCTRL0_SET=1<<14;
	
	RCC->QUADSPI1CLKDIV = 8;//384/8=48mhz QSPI1 CLK=48MHZ
	
	QSPI1->CTRL0_CLR=1<<29;

	GPIO_SetPinMux(GPIO0, GPIO_Pin_13, GPIO_FUNCTION_3);//QSPI1_MOSI 
	GPIO_SetPinMux(GPIO0, GPIO_Pin_7, GPIO_FUNCTION_3);//QSPI_CLK 
	GPIO_SetPinMux(GPIO0, GPIO_Pin_6, GPIO_FUNCTION_3);//QSPI1_MISO 	
	
	QSPI1->CTRL1=0x00002038; //The SPI DMA needs to be enabled to automatically clear the RUN with the help of the DMA mechanism.
	QSPI1->TIMING=0x00000400;
	QSPI1->CTRL0_SET=1<<28;
}


void SDSpiCS_Low(void)
{
	GPIO0->DT_CLR=GPIO_Pin_5;//QSPI1_TF_CS 
}
void SDSpiCS_High(void)
{
	GPIO0->DT_SET=GPIO_Pin_5;//QSPI1_TF_CS 
}


 
//When SD card initialization, it needs low speed
void SD_SPI_SpeedLow(void)
{
 	
	QSPI1->CTRL0_CLR = 1<<29;
	QSPI1->TIMING &= 0xffff00ff;
	QSPI1->TIMING |= (128<<8);
}
//When the SD card is working normally, the high speed
void SD_SPI_SpeedHigh(void)
{
	QSPI1->CTRL0_CLR = 1<<29;
	QSPI1->TIMING &= 0xffff00ff;
	QSPI1->TIMING |= (4<<8);
}
void SD_ExternCLk(void)
{
	SD_WriteReadBuf[0]=0xff;
 	xipTX(QSPI1,SD_WriteReadBuf,1);
}
///////////////////////////////////////////////////////////////////////////////////
//Deselect, release SPI bus
void SD_DisSelect(void)
{
	SDSpiCS_High();
	SD_ExternCLk();
}
//select the sd card and wait for the card to be ready OK
//return value: 0,success;1,failure;
uint8_t SD_Select(void)
{
	SDSpiCS_Low();
	if(SD_WaitReady()==0)return 0;
	SD_DisSelect();
	return 1;
}
//wait for the card to be ready
//return value:0,ready;other,error code
uint8_t SD_WaitReady(void)
{
	uint32_t t=0;
	do
	{
		xipRX(QSPI1,SD_WriteReadBuf,1);
		if(SD_WriteReadBuf[0]==0XFF)return 0;
		t++;		  	
	}while(t<0XFFFFFF);
	return 1;
}
//Wait for SD card response
//Response: the response value to get
// Return value: 0, the response value was successfully obtained
// Other, failed to get the response value
static uint8_t SD_GetResponse(uint8_t Response)
{
	uint16_t Count=0xFFFF;  						  
	while (Count){
		xipRX(QSPI1,SD_WriteReadBuf,1);
		if(SD_WriteReadBuf[0]==Response)break;
		Count--;	  
	}
	if (Count==0)return MSD_RESPONSE_FAILURE;
	else return MSD_RESPONSE_NO_ERROR;
}
//read the contents of a packet from the sd card
//buf:data buffer
//len:the length of the data to be read.
//return value: 0, success; other, failure;	
uint8_t SD_RecvData(uint8_t*buf,uint16_t len)
{			  	  
	if(SD_GetResponse(0xFE))return 1;
    xipRX(QSPI1,buf,len);
    
		SD_WriteReadBuf[0]=0xff;
		SD_WriteReadBuf[1]=0xff;
		xipTX(QSPI1,SD_WriteReadBuf,2);							  					    
    return 0;
}
//write the contents of a packet to the sd card 512 bytes
//buf:data buffer
//cmd:command
//return value: 0, success; other, failure;		
uint8_t SD_SendBlock(uint8_t*buf,uint8_t cmd)
{		  	  
	if(SD_WaitReady())return 1;
	SD_WriteReadBuf[0]=cmd;
	xipTX(QSPI1,SD_WriteReadBuf,1);
	if(cmd!=0XFD)
	{
		xipTX(QSPI1,buf,SD_BLOCK_MAXLEN);
		SD_WriteReadBuf[0]=0xff;
		SD_WriteReadBuf[1]=0xff;
		xipTX(QSPI1,SD_WriteReadBuf,3);	
		xipRX(QSPI1,SD_WriteReadBuf,1);

		if((SD_WriteReadBuf[0]&0x1F)!=0x05)return 2;								  					    
	}						 									  					    
  return 0;
}

//Send a command to the SD card
// input: uint8_t cmd command 
// 		uint32_t arg command parameter
// 		uint8_t crc crc checksum value	   
// return value: the response returned by the SD card															  
uint8_t SD_SendCmd(uint8_t cmd, uint32_t arg, uint8_t crc)
{	
	uint8_t Retry=0; 
	//SD_DisSelect();
	if(SD_Select())return 0XFF;
	
	SD_WriteReadBuf[0]=cmd | 0x40;
	SD_WriteReadBuf[1]=arg >> 24;
	SD_WriteReadBuf[2]=arg >> 16;
	SD_WriteReadBuf[3]=arg >> 8;
	SD_WriteReadBuf[4]=arg >> 0;
	SD_WriteReadBuf[5]=crc;
	xipTX(QSPI1,SD_WriteReadBuf,6);
	if(cmd==CMD12){
		SD_WriteReadBuf[1]=0xff;
		xipTX(QSPI1,SD_WriteReadBuf,1);//Skip a stuff byte when stop reading
	}
  
	Retry=0X1F;
	do{
		xipRX(QSPI1,SD_WriteReadBuf,1);
	}while((SD_WriteReadBuf[0]&0X80) && Retry--);	 
	
  return SD_WriteReadBuf[0];
}		    																			  
//Get the CID information of the SD card, including the manufacturer information
//Input: uint8_t *cid_data(memory to store CID, at least 16Byte)	  
// return value: 0: NO_ERR
// 1: Error													   
uint8_t SD_GetCID(uint8_t *cid_data)
{
	uint8_t r1;	   

	r1=SD_SendCmd(CMD10,0,0x01);
	if(r1==0x00){
		r1=SD_RecvData(cid_data,16); 
  }
	SD_DisSelect();
	if(r1)return 1;
	else return 0;
}																				  
//Get the CSD information of the SD card, including capacity and speed information
//Input:uint8_t *cid_data(memory to store CID, at least 16Byte)	    
// return value: 0: NO_ERR
// 1: Error														   
uint8_t SD_GetCSD(uint8_t *csd_data)
{
    uint8_t r1;	 
    r1=SD_SendCmd(CMD9,0,0x01);
    if(r1==0)
	{
    	r1=SD_RecvData(csd_data, 16);
    }
	SD_DisSelect();
	if(r1)return 1;
	else return 0;
}  
//Get the total number of sectors of the SD card (number of sectors)   
// Return value:0: Error in fetching capacity 
// Other:SD card capacity (number of sectors/512 bytes)
// The number of bytes per sector must be 512, because if it is not 512, the initialization will not pass.														  
uint32_t SD_GetSectorCount(void)
{
    uint8_t csd[16];
    uint32_t Capacity;  
    uint8_t n;
	uint16_t csize;  					    
	
    if(SD_GetCSD(csd)!=0) return 0;	    
  
    if((csd[0]&0xC0)==0x40)	 //V2.00 card
    {	
		csize = csd[9] + ((uint16_t)csd[8] << 8) + 1;
		Capacity = (uint32_t)csize << 10; 		   
    }else//V1.XX card
    {	
		n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
		csize = (csd[8] >> 6) + ((uint16_t)csd[7] << 2) + ((uint16_t)(csd[6] & 3) << 10) + 1;
		Capacity= (uint32_t)csize << (n - 9);   
    }
    return Capacity;
}

uint8_t SD_Initialize(void)
{
	uint8_t r1; // store the return value of the SD card
	uint16_t retry; // used for timeout counting
	uint16_t i;
	
	SD_SPI_Init(); // initialize IO
 	SD_SPI_SpeedLow(); // set to low speed mode  
	
 	for(i=0;i<10;i++){
		SD_WriteReadBuf[i]=0xff;
	}
	xipTX(QSPI1,SD_WriteReadBuf,10);//Send a minimum of 74 pulses
	retry=20;	
	do
	{
		
		r1=SD_SendCmd(CMD0,0,0x95);

	}while((r1!=0X01) && retry--);
 	SD_Type=0;
	if(r1==0X01)
	{
		if(SD_SendCmd(CMD8,0x1AA,0x87)==1)//SD V2.0
		{
			xipRX(QSPI1,SD_WriteReadBuf,4);//Get trailing return value of R7 resp
			if(SD_WriteReadBuf[2]==0X01&&SD_WriteReadBuf[3]==0XAA)//Does the card support 2.7~3.6V
			{
				retry=0XFFFE;
				do
				{
					SD_SendCmd(CMD55,0,0X01);	
					r1=SD_SendCmd(CMD41,0x40000000,0X01);
				}while(r1&&retry--);
				if(retry&&SD_SendCmd(CMD58,0,0X01)==0)
				{
					xipRX(QSPI1,SD_WriteReadBuf,4);
					if(SD_WriteReadBuf[0]&0x40)SD_Type=SD_TYPE_V2HC;
					else SD_Type=SD_TYPE_V2;   
				}
			}
		}
		else//SD V1.x/ MMC	V3
		{
			SD_SendCmd(CMD55,0,0X01);		
			r1=SD_SendCmd(CMD41,0,0X01);	
			if(r1<=1)
			{		
				SD_Type=SD_TYPE_V1;
				retry=0XFFFE;
				do 
				{
					SD_SendCmd(CMD55,0,0X01);	
					r1=SD_SendCmd(CMD41,0,0X01);
				}while(r1&&retry--);
			}else
			{
				SD_Type=SD_TYPE_MMC;
				retry=0XFFFE;
				do 
				{											    
					r1=SD_SendCmd(CMD1,0,0X01);
				}while(r1&&retry--);  
			}
			if(retry==0||SD_SendCmd(CMD16,512,0X01)!=0)SD_Type=SD_TYPE_ERR;
		}
	}
	SD_DisSelect();
	SD_SPI_SpeedHigh();
	if(SD_Type)return 0;
	else if(r1)return r1; 	   
	return 0xaa;
}
//read SD card
//buf:data buffer
//sector:sectors
//cnt:number of sectors
//return value: 0,ok;other,fail.
uint8_t SD_ReadDisk(uint8_t*buf,uint32_t sector,uint8_t cnt)
{
	uint8_t r1;
	if(SD_Type!=SD_TYPE_V2HC)sector<<= 9;
	if(cnt==1)
	{
		r1=SD_SendCmd(CMD17,sector,0X01);
		if(r1==0)
		{
			r1=SD_RecvData(buf,SD_BLOCK_MAXLEN);//// Receive 512 bytes	   
		}
	}else
	{
		r1=SD_SendCmd(CMD18,sector,0X01);
		do
		{
			r1=SD_RecvData(buf,SD_BLOCK_MAXLEN); 
			buf+=512;  
		}while(--cnt && r1==0); 	
		SD_SendCmd(CMD12,0,0X01);	
	}   
	SD_DisSelect();
	return r1;//
}
//write SD card
//buf:data buffer
//sector:start sector
//cnt:number of sectors
//return value: 0,ok;other,fail.
uint8_t SD_WriteDisk(uint8_t*buf,uint32_t sector,uint8_t cnt)
{
	uint8_t r1;
	if(SD_Type!=SD_TYPE_V2HC)sector *= SD_BLOCK_MAXLEN;
	if(cnt==1)
	{
		r1=SD_SendCmd(CMD24,sector,0X01);
		if(r1==0)
		{
			r1=SD_SendBlock(buf,0xFE);   
		}
	}else
	{
		if(SD_Type!=SD_TYPE_MMC)
		{
			SD_SendCmd(CMD55,0,0X01);	
			SD_SendCmd(CMD23,cnt,0X01);	
		}
 		r1=SD_SendCmd(CMD25,sector,0X01);
		if(r1==0)
		{
			do
			{
				r1=SD_SendBlock(buf,0xFC); 
				buf+=SD_BLOCK_MAXLEN;  
			}while(--cnt && r1==0);
			r1=SD_SendBlock(0,0xFD);
	}   
	SD_DisSelect();
	return r1;//
}	
}




