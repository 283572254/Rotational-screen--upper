 

/* Includes ------------------------------------------------------------------*/
#include "Y6.h"
#include "Y6_rcc.h"
#include "Y6_gpio.h"
#include "Y6_eval_qspi.h"
#include "Y6_qspi.h"
#include <stdio.h>

#define MAX_QSPI_DMA_BUSY_WATI	 0x200000
uint8_t _4ByteAddrMode = 0;

static int start_quad_spi_dma_tx(QSPI_TypeDef *QSPIptr, uint8_t *src_addr, int bytenum) //DMA1 hardware channel2
{
	uint32_t temreg;
	int waitchannel = MAX_QSPI_DMA_BUSY_WATI;

	while( (DMA->ChEnReg&0x01)&&(waitchannel--) )
			;
	if(waitchannel<=0)
		return -1;
	
	temreg = 0x00000000+(0<<0)    //INT_EN, ch0 irq disable
		                       	+(0<<1)      // DST_TR_WIDTH, des transfer width, should set to HSIZE, here is 000, means 8bit
                                +(0<<4)      // SRC_TR_WIDTH, sor transfer width, should set to HSIZE, here is 000, means 8bit
                                +(2<<7)      // DINC, des addr increment, des is SPI, so should set to 1x, means no change
                                +(0<<9)      // SINC, sor addr increment, src is sram, so should set to 00, means to increase 
                                +(1<<11)     // DEST_MSIZE, des burst length, set to 001 means 4 DST_TR_WIDTH per burst transcation
                                +(1<<14)     // SRC_MSIZE, sor burst length, set to 001 means 4 SOR_TR_WIDTH per burst transcation
                                +(1<<20)     // TT_FC,transfer type and flow control,001 means memory to peripheral,dma is flow controller
                                +(0<<23)     // DMS, des master select, 0 means ahb master 0
                                +(0<<25)     // SMS, sor master select, 1 means ahb master 1
                                +(0<<27)     // LLP_DST_EN, des block chaining enable, set to 0 disable it
                                +(0<<28) ;   // LLP_SOR_EN, sor block chaining enable, set to 0 disable it	

	DMA->SAR0 = (uint32_t)src_addr;
	DMA->DAR0 = (uint32_t)(&QSPI0->DATA);
	DMA->CTL0_L = temreg;
	DMA->CTL0_H = bytenum;
	DMA->LLP0 = 0;
	DMA->CFG0_L = 0;
    if(QSPIptr == QSPI0){
        DMA->CFG0_H = 0x00000000 + (8 << 7) + (8 << 11);
    }else if(QSPIptr == QSPI1){
        DMA->CFG0_H = 0x00000000 + (10 << 7) + (10 << 11);
    }
	DMA->DmaCfgReg = 0x01;
	DMA->ChEnReg = 0x101;
		
    waitchannel = MAX_QSPI_DMA_BUSY_WATI;
    while (((DMA->ChEnReg & 0x01) || (QSPI_GetFlagStatus(QSPIptr, QSPI_STATUS_SPI_BUSY) == SET)) && (waitchannel--))
        ;
	
	if(waitchannel <= 0)
	{
	  return -3;
	}  		
	
	return 0; 
}

