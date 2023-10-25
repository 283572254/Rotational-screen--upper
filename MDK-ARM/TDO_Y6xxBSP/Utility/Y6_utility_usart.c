#include "Y6.h"
#include "Y6_gpio.h"
#include "Y6_dma.h"
#include "Y6_uart.h"
#include "Y6_utility_usart.h"
#include "misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Retargets the C library printf function to the UART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the UART */
	UART_SendData(UART1, (uint8_t) ch);
	
	/* Loop until the end of transmission */
	while (UART_GetFlagStatus(UART1, UART_FLAG_TXFE) == RESET)
	{}
	
	return ch;
}

/**
  * @brief  configure uart
  * @param  UARTx: Select the UART peripheral.
  *   This parameter can be one of the following values:
  *   UARTx, x:[0:1:2].
  * @param  BaudRate: Set uart baudrate
  * @param  PinGroup: Select uart pin group to set pin mux
  *   This parameter can be one of the following values:
  *   UART0_GP2/7, UART1_GP0/2, UART2_GP0/7
  * @param  RxBuf: Set uart receive buffer
  * @retval:none
  */

void UART_Configuration(UART_TypeDef *UARTx, uint32_t BaudRate, UartPinGroup PinGroup)
{
  UART_InitTypeDef UART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStruct;

  RCC_UARTCLKSel(RCC_UARTCLK_SOURCE_SYSPLL);
  if (UARTx == UART0)
  {
    RCC_ResetAHBCLK(1 << AHBCLK_BIT_UART0);
    RCC_SETCLKDivider(RCC_CLOCKFREQ_UART0CLK, 4);
    NVIC_InitStruct.NVIC_IRQChannel = UART0_IRQn;
  }
  else if (UARTx == UART1)
  {
    RCC_ResetAHBCLK(1 << AHBCLK_BIT_UART1);
    RCC_SETCLKDivider(RCC_CLOCKFREQ_UART1CLK, 4);
    NVIC_InitStruct.NVIC_IRQChannel = UART1_IRQn;
  }
  else if (UARTx == UART2)
  {
    RCC_ResetAHBCLK(1 << AHBCLK_BIT_UART2);
    RCC_SETCLKDivider(RCC_CLOCKFREQ_UART2CLK, 4);
    NVIC_InitStruct.NVIC_IRQChannel = UART2_IRQn;
  }

  switch (PinGroup)
  {
  case UART0_GP2:
    GPIO_SetPinMux(GPIO0, GPIO_Pin_16, GPIO_FUNCTION_3);
    GPIO_SetPinMux(GPIO0, GPIO_Pin_17, GPIO_FUNCTION_3);
    break;
  case UART0_GP7:
    GPIO_SetPinMux(GPIO1, GPIO_Pin_24, GPIO_FUNCTION_2);
    GPIO_SetPinMux(GPIO1, GPIO_Pin_25, GPIO_FUNCTION_2);
    break;
  case UART1_GP0:
    GPIO_SetPinMux(GPIO0, GPIO_Pin_2, GPIO_FUNCTION_2);
    GPIO_SetPinMux(GPIO0, GPIO_Pin_3, GPIO_FUNCTION_2);
    break;
  case UART1_GP2:
    GPIO_SetPinMux(GPIO0, GPIO_Pin_18, GPIO_FUNCTION_2);
    GPIO_SetPinMux(GPIO0, GPIO_Pin_19, GPIO_FUNCTION_2);
    break;
  case UART2_GP0:
    GPIO_SetPinMux(GPIO0, GPIO_Pin_0, GPIO_FUNCTION_3);
    GPIO_SetPinMux(GPIO0, GPIO_Pin_1, GPIO_FUNCTION_3);
    break;
  case UART2_GP7:
    GPIO_SetPinMux(GPIO1, GPIO_Pin_26, GPIO_FUNCTION_2);
    GPIO_SetPinMux(GPIO1, GPIO_Pin_27, GPIO_FUNCTION_2);
    break;
  default:
    break;
  }

  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStruct.NVIC_IRQChannelPriority = 2;
  NVIC_Init(&NVIC_InitStruct);

  UART_Reset(UARTx);
  UART_StructInit(&UART_InitStructure);
  UART_InitStructure.UART_BaudRate = BaudRate;
  UART_InitStructure.UART_RXIFLSEL = UART_RXIFLSEL_14;
  UART_Init(UARTx, &UART_InitStructure);
  /* set timeout to 8 uart clk cycle len */
  UARTx->CTRL0_CLR = UART_CTRL0_RXTIMEOUT;
  UARTx->CTRL0_SET = 8 << 16;

  UART_ITConfig(UARTx, UART_IT_RXIEN | UART_IT_RTIEN, ENABLE);
  UART_Cmd(UARTx, ENABLE);
}

