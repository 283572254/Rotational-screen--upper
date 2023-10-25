 

/* Includes ------------------------------------------------------------------*/
#include "Y6_gpio.h"
#include "Y6_rcc.h"

/** @addtogroup Y6_StdPeriph_Driver
  * @{
  */

/** @defgroup GPIO 
  * @brief GPIO driver modules
  * @{
  */

/** @defgroup GPIO_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup GPIO_Private_Defines
  * @{
  */

#define GPIO_DMA_ENABLE ((uint32_t)0x80000000)
#define GPIO_DMA_DISABLE ((uint32_t)0x00000000)
/**
  * @}
  */

/** @defgroup GPIO_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup GPIO_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup GPIO_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup GPIO_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the GPIO peripheral registers to their default reset values.
  * @retval None
  */
void GPIO_Reset(void)
{
  RCC_SetPRESETCTRL(1 << PRESET_BIT_GPIO, DISABLE);
  RCC_SetPRESETCTRL(1 << PRESET_BIT_GPIO, ENABLE);
}

/**
  * @brief  Initializes the GPIOx peripheral according to the specified
  *   parameters in the GPIO_InitStruct.
  * @param  GPIOx: where x can be (0..1) to select the GPIO peripheral.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that
  *   contains the configuration information for the specified GPIO peripheral.
  * @retval None
  */
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct)
{
  uint32_t pinnum, temp;
  IOCON_TypeDef *PINCON;
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  if (GPIO_InitStruct->GPIO_Function == GPIO_FUNCTION_0)
    assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));

  assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
  assert_param(IS_GPIO_FUNCTION(GPIO_InitStruct->GPIO_Function));

  if (GPIOx == GPIO0)
  {
    for (pinnum = 0; pinnum < 32; pinnum++)
    {
      temp = (GPIO_InitStruct->GPIO_Pin) >> pinnum;
      temp &= 0x1;
      if (temp == 0x1)
      {
        PINCON = (IOCON_TypeDef *)(IOCON_PIO0_BASE + 0x4 * pinnum);
        PINCON->CON &= 0xFFFFFFF8;                     /* Clear IO function */
        PINCON->CON |= GPIO_InitStruct->GPIO_Function; /* Set IO function */
      }
    }
    if (GPIO_InitStruct->GPIO_Function == GPIO_FUNCTION_0)
    {
      if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT)
        GPIO0_IT->DIR_SET = GPIO_InitStruct->GPIO_Pin;
      else
        GPIO0_IT->DIR_CLR = GPIO_InitStruct->GPIO_Pin;
    }
  }
  else
  {
    for (pinnum = 0; pinnum < 32; pinnum++)
    {
      temp = (GPIO_InitStruct->GPIO_Pin) >> pinnum;
      temp &= 0x1;
      if (temp == 0x1)
      {
        PINCON = (IOCON_TypeDef *)(IOCON_PIO1_BASE + 0x4 * pinnum);
        PINCON->CON &= 0xFFFFFFF8;                     /* Clear IO function */
        PINCON->CON |= GPIO_InitStruct->GPIO_Function; /* Set IO function */
      }
    }
    if (GPIO_InitStruct->GPIO_Function == GPIO_FUNCTION_0)
    {
      if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT)
        GPIO1_IT->DIR_SET = GPIO_InitStruct->GPIO_Pin;
      else
        GPIO1_IT->DIR_CLR = GPIO_InitStruct->GPIO_Pin;
    }
  }
}

/**
  * @brief  Fills each GPIO_InitStruct member with its default value.
  * @param  GPIO_InitStruct : pointer to a GPIO_InitTypeDef structure which will
  *   be initialized.
  * @retval None
  */
void GPIO_StructInit(GPIO_InitTypeDef *GPIO_InitStruct)
{
  /* Reset GPIO init structure parameters values */
  GPIO_InitStruct->GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStruct->GPIO_Function = GPIO_FUNCTION_0;
  GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN;
}

