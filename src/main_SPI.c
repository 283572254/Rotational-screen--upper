

/* Includes ------------------------------------------------------------------*/
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
#include "Y6_utility_usart.h"

__ALIGN4 static uint8_t spi_cmd[4];
static int spi_flash_send_cmd(QSPI_TypeDef* QSPIptr, uint8_t cmd)
{
  spi_cmd[0] = cmd;
  return SpiTX(QSPIptr, spi_cmd, 1);
}

int spi_flash_read_ID(QSPI_TypeDef* QSPIptr, uint8_t* buf)
{
  int ret;
  QSPI_CS_Low(QSPIptr);
  spi_flash_send_cmd(QSPIptr, QUAD_SPI_FLASH_CMD_READ_ID);
  ret = SpiRX(QSPIptr, buf, 4);
  QSPI_CS_High(QSPIptr);
  return ret;
}

__ALIGN4 static uint8_t spi_addr[4];
static int spi_flash_send_addr(QSPI_TypeDef* QSPIptr, uint32_t faddr)
{
  spi_addr[0] = ((faddr >> 16) & 0xff);
  spi_addr[1] = ((faddr >> 8) & 0xff);
  spi_addr[2] = (faddr & 0xff);
  return SpiTX(QSPIptr, spi_addr, 3);
}

int spi_flash_read(QSPI_TypeDef* QSPIptr, uint8_t* buf, uint32_t faddr, int count)
{
  int ret;
  QSPI_CS_Low(QSPIptr);
  spi_flash_send_cmd(QSPIptr, QUAD_SPI_FLASH_CMD_READ);
  spi_flash_send_addr(QSPIptr, faddr);
  ret = SpiRX(QSPIptr, buf, count);
  QSPI_CS_High(QSPIptr);
  return ret;
}

void spi_flash_write_enable(QSPI_TypeDef* QSPIptr, int enable)
{
  int cmd = enable ? QUAD_SPI_FLASH_CMD_WRITE_ENABLE : QUAD_SPI_FLASH_CMD_WRITE_DISABLE;
  QSPI_CS_Low(QSPIptr);
  spi_flash_send_cmd(QSPIptr, cmd);
  QSPI_CS_High(QSPIptr);
  return;
}

__ALIGN4 static uint8_t spi_flash_status[4];
void spi_flash_read_status1(QSPI_TypeDef* QSPIptr, char* status)
{
  QSPI_CS_Low(QSPIptr);
  spi_flash_send_cmd(QSPIptr, QUAD_SPI_FLASH_CMD_READ_STATUS1);
  SpiRX(QSPIptr, spi_flash_status, 4);
  *status = spi_flash_status[0];
  QSPI_CS_High(QSPIptr);

  return;
}

void spi_flash_read_status2(QSPI_TypeDef* QSPIptr, char* status)
{
  QSPI_CS_Low(QSPIptr);
  spi_flash_send_cmd(QSPIptr, QUAD_SPI_FLASH_CMD_READ_STATUS2);
  SpiRX(QSPIptr, spi_flash_status, 4);
  *status = spi_flash_status[0];
  QSPI_CS_High(QSPIptr);

  return;
}

void spi_flash_write_status(QSPI_TypeDef* QSPIptr, uint8_t* buf, int n)
{
  volatile uint8_t status = 1;
  spi_flash_write_enable(QSPIptr, 1);

  QSPI_CS_Low(QSPIptr);
  spi_flash_send_cmd(QSPIptr, QUAD_SPI_FLASH_CMD_WRITE_STATUS);
  SpiTX(QSPIptr, buf, n);
  QSPI_CS_High(QSPIptr);

  status = 1;
  while (status & 1) {
    spi_flash_read_status1(QSPIptr, (char*)&status);
    commonDelay(1000);
  }
}

void spi_flash_global_unprotect(QSPI_TypeDef* QSPIptr)
{
  volatile uint8_t status1 = 1;
  volatile uint8_t status2 = 1;

  spi_flash_read_status1(QSPIptr, (char*)&status1);
  spi_flash_read_status2(QSPIptr, (char*)&status2);
  spi_flash_status[0] = status1 & 0xC3;
  spi_flash_status[1] = status2;
  spi_flash_write_status(QSPIptr, spi_flash_status, 2);
}

