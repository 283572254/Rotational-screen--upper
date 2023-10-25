#ifndef _gResMsg_h
#define _gResMsg_h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Functional module: gui Some operation description information definition
 *Implemented functions.
 
 *                              
 * List of functions
 *
 *V1.01: Function implementation
 *
 *V1.02：
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "gStdint.h"

#ifdef __cplusplus
 extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Resource Type Definition
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define RTYPE_NULL               0//Invalid resource type, the MCU detects this type to indicate the end of resource reading
#define RTYPE_GUICONFIG          2//GUI interface resources developed by HMI
#define RTYPE_PICTURE            3
#define RTYPE_TRUETYPE           4//Font Resources
#define RTYPE_CARTOON            5
#define RTYPE_VIDEO              6
#define RTYPE_VOICE              7
#define RTYPE_EVENT              8//Events executed during GUI runtime，

#define RTYPE_ERRER              9//Wrong type of resource

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *GUI library    Control type definition
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WIDGET_TYPE_MASK               0x00ff//The lower eight bits of the control type uint16_t wType indicate the control type, the higher eight bits indicate the basic properties of the control, there is no loc and other information
                                             //0 is an invalid control, the maximum value of all control types 255 (1-255)
#define WIDGET_TYPE_HASLOC_MASK        0x8000//bit15,1 means there is control position information.
                                             //0 means no
#define WIDGET_TYPE_HASSLIDE_MASX      0x4000//bit14, a 1 means the control supports sliding.
                                             //0 means no support
#define WIDGET_TYPE_HASTIMING_MAX      0x2000//bit13,1 means the control supports timed actions
												//0 means no support
#define WIDGET_TYPE_NULL               0x0000
#define WIDGET_TYPE_PAGE               0x8001
#define WIDGET_TYPE_TEXTBOX            0x8002
#define WIDGET_TYPE_ROLLTEXTBOX        0xa003
#define WIDGET_TYPE_NUMBERBOX          0x8004
#define WIDGET_TYPE_FLOATNUMBERBOX     0x8005
#define WIDGET_TYPE_BUTTON             0x8006
#define WIDGET_TYPE_PROGRESSBAR        0x8007
#define WIDGET_TYPE_PICTUREBOX         0x8008
#define WIDGET_TYPE_CUTPICTURE         0x8009
#define WIDGET_TYPE_TOUCHAREA          0x800a
#define WIDGET_TYPE_POINTER            0x800b
#define WIDGET_TYPE_GRAPH              0x800c
#define WIDGET_TYPE_SLIDER             0xC00d
#define WIDGET_TYPE_GTIMER             0x200e
#define WIDGET_TYPE_GVARIATE           0x000f
#define WIDGET_TYPE_BINARYBUTTON       0x8010
#define WIDGET_TYPE_OPTIONBOX          0x8011
#define WIDGET_TYPE_QRCODEBOX          0x8012
#define WIDGET_TYPE_VIRTUALGIF         0xA013
#define WIDGET_TYPE_ROUNDSLIDER  	   0xC014
#define WIDGET_TYPE_PICANIMATION       0xA015

#define WIFGET_TYPE_MIN                WIDGET_TYPE_PAGE
#define WIDGET_TYPE_MAX                WIDGET_TYPE_PICANIMATION

																																																				 //有效为1  无效为0
#define ASSERT_WIDGET_TYPE(type)    (((type&WIDGET_TYPE_MASK)<=(WIDGET_TYPE_MAX&WIDGET_TYPE_MASK))&((type&WIDGET_TYPE_MASK)>=(WIFGET_TYPE_MIN&WIDGET_TYPE_MASK)))
#define GET_WIDGET_TYPE(type)    			((type)&(WIDGET_TYPE_MASK))//Get a control type Remove the high eight bits of type to get the low eight bits, 
																		//often used in the control event processing to quickly look up the table to locate