/**
  * @brief  Sets the selected pins multiplex.
  * @param  GPIOx: where x can be (0..1) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *   This parameter can be one of GPIO_Pin_x where x can be (0..31).
  * @param  GPIO_Function: specifies the pin multiplex function.
  *   This parameter can be one of the GPIOFUNC_TypeDef enum values:
  *   	@arg GPIO_FUNCTION_0: 0.
  *   	@arg GPIO_FUNCTION_1: 1.
  *   	@arg GPIO_FUNCTION_2: 2.
  *   	@arg GPIO_FUNCTION_3: 3.
  *   	@arg GPIO_FUNCTION_4: 4.
  *   	@arg GPIO_FUNCTION_5: 5.
  *   	@arg GPIO_FUNCTION_6: 6.
  *   	@arg GPIO_FUNCTION_7: 7.
  * @retval None
  */
void GPIO_SetPinMux(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin, GPIOFUNC_TypeDef GPIO_Function)
{
  uint32_t pinnum, temp;
  IOCON_TypeDef *PINCON;
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_FUNCTION(GPIO_Function));

  if (GPIOx == GPIO0)
  {
    for (pinnum = 0; pinnum < 32; pinnum++)
    {
      temp = GPIO_Pin >> pinnum;
      temp &= 0x1;
      if (temp == 0x1)
      {
        PINCON = (IOCON_TypeDef *)(IOCON_PIO0_BASE + 0x4 * pinnum);
        PINCON->CON &= 0xFFFFFFF8;    /* Clear IO function */
        PINCON->CON |= GPIO_Function; /* Set IO function */
      }
    }
  }
  else
  {
    for (pinnum = 0; pinnum < 32; pinnum++)
    {
      temp = GPIO_Pin >> pinnum;
      temp &= 0x1;
      if (temp == 0x1)
      {
        PINCON = (IOCON_TypeDef *)(IOCON_PIO1_BASE + 0x4 * pinnum);
        PINCON->CON &= 0xFFFFFFF8;    /* Clear IO function */
        PINCON->CON |= GPIO_Function; /* Set IO function */
      }
    }
  }
}

/**
  * @brief  Configure GPIO as Analog function.
  * @param  GPIOx: where x can be (0..1) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *   This parameter can be one of GPIO_Pin_x where x can be (0..31).
  * @param  NewState: new state of Analog GPIO. 
  *   This parameter can be: ENABLE or DISABLE. 
  * @retval None. 
  */
void GPIO_ConfigAna(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin, FunctionalState NewState)
{
  uint32_t pinnum, temp;
  IOCON_TypeDef *PINCON;
  
  if (GPIOx == GPIO0)
  {
    for (pinnum = 0; pinnum < 32; pinnum++)
    {
      temp = GPIO_Pin >> pinnum;
      temp &= 0x1;
      if (temp == 0x1)
      {
        PINCON = (IOCON_TypeDef *)(IOCON_PIO0_BASE + 0x4 * pinnum);
		if(NewState == ENABLE){
	        PINCON->CON |= 0x00000080; /* Set ANA_EN */
		}else{
	        PINCON->CON &= 0xFFFFFF7F;    /* Clear ANA_EN */
		}
      }
    }
  }
  else
  {
    for (pinnum = 0; pinnum < 32; pinnum++)
    {
      temp = GPIO_Pin >> pinnum;
      temp &= 0x1;
      if (temp == 0x1)
      {
        PINCON = (IOCON_TypeDef *)(IOCON_PIO1_BASE + 0x4 * pinnum);
		if(NewState == ENABLE){
	        PINCON->CON |= 0x00000080; /* Set ANA_EN */
		}else{
	        PINCON->CON &= 0xFFFFFF7F;    /* Clear ANA_EN */
		}
      }
    }
  }
}

