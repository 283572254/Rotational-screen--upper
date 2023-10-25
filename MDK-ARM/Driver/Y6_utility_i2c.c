#include "Y6.h"
#include "Y6_rcc.h"
#include "Y6_gpio.h"
#include "Y6_dma.h"
#include "Y6_utility_i2c.h"
#include "misc.h"
#include "string.h"
#include "stdio.h"
#include "Y6_i2c.h"

#define I2C_DEBUG             1
#if I2C_DEBUG
  #include "stdio.h"
  #define i2c_debug(x)        printf("i2c error: %s\r\n", x);
#else
  #define i2c_debug(x)
#endif


#define TIMEOUT            0x10000// 
#define NUM_SPEEDS            2
/*CNT registers values when ic_clk = 12Mhz*/
static const uint16_t HCNT[NUM_SPEEDS] = {
   0x34, 0x06
};
static const uint16_t LCNT[NUM_SPEEDS] = {
   0x3B, 0x0F 
};


/** 
  * @brief  init i2c module
  * @param  speed: I2C_SPEED_STD - set i2c to standard speed mode
  *                I2C_SPEED_FAST - set i2c to fast speed mode
  *         pin_group: select pin group ti set to i2c pin mux
  *            This parameter can be one of the following values:
  *            I2C_GP0_A, I2C_GP0_B, I2C_GP7
  * @retval 0 = success
  *         -1= failed
  */
int I2C_Configuration(I2CSpeedSel speed, I2CPinGroup pin_group)
{
  uint32_t timeout;
  uint32_t sourceclock;
  uint16_t hcnt, lcnt;
  RCC_ResetAHBCLK(1<<AHBCLK_BIT_I2C0);

  if (pin_group == I2C_GP0_A)
  {
    GPIO_SetPinMux(GPIO0, GPIO_Pin_0, GPIO_FUNCTION_2);  /*SDA*/
    GPIO_SetPinMux(GPIO0, GPIO_Pin_1, GPIO_FUNCTION_2);  /*SCL*/
  }
  else if (pin_group == I2C_GP0_B)
  {
    GPIO_SetPinMux(GPIO0, GPIO_Pin_3, GPIO_FUNCTION_3);  /*SDA*/
    GPIO_SetPinMux(GPIO0, GPIO_Pin_4, GPIO_FUNCTION_3);  /*SCL*/
  }
  else if (pin_group == I2C_GP7)
  {
    GPIO_SetPinMux(GPIO1, GPIO_Pin_28, GPIO_FUNCTION_2);  /*SDA*/
    GPIO_SetPinMux(GPIO1, GPIO_Pin_29, GPIO_FUNCTION_2);  /*SCL*/
  }
  
  timeout = TIMEOUT;
  I2C0->ENABLE = 0;
  while ((I2C0->STAT & I2C_IC_STATUS_ACTIVITY) || (I2C0->ENABLE_STATUS & I2C_IC_ENABLE_STATUS_IC_EN))
  {
    I2C0->ENABLE = 0;
    timeout--;
    if(timeout == 0)
    {
      i2c_debug("init failed");
      return -1;
    }
  }
  
  /*disable interrupt*/
  I2C0->INTR_MASK &= ~0xfff;
 
  /*clear abort source*/
  I2C0->TX_ABRT_SOURCE &= ~(I2C_IC_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT);
  I2C0->TAR &= ~(I2C_TAR_IC_SPECIAL);
  I2C0->CLR_TX_ABRT;
  
  /*mode config*/
  I2C0->CON = I2C_CON_IC_SLAVE_DISABLE  //slave mode disable
            | I2C_CON_IC_RESTART_EN  //restart enable
            | (speed+1) << 1  //1:stardard speed, 2:fast speed
            | I2C_CON_MASTER_MODE;       //master mode
  
  /*speed config*/
  sourceclock = RCC_GetClocksFreq(RCC_CLOCKFREQ_SYSAHBCLK)/1000;
  if(sourceclock >= 12000)
  {
    hcnt = (uint16_t)(((int)HCNT[speed] + 8) * (sourceclock/12000) - 8);
    lcnt = (uint16_t)(((int)LCNT[speed] + 1) * (sourceclock/12000) - 1);
  }
  else
  {
    if(speed == I2C_SPEED_FAST)
      speed = I2C_SPEED_STD;  //according to DW_apb_i2c databook, when ic_clk <= 6Mhz, it's impossible to set 400kHz

    if ((sourceclock == 6000)||(sourceclock == 4000)||(sourceclock == 3000))
    {
      hcnt =  (uint16_t)(((int)HCNT[speed] + 8)/(12000/sourceclock) - 8);
      lcnt =  (uint16_t)(((int)LCNT[speed] + 1)/(12000/sourceclock) - 1);
    }
    else
    {
      i2c_debug("sysclk do not support selected speed mode");
      return -1;  //according to DW_apb_i2c databook, when ic_clk <= 2Mhz, it's impossible to set even 100kHz
    }
  }
  if (speed == I2C_SPEED_STD)
  {
    I2C0->SS_SCL_HCNT = hcnt;
    I2C0->SS_SCL_LCNT = lcnt;
  }else
  {
    I2C0->FS_SCL_HCNT = hcnt;
    I2C0->FS_SCL_LCNT = lcnt;
  }

  /* Set tranmit & receive FIFO threshold to zero */
  I2C0->RX_TL = 0;
  I2C0->TX_TL = 0;

  /*target device addressing initial setting*/
  I2C0->TAR = 0;

	commonDelay(0x40000);
	
  return 0;
}


