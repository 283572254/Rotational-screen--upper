 
/* Includes ------------------------------------------------------------------*/
#include "Y6_uart.h"
#include "Y6_rcc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** @addtogroup Y6_StdPeriph_Driver
  * @{
  */

/** @defgroup UART 
  * @brief UART driver modules
  * @{
  */

/** @defgroup UART_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup UART_Private_Defines
  * @{
  */

#define UART_LINECTRL_CLEAR_Mask  ((uint32_t)0x0000C001)
#define UART_CTRL2_CLEAR_Mask     ((uint32_t)0xFF8834FF)

#define UART_CTRL2_UE_BIT         ((uint32_t)0x00000001)         

#define UART_CTRL2_LBE_BIT        ((uint32_t)0x00000080)         

#define UART_LINECTRL_BRK_BIT     ((uint32_t)0x00000001)         

#define UART_CTRL2_IREN_BIT       ((uint32_t)0x00000002)  /*!< UART IrDA Enable Mask */
#define UART_IRDA_CLEAR_Mask      ((uint32_t)0xFFFFFFFB)

#define UART_AUTOBAUD_EN_Set      ((uint16_t)0x0001)
#define UART_AUTOBAUD_EN_Reset    ((uint16_t)0xFFFE)
#define UART_AUTOBAUD_CLEAR_Mask  ((uint16_t)0xFFF9)

#define UART_INTR_IT_Mask         ((uint32_t)0x00003FF0)



/**
  * @}
  */

/** @defgroup UART_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup UART_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup UART_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup UART_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the UARTx peripheral registers to their default reset values.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values: UARTx,x:[0:1].
  * @retval None
  */
void UART_Reset(UART_TypeDef* UARTx)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  
  if (UARTx == UART0)
  {
    RCC_SetPRESETCTRL(1<<PRESET_BIT_UART0, DISABLE);
    RCC_SetPRESETCTRL(1<<PRESET_BIT_UART0, ENABLE);
  }
  else if (UARTx == UART1)
  {
    RCC_SetPRESETCTRL(1<<PRESET_BIT_UART1, DISABLE);
    RCC_SetPRESETCTRL(1<<PRESET_BIT_UART1, ENABLE);
  }else if(UARTx == UART2)
  {
    RCC_SetPRESETCTRL(1<<PRESET_BIT_UART2, DISABLE);
    RCC_SetPRESETCTRL(1<<PRESET_BIT_UART2, ENABLE);
  }
}

/**
  * @brief  Initializes the UARTx peripheral according to the specified
  *   parameters in the UART_InitStruct .
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UARTx,x:[0:1].
  * @param  UART_InitStruct: pointer to a UART_InitTypeDef structure
  *   that contains the configuration information for the specified UART peripheral.
  * @retval None
  */