static int start_quad_spi_dma_rx(QSPI_TypeDef *QSPIptr, uint8_t *dst_addr, int bytenum) //DMA1 hardware channel 3
{
	uint32_t temreg;
	int waitchannel = MAX_QSPI_DMA_BUSY_WATI;

	if( ((uint32_t)dst_addr&0x03)||(bytenum&0x03) )	//must 4 bytes aligned.
		return -1;

	while( (DMA->ChEnReg&0x01)&&(waitchannel--) )
		;
	if(waitchannel<=0)
		return -1;
	
       temreg = 0x00000000+(0<<0)    //INT_EN, ch0 irq disable
       				    +(2<<1)      // DST_TR_WIDTH, des transfer width, should set to HSIZE, here is 010, means 32bit
	                    +(2<<4)      // SRC_TR_WIDTH, sor transfer width, should set to HSIZE, here is 010, means 32bit
					    +(0<<7)      // DINC, des addr increment, des is sram, so should set to 00, means to increase
	                    +(2<<9)      // SINC, sor addr increment, src is SPI, so should set to 1x, means no change 
					    +(0<<11)     // DEST_MSIZE, des burst length, set to 000 means 1 DST_TR_WIDTH per burst transcation
					    +(0<<14)     // SRC_MSIZE, sor burst length, set to 000 means 1 SOR_TR_WIDTH per burst transcation
	                    +(2<<20)     // TT_FC,transfer type and flow control,010 means peripheral to memory,dma is flow controller
	                    +(0<<23)     // DMS, des master select, 0 means ahb master 0
	                    +(0<<25)     // SMS, sor master select, 1 means ahb master 1
	                    +(0<<27)     // LLP_DST_EN, des block chaining enable, set to 0 disable it
	                    +(0<<28);    // LLP_SOR_EN, sor block chaining enable, set to 0 disable it


	DMA->SAR0 = (uint32_t)(&QSPI0->DATA);
	DMA->DAR0 = (uint32_t)dst_addr;
	DMA->CTL0_L = temreg;
	DMA->CTL0_H = 0x00000000+(bytenum/4)+(bytenum%4!=0);
	DMA->LLP0 = 0;
	DMA->CFG0_L = 0;
    if(QSPIptr == QSPI0){
        DMA->CFG0_H = 0x00000000 + (9 << 7) + (9 << 11);
    }else if(QSPIptr == QSPI1){
        DMA->CFG0_H = 0x00000000 + (11 << 7) + (11 << 11);
    }
	DMA->DmaCfgReg = 0x01;
	DMA->ChEnReg = 0x101;

    waitchannel = MAX_QSPI_DMA_BUSY_WATI;
    while (((DMA->ChEnReg & 0x01) || (QSPI_GetFlagStatus(QSPIptr, QSPI_STATUS_SPI_BUSY) == SET)) && (waitchannel--))
        ;
	
	if(waitchannel <= 0)
	{
	  return -3;
	}  		
	
	return 0;
}

/** @defgroup m407_EVAL_QSPI_Private_Defines
  * @{
  */   
#define MAX_BUSY_WAIT 0x00100000
/**
  * @}
  */ 

/** @defgroup m407_EVAL_QSPI_Private_Functions
  * @{
  */ 

/**
  * @brief  Initializes the QSPI controller and allocate the resource.
  * @param QSPIptr: the QUAD spi controller base address.
  * @param  qspi_clk_div: the QSPI clock Prescaler.
  * @param  internal_clk_div: the QSPI clock internal clock setting coefficient.  
  * @param  internal_clk_rate: the QSPI clock internal clock setting coefficient.
  * @retval 0: okay; else: fail.
  */
