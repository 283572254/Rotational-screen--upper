 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Y6_UART_H
#define __Y6_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "Y6.h"
#include "Y6_rcc.h"
#include "Y6_dma.h"


/** @addtogroup Y6_StdPeriph_Driver
  * @{
  */

/** @addtogroup UART
  * @{
  */ 

/** @defgroup UART_Exported_Types
  * @{
  */ 

/** 
  * @brief  UART Init Structure definition  
  */ 
typedef struct
{
  uint32_t UART_TXIFLSEL;

  uint32_t UART_RXIFLSEL;

  uint32_t UART_FEN;

  uint32_t UART_BaudRate;

  uint32_t UART_WordLength;          

  uint32_t UART_StopBits;           

  uint32_t UART_Parity;              

  uint32_t UART_Mode;               

  uint32_t UART_HardwareFlowControl; 

  uint32_t UART_SoftwareFlowControl;

} UART_InitTypeDef;

/** 
  * @brief  UART RS485 Init Structure definition  
  */ 
  
typedef struct
{

  uint8_t UART_RS485_MODE;   

  uint8_t UART_RS485_DCTRL; 

  uint8_t UART_RS485_ONIV;

} UART_RS485InitTypeDef;

/**
  * @}
  */ 

/** @defgroup UART_Exported_Constants
  * @{
  */ 
  
#define IS_UART_ALL_PERIPH(PERIPH)          (((PERIPH) == UART0) || \
                                            ((PERIPH) == UART1)  || \
                                            ((PERIPH) == UART2))

#define IS_UART_FC_PERIPH(PERIPH)           (((PERIPH) == UART0) || \
                                            ((PERIPH) == UART1)  || \
                                            ((PERIPH) == UART2))

#define IS_UART_IRDA_PERIPH(PERIPH)         (((PERIPH) == UART0) || \
                                            ((PERIPH) == UART1)  || \
                                            ((PERIPH) == UART2))

#define IS_UART_DMA_PERIPH(PERIPH)          (((PERIPH) == UART0) || \
                                            ((PERIPH) == UART1)  || \
                                            ((PERIPH) == UART2))
/** @defgroup UART_Word_Length 
  * @{
  */ 
  
#define UART_WordLength_5b                  ((uint32_t)0x00000000)
#define UART_WordLength_6b                  ((uint32_t)0x00000020)
#define UART_WordLength_7b                  ((uint32_t)0x00000040)
#define UART_WordLength_8b                  ((uint32_t)0x00000060)
#define IS_UART_WORD_LENGTH(LENGTH)         (((LENGTH) == UART_WordLength_5b) || \
                                            ((LENGTH) == UART_WordLength_6b) || \
                                            ((LENGTH) == UART_WordLength_7b) || \
                                            ((LENGTH) == UART_WordLength_8b))
/**
  * @}
  */ 

/** @defgroup UART_Stop_Bits 
  * @{
  */ 
  
#define UART_StopBits_1                     ((uint32_t)0x00000000)
#define UART_StopBits_2                     ((uint32_t)0x00000008)
#define IS_UART_STOPBITS(STOPBITS)          (((STOPBITS) == UART_StopBits_1)   || \
                                            ((STOPBITS) == UART_StopBits_2))
/**
  * @}
  */ 

/** @defgroup UART_Parity 
  * @{
  */ 
  
#define UART_Parity_No                      ((uint32_t)0x00000000)
#define UART_Parity_Odd                     ((uint32_t)0x00000002)
#define UART_Parity_Even                    ((uint32_t)0x00000006)
#define UART_Parity_EPS_0                   ((uint32_t)0x00000082)
#define UART_Parity_EPS_1                   ((uint32_t)0x00000086)
 
#define IS_UART_PARITY(PARITY)              (((PARITY) == UART_Parity_No)       || \
                                            ((PARITY) == UART_Parity_Even)     || \
                                            ((PARITY) == UART_Parity_Odd)      || \
                                            ((PARITY) == UART_Parity_EPS_0)    || \
                                            ((PARITY) == UART_Parity_EPS_1))
/**
  * @}
  */ 

