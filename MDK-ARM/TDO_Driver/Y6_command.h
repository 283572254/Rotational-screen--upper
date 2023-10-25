#ifndef _Y6_command_h
#define _Y6_command_h

 #include "comInterface.h"
 #include <stdint.h>
#include "gStdint.h"


typedef enum
{
  Y6_NO_CMD=(int)-3,      //Unsupported commands
  Y6_NULL_CMD=(int)-2,    //Empty command
	Y6_FAILED_CMD=(int)-1,  //Command execution failed
	Y6_OK_CMD               //Normal execution of the command, other values >= 0, indicating that the execution results need to reply
}Y6_CMD_State;

typedef Y6_CMD_State (*Y6_FUNC)(gui_uint8 cmd,const void *charc,uint32_t c_len);
															
#define Y6_FUNCSTRNAME_MAXLEN   16
typedef struct __Y6_FUNCSTR
{
	char Y6_Name[Y6_FUNCSTRNAME_MAXLEN];//Function Name
	Y6_FUNC Y6_Func;//Function Pointer
}Y6_FUNCSTR;
extern uint8_t Send_head_tail[5] ;
 void Cmd_R(uint8_t *charc , uint8_t c_len);	
#define Y6_COMMAND_MAXCOUNT     250
extern const Y6_FUNCSTR Y6_SystemCommand_Tab[Y6_COMMAND_MAXCOUNT];
void Y6_Communication_Loop(void);//SystemUart Message Loop

#endif


