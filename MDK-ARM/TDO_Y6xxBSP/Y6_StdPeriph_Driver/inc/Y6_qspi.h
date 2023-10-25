 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Y6_QSPI_H
#define __Y6_QSPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "Y6.h"

/** @addtogroup Y6_StdPeriph_Driver
  * @{
  */

/** @addtogroup QSPI
  * @{
  */

/** @defgroup QSPI_Exported_Types
  * @{
  */

typedef enum {QSPI_STD, QSPI_DUAL, QSPI_QUAD} QSPIModeSelect;
typedef struct
{
  																
  uint32_t QSPI_CPOL;                /*!< Specifies the serial clock steady state.
                                         This parameter can be a value of @ref QSPI_Clock_Polarity */

  uint32_t QSPI_CPHA;                /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be a value of @ref QSPI_Clock_Phase */            

  uint32_t QSPI_FirstBit;            /*!< Specifies whether data transfers start from MSB or LSB bit.
                                         This parameter can be a value of @ref QSPI_MSB_LSB_transmission */

  uint32_t QSPI_ClockDiv;              /*!< Specifies the DIVIDE parameter for clock frequency of the QSPI controller.
                                            					This even number can be a value between 0x2 and 0xFE. */

  uint32_t QSPI_ClockRate;            /*!<Specifies the RATE parameter for clock frequency of the QSPI controller.
						 				   This parameter can be a value between 0x0 and 0xFF.	*/
  uint32_t QSPI_SlaveMode;             /*!< Specifies the SPI is master mode or slaver mode.
                                             This parameter can be a value of @ref QSPI_SLAVE_MODE_Select */
  QSPIModeSelect QSPI_ModeSelect;     /*!< Specifies the SPI MODE:SPI standard mode/SPI Dual mode/SPI Quad mode. */
  
	uint32_t QSPI_FrameLength;           /*!< Specifies the SPI frame length. 
                                           This parameter can be a value of @ref QSPI_Wrod_Length_setting*/
} QSPI_InitTypeDef;



typedef struct
{
  uint32_t QSPI_DUPLEX;			/*!< Specifies QSPI work mode:.Full duplex /half duplex.
                                 This parameter can be a value of @ref QSPI_data_Duplex  */

  uint32_t QSPI_DataLength;     /*!< Specifies the number of data bytes to be transferred. */
 
  uint32_t QSPI_TransferDir;    /*!< Specifies the data transfer direction, whether the transfer is a read or write.
                                     				This parameter can be a value of @ref QSPI_Transfer_Direction */
} QSPI_DataInitTypeDef;


typedef enum {CAP_DLY_NONE=0, CAP_DLY_1CLK=1, CAP_DLY_2CLK=2, CAP_DLY_3CLK=3} QSPICapDly;

/**
  * @}
  */



/** @defgroup QSPI_PERIPH_CHECK
  * @{
  */
#define IS_QSPI_MODE(MODE) 		( (MODE==QSPI_STD)||(MODE==QSPI_DUAL)||(MODE==QSPI_QUAD) )
/**
  * @}
  */


/** @addtogroup QSPI_SLAVE_MODE_Select
  * @{
  */
#define QSPI_SLAVE_MODE       ((uint32_t)0x00000100) 
#define QSPI_MASTER_MODE      ((uint32_t)0x00000000) 
#define IS_QPSI_MASTER_OR_SLAVE_MODE(mode)  (((mode) == QSPI_SLAVE_MODE) || \
                                             ((mode) == QSPI_MASTER_MODE))
/**
  * @}
  */

/** @defgroup QSPI_Hardware_Flow_Control 
  * @{
  */
#define QSPI_PowerState_ON                   ((uint32_t)0x00000001)
#define QSPI_PowerState_OFF                  ((uint32_t)0x00000000)
#define IS_QSPI_POWER_STATE(STATE) (((STATE) == QSPI_PowerState_ON) || ((STATE) == QSPI_PowerState_OFF)) 
/**
  * @}
  */ 



/** @defgroup QSPI_Clock_Polarity 
  * @{
  */
