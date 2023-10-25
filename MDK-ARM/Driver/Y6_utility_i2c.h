#ifndef  __Y6_UTILITY_I2C_H
#define  __Y6_UTILITY_I2C_H
#include <stdint.h>

typedef enum
{
  I2C_SPEED_STD,
  I2C_SPEED_FAST,
} I2CSpeedSel;

typedef enum
{
  I2C_GP0_A,
  I2C_GP0_B,
  I2C_GP7,
} I2CPinGroup;

int I2C_Configuration(I2CSpeedSel speed, I2CPinGroup pin_group);
int I2C_DmaWrite(uint8_t dev_addr, uint32_t internal_addr, int addr_size, uint8_t *buf,  int write_size);
int I2C_DmaRead(uint8_t dev_addr, uint32_t internal_addr, int addr_size, uint8_t *buf,  int read_size);
int I2C_Write(uint8_t dev_addr, uint32_t internal_addr, int addr_size, uint8_t *buf,  int write_size);
int I2C_Read(uint8_t dev_addr, uint32_t internal_addr, int addr_size, uint8_t *buf,  int read_size);
void i2c_test(void);
#endif //__Y6_UTILITY_I2C_H