/**
  * @brief  Send data in dma mode
  * @param  UARTx: Select the UART peripheral.
  *   This parameter can be one of the following values:
  *   UARTx, x:[0:1:2]
  * @param  buf: data buf to be sent, must be 32 byte alignment
  * @param  size: data size
  * @param  channel: select the dma channel.
  *   This parameter can be one of the following values:
  *   DMA_CHANNEL_0/1/2/3
  * @param  isDmaBlock: DMA_NONBLOCK = return immediately
  *                     DMA_BLOCK = return when sent data
  * @param  isEnIrq: specifies whether enable channel dma complete interrupt or not,set with ENABLE/DISABLE.
  *          if set ENABLE, the return value must be saved by user. the return value is dma channel,
  *          the channel is use to DmaFreeChannel(channel) in IRQ handler function.
  * @retval: if isEnIrq = DISABLE
  *          -1=failed
  *           0=success
  *         if isEnIrq = ENABLE
  *           return the requested dma channel
  */
int UART_DMASendData(UART_TypeDef *UARTx, char *buf, int size, DmaBlockStatus isDmaBlock, FunctionalState isEnIrq)
{
  uint32_t temreg;
  DMAchannel channel;
  DMAChannel_TypeDef *TxDMAChannel;

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

  DmaChannelInterrupt(channel, isEnIrq);//dma传输完成中断
  TxDMAChannel = (DMAChannel_TypeDef *)(DMA_BASE + channel*0x58);

  temreg = 0x00000000 + (0 << DMA_CTRL_INT_EN)  //INT_EN, ch irq enable
                      + (0 << DMA_CTRL_DST_TR_WIDTH)      // DST_TR_WIDTH, des transfer width, should set to HSIZE, here is 000, means 8bit
                      + (0 << DMA_CTRL_SRC_TR_WIDTH)      // SRC_TR_WIDTH, sor transfer width, should set to HSIZE, here is 000, means 8bit
                      + (2 << DMA_CTRL_DINC)      // DINC, des addr increment, des is SPI, so should set to 1x, means no change
                      + (0 << DMA_CTRL_SINC)      // SINC, sor addr increment, src is sram, so should set to 00, means to increase 
                      + (2 << DMA_DEST_MSIZE)     // DEST_MSIZE, des burst length, set to 001 means 4 DST_TR_WIDTH per burst transcation
                      + (2 << DMA_SRC_MSIZE)     // SRC_MSIZE, sor burst length, set to 001 means 4 SOR_TR_WIDTH per burst transcation
                      + (1 << DMA_TTC_FC)     // TT_FC,transfer type and flow control,001 means memory to peripheral,dma is flow controller
                      + (0 << DMA_LLP_DST_EN)     // LLP_DST_EN, des block chaining enable, set to 0 disable it
                      + (0 << DMA_LLP_SRC_EN) ;   // LLP_SOR_EN, sor block chaining enable, set to 0 disable it  
  DMA->DmaCfgReg = 1;
  if(UARTx == UART0)
  {
    RCC->DMA_CH_SEL &= ~(1 << 0);
    DmaChannelCFGset(channel, 0, (REQ_UART0TX_TIM16 << DMA_CFG_SRC_PER) + (REQ_UART0TX_TIM16 << DMA_CFG_DEST_PER));
  }
  else if(UARTx == UART1)
  {
    DmaChannelCFGset(channel, 0, (REQ_UART1TX << DMA_CFG_SRC_PER) + (REQ_UART1TX << DMA_CFG_DEST_PER));
  }else if(UARTx == UART2)
  {
    DmaChannelCFGset(channel, 0, (REQ_UART2TX << DMA_CFG_SRC_PER) + (REQ_UART2TX << DMA_CFG_DEST_PER));
  }

  TxDMAChannel->LLP = 0;
  TxDMAChannel->CTL_H = size;
  TxDMAChannel->SAR = (uint32_t)buf;
  TxDMAChannel->DAR = (uint32_t)&UARTx->DATA;
  TxDMAChannel->CTL_L = temreg;

  UARTx->LINECTRL_SET = UART_LINECTRL_FEN;
  UARTx->CTRL2_CLR = UART_CTRL2_TXIFLSEL;
  UARTx->CTRL2_SET = UART_TXIFLSEL_8;
  UARTx->CTRL2_SET = UART_CTRL2_TXDMAE;
  // UARTx->CTRL1_CLR = UART_CTRL1_XFER_COUNT;
  UARTx->CTRL1_SET = size;
  UARTx->CTRL1_SET = UART_CTRL1_RUN;

  DMA->ChEnReg = 0x101 << channel;
  if(isDmaBlock == DMA_BLOCK)
  {
    while(DMA->ChEnReg & (0x01 << channel));
  }

  if (isEnIrq) return channel;
  DmaFreeChannel(channel);

  return 0;
}