void UART_Init(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct)
{
  uint32_t tmpreg = 0, UART_Freq = 0;
  uint32_t Baud_div,BAUD_DIVFRA,BAUD_DIVINT;
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
//  assert_param(IS_UART_BAUDRATE(UART_InitStruct->UART_BaudRate));  
  assert_param(IS_UART_WORD_LENGTH(UART_InitStruct->UART_WordLength));
  assert_param(IS_UART_STOPBITS(UART_InitStruct->UART_StopBits));
  assert_param(IS_UART_PARITY(UART_InitStruct->UART_Parity));
  assert_param(IS_UART_MODE(UART_InitStruct->UART_Mode));
  assert_param(IS_UART_HARDWARE_FLOW_CONTROL(UART_InitStruct->UART_HardwareFlowControl));
  assert_param(IS_UART_SoftwareFlowControl(UART_InitStruct->UART_SoftwareFlowControl));
  assert_param(IS_UART_TXIFLSEL(UART_InitStruct->UART_TXIFLSEL));
  assert_param(IS_UART_RXIFLSEL(UART_InitStruct->UART_RXIFLSEL));
  assert_param(IS_UART_FEN(UART_InitStruct->UART_FEN));
  /* The hardware flow control is available only for UARTx,x:[0:7] */
  if ((UART_InitStruct->UART_HardwareFlowControl != UART_HardwareFlowControl_None) || 
    (UART_InitStruct->UART_HardwareFlowControl != UART_SoftwareFlowControl_None))
  {
    assert_param(IS_UART_FC_PERIPH(UARTx));
  }
/*---------------------------- UART LINECTRL Configuration -----------------------*/
  UARTx->CTRL0_CLR = UART_CTRL0_CLKGATE | UART_CTRL0_SFTRST;
  tmpreg = UARTx->LINECTRL;
  tmpreg &= UART_LINECTRL_CLEAR_Mask;

  if(UARTx == UART0)
    UART_Freq = RCC_GetClocksFreq(RCC_CLOCKFREQ_UART0CLK);
  else if(UARTx == UART1)
    UART_Freq = RCC_GetClocksFreq(RCC_CLOCKFREQ_UART1CLK);
  else if(UARTx == UART2)
    UART_Freq = RCC_GetClocksFreq(RCC_CLOCKFREQ_UART2CLK);

  Baud_div = (UART_Freq * 4) / (UART_InitStruct->UART_BaudRate);
  BAUD_DIVFRA = (Baud_div & 0x3f)<<8;
  BAUD_DIVINT = ((Baud_div & 0x3fffc0) >> 6) << 16;
  tmpreg  |=   BAUD_DIVINT | BAUD_DIVFRA | UART_InitStruct->UART_WordLength |
        UART_InitStruct->UART_StopBits | UART_InitStruct->UART_Parity|
        UART_InitStruct->UART_FEN;
  UARTx->LINECTRL = tmpreg;

/*---------------------------- UART CTRL2 Configuration -----------------------*/
  tmpreg = UARTx->CTRL2;
  tmpreg &= UART_CTRL2_CLEAR_Mask;
  tmpreg |= UART_InitStruct->UART_TXIFLSEL | UART_InitStruct->UART_RXIFLSEL |
        UART_InitStruct->UART_Mode | UART_InitStruct->UART_HardwareFlowControl | 
        UART_InitStruct->UART_SoftwareFlowControl;
  UARTx->CTRL2 = tmpreg;
  
}

/**
  * @brief  Fills each UART_InitStruct member with its default value.
  * @param  UART_InitStruct: pointer to a UART_InitTypeDef structure
  *   which will be initialized.
  * @retval None
  */
void UART_StructInit(UART_InitTypeDef* UART_InitStruct)
{
  /* UART_InitStruct members default value */
  UART_InitStruct->UART_TXIFLSEL = UART_TXIFLSEL_2;
  UART_InitStruct->UART_RXIFLSEL = UART_RXIFLSEL_2;
  UART_InitStruct->UART_FEN = UART_FEN_Enable;
  UART_InitStruct->UART_BaudRate = 115200;
  UART_InitStruct->UART_WordLength = UART_WordLength_8b;
  UART_InitStruct->UART_StopBits = UART_StopBits_1;
  UART_InitStruct->UART_Parity = UART_Parity_No ;
  UART_InitStruct->UART_Mode = UART_Mode_Tx | UART_Mode_Rx;
  UART_InitStruct->UART_HardwareFlowControl = UART_HardwareFlowControl_None;
  UART_InitStruct->UART_SoftwareFlowControl = UART_SoftwareFlowControl_None;
}

/**
  * @brief  Enables or disables the specified UART peripheral.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UARTx,x:[0:1].
  * @param  NewState: new state of the UARTx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_Cmd(UART_TypeDef* UARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected UART by setting the UE bit in the CTRL2 register */
    UARTx->CTRL2_SET = UART_CTRL2_UE_BIT;
  }
  else
  {
    /* Disable the selected UART by clearing the UE bit in the CTRL2 register */
    UARTx->CTRL2_CLR = UART_CTRL2_UE_BIT;
  }
}

/**
  * @brief  Enables or disables the Loop-Back Mode.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UARTx,x:[0:1].
  * @param  NewState: new state of the UARTx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_LBECmd(UART_TypeDef* UARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected UART by setting the LBE bit in the CTRL2 register */
    UARTx->CTRL2_SET = UART_CTRL2_LBE_BIT;
  }
  else
  {
    /* Disable the selected UART by clearing the LBE bit in the CTRL2 register */
    UARTx->CTRL2_CLR = UART_CTRL2_LBE_BIT;
  }
}

