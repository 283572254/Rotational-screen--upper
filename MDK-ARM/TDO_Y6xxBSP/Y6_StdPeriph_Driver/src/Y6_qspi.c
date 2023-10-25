 

/* Includes ------------------------------------------------------------------*/
#include "Y6_qspi.h"
#include "Y6_rcc.h"
#include "stdio.h"
/** @addtogroup Y6_StdPeriph_Driver
  * @{
  */

/** @defgroup QSPI
  * @brief QSPI driver modules
  * @{
  */

/** @defgroup QSPI_Private_Typedefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup QSPI_Private_Functions
  * @{
  */

/**
  * @brief  Sets the power status of the QSPI controller.
  * @param QSPIptr: the QUAD spi controller base address.
  * @param  QSPI_PowerState: new state of the Power state. 
  *   This parameter can be one of the following values:
  *     @arg QSPI_PowerState_OFF
  *     @arg QSPI_PowerState_ON
  * @retval None
  */
void QSPI_SetPowerState(QSPI_TypeDef *QSPIptr, uint32_t QSPI_PowerState)
{

  /* Check the parameters */
  assert_param(IS_QSPI_POWER_STATE(QSPI_PowerState));

  if (QSPI_PowerState == QSPI_PowerState_ON)
  {
    if (QSPIptr == QSPI0){
      RCC_ResetAHBCLK(1 << AHBCLK_BIT_QSPI0);
    }
    else if (QSPIptr == QSPI1){
      RCC_ResetAHBCLK(1 << AHBCLK_BIT_QSPI1);
    }else{
      RCC_ResetAHBCLK(1 << AHBCLK_BIT_QSPI2);
    }
  }
  else
  {
    if (QSPIptr == QSPI0)
      RCC_SetAHBCLK(1 << AHBCLK_BIT_QSPI0, DISABLE);
    else if (QSPIptr == QSPI1)
      RCC_SetAHBCLK(1 << AHBCLK_BIT_QSPI1, DISABLE);
    else
      RCC_SetAHBCLK(1 << AHBCLK_BIT_QSPI2, DISABLE);
  }
}

/**
  * @brief  Initializes the QSPI peripheral according to the specified 
  *   parameters in the QSPI_InitStruct.  
  * @param QSPIptr: the QUAD spi controller base address.
  * @param  QSPI_InitStruct : pointer to a QSPI_InitTypeDef structure 
  *   that contains the configuration information for the QSPI peripheral.
  * @retval None
  */
void QSPI_HwInit(QSPI_TypeDef *QSPIptr, QSPI_InitTypeDef *QSPI_InitStruct)
{
  volatile int i;
  /* Check the parameters */
  assert_param(IS_QSPI_CPOL(QSPI_InitStruct->QSPI_CPOL));
  assert_param(IS_QSPI_CPHA(QSPI_InitStruct->QSPI_CPHA));
  assert_param(IS_QSPI_FIRST_BIT(QSPI_InitStruct->QSPI_FirstBit));
  assert_param(IS_QSPI_ClockDiv_setting(QSPI_InitStruct->QSPI_ClockDiv));
  //assert_param(IS_QSPI_ClockRate_setting(QSPI_InitStruct->QSPI_ClockRate));
  assert_param(IS_QPSI_MASTER_OR_SLAVE_MODE(QSPI_InitStruct->QSPI_SlaveMode));
  assert_param(IS_QSPI_MODE(QSPI_InitStruct->QSPI_ModeSelect));
  assert_param(IS_QSPI_FRAME_LENGTH(QSPI_InitStruct->QSPI_FrameLength));
  
  QSPI_SetPowerState(QSPIptr, QSPI_PowerState_ON);

#if 1
  /**Vital notice, must delay for a while**/
  for (i = 0; i < 0x1000; i++)
    ;
#endif

  QSPI_ModeSet(QSPIptr,QSPI_InitStruct->QSPI_ModeSelect);
  QSPI_FrameLengthSet(QSPIptr,QSPI_InitStruct->QSPI_FrameLength);
  QSPIptr->CTRL1_SET = QSPI_InitStruct->QSPI_CPOL | QSPI_InitStruct->QSPI_CPHA | \
                       QSPI_InitStruct->QSPI_SlaveMode;
  QSPI_FirstBitSet(QSPIptr, QSPI_InitStruct->QSPI_FirstBit);
  QSPIptr->TIMING = 0xFFFF0000 | QSPI_InitStruct->QSPI_ClockDiv | QSPI_InitStruct->QSPI_ClockRate;

  QSPIptr->CTRL1_SET = 0x0;
}