int quad_spi_flash_init(QSPI_TypeDef* QSPIptr,uint32_t rcc_clk_div,int internal_clk_div, int internal_clk_rate)
{
	volatile uint8_t status = 1;
	volatile uint8_t status2 = 1;
	volatile uint8_t status3;
	QSPI_InitTypeDef QSPI_InitStructure;

	QSPI_InitStructure.QSPI_CPOL = QSPI_CPOL_High;
	QSPI_InitStructure.QSPI_CPHA = QSPI_CPHA_2Edge;
	QSPI_InitStructure.QSPI_FirstBit = QSPI_FirstBit_MSB;
	//QSPI_InitStructure.QSPI_APB_QSPIClkDiv = qspi_clk_div;
	QSPI_InitStructure.QSPI_ClockDiv = (internal_clk_div<<8);
	QSPI_InitStructure.QSPI_ClockRate = internal_clk_rate;

    if(QSPIptr == QSPI0){
    	RCC->QUADSPI0CLKDIV = rcc_clk_div;
	    GPIO_SetPinMux(GPIO1, GPIO_Pin_1, GPIO_FUNCTION_1);
	    GPIO_SetPinMux(GPIO1, GPIO_Pin_2, GPIO_FUNCTION_1);
	    GPIO_SetPinMux(GPIO1, GPIO_Pin_4, GPIO_FUNCTION_1);
	    GPIO_SetPinMux(GPIO1, GPIO_Pin_5, GPIO_FUNCTION_1);

	    //QSPI0 is SPI mode, DAT2&DAT3 is pullup
	    GPIO_SetPinMux(GPIO1, GPIO_Pin_0, GPIO_FUNCTION_0);
	    GPIO_SetPinDir(GPIO1, GPIO_Pin_0, GPIO_Mode_OUT);
	    GPIO_SetPin(GPIO1, GPIO_Pin_0);
	
	    GPIO_SetPinMux(GPIO1, GPIO_Pin_3, GPIO_FUNCTION_0);
	    GPIO_SetPinDir(GPIO1, GPIO_Pin_3, GPIO_Mode_OUT);
	    GPIO_SetPin(GPIO1, GPIO_Pin_3);
			
			GPIO_ConfigDriver(GPIO1,GPIO_Pin_0,GPIO_DRIVER_1);
			GPIO_ConfigDriver(GPIO1,GPIO_Pin_3,GPIO_DRIVER_1);
			GPIO_ConfigDriver(GPIO1,GPIO_Pin_1,GPIO_DRIVER_1);
			GPIO_ConfigDriver(GPIO1,GPIO_Pin_2,GPIO_DRIVER_1);
			GPIO_ConfigDriver(GPIO1,GPIO_Pin_4,GPIO_DRIVER_1);
			GPIO_ConfigDriver(GPIO1,GPIO_Pin_5,GPIO_DRIVER_1);//12ma输出
    }else if(QSPIptr == QSPI1){
      RCC->QUADSPI1CLKDIV = rcc_clk_div;
	    GPIO_SetPinMux(GPIO0, GPIO_Pin_26, GPIO_FUNCTION_3);//gp3_2 d0
	    GPIO_SetPinMux(GPIO0, GPIO_Pin_27, GPIO_FUNCTION_3);//gp3_3 clk
	    GPIO_SetPinMux(GPIO0, GPIO_Pin_30, GPIO_FUNCTION_3);//gp3_6 d1
	    GPIO_SetPinMux(GPIO0, GPIO_Pin_31, GPIO_FUNCTION_3);//gp3_7 cs

	    //QSPI1 is SPI mode, DAT2&DAT3 is pullup
	    GPIO_SetPinMux(GPIO0, GPIO_Pin_28, GPIO_FUNCTION_0);//gp3_4 d3
	    GPIO_SetPinDir(GPIO0, GPIO_Pin_28, GPIO_Mode_OUT);
	    GPIO_SetPin(GPIO0, GPIO_Pin_28);
	
	    GPIO_SetPinMux(GPIO0, GPIO_Pin_29, GPIO_FUNCTION_0);//gp3_5 d2
	    GPIO_SetPinDir(GPIO0, GPIO_Pin_29, GPIO_Mode_OUT);
	    GPIO_SetPin(GPIO0, GPIO_Pin_29);
    }
	
    RCC_ResetAHBCLK(1 << AHBCLK_BIT_DMA);
    QSPI_HwInit(QSPIptr, &QSPI_InitStructure);
    return 0;
}

/**
  * @brief  start data write.  
  * @param QSPIptr: the QUAD spi controller base address.
  * @param  buf : the source address. 
  * @param  n : the bytes number.
  *  
  * @retval 0,okay; else, error.
  */
static int qspi_flash_write_buf(QSPI_TypeDef *QSPIptr, uint8_t *buf, int n)
{
	QSPI_DataInitTypeDef QSPI_DataInitStruct;

	QSPI_DataInitStruct.QSPI_DataLength = n;
	QSPI_DataInitStruct.QSPI_DUPLEX = QSPI_HalfDuplex;
	QSPI_DataInitStruct.QSPI_TransferDir = QSPI_Transfer_Write;

	QSPI_DMACmd(QSPIptr, ENABLE);
	QSPI_DataConfig(QSPIptr, &QSPI_DataInitStruct);
	if (start_quad_spi_dma_tx(QSPIptr,buf, n) != 0)
		return -1;
	QSPI_DMACmd(QSPIptr, DISABLE);
    return 0;		
}


/**
  * @brief  start data read.  
  * @param 	QSPIptr: the QUAD spi controller base address.
  * @param  buf : the target store address. 
  * @param  n : the bytes number.
  *  
  * @retval 0,okay; else, error.
  */