/** 
  * @brief  write bytes with dma
  * @param  dev_addr: device address on i2c bus
  *         internal_addr: i2c device internal address to write into
  *         addr_size: internal address byte length
  *         buf: written data address
  *         write_size: write size in bytes
  * @retval 0 = success
  *         -1= failed
  */
int I2C_DmaWrite(uint8_t dev_addr, uint32_t internal_addr, int addr_size, uint8_t *buf,  int write_size)
{
  int i;
  DMAchannel channel;
  DMAChannel_TypeDef *I2CDMAChannel;
  uint32_t timeout;
  uint32_t temreg;

  if(write_size > CHANNEL_MAX_SIZE)
  {
    i2c_debug("transmit size beyond dma trans-ability");
    return -1;
  }
  
  channel = DmaRequestChannel(NULL);
  if (channel > DMA_CHANNEL_3)
  {
    i2c_debug("all dma channel busy");
    return -1;
  }

  I2CDMAChannel = (DMAChannel_TypeDef *)(DMA_BASE + channel*0x58);

  /*channel 0 config*/
  temreg = 0x00000000 + (0 << DMA_CTRL_INT_EN)  //INT_EN, ch0 irq disable
                      + (0 << DMA_CTRL_DST_TR_WIDTH)      // DST_TR_WIDTH, des transfer width, should set to HSIZE, here is 000, means 8bit
                      + (0 << DMA_CTRL_SRC_TR_WIDTH)      // SRC_TR_WIDTH, sor transfer width, should set to HSIZE, here is 000, means 8bit
                      + (2 << DMA_CTRL_DINC)      // DINC, des addr increment, des is SPI, so should set to 1x, means no change
                      + (0 << DMA_CTRL_SINC)      // SINC, sor addr increment, src is sram, so should set to 00, means to increase 
                      + (0 << DMA_DEST_MSIZE)     // DEST_MSIZE, des burst length, set to 001 means 4 DST_TR_WIDTH per burst transcation
                      + (0 << DMA_SRC_MSIZE)     // SRC_MSIZE, sor burst length, set to 001 means 4 SOR_TR_WIDTH per burst transcation
                      + (6 << DMA_TTC_FC)     // TT_FC,transfer type and flow control,001 means memory to peripheral,dma is flow controller
                      + (0 << DMA_DMS)     // DMS, des master select, 0 means ahb master 0
                      + (0 << DMA_SMS)     // SMS, sor master select, 0 means ahb master 0
                      + (0 << DMA_LLP_DST_EN)     // LLP_DST_EN, des block chaining enable, set to 0 disable it
                      + (0 << DMA_LLP_SRC_EN) ;   // LLP_SOR_EN, sor block chaining enable, set to 0 disable it
  DMA->DmaCfgReg = 1;
  DmaChannelCFGset(channel, 0, (REQ_I2C0TX << DMA_CFG_SRC_PER) + (REQ_I2C0TX << DMA_CFG_DEST_PER));
  
  I2CDMAChannel->SAR = (uint32_t)buf;
  I2CDMAChannel->DAR = (uint32_t)&I2C0->DATA_CMD;
  I2CDMAChannel->CTL_L = temreg;
  I2CDMAChannel->CTL_H = write_size;
  
  /*disable I2C module*/
  timeout = TIMEOUT;
  I2C0->ENABLE = 0;
  while ((I2C0->STAT & I2C_IC_STATUS_ACTIVITY) || (I2C0->ENABLE_STATUS & I2C_IC_ENABLE_STATUS_IC_EN)){
    I2C0->ENABLE = 0;
    timeout--;
    if(timeout == 0){
      i2c_debug("init failed");
      DmaFreeChannel(channel);
      return -1;
    }
  }
  
  I2C0->CON &= ~I2C_CON_IC_RESTART_EN;  //restart disable
  
  temreg = I2C0->TAR;
  temreg &= ~0x000003ff;
  temreg |= 1 << 10; //generate START BYTE
  temreg |= dev_addr;
  I2C0->TAR = temreg;
  
  I2C0->ENABLE = 1;
  
  /*send device internal addr*/
  for (i = addr_size - 1; i >= 0; i--)
  {
    timeout = TIMEOUT;
    I2C0->DATA_CMD = (internal_addr >> i*8) & 0x00ff;
    while (((I2C0->STAT & (1 << 2)) == 0) && timeout)timeout--;
    if (timeout == 0){
      i2c_debug("Dma Write func send internal address failed");
      DmaFreeChannel(channel);
      return -1;
    }
  }

  I2C0->DMA_TDLR = 1; //dma tx level
  I2C0->DMA_CR |= 1 << 1; //I2C tx dma enable
  
  timeout = TIMEOUT;
  DMA->ChEnReg = 0x101 << channel;
  while((DMA->ChEnReg & (1 << channel)) && timeout)
    timeout--;
  
  if (timeout == 0){
		I2C_Configuration(I2C_SPEED_STD, I2C_GP0_A);
    i2c_debug("Dma Write func timeout");
    DmaFreeChannel(channel);
    return -1;
  }

  DmaFreeChannel(channel);

  return 0;
}