/**
  * @brief  Enables or disables the BRK.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UARTx,x:[0:1].
  * @param  NewState: new state of the UARTx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_BRKCmd(UART_TypeDef* UARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected UART by setting the BRK bit in the CTRL2 register */
    UARTx->LINECTRL_SET = UART_LINECTRL_BRK_BIT;
  }
  else
  {
    /* Disable the selected UART by clearing the BRK bit in the CTRL2 register */
    UARTx->LINECTRL_CLR = UART_LINECTRL_BRK_BIT;
  }
}

/**
  * @brief  Enables or disables the specified UART interrupts.
  * @param  UARTx: Select the UARTperipheral. 
  *   This parameter can be one of the following values:
  *   UARTx,x:[0:1].
  * @param  UART_IT: specifies the UART interrupt sources to be enabled or disabled.
  *   This parameter can be one of the following values:
  *     @arg UART_IT_RXIEN: Receive Interrupt Enable.
  *     @arg UART_IT_TXIEN: Transmit Interrupt Enable.
  *     @arg UART_IT_RTIEN: Receive Timeout Interrupt Enable.
  *     @arg UART_IT_FEIEN: Framing Error Interrupt Enable.
  *     @arg UART_IT_PEIEN: Parity Error Interrupt Enable.
  *     @arg UART_IT_BEIEN: Break Error Interrupt Enable.
  *     @arg UART_IT_OEIEN: Overrun Error Interrupt Enable.
  *     @arg UART_IT_TFEIEN:Tx FIFO EMPTY Raw Interrupt Enable.
  *     @arg UART_IT_ABEOEN:Autobaud End Interrupt Enable.
  *     @arg UART_IT_ABTOEN:Autobaud Timeout Interrupt Enable.
  * @param  NewState: new state of the specified UARTx interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_ITConfig(UART_TypeDef* UARTx, uint32_t UART_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_UART_CONFIG_IT(UART_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected UART by setting the UART_IT bit in the INTR register */
    UARTx->INTR_SET = UART_IT;
  }
  else
  {
    /* Disable the selected UART by clearing the UART_IT bit in the INTR register */
    UARTx->INTR_CLR = UART_IT;
  }
}

/**
  * @brief  Enables or disables the UARTx DMA interface.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UARTx,x:[0:1].
  * @param  UART_DMAReq: specifies the DMA request.
  *   This parameter can be any combination of the following values:
  *     @arg UART_DMAReq_Tx: UART DMA transmit request
  *     @arg UART_DMAReq_Rx: UART DMA receive request
  *     @arg UART_DMAReq_Rx_DMAONERROR: UART DMA receive and DMAONERROR request
  * @param  NewState: new state of the DMA Request sources.
  *   This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void UART_DMACmd(UART_TypeDef* UARTx, uint32_t UART_DMAReq, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_UART_DMA_PERIPH(UARTx));
  assert_param(IS_UART_DMAREQ(UART_DMAReq));  
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 
  if (NewState != DISABLE)
  {
    /* Enable the DMA transfer for selected requests by setting the DMAT and/or
       DMAR bits in the UART CTRL2 register */
    UARTx->CTRL2_SET = UART_DMAReq;
    if ((UART_DMAReq & UART_DMAReq_Rx) != 0)
      UARTx->CTRL0_SET = UART_CTRL0_RUN;
    if ((UART_DMAReq & UART_DMAReq_Tx) != 0)
      UARTx->CTRL1_SET = UART_CTRL1_RUN;

  }
  else
  {
    /* Disable the DMA transfer for selected requests by clearing the DMAT and/or
       DMAR bits in the UART CTRL2 register */
    UARTx->CTRL2_CLR = UART_DMAReq;
    if ((UART_DMAReq & UART_DMAReq_Rx) != 0)
      UARTx->CTRL0_CLR = UART_CTRL0_RUN;
    if ((UART_DMAReq & UART_DMAReq_Tx) != 0)
      UARTx->CTRL1_CLR = UART_CTRL1_RUN;
  }
}