static int qspi_flash_read_buf(QSPI_TypeDef *QSPIptr, uint8_t *buf, int n)
{
	QSPI_DataInitTypeDef QSPI_DataInitStruct;

	QSPI_DataInitStruct.QSPI_DataLength = n;
	QSPI_DataInitStruct.QSPI_DUPLEX = QSPI_HalfDuplex;
	QSPI_DataInitStruct.QSPI_TransferDir = QSPI_Transfer_Read;

    QSPI_DMACmd(QSPIptr, ENABLE);
    QSPI_DataConfig(QSPIptr, &QSPI_DataInitStruct);
    if (start_quad_spi_dma_rx(QSPIptr, buf, n) != 0)
        return -1;
    QSPI_DMACmd(QSPIptr, DISABLE);
    return 0;	
}


__ALIGN4 static uint8_t qspi_cmd[4];
static int qspi_flash_send_cmd(QSPI_TypeDef *QSPIptr, uint8_t cmd)
{
    qspi_cmd[0] = cmd;
    return qspi_flash_write_buf(QSPIptr, qspi_cmd, 1);
}

__ALIGN4 static uint8_t qspi_addr[4];
static int qspi_flash_send_addr(QSPI_TypeDef *QSPIptr, uint32_t faddr)
{  
	if(_4ByteAddrMode){
        qspi_addr[0] = faddr >> 24;
        qspi_addr[1] = ((faddr >> 16) & 0xff);
        qspi_addr[2] = ((faddr >> 8) & 0xff);
        qspi_addr[3] = (faddr & 0xff);
        return qspi_flash_write_buf(QSPIptr, qspi_addr, 4);
    }else{
	    qspi_addr[0] = faddr>>16;
	    qspi_addr[1] = ((faddr>>8) & 0xff);
	    qspi_addr[2] = (faddr & 0xff);
        return qspi_flash_write_buf(QSPIptr, qspi_addr, 3);
    }
}


__ALIGN4 static uint8_t qspi_flash_status[4];
void qspi_flash_read_status1(QSPI_TypeDef *QSPIptr, char *status)
{
    QSPI_CS_Low(QSPIptr);
    qspi_flash_send_cmd(QSPIptr, QUAD_SPI_FLASH_CMD_READ_STATUS1);
    qspi_flash_read_buf(QSPIptr, qspi_flash_status, 4);
    *status = qspi_flash_status[0];
    QSPI_CS_High(QSPIptr);

    return ;
}

void qspi_flash_read_status2(QSPI_TypeDef *QSPIptr, char *status)
{
    QSPI_CS_Low(QSPIptr);
    qspi_flash_send_cmd(QSPIptr, QUAD_SPI_FLASH_CMD_READ_STATUS2);
    qspi_flash_read_buf(QSPIptr, qspi_flash_status, 4);
    *status = qspi_flash_status[0];
    QSPI_CS_High(QSPIptr);

    return ;
}

void qspi_flash_read_status3(QSPI_TypeDef *QSPIptr, char *status)
{
	QSPI_CS_Low(QSPIptr);
	qspi_flash_send_cmd(QSPIptr, QUAD_SPI_FLASH_CMD_READ_STATUS3);
	qspi_flash_read_buf(QSPIptr, qspi_flash_status, 4);
	*status = qspi_flash_status[0];
	QSPI_CS_High(QSPIptr);
	return ;
}

static void qspi_delay(volatile int time)
{
    while ( time )time--; 
}

int qspi_flash_read_ID(QSPI_TypeDef *QSPIptr, uint8_t *buf)
{
	int ret;

	QSPI_CS_Low(QSPIptr);
    qspi_flash_send_cmd(QSPIptr, QUAD_SPI_FLASH_CMD_READ_ID);
    ret = qspi_flash_read_buf(QSPIptr, buf, 4);
    QSPI_CS_High(QSPIptr);

	return ret;
}

