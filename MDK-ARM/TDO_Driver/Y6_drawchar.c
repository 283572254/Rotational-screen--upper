#include "Y6_drawchar.h"
#include "stdio.h"
#include "lcdInterface.h"
#include "gWidgetInfo.h"
#include "guiConfig.h"

 extern const uint8_t Y6fontAscii_1616[];
const Y6_SYSTEM_FONTLIB Y6_FontLib_ASCII_1616={
	16,                    //w
	16,                    //h
	&Y6fontAscii_1616[0]     //
};
/*
*********************************************************************************************************************
* Function: gui_dispChar draws a string using the internal ASCII font, external call, does not support line feed display
* Entry parameters: x, the x starting coordinate of the character to be drawn
* y, the y starting point of the control character
* c, the first address of the drawn string
* exit parameter: none
*********************************************************************************************************************
*/
void Y6_gui_dispCharUseSystemFontLib(uint16_t x,uint16_t y,const char *c)
{
	 
	uint16_t x_start=x;
	uint16_t y_start=y;
	uint16_t offset=Y6_FontLib_ASCII_1616.width/8;


	if(Y6_FontLib_ASCII_1616.width%8)offset++;
	while(*c!=0x00){
		if((x_start+Y6_FontLib_ASCII_1616.width)>lcdPara.width){
			//If the horizontal exceeds the maximum display area, then display a line break
			y_start+=Y6_FontLib_ASCII_1616.height;
			x_start=x;
		}
		if((y_start+Y6_FontLib_ASCII_1616.height)>lcdPara.height){
			//If you go beyond the vertical, you have to end the string drawing
			break;
		}
		if((*c==0x0a)|(*c==0x0d)){
			y_start+=Y6_FontLib_ASCII_1616.height;//line break
			x_start=x;
		}
		else if(*c==0x20){
			//Drawing of empty spaces
			LCD_POSITION sPos={x_start,y_start};
			LCD_POSITION ePos={x_start+Y6_FontLib_ASCII_1616.width-1,y_start+Y6_FontLib_ASCII_1616.height-1};
			Lcd_Des.fillUseOneData(sPos,ePos,lcdPara.backColor,Y6_FontLib_ASCII_1616.width*Y6_FontLib_ASCII_1616.height);
			x_start+=Y6_FontLib_ASCII_1616.width>>1;//Spaces only take up half the width of the word pattern
		}
		else if((*c>='!')&(*c<='~')){
			//Draw normal characters
			printf("%c",*c);
			WIDGET_LOCATION dispLoc={x_start,y_start,Y6_FontLib_ASCII_1616.width,Y6_FontLib_ASCII_1616.height};
			uint16_t needWidth=Lcd_Des.fillUseContinuousDataSplitBit(&Y6_FontLib_ASCII_1616.data[(*c)*offset*Y6_FontLib_ASCII_1616.height],offset,dispLoc);
			x_start=x_start+needWidth+CHAR_WIDTH_MAX;
		}
		else {
			//Ignore unrecognized characters			
		}
		c++;
	}
}
 
