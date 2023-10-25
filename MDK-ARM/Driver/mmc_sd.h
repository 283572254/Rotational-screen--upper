#ifndef _MMC_SD_H_
#define _MMC_SD_H_		 
 	#include "stdint.h"					    	 
// 
#define SD_TYPE_ERR     0X00
#define SD_TYPE_MMC     0X01
#define SD_TYPE_V1      0X02
#define SD_TYPE_V2      0X04
#define SD_TYPE_V2HC    0X06	   
//SD card command table 	   
#define CMD0 		0 			//card reset
#define CMD1 		1			
#define CMD8 		8 			//command 8 , SEND_IF_COND
#define CMD9 		9 			//command 9 , read CSD data
#define CMD10 		10 			//command 10, read CID data
#define CMD12 		12 			//command 12, stop data transfer
#define CMD16 		16 			//command 16, set SectorSize should return 0x00
#define CMD17 		17 			//command 17, read the sector
#define CMD18 		18 			//command 18, read Multi sector
#define CMD23 		23 			//command 23, set multi-sector to pre-write N blocks before writing
#define CMD24 		24 			//command 24, write sector
#define CMD25 		25 			//command 25, write Multi sector
#define CMD41 		41 			//command 41, should return 0x00
#define CMD55 		55 			//command 55, should return 0x01
#define CMD58 		58 			//command 58, read OCR information
#define CMD59 		59 			//command 59, enable/disable CRC, should return 0x00
//Data writing response word meaning
#define MSD_DATA_OK                0x05
#define MSD_DATA_CRC_ERROR         0x0B
#define MSD_DATA_WRITE_ERROR       0x0D
#define MSD_DATA_OTHER_ERROR       0xFF
//SD card response mark word
#define MSD_RESPONSE_NO_ERROR      0x00
#define MSD_IN_IDLE_STATE          0x01
#define MSD_ERASE_RESET            0x02
#define MSD_ILLEGAL_COMMAND        0x04
#define MSD_COM_CRC_ERROR          0x08
#define MSD_ERASE_SEQUENCE_ERROR   0x10
#define MSD_ADDRESS_ERROR          0x20
#define MSD_PARAMETER_ERROR        0x40
#define MSD_RESPONSE_FAILURE       0xFF
 							   						 	 			    	  
#define SD_BLOCK_MAXLEN            512
		
void 			SD_SPI_Init(void);
void 			SD_SPI_SpeedLow(void);
void 			SD_SPI_SpeedHigh(void);
void 			SD_ExternCLk(void);
void 			SDSpiCS_Low(void);
void 			SDSpiCS_High(void);
uint8_t 	SD_WaitReady(void);																			
uint8_t 	SD_GetResponse(uint8_t Response);												
uint8_t 	SD_Initialize(void);																	
uint8_t 	SD_ReadDisk(uint8_t*buf,uint32_t sector,uint8_t cnt);		
uint8_t 	SD_WriteDisk(uint8_t*buf,uint32_t sector,uint8_t cnt);	
uint32_t  SD_GetSectorCount(void);   														
uint8_t 	SD_GetCID(uint8_t *cid_data);                 				
uint8_t 	SD_GetCSD(uint8_t *csd_data);                 					
	
#endif




