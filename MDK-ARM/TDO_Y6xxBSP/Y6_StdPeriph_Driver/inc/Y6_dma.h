 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Y6_DMA_H
#define __Y6_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "Y6.h"

/** @addtogroup Y6_StdPeriph_Driver
  * @{
  */

/** @addtogroup DMA
  * @{
  */

/* Exported defines ------------------------------------------------------------*/

/*Bit domain Shift for CTRL_L*/
#define DMA_CTRL_INT_EN                 (0) 
#define DMA_CTRL_DST_TR_WIDTH           (1)  //see DMA Transfer Width
#define DMA_CTRL_SRC_TR_WIDTH           (4)  //see DMA Transfer Width
#define DMA_CTRL_DINC                   (7)  //see DMA Address Changing
#define DMA_CTRL_SINC                   (9)  //see DMA Address Changing
#define DMA_DEST_MSIZE                  (11) //see Burst Transaction Length
#define DMA_SRC_MSIZE                   (14) //see Burst Transaction Length
#define DMA_SRC_GATHER_EN               (17)
#define DMA_DST_GATHER_EN               (18)
#define DMA_TTC_FC                      (20) //see Transfer Type and Flow Control
#define DMA_DMS                         (23)
#define DMA_SMS                         (25)
#define DMA_LLP_DST_EN                  (27)
#define DMA_LLP_SRC_EN                  (28)

/*Bit domain Shift for CTRL_H*/
#define DMA_BLOCK_TS                    (32)
#define DMA_DONE                        (44)


/*Bit domain shift for CFG_H*/
#define DMA_CFG_SRC_PER                 (7)
#define DMA_CFG_DEST_PER                (11)

/*Bit domain shift for CFG_L*/
#define DMA_CFG_RELOAD_SRC              (30)
#define DMA_CFG_RELOAD_DST              (31)

/*DMA Transfer Width*/
#define DMA_WIDTH_8                     (0x00)
#define DMA_WIDTH_16                    (0x01)
#define DMA_WIDTH_32                    (0x02)
#define DMA_WIDTH_64                    (0x03)
#define DMA_WIDTH_128                   (0x04)
#define DMA_WIDTH_256                   (0x05)

/*DMA Address Changing*/
#define DMA_ADDRESS_INCREMENT           (0x00)
#define DMA_ADDRESS_DECREMENT           (0x01)
#define DMA_ADDRESS_NO_CHANGE           (0x02)

/*Burst Transaction Length*/
#define DMA_BURST_1_ITEM                (0x00)
#define DMA_BURST_4_ITEM                (0x01)
#define DMA_BURST_8_ITEM                (0x02)
#define DMA_BURST_16_ITEM               (0x03)
#define DMA_BURST_32_ITEM               (0x04)
#define DMA_BURST_64_ITEM               (0x05)
#define DMA_BURST_128_ITEM              (0x06)
#define DMA_BURST_256_ITEM              (0x07)

/*Transfer Type and Flow Control*/
#define DMA_MEM_TO_MEM_DMAC             (0x00)
#define DMA_MEM_TO_PER_DMAC             (0x01)
#define DMA_PER_TO_MEM_DMAC             (0x02)
#define DMA_PER_TO_PER_DMAC             (0x03)
#define DMA_PER_TO_MEM_PERI             (0x04)
#define DMA_PER_TO_PER_SOU_PER          (0x05)
#define DMA_MEM_TO_PER_PER              (0x06)
#define DMA_PER_TO_PER_DES_PER          (0x07)


/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/

/** @defgroup DMA_Exported_Constants
  * @{
  */

/** @defgroup DMA_channel 
  * @{
  */
#define DMAChannelNum 4
typedef enum {
  DMA_CHANNEL_0 = 0, 
  DMA_CHANNEL_1,
  DMA_CHANNEL_2,
  DMA_CHANNEL_3,
}DMAchannel;

#define IS_DMA_CHANNEL(CHANNEL) (((CHANNEL) == DMA_CHANNEL_0) || \
                                 ((CHANNEL) == DMA_CHANNEL_1) || \
                                 ((CHANNEL) == DMA_CHANNEL_2) || \
                                 ((CHANNEL) == DMA_CHANNEL_3))


/** @defgroup DMA_method
  * @{
  */ 
#define DMAMETHODNUM 10
typedef enum {
  DMAtranstype1 = 1,
  DMAtranstype2,
  DMAtranstype3,
  DMAtranstype4,
  DMAtranstype5,
  DMAtranstype6,
  DMAtranstype7,
  DMAtranstype8,
  DMAtranstype9,
  DMAtranstype10
}DMAmethod;

#define IS_DMA_METHOD(METHOD)  (((METHOD) == DMAtranstype1) || \
                                ((METHOD) == DMAtranstype2) || \
                                ((METHOD) == DMAtranstype3) || \
                                ((METHOD) == DMAtranstype4) || \
                                ((METHOD) == DMAtranstype5) || \
                                ((METHOD) == DMAtranstype6) || \
                                ((METHOD) == DMAtranstype7) || \
                                ((METHOD) == DMAtranstype8) || \
                                ((METHOD) == DMAtranstype9) || \
                                ((METHOD) == DMAtranstype10))
/**
  * @}
  */ 


/** @defgroup DMA_ChannelState
  * @{
  */ 
typedef enum {
  CHANNEL_IDLE =0,
  CHANNEL_BUSY
}ChannelState;
/**
  * @}
  */ 


/**
  * @}
  */ 

/** @defgroup DMA request channel
  * @}
  */ 
typedef enum {
  REQ_UART0TX_TIM16 = 0,
  REQ_UART0RX_TIM17,
  REQ_UART1TX,
  REQ_UART1RX,
  REQ_I2C0TX,
  REQ_I2C0RX,
  REQ_UART2TX,
  REQ_UART2RX,
  REQ_QSPI0TX,
  REQ_QSPI0RX,
  REQ_QSPI1TX,
  REQ_QSPI1RX,
  REQ_TIM4,
  REQ_TIM1,
  REQ_QSPI2TX,
  REQ_QSPI2RX_TIM15,
}DMAReqChannel;

/**
  * @}
  */ 
#define CHANNEL_MAX_SIZE    (511)

/**
  * @}
  */ 
typedef void(*DmaHandler)(void);

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
DMAchannel DmaRequestChannel(DmaHandler handler);
void DmaFreeChannel(DMAchannel channel);
int DmaInit(DMAchannel channel);
static int _WaitDmaSemaphore(DMAchannel channel);
int DmaStop(DMAchannel channel);
void DmaChannelCFGset(DMAchannel channel, uint32_t lowregval, uint32_t highregval);
static void DmaStart(DMAchannel channel);
int DmaStartRoutine(DMAchannel channel, int bWaitSemaAfter);
ChannelState DmaIsBusy(DMAchannel channel);
void DmaChannelInterrupt(DMAchannel channel, int funswitch);
int DmaChannelInterruptStatusBit(DMAchannel channel, int statustype);
void DmaChannelClearInterruptStatus(DMAchannel channel);

#ifdef __cplusplus
}
#endif

#endif /*__Y6_DMA_H */

/**
  * @}
  */

/**
  * @}
  */


/******************* (C) COPYRIGHT 2013 TDO *****END OF FILE****/
