#include "Y6_drawFigure.h"
#include "lcdInterface.h"
 #include "stdint.h"
#include "stdio.h"
#include "gWidgetInfo.h"
/*
*********************************************************************************************************************
* Function: LCD_DrawPoint, LCD draws a point, using the specified color
*Entry parameters: x,y:coordinates
*Exit parameter: None
*********************************************************************************************************************
*/ 
static void LCD_DrawPoint_color(uint16_t x,uint16_t y,const uint16_t color)
{
	LCD_POSITION sPos={x,y};
	LCD_POSITION ePos={x,y};

	 Lcd_Des.fillUseOneData(sPos,ePos,color,1);	
}

static void LCD_Fill_color_old(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
{          
	uint32_t xlen=ex-sx+1;
	uint32_t ylen=ey-sy+1; 
	LCD_POSITION sPos={sx,sy};
	LCD_POSITION ePos={ex,ey};
	Lcd_Des.fillUseOneData(sPos,ePos,color,xlen*ylen);
}


static void LCD_Fill_color(int x0,int y0,int x1,int y1,int color)
{
 int sx, sy, ex, ey;
 
 sx = x0;
 sy = y0;
 ex = x1;
 ey = y1;
 
 if(sx < 0) sx = 0;
 else if(sx > (lcdPara.width - 1) ) sx = lcdPara.width - 1;
 if(sy < 0) sy = 0;
 else if(sy > (lcdPara.height - 1) ) sy = lcdPara.height - 1;
 
 if(ex < 0) ex = 0;
 else if(ex > (lcdPara.width - 1) ) ex = lcdPara.width - 1;
 if(ey < 0) ey = 0;
 else if(ey > (lcdPara.height - 1) ) ey = lcdPara.height - 1;
 
	uint32_t xlen=ex-sx+1;
	uint32_t ylen=ey-sy+1; 
	LCD_POSITION sPos={sx,sy};
	LCD_POSITION ePos={ex,ey};
	Lcd_Des.fillUseOneData(sPos,ePos,color,xlen*ylen);
// LCD_Fill_color(sx,sy,ex,ey,color);
}
/*
*********************************************************************************************************************
* Function: gui_dispLine draws a straight line using the foreground color of the LCD_INTERFACE driver interface
* Entry parameters: x1, the start coordinates for drawing a straight line
* y1.
* x2, the coordinates of the end point of the drawn line
* y2, the
*Exit parameter: None
*********************************************************************************************************************
*/
void gui_dispLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1;  
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; 
	else if(delta_x==0)incx=0;
	else {incx=-1;delta_x=-delta_x;} 
	
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;
	else{incy=-1;delta_y=-delta_y;} 
	
	if( delta_x>delta_y)distance=delta_x; 
	else distance=delta_y; 
	
	for(t=0;t<=distance+1;t++ ){  
		LCD_DrawPoint_color(uRow,uCol,lcdPara.fontcolor);
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) { 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) { 
			yerr-=distance; 
			uCol+=incy; 
		} 
	} 
}

/*
*********************************************************************************************************************
* Function: gui_dispLine draws a straight line using a custom color
* Entry parameters: x1, the start coordinates for drawing a straight line
* y1.
* x2, the coordinates of the end point of the drawn line
* y2, the
*Exit parameter: None
*********************************************************************************************************************
*/
void gui_dispLine_color(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
 
 
	if(delta_x>0)incx=1; 
	else if(delta_x==0)incx=0;
	else {incx=-1;delta_x=-delta_x;} 
	
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;
	else{incy=-1;delta_y=-delta_y;} 
	
	if( delta_x>delta_y)distance=delta_x; 
	else distance=delta_y; 
	
	for(t=0;t<=distance+1;t++ ){  
		LCD_DrawPoint_color(uRow,uCol,color); 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) { 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) { 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}
}