#define ADJUST_WIDGET_TYPE(type,needtype) 	(type)==(needtype)?(0):(1)/
#define ADJUST_WIDGET_NOLOC(type) 			(((type)&WIDGET_TYPE_HASLOC_MASK)?(0):(1))
#define ADJUST_WIDGET_NOSLIDE(type) 		(((type)&WIDGET_TYPE_HASSLIDE_MASX)?(0):(1))//
#define ADJUST_WIDGET_NOTIMING(type) 		(((type)&WIDGET_TYPE_HASTIMING_MAX)?(0):(1))

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Backgrounds supported by controls in the GUI library
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WIDGET_BACKMODE_NULL                0//No background
#define WIDGET_BACKMODE_COLOR               1//Display a color value
#define WIDGET_BACKMODE_PIC                 2//Show an image
#define WIDGET_BACKMODE_CUTPIC              3//Cut out a portion of a full-width image to display
#define IS_WIDGET_BACKMODE(x)               ((x>=WIDGET_BACKMODE_COLOR)&(x<=WIDGET_BACKMODE_CUTPIC))

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Text alignment supported by controls in the GUI library
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CHARALIGN_X_L                        0
#define CHARALIGN_X_C                        1
#define CHARALIGN_X_R                        2
#define CHARALIGN_Y_T                        0
#define CHARALIGN_Y_C                        1
#define CHARALIGN_Y_B                        2

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Private property definitions for controls in the GUI library
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WIDGET_VS_PRIVATE                  0x00
#define WIDGET_VS_GLOBAL                   0x01

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *The types of events supported by the control registration in the GUI library
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define EVENT_REGISTER_TYPE_RELEASE         0x0001
#define EVENT_REGISTER_TYPE_PRESS           0x0002
#define EVENT_REGISTER_TYPE_TIMEOUT         0x0003//Instructions to register a control timed overflow event
#define EVENT_REGISTER_TYPE_UPDATE          0x0004//directs the registration of a control update event
#define EVENT_REGISTER_TYPE_SLIDE           0x0005//directs the registration of a control slide event

#define EVENT_REGISTER_TYPE_ENTER           0x0101
#define EVENT_REGISTER_TYPE_LEAVE           0x0102

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Definition of the number box display method in the GUI library
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NUMBERBOX_DISPMODE_NUMBER           0
#define NUMBERBOX_DISPMODE_MONEY            1
#define NUMBERBOX_DISPMODE_HEX              2

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *GUI library Bistate button state definition
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BINARYBUTTON_STATE_DISENABLE        0
#define BINARYBUTTON_STATE_ENABLE           1

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * GUI library Progress bar direction definition
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define PROGRESSBAR_DIR_H                   0//Progress bar direction horizontal
#define PROGRESSBAR_DIR_V                   1

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *  Slider orientation definition in GUI library
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SLIDER_DIR_H                        0//horizontal
#define SLIDER_DIR_V                        1

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * GUI library Options box state and style definition
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define OPTIONBOX_STATE_NOCHOOSE            0
#define OPTIONBOX_STATE_CHOOSE              1
#define OPTIONBOX_TYPE_RECT                 0
#define OPTIONBOX_TYPE_CIRCLE               1

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *GUI library Curve frame scan direction and polar position definition
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define GRAPH_SCAN_LR                       0//Left to right advance
#define GRAPH_SCAN_RL                       1
#define GRAPH_XAXIS_D                       0//X-axis position, bottom, middle, top
#define GRAPH_XAXIS_C                       1
#define GRAPH_XAXIS_T                       2
#define GRAPH_YAXIS_L                       0//y-axis position, left, center, right
#define GRAPH_YAXIS_C                       1
#define GRAPH_YAXIS_R                       2

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *GUI library Animated picture box animation style
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define PICANIMATION_TYPE_lSLIDEINTO   0           //Slide in from the left
#define PICANIMATION_TYPE_rSLIDEINTO   1           
#define PICANIMATION_TYPE_uSLIDEINTO   2           
#define PICANIMATION_TYPE_dSLIDEINTO   3           
#define PICANIMATION_TYPE_luSLIDEINTO  4           //Slide in top left
#define PICANIMATION_TYPE_ruSLIDEINTO  5           
#define PICANIMATION_TYPE_ldSLIDEINTO  6           //Slide in left
#define PICANIMATION_TYPE_rdSLIDEINTO  7           
#define PICANIMATION_TYPE_lSLIDEOUT    8           //Slide out to the left
#define PICANIMATION_TYPE_rSLIDEOUT    9           
#define PICANIMATION_TYPE_uSLIDEOUT    10          
#define PICANIMATION_TYPE_dSLIDEOUT    11          
#define PICANIMATION_TYPE_luSLIDEOUT   12          //Slide out top left
#define PICANIMATION_TYPE_ruSLIDEOUT   13          
#define PICANIMATION_TYPE_ldSLIDEOUT   14          
#define PICANIMATION_TYPE_rdSLIDEOUT   15          
#define PICANIMATION_TYPE_hOPEN        16          //Slide out left and right
#define PICANIMATION_TYPE_vOPEN        17          
#define PICANIMATION_TYPE_hCLOSE       18          //Slide in left and right
#define PICANIMATION_TYPE_vCLOSE       19          
#define PICANIMATION_TYPE_CORNERINTO   20           //Four corners slide in
#define PICANIMATION_TYPE_CORNEROUT    21           //
#define PICANIMATION_TYPE_SHUTTER      22          //Blinds
//#define PICANIMATION_TYPE_PLAID        23          //Grille effect
#ifdef __cplusplus
}
#endif

#endif
