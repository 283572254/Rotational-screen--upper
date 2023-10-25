 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Y6_I2C_H
#define __Y6_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "Y6.h"

/** @addtogroup Y6_StdPeriph_Driver
  * @{
  */

/** @addtogroup I2C
  * @{
  */

/* Exported types ------------------------------------------------------------*/



/** 
  * @brief  I2C Init structure definition  
  */

typedef struct
{
  uint8_t I2C_Mode;          /*!<Specifies whether the I2C is as master or slave mode.
                                        0 is slave mode,1 is mastet mode,@I2C_Mode*/
  uint8_t I2C_ClockSpeed;          /*!< Specifies the I2C clock speed.
                                        0 is standard(100 kbit/s) while 1 is fast(400 kbit/s). */

  uint16_t I2C_10BITADDR_SLAVE;    /*!<Specifies whether the I2C
                                                          responds to 7- or 10-bit addresses when as slave mode.*/
  uint16_t I2C_OwnAddress;         /*!< Specifies  own address when as slave mode.
                                         This parameter can be a 7-bit or 10-bit address. */

  uint16_t I2C_10BITADDR_MASTER;   /*!<Specifies whether the I2C starts its transfers in 7- or 10-bit
                                                      addressing mode when acting as a master.*/
  uint16_t I2C_RESTART_EN;          /*!<Specifies whether RESTART conditions may be sent when
                                                        acting as a master.*/
}I2C_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @addtogroup I2C_Mode
  * @{
  */
#define I2C_MASTER_MODE       0
#define I2C_SLAVE_MODE       1
/**
  * @}
  */

/** @defgroup I2C_Exported_Constants
  * @{
  */

#define IS_I2C_ALL_PERIPH(PERIPH) ( (PERIPH) == I2C0 )

/**
  * @}
  */


/** @defgroup I2C_transfer_direction 
  * @{
  */
#define IS_SPECIAL_DOMAIN(DOMAIN) (((DOMAIN) == I2C_TAR_IC_SPECIAL) || \
                                     ((DOMAIN) == 0))
/**
  * @}
  */


/** @defgroup I2C_transfer_direction 
  * @{
  */
#define IS_GC_START_DOMAIN(DOMAIN) (((DOMAIN) == I2C_TAR_GC_OR_START) || \
                                     ((DOMAIN) == 0))
/**
  * @}
  */


/** @defgroup I2C_registers 
  * @{
  */
#define I2C_Register_CON                     ((uint8_t)0x00)
#define I2C_Register_TAR                     ((uint8_t)0x04)
#define I2C_Register_SAR                     ((uint8_t)0x08)
#define I2C_Register_HS_MADDR                ((uint8_t)0x0C)
#define I2C_Register_DATA_CMD                ((uint8_t)0x10)
#define I2C_Register_SS_SCL_HCNT             ((uint8_t)0x14)
#define I2C_Register_SS_SCL_LCNT             ((uint8_t)0x18)
#define I2C_Register_FS_SCL_HCNT             ((uint8_t)0x1C)
#define I2C_Register_FS_SCL_LCNT             ((uint8_t)0x20)
#define I2C_Register_HS_SCL_HCNT             ((uint8_t)0x24)
#define I2C_Register_HS_SCL_LCNT             ((uint8_t)0x28)
#define I2C_Register_INTR_STAT               ((uint8_t)0x2C)
#define I2C_Register_INTR_MASK               ((uint8_t)0x30)
#define I2C_Register_RAW_INTR_STAT           ((uint8_t)0x34)
#define I2C_Register_RX_TL                   ((uint8_t)0x38)
#define I2C_Register_TX_TL                   ((uint8_t)0x3C)
#define I2C_Register_CLR_INTR                ((uint8_t)0x40)    
#define I2C_Register_CLR_RX_UNDER            ((uint8_t)0x44)
#define I2C_Register_CLR_RX_OVER             ((uint8_t)0x48)
#define I2C_Register_CLR_TX_OVER             ((uint8_t)0x4C)
#define I2C_Register_CLR_RD_REQ              ((uint8_t)0x50)
#define I2C_Register_CLR_TX_ABRT             ((uint8_t)0x54)
#define I2C_Register_CLR_RX_DONE             ((uint8_t)0x58)
#define I2C_Register_CLR_ACTIVITY            ((uint8_t)0x5C)
#define I2C_Register_CLR_STOP_DET            ((uint8_t)0x60)
#define I2C_Register_CLR_START_DET           ((uint8_t)0x64)
#define I2C_Register_CLR_GEN_CALL            ((uint8_t)0x68)
#define I2C_Register_ENABLE                  ((uint8_t)0x6C)
#define I2C_Register_STAT                    ((uint8_t)0x70)
#define I2C_Register_TXFLR                   ((uint8_t)0x74)
#define I2C_Register_RXFLR                   ((uint8_t)0x78)

