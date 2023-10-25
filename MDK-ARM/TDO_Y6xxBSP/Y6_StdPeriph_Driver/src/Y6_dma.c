

/* Includes ------------------------------------------------------------------*/
#include "Y6_dma.h"
#include "Y6_rcc.h"
#include "stdlib.h"
#include "string.h"


/** @addtogroup Y6_StdPeriph_Driver
  * @{
  */

/** @defgroup DMA 
  * @brief DMA driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MAX_RBB_WAIT				(0x1000000)

/* Masks Definition */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/** @defgroup DMA_Private_Functions
  * @{
  */

/** @defgroup DMA_Group1 Initialization and package allocation functions
 *  @brief   Initialization and Reservation functions
 *
@verbatim   
 ===============================================================================
                 Initialization and Reservation functions
 ===============================================================================  

  This subsection provides functions allowing to initialize the DMA controller and allocate the
  resources for DMA transferring.
  
@endverbatim
  * @{
  */


uint8_t ChannelUsedMask = 0;
DmaHandler DmaHandlerGroup[4] = {NULL, NULL, NULL, NULL};


/**
  *  @brief  DmaRequestChannel - request dma channel
  *  @param  handler: the handler will be executed when enabled dma channel interrupt
  *                   if nothing to do, set NULL
  *  @retval  0~3, channel ID; else, error
  */
DMAchannel DmaRequestChannel(DmaHandler handler)
{
  int channel;
  //add "enter critical" code here
  for (channel = 0; channel < DMAChannelNum; channel++)
  {
    if (ChannelUsedMask & (1 << channel))
      continue;
    if (DMA->ChEnReg & (1 << channel))
    {
      ChannelUsedMask |= 1 << channel;
      continue;
    }
    
    break;
  }
  
  if (channel < DMAChannelNum)
    DmaHandlerGroup[channel] = handler;
  ChannelUsedMask |= 1 << channel;
  //add "exit critical" code here
  return (DMAchannel)channel;
}

/**
  *  @brief  DmaFreeChannel - free dma channel
  *  @param  channel: free which channel
  *  @retval  0~3, channel ID; else, error
  */
void DmaFreeChannel(DMAchannel channel)
{
  ChannelUsedMask &= ~(1 << channel);
//	if (DMA->ChEnReg & (1 << channel)){
//		DMA->ChEnReg|=(1<<(8+channel));
//		DMA->ChEnReg&=~(1 << channel);
//		DMA->ChEnReg&=~(1<<(8+channel));
//	}
	DmaStop(channel);
  DmaHandlerGroup[channel] = NULL;
}



/**
  *  @brief  DmaInit - init the desired DMA channel.
  *  @param  channel: which channel of the chosen module to be used.
  *
  *  @note  If the channel is being used, we just return, and may retry for another one.
  *
  *  @retval  0, okay; else, error.
  */   
int DmaInit(DMAchannel channel)
{  
  assert_param(IS_DMA_CHANNEL(channel));

  if( DmaIsBusy(channel)==CHANNEL_BUSY ) 
    return -1;

  RCC_ResetAHBCLK(1<<AHBCLK_BIT_DMA);

  DMA->DmaCfgReg = 1;

  if ( DmaStop(channel) )
    return -1;
  else
    return 0;	
}


/**
  * @}
  */



/** @defgroup DMA_Group2 Transferring control functions
 *  @brief   Data Counter functions 
 *
@verbatim   
 ===============================================================================
                            Transferring Control functions
 ===============================================================================  

  This subsection provides function allowing to configure and control the DMA transfer.

@endverbatim
  * @{
  */

/**
  *  @brief   _WaitDmaSemaphore - wait for a dma channel to be idle. Like not ready before start   
  *              and timeout for finish.
  *  @param  dma_channel: which channel of the chosen module to be used.
  *
  *  @note: For data service finish verification check, user may need to check the busy bit of the function controller, 
  *              which requests DMA service, even when _WaitDmaSemaphore finishes; 
  *
  *  @retval  0, okay; -1, error;
  */
