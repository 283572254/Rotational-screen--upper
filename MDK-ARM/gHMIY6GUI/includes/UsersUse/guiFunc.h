#ifndef _guiFunc_h
#define _guiFunc_h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Function module: GUI library function
 * Realized functions.
 
 *                              
 * List of functions
 *
 *V1.01: Function Implementation
 *
 *V1.02��
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "gStdint.h"
#include "gReturn.h"
#include "gWidgetInfo.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *GUI lib initialization should be called between initializing all peripherals and entering the main loop

 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void guiInit(void);                                                        //

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *GUI main loop is responsible for GUI event handling, message handling, GUI processing, etc. Users should call it repeatedly in the main loop.
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void guiMainLoop(void);                                                     //

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *GUI System tick clock processing function, the user should create a timer (recommended time base 1ms overflow)
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void guiTickHandle(void);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Enter a touch message
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiSendMsgTouch(gui_uint8 count , const	pLCD_POSITION pos);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Enter a keystroke message
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiSendMsgKey(gui_uint16 keyValue);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Full screen swipe monochrome and return to refresh time
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_uint32 guiGetRefreshColorTime(gui_color color);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Full screen swipe and return to refresh time
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_uint32 guiGetRefreshPicTime(gui_uint16 imageid);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Instructs the GUI LIB to jump to a new screen
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiJumpPage(gui_uint16 pageID , WIDGET_EVENT leaveEvent , WIDGET_EVENT enterEvent);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Instructs the GUI LIB to refresh the current page
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiRefreshPage(void);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Instructs the GUI LIB to refresh the current control
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

gui_Err guiRefreshWidget( gui_uint16 widgetID);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Register events for controls with specified IDs
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiRegisterEvent(gui_uint16 type , gui_uint16 widgetID , WIDGET_EVENT event);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Create a control
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiCreateWidget(const void * widgetInfo);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Delete a control
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiDeleteWidget(gui_uint16 widgetID);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Set control text
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiSetWidgetText(gui_uint16 widgetID , gui_uint16 textLen , const char* text);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Append str to the control text
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiAppendWidgetText(gui_uint16 widgetID , gui_uint16 textLen , const char* text);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Control text deletion characters
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiDeleteWidgetText(gui_uint16 widgetID , gui_uint16 textLen);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Get the text property of the control
 *The maxLen passed is the maximum allowed for the control's text, the actual length of the text is counted by strlen
 *strlen result greater than maxLen means the text is limited to maxLen.
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiGetWidgetText(gui_uint16 widgetID , gui_uint16* maxLen , const char** text);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Set the control value
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiSetWidgetValue(gui_uint16 widgetID , gui_uint32 value);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Get the control value property
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiGetWidgetValue(gui_uint16 widgetID , gui_uint32* value);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Set the background color of the control
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiSetWidgetBackColor(gui_uint16 widgetID , gui_color backColor);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Get the control background color property
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiGetWidgetBackColor(gui_uint16 widgetID , gui_color* backColor);

/*
 * Set the foreground color of the control
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiSetWidgetFrontColor(gui_uint16 widgetID , gui_color frontColor);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Get the control foreground color property
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiGetWidgetFrontColor(gui_uint16 widgetID , gui_color* frontColor);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
* Set the control timeout time property
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiSetWidgetOvertime(gui_uint16 widgetID , gui_uint16 timeOut);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Read the control timeout property
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiGetWidgetOvertime(gui_uint16 widgetID , gui_uint16* timeOut);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Setting control switch properties
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiSetWidgetEnable(gui_uint16 widgetID , gui_uint8 enable);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Reading control switch properties
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiGetWidgetEnable(gui_uint16 widgetID , gui_uint8* enable);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Set the control position property
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiSetWidgetLocation(gui_uint16 widgetID , WIDGET_LOCATION loc);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Read the control position property
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiGetWidgetLocation(gui_uint16 widgetID , WIDGET_LOCATION* loc);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Set the control image ID
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiSetWidgetPictureID(gui_uint16 widgetID , gui_uint16 picId);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 **Read the control image ID
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiGetWidgetPictureID(gui_uint16 widgetID , gui_uint16* picId);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Set the value of curve single
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiSetWidgetGraphValue(gui_uint16 widgetID,gui_uint8 ch, gui_uint16 value);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Set the value of the curve multiple
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiSetWidgetGraphValues(gui_uint16 widgetID,gui_uint8 ch, gui_uint8 *value,gui_uint16 count);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Clear the value of the curve
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiClearWidgetGraphValues(gui_uint16 widgetID,gui_uint8 ch);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Set the animation style of the moving frame control
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiSetWidgetPicanimationpattern(gui_uint16 widgetID,gui_uint8 pattern);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Retrieve the animation style of the moving frame control
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiGetWidgetPicanimationpattern(gui_uint16 widgetID,gui_uint8 *pattern);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Set the edge limit of the circular slider
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_Err guiSetWidgetRoundSliderBound(gui_uint16 widgetID,gui_uint32 maxvalue , gui_uint32 minvalue);
#endif
