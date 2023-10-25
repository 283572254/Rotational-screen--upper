#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Y6_uart.h" 
#include "Y6_gpio.h" 
#include "Y6_rcc.h"	 
#include "misc.h"
#include "Y6_dma.h"
#include "Y6_wdg.h"
#include "Y6_qspi.h"	 
#include "Y6_eval_qspi.h"
#include "Y6_xip1.h"

void initXIP1(uint8_t addr4Bytes)
{
	qspi_flash_init(QSPI1, 4, QSPI_MASTER_MODE, 2, 0, QSPI1_GP3, 1);
	qspi_flash_quad_function_select(QSPI1, QUAD_ENABLE, 0x02);
	if(addr4Bytes){
		qspi_flash_4Byte_address_enable(QSPI1, ENABLE);
	}
	
  qspi_flash_init(QSPI1, 2, QSPI_MASTER_MODE, 2, 0, QSPI1_GP3, 1);
	QSPI_PinSwitch(QSPI1, 1);
	QSPI_ModeSet(QSPI1, QSPI_STD);

	if(addr4Bytes){
		QSPI1->XIP_READ_CMD = 0xEC;
		QSPI1->ADD_BYTE_LEN = 1;
	}else{
		QSPI1->XIP_READ_CMD = 0xEB;
		QSPI1->ADD_BYTE_LEN = 0;
	}

	QSPI1->DUMMY = 2;		
	QSPI1->START_ADDR = 0;		//QSPI1 = 0;
	QSPI1->CTRL2 = 0x0000;		
	QSPI1->BUSY_DLY = 0x00000101;
	//bit13 DMA_ENABLE=0
	QSPI_DMACmd(QSPI1, DISABLE);
	//bit26 WRITE
	QSPI1->CTRL0_CLR = 1<<26;
	//bit28 HALF_DUPLEX=1
	QSPI1->CTRL0_SET = 1<<28;
	//bit25 MEMAP=1
	QSPI1->CTRL0_SET = 0x0a000000;
	//ADDRESS_REMAP1
	RCC->ADDRESS_REMAP1 = 1;
}