static int _WaitDmaSemaphore(DMAchannel channel)
{
  int wait_dma = MAX_RBB_WAIT;

  assert_param(IS_DMA_CHANNEL(channel));

  while( DmaIsBusy(channel)==CHANNEL_BUSY )
  {
    if(!(wait_dma--))
    {
      return -1;
    }
  }

  return 0; 		
}



/**
  *  @brief  DmaStop - disable a dma channel, and clear the corresponding interrupt enable bits and interrupt status bits.
  *  @param  channel: which channel  to be used.
  *
  *  @retval  value: 0, channel is disabled properly. -1, error of timeout.
  */
int DmaStop(DMAchannel channel)
{     
  int i;
  int wait_time = MAX_RBB_WAIT;
  assert_param(IS_DMA_CHANNEL(channel));
  DMA->ChEnReg = (1<<channel)<<8;
  /*disable all interrupts*/
  for(i=0; i<5; i++)
  {
      DmaChannelInterrupt(channel, 0);
  }
  /*clear all interrupt status*/
  for(i=0; i<5; i++)
  {
      DmaChannelClearInterruptStatus(channel);
  }
  /*according to the data book, we must poll the corresponding ChEnReg.CH_EN bit*/
  while( DmaIsBusy(channel)==CHANNEL_BUSY )
  {
    if(!(wait_time--))
    {
    return -1;
    }
  }

	return 0;
}


/**
 *  @brief  DmaChannelCFGset - set DMA channel's Channel ConfigurationRegister(CFG)
 *  @param  dma_channel: which channel of the chosen module to be used.
 *  @param  lowregval: CFG's low 32-bit setting.
 *  @param  highregval: CFG's high 32-bit setting.
 * 
 *  @note  This must be called before DMA-start(DmaStartRoutine).
 *
 *  @retval  None.
 */
void DmaChannelCFGset(DMAchannel channel, uint32_t lowregval, uint32_t highregval)
{
  assert_param(IS_DMA_CHANNEL(channel));

  *(uint32_t *)((uint32_t)(&(DMA->CFG0_L))+0x58*channel) = lowregval;	 
  *(uint32_t *)((uint32_t)(&(DMA->CFG0_H))+0x58*channel) = highregval;
}


/**
  *  @brief  DmaStart - start DMA transmission.  
  *  @param  dma_channel: which channel of the chosen module to be used.
  *  @retval  None.
  */
static void DmaStart(DMAchannel channel)
{	
  assert_param(IS_DMA_CHANNEL(channel));

  DMA->DmaCfgReg = 0x01;	
  DMA->ChEnReg = ((1<<channel)<<8)+(1<<channel);

	return ;
}


/**
  *  @brief  DmaStartRoutine - do preparation for dma start. 
  *  @param  channel: which channel of the chosen module to be used.
  *  @param  bWaitSemaAfter: wait until this LLI finish? 0, no; !0, yes.
  *
  *  @note
  * 1. user must already set Channel Configuration Register(CFG) 
  * properly before calling this function. 
  *  
  * 2. user must ensure that the DmaPkg->SAR and DmaPkg->DAR are
  * aligned to the setting of CTRL->SRC_TR_WIDTH and 
  * CTRL->DST_TR_WIDTH, we just ignore it here for avoiding the 
  * unnecessary complexity. 
  *   For more, see DesignWare DW_ahb_dmac Databook.
  *
  *  @retval  0, okay; else, error.   
  */
int DmaStartRoutine(DMAchannel channel, int bWaitSemaAfter)
{
  int ret = 0;

  assert_param(IS_DMA_CHANNEL(channel));

  if( DmaIsBusy(channel)!=CHANNEL_BUSY )
  {
      ret = CHANNEL_IDLE;
      DmaStart(channel);        
  }
  else
  {
      ret = CHANNEL_BUSY;
  }

  if(ret!=CHANNEL_IDLE)
  {
      return -1;
  }

  if( !bWaitSemaAfter )
  {
    return 0;
  }
  else
  {	
    return _WaitDmaSemaphore(channel);
  }
}


/**
  * @}
  */