/**
  * @brief  Configure GPIO internal pull-dwon,pull-up or disable.
  * @param  GPIOx: where x can be (0..1) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *   This parameter can be one of GPIO_Pin_x where x can be (0..31).
  * @param  NewPull: specifies function mode.
  *   This parameter can be one of the GPIOPull_TypeDef enum values:
  *   	@arg GPIO_PULL_DISABLE: disable.
  *   	@arg GPIO_PULL_DOWN: pull-down.
  *   	@arg GPIO_PULL_UP: pull-up.
  * @retval None. 
  */
void GPIO_ConfigPull(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin, GPIOPull_TypeDef NewPull)
{
  uint32_t pinnum, temp;
  IOCON_TypeDef *PINCON;
  
  if (GPIOx == GPIO0)
  {
    for (pinnum = 0; pinnum < 32; pinnum++)
    {
      temp = GPIO_Pin >> pinnum;
      temp &= 0x1;
      if (temp == 0x1)
      {
        PINCON = (IOCON_TypeDef *)(IOCON_PIO0_BASE + 0x4 * pinnum);
        PINCON->CON &= 0xFFFFFFE7;    /* Clear PULL function */
        PINCON->CON |= NewPull;			 /* Set PULL function */
      }
    }
  }
  else
  {
    for (pinnum = 0; pinnum < 32; pinnum++)
    {
      temp = GPIO_Pin >> pinnum;
      temp &= 0x1;
      if (temp == 0x1)
      {
        PINCON = (IOCON_TypeDef *)(IOCON_PIO1_BASE + 0x4 * pinnum);
        PINCON->CON &= 0xFFFFFFE7;    /* Clear PULL function */
        PINCON->CON |= NewPull;			 /* Set PULL function */
      }
    }
  }
}

/**
  * @brief  Configuring IO driver capabilities.
  * @param  GPIOx: where x can be (0..1) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *   This parameter can be one of GPIO_Pin_x where x can be (0..31).
  * @param  NewDriver: specifies driver capabilities. 
  *   This parameter can be one of the GPIODrive_TypeDef enum values:
  *   	@arg GPIO_DRIVER_0: 8mA.
  *   	@arg GPIO_DRIVER_1: 12mA.
  * @retval None. 
  */
void GPIO_ConfigDriver(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin, GPIODrive_TypeDef NewDriver)
{
  uint32_t pinnum, temp;
  IOCON_TypeDef *PINCON;
  
  if (GPIOx == GPIO0)
  {
    for (pinnum = 0; pinnum < 32; pinnum++)
    {
      temp = GPIO_Pin >> pinnum;
      temp &= 0x1;
      if (temp == 0x1)
      {
        PINCON = (IOCON_TypeDef *)(IOCON_PIO0_BASE + 0x4 * pinnum);
        PINCON->CON &= 0xFFFFFEFF;    /* Clear Driver function */
        PINCON->CON |= NewDriver;			 /* Set Driver function */
      }
    }
  }
  else
  {
    for (pinnum = 0; pinnum < 32; pinnum++)
    {
      temp = GPIO_Pin >> pinnum;
      temp &= 0x1;
      if (temp == 0x1)
      {
        PINCON = (IOCON_TypeDef *)(IOCON_PIO1_BASE + 0x4 * pinnum);
        PINCON->CON &= 0xFFFFFEFF;    /* Clear Driver function */
        PINCON->CON |= NewDriver;			 /* Set Driver function */
      }
    }
  }
}

/**
  * @brief  Configure GPIO slew rate.
  * @param  GPIOx: where x can be (0..1) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *   This parameter can be one of GPIO_Pin_x where x can be (0..31).
  * @param  NewSlewRate: specifies the slew rate is fast or slow. 
  *   This parameter can be one of the GPIOSLEWRATE_TypeDef enum values:
  *   	@arg GPIO_SLEWRATE_FAST: fast.
  *   	@arg GPIO_SLEWRATE_SLOW: slow.
  * @retval  
  */
