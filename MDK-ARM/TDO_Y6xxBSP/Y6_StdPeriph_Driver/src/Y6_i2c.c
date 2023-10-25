 /**
  ******************************************************************************
  * @file    m1130_i2c.c
  * @author  Alpscale Application Team
  * @version V1.0.0
  * @date    19-December-2013
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Inter-integrated circuit (I2C)
  *           - Initialization and Configuration
  *           - Data transfers
  *           - Interrupts, events and flags management        
  *  
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, ALPHASCALE SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2013 Alpscale</center></h2>
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "Y6_i2c.h"
#include "Y6_rcc.h"

/** @addtogroup Y6_StdPeriph_Driver
  * @{
  */

/** @defgroup I2C 
  * @brief I2C driver modules
  * @{
  */ 


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup I2C_Private_Functions
  * @{
  */

/** @defgroup I2C_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim   
 ===============================================================================
                   Initialization and Configuration functions
 ===============================================================================  

@endverbatim
  * @{
  */


#define NUM_SPEEDS    2
/*CNT registers values when ic_clk = 12Mhz*/
const uint16_t HCNT[NUM_SPEEDS] = {
   0x34,  0x6 	
};
const uint16_t LCNT[NUM_SPEEDS] = {
   0x3b,  0xf 
};



/**
  * @brief  Deinitialize the I2Cx peripheral registers to their default reset values.
  * @param  I2Cx: the target I2C peripheral.
  * @retval None
  */
void I2C_Reset(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  if(I2Cx == I2C0) {
    RCC_ResetAHBCLK(1 << PRESET_BIT_I2C0);
  }
}

/**
  * @brief  Initializes the I2Cx peripheral according to the specified 
  *         parameters in the I2C_InitStruct.          
  * @param  I2Cx: the target I2C peripheral.
  * @param  I2C_InitStruct: pointer to a I2C_InitTypeDef structure that contains 
  *         the configuration information for the specified I2C peripheral.
  * @retval 0, okay; else, fail.
  */
int I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct)
{
  uint32_t regValue = 0;
  int sourceclock;
  uint16_t hcnt,lcnt;
  int SPEEDMODE;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_CLOCK_SPEED(I2C_InitStruct->I2C_ClockSpeed));
  assert_param(IS_I2C_BITADDR_SLAVE(I2C_InitStruct->I2C_10BITADDR_SLAVE));  
  assert_param(IS_I2C_BITADDR_MASTER(I2C_InitStruct->I2C_10BITADDR_MASTER));  
  assert_param(IS_I2C_RESTART_CHECK(I2C_InitStruct->I2C_RESTART_EN));  


  I2C_Cmd(I2Cx, DISABLE, (I2C_InitStruct->I2C_ClockSpeed == I2C_Speedmode_Stand)?0:1);
  I2C_ITConfig(I2Cx, I2C_IT_ALL, DISABLE );
  I2C_ClearITPendingBit(I2Cx);
  I2C_ClearRawITPendingBit(I2Cx, I2C_RAW_IT_BIT_ALL);
  I2C_Clear_TX_ABRT_SOURCE(I2Cx, TX_ABRT_SOURCE_BIT_ALL);

  regValue = I2C_InitStruct->I2C_ClockSpeed|I2C_InitStruct->I2C_10BITADDR_SLAVE|I2C_InitStruct->I2C_10BITADDR_MASTER|I2C_InitStruct->I2C_RESTART_EN;
  I2Cx->CON = regValue;

  /* set I2C mode */
  if (I2C_InitStruct->I2C_Mode == I2C_MASTER_MODE)
  {
    I2Cx->CON |= (1 | (1 << 6));
  }else{
    I2Cx->CON &= ~(1 | (1 << 6));
  }

  I2C_SetOwnAddress(I2Cx, I2C_InitStruct->I2C_OwnAddress);
  SPEEDMODE = (I2C_InitStruct->I2C_ClockSpeed == I2C_Speedmode_Stand) ? 0 : 1;
  sourceclock = RCC_GetClocksFreq(RCC_CLOCKFREQ_SYSAHBCLK)/1000;

  if(sourceclock >= 12000)
  {
    hcnt = (uint16_t)(((int)HCNT[SPEEDMODE]+8)*(sourceclock/12000)-8);
    lcnt = (uint16_t)(((int)LCNT[SPEEDMODE]+1)*(sourceclock/12000)-1);
  }
  else
  {
    if(SPEEDMODE == 1)
    SPEEDMODE = 0;	  //according to DW_apb_i2c databook, when ic_clk <= 6Mhz, it's impossible to set 400kHz

    if( (sourceclock==6000)||(sourceclock==4000)||(sourceclock==3000) )
    {
      hcnt =  (uint16_t)(((int)HCNT[SPEEDMODE]+8)/(12000/sourceclock)-8);
      lcnt =  (uint16_t)(((int)LCNT[SPEEDMODE]+1)/(12000/sourceclock)-1);
    }
    else
    {
      return -1;  //according to DW_apb_i2c databook, when ic_clk <= 2Mhz, it's impossible to set even 100kHz
    }
  } 
  if(SPEEDMODE==0)
  {
    I2Cx->SS_SCL_HCNT = hcnt;
    I2Cx->SS_SCL_LCNT = lcnt;
  }else{
    I2Cx->FS_SCL_HCNT = hcnt;
    I2Cx->FS_SCL_LCNT = lcnt;
  }


  /* Set tranmit & receive FIFO threshold to zero */
  I2Cx->RX_TL = 0;
  I2Cx->TX_TL = 0;
  
  /*target device addressing initial setting*/
  I2Cx->TAR = 0;

  return 0;
  /*Don't enable I2C controller right now*/	  
  
}