/**
  * @brief  Transmits single data through the UARTx peripheral.
  * @param  UARTx: Select the UART operipheral. 
  *   This parameter can be one of the following values:
  *   UARTx,x:[0:1].
  * @param  Data: the data to transmit.
  * @retval None
  */
void UART_SendData(UART_TypeDef* UARTx, uint8_t Data)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  
  /* Transmit Data */
  UARTx->DATA = Data;
}

/**
  * @brief  Returns the most recent received data by the UARTx peripheral.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UARTx,x:[0:9].
  * @retval The received data.
  */
uint32_t UART_ReceiveData(UART_TypeDef* UARTx)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  
  /* Receive Data */
  return (UARTx->DATA);
}


/**
  * @brief  Configures the UARTx IrDA interface.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UARTx,x:[0:1].
  * @param  UART_IrDAMode: specifies the IrDA mode.
  *   This parameter can be one of the following values:
  *     @arg UART_IrDAMode_LowPower
  *     @arg UART_IrDAMode_Normal
  * @retval None
  */
void UART_IrDAConfig(UART_TypeDef* UARTx, uint32_t UART_IrDAMode)
{
  uint32_t tmpreg=0;
  /* Check the parameters */
  assert_param(IS_UART_IRDA_PERIPH(UARTx));
  assert_param(IS_UART_IRDA_MODE(UART_IrDAMode));
  
  tmpreg = UARTx->CTRL2;
  tmpreg &= UART_IRDA_CLEAR_Mask;
  tmpreg |= UART_IrDAMode;
  UARTx->CTRL2 = tmpreg;
}

/**
  * @brief  Enables or disables the UARTx IrDA interface.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UARTx,x:[0:1].
  * @param  NewState: new state of the IrDA mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_IrDACmd(UART_TypeDef* UARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_UART_IRDA_PERIPH(UARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the IrDA mode by setting the IREN bit in the CTRL2 register */
    UARTx->CTRL2_SET = UART_CTRL2_IREN_BIT;
  }
  else
  {
    /* Disable the IrDA mode by clearing the IREN bit in the CTRL2 register */
    UARTx->CTRL2_CLR = UART_CTRL2_IREN_BIT;
  }
}

/**
  * @brief  Set the baud rate divisor of the IRDA_LowPower.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UARTx,x:[0:1].
  * @param  ILPDVSR: The baud rate divisor of the IRDA_LowPower.
  * @retval None
  */
void UART_SetILPDVSR(UART_TypeDef* UARTx, uint8_t ILPDVSR)
{
  assert_param(IS_UART_IRDA_PERIPH(UARTx));
  assert_param(IS_UART_ILPDVSR(ILPDVSR));

  UARTx->ILPR = ILPDVSR;
}

/**
  * @brief  Initializes the UARTx peripheral according to the specified
  *   parameters in the UART_RS485InitStruct .
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UARTx,x:[0:1].
  * @param  UART_RS485InitStruct: pointer to a UART_RS485InitTypeDef structure
  *   that contains the configuration information for the specified UART peripheral.
  * @retval None
  */
void UART_RS485Init(UART_TypeDef* UARTx, UART_RS485InitTypeDef* UART_RS485InitStruct)
{
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_UART_RS485_NMM(UART_RS485InitStruct->UART_RS485_MODE));
  assert_param(IS_UART_RS485_DCTRL(UART_RS485InitStruct->UART_RS485_DCTRL));
  assert_param(IS_UART_RS485_ONIV_MODE(UART_RS485InitStruct->UART_RS485_ONIV));
  
  UARTx->RS485CTRL = UART_RS485InitStruct->UART_RS485_MODE | UART_RS485InitStruct->UART_RS485_DCTRL | UART_RS485InitStruct->UART_RS485_ONIV;
}

/**
  * @brief  Fills each UART_RS485InitStruct member with its default value.
  * @param  UART_InitStruct: pointer to a UART_RS485InitTypeDef structure
  *   which will be initialized.
  * @retval None
  */