#define I2C_Register_TX_ABRT_SOURCE          ((uint8_t)0x80)
#define I2C_Register_SLV_DATA_NACK_ONLY      ((uint8_t)0x84)
#define I2C_Register_DMA_CR                  ((uint8_t)0x88)
#define I2C_Register_DMA_TDLR                ((uint8_t)0x8C)
#define I2C_Register_DMA_RDLR                ((uint8_t)0x90)
#define I2C_Register_SDA_SETUP               ((uint8_t)0x94)
#define I2C_Register_ACK_GENERAL_CALL        ((uint8_t)0x98)
#define I2C_Register_ENABLE_STATUS           ((uint8_t)0x9C)
#define IS_I2C_REGISTER(REGISTER) ( ((((int)REGISTER)%4) == 0)&&((int)REGISTER>=I2C_Register_CON)&&(REGISTER<=I2C_Register_ENABLE_STATUS) )
/**
  * @}
  */




/** @defgroup I2C_interrupts_definition 
  * @{
  */
#define I2C_IT_RX_UNDER                      ((uint16_t)0x0001)
#define I2C_IT_RX_OVER                       ((uint16_t)0x0002)
#define I2C_IT_RX_FULL                       ((uint16_t)0x0004)
#define I2C_IT_TX_OVER                       ((uint16_t)0x0008)
#define I2C_IT_TX_EMPTY                      ((uint16_t)0x0010)
#define I2C_IT_RD_REQ                        ((uint16_t)0x0020)
#define I2C_IT_TX_ABRT                       ((uint16_t)0x0040)
#define I2C_IT_RX_DONE                       ((uint16_t)0x0080)
#define I2C_IT_ACTIVITY                      ((uint16_t)0x0100)
#define I2C_IT_STOP_DET                      ((uint16_t)0x0200)
#define I2C_IT_START_DET                     ((uint16_t)0x0400)
#define I2C_IT_GEN_CALL                      ((uint16_t)0x0800)
#define I2C_IT_ALL                           ((uint16_t)0x0fff)

#define IS_I2C_CONFIG_IT(IT) ( ((((IT) & (uint16_t)0xF000) == 0x00) && ((IT) != 0x00))||(IT==I2C_IT_ALL) )
/**
  * @}
  */ 



/** @defgroup I2C_interrupt_bit_definition 
  * @{
  */
/*INT bit already defined in Y6.h*/
#define IS_I2C_IT_BIT(IT)    (((IT) == I2C_IC_INTR_STAT_R_RX_UNDER) || ((IT) == I2C_IC_INTR_STAT_R_RX_OVER) || \
                              ((IT) == I2C_IC_INTR_STAT_R_RX_FULL) || ((IT) == I2C_IC_INTR_STAT_R_TX_OVER) || \
                              ((IT) == I2C_IC_INTR_STAT_R_TX_EMPTY) || ((IT) == I2C_IC_INTR_STAT_R_RD_REQ) || \
                              ((IT) == I2C_IC_INTR_STAT_R_TX_ABRT) || ((IT) == I2C_IC_INTR_STAT_R_RX_DONE) || \
                              ((IT) == I2C_IC_INTR_STAT_R_ACTIVITY) || ((IT) == I2C_IC_INTR_STAT_R_STOP_DET) || \
                              ((IT) == I2C_IC_INTR_STAT_R_START_DET) || ((IT) == I2C_IC_INTR_STAT_R_GEN_CALL) )