/**
  * @brief  Controls whether the DW_apb_i2c is enabled.
  * @param  I2Cx: the target I2C peripheral.
  * @param  NewState: new state of the I2Cx peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
  * @param  SpeedMode: 0, standard; 1, fast.
  * @retval 0, ok; else, fail.
  */
int I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState, int SpeedMode)
{
  int i,n;
  int count = 0;
  int err=0;
  static const int delay[NUM_SPEEDS] = {1000, 250};  //according to data book, the delay time interval needed in us unit for each disabling try


  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param( (SpeedMode==0)||(SpeedMode==1) );
  
  if (NewState != ENABLE)
  {
    /* Disable the DW_apb_i2c */
    I2Cx->ENABLE = (uint32_t)((uint16_t)0);

    while( (I2C_ReadRegister(I2Cx, I2C_Register_ENABLE_STATUS)&I2C_IC_ENABLE_STATUS_IC_EN)||(I2C_ReadRegister(I2Cx, I2C_Register_STAT)&I2C_IC_STATUS_ACTIVITY) )	
    {
        for(i=delay[SpeedMode]; i>0; i--)
      {	 
      /*Dummy 1-us delay*/
        for(n=100; n>0; n--)
        {
        ;
        }	 
      }
      I2Cx->ENABLE = (uint32_t)((uint32_t)0);
      if (count++ > 10)
      {
        err = -1;
        break;
      }   
    }

    return err;	
  }
  else
  {
    /* Enable the DW_apb_i2c */
    I2Cx->ENABLE = (uint16_t)((uint16_t)1);
    return 0;
  }
}



/**
  * @brief  Configures the Target Address Register special function.
  * @param  I2Cx: the target I2C peripheral.
  * @param  SPECIAL_DOMAIN_SET: specifies IC_TAR SPECIAL domain whether set.
  * @param  GC_START_DOMAIN_SET: specifies IC_TAR GC_OR_START domain whether set.
  * @retval None.
  */
void I2C_ConfigureTARSpecial(I2C_TypeDef* I2Cx, uint32_t SPECIAL_DOMAIN_SET, uint32_t GC_START_DOMAIN_SET)
{
  uint32_t TempRegVal;
  
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_SPECIAL_DOMAIN(SPECIAL_DOMAIN_SET));
  assert_param(IS_GC_START_DOMAIN(GC_START_DOMAIN_SET));

  TempRegVal = I2Cx->TAR;
  
  TempRegVal &= (uint32_t)(~(I2C_TAR_IC_SPECIAL|I2C_TAR_GC_OR_START));

  TempRegVal |= SPECIAL_DOMAIN_SET|GC_START_DOMAIN_SET;

  I2Cx->TAR = TempRegVal;
}