/** @defgroup UART_Mode 
  * @{
  */ 
  
#define UART_Mode_Tx                        ((uint32_t)0x00000100)
#define UART_Mode_Rx                        ((uint32_t)0x00000200)
#define IS_UART_MODE(MODE)                  (((MODE) == UART_Mode_Tx) || \
                                            ((MODE) == UART_Mode_Rx) || \
                                            ((MODE) == (UART_Mode_Rx|UART_Mode_Tx)))
/**
  * @}
  */ 

/** @defgroup UART_Hardware_Flow_Control 
  * @{
  */ 
#define UART_HardwareFlowControl_None       ((uint32_t)0x00000000)
#define UART_HardwareFlowControl_RTS        ((uint32_t)0x00004000)
#define UART_HardwareFlowControl_CTS        ((uint32_t)0x00008000)
#define UART_HardwareFlowControl_RTS_CTS    ((uint32_t)0x0000C000)
#define IS_UART_HARDWARE_FLOW_CONTROL(CONTROL)\
                                            (((CONTROL) == UART_HardwareFlowControl_None) || \
                                            ((CONTROL) == UART_HardwareFlowControl_RTS)  || \
                                            ((CONTROL) == UART_HardwareFlowControl_CTS)  || \
                                            ((CONTROL) == UART_HardwareFlowControl_RTS_CTS))

/**
  * @}
  */ 

/** @defgroup SoftwareFlowControl 
  * @{
  */ 
  
#define UART_SoftwareFlowControl_None       ((uint32_t)0x00000000)
#define UART_SoftwareFlowControl_RTS        ((uint32_t)0x00000800)
#define IS_UART_SoftwareFlowControl(CONTROL) \
                                            (((CONTROL) == UART_SoftwareFlowControl_None) || \
                                            ((CONTROL) == UART_SoftwareFlowControl_RTS))

/**
  * @}
  */ 

/** @defgroup UART_TXIFLSEL 
  * @{
  */ 
  
#define UART_TXIFLSEL_2                     ((uint32_t)0x00000000)
#define UART_TXIFLSEL_4                     ((uint32_t)0x00010000)
#define UART_TXIFLSEL_8                     ((uint32_t)0x00020000)
#define UART_TXIFLSEL_12                    ((uint32_t)0x00030000)
#define UART_TXIFLSEL_14                    ((uint32_t)0x00040000)
#define IS_UART_TXIFLSEL(TXIFLSEL)          (((TXIFLSEL) == UART_TXIFLSEL_2)  || \
                                            ((TXIFLSEL) == UART_TXIFLSEL_4)  || \
                                            ((TXIFLSEL) == UART_TXIFLSEL_8)  || \
                                            ((TXIFLSEL) == UART_TXIFLSEL_12) || \
                                            ((TXIFLSEL) == UART_TXIFLSEL_14))

/**
  * @}
  */ 

/** @defgroup UART_RXIFLSEL 
  * @{
  */ 
  
#define UART_RXIFLSEL_2                     ((uint32_t)0x00000000)
#define UART_RXIFLSEL_4                     ((uint32_t)0x00100000)
#define UART_RXIFLSEL_8                     ((uint32_t)0x00200000)
#define UART_RXIFLSEL_12                    ((uint32_t)0x00300000)
#define UART_RXIFLSEL_14                    ((uint32_t)0x00400000)
#define IS_UART_RXIFLSEL(RXIFLSEL)          (((RXIFLSEL) == UART_RXIFLSEL_2)  || \
                                            ((RXIFLSEL) == UART_RXIFLSEL_4)  || \
                                            ((RXIFLSEL) == UART_RXIFLSEL_8)  || \
                                            ((RXIFLSEL) == UART_RXIFLSEL_12) || \
                                            ((RXIFLSEL) == UART_RXIFLSEL_14))

/**
  * @}
  */ 

/** @defgroup UART_FEN 
  * @{
  */ 
  
#define UART_FEN_Enable                     ((uint32_t)0x00000010)
#define UART_FEN_Disable                    ((uint32_t)0x00000000)
#define IS_UART_FEN(STATE)                  (((STATE) == UART_FEN_Enable) || \
                                            ((STATE) == UART_FEN_Disable))