/**
  * @}
  */


/** @defgroup I2C_raw_interrupt_bit_definition  
  * @{
  */
/*Raw INT bit already defined in Y6.h*/
#define  I2C_RAW_IT_BIT_ALL      ((uint16_t)(0xfeb))
#define IS_I2C_RAW_IT_BIT(IT)    (((IT) == I2C_IC_RAW_INTR_STAT_RX_UNDER) || ((IT) == I2C_IC_RAW_INTR_STAT_RX_OVER) || \
                                  ((IT) == I2C_IC_RAW_INTR_STAT_TX_OVER) || \
                                  ((IT) == I2C_IC_RAW_INTR_STAT_RD_REQ) || \
                                  ((IT) == I2C_IC_RAW_INTR_STAT_TX_ABRT) || ((IT) == I2C_IC_RAW_INTR_STAT_RX_DONE) || \
                                  ((IT) == I2C_IC_RAW_INTR_STAT_ACTIVITY) || ((IT) == I2C_IC_RAW_INTR_STAT_STOP_DET) || \
                                  ((IT) == I2C_IC_RAW_INTR_STAT_START_DET) || ((IT) == I2C_IC_RAW_INTR_STAT_GEN_CALL)|| \
                                  ((IT) == I2C_RAW_IT_BIT_ALL))
        /**
  * @}
  */



/** @defgroup I2C_TX_ABRT_SOURCE_bit_definition  
  * @{
  */
/*IC_TX_ABRT_SOURCE bit already defined in Y6.h*/
#define  TX_ABRT_SOURCE_BIT_ALL    ((uint16_t)(0xffff))
#define IS_TX_ABRT_SOURCE_BIT(IT)     (((IT) == I2C_IC_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK) || ((IT) == I2C_IC_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK) || \
                                       ((IT) == I2C_IC_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK) || ((IT) == I2C_IC_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK) || \
                                       ((IT) == I2C_IC_TX_ABRT_SOURCE_ABRT_GCALL_NOACK) || ((IT) == I2C_IC_TX_ABRT_SOURCE_ABRT_GCALL_READ) || \
                                       ((IT) == I2C_IC_TX_ABRT_SOURCE_ABRT_HS_ACKDET) || ((IT) == I2C_IC_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET) || \
                                       ((IT) == I2C_IC_TX_ABRT_SOURCE_ABRT_HS_NORSTRT) || ((IT) == I2C_IC_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT) || \
                                       ((IT) == I2C_IC_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT) || ((IT) == I2C_IC_TX_ABRT_SOURCE_ABRT_MASTER_DIS) || \
                                       ((IT) == I2C_IC_TX_ABRT_SOURCE_ARB_LOST) || ((IT) == I2C_IC_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO) || \
                                       ((IT) == I2C_IC_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST) || ((IT) == I2C_IC_TX_ABRT_SOURCE_ABRT_SLVRD_INTX) || \
                                       ((IT) == TX_ABRT_SOURCE_BIT_ALL))

/**
  * @}
  */


/** 
  * @brief  IC_STATUS register flags  
  * @{
  */
/*alreday defined in Y6.h*/
#define IS_I2C_GET_FLAG(FLAG) (((FLAG) == I2C_IC_STATUS_ACTIVITY) || ((FLAG) == I2C_IC_STATUS_TFNF) || \
                               ((FLAG) == I2C_IC_STATUS_TFE) || ((FLAG) == I2C_IC_STATUS_RFNE) || \
                               ((FLAG) == I2C_IC_STATUS_RFF) || ((FLAG) == I2C_IC_STATUS_MST_ACTIVITY) || \
                               ((FLAG) == I2C_IC_STATUS_SLV_ACTIVITY))