void GPIO_ConfigSlewRate(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin, GPIOSLEWRATE_TypeDef NewSlewRate)
{
  uint32_t pinnum, temp;
  IOCON_TypeDef *PINCON;
  
  if (GPIOx == GPIO0)
  {
    for (pinnum = 0; pinnum < 32; pinnum++)
    {
      temp = GPIO_Pin >> pinnum;
      temp &= 0x1;
      if (temp == 0x1)
      {
        PINCON = (IOCON_TypeDef *)(IOCON_PIO0_BASE + 0x4 * pinnum);
        PINCON->CON &= 0xFFFFFDFF;    /* Clear Driver function */
        PINCON->CON |= NewSlewRate;			 /* Set Driver function */
      }
    }
  }
  else
  {
    for (pinnum = 0; pinnum < 32; pinnum++)
    {
      temp = GPIO_Pin >> pinnum;
      temp &= 0x1;
      if (temp == 0x1)
      {
        PINCON = (IOCON_TypeDef *)(IOCON_PIO1_BASE + 0x4 * pinnum);
        PINCON->CON &= 0xFFFFFDFF;    /* Clear Driver function */
        PINCON->CON |= NewSlewRate;			 /* Set Driver function */
      }
    }
  }
}

/**
  * @brief  Sets the selected pins direction.
  * @param  GPIOx: where x can be (0..1) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..31).
  * @param  GPIO_Mode: specifies the direction mode.
  *   This parameter can be one of the GPIOMode_TypeDef enum values:
  *     @arg GPIO_Mode_IN: to set pin input.
  *     @arg GPIO_Mode_OUT: to set pin output.
  * @retval None
  */
void GPIO_SetPinDir(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode)
{
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_MODE(GPIO_Mode));
  
  GPIO_SetPinMux(GPIOx, GPIO_Pin, GPIO_FUNCTION_0);
  if (GPIO_Mode == GPIO_Mode_OUT)
  {
    if (GPIOx == GPIO0)
    {
      GPIO0_IT->DIR_SET = GPIO_Pin;
    }
    else
    {
      GPIO1_IT->DIR_SET = GPIO_Pin;
    }
  }
  else if (GPIO_Mode == GPIO_Mode_IN)
  {
    if (GPIOx == GPIO0)
    {
      GPIO0_IT->DIR_CLR = GPIO_Pin;
    }
    else
    {
      GPIO1_IT->DIR_CLR = GPIO_Pin;
    }
  }
}

/**
  * @brief  Writes the specified port.
  * @param  GPIOx: where x can be (0..1) to select the GPIO peripheral.
  * @param  PortVal:  specifies the value to be written to the selected port.
  * @retval none.
  */
void GPIO_WritePort(GPIO_TypeDef *GPIOx, uint32_t PortVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  GPIOx->DT = PortVal;
}

/**
  * @brief  Reads the specified port all pins data value.
  * @param  GPIOx: where x can be (0..1) to select the GPIO peripheral.
  * @retval GPIO port all pins data value.
  */
uint32_t GPIO_ReadPort(GPIO_TypeDef *GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  return (GPIOx->DT);
}

/**
  * @brief  Sets or clears the selected data port bit.
  * @param  GPIOx: where x can be (0..1) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *   This parameter can be one of GPIO_Pin_x where x can be (0..31).
  * @param  BitVal: specifies the value to be written to the selected bit.
  *   This parameter can be one of the BitAction enum values:
  *     @arg Bit_RESET: to clear the port pin
  *     @arg Bit_SET: to set the port pin
  * @retval None
  */
void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin, BitAction BitVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_BIT_ACTION(BitVal));

  if (BitVal != Bit_RESET)
  {
    GPIOx->DT_SET = GPIO_Pin;
  }
  else
  {
    GPIOx->DT_CLR = GPIO_Pin;
  }
}