/**
   * @brief  Specifies the SPI mode.
   * @param  QSPIptr: the QUAD spi controller base address.  
   * @param  ModeSelect: the selected spi mode.
   *        This parameter can be one of the following values: 
   *         @arg QSPI_STD: standard spi mode 
   *         @arg QSPI_DUAL: Dual spi mode 
   *         @arg QSPI_QUAD: quad spi mode 
   * @retval None 
   */
void QSPI_ModeSet(QSPI_TypeDef *QSPIptr, QSPIModeSelect ModeSelect)
{
  /* Check the parameters */
  assert_param(IS_QSPI_MODE(ModeSelect));

  if (ModeSelect == QSPI_STD)
  {
    QSPIptr->CTRL1 = (QSPIptr->CTRL1 & 0xfffffff8) | 0x00;
  }
  else if (ModeSelect == QSPI_DUAL)
  {
    QSPIptr->CTRL1 = (QSPIptr->CTRL1 & 0xfffffff8) | 0x01;
  }
  else
  {
    QSPIptr->CTRL1 = (QSPIptr->CTRL1 & 0xfffffff8) | 0x02;
  }
}

/**
  * @brief  Set Number of bits in each frame of data
  * @param  QSPIptr: the QUAD spi controller base address. 
  * @param  wl:word length
  *    This parameter can be one of the following values: 
  *         @arg QSPI_FRAME_LENGTH_4Bit 
  *         @arg QSPI_FRAME_LENGTH_8Bit
  *         @arg QSPI_FRAME_LENGTH_16Bit
  *         @arg QSPI_FRAME_LENGTH_24Bit
  *         @arg QSPI_FRAME_LENGTH_32Bit
  * 
  * @retval None 
  */
void QSPI_FrameLengthSet(QSPI_TypeDef *QSPIptr, uint8_t wl)
{
  assert_param(IS_QSPI_FRAME_LENGTH(wl));
  switch (wl)
  {
    case QSPI_FRAME_LENGTH_4Bit:
      QSPIptr->CTRL1 = (QSPIptr->CTRL1 & 0xffffff07) | QSPI_FRAME_LENGTH_4Bit;
      break;
    case QSPI_FRAME_LENGTH_8Bit:
      QSPIptr->CTRL1 = (QSPIptr->CTRL1 & 0xffffff07) | QSPI_FRAME_LENGTH_8Bit;
      break;
    case QSPI_FRAME_LENGTH_16Bit:
      QSPIptr->CTRL1 = (QSPIptr->CTRL1 & 0xffffff07) | QSPI_FRAME_LENGTH_16Bit;
      break;
    case QSPI_FRAME_LENGTH_24Bit:
      QSPIptr->CTRL1 = (QSPIptr->CTRL1 & 0xffffff07) | QSPI_FRAME_LENGTH_24Bit;
      break;
    case QSPI_FRAME_LENGTH_32Bit:
      QSPIptr->CTRL1 = (QSPIptr->CTRL1 & 0xffffff07) | QSPI_FRAME_LENGTH_32Bit;
      break;
    default:
      break;
  }
}

/**
  * @brief  Set to support 2/4 line send command word (QSPI mode enable, only valid
  *          for send command word), default is 1 line
  * @param  QSPIptr: the QUAD spi controller base address. 
  * @param  enable:set 0/1 to set 2/4 line send command word or 1 line. 
  * @retval None 
  */
void QSPI_QpiSet(QSPI_TypeDef *QSPIptr, uint8_t enable)
{
  if (enable)
  {
    QSPIptr->CTRL1 = QSPIptr->CTRL1 | 0x00800000;
  }
  else
  {
    QSPIptr->CTRL1 = QSPIptr->CTRL1 & 0xFF7FFFFF;
  }
}

/**
  * @brief  Gets the power status of the QUAD SPI controller.
  * @param QSPIptr: the QUAD spi controller base address.
  * @retval Power status of the controller. The returned value can
  *   be one of the following:
  * - 0x0: Power OFF   
  * - !0x0: Power ON 
  */
uint32_t QSPI_GetPowerState(QSPI_TypeDef *QSPIptr)
{
  if (QSPIptr == QSPI0)
    return ((RCC->PRESETCTRL0 & (1 << PRESET_BIT_QSPI0)) && (RCC->AHBCLKCTRL0 & (1 << AHBCLK_BIT_QSPI0)));
  else
    return ((RCC->PRESETCTRL0 & (1 << PRESET_BIT_QSPI1)) && (RCC->AHBCLKCTRL0 & (1 << AHBCLK_BIT_QSPI1)));
}

