#ifndef _DemoPage3_h
#define _DemoPage3_h
#include "gWidgetInfo.h"
#include "gStdint.h"
#include "gReturn.h"
#include "gResMsg.h"
/*********************************关机界面**********************************/
#define LTPwID 0x3101
static const PAGE_INFO LightTempPage={
	{.wType = WIDGET_TYPE_PAGE , .wId = LTPwID , .wVscope = WIDGET_VS_PRIVATE},
	{.x = 0 , .y = 0 , .width = 480 , .height = 320},
	.backMode = WIDGET_BACKMODE_PIC , 
	.backColor = 0x0000,
	.picId = 19,
	.enterEvent = GUI_NULL,
	.leaveEvent = GUI_NULL,
	.pressEvent = GUI_NULL,
	.releaseEvent = GUI_NULL,
};
#define LTPBackButtonwID 0x3102
static const BUTTON_INFO LightTempPageBackButton={
 {.wType = WIDGET_TYPE_BUTTON , .wId = LTPBackButtonwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0 , .y = 0 , .width = 55 , .height = 38},
 .backMode = WIDGET_BACKMODE_CUTPIC,
 .fontlibId = 0,              
 .borderWidth = 1,              
 .borderColor = 0xFFDC,        
 .pressPicId  = 19,             
 .releasePicId = 21,            
 .pressBackColor = 0x0020,
 .releaseBackColor = 0xBDF7,   
 .pressFontColor = 0xFFFF,        
 .releaseFontColor = 0x0000,      
 .xAlign = 1,
 .yAlign = 1,
 .isDr = 1,                   
 .text = (char *)0x04,
 .maxLen = 0x06,
 .pressEvent = GUI_NULL,
 .releaseEvent = GUI_NULL,
 .updateEvent = GUI_NULL,
};
#define LTPSwitchButtonwID 0x3103
static const BINARYBUTTON_INFO LightTempPageSwitchButton={    
 {.wType = WIDGET_TYPE_BINARYBUTTON , .wId = LTPSwitchButtonwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 95 , .y = 140 , .width = 110 , .height = 85},
 .backMode = WIDGET_BACKMODE_CUTPIC,              
 .fontlibId = 0,                      
 .borderWidth = 1,                   
 .borderColor = 0xFFDC, 
 .enablePicId = 20,
 .disenablePicId = 19,
 .enableBackColor = 0x0020,
 .disenableBackColor = 0x631C,
 .enableFontColor = 0x631C,  
 .disenableFontColor = 0xFFFF,
 .xAlign = 1,                        
 .yAlign = 1, 
 .isDr = 1,                         
 .value = 0,                  
 .text = (char *)0x00,    
 .maxLen = 0x0016,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};
gui_Err LightTempPageEnterEvent(gui_int32 argc , const char **argv);
gui_Err LightTempPageLeaveEvent(gui_int32 argc , const char **argv);
static gui_Err LightPageTurnON_releaseEvent(gui_int32 argc , const char **argv);
static gui_Err LightTempPageBack_releaseEvent(gui_int32 argc , const char **argv);
/*********************************开机界面**********************************/
#define LPwID 0x3001
static const PAGE_INFO LightPage={
	{.wType = WIDGET_TYPE_PAGE , .wId = LPwID , .wVscope = WIDGET_VS_PRIVATE},
	{.x = 0 , .y = 0 , .width = 480 , .height = 320},
	.backMode = WIDGET_BACKMODE_PIC , 
	.backColor = 0x0000,
	.picId = 20,
	.enterEvent = GUI_NULL,
	.leaveEvent = GUI_NULL,
	.pressEvent = GUI_NULL,
	.releaseEvent = GUI_NULL,
};
#define LPSwitchButtonwID 0x3002
static const BINARYBUTTON_INFO LightPageSwitchButton={    
 {.wType = WIDGET_TYPE_BINARYBUTTON , .wId = LPSwitchButtonwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 95 , .y = 140 , .width = 110 , .height = 85},
 .backMode = WIDGET_BACKMODE_CUTPIC,              
 .fontlibId = 0,                      
 .borderWidth = 1,                   
 .borderColor = 0xFFDC, 
 .enablePicId = 19,
 .disenablePicId = 20,
 .enableBackColor = 0x0020,
 .disenableBackColor = 0x631C,
 .enableFontColor = 0x631C,  
 .disenableFontColor = 0xFFFF,
 .xAlign = 1,                        
 .yAlign = 1, 
 .isDr = 1,                         
 .value = 0,                  
 .text = (char *)0x00,    
 .maxLen = 0x0016,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};