uint32_t null;
/** 
  * @brief  read bytes with dma
  * @param  dev_addr: device address on i2c bus
  *         internal_addr: i2c device internal address to write into
  *         addr_size: internal address byte length
  *         buf: mem to store read data
  *         read_size: read size in bytes
  * @retval 0 = success
  *         -1= failed
  */
int I2C_DmaRead(uint8_t dev_addr, uint32_t internal_addr, int addr_size, uint8_t *buf,  int read_size)
{
  int i;
  DMAchannel channel_tx, channel_rx;
  DMAChannel_TypeDef *TxDMAChannel, *RxDMAChannel;
  uint32_t timeout;
  uint32_t temreg;
  
  if(read_size > CHANNEL_MAX_SIZE)
  {
    i2c_debug("transmit size beyond dma trans-ability");
    return -1;
  }

  null = 0x100;
  
  channel_tx = DmaRequestChannel(NULL);
  if (channel_tx > DMA_CHANNEL_3){
		i2c_debug("no tx channel");
		return -1;
	}
  channel_rx = DmaRequestChannel(NULL);
  if (channel_rx > DMA_CHANNEL_3){
		i2c_debug("no rx channel");
    DmaFreeChannel(channel_tx);
    return -1;
  }

  TxDMAChannel = (DMAChannel_TypeDef *)(DMA_BASE + channel_tx*0x58);
  RxDMAChannel = (DMAChannel_TypeDef *)(DMA_BASE + channel_rx*0x58);

  DMA->DmaCfgReg = 1;
  DmaChannelCFGset(channel_tx, 0, (REQ_I2C0TX << DMA_CFG_SRC_PER) + (REQ_I2C0TX << DMA_CFG_DEST_PER));
  DmaChannelCFGset(channel_rx, 0, (REQ_I2C0RX << DMA_CFG_SRC_PER) + (REQ_I2C0RX << DMA_CFG_DEST_PER));
  
  /*channel 0 config*/
  temreg = 0x00000000 + (0 << DMA_CTRL_INT_EN)  //INT_EN, ch0 irq disable
                      + (2 << DMA_CTRL_DST_TR_WIDTH)      // DST_TR_WIDTH, des transfer width, should set to HSIZE, here is 000, means 8bit
                      + (2 << DMA_CTRL_SRC_TR_WIDTH)      // SRC_TR_WIDTH, sor transfer width, should set to HSIZE, here is 000, means 8bit
                      + (2 << DMA_CTRL_DINC)      // DINC, des addr increment, des is SPI, so should set to 1x, means no change
                      + (2 << DMA_CTRL_SINC)      // SINC, sor addr increment, src is sram, so should set to 1x, means no change 
                      + (0 << DMA_DEST_MSIZE)     // DEST_MSIZE, des burst length, set to 001 means 4 DST_TR_WIDTH per burst transcation
                      + (0 << DMA_SRC_MSIZE)     // SRC_MSIZE, sor burst length, set to 001 means 4 SOR_TR_WIDTH per burst transcation
                      + (1 << DMA_TTC_FC)     // TT_FC,transfer type and flow control,001 means memory to peripheral,dma is flow controller
                      + (0 << DMA_DMS)     // DMS, des master select, 0 means ahb master 0
                      + (0 << DMA_SMS)     // SMS, sor master select, 0 means ahb master 0
                      + (0 << DMA_LLP_DST_EN)     // LLP_DST_EN, des block chaining enable, set to 0 disable it
                      + (0 << DMA_LLP_SRC_EN) ;   // LLP_SOR_EN, sor block chaining enable, set to 0 disable it  
  
  TxDMAChannel->SAR = (uint32_t)&null;
  TxDMAChannel->DAR = (uint32_t)&I2C0->DATA_CMD;
  TxDMAChannel->CTL_L = temreg;
  TxDMAChannel->CTL_H = read_size;
  
  /*channel 1 config*/
  temreg = 0x00000000 + (1 << DMA_CTRL_INT_EN)  //INT_EN, ch1 irq disable
                      + (0 << DMA_CTRL_DST_TR_WIDTH)      // DST_TR_WIDTH, des transfer width, should set to HSIZE, here is 000, means 8bit
                      + (0 << DMA_CTRL_SRC_TR_WIDTH)      // SRC_TR_WIDTH, sor transfer width, should set to HSIZE, here is 000, means 8bit
                      + (0 << DMA_CTRL_DINC)      // DINC, des addr increment, des is SPI, so should set to 1x, means no change
                      + (2 << DMA_CTRL_SINC)      // SINC, sor addr increment, src is sram, so should set to 00, means to increase 
                      + (0 << DMA_DEST_MSIZE)     // DEST_MSIZE, des burst length, set to 001 means 4 DST_TR_WIDTH per burst transcation
                      + (0 << DMA_SRC_MSIZE)     // SRC_MSIZE, sor burst length, set to 001 means 4 SOR_TR_WIDTH per burst transcation
                      + (2 << DMA_TTC_FC)     // TT_FC,transfer type and flow control,001 means memory to peripheral,dma is flow controller
                      + (0 << DMA_DMS)     // DMS, des master select, 0 means ahb master 0
                      + (0 << DMA_SMS)     // SMS, sor master select, 0 means ahb master 0
                      + (0 << DMA_LLP_DST_EN)     // LLP_DST_EN, des block chaining enable, set to 0 disable it
                      + (0 << DMA_LLP_SRC_EN) ;   // LLP_SOR_EN, sor block chaining enable, set to 0 disable it  
  
  RxDMAChannel->SAR = (uint32_t)&I2C0->DATA_CMD;
  RxDMAChannel->DAR = (uint32_t)buf;
  RxDMAChannel->CTL_L = temreg;
  RxDMAChannel->CTL_H = read_size;
  
  /*disable I2C module*/
  timeout = TIMEOUT;
  I2C0->ENABLE = 0;
  while ((I2C0->STAT & I2C_IC_STATUS_ACTIVITY) || (I2C0->ENABLE_STATUS & I2C_IC_ENABLE_STATUS_IC_EN)){
    I2C0->ENABLE = 0;
    timeout--;
    if(timeout == 0){
      i2c_debug("init failed");
      DmaFreeChannel(channel_tx);
      DmaFreeChannel(channel_rx);
      return -1;
    }
  }
  
  I2C0->CON |= 1 << 5;  //restart enable
  
  temreg = I2C0->TAR;
  temreg &= ~0x000003ff;
  temreg |= 1 << 10; //generate START BYTE
  temreg |= dev_addr;
  I2C0->TAR = temreg;

  I2C0->ENABLE = 1;
  
  /*send device internal addr*/
  for (i = addr_size - 1; i >= 0; i--){
    timeout = TIMEOUT;
    I2C0->DATA_CMD = (internal_addr >> i*8) & 0x00ff;
    while (((I2C0->STAT & (1 << 2)) == 0) && timeout)
      timeout--;
    if (timeout == 0){
      i2c_debug("Dma Read func send internal address failed");
      DmaFreeChannel(channel_tx);
      DmaFreeChannel(channel_rx);
      return -1;
    }
  }

  I2C0->DMA_TDLR = 1; //dma tx level
  I2C0->DMA_RDLR = 0; //dma rx level
  I2C0->DMA_CR |= 3; //I2C rx dma enable


  timeout = TIMEOUT;
  DMA->ChEnReg = (0x101 << channel_tx) | (0x101 << channel_rx); //start dma transfer
  while((DMA->ChEnReg & (1 << channel_rx)) && timeout) 
	  timeout--; 
  if (timeout == 0){
    i2c_debug("Dma Read func timeout");
    DmaFreeChannel(channel_tx);
    DmaFreeChannel(channel_rx);
    return -1;
  }

  DmaFreeChannel(channel_tx);
  DmaFreeChannel(channel_rx);
  return 0;
}