/**
  * @brief  receive data in dma mode
  * @param  UARTx: Select the UART peripheral.
  *   This parameter can be one fo the following values:
  *   UARTx, x:[0:1:2]
  * @param  buf: buffer for received data, must be 32 byte alignment
  * @param  size: data size to be received
  * @param  channel: select the dma channel.
  *   This parameter can be one of the following values:
  *   DMA_CHANNEL_0/1/2/3
  * @param  isDmaBlock: DMA_NONBLOCK = return immediately
  *                     DMA_BLOCK = return when received 'size' specified data
  * @param  isEnIrq: specifies whether enable channel dma complete interrupt or not,set with ENABLE/DISABLE.
  *          if set ENABLE, the return value must be saved by user. the return value is dma channel,
  *          the channel is use to DmaFreeChannel(channel) in IRQ handler function.
  * @retval: if isEnIrq = DISABLE
  *          -1=failed
  *           0=success
  *         if isEnIrq = ENABLE
  *           return the requested dma channe
  */
void UART_DMARecvIRQHandler(void);
int UART_DMAReceiveData(UART_TypeDef *UARTx, char *buf, int size, DmaBlockStatus isDmaBlock, FunctionalState isEnIrq)
{
  uint32_t temreg;
  DMAchannel channel;
  DMAChannel_TypeDef *RxDmaChannel;

  if(size > CHANNEL_MAX_SIZE)
  {
    printf("rx size beyond dma channel ability\r\n");
    return -1;
  }

  channel = DmaRequestChannel(UART_DMARecvIRQHandler);
  if ((int)channel >= DMAChannelNum)
  {
    printf("all dma channel busy\r\n");
    return -1;
  }

  RxDmaChannel = (DMAChannel_TypeDef *)(DMA_BASE + channel*0x58);

  temreg = 0x00000000 + (1 << DMA_CTRL_INT_EN)  //INT_EN, ch irq enable
                      + (0 << DMA_CTRL_DST_TR_WIDTH)      // DST_TR_WIDTH, des transfer width, should set to HSIZE, here is 000, means 8bit
                      + (0 << DMA_CTRL_SRC_TR_WIDTH)      // SRC_TR_WIDTH, sor transfer width, should set to HSIZE, here is 000, means 8bit
                      + (0 << DMA_CTRL_DINC)      // DINC, des addr increment, des is SPI, so should set to 1x, means no change
                      + (2 << DMA_CTRL_SINC)      // SINC, sor addr increment, src is sram, so should set to 00, means to increase 
                      + (2 << DMA_DEST_MSIZE)     // DEST_MSIZE, des burst length, set to 001 means 4 DST_TR_WIDTH per burst transcation
                      + (2 << DMA_SRC_MSIZE)     // SRC_MSIZE, sor burst length, set to 001 means 4 SOR_TR_WIDTH per burst transcation
                      + (2 << DMA_TTC_FC)     // TT_FC,transfer type and flow control,001 means memory to peripheral,dma is flow controller
                      + (0 << DMA_LLP_DST_EN)     // LLP_DST_EN, des block chaining enable, set to 0 disable it
                      + (0 << DMA_LLP_SRC_EN) ;   // LLP_SOR_EN, sor block chaining enable, set to 0 disable it  
  DMA->DmaCfgReg = 1;
  if(UARTx == UART0)
  {
    RCC->DMA_CH_SEL &= ~(1 << 1);
    DmaChannelCFGset(channel, 0, (REQ_UART0RX_TIM17 << DMA_CFG_SRC_PER) + (REQ_UART0RX_TIM17 << DMA_CFG_DEST_PER));
  }
  else if(UARTx == UART1)
  {
    DmaChannelCFGset(channel, 0, (REQ_UART1RX << DMA_CFG_SRC_PER) + (REQ_UART1RX << DMA_CFG_DEST_PER));
  }else if(UARTx == UART2)
  {
    DmaChannelCFGset(channel, 0, (REQ_UART2RX << DMA_CFG_SRC_PER) + (REQ_UART2RX << DMA_CFG_DEST_PER));
  }

  RxDmaChannel->LLP = 0;
  RxDmaChannel->CTL_H = size;
  RxDmaChannel->SAR = (uint32_t)&UARTx->DATA;
  RxDmaChannel->DAR = (uint32_t)buf;
  RxDmaChannel->CTL_L = temreg;

  UARTx->LINECTRL_SET = UART_LINECTRL_FEN;
  UARTx->CTRL2_CLR = UART_CTRL2_RXIFLSEL;
  UARTx->CTRL2_SET = UART_RXIFLSEL_8;
  UARTx->CTRL2_SET = UART_CTRL2_RXDMAE;
  // UARTx->CTRL0_CLR = UART_CTRL0_XFER_COUNT;
  UARTx->CTRL0_SET = size;
  UARTx->CTRL0_SET = UART_CTRL0_RUN;

  DmaChannelClearInterruptStatus(channel);
  DmaChannelInterrupt(channel, isEnIrq);//dma传输完成中断
  DMA->ChEnReg = 0x101 << channel;
  if(isDmaBlock == DMA_BLOCK)
  {
    while(DMA->ChEnReg & (0x01 << channel));
  }

  if (isEnIrq) return channel;
  DmaFreeChannel(channel);

  return 0;
}


