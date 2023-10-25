#ifndef _comInterface_h
#define _comInterface_h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Functional module: Communication interface definition
 * Achieved functions: 1.
 
 *                              
 * Interface support Read/write function Command support 
 *
 *V1.01: Function implementation Function implementation ok 2019/07/04
 *
 *V1.02.
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "gStdint.h"
#include "gReturn.h"
#include <stdint.h>


#define COM_RECEIVED_NO                 0//Not received
#define COM_RECEIVED                    1//
typedef struct _COM_DESCRIPTOR1{
/* Definition of interfaces that should be provided by the driver layer */
	void  (*outputChar)(uint8_t c);
	void  (*outputString)( uint8_t *c , uint32_t len);

	/*Definition of interfaces that should be called by the driver layer*/
	uint32_t(*getOutputBuffMaxLen)(void);
	uint8_t* (* getOutputBuff)(void);
	uint32_t(*getInputBuffMaxLen)(void);
	uint8_t* (* getInputBuff)(void);
	uint32_t (*getInputLen)(void);
	uint8_t  (*getInputStatus)(void);

	void  (*inputChar)(uint8_t c);
	void  (*inputString)(const uint8_t *c , uint32_t len);
	void  (*inputEnd)(void);

	void  (*clearOutputBuff)(void);
	void  (*clearInputBuff)(void);
}COM_DESCRIPTOR1;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Communication port function descriptors
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _COM_DESCRIPTOR{
	
	void  (*write)( uint8_t *c , uint32_t len);
	
	void  (*read)(const char *c , gui_uint32 len);
}COM_DESCRIPTOR;

extern const COM_DESCRIPTOR1 Com_Des;
extern const COM_DESCRIPTOR DebugCom_Des;

#endif