/*
*********************************************************************************************************************
* Function function: Line drawing function with color (straight line, diagonal line)
*Entry parameters: x1, starting point coordinates
* y1, the
* x2, end point coordinates
* y2, the
*Exit parameter: None
*********************************************************************************************************************
*/
void LCD_Draw_ColorLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    uint16_t	i = 0;
	int16_t		delta_x = 0, delta_y = 0;
	int8_t		incx = 0, incy = 0;
	uint16_t	distance = 0;
	uint16_t  t = 0;
	uint16_t	x = 0, y = 0;
	uint16_t 	x_temp = 0, y_temp = 0;
	
    if(y1 == y2)
    {
     /* Quickly draw horizontal lines  */
        gui_dispLine_color(x1, y1, x2, y2, color);
        return;
    }
	else
	{
		/* Draw diagonal lines (Bresenham algorithm) */
		/* Calculate the spacing between two points in the x and y directions to get the step value of the brush in the x and y directions */ 
		delta_x = x2 - x1;
		delta_y = y2 - y1;
		if(delta_x > 0)
		{
			//Slanted line (from left to right)
			incx = 1;
		}
		else if(delta_x == 0)
		{
			//Vertical diagonal line (vertical line)
			incx = 0;
		}
		else
		{
			//Slanted line (right to left)
			incx = -1;
			delta_x = -delta_x;
		}
		if(delta_y > 0)
		{
			//Slanted line (from left to right)
			incy = 1;
		}
		else if(delta_y == 0)
		{
			//Horizontal diagonal line (horizontal line)
			incy = 0;
		}
		else
		{
			//Slanted line (right to left)
			incy = -1;
			delta_y = -delta_y;
		}			
		
		/* Calculate the distance of the brush punch (take the maximum of the two spacings) */
		if(delta_x > delta_y)
		{
			distance = delta_x;
		}
		else
		{
			distance = delta_y;
		}
		
		x = x1;
		y = y1;
		for(t = 0; t <= distance + 1;t++)
		{
			LCD_DrawPoint_color(x, y, color);
		
			x_temp += delta_x;	
			if(x_temp > distance)
			{
				x_temp -= distance;		
				x += incx;
					
			}
			y_temp += delta_y;
			if(y_temp > distance)
			{
				
				y_temp -= distance;
				
				y += incy;
			}
		}
	}
}


/****************************************************************************
* Name: GUI_LineS()
* Function: Connects consecutive lines between multiple points. Connects from the first point to the second point, and then to the third point...
* Entry parameters: points Pointer to coordinate data of multiple points, the data is arranged as (x0,y0), (x1,y1), (x2,y2)...
* num Number of points, at least greater than 1
* color Display color
* Export parameter: None
* Explanation: The operation failed because the specified address is out of the valid range.
****************************************************************************/
void GUI_LineS(uint16_t const *points, uint8_t num, uint16_t color)
{  uint32_t  x0, y0;
   uint32_t  x1, y1;
   uint8_t  i;

 
   if(0==num) return;
   if(1==num)						
   { 
 	  x0 = *points++;
	  y0 = *points;
		 printf("x0 = %2x,y0 = %2x\n",x0,y0);

	  LCD_DrawPoint_color(x0,y0,color);
   }
   
   
   x0 = *points++;					
   y0 = *points++;
	  printf("x0 = %2x,y0 = %2x\n",x0,y0);

   for(i=1; i<num; i++)
   {  x1 = *points++;				
      y1 = *points++;
		 	printf("x1= %2x,y1 = %2x\n",x1,y1);
      gui_dispLine_color(x0, y0, x1, y1, color);
      x0 = x1;					
      y0 = y1;
 
   }
}

/*
*********************************************************************************************************************
* Function: gui_dispRectangle draws a rectangular box using the foreground color
* Entry parameters: x1, the coordinates of the starting point of the drawn rectangle (upper left corner coordinates)
* y1, the
* x2, the coordinates of the end point of the drawn rectangle (lower right coordinate)
* y2, the
* exit parameter: none
*********************************************************************************************************************
*/
void gui_dispRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	Lcd_Des.fill(x1,y1,x2,y1);
	Lcd_Des.fill(x1,y1,x1,y2);
	Lcd_Des.fill(x1,y2,x2,y2);
	Lcd_Des.fill(x2,y1,x2,y2);
}
/*
*********************************************************************************************************************
* Function: gui_dispRectangle_color draws a rectangle with a custom color
*Entry parameters: x1,y1, the coordinates of the starting point of the rectangle (upper left corner)
* x2,y2, the coordinates of the end point of the drawn rectangle (lower right corner coordinates)
* exit parameter: none
*********************************************************************************************************************
*/
void gui_dispRectangle_color(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	LCD_Fill_color(x1,y1,x2,y1,color);
	LCD_Fill_color(x1,y1,x1,y2,color);
	LCD_Fill_color(x1,y2,x2,y2,color);
	LCD_Fill_color(x2,y1,x2,y2,color);
}

/*
*********************************************************************************************************************
*Function: gui_dispRectangle_Solid draws a rectangle using the foreground color and fills it.
*Entry parameters: x1,y1, the coordinates of the starting point of the rectangle (upper left corner)
* x2,y2, the coordinates of the end point of the drawn rectangle (lower right corner coordinates)
* exit parameter: none
*********************************************************************************************************************
*/
void gui_dispRectangle_Solid(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	Lcd_Des.fill(x1,y1,x2,y2);
}