/**
  * @}
  */ 

/** @defgroup UART_RS485_NMM 
  * @{
  */ 

#define UART_RS485_NMM_MAD                  ((uint8_t)0x03)
#define UART_RS485_NMM_AAD                  ((uint8_t)0x07)
#define UART_RS485_NMM_Disable              ((uint8_t)0x00)
#define IS_UART_RS485_NMM(MODE)             (((MODE) == UART_RS485_NMM_MAD) || \
                                            ((MODE) == UART_RS485_NMM_AAD) || \
                                            ((MODE) == UART_RS485_NMM_Disable))
/**
  * @}
  */ 

/** @defgroup UART_RS485_DCTRL 
  * @{
  */ 

#define UART_RS485_DCTRL_RTS                ((uint8_t)0x10)
#define UART_RS485_DCTRL_DISABLE            ((uint8_t)0x00)
#define IS_UART_RS485_DCTRL(MODE)           (((MODE) == UART_RS485_DCTRL_RTS) || \
                                            ((MODE) == UART_RS485_DCTRL_DISABLE))
/**
  * @}
  */ 

/** @defgroup UART_RS485_ONIV 
  * @{
  */ 

#define UART_RS485_ONIV_MODE_0              ((uint8_t)0x20)
#define UART_RS485_ONIV_MODE_1              ((uint8_t)0x00)
#define IS_UART_RS485_ONIV_MODE(MODE)       (((MODE) == UART_RS485_ONIV_MODE_0) || \
                                            ((MODE) == UART_RS485_ONIV_MODE_1))
/**
  * @}
  */ 

/** @defgroup UART_AUTOBAUD_MODE 
  * @{
  */ 

#define UART_AUTOBAUD_MODE_RE_0             ((uint16_t)0x0004)
#define UART_AUTOBAUD_MODE_RE_1             ((uint16_t)0x0006)
#define UART_AUTOBAUD_MODE_RD_0             ((uint16_t)0x0000)
#define UART_AUTOBAUD_MODE_RD_1             ((uint16_t)0x0002)
#define IS_UART_AUTOBAUD_MODE(MODE)         (((MODE) == UART_AUTOBAUD_MODE_RE_0) || \
                                            ((MODE) == UART_AUTOBAUD_MODE_RE_1) || \
                                            ((MODE) == UART_AUTOBAUD_MODE_RD_0) || \
                                            ((MODE) == UART_AUTOBAUD_MODE_RD_1))
/**
  * @}
  */ 

/** @defgroup UART_Interrupt_definition 
  * @{
  */

#define UART_IT_RXIEN                       ((uint32_t)0x00100000)
#define UART_IT_TXIEN                       ((uint32_t)0x00200000)
#define UART_IT_RTIEN                       ((uint32_t)0x00400000)
#define UART_IT_FEIEN                       ((uint32_t)0x00800000)
#define UART_IT_PEIEN                       ((uint32_t)0x01000000)
#define UART_IT_BEIEN                       ((uint32_t)0x02000000)
#define UART_IT_OEIEN                       ((uint32_t)0x04000000)
#define UART_IT_TFEIEN                      ((uint32_t)0x08000000)
#define UART_IT_ABEOEN                      ((uint32_t)0x10000000)
#define UART_IT_ABTOEN                      ((uint32_t)0x20000000)
#define IS_UART_CONFIG_IT(IT)               ((((IT) & ((uint32_t)0x3FF00000)) != 0) && (((IT) & ((uint32_t)0xC00FFFFF)) == 0))