/**
  * @brief  Enables or disables the QSPI interrupts.  
  * @param QSPIptr: the QUAD spi controller base address.
  * @param  QSPI_IT: specifies the SPI interrupt source to be enabled or disabled.
  *   This parameter can be one or a combination of the following values: 
  *     @arg QSPI_IT_RXOVEFLW:  Received FIFO overrun error interrupt 
  *     @arg QSPI_IT_RXTIMEOUT:  data not be read in time 
  *     @arg QSPI_IT_RXFIFOHF: Receive FIFO Half Full interrupt
  *     @arg QSPI_IT_TXFIFOHE: Transmit FIFO Half Empty interrupt
  *
  * @param  NewState: new state of the specified QSPI interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @note: once, only one kind of interrupts can be set.   
  * @retval None 
  */
void QSPI_ITConfig(QSPI_TypeDef *QSPIptr, uint32_t QSPI_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_QSPI_IT(QSPI_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the SPI interrupts */
    QSPIptr->CTRL1_CLR = QSPI_IT;
    QSPIptr->CTRL1_SET = QSPI_IT >> 1;
  }
  else
  {
    /* Disable the SPI interrupts */
    QSPIptr->CTRL1_CLR = QSPI_IT >> 1;
    QSPIptr->CTRL1_CLR = QSPI_IT;
  }
}

/**
  * @brief  Enables or disables QSPI DMA request and the DMA Command End signals asserting.  
  * @param QSPIptr: the QUAD spi controller base address.
  * @param  NewState: new state of the selected SPI DMA request.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void QSPI_DMACmd(QSPI_TypeDef *QSPIptr, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState == ENABLE)
    QSPIptr->CTRL1_SET = QSPI_CTRL1_DMA_ENABLE;
  else
    QSPIptr->CTRL1_CLR = QSPI_CTRL1_DMA_ENABLE;
}

/**
  * @brief  when transmission starts, assert the CS signal.
  * @param QSPIptr: the QUAD spi controller base address.
  * @retval None
  */
void QSPI_CS_Low(QSPI_TypeDef *QSPIptr)
{
  QSPIptr->CTRL0 |= QSPI_CTRL0_LOCK_CS;
}

/** 
  * @brief  After transmission, deassert the CS signal..
  * @param QSPIptr: the QUAD spi controller base address.
  * @retval None
  */
void QSPI_CS_High(QSPI_TypeDef *QSPIptr)
{
  QSPIptr->CTRL0 &= ~QSPI_CTRL0_LOCK_CS;
}

/**
  * @brief  Trigger the QSPI controller for data transfer according to the specified 
  *             parameters in the QSPI_DataInitStruct.
  * @param QSPIptr: the QUAD spi controller base address.
  * @param QSPI_DataInitStruct : pointer to a QSPI_DataInitTypeDef structure that
  *   contains the configuration information for the QSPI controller.
  * @retval None
  */
void QSPI_DataConfig(QSPI_TypeDef *QSPIptr, QSPI_DataInitTypeDef *QSPI_DataInitStruct)
{
  uint32_t tmepReg;
  int curTransferDir;

  /* Check the parameters */
  assert_param(IS_QSPI_Duplex(QSPI_DataInitStruct->QSPI_DUPLEX));
  assert_param(IS_QSPI_QSPI_Direction(QSPI_DataInitStruct->QSPI_TransferDir));

  if(QSPIptr->CTRL0 & 0x04000000)
  	curTransferDir = QSPI_Transfer_Read;
  else
  	curTransferDir = QSPI_Transfer_Write;

  QSPIptr->XFER = QSPI_DataInitStruct->QSPI_DataLength;
  if(curTransferDir == QSPI_DataInitStruct->QSPI_TransferDir){
	  if (QSPIptr->CTRL0 & QSPI_CTRL0_LOCK_CS)
	  {
	    tmepReg = 0x20000000|QSPI_DataInitStruct->QSPI_DUPLEX | QSPI_DataInitStruct->QSPI_TransferDir | QSPI_CTRL0_LOCK_CS;
	  }
	  else
	  {
	    tmepReg = 0x20000000|QSPI_DataInitStruct->QSPI_DUPLEX | QSPI_DataInitStruct->QSPI_TransferDir;
	  }
	  QSPIptr->CTRL0 = tmepReg;
  }else{
	  if (QSPIptr->CTRL0 & QSPI_CTRL0_LOCK_CS)
	  {
	    tmepReg = QSPI_DataInitStruct->QSPI_DUPLEX | QSPI_DataInitStruct->QSPI_TransferDir | QSPI_CTRL0_LOCK_CS;
	  }
	  else
	  {
	    tmepReg = QSPI_DataInitStruct->QSPI_DUPLEX | QSPI_DataInitStruct->QSPI_TransferDir;
	  }
	  QSPIptr->CTRL0 = tmepReg;
	  QSPIptr->CTRL0 |= 0x20000000;
  	}
}