int spi_flash_write_page(QSPI_TypeDef* QSPIptr, uint8_t* buf, uint32_t faddr, int count)
{
  volatile uint8_t status = 1;

  spi_flash_write_enable(QSPIptr, 1);
  QSPI_CS_Low(QSPIptr);
  if (spi_flash_send_cmd(QSPIptr, QUAD_SPI_FLASH_CMD_WRITE)) {
    printf("spi_flash_write_page,line=%d\r\n", __LINE__);
    return -1;
  }
  if (spi_flash_send_addr(QSPIptr, faddr)) {
    printf("spi_flash_write_page,line=%d\r\n", __LINE__);
    return -1;
  }
  if (SpiTX(QSPIptr, buf, count)) {
    printf("spi_flash_write_page,line=%d\r\n", __LINE__);
    return -1;
  }
  QSPI_CS_High(QSPIptr);

  while (status & 1) {
    spi_flash_read_status1(QSPIptr, (char*)&status);
    commonDelay(1000);
  }

  return count;
}

int spi_flash_erase_block_64k(QSPI_TypeDef* QSPIptr, uint32_t faddr)
{
  volatile uint8_t status = 1;

  spi_flash_write_enable(QSPIptr, 1);

  QSPI_CS_Low(QSPIptr);
  spi_flash_send_cmd(QSPIptr, QUAD_SPI_FLASH_CMD_ERASE_64K);
  spi_flash_send_addr(QSPIptr, faddr);
  QSPI_CS_High(QSPIptr);

  while (status & 1) {
    spi_flash_read_status1(QSPIptr, (char*)&status);
    commonDelay(1000);
  }

  return 0;
}

int spi_flash_write(QSPI_TypeDef* QSPIptr, uint8_t* buf, uint32_t faddr, int count)
{
  int i;
  int pages;
  int remains; // first page remains
  int w_bytes;

  spi_flash_write_enable(QSPIptr, 1);
  spi_flash_global_unprotect(QSPIptr);

  remains = (1 << QSPI_FLASH_PAGESHIFT) - (faddr & ((1 << QSPI_FLASH_PAGESHIFT) - 1));

  if (count <= remains) {
    remains = count;
  }

  // count left
  count -= remains;

  // total pages going to write
  pages = ((count - 1) >> QSPI_FLASH_PAGESHIFT) + 1;

  // send first page remains
  spi_flash_write_page(QSPIptr, buf, faddr, remains);

  faddr += remains;
  buf += remains;

  for (i = 0; i < pages; i++) {
    if (count > (1 << QSPI_FLASH_PAGESHIFT)) {
      w_bytes = (1 << QSPI_FLASH_PAGESHIFT);
    } else {
      w_bytes = count;
    }
    // send remain pages
    spi_flash_write_page(QSPIptr, buf, faddr, w_bytes);

    faddr += w_bytes;
    buf += w_bytes;
    count -= w_bytes;
  }

  return count;
}

__ALIGN4 static uint8_t spi_flash_status[4];
void spi_flash_quad_function_select(QSPI_TypeDef* QSPIptr, QUADfuncSelect sel, uint8_t qeMask)
{
  volatile uint8_t status = 1;
  volatile uint8_t status2 = 1;

  spi_flash_read_status1(QSPIptr, (char*)&status);
  spi_flash_read_status2(QSPIptr, (char*)&status2);
  spi_flash_status[0] = status;
  if (sel == QUAD_ENABLE)
    spi_flash_status[1] = status2 | qeMask;
  else
    spi_flash_status[1] = status2 & (~qeMask);
  spi_flash_write_status(QSPIptr, spi_flash_status, 2);
}

static int spi_flash_send_dummy(QSPI_TypeDef* QSPIptr, uint32_t count)
{
  spi_addr[0] = (uint8_t)0;
  spi_addr[1] = (uint8_t)0;
  spi_addr[2] = (uint8_t)0;
  spi_addr[3] = (uint8_t)0;

  return SpiTX(QSPIptr, spi_addr, count);
}

int spi_flash_quad_io_read_page(QSPI_TypeDef* QSPIptr, uint8_t* buf, uint32_t faddr, int count)
{
  QSPI_PinSwitch(QSPIptr, 1); //only after QUAD_ENABLE
  QSPI_CS_Low(QSPIptr);
  spi_flash_send_cmd(QSPIptr, QUAD_SPI_CMD_FAST_READ_QUAD_IO); /*switch the controller to quad function*/
  QSPI_ModeSet(QSPIptr, QSPI_QUAD);
  spi_flash_send_addr(QSPIptr, faddr);
  spi_flash_send_dummy(QSPIptr, 3);
  SpiRX(QSPIptr, buf, count);
  QSPI_CS_High(QSPIptr);

  QSPI_ModeSet(QSPIptr, QSPI_STD); /*change the controller to STD*/
  QSPI_PinSwitch(QSPIptr, 0);      //just before QUAD_DISABLE
  return 0;
}

