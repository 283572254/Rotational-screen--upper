#ifndef _guiConfig_h
#define _guiConfig_h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Function module: Variable definition for controlling lib global switch
 * Implemented functions.
 
 *                              
 * List of functions
 *
 *V1.01: Function implementation
 *
 *V1.02£º
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "gStdint.h"
#include "gWidgetInfo.h"

#ifdef __cplusplus
 extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	  *Macro definition of switch type    
 *The content of the macro definition cannot be modified by the user, 
 but it can be used. The value of a configuration item defined by a variable can be modified by the user.
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define 	 GUI_FUNC_GLOBALS_CLOSE        0	 
#define 	 GUI_FUNC_GLOBALS_OPEN         1
	 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
* Storage FLASH configuration information
 *The content defined by using macros cannot be modified by the user but can be used.  
 Configuration items defined by variables can be modified by the user.
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const gui_uint32  FLASH_TOTAL_SIZE;
extern const gui_uint32  FLASH_SECTOR_SIZE;
extern const gui_uint32  FLASH_RES_START_ADDR;
extern const gui_uint32  READFLASH_ADDR_OFFSET;
	 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Some common GUI macro definitions for switches   
 * The content defined by the use of macros cannot be modified by the user but can be used   
 Configuration items defined by variables can be modified by the user.	
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const gui_uint8  GUI_USING_Debug;
extern const gui_uint32 GUI_Debug_BUF_MAX;
extern const gui_uint8  GUI_USING_QRcode;
extern const gui_uint8  GUI_USING_Graph;
extern const gui_uint16 CHAR_WIDTH_MAX  ;                                                          //Allowable spacing of fonts

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Message related configuration
 * The content defined using macros cannot be modified by the user but can be used   
 Configuration items defined by variables can be modified by the user	
 */
////////////////////////////////////////////////////////////////////////////////////////////*///////////////////////////////////////////
#define   INPUTMSG_TOUCH_DOT_MAX       0x0005           //Maximum number of touch points
extern const gui_uint16   INPUTMSG_QUEUE_DEPTH;
extern const gui_uint16   INPUTMSG_KEYVALUE_NULL;
extern const gui_uint16   INPUTMSG_KEYVALUE_UP;
extern const gui_uint16   INPUTMSG_KEYVALUE_DOWN;
extern const gui_uint16   INPUTMSG_KEYVALUE_LEFT;
extern const gui_uint16   INPUTMSG_KEYVALUE_RIGHT;
extern const gui_uint16   INPUTMSG_KEYVALUE_OK;
extern const LCD_POSITION INPUTMSG_TOUCHVALUE_NULL;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Keyboard-related configuration      
 */
////////////////////////////////////////////////////////////////////////////////////////////*///////////////////////////////////////////
extern const gui_uint16   KEYBOARD_INPUT_BUF_MAX;
extern const gui_color    KEYBOARD_PAGE_BACKCOLOR;
extern const gui_color    KEYBOARD_WIDGET_BACKCOLOR;
extern const gui_color    KEYBOARD_WIDGET_FONTCOLOR;
extern const gui_color    KEYBOARD_WIDGET_PRESSBACKCOLOR;
#ifdef __cplusplus
}
#endif

#endif 
