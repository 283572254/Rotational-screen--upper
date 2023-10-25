#ifndef  __Y6_UTILITY_USART_H
#define  __Y6_UTILITY_USART_H
#include "Y6_uart.h"

typedef enum
{
  UART0_GP2,
  UART0_GP7,
  UART1_GP0,
  UART1_GP2,
  UART2_GP0,
  UART2_GP7,
} UartPinGroup;

typedef enum
{
  DMA_NONBLOCK,
  DMA_BLOCK,
} DmaBlockStatus;

void UART_Configuration(UART_TypeDef *UARTx, uint32_t BaudRate, UartPinGroup PinGroup);
int UART_DMASendData(UART_TypeDef *UARTx, char *buf, int size, DmaBlockStatus isDmaBlock, FunctionalState isEnIrq);
int UART_DMAReceiveData(UART_TypeDef *UARTx, char *buf, int size, DmaBlockStatus isDmaBlock, FunctionalState isEnIrq);

#endif //__Y6_UTILITY_USART_H