/* below is uart send/receive demo */

char test_buf[256];
volatile int recvlen = 0;
volatile int recv_flag = 0;
volatile int rx_ptr = 0;
void UART_IRQHandler(UART_TypeDef *UARTx)
{
  if (UART_GetITStatus(UARTx, UART_IT_RXIS))
  {
    while (!UART_GetFlagStatus(UARTx, UART_FLAG_RXFE))
      test_buf[rx_ptr++] = UARTx->DATA;
  }

  if (UART_GetITStatus(UARTx, UART_IT_RTIS))
  {
    while (!UART_GetFlagStatus(UARTx, UART_FLAG_RXFE))
      test_buf[rx_ptr++] = UARTx->DATA;

    recvlen = rx_ptr;
    recv_flag = 1;
    rx_ptr = 0;
  }
}

void UART0_IRQHandler(void)
{
  UART_IRQHandler(UART0);
}


void UART1_IRQHandler(void)
{
  UART_IRQHandler(UART1);
}

void UART2_IRQHandler(void)
{
  UART_IRQHandler(UART2);
}


/* how to use UART API */
#define DMA_RECV_TEST       1
#define DMA_TEST_SIZE       20
char DmaRecvBuf[256];
int irqChannel;

void uart_test(void)
{
  NVIC_InitTypeDef NVIC_InitStruct;
  char *str = "This is Y6 UART test demo\r\n";
	UART_Configuration(UART1, 115200, UART1_GP0);
	memcpy(test_buf, str, strlen(str));
  UART_DMASendData(UART1, test_buf, strlen(str), DMA_BLOCK,DISABLE);
	memset(test_buf, 0, sizeof(test_buf));

  #if (!DMA_RECV_TEST)
  /* use interrupt to receive data with unknown data length */
  while(1)
  {
    if (recv_flag == 1)
    {
      printf("uart received %d bytes, comment is %s\r\n", recvlen, test_buf);
      memset(test_buf, 0, sizeof(test_buf));
      recv_flag = 0;
    }
  }
  #else
  /* use dma to receive n bytes data */
  NVIC_InitStruct.NVIC_IRQChannel = DMA_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStruct.NVIC_IRQChannelPriority = 2;
  NVIC_Init(&NVIC_InitStruct);
  /* disable uart irq when using dma */
  UART_ITConfig(UART1, UART_IT_RTIEN | UART_IT_RXIEN, DISABLE);
  memset(DmaRecvBuf, 0, sizeof(DmaRecvBuf));
  irqChannel = UART_DMAReceiveData(UART1, DmaRecvBuf, DMA_TEST_SIZE, DMA_NONBLOCK, ENABLE);

  while(1);

  #endif
}


void UART_DMARecvIRQHandler(void)
{
  printf("uart dma received: %s\r\n", DmaRecvBuf);
  //TODO...
  DmaFreeChannel(irqChannel);
}