/*
*********************************************************************************************************************
* Function: gui_dispRectangle_Solid_color draws a rectangle using a custom color and fills it.
*Entry parameters: x1,y1, the coordinates of the starting point of the rectangle (upper left corner)
* x2,y2, the coordinates of the end point of the drawn rectangle (lower right corner coordinates)
* exit parameter: none
*********************************************************************************************************************
*/
void gui_dispRectangle_Solid_color(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	LCD_Fill_color(x1,y1,x2,y2,color);
}
/*
*********************************************************************************************************************
*Function: gui_dispCircle draws a circle using the foreground color
* Entry parameters: x0, the coordinates of the center of the circle
* y0, the
* r, the radius of the circle
* exit parameter: none
*********************************************************************************************************************
*/


void gui_dispCircle(uint16_t x0,uint16_t y0,uint16_t r)
{
	int a,b;
	int di;
	a=0;
	b=r;	  
	di=3-(r<<1);           
	while(a<=b){
		LCD_DrawPoint_color(x0+a,y0-b,lcdPara.fontcolor);             //5
		LCD_DrawPoint_color(x0+a,y0+b,lcdPara.fontcolor);             //6  
		LCD_DrawPoint_color(x0+b,y0+a,lcdPara.fontcolor);             //4               
		LCD_DrawPoint_color(x0+b,y0-a,lcdPara.fontcolor);             //0
		LCD_DrawPoint_color(x0-a,y0+b,lcdPara.fontcolor);             //1       
 		LCD_DrawPoint_color(x0-b,y0+a,lcdPara.fontcolor);             
		LCD_DrawPoint_color(x0-a,y0-b,lcdPara.fontcolor);             //2             
  	LCD_DrawPoint_color(x0-b,y0-a,lcdPara.fontcolor);             //7     	         
		a++;
		   
		if(di<0)di +=4*a+6;	  
		else{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
}

/*
*********************************************************************************************************************
* Function: gui_dispCircle_color draws a circle with a custom color
*Entry parameters: x0,y0, the coordinates of the center of the circle
* r, the radius of the circle
* exit parameter: none
*********************************************************************************************************************
*/


void gui_dispCircle_color(uint16_t x0,uint16_t y0,uint16_t r,uint16_t color)
{
	int a,b;
	int di;
	a=0;
	b=r;	  
	di=3-(r<<1);            
	while(a<=b){
		LCD_DrawPoint_color(x0+a,y0-b,color);             //5
		LCD_DrawPoint_color(x0+a,y0+b,color);             //6  
		LCD_DrawPoint_color(x0+b,y0+a,color);             //4               
		LCD_DrawPoint_color(x0+b,y0-a,color);             //0
		LCD_DrawPoint_color(x0-a,y0+b,color);             //1       
 		LCD_DrawPoint_color(x0-b,y0+a,color);             
		LCD_DrawPoint_color(x0-a,y0-b,color);             //2             
  	LCD_DrawPoint_color(x0-b,y0-a,color);             //7     	         
		a++;
		  
		if(di<0)di +=4*a+6;	  
		else{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
}

/*
*********************************************************************************************************************
*Function: gui_dispCircle_Solid draws a solid circle using the foreground color
* Entry parameters: x0, the coordinates of the center of the circle
* y0, the
* r, the radius of the circle
* exit parameter: none
*********************************************************************************************************************
*/
void gui_dispCircle_Solid(uint16_t x0,uint16_t y0,uint16_t r)
{
	int a,b;
	int di;
	a=0;
	b=r;	  
	di=3-(r<<1);             
	while(a<=b){
		Lcd_Des.fill(x0+a,y0-b,x0+a,y0+b);
		Lcd_Des.fill(x0+b,y0-a,x0+b,y0+a);   
		Lcd_Des.fill(x0-a,y0-b,x0-a,y0+b);        	            
		Lcd_Des.fill(x0-b,y0-a,x0-b,y0+a);  
		a++;		  
		if(di<0)di +=4*a+6;	  
		else{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
}

/*
*********************************************************************************************************************
* Function: gui_dispCircle_Solid_color draws a solid circle with a custom color
* Entry parameters: x0, the coordinates of the center of the circle
* y0, the
* r, the radius of the circle
* exit parameter: none
*********************************************************************************************************************
*/
void gui_dispCircle_Solid_color(uint16_t x0,uint16_t y0,uint16_t r,uint16_t color)
{
	int a,b;
	int di;
	a=0;
	b=r;	  
	di=3-(r<<1);      
	while(a<=b){
		LCD_Fill_color(x0+a,y0-b,x0+a,y0+b,color);
		LCD_Fill_color(x0+b,y0-a,x0+b,y0+a,color);   
		LCD_Fill_color(x0-a,y0-b,x0-a,y0+b,color);        	            
		LCD_Fill_color(x0-b,y0-a,x0-b,y0+a,color);  
		a++;
	  
		if(di<0)di +=4*a+6;	  
		else{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
}

