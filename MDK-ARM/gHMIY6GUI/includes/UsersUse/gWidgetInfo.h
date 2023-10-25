#ifndef _gWidgetInfo_h
#define _gWidgetInfo_h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Function module: gui control related information definition
 * Implemented functions.
 
 *                              
 * List of functions
 *
 *V1.01: Function Implementation
 *
 *V1.02.

 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "gStdint.h"
#include "gReturn.h"

#ifdef __cplusplus
 extern "C" {
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *LCD coordinate system                   Coordinate information description
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _LCD_POSITION{
	gui_uint16 x;
	gui_uint16 y;
}LCD_POSITION;
typedef LCD_POSITION*  pLCD_POSITION;

__packed typedef struct _LCD_RECTANGLE{
	LCD_POSITION startPos;
	LCD_POSITION endPos;
}LCD_RECTANGLEN;
typedef LCD_RECTANGLEN*  pLCD_RECTANGLEN;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *GUIlib    Control Location Information
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _WIDGET_LOCATION{
	
  gui_uint16 x;                                 //Start coordinates of the display
  gui_uint16 y;  								//The starting coordinates of the display
  gui_uint16 width; 							//Width of the display
  gui_uint16 height;		 					//Height of the display	                                                    	                       
}WIDGET_LOCATION; 
typedef WIDGET_LOCATION*  pWIDGET_LOCATION;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *GUI Library    Description of the basic information of a control------All controls should have it, and it is at the top of the control descriptor
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WIDGET_NAME_MAX_LEN                11//Maximum string length of a control's name
__packed typedef struct _WIDGET_BASE_INFO{	
  gui_uint16 wType;                           
  gui_uint16 wId;                              
	//gui_uint8 wName[WIDGET_NAME_MAX_LEN];        //Control Name
  gui_uint8  wVscope;                          //Private properties of controls
}WIDGET_BASE_INFO; 
typedef WIDGET_BASE_INFO*  pWIDGET_BASE_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *GUI¿âÖÐ  Prototypes used for control events and other content
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef gui_Err (*WIDGET_EVENT)(gui_int32 argc , const char **argv);//Display control prototype for all controls

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Controls in the GUI library Page information description
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _PAGE_INFO{
	
	WIDGET_BASE_INFO base_info;                //Basic information that all controls have
	WIDGET_LOCATION loc;                       //Control Location Information
  gui_uint8  backMode;                         
	gui_color backColor;                       //Background color, called when the background mode is to display a color
	gui_uint16 picId;                          //Image ID, called when the background mode is display image
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Private properties for each control
	WIDGET_EVENT enterEvent; 					//Enter the page
	WIDGET_EVENT leaveEvent; 					//leave the page
	WIDGET_EVENT pressEvent; 					//control press event, user-defined, registered in
	WIDGET_EVENT releaseEvent; 					//control release event, user-defined, registered
	WIDGET_EVENT updateEvent; 					//Control update event, user-defined, registered
}PAGE_INFO; 
typedef PAGE_INFO*  pPAGE_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *  Bistable button message description
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _BINARYBUTTON_INFO{
	
	WIDGET_BASE_INFO base_info;               
	WIDGET_LOCATION loc;                      
	gui_uint8 backMode;                       
	gui_uint16 fontlibId;                     
	gui_uint8 borderWidth;                    
	gui_color borderColor;                    
	gui_uint16 enablePicId;                   
	gui_uint16 disenablePicId;                
	gui_color enableBackColor;                
	gui_color disenableBackColor;             
	gui_color enableFontColor;                
	gui_color disenableFontColor;             
	gui_uint8  xAlign;                        
	gui_uint8  yAlign;                        
	gui_uint8  isDr;                           //When the display doesn't work, is there a line break?
	gui_uint8  value;                          //Dual-state button, 0 released state, 1 pressed state
	char  *text;                               //Data pointer for text display, copied from flash when created
	                                           
	gui_uint16 maxLen;                         //The maximum length of the text box display, counted by bytes, is also the length of memory that the MCU needs to apply,
												// ASCII occupies one byte, Chinese occupies two bytes
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	WIDGET_EVENT pressEvent;                   
	WIDGET_EVENT releaseEvent;                 
	WIDGET_EVENT updateEvent;                  
}BINARYBUTTON_INFO;
typedef BINARYBUTTON_INFO*  pBINARYBUTTON_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Button Information Description
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _BUTTON_INFO{
	
	WIDGET_BASE_INFO base_info;                
	WIDGET_LOCATION loc;                       
	gui_uint8 backMode;                        
	gui_uint16 fontlibId;                      
	gui_uint8 borderWidth;                     
	gui_color borderColor;                     
	gui_uint16 pressPicId;                     
	gui_uint16 releasePicId;                   
	gui_color pressBackColor;                  
	gui_color releaseBackColor;                
	gui_color pressFontColor;                  
	gui_color releaseFontColor;                
	gui_uint8  xAlign;                         
	gui_uint8  yAlign;                         
	gui_uint8  isDr;                           
	char  *text;                               
	                                           	                                           
	gui_uint16 maxLen;                         
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	WIDGET_EVENT pressEvent;                   
	WIDGET_EVENT releaseEvent;                 
	WIDGET_EVENT updateEvent;                  
}BUTTON_INFO; 
typedef BUTTON_INFO*  pBUTTON_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
* Description of cutout information
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _CUTPICTURE_INFO{
	
	WIDGET_BASE_INFO base_info;                
	WIDGET_LOCATION loc;                       
	gui_uint16 picId;                          
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	WIDGET_EVENT pressEvent;                   
	WIDGET_EVENT releaseEvent;                 
	WIDGET_EVENT updateEvent;                  
}CUTPICTURE_INFO; 
typedef CUTPICTURE_INFO*  pCUTPICTURE_INFO;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Virtual Floating Point Information Description
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _FLOATNUMBERBOX_INFO{
	
	WIDGET_BASE_INFO base_info;                
	WIDGET_LOCATION loc;                       
	gui_uint8 backMode;                        
	gui_uint8 keyId;                           //Enter the keyboard ID. -1 means no keyboard
	gui_uint16 fontlibId;                      
	gui_uint8 borderWidth;                     
	gui_color borderColor;                     
	gui_uint16 picId;                          
	gui_color backColor;                       
	gui_color frontColor;                      
	gui_uint8  xAlign;                         
	gui_uint8  yAlign;                         
	gui_uint8  fdcount;                        //The fractional part length, maxlen-fdcount is the integer part length
	gui_uint8  isDr;                           
	gui_uint32 data;                           
	gui_uint8 maxLen;                          
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	WIDGET_EVENT pressEvent;                   
	WIDGET_EVENT releaseEvent;                 
	WIDGET_EVENT updateEvent;                  
}FLOATNUMBERBOX_INFO; 
typedef FLOATNUMBERBOX_INFO*  pFLOATNUMBERBOX_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Curve box information description
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define GRAPH_CHANNEL_MAX                     4//Maximum number of channels for curve control
__packed typedef struct _GRAPH_INFO{
	
	WIDGET_BASE_INFO base_info;                
	WIDGET_LOCATION loc;                       
		gui_uint8 backMode;                        
	gui_uint8 dir; //bit0-bit3 control waveform recommended mode, 0000 left to right advance,0001 right to left advance
	gui_uint8 xAxis_loc; //axis position
	gui_uint8 yAxis_loc; //axis position
	gui_uint8 channelCount; //number of channels, 1-4, total 4 channels
	gui_color axisColor; //the displayed axis color
	gui_color backColor; //background color
	gui_color gridColor; //grid color
	gui_uint8 gridWidth; //Grid width 0 means no grid
	gui_uint8 gridHeight; //gridHeight0 means no grid
	gui_uint16 picId; //cutout mode or picture mode, picture ID
	gui_color graphColor[GRAPH_CHANNEL_MAX]; //the color value of the 4 channels
	gui_uint16 dis; //scaling factor on the Y-axis of the waveform
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//The configuration information down from the upper computer ends at this place, whether it is reading data from external flash or copying data from internal flash, sizeof(GRAPH_INFO) should be -16
	// The following 16 bytes of data are only available on the MCU side, the 4 pointers are stored, pointing to the data addresses of the 4 channels, the data types are uint8_t, 0-255
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	gui_uint8 *graphData[GRAPH_CHANNEL_MAX];   
	gui_uint16 dataLen[GRAPH_CHANNEL_MAX];
	WIDGET_EVENT pressEvent;                   
	WIDGET_EVENT releaseEvent;                 
	WIDGET_EVENT updateEvent;                  
}GRAPH_INFO; 
typedef GRAPH_INFO*  pGRAPH_INFO;

#define GRAPH_INFO_LEN_OFFSET     (GRAPH_CHANNEL_MAX*4+GRAPH_CHANNEL_MAX*2+12) //The curve control has so many extra bytes of data in addition to the control parameters 


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Timer Message Description
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _GTIMER_INFO{
	
	WIDGET_BASE_INFO base_info;             
	gui_uint16 timeOut; //Timer timeout time
	gui_uint8 enable; //Timer switch bit, 0 off, 1 on
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	gui_uint32 timeValue; //timer current count value (period is 1MS) low 16 bits is the current counter value, high 16 bits is the timer overflow flag, or other identification
	WIDGET_EVENT timeoutEvent; //Timer overflow, user-defined, registered in
}GTIMER_INFO; 
typedef GTIMER_INFO*  pGTIMER_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Variable control information description
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _GVARIATE_INFO{
	
	WIDGET_BASE_INFO base_info;               
	gui_uint8 vaType; 				//variable type, 0 value, 1 string
	gui_uint32 value; 				//variable value
	char  *text;                               
	                                           	                                           
	gui_uint16 maxLen;                         
}GVARIATE_INFO; 
typedef GVARIATE_INFO*  pGVARIATE_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Description of digital box information
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _NUMBERBOX_INFO{
	
	WIDGET_BASE_INFO base_info;               
	WIDGET_LOCATION loc;                      
	gui_uint8 backMode;                       
	gui_uint8 keyId;                           //Enter the keyboard ID. -1 means no keyboard
	gui_uint16 fontlibId;                      
	gui_uint8 borderWidth;                     
	gui_color borderColor;                     
	gui_uint16 picId;                          
	gui_color backColor;                       
	gui_color frontColor;                      
	gui_uint8  xAlign;                         
	gui_uint8  yAlign;                         
	gui_uint8 formatType; //numeric display mode, 0 digits, 1 currency, 2 HEX
	gui_uint8 isDr; //whether or not line feed when displaying not down
	gui_uint32 data; //the value to be displayed
	gui_uint8 maxLen; //the maximum length of the display when the value is displayed specified
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	WIDGET_EVENT pressEvent;                   
	WIDGET_EVENT releaseEvent;                 
	WIDGET_EVENT updateEvent;                  
}NUMBERBOX_INFO; 
typedef NUMBERBOX_INFO*  pNUMBERBOX_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Option box information description
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _OPTIONBOX_INFO{
	
	WIDGET_BASE_INFO base_info; 		//basic information that all controls have
	WIDGET_LOCATION loc; 				//control location information
	gui_uint8 backMode; 				//background mode, cutout, monochrome, image
	gui_uint8 optionType; 				//option style, 0 center shows square, for checkbox, 1 center shows round, for single checkbox
	gui_color backColor; 				//background color
	gui_color frontColor; 				// foreground color, that is, the color of the box displayed in the middle
	gui_uint16 cPicId; 					//Select the background image under
	gui_uint16 nocPicId; 				//not selected under the background image
	gui_uint8 value; 					//value, 0 means no selection, 1 means selection
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	WIDGET_EVENT pressEvent;                   
	WIDGET_EVENT releaseEvent;                  
	WIDGET_EVENT updateEvent;                          
}OPTIONBOX_INFO; 
typedef OPTIONBOX_INFO*  pOPTIONBOX_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Image box information description
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _PICTUREBOX_INFO{
	
	WIDGET_BASE_INFO base_info;                
	WIDGET_LOCATION loc;                       
	gui_uint16 picId;                          
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	WIDGET_EVENT pressEvent;                   
	WIDGET_EVENT releaseEvent;                  
	WIDGET_EVENT updateEvent;                  
}PICTUREBOX_INFO; 
typedef PICTUREBOX_INFO*  pPICTUREBOX_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Pointer Information Description
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _POINTER_INFO{
	
	WIDGET_BASE_INFO base_info;               
	WIDGET_LOCATION loc;                      
	gui_uint8 backMode; // background mode, support monochrome and picture
	gui_uint16 picId; //Picture or cut mode: picture ID
	gui_color backColor; //monochrome mode: background color
	gui_color frontColor; //monochrome mode: foreground color
	gui_uint8 frontWidth; //Pointer line width
	gui_uint8 circleRadius; // radius of the pointer's circle, in pixels
	gui_uint16 AngleValue; // radian value 0-360, identifies the position of the pointer display
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	gui_uint16 last_endx;                      //The end coordinates of the last time the pointer was drawn, the starting coordinates are always the center of the circle of the dashboard, always the same
	gui_uint16 last_endy;
	WIDGET_EVENT pressEvent;                   
	WIDGET_EVENT releaseEvent;                  
	WIDGET_EVENT updateEvent;                  
}POINTER_INFO; 
typedef POINTER_INFO*  pPOINTER_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Progress bar information description
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _PROGRESSBAR_INFO{
	
	WIDGET_BASE_INFO base_info;               
	WIDGET_LOCATION loc;                      
	gui_uint8 backMode; //background mode, support monochrome and picture
	gui_uint8 dir; //direction
	gui_uint8 value; //value of the progress bar, 0-100%
	gui_uint16 backPicId; //image mode, background image
	gui_uint16 frontPicId; //In picture mode, front image
	gui_color backColor; //monochrome mode, background color
	gui_color frontColor; //monochrome mode, front color
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	WIDGET_EVENT pressEvent;                  
	WIDGET_EVENT releaseEvent;                
	WIDGET_EVENT updateEvent;                 
}PROGRESSBAR_INFO; 
typedef PROGRESSBAR_INFO*  pPROGRESSBAR_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *QR code information description
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _QRCODEBOX_INFO{
	
	WIDGET_BASE_INFO base_info;                
	WIDGET_LOCATION loc;                       
	gui_uint8  dispLogo;                       //Whether to display LOGO in the center, 0 does not show, 1 shows
	gui_color backColor;                       
	gui_color frontColor;                      
	gui_uint16 logoPicId;                     
	char  *text;                             
	                                           
	gui_uint16 maxLen;                         //The maximum length of the text box display, ASCII occupies one byte, Chinese occupies two bytes
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	gui_uint16 textLen;                        //Just the actual length of the current text
	WIDGET_EVENT pressEvent;                   
	WIDGET_EVENT releaseEvent;                 
	WIDGET_EVENT updateEvent;                  
}QRCODEBOX_INFO; 
typedef QRCODEBOX_INFO*  pQRCODEBOX_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *  Scrolling text message description
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _ROLLTEXTBOX_INFO{
	
	WIDGET_BASE_INFO base_info;               
	WIDGET_LOCATION loc;                      
	gui_uint8 backMode; //background mode
	gui_uint8 keyId; //Input keyboard ID. -1 means no keyboard
	gui_uint16 fontlibId; // font ID
	gui_uint8 borderWidth; //border line width, in pixels
	gui_color borderColor; //border color
	gui_uint16 picId; //background image ID
	gui_color backColor; //background color
	gui_color frontColor; //foreground color
	gui_uint8 xAlign; //horizontal alignment
	gui_uint8 yAlign; //vertical alignment
	gui_uint8 isPassword; //Whether to show password, 0 no 1 yes
	gui_uint8 isDr; //whether or not to show a line break when it is not down
	char  *text;                             
	gui_uint16 maxLen; //Maximum length of text box display, bytes
	gui_uint8 dir; //Text shift direction
	gui_uint8 dis; //Text movement amplitude, how many pixels per movement
	gui_uint16 timeOut; //Text movement period
	gui_uint8 enable; //text move enable, 0 no move, 1 move
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	gui_uint32 timeValue; 
	gui_uint16 textLen;                       //Just the actual length of the current text
	char *count_st;							  						//Text display start pointer
	gui_uint16 start_x;						 					  //The starting x coordinate of the text box display 
	WIDGET_EVENT pressEvent;                  
	WIDGET_EVENT releaseEvent;                
	WIDGET_EVENT updateEvent;                 
	WIDGET_EVENT timeoutEvent;                
}ROLLTEXTBOX_INFO; 
typedef ROLLTEXTBOX_INFO*  pROLLTEXTBOX_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Slider Information Description
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _SLIDER_INFO{
	
	WIDGET_BASE_INFO base_info;                
	WIDGET_LOCATION loc;                       
	gui_uint8 dir; //direction definition, horizontal or vertical
	gui_uint8 backMode; //background mode, cut, monochrome, picture
	gui_color backColor; //background color
	gui_uint16 backPicId; //background image
	gui_uint8 vernierMode; //cursor mode, monochrome, picture
	gui_color vernierColor; //cursor color
	gui_uint16 vernierPicId; //cursor picture
	gui_uint16 vernierWidth; //cursor width
	gui_uint16 vernierHeight; //cursor height
	gui_uint16 value; //cursor value
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	gui_uint16 v_last_x;                       //Position of the slider last time
	gui_uint16 v_last_y;
	WIDGET_EVENT pressEvent;                   
	WIDGET_EVENT releaseEvent;                 
	WIDGET_EVENT slidEvent;
	WIDGET_EVENT updateEvent;                  
}SLIDER_INFO; 
typedef SLIDER_INFO*  pSLIDER_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Text Box Message Description
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _TEXTBOX_INFO{
	
	WIDGET_BASE_INFO base_info;                
	WIDGET_LOCATION loc;                       
	gui_uint8 backMode;                        
	gui_uint8 keyId;                           //Enter the keyboard ID. -1 means no keyboard
	gui_uint16 fontlibId;                      
	gui_uint8 borderWidth;                     
	gui_color borderColor;                     
	gui_uint16 picId;                          
	gui_color backColor;                       
	gui_color frontColor;                      
	gui_uint8  xAlign;                         
	gui_uint8  yAlign;                         
	gui_uint8  isPassword;                     //Whether to display the password, 0 no 1 yes
	gui_uint8  isDr;                           
	char  *text;                               
	                                           
	                                           
	gui_uint16 maxLen;                         
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	gui_uint16 textLen;                       //Just the actual length of the current text
	WIDGET_EVENT pressEvent;                 
	WIDGET_EVENT releaseEvent;               
	WIDGET_EVENT updateEvent;                
}TEXTBOX_INFO; 
typedef TEXTBOX_INFO*  pTEXTBOX_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Touch hot zone information description
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _TOUCHAREA_INFO{
	
	WIDGET_BASE_INFO base_info;                
	WIDGET_LOCATION loc;                       
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	WIDGET_EVENT pressEvent;                   
	WIDGET_EVENT releaseEvent;                 
	WIDGET_EVENT updateEvent;                  
}TOUCHAREA_INFO; 
typedef TOUCHAREA_INFO*  pTOUCHAREA_INFO;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *Virtual GIF Control Description
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _VIRTUALGIF_INFO{
	
	WIDGET_BASE_INFO base_info;                
	WIDGET_LOCATION loc;                       
	gui_uint16 startPicId; //Gif first picture ID
	gui_uint16 endPicId; //Gif end picture ID
	gui_uint16 playTime; //frame interval
	gui_uint8 enable; //Playback switch bit, 0 off, 1 on
	gui_uint8 replayEnable; //Repeat play switch bit, 0 off, 1 on
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	gui_uint32 timeValue;                   
  gui_uint16   currentPicId;                 //Current picture ID
	WIDGET_EVENT pressEvent;                   
	WIDGET_EVENT releaseEvent;                 
	WIDGET_EVENT updateEvent;                 
	WIDGET_EVENT timeoutEvent;                

}VIRTUALGIF_INFO; 
typedef VIRTUALGIF_INFO*  pVIRTUALGIF_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 ** Round slider control description
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _ROUNDSLIDER_INFO{
	
	WIDGET_BASE_INFO base_info;                
	WIDGET_LOCATION loc;                       // set width=height
	gui_uint8 backMode; //background mode, monochrome, picture; monochrome mode slider for circle/circle (according to insideRadius)
	gui_color backColor; //background color (color of large circle when insideRadius=0, color of circle when insideRadius>0)
	gui_uint16 outerRadius; //background outer radius (valid in monochrome mode) (0<=innerRadius<outerRadius<=width/2)
	gui_uint16 insideRadius; // background inside radius (valid for monochrome mode) (0<=inside radius<outside radius<=width/2)
	gui_uint16 backPicId; //background image
	gui_uint8 vernierMode; // cursor mode, monochrome, picture; monochrome mode downstream cursor is a small solid circle, inner tangent to the circle slide, its center in r = (width/2 - vernierWidth/2) of the virtual circle movement
	gui_uint16 vernierWidth; // cursor width, regardless of monochrome and picture, the cursor must be square, only pass vernierWidth, height automatically locked equal to vernierWidth, if the upper user set the picture width and height is not equal to the pop-up prompt box
	gui_color vernierColor; //cursor color
	gui_uint16 vernierPicId; //cursor picture
	gui_uint16 value; //cursor value 0-360
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	gui_uint16 v_last_x;                       //Position of the slider last time
	gui_uint16 v_last_y;
  gui_uint16 value_min;
  gui_uint16 value_max;
	WIDGET_EVENT pressEvent;                   
	WIDGET_EVENT releaseEvent;                  
	WIDGET_EVENT slidEvent;
	WIDGET_EVENT updateEvent;                  
}ROUNDSLIDER_INFO; 
typedef ROUNDSLIDER_INFO*  pROUNDSLIDER_INFO;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 **  Image animation control description
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__packed typedef struct _PICANIMATION_INFO{
	
	WIDGET_BASE_INFO base_info;                
	WIDGET_LOCATION loc;                       
	gui_uint16 beforePicId; 				//the picture ID before the animation transition
	gui_uint16 afterPicId; 				//the picture ID after the animation transition
	gui_uint16 playTime; 				//frame time interval
	gui_uint8 pattern; 					//animation pattern
	gui_uint8 dis; 						//how many pixels to transform per unit time			
  gui_uint8 enable; 					//play switch bit, 0 off, 1 on
	gui_uint8 replayEnable; 				//Repeat play switch bit, 0 off, 1 on
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
  gui_uint32   timeValue;                      // 
  gui_uint16   flagover;                 //Current picture ID
  gui_uint16   currentplay;                  //Current picture frame rate
	WIDGET_EVENT pressEvent;               
	WIDGET_EVENT releaseEvent;             
	WIDGET_EVENT updateEvent;              
  WIDGET_EVENT timeoutEvent;               

}PICANIMATION_INFO; 
typedef PICANIMATION_INFO*  pPICANIMATION_INFO;

#ifdef __cplusplus
}
#endif
#endif