#define UART_IT_RXIS                        ((uint32_t)0x00000010)
#define UART_IT_TXIS                        ((uint32_t)0x00000020)
#define UART_IT_RTIS                        ((uint32_t)0x00000040)
#define UART_IT_FEIS                        ((uint32_t)0x00000080)
#define UART_IT_PEIS                        ((uint32_t)0x00000100)
#define UART_IT_BEIS                        ((uint32_t)0x00000200)
#define UART_IT_OEIS                        ((uint32_t)0x00000400)
#define UART_IT_TFEIS                       ((uint32_t)0x00000800)
#define UART_IT_ABEO                        ((uint32_t)0x00001000)
#define UART_IT_ABTO                        ((uint32_t)0x00002000)
#define UART_IT_ABEOIntClr                  (((uint32_t)0x00000100) << 16)
#define UART_IT_ABTOIntClr                  (((uint32_t)0x00000200) << 16)
#define IS_UART_GET_IT(IT)                  (((IT) == UART_IT_RXIS) || ((IT) == UART_IT_TXIS)     || \
                                            ((IT) == UART_IT_RTIS) || ((IT) == UART_IT_FEIS)     || \
                                            ((IT) == UART_IT_PEIS) || ((IT) == UART_IT_BEIS)     || \
                                            ((IT) == UART_IT_OEIS) || ((IT) == UART_IT_TFEIS)    || \
                                            ((IT) == UART_IT_ABEO) || ((IT) == UART_IT_ABTO))

#define IS_UART_CLEAR_IT(IT)                ((((IT) & 0x03003FF0) != 0) && (((IT) & 0xFCFFC00F) == 0))
/**
  * @}
  */

/** @defgroup UART_DMA_Requests 
  * @{
  */

#define UART_DMAReq_Tx                      ((uint32_t)0x02000000)
#define UART_DMAReq_Rx                      ((uint32_t)0x01000000)
#define UART_DMAReq_Rx_DMAONERROR           ((uint32_t)0x05000000)
#define IS_UART_DMAREQ(DMAREQ)              (((DMAREQ) == UART_DMAReq_Tx) || \
                                            ((DMAREQ) == UART_DMAReq_Rx) || \
                                            ((DMAREQ) == (UART_DMAReq_Rx | UART_DMAReq_Tx)) || \
                                            ((DMAREQ) == (UART_DMAReq_Tx | UART_DMAReq_Rx_DMAONERROR)) || \
                                            ((DMAREQ) == UART_DMAReq_Rx_DMAONERROR))

/**
  * @}
  */ 

/** @defgroup UART_WakeUp_methods
  * @{
  */

#define UART_WakeUp_IdleLine                ((uint16_t)0x0000)
#define UART_WakeUp_AddressMark             ((uint16_t)0x0800)
#define IS_UART_WAKEUP(WAKEUP)              (((WAKEUP) == UART_WakeUp_IdleLine) || \
                                            ((WAKEUP) == UART_WakeUp_AddressMark))
/**
  * @}
  */

/** @defgroup UART_LIN_Break_Detection_Length 
  * @{
  */
  
#define UART_LINBreakDetectLength_10b       ((uint16_t)0x0000)
#define UART_LINBreakDetectLength_11b       ((uint16_t)0x0020)
#define IS_UART_LIN_BREAK_DETECT_LENGTH(LENGTH) \
                                            (((LENGTH) == UART_LINBreakDetectLength_10b) || \
                                            ((LENGTH) == UART_LINBreakDetectLength_11b))
/**
  * @}
  */

/** @defgroup UART_IrDA_Low_Power 
  * @{
  */

#define UART_IrDAMode_LowPower              ((uint32_t)0x00000040)
#define UART_IrDAMode_Normal                ((uint32_t)0x00000000)
#define IS_UART_IRDA_MODE(MODE)             (((MODE) == UART_IrDAMode_LowPower) || \
                                            ((MODE) == UART_IrDAMode_Normal))
/**
  * @}
  */ 

/** @defgroup UART_Flags 
  * @{
  */