#define LPSleepButtonwID 0x3003
static const BINARYBUTTON_INFO LightPageSleepButton={
 {.wType = WIDGET_TYPE_BINARYBUTTON , .wId = LPSleepButtonwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 8 , .y = 235 , .width = 85 , .height = 70},
 .backMode = WIDGET_BACKMODE_CUTPIC,              
 .fontlibId = 0,                      
 .borderWidth = 1,                   
 .borderColor = 0xFFDC, 
 .enablePicId = 21,
 .disenablePicId = 20,
 .enableBackColor = 0x0020,
 .disenableBackColor = 0x631C,
 .enableFontColor = 0x631C,  
 .disenableFontColor = 0xFFFF,
 .xAlign = 1,                        
 .yAlign = 1, 
 .isDr = 1,                         
 .value = 0,                  
 .text = (char *)0x00,    
 .maxLen = 0x0016,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};
#define LPEveButtonwID 0x3004
static const BINARYBUTTON_INFO LightPageEveButton={
 {.wType = WIDGET_TYPE_BINARYBUTTON , .wId = LPEveButtonwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 103 , .y = 235 , .width = 85 , .height = 70},
 .backMode = WIDGET_BACKMODE_CUTPIC,              
 .fontlibId = 0,                      
 .borderWidth = 1,                   
 .borderColor = 0xFFDC, 
 .enablePicId = 21,
 .disenablePicId = 20,
 .enableBackColor = 0x0020,
 .disenableBackColor = 0x631C,
 .enableFontColor = 0x631C,  
 .disenableFontColor = 0xFFFF,
 .xAlign = 1,                        
 .yAlign = 1, 
 .isDr = 1,                         
 .value = 0,                  
 .text = (char *)0x00,    
 .maxLen = 0x0016,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};
#define LPReadButtonwID 0x3005
static const BINARYBUTTON_INFO LightPageReadButton={
 {.wType = WIDGET_TYPE_BINARYBUTTON , .wId = LPReadButtonwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 198 , .y = 235 , .width = 85 , .height = 70},
 .backMode = WIDGET_BACKMODE_CUTPIC,              
 .fontlibId = 0,                      
 .borderWidth = 1,                   
 .borderColor = 0xFFDC, 
 .enablePicId = 21,
 .disenablePicId = 20,
 .enableBackColor = 0x0020,
 .disenableBackColor = 0x631C,
 .enableFontColor = 0x631C,  
 .disenableFontColor = 0xFFFF,
 .xAlign = 1,                        
 .yAlign = 1, 
 .isDr = 1,                         
 .value = 0,                  
 .text = (char *)0x00,    
 .maxLen = 0x0016,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};
#define LPOfficeButtonwID 0x3006
static const BINARYBUTTON_INFO LightPageOfficeButton={
 {.wType = WIDGET_TYPE_BINARYBUTTON , .wId = LPOfficeButtonwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 293 , .y = 235 , .width = 85 , .height = 70},
 .backMode = WIDGET_BACKMODE_CUTPIC,              
 .fontlibId = 0,                      
 .borderWidth = 1,                   
 .borderColor = 0xFFDC, 
 .enablePicId = 21,
 .disenablePicId = 20,
 .enableBackColor = 0x0020,
 .disenableBackColor = 0x631C,
 .enableFontColor = 0x631C,  
 .disenableFontColor = 0xFFFF,
 .xAlign = 1,                        
 .yAlign = 1, 
 .isDr = 1,                         
 .value = 0,                  
 .text = (char *)0x00,    
 .maxLen = 0x0016,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};
#define LPSunButtonwID 0x3007
static const BINARYBUTTON_INFO LightPageSunButton={
 {.wType = WIDGET_TYPE_BINARYBUTTON , .wId = LPSunButtonwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 388 , .y = 235 , .width = 85 , .height = 70},
 .backMode = WIDGET_BACKMODE_CUTPIC,              
 .fontlibId = 0,                      
 .borderWidth = 1,                   
 .borderColor = 0xFFDC, 
 .enablePicId = 21,
 .disenablePicId = 20,
 .enableBackColor = 0x0020,
 .disenableBackColor = 0x631C,
 .enableFontColor = 0x631C,  
 .disenableFontColor = 0xFFFF,
 .xAlign = 1,                        
 .yAlign = 1, 
 .isDr = 1,                         
 .value = 0,                  
 .text = (char *)0x00,    
 .maxLen = 0x0016,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};
