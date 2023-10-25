#ifndef _lcdDriver_h
#define _lcdDriver_h
#include "gStdint.h"
#include "gReturn.h"
#include "lcdInterface.h"
#include "Y6_include_conf.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define  LCD_BG_OPEN()    GPIO1->DT_SET=BG_PIN//set bit      //LCD_BG 
#define  LCD_BG_CLOSE()   GPIO1->DT_CLR=BG_PIN//clear bit    //LCD_BG 

#define  LCD_RS_G()       GPIO1->DT_SET=GPIO_Pin_11//set bit     LCD_RS 
#define  LCD_RS_D()       GPIO1->DT_CLR=GPIO_Pin_11//clear bit   LCD_RS 

#define  LCD_CS_G()       CS_PORT->DT_SET = CS_PIN;
#define  LCD_CS_D()       CS_PORT->DT_CLR = CS_PIN;

#define  BEEP_OPEN()    GPIO0->DT_SET=BEEP_PIN//set bit      //BEEP 
#define  BEEP_CLOSE()   GPIO0->DT_CLR=BEEP_PIN//clear bit    //BEEP 

//Brush colors
#define WHITE       0xFFFF
#define BLACK       0x0000    
#define BLUE        0x001F  
#define BRED        0XF81F
#define GRED        0XFFE0
#define GBLUE       0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN       0XBC40 
#define BRRED       0XFC07 
#define GRAY        0X8430 
#define DARKBLUE    0X01CF 
#define LIGHTBLUE   0X7D7C   
#define GRAYBLUE    0X5458 
#define LIGHTGREEN  0X841F  
#define LGRAY       0XC618 
#define LGRAYBLUE   0XA651 
#define LBBLUE      0X2B12      
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                                                   
/*
*remake: Rough short delay, user LCD read/write timing
*/                                                   
#define  DELAY()   __NOP();__NOP();__NOP()
/*
*remake: External data interface
*/
#define LCD_WIDTH       WIDTH_DEF   
#define LCD_HEIGHT      HEIGHT_DEF	
#define GUI_LCD_LINEBUFFER_SIZE LCD_HEIGHT

#define DIR_HORIZONTAL  1
#define DIR_VERTICAL    0

#define LCD_LuminanceMax 100

#define LCDINTERFACE_DELAY_NOP()    //__nop();__nop();__nop();__nop()

#define Flash_Read_ByteMax          2000 //Bytes as a unit.  The maximum DMA transfer is 511 blocks (4 bytes per block). 
											//This value is less than 511 and less than LCD_SENDBUF_HALFWORD_MAX*2.
#define Lcd_SendBuf_HalfWord_Max    Flash_Read_ByteMax / 2  
extern  __align(4) gui_uint16  lcdSendBuff[2][Lcd_SendBuf_HalfWord_Max+2];

typedef struct  _LCD_DRIVER{   
		
	void       (*writeData)(gui_uint16 data);
	gui_uint16 (*readData)(void);
	void 	  (*writeCMD)(gui_uint16 cmd);
	void 		(*setcursor)(gui_uint16 Xpos, gui_uint16 Ypos, gui_uint16 Xepos, gui_uint16 Yepos);
	void    (*scan_dir)(Y6_LCD_SCAN dir);                                             	
	void 		(*open)(void);                                                            
	void 		(*close)(void);                                                            
	void 		(*scroll)(gui_uint16 sx,gui_uint16 sy,gui_uint16 ex,gui_uint16 ey);              
	void 		(*SetDim)(gui_uint8 pulse);
}LCD_DRIVER;  
extern const LCD_DRIVER Lcd_Driver; 

void LCD_CLS(uint16_t color);

#endif