int spi_flash_quad_io_read(QSPI_TypeDef* QSPIptr, uint8_t* buf, uint32_t faddr, int count)
{
  int i;
  int pages;
  int remains; // first page remains
  int w_bytes;

  remains = (1 << QSPI_FLASH_PAGESHIFT) - (faddr & ((1 << QSPI_FLASH_PAGESHIFT) - 1));
  if (count <= remains) {
    remains = count;
  }

  // count left
  count -= remains;
  // total pages going to write
  pages = ((count - 1) >> QSPI_FLASH_PAGESHIFT) + 1;
  // send first page remains
  spi_flash_quad_io_read_page(QSPIptr, buf, faddr, remains);

  faddr += remains;
  buf += remains;
  for (i = 0; i < pages; i++) {
    if (count > (1 << QSPI_FLASH_PAGESHIFT)) {
      w_bytes = (1 << QSPI_FLASH_PAGESHIFT);
    } else {
      w_bytes = count;
    }
    // send remain pages
    spi_flash_quad_io_read_page(QSPIptr, buf, faddr, w_bytes);

    faddr += w_bytes;
    buf += w_bytes;
    count -= w_bytes;
  }
  return 0;
}

int spi_flash_quad_io_write_page(QSPI_TypeDef* QSPIptr, uint8_t* buf, uint32_t faddr, int count)
{
  volatile uint8_t status = 1;

  QSPI_PinSwitch(QSPIptr, 1); //only after QUAD_ENABLE
  spi_flash_write_enable(QSPIptr, 1);
  QSPI_CS_Low(QSPIptr);
  spi_flash_send_cmd(QSPIptr, QUAD_SPI_FLASH_CMD_QUAD_WRITE);
  spi_flash_send_addr(QSPIptr, faddr);
  QSPI_ModeSet(QSPIptr, QSPI_QUAD);
  SpiTX(QSPIptr, buf, count);
  QSPI_CS_High(QSPIptr);
  QSPI_ModeSet(QSPIptr, QSPI_STD);
  QSPI_PinSwitch(QSPIptr, 0); //only after QUAD_ENABLE

  while (status & 1) {
    spi_flash_read_status1(QSPIptr, (char*)&status);
    commonDelay(1000);
  }

  return count;
}

int spi_flash_quad_io_write(QSPI_TypeDef* QSPIptr, uint8_t* buf, uint32_t faddr, int count)
{
  int i;
  int pages;
  int remains; // first page remains
  int w_bytes;

  spi_flash_global_unprotect(QSPIptr);
  remains = (1 << QSPI_FLASH_PAGESHIFT) - (faddr & ((1 << QSPI_FLASH_PAGESHIFT) - 1)); //faddr最后一个page剩余字节
  if (count <= remains) {
    remains = count;
  }

  // count left
  count -= remains;
  // total pages going to write
  pages = ((count - 1) >> QSPI_FLASH_PAGESHIFT) + 1;
  // send first page remains
  spi_flash_quad_io_write_page(QSPIptr, buf, faddr, remains);

  faddr += remains;
  buf += remains;
  for (i = 0; i < pages; i++) {
    if (count > (1 << QSPI_FLASH_PAGESHIFT)) {
      w_bytes = (1 << QSPI_FLASH_PAGESHIFT);
    } else {
      w_bytes = count;
    }
    // send remain pages
    spi_flash_quad_io_write_page(QSPIptr, buf, faddr, w_bytes);

    faddr += w_bytes;
    buf += w_bytes;
    count -= w_bytes;
  }
  return 0;
}

#define TEST_BYTES 256
__align(4) static uint8_t wdatabuffer[TEST_BYTES] = { 0 };
__align(4) static uint8_t rdatabuffer[TEST_BYTES] = { 0 };
#define QSPIx QSPI1
#define QSPI_MODE QSPI_QUAD //QSPI_STD //QSPI_QUAD
#define WRITE_VAL									(0x2)

#define TEST2_BYTES 4
static uint8_t wbuffer[TEST2_BYTES] = { 0 };
static uint8_t rbuffer[TEST2_BYTES] = { 0 };