/**
  * @brief  Target Address Register when as a master.
  * @param  I2Cx: the target I2C peripheral.
  * @param  Address: specifies the slave address which will be transmitted
  *
  * @retval None.
  */
void I2C_SendSlavAddress(I2C_TypeDef* I2Cx, uint8_t Address)
{
  uint32_t tempReg;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  tempReg = I2Cx->TAR;

  tempReg = tempReg&((uint32_t)(~I2C_TAR_IC_TAR0_9));
  
  I2Cx->TAR = tempReg|Address;
}


/**
  * @brief  Configures I2C master own address .
  * @param  I2Cx: the target I2C peripheral.
  * @param  Address: specifies I2C master own address.
  * @retval None.
  */
void I2C_SetOwnAddress(I2C_TypeDef* I2Cx, uint8_t Address)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
 
  /* Store the new register value */
  I2Cx->SAR = Address;
}



/**
  * @}
  */

/** @defgroup I2C_Group2 Data transfers functions
 *  @brief   Data transfers functions 
 *
@verbatim   
 ===============================================================================
                        Data transfers functions
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Sends a data byte through the I2Cx peripheral.
  * @param  I2Cx: the target I2C peripheral.
  * @param  Data: Byte to be transmitted..
  * @retval None
  */
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  
  /* Write in the DR register the data to be sent */
  I2Cx->DATA_CMD = (uint32_t)Data;
}


/**
  * @brief  Trigger data receiving when as master.
  * @param  I2Cx: the target I2C peripheral.
  * @retval None.
  */
void I2C_TriggerRecData(I2C_TypeDef* I2Cx)
{
  I2Cx->DATA_CMD = (uint32_t)(1<<8);
}


/**
  * @brief  Returns the most recent received data by the I2Cx peripheral.
  * @param  I2Cx: the target I2C peripheral.
  * @retval The value of the received data.
  */
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  
  /* Return the data in the IC_DATA_CMD register */
  return (uint8_t)(I2Cx->DATA_CMD&0xff);
}

/**
  * @}
  */


/** @defgroup I2C_Group3 Interrupts events and flags management functions
 *  @brief   Interrupts, events and flags management functions
 *
@verbatim   
 ===============================================================================
                Interrupts, events and flags management functions
 ===============================================================================  
  This section provides functions allowing to configure the I2C Interrupts 
  sources and check or clear the flags or pending bits status.
  The user should identify which mode will be used in his application to manage 
  the communication: Polling mode, Interrupt mode.    
  
@endverbatim
  * @{
  */


/**
  * @brief  Reads the specified I2C register and returns its value.
  * @param  I2Cx: the target I2C peripheral.  
  * @param  I2C_Register: specifies the register to read.
  *          This parameter can be one of the following values:
  *            @arg I2C_Register_CON:  I2C Control Register.
  *            @arg I2C_Register_TAR:   I2C Target Address Register.
  *            ......
  *            @arg I2C_Register_ENABLE_STATUS: I2C Enable Status Register
  * @retval The value of the read register.
  */
uint32_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint8_t I2C_Register)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_REGISTER(I2C_Register));
 
  tmp = (uint32_t) I2Cx;
  tmp += I2C_Register;

  /* Return the selected register value */
  return (*(__IO uint32_t *) tmp);
}



/**
  * @brief  Enables or disables the specified I2C interrupts.
  * @param  I2Cx: the target I2C peripheral.
  * @param  I2C_IT: specifies the I2C interrupts sources to be enabled or disabled. 
  *          This parameter can be any combination of the following values:
  *            @arg I2C_IT_RX_UNDER: Set if the processor attempts to read the receive buffer when it is empty by reading from the IC_DATA_CMD register.
  *            @arg I2C_IT_RX_OVER: Set if the receive buffer is completely filled to IC_RX_BUFFER_DEPTH and an additional byte is received from an external I2C device.
  *		......
  *            @arg I2C_IT_GEN_CALL: Set only when a General Call address is received and it is acknowledged.
  * @param  NewState: new state of the specified I2C interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_ITConfig(I2C_TypeDef* I2Cx, uint16_t I2C_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_I2C_CONFIG_IT(I2C_IT));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C interrupts */
    I2Cx->INTR_MASK |= I2C_IT;
  }
  else
  {
    /* Disable the selected I2C interrupts */
    I2Cx->INTR_MASK &= (uint16_t)~I2C_IT;
  }
}