/** @defgroup DMA_Group3 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions 
 *
@verbatim   
 ===============================================================================
                  Interrupts and flags management functions
 ===============================================================================  

  This subsection provides functions allowing to
   - Check the DMA channel busy status
   - Configure the DMA Interrupts sources and check or clear the flags or pending bits status.   
@endverbatim
  * @{
  */

/**
  *  @brief  DmaIsBusy - check whether one channel is reday for use.
  *  @param  channel: which channel of the chosen module to be used.
  *
  *  @retval  The DMA target channel state.
  */
ChannelState DmaIsBusy(DMAchannel channel)
{
  assert_param(IS_DMA_CHANNEL(channel));

  if((DMA->ChEnReg) & (1 << channel))
    return CHANNEL_BUSY;
  else
    return CHANNEL_IDLE;
}


/**
   *  @brief  DmaChannelInterrupt - disable or enable a kind of interrupt for one channel.
   *  @param  channel: which channel to be used.
   *  @param  inttype: the desired interrupt
   *  @param  funswitch: disable or enable. 0, disable; 1, enable.
   *
   *  @retval None
   */
void DmaChannelInterrupt(DMAchannel channel, int funswitch )
{
  assert_param(IS_DMA_CHANNEL(channel));

  if( funswitch!=0 )
  {			
    *(uint32_t *)((uint32_t)(&DMA->MaskTfr)) = ((1<<channel)<<8)+(1<<channel);
  }
  else
  {
    *(uint32_t *)((uint32_t)(&DMA->MaskTfr)) = (1<<channel)<<8;
  }
}

/**
  *  @brief  DmaChannelInterruptStatusBit - read Interrupt Raw Status Registers or Interrupt Status Registers of
  *              one dma channel for the targeted interrupt status type.
  *  @param  channel: which channel of the chosen module to be used.
  *  @param  inttype  the desired interrupt status type.
  *  @param  statustype: 0, raw; 1, masked. 
  *
  *  return value: 0, interrupt status bit not set; !0, interrupt status bit is set.
  */
int DmaChannelInterruptStatusBit(DMAchannel channel, int statustype )
{
  int retval;

  assert_param(IS_DMA_CHANNEL(channel));

  if(statustype == 0) //raw interrupt status type
  {
    retval = *(uint32_t *)((uint32_t)(&DMA->RawTfr))&(1<<channel);
  }
  else //masked 
  {
    retval = *(uint32_t *)((uint32_t)(&DMA->StatusTfr))&(1<<channel);
  }


  return retval;
}


/**
  *  @brief  DmaChannelClearInterruptStatus - clear the corresponding bit in the chosen interrupt type's  
  *              interrupt Raw Status and interrupt Status registers of one dma channel.
  *  @param  channel: which channel to be used.
  *  @param  inttype: the desired interrupt status type.
  *
  *  @retval None.
  */
void DmaChannelClearInterruptStatus(DMAchannel channel)
{		
  assert_param(IS_DMA_CHANNEL(channel));
  
  *((uint32_t *)( (uint32_t)(&DMA->ClearTfr))) = (uint32_t)(1<<channel);
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

void DMA_IRQHandler(void)
{
  if (DmaChannelInterruptStatusBit(DMA_CHANNEL_0, 1))
  {
    if (DmaHandlerGroup[0]) DmaHandlerGroup[0]();
    DmaChannelClearInterruptStatus(DMA_CHANNEL_0);
  }
  if (DmaChannelInterruptStatusBit(DMA_CHANNEL_1, 1))
  {
    if (DmaHandlerGroup[1]) DmaHandlerGroup[1]();
    DmaChannelClearInterruptStatus(DMA_CHANNEL_1);
  }
  if (DmaChannelInterruptStatusBit(DMA_CHANNEL_2, 1))
  {
    if (DmaHandlerGroup[2]) DmaHandlerGroup[2]();
    DmaChannelClearInterruptStatus(DMA_CHANNEL_2);
  }
  if (DmaChannelInterruptStatusBit(DMA_CHANNEL_3, 1))
  {
    if (DmaHandlerGroup[3]) DmaHandlerGroup[3]();
    DmaChannelClearInterruptStatus(DMA_CHANNEL_3);
  }
}

/******************* (C) COPYRIGHT 2013 TDO *****END OF FILE****/