/*
	status&0xC3全兼容:
	(1)ISSI		BP3~BP0
	(2)GD		BP4~BP0		当BP2~BP0为0时全部可写
	(3)ESMT		BP3~BP0
	(4)WB		TB,BP2~BP0	当BP2~BP0为0时全部可写
	(5)MXIC		BP3~BP0
*/
void qspi_flash_global_unprotect(QSPI_TypeDef* QSPIptr)
{
    volatile uint8_t status1 = 1;
    volatile uint8_t status2 = 1;

    qspi_flash_read_status1(QSPIptr, (char *)&status1);
    qspi_flash_read_status2(QSPIptr, (char *)&status2);

    qspi_flash_write_enable(QSPIptr, 1);

    QSPI_CS_Low(QSPIptr);
    qspi_flash_send_cmd(QSPIptr, QUAD_SPI_FLASH_CMD_WRITE_STATUS);
    qspi_cmd[0] = status1&0xC3;
    qspi_cmd[1] = status2;
    qspi_flash_write_buf(QSPIptr, qspi_cmd, 2);
    QSPI_CS_High(QSPIptr);

    status1 = 1;
    while (status1 & 1)
    {
        qspi_flash_read_status1(QSPIptr, (char *)&status1);
        qspi_delay(1000);
    }
		
    return ;
}

void qspi_flash_write_enable(QSPI_TypeDef *QSPIptr, int enable)
{
	int cmd = enable ? QUAD_SPI_FLASH_CMD_WRITE_ENABLE:QUAD_SPI_FLASH_CMD_WRITE_DISABLE;

	QSPI_CS_Low(QSPIptr);
	qspi_flash_send_cmd(QSPIptr, cmd);
	QSPI_CS_High(QSPIptr);

	return ;
}

//DMA一次只能发送1023字节
int qspi_flash_read_page(QSPI_TypeDef *QSPIptr, uint8_t *buf, uint32_t faddr, int count)
{
    int cmd = _4ByteAddrMode ? QUAD_SPI_FLASH_CMD_READ_WITH_4BYTE_ADDR : QUAD_SPI_FLASH_CMD_READ;

    QSPI_CS_Low(QSPIptr);
    qspi_flash_send_cmd(QSPIptr,cmd);
    qspi_flash_send_addr(QSPIptr, faddr);
    qspi_flash_read_buf(QSPIptr, buf, count);
    QSPI_CS_High(QSPIptr);  

    return count;
}

int qspi_flash_read(QSPI_TypeDef *QSPIptr, uint8_t *buf, uint32_t faddr, int count)
{
//    int ret=0;
	int remaincount = count;
	int countnum;
	do{
		countnum = (remaincount<=256)?remaincount:256;

		qspi_flash_read_page(QSPIptr, buf, faddr, countnum);
		remaincount -= countnum;
		buf += countnum;			
		faddr += countnum;
		//printf("start read flash\r\n");	
	}while(remaincount>0);
	
  return remaincount;
}

int qspi_flash_erase_block_4k(QSPI_TypeDef *QSPIptr, uint32_t faddr)
{
    int cmd = _4ByteAddrMode ? QUAD_SPI_FLASH_CMD_ERASE_4K_WITH_4BYTE_ADDR : QUAD_SPI_FLASH_CMD_ERASE_4K;
    volatile uint8_t status = 1;

    QSPI_CS_Low(QSPIptr);
    qspi_flash_send_cmd(QSPIptr, cmd);
    qspi_flash_send_addr(QSPIptr, faddr);
    QSPI_CS_High(QSPIptr);

    while (status & 1)
    {
        qspi_flash_read_status1(QSPIptr, (char *)&status);
        qspi_delay(1000);
    }

    return 0;
}

int qspi_flash_write_page(QSPI_TypeDef *QSPIptr, uint8_t *buf, uint32_t faddr, int count)
{
    volatile uint8_t status = 1;
    int cmd = _4ByteAddrMode ? QUAD_SPI_FLASH_CMD_WRITE_WITH_4BYTE_ADDR : QUAD_SPI_FLASH_CMD_WRITE;

    qspi_flash_write_enable(QSPIptr, 1);
    QSPI_CS_Low(QSPIptr);
    if (qspi_flash_send_cmd(QSPIptr, cmd))
        return -1;
    if (qspi_flash_send_addr(QSPIptr, faddr))
        return -1;
    if (qspi_flash_write_buf(QSPIptr, buf, count))
        return -1;
    QSPI_CS_High(QSPIptr);

    while (status & 1)
    {
        qspi_flash_read_status1(QSPIptr, (char *)&status);
        qspi_delay(1000);
    }

    return count;
}