/*
 ===============================================================================
                          Basic state monitoring                    
 ===============================================================================  
 */

/**
  * @brief	Checks whether the specified I2C flag is set or not.
  * @param	I2Cx: the target I2C peripheral.
  * 
  * @retval the register value of IC_STATUS
  */
uint8_t I2C_GetFlagStatus(I2C_TypeDef* I2Cx)
{
	return (uint8_t)(I2Cx->STAT&0x7f);
}


/**
  * @brief  Checks whether the specified single I2C flag is set or not.
  * @param  I2Cx: the target I2C peripheral.
  * @param  Status: I2C Status Register value.
  * @param  I2C_FLAG: specifies the flag to check. 
  *          This parameter can be one of the following values:
  *            @arg I2C_IC_STATUS_ACTIVITY: I2C Activity Status
  *            @arg I2C_IC_STATUS_TFNF: SMBus host header (Slave mode)
  *            @arg I2C_IC_STATUS_TFE: SMBus default header (Slave mode)
  *            @arg I2C_IC_STATUS_RFNE: General call header flag (Slave mode)
  *            @arg I2C_IC_STATUS_RFF: Transmitter/Receiver flag
  *            @arg I2C_IC_STATUS_MST_ACTIVITY: Bus busy flag
  *            @arg I2C_IC_STATUS_SLV_ACTIVITY: Master/Slave flag
  * @retval The new state of I2C_FLAG (SET or RESET).
  */
FlagStatus I2C_CheckFlagStatus(I2C_TypeDef* I2Cx, uint8_t Status, uint32_t I2C_FLAG)
{
  FlagStatus bitstatus = RESET;
  __IO uint32_t i2creg = 0, i2cxbase = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_GET_FLAG(I2C_FLAG));
  
  if( (((uint32_t)Status) & I2C_FLAG) != (uint32_t)RESET)
  {
    /* I2C_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* I2C_FLAG is reset */
    bitstatus = RESET;
  }
  
  /* Return the I2C_FLAG status */
  return  bitstatus;
}


/**
  * @brief  Get the I2Cx's Interrupt Status Register.
  * @param  I2Cx: the target I2C peripheral.
  *  
  * @retval Interrupt Status value.
  */
uint32_t I2C_GetITFlag(I2C_TypeDef* I2Cx)
{
  uint32_t FlagValue = 0;
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  
  FlagValue = I2Cx->INTR_STAT;  

  return (FlagValue&0xfff);
}



/**
  * @brief  Get the I2Cx's Raw Interrupt Status Register.
  * @param  I2Cx: the target I2C peripheral.
  *  
  * @retval Raw Interrupt Status value.
  */
uint32_t I2C_GetRawITFlag(I2C_TypeDef* I2Cx)
{
  uint32_t FlagValue = 0;
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  
  FlagValue = I2Cx->RAW_INTR_STAT;
  
  return (FlagValue&0xfff);
}


/**
  * @brief  Checks whether the specified I2C interrupt has occurred or not.
  * @param  I2Cx: the target I2C peripheral.
  * @param  I2C_IT_FLAG: specifies the interrupt flag to check. 
  * @param  I2c_IT_BIT: specifies which INT bit to check.  
  *          This parameter can be one of the following values:
  *            @arg R_RX_UNDER: read the receive buffer when it is empty by reading from the IC_DATA_CMD register.
  *            @arg RX_OVER: buffer is completely filled to IC_RX_BUFFER_DEPTH and an additional byte is received from an external I2C device.
  *            ......
  *            @arg GEN_CALL: General Call address is received and it is acknowledged.
  * @retval The new state of I2C_IT (SET or RESET).
  */
ITStatus I2C_CheckITFlag(I2C_TypeDef* I2Cx, uint32_t I2C_IT_FLAG, uint32_t I2C_IT_BIT)
{
  ITStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_IT_BIT(I2C_IT_BIT));


  /* Check the status of the specified I2C flag */
  if ( (I2C_IT_FLAG & I2C_IT_BIT) != (uint32_t)RESET )
  {
    /* I2C_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* I2C_IT is reset */
    bitstatus = RESET;
  }
  
  /* Return the I2C_IT status */
  return  bitstatus;
}