/**
  * @brief  Read one data word from Rx FIFO.
  * @param QSPIptr: the QUAD spi controller base address.
  * @retval Data received
  */
uint32_t QSPI_ReadData(QSPI_TypeDef *QSPIptr)
{
  return QSPIptr->DATA;
}

/**
  * @brief  write CMD data word.
  * @param QSPIptr: the QUAD spi controller base address.
  * @param cmd: the CMD data word.  
  * @retval none.
  */
void QSPI_WriteCMD(QSPI_TypeDef *QSPIptr, uint32_t cmd)
{
  QSPIptr->CMD = cmd;
}

/**
  * @brief  Write one data word to Tx FIFO.
  * @param QSPIptr: the QUAD spi controller base address.
  * @param Data: data to be written.
  * @retval None
  */
void QSPI_WriteData(QSPI_TypeDef *QSPIptr, uint32_t Data)
{
  QSPIptr->DATA = Data;
}

/**
  * @brief  Set additional function under Quad Input / Output FAST_READ (EBh) mode
  * @param  QSPIx: the QUAD spi controller base address. 
  * @param  fun: additional function 
  * @param  NewState: ENABLE/DISABLE
  * @retval None
  */
void QSPI_EBmodeSet(QSPI_TypeDef* QSPIx,uint8_t fun, FunctionalState NewState)
{
  uint32_t temp = QSPIx->CTRL2;
  if(NewState == ENABLE){
    QSPIx->CTRL2 = (fun << 8) | 1;
  }else{
    QSPIx->CTRL2 = (fun << 8) | (temp & ~0x1);
  }
}

/**
  * @brief  Set QSPI First Bit mode MSB/LSB.
  * @param  QSPIptr: the QUAD spi controller base address.
  * @param  Qspi_FirstBit: specifies the flag to set MSB/LSB.
  *   This parameter can be one of the following values:
  *     @arg QSPI_FirstBit_MSB
  *     @arg QSPI_FirstBit_LSB
  * @retval None 
  */
void QSPI_FirstBitSet(QSPI_TypeDef *QSPIptr, uint32_t Qspi_FirstBit)
{
  assert_param(IS_QSPI_FIRST_BIT(Qspi_FirstBit));
  if(Qspi_FirstBit == QSPI_FirstBit_LSB){
    QSPIptr->CTRL1_SET = QSPI_FirstBit_LSB;
  }else{
    QSPIptr->CTRL1_CLR = QSPI_FirstBit_LSB;
  }
}

/**
  * @brief  Checks whether the specified QSPI flag is set or not.  
  * @param QSPIptr: the QUAD spi controller base address.
  * @param  QSPI_FLAG: specifies the flag to check. 
  *   This parameter can be one of the following values:
  *     @arg QSPI_STATUS_RXDAVL
  *     @arg QSPI_STATUS_TXDAVL
  *     @arg QSPI_STATUS_RECV_TIMEOUT_STAT
  *     @arg QSPI_STATUS_RECV_DATA_STAT
  *     @arg QSPI_STATUS_RECV_OVRFLW
  *     @arg QSPI_STATUS_RECV_FULL
  *     @arg QSPI_STATUS_RECV_NOT_EMPTY
  *     @arg QSPI_STATUS_XMIT_NOT_FULL
  *     @arg QSPI_STATUS_XMIT_EMPTY
  *     @arg QSPI_STATUS_XMIT_UNDRFLW
  *     @arg QSPI_STATUS_SPI_BUSY:  SPI controller busy       
  *
  * @note once, only one kind of FLAG can be checked.
  * @retval The new state of FlagStatus (SET or RESET).
  */