/**
  * @brief  Reads the specified port bit data value.
  * @param  GPIOx: where x can be (0..1) to select the GPIO peripheral.
  * @param  GPIO_Pin:  specifies the port bit to read.
  *   This parameter can be GPIO_Pin_x where x can be (0..31).
  * @retval The specified port pin value.
  */
uint8_t GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

  if ((GPIOx->DT & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

/**
  * @brief  Sets the selected data port bits.
  * @param  GPIOx: where x can be (0..1) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..31).
  * @retval None
  */
void GPIO_SetPin(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->DT_SET = GPIO_Pin;
}

/**
  * @brief  Clears the selected data port bits.
  * @param  GPIOx: where x can be (0..1) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..31).
  * @retval None
  */
void GPIO_ClearPin(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->DT_CLR = GPIO_Pin;
}


/**
  * @brief  Masks the selected port pin data register bits.
  * @param  GPIOx: where x can be (0..1) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..31).
  * @retval None
  */
void GPIO_PinMask(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  if (GPIOx == GPIO0)
  {
    /* Set mask bit */
    GPIO0_IT->DATAMASK_SET = GPIO_Pin;
  }
  else
  {
    GPIO1_IT->DATAMASK_SET = GPIO_Pin;
  }
}

/**
  * @brief  Unmasks the selected port pin data register bits.
  * @param  GPIOx: where x can be (0..1) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..31).
  * @retval None
  */
void GPIO_PinUnmask(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  if (GPIOx == GPIO0)
  {
    /* Clear mask bit */
    GPIO0_IT->DATAMASK_CLR = GPIO_Pin;
  }
  else
  {
    GPIO1_IT->DATAMASK_CLR = GPIO_Pin;
  }
}

/**
  * @brief  Enables edge IT on the specified port pins.
  * @param  GPIOx_IT: where x can be (0..1) to select the GPIO peripheral.
  * @param  GPIO_Pin:  specifies the port bit to set.
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..31).
  * @param  GPIO_Irq: specifies the irq type.
  *   This parameter can be one of the EdgeAction enum values:
  *     @arg GPIO_IRQ_EDGE_FALLING: to select falling edge trigger.
  *     @arg GPIO_IRQ_EDGE_RISING: to select rising edge trigger.
  *     @arg GPIO_IRQ_EDGE_DOUBLE: to select double edge trigger.
  * @retval none.
  */
void GPIO_EdgeITEnable(GPIO_IT_TypeDef *GPIOx_IT, uint32_t GPIO_Pin, EdgeAction GPIO_Irq)
{
  /* Check the parameters */
  assert_param(IS_GPIO_IT_ALL_PERIPH(GPIOx_IT));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_EDGE_ACTION(GPIO_Irq));

  GPIOx_IT->IS_CLR = GPIO_Pin; /* Clear IS register bits,select edge trigger */

  if (GPIO_Irq == GPIO_IRQ_EDGE_FALLING)
  {
    GPIOx_IT->IEV_CLR = GPIO_Pin; /* Choose falling edge */
  }
  else if (GPIO_Irq == GPIO_IRQ_EDGE_RISING)
  {
    GPIOx_IT->IEV_SET = GPIO_Pin; /* Choose rising edge */
  }
  else if (GPIO_Irq == GPIO_IRQ_EDGE_DOUBLE)
  {
    GPIOx_IT->IBE_SET = GPIO_Pin; /* Choose double edge */
  }
  GPIOx_IT->IE_SET = GPIO_Pin; /* Unmask IRQ */
}

/**
  * @brief  Enables level IT on the specified port pins.
  * @param  GPIOx_IT: where x can be (0..1) to select the GPIO peripheral.
  * @param  GPIO_Pin:  specifies the port bit to set.
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..31).
  * @param  GPIO_Irq: specifies the irq type.
  *   This parameter can be one of the LevelAction enum values:
  *     @arg GPIO_IRQ_LEVEL_LOW: to select low level trigger.
  *     @arg GPIO_IRQ_LEVEL_HIGH: to select high level trigger.
  * @retval none.
  */
void GPIO_LevelITEnable(GPIO_IT_TypeDef *GPIOx_IT, uint32_t GPIO_Pin, LevelAction GPIO_Irq)
{
  /* Check the parameters */
  assert_param(IS_GPIO_IT_ALL_PERIPH(GPIOx_IT));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_LEVEL_ACTION(GPIO_Irq));

  if (GPIO_Irq == GPIO_IRQ_LEVEL_LOW)
  {
    GPIOx_IT->IEV_CLR = GPIO_Pin; /* Choose low level */
  }
  else if (GPIO_Irq == GPIO_IRQ_LEVEL_HIGH)
  {
    GPIOx_IT->IEV_SET = GPIO_Pin; /* Choose high level */
  }
  GPIOx_IT->IS_SET = GPIO_Pin; /* Set IS register bits,select level trigger */
  GPIOx_IT->IE_SET = GPIO_Pin; /* Unmask IRQ */
}