void spi_flash_demo(QSPI_TypeDef* QSPIptr)
{
  //****SPI Function test start//
  int i, j;
  volatile uint8_t status;
  volatile uint8_t cmd[2];

  if (QSPIx == QSPI0) {
    qspi_flash_init(QSPIptr, 8, QSPI_MASTER_MODE, 2, 0, QSPI0_GP4, 1);
  } else if (QSPIx == QSPI1) {
    qspi_flash_init(QSPIptr, 8, QSPI_MASTER_MODE, 2, 0, QSPI1_GP3, 1);
  } else {
    qspi_flash_init(QSPIptr, 8, QSPI_MASTER_MODE, 2, 0, QSPI2_GP5, 1);
  }
  QSPI_DMACmd(QSPIptr, ENABLE); //DMA enable,can set the FIFO size as 16 bytes,default only has 4 bytes

#if 1
  //read id
  for (i = 0; i < 10; i++)
    *(wdatabuffer + i) = 0xa5;

  if (spi_flash_read_ID(QSPIptr, wdatabuffer)) {
    printf("error!\r\n");
  }
  printf("flash JEDEC ID: %2x %2x %2x %2x\r\n", *wdatabuffer, *(wdatabuffer + 1), *(wdatabuffer + 2), *(wdatabuffer + 3));

  for (i = 0; i < TEST_BYTES; i++)
    *(wdatabuffer + i) = ((i + WRITE_VAL) % 256);

  //erase flash
  spi_flash_global_unprotect(QSPIptr);
  spi_flash_erase_block_64k(QSPIptr, 0); //Must be done before write

  //write flash
  if (QSPI_MODE == QSPI_STD) {
    spi_flash_write(QSPIptr, wdatabuffer, 0, TEST_BYTES);
  } else if (QSPI_MODE == QSPI_QUAD) {
    spi_flash_quad_io_write(QSPIptr, wdatabuffer, 0x0, TEST_BYTES);
  }
  commonDelay(40000);

  //read flash
  if (QSPI_MODE == QSPI_STD) {
    spi_flash_read(QSPIptr, rdatabuffer, 0, TEST_BYTES);
  } else if (QSPI_MODE == QSPI_QUAD) {
    spi_flash_quad_function_select(QSPIptr, QUAD_ENABLE, 0x02); //ESMT needn't it
    spi_flash_quad_io_read(QSPIptr, rdatabuffer, 0, TEST_BYTES);
    spi_flash_quad_function_select(QSPIptr, QUAD_DISABLE, 0x02);
  }
  commonDelay(40000);

  //compare result
  for (i = 0; i < TEST_BYTES; i++) {
    if (wdatabuffer[i] != rdatabuffer[i]) {
      outl(0xdeaddead, SIM_FLAG);
      while (1)
        ;
    }
  }
  outl(0x5555aaaa, SIM_FLAG);
#else
  //增量读写测试
  spi_flash_global_unprotect(QSPIptr);
  spi_flash_erase_block_64k(QSPIptr, 0); //Must be done before write
  for (i = TEST_BYTES; i < TEST_BYTES * 3;) {
    for (j = 0; j < TEST2_BYTES; j++) {
      *(wbuffer + j) = ((i + 0x0a) % 256);
    }
    spi_flash_write(QSPIptr, wbuffer, i, 4);
    spi_flash_read(QSPIptr, rbuffer, i, 4);
    if (memcmp(wbuffer, rbuffer, 4) != 0) {
      printf("i=%d,read buffer,r[0]=%d,r[1]=%d,r[2]=%d,r[3]=%d\r\n", i, rbuffer[0], rbuffer[1], rbuffer[2], rbuffer[3]);
      printf("write buffer,r[0]=%d,r[1]=%d,r[2]=%d,r[3]=%d\r\n", wbuffer[0], wbuffer[1], wbuffer[2], wbuffer[3]);
      goto err;
    }
    i += 4;
  }
  printf("test ok\r\n");
  goto ok;
err:
  printf("test fail\r\n");
#endif
  while (1)
    ;
}

//#define write_reg(p,v) *(volatile uint32_t *) (p) = (v)

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main()
{
  //RCC->MAINCLKSEL = 2;
  //RCC->MAINCLKUEN = 0;
  //RCC->MAINCLKUEN = 1;

  UART_Configuration(UART1, 115200, UART1_GP2);
  printf("\r\r\n-----------------Y6 Standard Peripheral Library Driver-----------------\r\r\n");

  spi_flash_demo(QSPIx); //qspi 非dma读写

  while (1) {
    ;
  }
}