FlagStatus QSPI_GetFlagStatus(QSPI_TypeDef *QSPIptr, uint32_t QSPI_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_QSPI_STATUS_FLAG(QSPI_FLAG));

  if ((QSPIptr->STATUS & QSPI_FLAG) != (uint32_t)RESET)
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
  * @brief  Checks whether the specified QSPI interrupt has occurred or not.
  * @param QSPIptr: the QUAD spi controller base address.
  * @param  QSPI_IT: specifies the SPI interrupt source to check. 
  *     @arg QSPI_IT_RXOVEFLW
  *     @arg QSPI_IT_RXTIMEOUT
  *     @arg QSPI_IT_RXFIFOHF
  *     @arg QSPI_IT_TXFIFOHE
  * @retval The specified interrupt status state (SET or RESET).
  */
ITStatus QSPI_GetITStatus(QSPI_TypeDef *QSPIptr, uint32_t QSPI_IT)
{
  ITStatus bitstatus;

  /* Check the parameters */
  assert_param(IS_QSPI_GET_IT(QSPI_IT));

  if ((QSPIptr->CTRL1 & QSPI_IT) != (uint32_t)RESET)
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
  * @brief  Clears the QSPI's interrupt pending bits.  
  * @param QSPIptr: the QUAD spi controller base address.
  * @param  QSPI_IT: specifies the interrupt pending bit to clear. 
  *     @arg QSPI_IT_RXOVEFLW
  *     @arg QSPI_IT_RXTIMEOUT
  *     @arg QSPI_IT_RXFIFOHF
  *     @arg QSPI_IT_TXFIFOHE	 
  * @retval None
  */
void QSPI_ClearITPendingBit(QSPI_TypeDef *QSPIptr, uint32_t QSPI_IT)
{
  /* Check the parameters */
  assert_param(IS_QSPI_CLEAR_IT(QSPI_IT));

  QSPIptr->CTRL1_CLR = QSPI_IT;
}

/**
  * @brief  Configure delay time when QSPI capture data.
  * @param  QSPIptr: the QUAD spi controller base address.
  * @param  dly: specifies the delay time size. 
  *   This parameter can be one of the QSPICapDly enum values:
  *     @arg CAP_DLY_NONE: not delay
  *     @arg CAP_DLY_1CLK: delay 1 QSPI clock
  *     @arg CAP_DLY_2CLK: delay 2 QSPI clock
  *     @arg CAP_DLY_3CLK: delay 3 QSPI clock
  * @retval None. 
  */
void QSPI_SetCaptureDelay(QSPI_TypeDef *QSPIptr, QSPICapDly dly)
{
      QSPIptr->BUSY_DLY = (QSPIptr->BUSY_DLY & 0xfffffcff) | dly;//bit8&9
}

/**
  * @brief  Configure delay time after QSPI transmission ends,then pull-down busy.
  * @param  QSPIptr: the QUAD spi controller base address.
  * @param  dly: specifies the delay time size. 
  * @retval None. 
  */
void QSPI_SetBusyDelay(QSPI_TypeDef *QSPIptr, uint8_t dly)
{
      QSPIptr->BUSY_DLY = (QSPIptr->BUSY_DLY & 0xffffffe0) | dly;
}
//#define	_NOP_()		{__asm("nop");}
///**
//  * @brief  qspi no dma send data.
//  * @param  QSPIptr: the QUAD spi controller base address. 
//  * @param  data: pointer to the buffer containing the data to be written. 
//  * @param  num: write data length.
//  * @retval 0: ok, other: fail. 
//  */
//#define MAX_BUSY_WAIT 0x00100000
//int QSPI_SpiTX(QSPI_TypeDef *QSPIptr, uint8_t *data, uint32_t num)
//{
//	//num<=16
//	//FIFO is 4*32bit
//	uint16_t i, j;
//	volatile int waitnum = MAX_BUSY_WAIT;
//	QSPI_DataInitTypeDef QSPI_DataInitStruct;

//	for (i = 0; i < num / 4; i++)
//	{
//		QSPI_DataInitStruct.QSPI_DataLength = 4;
//		QSPI_DataInitStruct.QSPI_DUPLEX = QSPI_HalfDuplex;
//		QSPI_DataInitStruct.QSPI_TransferDir = QSPI_Transfer_Write;
//		QSPI_DataConfig(QSPIptr, &QSPI_DataInitStruct);
//		QSPIptr->DATA = *((uint32_t *)data + i);

//		waitnum = MAX_BUSY_WAIT;
//		while ((QSPI_GetFlagStatus(QSPIptr, QSPI_STATUS_XMIT_EMPTY) == RESET) && (waitnum--))
//			_NOP_();
//		if (waitnum < 0)
//		{
//			printf("spi tx is not empty timeout\r\n");
//			return -1;
//		}

//		waitnum = MAX_BUSY_WAIT;
//		while ((QSPI_GetFlagStatus(QSPIptr, QSPI_STATUS_SPI_BUSY) == SET) && (waitnum--))
//			_NOP_();
//		if (waitnum < 0)
//		{
//			printf("spi tx is busy timeout\r\n");
//			return -1;
//		}
//	}

//	num %= 4;
//	if(num){
//		uint8_t* pData = (uint8_t*)((uint32_t)QSPIptr+0x40);

//		QSPI_DataInitStruct.QSPI_DataLength = num;
//		QSPI_DataInitStruct.QSPI_DUPLEX = QSPI_HalfDuplex;
//		QSPI_DataInitStruct.QSPI_TransferDir = QSPI_Transfer_Write;
//		QSPI_DataConfig(QSPIptr, &QSPI_DataInitStruct);
//		for(j=0;j<num;j++){
//			*pData = data[i*4+j];
//		}
//		waitnum = MAX_BUSY_WAIT;
//		while ((QSPI_GetFlagStatus(QSPIptr, QSPI_STATUS_XMIT_EMPTY) == RESET) && (waitnum--))
//			_NOP_();
//		if (waitnum < 0)
//		{
//			printf("spi tx is not empty timeout\r\n");
//			return -1;
//		}

//		waitnum = MAX_BUSY_WAIT;
//		while ((QSPI_GetFlagStatus(QSPIptr, QSPI_STATUS_SPI_BUSY) == SET) && (waitnum--))
//			_NOP_();
//		if (waitnum < 0)
//		{
//			printf("spi tx is busy timeout\r\n");
//			return -1;
//		}
//	}
//	return 0;
//}

///**
//  * @brief  qspi no dma receive data
//  * @param  QSPIptr: the QUAD spi controller base address. 
//  * @param  data: pointer to the buffer containing the data to be read. 
//  * @param  num: read data length. 
//  * @retval 0: ok, other: fail. 
//  */
//int QSPI_SpiRX(QSPI_TypeDef* QSPIptr,uint8_t *data,uint32_t num)
//{
//	uint16_t i;
//	uint32_t temp32;
//	int waitnum = MAX_BUSY_WAIT;
//	QSPI_DataInitTypeDef QSPI_DataInitStruct;

//	for(i=0; i<num/4; i++) {
//		QSPI_DataInitStruct.QSPI_DataLength = 4;
//		QSPI_DataInitStruct.QSPI_DUPLEX = QSPI_HalfDuplex;
//		QSPI_DataInitStruct.QSPI_TransferDir = QSPI_Transfer_Read;
//		QSPI_DataConfig(QSPIptr, &QSPI_DataInitStruct);

//		waitnum = MAX_BUSY_WAIT;
//		while ((QSPI_GetFlagStatus(QSPIptr, QSPI_STATUS_SPI_BUSY) == SET) && (waitnum--))
//			_NOP_();
//		if (waitnum < 0)
//		{
//			printf("spi rx is busy timeout\r\n");
//			return -1;
//		}

//		*((uint32_t *)data + i) = QSPIptr->DATA;
//	}

//	num %= 4;
//	if(num) {
//		QSPI_DataInitStruct.QSPI_DataLength = num;
//		QSPI_DataInitStruct.QSPI_DUPLEX = QSPI_HalfDuplex;
//		QSPI_DataInitStruct.QSPI_TransferDir = QSPI_Transfer_Read;
//		QSPI_DataConfig(QSPIptr, &QSPI_DataInitStruct);

//		waitnum = MAX_BUSY_WAIT;
//		while ((QSPI_GetFlagStatus(QSPIptr, QSPI_STATUS_SPI_BUSY) == SET) && (waitnum--))
//			_NOP_();
//		if (waitnum < 0)
//		{
//			printf("spi rx is busy timeout\r\n");
//			return -1;
//		}

//		temp32 = QSPIptr->DATA;
//		data[i*4] = temp32 & 0xff;
//		if(num>1){
//			data[i*4 + 1] = (temp32 >> 8) & 0xff;
//		}
//		if(num>2){
//			data[i*4 + 2] = (temp32 >> 16) & 0xff;
//		}
//	}
//    return 0;
//}
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2013 TDO *****END OF FILE****/