/**
  * @brief  Mask IT on the specified port pins.
  * @param  GPIOx_IT: where x can be (0..3) to select the GPIO peripheral.
  * @param  GPIO_Pin:  specifies the port bit to set.
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..31).
  * @retval none.
  */
void GPIO_MaskIT(GPIO_IT_TypeDef *GPIOx_IT, uint32_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_IT_ALL_PERIPH(GPIOx_IT));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx_IT->IE_CLR = GPIO_Pin;
}

/**
  * @brief  Unmask IT on the specified port pins.
  * @param  GPIOx_IT: where x can be (0..1) to select the GPIO peripheral.
  * @param  GPIO_Pin:  specifies the port bit to set.
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..31).
  * @retval none.
  */
void GPIO_UnmaskIT(GPIO_IT_TypeDef *GPIOx_IT, uint32_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_IT_ALL_PERIPH(GPIOx_IT));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx_IT->IE_SET = GPIO_Pin;
}

/**
  * @brief  Clear edge IT on the specified port pins.
  * @param  GPIOx_IT: where x can be (0..1) to select the GPIO peripheral.
  * @param  GPIO_Pin:  specifies the port bit to set.
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..31).
  * @retval none.
  */
void GPIO_EdgeITClear(GPIO_IT_TypeDef *GPIOx_IT, uint32_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_IT_ALL_PERIPH(GPIOx_IT));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx_IT->IC_SET = GPIO_Pin;
}

/**
  * @brief  Gets the original IT status on the specified port pin.
  * @param  GPIOx_IT: where x can be (0..1) to select the GPIO peripheral. 
  * @param  GPIO_Pin:  specifies the port bit to read.
  *   This parameter can be GPIO_Pin_x where x can be (0..31).
  * @retval The original IT status.
  *         @arg  Bit_SET: have interrupt
  *         @arg  Bit_RESET: no interrupt
  */
uint8_t GPIO_GetOriginalITStatus(GPIO_IT_TypeDef *GPIOx_IT, uint32_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;
  /* Check the parameters */
  assert_param(IS_GPIO_IT_ALL_PERIPH(GPIOx_IT));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

  if ((GPIOx_IT->IRS & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

/**
  * @brief  Gets the mask IT status on the specified port pin.
  * @param  GPIOx_IT: where x can be (0..1) to select the GPIO peripheral. 
  * @param  GPIO_Pin:  specifies the port bit to read.
  *   This parameter can be GPIO_Pin_x where x can be (0..31).
 * @retval The mask IT status.
  *         @arg  Bit_SET: have interrupt
  *         @arg  Bit_RESET: no interrupt
  */
uint8_t GPIO_GetMaskITStatus(GPIO_IT_TypeDef *GPIOx_IT, uint32_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;
  /* Check the parameters */
  assert_param(IS_GPIO_IT_ALL_PERIPH(GPIOx_IT));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

  if ((GPIOx_IT->MIS & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
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

/******************* (C) COPYRIGHT 2013 TDO *****END OF FILE****/