/** 
  * @brief  write bytes in pio mode
  * @param  dev_addr: device address on i2c bus
  *         internal_addr: i2c device internal address to write into
  *         addr_size: internal address byte length
  *         buf: written data address
  *         write_size: write size in bytes
  * @retval 0 = success
  *         -1= failed
  */
int I2C_Write(uint8_t dev_addr, uint32_t internal_addr, int addr_size, uint8_t *buf,  int write_size)
{
  int i;
  uint32_t timeout;
  uint32_t temreg;
  
  /*disable I2C module*/
  timeout = TIMEOUT;
  I2C0->ENABLE = 0;
	printf("i2c_stat=%#x\n",I2C0->STAT);
  while ((I2C0->STAT & I2C_IC_STATUS_ACTIVITY) || (I2C0->ENABLE_STATUS & I2C_IC_ENABLE_STATUS_IC_EN))
  {
    I2C0->ENABLE = 0;
    timeout--;
    if(timeout == 0)
    {
      i2c_debug("init failed");
      return -1;
    }
  }
  
  I2C0->CON &= ~(1 << 5);  //restart disable
  
  temreg = I2C0->TAR;
  temreg &= ~0x000003ff;
  temreg |= 1 << 10; //generate START BYTE
  temreg |= dev_addr;
  I2C0->TAR = temreg;
  
  I2C0->ENABLE = 1;
  
  /*send device internal addr*/
  for (i = addr_size - 1; i >= 0; i--)
  {
    timeout = TIMEOUT;
    I2C0->DATA_CMD = (internal_addr >> i*8) & 0x00ff;
    while (((I2C0->STAT & (1 << 2)) == 0) && timeout)
      timeout--;
    if (timeout == 0)
    {
      i2c_debug("send internal address failed");
      return -1;
    }
  }
  
  /*write data*/
  for (i = 0; i < write_size; i++)
  {
    timeout = TIMEOUT;
    I2C0->DATA_CMD = buf[i] & 0x00ff;
	//  printf("buf[%d]=%d,I2C0->DATA_CMD=%#x\n",i,buf[i],I2C0->DATA_CMD);
    while (((I2C0->STAT & (1 << 2)) == 0) && timeout)
      timeout--;
    if (timeout == 0)
    {
      i2c_debug("write data timeout");
      return -1;
    }
  }

  return 0;
}

