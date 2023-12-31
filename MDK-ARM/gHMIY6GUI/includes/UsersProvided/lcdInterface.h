#ifndef _lcdInterface_h
#define _lcdInterface_h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Functional module: lcd interface file
 * Implemented functions.
              
 * List of functions
 *
 *V1.01: Function Implementation
 *
 *V1.02.
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "gStdint.h"
#include "gWidgetInfo.h"

#ifdef __cplusplus
 extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *The basic parameters used by LCD
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _LCD_PARAMETER{
	gui_uint16 width;					
	gui_uint16 height;					
	gui_color  backColor;				
	gui_color  fontcolor;				
	gui_uint8  *drawBuff;				
	gui_uint32  buffSize;				
}LCD_PARAMETER;
typedef LCD_PARAMETER* pLCD_PARAMETER;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *The basic interface used by LCD
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _LCD_DESCRIPTOR{
	void (*drawPoint)(gui_uint16 x,gui_uint16 y);
	gui_color (*readPoint)(gui_uint16 x,gui_uint16 y);
	void (*fill)(gui_uint16 sx,gui_uint16 sy,gui_uint16 ex,gui_uint16 ey);
	void (*fillUseOneData)(LCD_POSITION sPos,LCD_POSITION ePos,const gui_color Data,gui_uint32 WriteCount);
	void (*fillUseContinuousData)(LCD_POSITION sPos,const gui_color* Data,gui_uint16 dataWidth,gui_uint16 dataHeight);
	void (*fillUsePartContinuousData)(const gui_color* DataBase,gui_uint16 WidthOffset,WIDGET_LOCATION dispLoc,LCD_POSITION dataPos);
	gui_uint16 (*fillUseContinuousDataSplitBit)(const gui_uint8* DataBase,gui_uint16 CharWidthOffset,WIDGET_LOCATION dispLoc);
	void (*clear)(void);
}LCD_DESCRIPTOR;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *The library will use the LCD interface declaration ------- the definition of this part of the thing the user needs to implement it themselves
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern 	      LCD_PARAMETER lcdPara;
extern const  LCD_DESCRIPTOR Lcd_Des;


#ifdef __cplusplus
}
#endif

#endif