#define LPBackButtonwID 0x3008
static const BUTTON_INFO LightPageBackButton={
 {.wType = WIDGET_TYPE_BUTTON , .wId = LPBackButtonwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 0 , .y = 0 , .width = 55 , .height = 38},
 .backMode = WIDGET_BACKMODE_CUTPIC,
 .fontlibId = 0,              
 .borderWidth = 1,              
 .borderColor = 0xFFDC,        
 .pressPicId  = 19,             
 .releasePicId = 21,            
 .pressBackColor = 0x0020,
 .releaseBackColor = 0xBDF7,   
 .pressFontColor = 0xFFFF,        
 .releaseFontColor = 0x0000,      
 .xAlign = 1,
 .yAlign = 1,
 .isDr = 1,                   
 .text = (char *)0x04,
 .maxLen = 0x06,
 .pressEvent = GUI_NULL,
 .releaseEvent = GUI_NULL,
 .updateEvent = GUI_NULL,
};
#define LPOptionBox1wID 0x3009
static const OPTIONBOX_INFO LightPageOptionBox1={   
 {.wType = WIDGET_TYPE_OPTIONBOX , .wId = LPOptionBox1wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 120 , .y = 116 , .width = 20 , .height = 20},
 .backMode = WIDGET_BACKMODE_COLOR ,  
 .optionType = OPTIONBOX_TYPE_RECT,
 .backColor = 0xFFFF,
 .frontColor = 0x0000,
 .cPicId = 0,                      
 .nocPicId = 1,                    
 .value = OPTIONBOX_STATE_NOCHOOSE,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL       
};
#define LPOptionBox2wID 0x300A
static const OPTIONBOX_INFO LightPageOptionBox2={   
 {.wType = WIDGET_TYPE_OPTIONBOX , .wId = LPOptionBox2wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 230 , .y = 116 , .width = 20 , .height = 20},
 .backMode = WIDGET_BACKMODE_COLOR ,  
 .optionType = OPTIONBOX_TYPE_RECT,
 .backColor = 0xFFFF,
 .frontColor = 0x0000,
 .cPicId = 5,                      
 .nocPicId = 1,                    
 .value = OPTIONBOX_STATE_CHOOSE,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL       
};
#define LPOptionBox3wID 0x300B
static const OPTIONBOX_INFO LightPageOptionBox3={   
 {.wType = WIDGET_TYPE_OPTIONBOX , .wId = LPOptionBox3wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 340 , .y = 116 , .width = 20 , .height = 20},
 .backMode = WIDGET_BACKMODE_COLOR ,  
 .optionType = OPTIONBOX_TYPE_RECT,
 .backColor = 0xFFFF,
 .frontColor = 0x0000,
 .cPicId = 0,                      
 .nocPicId = 1,                    
 .value = OPTIONBOX_STATE_NOCHOOSE,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL       
};
#define LPTextBox1wID 0x300C
static const TEXTBOX_INFO LightPageTextBox1={
 {.wType = WIDGET_TYPE_TEXTBOX , .wId = LPTextBox1wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 142 , .y = 113 , .width = 50 , .height = 30},
 .backMode = WIDGET_BACKMODE_CUTPIC,                 
 .keyId = 255,                          
 .fontlibId = 0,                     
 .borderWidth = 0,                   
 .borderColor = 0x00FF,              
 .picId = 21,                         
 .backColor = 0x0000,
 .frontColor = 0x0000,
 .xAlign = 0,                        
 .yAlign = 1,                       
 .isPassword = 0,                  
 .isDr = 0,   
 .text = (char *)0x00,                 
 .maxLen = 0x00014,                   
 .textLen = 0x0005,            
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL                   
};
#define LPTextBox2wID 0x300D
static const TEXTBOX_INFO LightPageTextBox2={
 {.wType = WIDGET_TYPE_TEXTBOX , .wId = LPTextBox2wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 251 , .y = 113 , .width = 50 , .height = 30},
 .backMode = WIDGET_BACKMODE_CUTPIC,                 
 .keyId = 255,                          
 .fontlibId = 0,                     
 .borderWidth = 0,                   
 .borderColor = 0x00FF,              
 .picId = 21,                         
 .backColor = 0x0000,
 .frontColor = 0x0000,
 .xAlign = 0,                        
 .yAlign = 1,                       
 .isPassword = 0,                  
 .isDr = 0,   
 .text = (char *)0x00,                 
 .maxLen = 0x00014,                   
 .textLen = 0x0005,            
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL                   
};
#define LPTextBox3wID 0x300E
static const TEXTBOX_INFO LightPageTextBox3={
 {.wType = WIDGET_TYPE_TEXTBOX , .wId = LPTextBox3wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 361 , .y = 113 , .width = 50 , .height = 30},
 .backMode = WIDGET_BACKMODE_CUTPIC,                 
 .keyId = 255,                          
 .fontlibId = 0,                     
 .borderWidth = 0,                   
 .borderColor = 0x00FF,              
 .picId = 21,                         
 .backColor = 0x0000,
 .frontColor = 0x0000,
 .xAlign = 0,                        
 .yAlign = 1,                       
 .isPassword = 0,                  
 .isDr = 0,   
 .text = (char *)0x00,                 
 .maxLen = 0x00014,                   
 .textLen = 0x0005,            
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL                   
};
#define LPSlider1wID 0x300F
static const SLIDER_INFO LightPageSlider1={    
 {.wType = WIDGET_TYPE_SLIDER , .wId = LPSlider1wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 30 , .y = 60 , .width = 32 , .height = 170},  
 .dir = SLIDER_DIR_V,
 .backMode = WIDGET_BACKMODE_PIC,
 .backColor = 0xFF00,
 .backPicId = 22,
 .vernierMode = WIDGET_BACKMODE_PIC,
 .vernierColor = 0x00FF,
 .vernierPicId = 18,
 .vernierWidth = 32,
 .vernierHeight = 32,
 .value = 100,
 .v_last_x = 0,                    
 .v_last_y = 0,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL, 
 .slidEvent = GUI_NULL, 
 .updateEvent = GUI_NULL  
};
#define LPSlider2wID 0x3010
static const SLIDER_INFO LightPageSlider2={    
 {.wType = WIDGET_TYPE_SLIDER , .wId = LPSlider2wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 421 , .y = 60 , .width = 32 , .height = 170},  
 .dir = SLIDER_DIR_V,
 .backMode = WIDGET_BACKMODE_PIC,
 .backColor = 0xFF00,
 .backPicId = 23,
 .vernierMode = WIDGET_BACKMODE_PIC,
 .vernierColor = 0x00FF,
 .vernierPicId = 24,
 .vernierWidth = 32,
 .vernierHeight = 32,
 .value = 100,
 .v_last_x = 0,                    
 .v_last_y = 0,
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL, 
 .slidEvent = GUI_NULL, 
 .updateEvent = GUI_NULL  
};

