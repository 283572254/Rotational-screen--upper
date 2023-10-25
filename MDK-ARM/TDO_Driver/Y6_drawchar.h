#ifndef _Y6_drawchar_h
#define _Y6_drawchar_h
#include "stdint.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /* Function module: Character drawing module (currently only support GB2312 encoding mode, please switch KEIL's encoding to GB2312) (using foreground color for drawing)
 * Realized functions: 1. disp char information definition
 * 2. use the system font for string drawing, only ASCII strings can be drawn
 *
 *
 * Written by: TDO LCD Application development team
 *Written: 2019-7-23
 * Test by: TDO LCD Application development team
 * Testing time: 2019-7-23
 * Version number: V1.01_2019-7-23
 *Version Description.
 *                              
 * Function list
 *
 *V1.01: Legacy issues: the word model may have some problems, resulting in the display is not very beautiful, spacing, character display position problems.
 * For example, the Chinese character 一 should be centered on the top, but the result is completely centered on the top. Now it is forced to be aligned at the bottom.
 *V1.01
 *V1.01: Function implementation
 *
 *V1.02.
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _Y6_SYSTEM_FONTLIB{
	
	uint16_t width;    
	uint16_t height;  
	const uint8_t  *data;    
}Y6_SYSTEM_FONTLIB; 

extern const Y6_SYSTEM_FONTLIB Y6_FontLib_ASCII_1616;

//1、disp char信息定义
typedef struct _Y6_DISPCHAR_MSG{
	uint16_t fontLibId;                              
	uint8_t  xAlign;                                  //Horizontal alignment mode
	uint8_t  yAlign;                                  //
	uint8_t  isPassword;                              //Whether to display by password
	uint8_t  isDr;                                    //Whether to display line feeds
	uint16_t sx;
	uint16_t sy;                                      //Starting point coordinates
	uint16_t ex;
	uint16_t ey;                                      //End point coordinates
	uint8_t  backMode;                                //
	uint16_t picid;                                   //
	const char* data;                                 //String to be displayed
}Y6_DISPCHAR_MSG;
typedef Y6_DISPCHAR_MSG*  pY6_DISPCHAR_MSG;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//2、Use the system font for string drawing, only ASCII strings can be drawn
void Y6_gui_dispCharUseSystemFontLib(uint16_t x,uint16_t y,const char *c);
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//文本支持的对齐方式
#define Y6_CHARALIGN_X_L                              0//Left Alignment
#define Y6_CHARALIGN_X_C                              1//
#define Y6_CHARALIGN_X_R                              2//
#define Y6_CHARALIGN_Y_T                              0//
#define Y6_CHARALIGN_Y_C                              1//
#define Y6_CHARALIGN_Y_B                              2//
#endif