void UART_RS485StructInit(UART_RS485InitTypeDef* UART_RS485InitStruct)
{
  UART_RS485InitStruct->UART_RS485_MODE = UART_RS485_NMM_Disable;
  UART_RS485InitStruct->UART_RS485_DCTRL = UART_RS485_DCTRL_RTS;
  UART_RS485InitStruct->UART_RS485_ONIV = UART_RS485_ONIV_MODE_1;
}

/**
  * @brief  Sets the address of the UART_RS485.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UARTx,x:[0:1].
  * @param  UART_Address: The Address of UART_RS485.
  * @retval None
  */
void UART_RS485SetAddress(UART_TypeDef* UARTx, uint8_t UART_Address)
{
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_UART_RS485ADDRESS(UART_Address)); 

  UARTx->RS485ADRMATCH = UART_Address;
}

/**
  * @brief  Sets the delay time of controling direction.
  * @param  UARTx: Select the UART or the HUART peripheral. 
  *   This parameter can be one of the following values:
  *   HUART0, HUART1, UART0, UART1, UART2 or UART3.
  * @param  UART_DLYTime: The delay time of controling direction.
  * @retval None
  */
void UART_RS485SetDelay(UART_TypeDef* UARTx, uint8_t UART_DLYTime)
{
  assert_param(IS_UART_ALL_PERIPH(UARTx));

  UARTx->RS485DLY = UART_DLYTime;
}

/**
  * @brief  Configures the UARTx AUTOBAUD interface.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UARTx,x:[0:1].
  * @param  UART_AUTOBAUDMODE: specifies the AUTOBAUD mode.
  *   This parameter can be one of the following values:
  *     @arg UART_AUTOBAUD_MODE_RE_0
  *     @arg UART_AUTOBAUD_MODE_RE_1
  *     @arg UART_AUTOBAUD_MODE_RD_0
  *     @arg UART_AUTOBAUD_MODE_RD_1
  * @retval None
  */
void UART_AUTOBAUDConfig(UART_TypeDef* UARTx, uint16_t UART_AUTOBAUDMODE)
{
  uint16_t tmpreg=0;
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_UART_AUTOBAUD_MODE(UART_AUTOBAUDMODE));

  tmpreg = UARTx->AUTOBAUD;
  tmpreg &= UART_AUTOBAUD_CLEAR_Mask;
  tmpreg |= UART_AUTOBAUDMODE;
  UARTx->AUTOBAUD = tmpreg;
}

/**
  * @brief  Enables or disables the UARTx AUTOBAUD interface.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UARTx,x:[0:1].
  * @param  NewState: new state of the AUTOBAUD mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */

void UART_AUTOBAUDCmd(UART_TypeDef* UARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 
  if (NewState != DISABLE)
  {
    /* Start AUTOBAUD */
    UARTx->AUTOBAUD |= UART_AUTOBAUD_EN_Set;
  }
  else
  {
    /* Stop AUTOBAUD */
    UARTx->AUTOBAUD &= UART_AUTOBAUD_EN_Reset;
  }
}

/**
  * @brief  Checks whether the specified UART flag is set or not.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UARTx,x:[0:1].
  * @param  UART_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg UART_FLAG_FERR:  Framing Error Flag.
  *     @arg UART_FLAG_PERR:  Parity Error Flag.
  *     @arg UART_FLAG_BERR:  Break Error Flag.
  *     @arg UART_FLAG_OERR:  Overrun Error Flag.
  *     @arg UART_FLAG_RXFE:  Receive FIFO Empty Flag.
  *     @arg UART_FLAG_TXFF:  Transmit FIFO Full Flag.
  *     @arg UART_FLAG_RXFF:  Receive FIFO Full Flag.
  *     @arg UART_FLAG_TXFE:  Transmit FIFO Empty Flag.
  *     @arg UART_FLAG_CTS:   Clear To Send Flag.
  *     @arg UART_FLAG_BUSY:  UART Busy Flag.
  * @retval The new state of UART_FLAG (SET or RESET).
  */