/**
  * @brief  Clear Combined and Individual Interrupt Register.
  * @param  I2Cx: the target I2C peripheral.
  *
  * @retval None
  */
void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx)
{
  volatile uint32_t RegValue = 0;
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  /* Read this register to clear the combined interrupt, all individual interrupts, and the IC_TX_ABRT_SOURCE register. */
  RegValue = I2Cx->CLR_INTR;
  
  RegValue++;
}


/**
  * @brief  Clear specified IC_RAW_INTR_STAT register bit.
  * @param  I2Cx: the target I2C peripheral.
  * @param  I2C_RAW_IT_BIT: Specified bit to clear.
  *
  * @retval None
  */
void I2C_ClearRawITPendingBit(I2C_TypeDef* I2Cx, uint32_t I2C_RAW_IT_BIT)
{
  volatile uint32_t RegValue = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_RAW_IT_BIT(I2C_RAW_IT_BIT));

  if(I2C_RAW_IT_BIT&I2C_IC_RAW_INTR_STAT_RX_UNDER)
  {
    RegValue = I2Cx->CLR_RX_UNDER;
  }

  if(I2C_RAW_IT_BIT&I2C_IC_RAW_INTR_STAT_RX_OVER)
  {
    RegValue = I2Cx->CLR_RX_OVER;
  }

  if(I2C_RAW_IT_BIT&I2C_IC_RAW_INTR_STAT_TX_OVER)
  {
    RegValue = I2Cx->CLR_TX_OVER;
  }

  if(I2C_RAW_IT_BIT&I2C_IC_RAW_INTR_STAT_RD_REQ)
  {
    RegValue = I2Cx->CLR_RD_REQ;
  }

  if(I2C_RAW_IT_BIT&I2C_IC_RAW_INTR_STAT_TX_ABRT)
  {
    RegValue = I2Cx->CLR_TX_ABRT;
  }

  if(I2C_RAW_IT_BIT&I2C_IC_RAW_INTR_STAT_RX_DONE)
  {
    RegValue = I2Cx->CLR_RX_DONE;
  }

  if(I2C_RAW_IT_BIT&I2C_IC_RAW_INTR_STAT_ACTIVITY)
  {
    RegValue = I2Cx->CLR_ACTIVITY;
  }

  if(I2C_RAW_IT_BIT&I2C_IC_RAW_INTR_STAT_STOP_DET)
  {
    RegValue = I2Cx->CLR_STOP_DET;
  }

  if(I2C_RAW_IT_BIT&I2C_IC_RAW_INTR_STAT_START_DET)
  {
    RegValue = I2Cx->CLR_START_DET;
  }

  if(I2C_RAW_IT_BIT&I2C_IC_RAW_INTR_STAT_GEN_CALL)
  {
    RegValue = I2Cx->CLR_GEN_CALL;
  }

  RegValue++;
}


/**
  * @brief  Clear specified IC_TX_ABRT_SOURCE register bit.
  * @param  I2Cx: the target I2C peripheral.
  * @param  I2C_TX_ABRT_SOURCE_BIT: Specified bit to clear.
  *
  * @retval None
  */
void I2C_Clear_TX_ABRT_SOURCE(I2C_TypeDef* I2Cx, uint32_t I2C_TX_ABRT_SOURCE_BIT)
{
  volatile uint32_t RegValue = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx)); 
  assert_param(IS_TX_ABRT_SOURCE_BIT(I2C_TX_ABRT_SOURCE_BIT));

  /*speical treatment for bit9*/
  if(I2C_TX_ABRT_SOURCE_BIT&I2C_IC_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT)
  {
    RegValue = I2Cx->TX_ABRT_SOURCE;
    I2Cx->TX_ABRT_SOURCE = RegValue&(~(1<<9));
    RegValue = I2Cx->CON;
    I2Cx->CON = RegValue|(1<<5);
    RegValue = I2Cx->TAR;
    I2Cx->TAR = RegValue&(~(1<<11));
  }

  RegValue = I2Cx->CLR_TX_ABRT;
  RegValue++;
}

/**
  * @}
  */ 

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