#define UART_FLAG_FERR                      ((uint32_t)0x00010000)
#define UART_FLAG_PERR                      ((uint32_t)0x00020000)
#define UART_FLAG_BERR                      ((uint32_t)0x00040000)
#define UART_FLAG_OERR                      ((uint32_t)0x00080000)
#define UART_FLAG_RXFE                      ((uint32_t)0x01000000)
#define UART_FLAG_TXFF                      ((uint32_t)0x02000000)
#define UART_FLAG_RXFF                      ((uint32_t)0x04000000)
#define UART_FLAG_TXFE                      ((uint32_t)0x08000000)
#define UART_FLAG_CTS                       ((uint32_t)0x10000000)
#define UART_FLAG_BUSY                      ((uint32_t)0x20000000)
#define IS_UART_FLAG(FLAG)                  (((FLAG) == UART_FLAG_FERR) || ((FLAG) == UART_FLAG_PERR) || \
                                            ((FLAG) == UART_FLAG_BERR) || ((FLAG) == UART_FLAG_OERR) || \
                                            ((FLAG) == UART_FLAG_RXFE) || ((FLAG) == UART_FLAG_TXFF) || \
                                            ((FLAG) == UART_FLAG_RXFF) || ((FLAG) == UART_FLAG_TXFE) || \
                                            ((FLAG) == UART_FLAG_CTS)  || ((FLAG) == UART_FLAG_BUSY))
                              
#define IS_UART_CLEAR_FLAG(FLAG)            ((((FLAG)&0xFFF0FFFF) == 0) && (((FLAG)&0x000F0000) != 0))

#define IS_UART_PERIPH_FLAG(PERIPH, UART_FLAG) ((((*(uint32_t*)&(PERIPH)) != UART4_BASE) &&\
                                            ((*(uint32_t*)&(PERIPH)) != UART5_BASE)) \
                                            || ((UART_FLAG) != UART_FLAG_CTS)) 
#define IS_UART_BAUDRATE(BAUDRATE)          (((BAUDRATE) > 0) && ((BAUDRATE) < 0x0016E361))
#define IS_UART_ILPDVSR(ILPDVSR)            (((ILPDVSR) <= 0xFF) && ((ILPDVSR)>0))
#define IS_UART_RS485ADDRESS(ADDRESS)       (((ADDRESS) <= 0xFF) && ((ADDRESS)>0))


/**
  * @}
  */ 

/**
  * @}
  */ 

/** @defgroup UART_Exported_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup UART_Exported_Functions
  * @{
  */

void UART_Reset(UART_TypeDef* UARTx);
void UART_Init(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct);
void UART_StructInit(UART_InitTypeDef* UART_InitStruct);
void UART_Cmd(UART_TypeDef* UARTx, FunctionalState NewState);
void UART_ITConfig(UART_TypeDef* UARTx, uint32_t UART_IT, FunctionalState NewState);
void UART_DMACmd(UART_TypeDef* UARTx, uint32_t UART_DMAReq, FunctionalState NewState);
void UART_SendData(UART_TypeDef* UARTx, uint8_t Data);
uint32_t UART_ReceiveData(UART_TypeDef* UARTx);
void UART_IrDAConfig(UART_TypeDef* UARTx, uint32_t UART_IrDAMode);
void UART_IrDACmd(UART_TypeDef* UARTx, FunctionalState NewState);
void UART_SetILPDVSR(UART_TypeDef* UARTx, uint8_t ILPDVSR);
void UART_RS485Init(UART_TypeDef* UARTx, UART_RS485InitTypeDef* UART_RS485InitStruct);
void UART_RS485StructInit(UART_RS485InitTypeDef* UART_RS485InitStruct);
void UART_RS485SetAddress(UART_TypeDef* UARTx, uint8_t UART_Address);
void UART_RS485SetDelay(UART_TypeDef* UARTx, uint8_t UART_DLYTime);
void UART_AUTOBAUDConfig(UART_TypeDef* UARTx, uint16_t UART_AUTOBAUDMODE);
void UART_AUTOBAUDCmd(UART_TypeDef* UARTx, FunctionalState NewState);
FlagStatus UART_GetFlagStatus(UART_TypeDef* UARTx, uint32_t UART_FLAG);
void UART_ClearFlag(UART_TypeDef* UARTx, uint32_t UART_FLAG);
ITStatus UART_GetITStatus(UART_TypeDef* UARTx, uint32_t UART_IT);
void UART_ClearITPendingBit(UART_TypeDef* UARTx, uint32_t UART_IT);

#ifdef __cplusplus
}
#endif

#endif /* __Y6_UART_H */
/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2012 TDO *****END OF FILE****/

