#ifndef _SystemUart_h
#define _SystemUart_h
//#include "typedefine.h"
//#include "command.h"
#include "Y6.h"



void SystemUart_Init(uint32_t BaudRate);
void SystemUart2_Init(uint32_t BaudRate);
void SENDTEST( uint8_t *c,uint32_t len);
void printString(uint8_t *c,uint32_t len);
void printChar(uint8_t c);

#endif
