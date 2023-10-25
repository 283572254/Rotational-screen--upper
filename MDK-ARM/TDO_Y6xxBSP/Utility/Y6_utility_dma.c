#include "Y6.h"
#include "Y6_dma.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/** 
  * @brief  copy source memory comment to destination by dma
  * @param  dst: destination memory address
  *         src: source address
  *         size: copy size in byte
  * @retval 0 = success
  *         -1= failed
  */
int DMA_MemCopy(void *dst, void *src, int size)
{
  uint32_t temreg;
  DMAchannel channel;
  DMAChannel_TypeDef *MemDMAChannel;

  if (size > CHANNEL_MAX_SIZE)
  {
    printf("size beyond channel ability\r\n");
    return -1;
  }

  channel = DmaRequestChannel(NULL);
  if ((int)channel >= DMAChannelNum)
  {
    printf("all dma channel busy\r\n");
    return -1;
  }

  MemDMAChannel = (DMAChannel_TypeDef *)(DMA_BASE + 0x58*channel);

  temreg = 0x00000000 + (0 << DMA_CTRL_INT_EN)  //INT_EN, ch irq enable
                      + (0 << DMA_CTRL_DST_TR_WIDTH)      // DST_TR_WIDTH, des transfer width, should set to HSIZE, here is 000, means 8bit
                      + (0 << DMA_CTRL_SRC_TR_WIDTH)      // SRC_TR_WIDTH, sor transfer width, should set to HSIZE, here is 000, means 8bit
                      + (0 << DMA_CTRL_DINC)      // DINC, des addr increment, des is SPI, so should set to 1x, means no change
                      + (0 << DMA_CTRL_SINC)      // SINC, sor addr increment, src is sram, so should set to 00, means to increase 
                      + (2 << DMA_DEST_MSIZE)     // DEST_MSIZE, des burst length, set to 001 means 4 DST_TR_WIDTH per burst transcation
                      + (2 << DMA_SRC_MSIZE)     // SRC_MSIZE, sor burst length, set to 001 means 4 SOR_TR_WIDTH per burst transcation
                      + (0 << DMA_TTC_FC)     // TT_FC,transfer type and flow control,001 means memory to peripheral,dma is flow controller
                      + (0 << DMA_LLP_DST_EN)     // LLP_DST_EN, des block chaining enable, set to 0 disable it
                      + (0 << DMA_LLP_SRC_EN) ;   // LLP_SOR_EN, sor block chaining enable, set to 0 disable it	

  DMA->DmaCfgReg = 1;
  MemDMAChannel->CFG_H = 0;
  MemDMAChannel->CFG_L = 0;

  MemDMAChannel->LLP = 0;
  MemDMAChannel->CTL_H = size;
  MemDMAChannel->SAR = (uint32_t)src;
  MemDMAChannel->DAR = (uint32_t)dst;
  MemDMAChannel->CTL_L = temreg;
  
  DMA->ChEnReg = 0x101 << channel;
  while(DMA->ChEnReg & (1 << channel));
  DmaFreeChannel(channel);

  return 0;
}

/** 
  * @brief  set destination memory comment to 'comm' by dma
  * @param  dst: destination memory address
  *         comm: memory comment
  *         width: 1 = byte order
  *                2 = hword order
  *                4 = word order
  *         size: memory size in order
  * @retval 0 = success
  *         -1= failed
  */
int DMA_MemSet(void *dst, uint32_t comm, int width, int size)
{
  uint32_t temreg;
  DMAchannel channel;
  DMAChannel_TypeDef *MemDMAChannel;

  if ((width != 1) && (width != 2) && (width != 4))
  {
    printf("param width wrong\r\n");
    return -1;
  }

  if(size > CHANNEL_MAX_SIZE)
  {
    printf("tx size beyond dma channel ability\r\n");
    return -1;
  }

  channel = DmaRequestChannel(NULL);
  if ((int)channel >= DMAChannelNum)
  {
    printf("all dma channel busy\r\n");
    return -1;
  }

  MemDMAChannel = (DMAChannel_TypeDef *)(DMA_BASE + 0x58*channel);

  temreg = 0x00000000 + (0 << DMA_CTRL_INT_EN)  //INT_EN, ch irq enable
                      + ((width >> 1) << DMA_CTRL_DST_TR_WIDTH)      // DST_TR_WIDTH, des transfer width, should set to HSIZE, here is 000, means 8bit
                      + ((width >> 1) << DMA_CTRL_SRC_TR_WIDTH)      // SRC_TR_WIDTH, sor transfer width, should set to HSIZE, here is 000, means 8bit
                      + (0 << DMA_CTRL_DINC)      // DINC, des addr increment, des is SPI, so should set to 00, means to increase
                      + (2 << DMA_CTRL_SINC)      // SINC, sor addr increment, src is sram, so should set to 1x, means no change 
                      + (0 << DMA_DEST_MSIZE)     // DEST_MSIZE, des burst length, set to 001 means 4 DST_TR_WIDTH per burst transcation
                      + (0 << DMA_SRC_MSIZE)     // SRC_MSIZE, sor burst length, set to 001 means 4 SOR_TR_WIDTH per burst transcation
                      + (0 << DMA_TTC_FC)     // TT_FC,transfer type and flow control,001 means memory to peripheral,dma is flow controller
                      + (0 << DMA_LLP_DST_EN)     // LLP_DST_EN, des block chaining enable, set to 0 disable it
                      + (0 << DMA_LLP_SRC_EN) ;   // LLP_SOR_EN, sor block chaining enable, set to 0 disable it	

  DMA->DmaCfgReg = 1;
  MemDMAChannel->CFG_H = 0;
  MemDMAChannel->CFG_L = 0;

  MemDMAChannel->LLP = 0;
  MemDMAChannel->CTL_H = size;
  MemDMAChannel->SAR = (uint32_t)&comm;
  MemDMAChannel->DAR = (uint32_t)dst;
  MemDMAChannel->CTL_L = temreg;
  
  DMA->ChEnReg = 0x101 << channel;
  while(DMA->ChEnReg & (1 << channel));
  DmaFreeChannel(channel);

  return 0;
}
