#include "Y6.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeReg(uint32_t addr, uint32_t value)
{
	*((uint32_t*)addr) = value;
}

uint32_t readReg(uint32_t addr)
{
	return *((uint32_t*)addr);
}

//以下3个接口:测试一个寄存器的值是不是某个值
//addr寄存器地址,val是正确值
void testReg32(uint32_t addr, uint32_t val)
{
	if(inl(addr) != val){
    	outl(addr, SIM_FLAG);
	}
}

void testReg16(uint32_t addr, uint16_t val)
{
	if(ins(addr) != val){
    	outl(addr, SIM_FLAG);
	}
}

void testReg8(uint32_t addr, uint8_t val)
{
	if(inb(addr) != val){
    	outl(addr, SIM_FLAG);
	}
}

//以下3个接口:测试一个寄存器的值某些bit是不是某个值
//addr寄存器地址，mask的某些bit是1表示测试这些bit,val是正确值
void testMask32(uint32_t addr, uint32_t mask, uint32_t val)
{
	if((inl(addr) & mask) != val){
    	outl(addr, SIM_FLAG);
	}
}

void testMask16(uint32_t addr, uint16_t mask, uint16_t val)
{
	if((ins(addr) & mask) != val){
    	outl(addr, SIM_FLAG);
	}
}

void testMask8(uint32_t addr, uint8_t mask, uint8_t val)
{
	if((inb(addr) & mask) != val){
    	outl(addr, SIM_FLAG);
	}
}

