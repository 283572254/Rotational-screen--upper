#include "guiConfig.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Some common switch macro definitions  
 */
////////////////////////////////////////////////////////////////////////////////////////////*///////////////////////////////////////////
const gui_uint8 GUI_USING_Debug=GUI_FUNC_GLOBALS_CLOSE ; 				//Whether to use the debug information output at key locations
const gui_uint32 GUI_Debug_BUF_MAX=256;							 		//Debug output buffer size
const gui_uint8 GUI_USING_QRcode=GUI_FUNC_GLOBALS_OPEN; 				//whether to use the QR code control
const gui_uint8 GUI_USING_Graph=GUI_FUNC_GLOBALS_OPEN; 					//whether to use the curve control

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Storage FLASH Configuration Information
 */
////////////////////////////////////////////////////////////////////////////////////////////*///////////////////////////////////////////
const gui_uint32	FLASH_TOTAL_SIZE =0x00800000; 										//storage flash total capacity size,Bytes
const gui_uint32	FLASH_SECTOR_SIZE =4096; 										//Store flash sector size
const gui_uint32	FLASH_RES_START_ADDR =0x00103000;									 // resource storage start address // 260*4096
																								// resource data contains: GUI resource data, some system data used by the GUI																																														
const gui_uint32	READFLASH_ADDR_OFFSET =0x8000; 											// resource base address when accessing the resource. xip mode requires -32K

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Message Related Configuration
 */
////////////////////////////////////////////////////////////////////////////////////////////*///////////////////////////////////////////
const gui_uint16  INPUTMSG_QUEUE_DEPTH        =0x0008;                                       //消息队列深度   4-8可以设定
const gui_uint16  INPUTMSG_KEYVALUE_NULL      =0xffff;                                       //an invalid key key value when the user sends a key key value
																							// send if no valid key is pressed, or if the key is released																																														 //该值
const gui_uint16   INPUTMSG_KEYVALUE_UP        =0x0001;                                      //The user detects a keystroke. Indicates the value of the key moved on the UI
const gui_uint16   INPUTMSG_KEYVALUE_DOWN      =0x0002;                                      
const gui_uint16   INPUTMSG_KEYVALUE_LEFT      =0x0003;
const gui_uint16   INPUTMSG_KEYVALUE_RIGHT     =0x0004;
const gui_uint16   INPUTMSG_KEYVALUE_OK        =0x0005;
const LCD_POSITION INPUTMSG_TOUCHVALUE_NULL    ={481,321};                                    //The value of an invalid touch point

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Keyboard-related configuration      
 */
////////////////////////////////////////////////////////////////////////////////////////////*///////////////////////////////////////////
const gui_uint16   KEYBOARD_INPUT_BUF_MAX      =64;                                           //the maximum buffer area allowed for keyboard input
const gui_color    KEYBOARD_PAGE_BACKCOLOR     =0x0011;                                       //the keyboard's page background color
const gui_color    KEYBOARD_WIDGET_BACKCOLOR   =0x0000;                                        //control's background color
const gui_color    KEYBOARD_WIDGET_FONTCOLOR   =0xffff;                                       //the foreground color of the control
const gui_color    KEYBOARD_WIDGET_PRESSBACKCOLOR  =0xc618;                                   //the color of the control after it is pressed
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Font-related configuration      
 */
//////////////////////////////////////////////////////////////////////////////////////////////*///////////////////////////////////////////
const gui_uint16 CHAR_WIDTH_MAX = 0;                                                          //Allowable spacing of fonts