int qspi_flash_write(QSPI_TypeDef *QSPIptr, uint8_t *buf, uint32_t faddr, int count)
{
    int i;
    int pages;
    int remains; // first page remains
    int w_bytes;

    qspi_flash_write_enable(QSPIptr, 1);
    qspi_flash_global_unprotect(QSPIptr);


    remains = (1<<QSPI_FLASH_PAGESHIFT) - (faddr & ((1<<QSPI_FLASH_PAGESHIFT)-1));

    if (count <= remains)
    {
        remains = count;
    }

    // count left
    count -= remains;

    // total pages going to write
    pages = ((count-1) >> QSPI_FLASH_PAGESHIFT) + 1; 

    // send first page remains
    qspi_flash_write_page(QSPIptr, buf, faddr, remains);

    faddr += remains;
    buf += remains;

    for (i = 0; i < pages ; i++)
    {
        if (count > (1<<QSPI_FLASH_PAGESHIFT))
        {
            w_bytes = (1<<QSPI_FLASH_PAGESHIFT);
        }
        else
        {
            w_bytes = count;
        }
        // send remain pages
        qspi_flash_write_page(QSPIptr, buf, faddr, w_bytes);

        faddr += w_bytes;
        buf += w_bytes;
        count -= w_bytes;
    }

    return count;
}

void qspi_flash_enableQE(QSPI_TypeDef *QSPIptr, uint8_t qeMask)
{
	volatile uint8_t status = 1;
	volatile uint8_t status2 = 1;
	qspi_flash_read_status2(QSPIptr, (char *)&status2);

	qspi_flash_write_enable(QSPIptr,1);
	QSPI_CS_Low(QSPIptr);
	qspi_flash_send_cmd(QSPIptr, QUAD_SPI_FLASH_CMD_WRITE_STATUS2);
	qspi_cmd[0] = status2|qeMask;
	qspi_flash_write_buf(QSPIptr, qspi_cmd, 1);
	QSPI_CS_High(QSPIptr);

	status = 1;
	while (status & 1){
		qspi_flash_read_status1(QSPIptr, (char *)&status);
		qspi_delay(1000);
	}	
}
//	qspi_cmd[0] = status3;
//	qspi_cmd[0]&=0x9f;
//	qspi_cmd[0]|=(dsMask<<5);
void qspi_flash_SetDriverStrength(QSPI_TypeDef *QSPIptr, uint8_t dsMask)
{
	volatile uint8_t status = 1;
	volatile uint8_t status3 = 1;
	dsMask&=0x03;
	qspi_flash_read_status3(QSPIptr, (char *)&status3);
	//printf("status3 0x%02x\r\n",status3);
	
	qspi_flash_write_enable(QSPIptr,1);
	
	QSPI_CS_Low(QSPIptr);
	qspi_flash_send_cmd(QSPIptr, QUAD_SPI_FLASH_CMD_WRITE_STATUS3);
	qspi_cmd[0] = status3;
	qspi_cmd[0]&=0x9f;
	qspi_cmd[0]|=(dsMask<<5);
	qspi_flash_write_buf(QSPIptr, qspi_cmd, 1);
	QSPI_CS_High(QSPIptr);

	status = 1;
	while (status & 1){
		qspi_flash_read_status1(QSPIptr, (char *)&status);
		qspi_delay(1000);
	}
	qspi_flash_read_status3(QSPIptr, (char *)&status3);
	//printf("status3 0x%02x\r\n",status3);
}

void qspi_flash_4Byte_address_enable(QSPI_TypeDef *QSPIptr, uint8_t enable)
{
    int cmd = enable ? QUAD_SPI_CMD_ENTER_4BYTE_ADDR_MODE : QUAD_SPI_CMD_EXIT_4BYTE_ADDR_MODE;
    _4ByteAddrMode = enable ? ENABLE : DISABLE;
    QSPI_CS_Low(QSPIptr);
    qspi_flash_send_cmd(QSPIptr, cmd);
    QSPI_CS_High(QSPIptr);
}


