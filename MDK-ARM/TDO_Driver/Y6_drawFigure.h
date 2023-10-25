#ifndef _led_h
#define _led_h
#include "stdint.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void gui_dispLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
  void gui_dispLine_color(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);
  void GUI_LineS(uint16_t const *points, uint8_t num, uint16_t color);

void gui_dispRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void gui_dispRectangle_Solid(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

void gui_dispRectangle_color(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);
void gui_dispRectangle_Solid_color(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);

void gui_dispCircle(uint16_t x0,uint16_t y0,uint16_t r);
void gui_dispCircle_Solid(uint16_t x0,uint16_t y0,uint16_t r);
void gui_dispCircle_color(uint16_t x0,uint16_t y0,uint16_t r,uint16_t color);
void gui_dispCircle_Solid_color(uint16_t x0,uint16_t y0,uint16_t r,uint16_t color);

#endif