/** 
  * @brief  read bytes in pio mode
  * @param  dev_addr: device address on i2c bus
  *         internal_addr: i2c device internal address to write into
  *         addr_size: internal address byte length
  *         buf: mem to store read data
  *         read_size: read size in bytes
  * @retval 0 = success
  *         -1= failed
  */
int I2C_Read(uint8_t dev_addr, uint32_t internal_addr, int addr_size, uint8_t *buf,  int read_size)
{	
 int i;
  uint32_t timeout;
  uint32_t temreg;
  /*disable I2C module*/
  timeout = TIMEOUT;
  I2C0->ENABLE = 0;
  while ((I2C0->STAT & I2C_IC_STATUS_ACTIVITY) || (I2C0->ENABLE_STATUS & I2C_IC_ENABLE_STATUS_IC_EN))
  {
    I2C0->ENABLE = 0;
    timeout--;
    if(timeout == 0)
    {
      i2c_debug("init failed");
      return -1;
    }
  }
  
  I2C0->CON |= 1 << 5;  //restart enable
  
  temreg = I2C0->TAR;
  temreg &= ~0x000003ff;
  temreg |= 1 << 10; //generate START BYTE
  temreg |= dev_addr;
  I2C0->TAR = temreg;
  
  I2C0->ENABLE = 1;
  
  /*send device internal addr*/
  for (i = addr_size - 1; i >= 0; i--)
  {
    timeout = TIMEOUT;
    I2C0->DATA_CMD = (internal_addr >> i*8) & 0x00ff;
    while (((I2C0->STAT & (1 << 2)) == 0) && timeout){
			timeout--;
		}
    if (timeout == 0)
    {
      i2c_debug("send internal address failed");
      return -1;
    }
  }
  
  /*read*/
  i = 0;
  while (i < read_size)
  {  
		//printf("i:0x%02x  read_size:0x%02x\r\n",i,read_size);
    if ((I2C0->STAT & (1 << 4)) == 0)
    {
      I2C0->DATA_CMD = 1 << 8; //trigger read
		
    }
    if ((I2C0->STAT & (1 << 3)) ==0)
    {
      buf[i] = I2C0->DATA_CMD & 0xff;
	//  printf("I2C0->DATA_CMD=%#x,buf[%d]=%d\n",I2C0->DATA_CMD,i,buf[i]);
      i++;
		
    }
  }

  return 0;
}


void i2c_test(void)
{
  int reg;
  char write_buf[8] = {0x60, 0, 0, 0x06, 1};
  char read_buf[8];
  I2C_Configuration(I2C_SPEED_STD, I2C_GP7);

  reg=I2C_DmaWrite(0x2a >> 1, 0xFA, 1, (uint8_t *)write_buf, 5);

  commonDelay(0x4000);
  memset(read_buf, 0, sizeof(read_buf));

  reg = I2C_DmaRead(0x2a >> 1, 0xA7, 1, (uint8_t *)read_buf, 1);
  reg = I2C_DmaRead(0x2a >> 1, 0xEE, 1, (uint8_t *)read_buf+2, 1);
}