/**
  * @}
  */


/** @defgroup I2C_clock_speed 
  * @{
  */
//high not support for the moment
#define I2C_Speedmode_Stand            ((uint16_t)0x0002)
#define I2C_Speedmode_FAST             ((uint16_t)0x0004)
#define IS_I2C_CLOCK_SPEED(SPEED) (((SPEED) == I2C_Speedmode_Stand) || ((SPEED) == I2C_Speedmode_FAST))
/**
  * @}
  */
  
/** @defgroup I2C_BITADDR_SLAVE 
  * @{
  */
#define I2C_10_BITADDR_SLAVE          ((uint16_t)0x0008)
#define I2C_7BITADDR_SLAVE            ((uint16_t)0x0000)
#define IS_I2C_BITADDR_SLAVE(SLAVE) (((SLAVE) == I2C_7BITADDR_SLAVE)||((SLAVE) == I2C_10_BITADDR_SLAVE))
/**
  * @}
  */

/** @defgroup I2C_BITADDR_MASTER 
  * @{
  */
#define I2C_10_BITADDR_MASTER          ((uint16_t)0x0010)
#define I2C_7BITADDR_MASTER            ((uint16_t)0x0000)
#define IS_I2C_BITADDR_MASTER(MASTER) (((MASTER) == I2C_7BITADDR_MASTER)||((MASTER) == I2C_10_BITADDR_MASTER))
/**
  * @}
  */

/** @defgroup I2C_RESTART_CHECK
  * @{
  */
#define I2C_RESTART_ENABLED            ((uint16_t)0x0020)
#define I2C_RESTART_DISABLED           ((uint16_t)0x0000)
#define IS_I2C_RESTART_CHECK(RESTART) (((RESTART) == I2C_RESTART_ENABLED)||((RESTART) == I2C_RESTART_DISABLED))
/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 

/*  Function used to set the I2C configuration to the default reset state *****/
void I2C_Reset(I2C_TypeDef* I2Cx);


/* Initialization and Configuration functions *********************************/
int I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct);
int I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState, int SpeedMode);
void I2C_ConfigureTARSpecial(I2C_TypeDef* I2Cx, uint32_t SPECIAL_DOMAIN_SET, uint32_t GC_START_DOMAIN_SET);
void I2C_SendSlavAddress(I2C_TypeDef* I2Cx, uint8_t Address);
void I2C_SetOwnAddress(I2C_TypeDef* I2Cx, uint8_t Address);


/* Data transfers functions ***************************************************/ 
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data);
void I2C_TriggerRecData(I2C_TypeDef* I2Cx);
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx);


/* Interrupts, events and flags management functions **************************/
uint32_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint8_t I2C_Register);
void I2C_ITConfig(I2C_TypeDef* I2Cx, uint16_t I2C_IT, FunctionalState NewState);
uint8_t I2C_GetFlagStatus(I2C_TypeDef* I2Cx);
FlagStatus I2C_CheckFlagStatus(I2C_TypeDef* I2Cx, uint8_t Status, uint32_t I2C_FLAG);
uint32_t I2C_GetITFlag(I2C_TypeDef* I2Cx);
uint32_t I2C_GetRawITFlag(I2C_TypeDef* I2Cx);
ITStatus I2C_CheckITFlag(I2C_TypeDef* I2Cx, uint32_t I2C_IT_FLAG, uint32_t I2C_IT_BIT);
void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx);
void I2C_ClearRawITPendingBit(I2C_TypeDef* I2Cx, uint32_t I2C_RAW_IT_BIT);
void I2C_Clear_TX_ABRT_SOURCE(I2C_TypeDef* I2Cx, uint32_t I2C_TX_ABRT_SOURCE_BIT);


#ifdef __cplusplus
}
#endif

#endif /*__Y6_I2C_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2013 TDO*****END OF FILE****/
