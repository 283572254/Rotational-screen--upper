#include "comInterface.h"
#include <stdint.h>
#define OUTPUT_BUFF_MAX               64//Output buffer size
#define INPUT_BUFF_MAX                255//Input buffer size

static uint8_t outputBuff[OUTPUT_BUFF_MAX];
static uint8_t inputBuff[INPUT_BUFF_MAX];

static uint32_t inputLocation=0;           //Output current position
static volatile uint8_t inputEndFlag=COM_RECEIVED_NO;//Whether the reception is completed

/*
*********************************************************************************************************************
*Function: returnOutputMaxLen returns the maximum size of the output buffer
*Entry parameter: None
*Export parameter: the maximum size of the buffer
*********************************************************************************************************************
*/
static uint32_t returnOutputMaxLen(void)
{
	return OUTPUT_BUFF_MAX;
}
/*
*********************************************************************************************************************
*Function: returnIutputMaxLen returns the maximum size of the input buffer
*Entry parameter: None
*Export parameter: the maximum size of the buffer
*********************************************************************************************************************
*/
static uint32_t returnIutputMaxLen(void)
{
	return INPUT_BUFF_MAX;
}
/*
*********************************************************************************************************************
* Function: returnOutputBuff Return output buffer
*Entry parameter: None
*Export parameter: first address of the buffer
*********************************************************************************************************************
*/
static uint8_t* returnOutputBuff(void)
{
	return outputBuff;
}
/*
*********************************************************************************************************************
*Function: returnInputBuff Return input buffer
*Entry parameter: None
*Export parameter: first address of the buffer
*********************************************************************************************************************
*/
static uint8_t* returnInputBuff(void)
{
	return inputBuff;
}
/*
*********************************************************************************************************************
*Function: returnInputLen Return input length
*Entry parameter: None
*Export parameter: length of input
*********************************************************************************************************************
*/
static uint32_t returnInputLen(void)
{
	return inputLocation;
}
/*
*********************************************************************************************************************
* Function: inputChar Input a character
*Entry parameter: c inputChar
*Export parameter: none
*********************************************************************************************************************
*/
static void inputChar(uint8_t c)
{
	inputBuff[inputLocation]=c;
	inputLocation++;
	if(inputLocation>=INPUT_BUFF_MAX)inputLocation=0;
}
/*
*********************************************************************************************************************
* Function: inputChar Input a character
*Entry parameter: c Input character
* len The length of the input
*Export parameter: none
*********************************************************************************************************************
*/
static void inputString(const uint8_t *c , uint32_t len)
{
	uint32_t rLen=len;
	uint32_t i;
	if(len>=INPUT_BUFF_MAX)rLen=INPUT_BUFF_MAX;
	for(i=0;i<rLen;i++){
		inputBuff[i]=c[i];
	}
}
/*
*********************************************************************************************************************
*Function: inputEnd Prompt for end of reception
*Entry parameter: None
*Export parameter: none
*********************************************************************************************************************
*/
static void inputEnd(void)
{
	inputEndFlag=COM_RECEIVED;
}
/*
*********************************************************************************************************************
*Function: getInputStatus Get input status
*Entry parameter: None
*Export parameter: none
*********************************************************************************************************************
*/
static uint8_t returnInputStatus(void)
{
	return inputEndFlag;
}
/*
*********************************************************************************************************************
* Function: clearOutput Clear the output buffer
*Entry parameter: None
*Export parameter: none
*********************************************************************************************************************
*/
static void clearOutput(void)
{
	uint32_t i;
	for (i = 0; i < OUTPUT_BUFF_MAX; i++)
	{
		outputBuff[i]=0;
	}
}
/*
*********************************************************************************************************************
*Function: clearIutput Clear input buffer
*Entry parameter: None
*Export parameter: none
*********************************************************************************************************************
*/
static void clearIutput(void)
{
	uint32_t i;
	for (i = 0; i < INPUT_BUFF_MAX; i++)
	{
		inputBuff[i]=0;
	}
	inputEndFlag=COM_RECEIVED_NO;
	inputLocation=0;
}
/*
*********************************************************************************************************************
*Structure Function interface for communication processing
*********************************************************************************************************************
*/
#include "systemUart.h"
const COM_DESCRIPTOR1 Com_Des={
	printChar,
	printString,
	returnOutputMaxLen,
	returnOutputBuff,
	returnIutputMaxLen,
	returnInputBuff,
	returnInputLen,
	returnInputStatus,
	inputChar,
	inputString,
	inputEnd,
	clearOutput,
	clearIutput,
};


extern gui_uint8 KeyVaule;
extern gui_uint8 LCD_Luminance;
extern gui_uint8 Mode;
extern gui_uint8 WindSpeed;
extern gui_uint8 WindDir;
extern gui_uint8 SetTemp;
extern gui_uint8 NoeTemp;
extern gui_uint8 TimeButton;
extern gui_uint8 SetTime;
extern gui_uint8 Trouble;


