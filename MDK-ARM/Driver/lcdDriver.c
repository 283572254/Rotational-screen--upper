#include "lcdDriver.h"
#include "systemheart.h"
#include "stdio.h"
#include "lcdinterface.h"
#include "Y6_gpio.h"
#include "QspiDMA.h"
#include "lcdInit.h"
#include "pwm.h"
#include "Y6_include_conf.h"

static __align(4) uint8_t  lcdSendBuff1[4];
#define LCDDRIVER_DELAY_NOP()     //__nop();__nop();__nop();__nop()
__align(4) gui_uint16  lcdSendBuff[2][Lcd_SendBuf_HalfWord_Max+2];



LCD_PARAMETER lcdPara={
	LCD_WIDTH,                          //LCD WIDTH
	LCD_HEIGHT,                         //LCD Height
	BLACK,                              //LCD Background color
	WHITE,                              //LCD  Foreground color
	(gui_uint8 *)lcdSendBuff,
	Flash_Read_ByteMax*2	
};

static uint16_t LCD_Read_DATA(void)
{
	return 0;
}

static void LCD_Write_DATA(uint16_t data)
{
	LCD_RS_G();
	LCD_CS_D();
	lcdSendBuff1[0] = data;
	QSPIDMA_SendBytes(LCD_QSPI , LCD_QSPIDMA_SEND_CHANNEL , lcdSendBuff1 , 1);
	QSPIDMA_WaitEnd(LCD_QSPI , LCD_QSPIDMA_SEND_CHANNEL);
	LCD_CS_G()
}

static void LCD_Write_CMD(uint16_t cmd)
{
	LCD_RS_D();
	LCD_CS_D();
	lcdSendBuff1[0] = cmd;
	QSPIDMA_SendBytes(LCD_QSPI , LCD_QSPIDMA_SEND_CHANNEL , lcdSendBuff1 , 1);
	QSPIDMA_WaitEnd(LCD_QSPI , LCD_QSPIDMA_SEND_CHANNEL);
	LCD_RS_G();
	LCD_CS_G()
}

/*
*********************************************************************************************************************
*Function£º LCD_WriteReg, LCD write the value of a register
*Parameters£º
*Return £ºNULL
*********************************************************************************************************************
*/
static void LCD_WriteReg(uint16_t LCD_Reg,uint16_t LCD_RegValue)
{	
	LCD_Write_CMD(LCD_Reg);  
	LCD_Write_DATA(LCD_RegValue);	    		 
}

static void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos, uint16_t Xepos, uint16_t Yepos)
{	    
	LCD_Write_CMD(0X2A); 
	LCD_Write_DATA(Xpos>>8);LCD_Write_DATA(Xpos&0XFF);
	LCD_Write_DATA(Xepos>>8);LCD_Write_DATA(Xepos&0XFF); 		
	LCD_Write_CMD(0X2B); 
	LCD_Write_DATA(Ypos>>8);LCD_Write_DATA((Ypos)&0XFF); 		
	LCD_Write_DATA(Yepos>>8);LCD_Write_DATA((Yepos)&0XFF); 	
} 

static void LCD_DisplayOn(void)
{					   
	LCD_Write_CMD(0x29);
}	

static void LCD_DisplayOff(void)
{	   
	LCD_Write_CMD(0x28);
}  

static void LCD_Scan_Dir(Y6_LCD_SCAN dir)
{
	 uint16_t width_x=lcdPara.width;

 	switch(dir)
	{
		case Y6_DIR_HORIZONTAL:				
			LCD_WriteReg(0x36,VALUE_HOR); //Horizontal Screen
			lcdPara.width=lcdPara.height;
			lcdPara.height=width_x;
		break;
		case Y6_HOR_DOWN_SCR:
			LCD_WriteReg(0x36,VALUE_HOR_DOWN);
			lcdPara.width=lcdPara.height;
			lcdPara.height=width_x;	
		break;
		case Y6_DIR_VERTICAL:
			LCD_WriteReg(0x36,VALUE_VER);//  vertical screen
			lcdPara.width=width_x;
			lcdPara.height=lcdPara.height;
		break;
		case Y6_VER_DOWN_SCR:
			LCD_WriteReg(0x36,VALUE_VER_DOWN);
			lcdPara.width=width_x;
			lcdPara.height=lcdPara.height;
		break;
		default:
		break;
	}
} 
/*
*********************************************************************************************************************
*Function£ºLCD_Scroll£¬Set scrolling area
*Parameters£ºsx sy   Starting point coordinates
*            ex ey   End point coordinates
*Return : null
*********************************************************************************************************************
*/
static void LCD_Scroll(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey)
{
	uint16_t y_offset=sx-ex;
	LCD_Write_CMD(0x33);
	LCD_Write_DATA(sx>>8);LCD_Write_DATA(sx&0XFF);
	LCD_Write_DATA(y_offset>>8);LCD_Write_DATA(y_offset&0XFF);
	LCD_Write_DATA(ey>>8);LCD_Write_DATA(ey&0XFF);
	LCD_Write_CMD(0x37);
	LCD_Write_DATA(ex>>8);LCD_Write_DATA(ex&0XFF);
}

/*
*********************************************************************************************************************
*Function£ºLCD_CLS£¬Specify color to clear screen
*Parameters£ºsx sy    Starting point coordinates
*          ex ey   End point coordinates
*return£ºnull
*********************************************************************************************************************
*/
void LCD_CLS(uint16_t color)
{
	uint32_t totalpoint=lcdPara.width;
	totalpoint*=lcdPara.height; 			 
	LCD_POSITION sPos={0,0};
	LCD_POSITION ePos={lcdPara.width-1,lcdPara.height-1};
 	Lcd_Des.fillUseOneData(sPos,ePos, color,totalpoint);
}


const LCD_DRIVER Lcd_Driver={   
	LCD_Write_DATA,
	LCD_Read_DATA,
	LCD_Write_CMD, 			
	LCD_SetCursor,       //LCD  Set the cursor start and end positions
	LCD_Scan_Dir,        //LCD Scanning direction
	LCD_DisplayOn,
	LCD_DisplayOff,
	LCD_Scroll,
	SetPwm
};	 