#define QSPI_CPOL_Low                    ((uint32_t)0x00000000)
#define QSPI_CPOL_High                   ((uint32_t)0x00000200)
#define IS_QSPI_CPOL(CPOL) (((CPOL) == QSPI_CPOL_Low) || \
                           ((CPOL) == QSPI_CPOL_High))
/**
  * @}
  */


/** @defgroup QSPI_Clock_Phase 
  * @{
  */
#define QSPI_CPHA_1Edge                  ((uint32_t)0x00000000)
#define QSPI_CPHA_2Edge                  ((uint32_t)0x00000400)
#define IS_QSPI_CPHA(CPHA) (((CPHA) == QSPI_CPHA_1Edge) || \
                           ((CPHA) == QSPI_CPHA_2Edge))
/**
  * @}
  */


/** @defgroup QSPI_MSB_LSB_transmission 
  * @{
  */
#define QSPI_FirstBit_MSB                ((uint32_t)0x00000000)
#define QSPI_FirstBit_LSB                ((uint32_t)0x00400000)
#define IS_QSPI_FIRST_BIT(BIT) (((BIT) == QSPI_FirstBit_MSB) || \
                               ((BIT) == QSPI_FirstBit_LSB))
/**
  * @}
  */

/** @defgroup QSPI_ClockDiv_setting 
  * @{
  */
#define IS_QSPI_ClockDiv_setting(DIV) ( (((DIV)&0xFFFF00FF)==0x0)&&((DIV)!=0x0) )
/**
  * @}
  */

/** @defgroup QSPI_ClockRate_setting 
  * @{
  */
// #define IS_QSPI_ClockRate_setting(RATE) ( (((RATE)&0xFFFFFF00)==0x0)&&((RATE)!=0x0) )
#define IS_QSPI_ClockRate_setting(RATE) ( (((RATE)&0xFFFFFF00)==0x0) )
/**
  * @}
  */

/** @addtogroup QSPI_Wrod_Length_setting
  * @{
  */
#define QSPI_FRAME_LENGTH_4Bit       ((uint32_t)0x00000018)
#define QSPI_FRAME_LENGTH_8Bit       ((uint32_t)0x00000038)
#define QSPI_FRAME_LENGTH_16Bit      ((uint32_t)0x00000078)
#define QSPI_FRAME_LENGTH_24Bit      ((uint32_t)0x000000b8)
#define QSPI_FRAME_LENGTH_32Bit      ((uint32_t)0x000000f8)
#define IS_QSPI_FRAME_LENGTH(wl)     (((wl) == QSPI_FRAME_LENGTH_4Bit) || \
                                     ((wl) == QSPI_FRAME_LENGTH_8Bit) || \
                                     ((wl) == QSPI_FRAME_LENGTH_16Bit) || \
                                     ((wl) == QSPI_FRAME_LENGTH_24Bit) || \
                                     ((wl) == QSPI_FRAME_LENGTH_32Bit))
/**
  * @}
  */



/** @defgroup QSPI_data_Duplex 
  * @{
  */  
#define QSPI_FullDuplex  ((uint32_t)0x00000000)
#define QSPI_HalfDuplex  ((uint32_t)0x10000000)
#define IS_QSPI_Duplex(DIRECTION) (((DIRECTION) == QSPI_FullDuplex) || \
                                     	  ((DIRECTION) == QSPI_HalfDuplex))
/**
  * @}
  */


/** @defgroup QSPI_Transfer_Direction 
  * @{
  */  
#define QSPI_Transfer_Write  ((uint32_t)0x00000000)
#define QSPI_Transfer_Read  ((uint32_t)0x04000000)
#define IS_QSPI_QSPI_Direction(DIRECTION) (((DIRECTION) == QSPI_Transfer_Write) || \
                                     	  ((DIRECTION) == QSPI_Transfer_Read))
/**
  * @}
  */


/** @defgroup QSPI_Interrupt_soucres 
  * @{
  */
#define QSPI_IT_RXOVEFLW                   ((uint32_t)0x00008000)
#define QSPI_IT_RXTIMEOUT					((uint32_t)0x00020000)
#define QSPI_IT_RXFIFOHF					((uint32_t)0x00080000)
#define QSPI_IT_TXFIFOHE					((uint32_t)0x00200000)