FlagStatus UART_GetFlagStatus(UART_TypeDef* UARTx, uint32_t UART_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_UART_FLAG(UART_FLAG));
  /* The CTS flag is not available for UART4 and UART5 */
  if (UART_FLAG == UART_FLAG_CTS)
  {
    assert_param(IS_UART_FC_PERIPH(UARTx));
  }  
  
  if ((UARTx->STAT & UART_FLAG) != RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the UARTx's pending flags.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UARTx,x:[0:1].
  * @param  UART_FLAG: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg UART_FLAG_FERR:  Framing Error Flag.
  *     @arg UART_FLAG_PERR:  Parity Error Flag.
  *     @arg UART_FLAG_BERR:  Break Error Flag.
  *     @arg UART_FLAG_OERR:  Overrun Error Flag.   
  * @retval None
  */
void UART_ClearFlag(UART_TypeDef* UARTx, uint32_t UART_FLAG)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_UART_CLEAR_FLAG(UART_FLAG));
  
  UARTx->STAT &= ~UART_FLAG;
}

/**
  * @brief  Checks whether the specified UART interrupt has occurred or not.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UARTx,x:[0:1].
  * @param  UART_IT: specifies the UART interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg UART_IT_RXIS:   Receive Interrupt Status.
  *     @arg UART_IT_TXIS:   Transmit Interrupt Status.
  *     @arg UART_IT_RTIS:   Receive Timeout Interrupt Status.
  *     @arg UART_IT_FEIS:   Framing Error Interrupt Status.
  *     @arg UART_IT_PEIS:   Parity Error Interrupt Status.
  *     @arg UART_IT_BEIS:   Break Error Interrupt Status.
  *     @arg UART_IT_OEIS:   Overrun Error Interrupt Status.
  *     @arg UART_IT_TFEIS:  Tx FIFO EMPTY Raw Interrupt state.
  *     @arg UART_IT_ABEO:   AUTOBAUD End state.
  *     @arg UART_IT_ABTO:   AUTOBAUD TimeOut state.
  * @retval The new state of UART_IT (SET or RESET).
  */
ITStatus UART_GetITStatus(UART_TypeDef* UARTx, uint32_t UART_IT)
{
  ITStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_UART_GET_IT(UART_IT));
  if((UARTx->INTR & UART_IT) != RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  
  return bitstatus;  
}

/**
  * @brief  Clears the UARTx interrupt pending bits.
  * @param  UARTx: Select the UART peripheral. 
  *   This parameter can be one of the following values:
  *   UARTx,x:[0:1].
  * @param  UART_IT: specifies the interrupt pending bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg UART_IT_RXIS:   Receive Interrupt .
  *     @arg UART_IT_TXIS:   Transmit Interrupt .
  *     @arg UART_IT_RTIS:   Receive Timeout Interrupt .
  *     @arg UART_IT_FEIS:   Framing Error Interrupt .
  *     @arg UART_IT_PEIS:   Parity Error Interrupt .
  *     @arg UART_IT_BEIS:   Break Error Interrupt .
  *     @arg UART_IT_OEIS:   Overrun Error Interrupt .
  *     @arg UART_IT_TFEIS:  Tx FIFO EMPTY Raw Interrupt .
  *     @arg UART_IT_ABEOIntClr: AUTOBAUD End Interrupt.
  *     @arg UART_IT_ABTOIntClr: AUTOBAUD TimeOut Interrupt.
  * @retval None
  */
void UART_ClearITPendingBit(UART_TypeDef* UARTx, uint32_t UART_IT)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_UART_CLEAR_IT(UART_IT));
  if((UART_IT >= UART_IT_ABEOIntClr))
  {
    UARTx->AUTOBAUD |= ((UART_IT & (~UART_INTR_IT_Mask)) >> 16);
    if((UART_IT & UART_INTR_IT_Mask) != 0)
    {
      UARTx->INTR_CLR = (UART_IT & UART_INTR_IT_Mask); 
    }
  }
  else
  {
     UARTx->INTR_CLR = UART_IT;
  }
}




/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2013 TDO *****END OF FILE****/