#define LPNumBox1wID 0x3011
static const NUMBERBOX_INFO LightPageNumberBox1={
 {.wType = WIDGET_TYPE_NUMBERBOX , .wId = LPNumBox1wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 207 , .y = 8 , .width = 75 , .height = 20},
 .backMode = WIDGET_BACKMODE_CUTPIC,              
 .keyId = 255,                          
 .fontlibId = 0,                      
 .borderWidth = 1,                   
 .borderColor = 0xFFDC,              
 .picId = 20,                         
 .backColor = 0x00FF,
 .frontColor = 0x0000,
 .xAlign = 1,                        
 .yAlign = 1, 
 .formatType = 0,                     
 .isDr = 0,                           
 .data = 100,
 .maxLen = 3,                      
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};
#define LPNumBox2wID 0x3012
static const NUMBERBOX_INFO LightPageNumberBox2={
 {.wType = WIDGET_TYPE_NUMBERBOX , .wId = LPNumBox2wID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 207 , .y = 40 , .width = 75 , .height = 20},
 .backMode = WIDGET_BACKMODE_CUTPIC,              
 .keyId = 255,                          
 .fontlibId = 0,                      
 .borderWidth = 1,                   
 .borderColor = 0xFFDC,              
 .picId = 20,                         
 .backColor = 0x00FF,
 .frontColor = 0x0000,
 .xAlign = 1,                        
 .yAlign = 1, 
 .formatType = 0,                     
 .isDr = 0,                           
 .data = 6500,
 .maxLen = 4,                      
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};
#define LPNumBoxAwID 0x3013
static const NUMBERBOX_INFO LightPageNumberBoxA={
 {.wType = WIDGET_TYPE_NUMBERBOX , .wId = LPNumBoxAwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 65 , .y = 215 , .width = 20 , .height = 20},
 .backMode = WIDGET_BACKMODE_CUTPIC,              
 .keyId = 255,                          
 .fontlibId = 0,                      
 .borderWidth = 1,                   
 .borderColor = 0xFFDC,              
 .picId = 20,                         
 .backColor = 0x00FF,
 .frontColor = 0x0000,
 .xAlign = 0,                        
 .yAlign = 1, 
 .formatType = 0,                     
 .isDr = 0,                           
 .data = 1,
 .maxLen = 1,                      
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};
#define LPNumBoxBwID 0x3014
static const NUMBERBOX_INFO LightPageNumberBoxB={
 {.wType = WIDGET_TYPE_NUMBERBOX , .wId = LPNumBoxBwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 65 , .y = 65 , .width = 30 , .height = 20},
 .backMode = WIDGET_BACKMODE_CUTPIC,              
 .keyId = 255,                          
 .fontlibId = 0,                      
 .borderWidth = 1,                   
 .borderColor = 0xFFDC,              
 .picId = 20,                         
 .backColor = 0x00FF,
 .frontColor = 0x0000,
 .xAlign = 0,                        
 .yAlign = 1, 
 .formatType = 0,                     
 .isDr = 0,                           
 .data = 100,
 .maxLen = 3,                      
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};
#define LPNumBoxCwID 0x3015
static const NUMBERBOX_INFO LightPageNumberBoxC={
 {.wType = WIDGET_TYPE_NUMBERBOX , .wId = LPNumBoxCwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 385 , .y = 65 , .width = 35 , .height = 20},
 .backMode = WIDGET_BACKMODE_CUTPIC,              
 .keyId = 255,                          
 .fontlibId = 0,                      
 .borderWidth = 1,                   
 .borderColor = 0xFFDC,              
 .picId = 20,                         
 .backColor = 0x00FF,
 .frontColor = 0x0000,
 .xAlign = 1,                        
 .yAlign = 1, 
 .formatType = 0,                     
 .isDr = 0,                           
 .data = 6500,
 .maxLen = 4,                      
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};
#define LPNumBoxDwID 0x3016
static const NUMBERBOX_INFO LightPageNumberBoxD={
 {.wType = WIDGET_TYPE_NUMBERBOX , .wId = LPNumBoxDwID , .wVscope = WIDGET_VS_PRIVATE},
 {.x = 385 , .y = 215 , .width = 35 , .height = 20},
 .backMode = WIDGET_BACKMODE_CUTPIC,              
 .keyId = 255,                          
 .fontlibId = 0,                      
 .borderWidth = 1,                   
 .borderColor = 0xFFDC,              
 .picId = 20,                         
 .backColor = 0x00FF,
 .frontColor = 0x0000,
 .xAlign = 1,                        
 .yAlign = 1, 
 .formatType = 0,                     
 .isDr = 0,                           
 .data = 3000,
 .maxLen = 4,                      
 .pressEvent = GUI_NULL,               
 .releaseEvent = GUI_NULL,             
 .updateEvent = GUI_NULL 
};
gui_Err LightPageEnterEvent(gui_int32 argc , const char **argv);
gui_Err LightPageLeaveEvent(gui_int32 argc , const char **argv);
static gui_Err BackToHome_releaseEvent_releaseEvent(gui_int32 argc , const char **argv);
static gui_Err LightPageOFF_releaseEvent(gui_int32 argc , const char **argv);
static gui_Err LightPageBinaryS_pressEvent(gui_int32 argc , const char **argv);
static gui_Err LightPageBinaryE_pressEvent(gui_int32 argc , const char **argv);
static gui_Err LightPageBinaryR_pressEvent(gui_int32 argc , const char **argv);
static gui_Err LightPageBinaryO_pressEvent(gui_int32 argc , const char **argv);
static gui_Err LightPageBinaryL_pressEvent(gui_int32 argc , const char **argv);
static gui_Err LightPageOption1_pressEvent(gui_int32 argc , const char **argv);
static gui_Err LightPageOption2_pressEvent(gui_int32 argc , const char **argv);
static gui_Err LightPageOption3_pressEvent(gui_int32 argc , const char **argv);
static gui_Err GetLuminance_slideEvent(gui_int32 argc , const char **argv);
static gui_Err GetColorTemp_slideEvent(gui_int32 argc , const char **argv);



#endif