#define IS_QSPI_IT(IT) ( ((IT) == QSPI_IT_RXOVEFLW) ||((IT) == QSPI_IT_RXTIMEOUT) ||((IT) == QSPI_IT_RXFIFOHF) ||((IT) == QSPI_IT_TXFIFOHE) )

#define IS_QSPI_GET_IT(IT) ( ((IT) == QSPI_IT_RXOVEFLW) ||((IT) == QSPI_IT_RXTIMEOUT) ||((IT) == QSPI_IT_RXFIFOHF) ||((IT) == QSPI_IT_TXFIFOHE) )
                            
#define IS_QSPI_CLEAR_IT(IT) ( ((IT) == QSPI_IT_RXOVEFLW) ||((IT) == QSPI_IT_RXTIMEOUT) ||((IT) == QSPI_IT_RXFIFOHF) ||((IT) == QSPI_IT_TXFIFOHE) )
/**
  * @}
  */ 


/** @defgroup QSPI_Status_flag 
  * @{
  */  
#define IS_QSPI_STATUS_FLAG(FLAG) ( (FLAG)&0x0ff00ff1 )
/**
  * @}
  */ 



/** @defgroup QSPI_Exported_Functions
  * @{
  */
void QSPI_SetPowerState(QSPI_TypeDef* QSPIx, uint32_t QSPI_PowerState);
void QSPI_HwInit(QSPI_TypeDef* QSPIx, QSPI_InitTypeDef* QSPI_InitStruct);
void QSPI_ModeSet(QSPI_TypeDef* QSPIptr, QSPIModeSelect ModeSelect);
uint32_t QSPI_GetPowerState(QSPI_TypeDef* QSPIx);
void QSPI_ITConfig(QSPI_TypeDef* QSPIx, uint32_t QSPI_IT, FunctionalState NewState);
void QSPI_DMACmd(QSPI_TypeDef* QSPIx, FunctionalState NewState);
void QSPI_CS_Low(QSPI_TypeDef* QSPIx);
void QSPI_CS_High(QSPI_TypeDef* QSPIx);
void QSPI_DataConfig(QSPI_TypeDef* QSPIx, QSPI_DataInitTypeDef* QSPI_DataInitStruct);
uint32_t QSPI_ReadData(QSPI_TypeDef* QSPIx);
void QSPI_WriteCMD(QSPI_TypeDef* QSPIptr, uint32_t cmd);
void QSPI_WriteData(QSPI_TypeDef* QSPIx, uint32_t Data);
void QSPI_EBmodeSet(QSPI_TypeDef* QSPIx,uint8_t fun, FunctionalState NewState);
void QSPI_FirstBitSet(QSPI_TypeDef *QSPIptr, uint32_t Qspi_FirstBit);
FlagStatus QSPI_GetFlagStatus(QSPI_TypeDef* QSPIx, uint32_t QSPI_FLAG);				
ITStatus QSPI_GetITStatus(QSPI_TypeDef* QSPIx, uint32_t QSPI_IT);
void QSPI_ClearITPendingBit(QSPI_TypeDef* QSPIx, uint32_t QSPI_IT);
void QSPI_FrameLengthSet(QSPI_TypeDef* QSPIptr, uint8_t wl);
void QSPI_QpiSet(QSPI_TypeDef* QSPIptr, uint8_t enable);
void QSPI_SetBusyDelay(QSPI_TypeDef *QSPIptr, uint8_t dly);
void QSPI_SetCaptureDelay(QSPI_TypeDef *QSPIptr, QSPICapDly dly);

//int QSPI_SpiTX(QSPI_TypeDef *QSPIptr, uint8_t *data, uint32_t num);
//int QSPI_SpiRX(QSPI_TypeDef* QSPIptr,uint8_t *data,uint32_t num);

#ifdef __cplusplus
}
#endif

#endif /* __Y6_QSPI_H */
/**
  * @
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2013 TDO *****END OF FILE****/
