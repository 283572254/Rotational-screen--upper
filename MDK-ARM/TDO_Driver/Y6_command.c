
#include "Y6_command.h"
#include <stdio.h>
#include <string.h>
#include "memoryInterface.h"
#include <stdint.h>
#include "Y6_include_conf.h"
#define HMICMDLEN  400
static uint8_t  HMIuart_data[HMICMDLEN];         
static uint8_t handleBuff_data[HMICMDLEN];         
  
static Y6_CMD_State Y6_command_Handle(uint8_t cmd, const void *charc,uint32_t c_len);
 uint8_t Serial_Flag=1;

void Y6_Communication_Loop(void)
{
	
	uint8_t *receiveBuff = Com_Des.getInputBuff();
	
	if(Com_Des.getInputStatus() == COM_RECEIVED_NO)return; //Ask if reception is complete	
	uint32_t receiveLen = Com_Des.getInputLen();//Get the received length
	Memory_Des.memcpy(handleBuff_data ,receiveBuff,receiveLen);
	Com_Des.clearInputBuff();
	
	 uint8_t data_flag=0;
	static uint16_t datalen=0;	
	
 	uint8_t cmd;
    for(uint16_t i=0;i<receiveLen;i++)
	{
			data_flag = *(handleBuff_data+i);
		 	#if  USE_PRINTF_DEBUG
	 	     //	printf("%#x ",data_flag);
			#endif
			if(datalen >= 5)
			{
				HMIuart_data[datalen++] = data_flag;  
				if((0xCC==HMIuart_data[datalen-4])&&(0x33==HMIuart_data[datalen-3])&&(0xC3==HMIuart_data[datalen-2])&&(0x3C==HMIuart_data[datalen-1]))
				{    //Command frame end.   CC 33 C3 3C
					 cmd = HMIuart_data[1];					
				 	 Y6_command_Handle(cmd, &HMIuart_data[2],datalen-6);							
					 datalen = 0;										
				}
			}
			else if(datalen == 0 && data_flag == 0xAA)  //Command frame header.   AA
			{
						HMIuart_data[datalen++] = data_flag;
			}
			else if(datalen < 5)
			{
						HMIuart_data[datalen++] = data_flag;
			}
	}	
 
}

static Y6_CMD_State Y6_command_Handle(uint8_t cmd ,const void *charc,uint32_t c_len)
{
	if(cmd>=Y6_COMMAND_MAXCOUNT)
	{
 		return Y6_NO_CMD;
	}
	else
	{
		
	}
 	return Y6_SystemCommand_Tab[cmd].Y6_Func( cmd,charc,c_len);
}

static Y6_CMD_State Y6_NULL_HANDLE( uint8_t cmd,const void *charc,uint32_t c_len)
{

	return Y6_NULL_CMD;
}

//System Instruction Set Index Table
//Users are free to add and change instructions and refactor this part of the code while maintaining full functionality.
extern Y6_CMD_State Y6_Return( uint8_t cmd,const void *charc,uint32_t c_len);
extern Y6_CMD_State Y6_ClearScreen( uint8_t cmd,const void *charc,uint32_t c_len);
extern Y6_CMD_State Y6_SetHMIColor( uint8_t cmd,const void *charc,uint32_t c_len);
extern Y6_CMD_State Y6_HMISet_Work_Mode( uint8_t cmd,const void *charc,uint32_t c_len);
extern Y6_CMD_State Y6_HMI_led_Opera( uint8_t cmd,const void *charc,uint32_t c_len);
extern Y6_CMD_State Y6_HMI_RESET( uint8_t cmd,const void *charc,uint32_t c_len);
extern  Y6_CMD_State Y6_Set_Key( uint8_t cmd,const void *charc,uint32_t c_len);


const Y6_FUNCSTR Y6_SystemCommand_Tab[Y6_COMMAND_MAXCOUNT]=
{
	{"CmdReturn",    			Y6_Return},          //0  
	{"NULL",		   			Y6_NULL_HANDLE},            //1
	{"NULL",	   				Y6_NULL_HANDLE},            //2
	{"NULL",	 				Y6_NULL_HANDLE},            //3
	{"NULL",	 				Y6_NULL_HANDLE},            //4
	{"NULL",		     		Y6_NULL_HANDLE},            //5
	{"NULL",					Y6_NULL_HANDLE},            //6
	{"NULL",					Y6_NULL_HANDLE},            //7
	{"NULL",					Y6_NULL_HANDLE},            //8
	{"NULL",					Y6_NULL_HANDLE},            //9
	{"NULL",					Y6_NULL_HANDLE},            //10
	{"NULL",					Y6_NULL_HANDLE},            //11
	{"NULL",					Y6_NULL_HANDLE},            //12
	{"NULL",					Y6_NULL_HANDLE},            //13
	{"NULL",					Y6_NULL_HANDLE},            //14
	{"NULL",					Y6_NULL_HANDLE},            //15
	{"NULL",					Y6_NULL_HANDLE},            //16
	{"NULL",					Y6_NULL_HANDLE},            //17
	{"NULL",					Y6_NULL_HANDLE},            //18
	{"NULL",					Y6_NULL_HANDLE},            //19
	{"NULL",					Y6_NULL_HANDLE},            //20
	{"NULL",					Y6_NULL_HANDLE},            //21
	{"NULL",					Y6_NULL_HANDLE},            //22
	{"NULL",					Y6_NULL_HANDLE},            //23
	{"NULL",					Y6_NULL_HANDLE},            //24
	{"NULL",					Y6_NULL_HANDLE},            //25
	{"NULL",					Y6_NULL_HANDLE},            //26
	{"NULL",					Y6_NULL_HANDLE},            //27
	{"NULL",					Y6_NULL_HANDLE},            //28
	{"NULL",					Y6_NULL_HANDLE},            //29
	{"NULL",					Y6_NULL_HANDLE},            //30
	{"NULL",					Y6_NULL_HANDLE},            //31
	{"NULL",					Y6_NULL_HANDLE},            //32
	{"NULL",					Y6_NULL_HANDLE},            //33
	{"NULL",					Y6_NULL_HANDLE},            //34
	{"NULL",					Y6_NULL_HANDLE},            //35
	{"NULL",					Y6_NULL_HANDLE},            //36
	{"NULL",					Y6_NULL_HANDLE},            //37
	{"NULL",					Y6_NULL_HANDLE},            //38
	{"NULL",					Y6_NULL_HANDLE},            //39
	{"NULL",					Y6_NULL_HANDLE},            //40
	{"NULL",					Y6_NULL_HANDLE},            //41   
	{"NULL",					Y6_NULL_HANDLE},            //42
	{"NULL",					Y6_NULL_HANDLE},            //43
	{"NULL",					Y6_NULL_HANDLE},            //44
	{"NULL",					Y6_NULL_HANDLE},            //45
	{"NULL",					Y6_NULL_HANDLE},            //46
	{"NULL",					Y6_NULL_HANDLE},            //47
	{"NULL",					Y6_NULL_HANDLE},            //48
	{"NULL",					Y6_NULL_HANDLE},            //49
	{"NULL",					Y6_NULL_HANDLE},            //50
	{"NULL",					Y6_NULL_HANDLE},            //51
	{"NULL",					Y6_NULL_HANDLE},            //52
	{"NULL",					Y6_NULL_HANDLE},            //53
	{"NULL",					Y6_NULL_HANDLE},            //54
	{"NULL",					Y6_NULL_HANDLE},            //55
	{"NULL",					Y6_NULL_HANDLE},            //56
	{"NULL",					Y6_NULL_HANDLE},            //57
	{"NULL",					Y6_NULL_HANDLE},            //58
	{"NULL",					Y6_NULL_HANDLE},            //59
	{"NULL",					Y6_NULL_HANDLE},            //60
	{"NULL",					Y6_NULL_HANDLE},            //61
	{"NULL",					Y6_NULL_HANDLE},            //62
	{"NULL",					Y6_NULL_HANDLE},            //63
	{"NULL",					Y6_NULL_HANDLE},            //64  
	{"NULL",					Y6_NULL_HANDLE},            //65  
	{"NULL",					Y6_NULL_HANDLE},            //66
	{"NULL",					Y6_NULL_HANDLE},            //67
	{"NULL",					Y6_NULL_HANDLE},            //68  
	{"NULL",					Y6_NULL_HANDLE},           	 //69  
	{"NULL",					Y6_NULL_HANDLE},            //70
	{"NULL",					Y6_NULL_HANDLE},            //71
	{"NULL",					Y6_NULL_HANDLE},            //72
	{"NULL",					Y6_NULL_HANDLE},            //73
	{"NULL",					Y6_NULL_HANDLE},            //74 
	{"NULL",					Y6_NULL_HANDLE},            //75
	{"NULL",					Y6_NULL_HANDLE},            //76
	{"NULL",					Y6_NULL_HANDLE},            //77
	{"NULL",			   	 	Y6_NULL_HANDLE},            //78
	{"NULL",		   	  	Y6_NULL_HANDLE},            //79
	{"NULL",			    Y6_NULL_HANDLE},            //80  
	{"NULL",			    Y6_NULL_HANDLE},           //81  
	{"ClearScreen",			Y6_ClearScreen},            //82  
	{"NULL",					Y6_NULL_HANDLE},            //83  
	{"NULL",					Y6_NULL_HANDLE},            //84  
	{"NULL",					Y6_NULL_HANDLE},            //85  
	{"NULL",					Y6_NULL_HANDLE},            //86  
	{"NULL",					Y6_NULL_HANDLE},            //87  
	{"NULL",					Y6_NULL_HANDLE},            //88  
	{"NULL",					Y6_NULL_HANDLE},            //89 
	{"NULL",					Y6_NULL_HANDLE},            //90  
	{"NULL",					Y6_NULL_HANDLE},            //91  
	{"NULL",					Y6_NULL_HANDLE},            //92  
	{"NULL",					Y6_NULL_HANDLE},            //93  
	{"HMI_led_Opera",		Y6_HMI_led_Opera},            //94  
	{"HMI_led_Opera",		Y6_HMI_led_Opera},            //95  
	{"NULL",					Y6_NULL_HANDLE},            //96
	{"NULL",					Y6_NULL_HANDLE},            //97
	{"NULL",					Y6_NULL_HANDLE},            //98
	{"NULL",					Y6_NULL_HANDLE},             //99 
	{"Set_Key",					Y6_Set_Key},            //100	 
	
	{"NULL",					Y6_NULL_HANDLE},            //101
	{"NULL",					Y6_NULL_HANDLE},            //102
	{"NULL",					Y6_NULL_HANDLE},            //103
	{"NULL",					Y6_NULL_HANDLE},            //104
	{"NULL",					Y6_NULL_HANDLE},            //105   
	{"NULL",					Y6_NULL_HANDLE},            //106
	{"NULL",					Y6_NULL_HANDLE},            //107
	{"NULL",					Y6_NULL_HANDLE},            //108
	{"NULL",					Y6_NULL_HANDLE},            //109
	{"NULL",					Y6_NULL_HANDLE},            //110  
	{"NULL",					Y6_NULL_HANDLE},            //111   
	{"NULL",					Y6_NULL_HANDLE},            //112 
	{"NULL",					Y6_NULL_HANDLE},            //113  
	{"NULL",					Y6_NULL_HANDLE},            //114  
	{"NULL",					Y6_NULL_HANDLE},            //115  
	{"NULL",					Y6_NULL_HANDLE},            //116   	 
	{"NULL",					Y6_NULL_HANDLE},            //117    
	{"NULL",					Y6_NULL_HANDLE},            //118     
	{"NULL",					Y6_NULL_HANDLE},            //119
	{"NULL",					Y6_NULL_HANDLE},            //120  
	{"NULL",					Y6_NULL_HANDLE},            //121 
	{"NULL",					Y6_NULL_HANDLE},            //122
	{"NULL",					Y6_NULL_HANDLE},            //123
	{"NULL",					Y6_NULL_HANDLE},            //124
	{"NULL",					Y6_NULL_HANDLE},            //125
	{"NULL",					Y6_NULL_HANDLE},            //126
	{"NULL",					Y6_NULL_HANDLE},            //127
	{"NULL",					Y6_NULL_HANDLE},            //128    
	{"NULL",					Y6_NULL_HANDLE},            //129
	{"NULL",					Y6_NULL_HANDLE},            //130
	{"NULL",					Y6_NULL_HANDLE},            //131
	{"NULL",					Y6_NULL_HANDLE},            //132
	{"NULL",					Y6_NULL_HANDLE},            //133
	{"NULL",					Y6_NULL_HANDLE},            //134
	{"NULL",					Y6_NULL_HANDLE},            //135
	{"NULL",					Y6_NULL_HANDLE},            //136
	{"NULL",					Y6_NULL_HANDLE},            //137
	{"NULL",					Y6_NULL_HANDLE},            //138
	{"NULL",					Y6_NULL_HANDLE},            //139
	{"NULL",					Y6_NULL_HANDLE},            //140
	{"NULL",					Y6_NULL_HANDLE},            //141
	{"HMI_RESET",				Y6_HMI_RESET},            //142     //Reboot
	{"NULL",					Y6_NULL_HANDLE},            //143
	{"NULL",					Y6_NULL_HANDLE},            //144
	{"NULL",					Y6_NULL_HANDLE},            //145
	{"NULL",					Y6_NULL_HANDLE},            //146
	{"NULL",					Y6_NULL_HANDLE},            //147
	{"NULL",					Y6_NULL_HANDLE},            //148
	{"NULL",					Y6_NULL_HANDLE},            //149
	{"NULL",					Y6_NULL_HANDLE},            //150
	{"NULL",					Y6_NULL_HANDLE},            //151 
	{"NULL",					Y6_NULL_HANDLE},            //152  
	{"NULL",					Y6_NULL_HANDLE},            //153  
	{"NULL",					Y6_NULL_HANDLE},            //154
	{"NULL",					Y6_NULL_HANDLE},            //155  
	{"NULL",					Y6_NULL_HANDLE},            //156  
	{"NULL",					Y6_NULL_HANDLE},            //157  
	{"NULL",					Y6_NULL_HANDLE},            //158
	{"NULL",					Y6_NULL_HANDLE},            //159  
	{"NULL",					Y6_NULL_HANDLE},            //160
	{"NULL",					Y6_NULL_HANDLE},            //161
	{"NULL",					Y6_NULL_HANDLE},            //162
	{"NULL",					Y6_NULL_HANDLE},            //163
	{"NULL",					Y6_NULL_HANDLE},            //164
	{"NULL",					Y6_NULL_HANDLE},            //165
	{"NULL",					Y6_NULL_HANDLE},            //166
	{"NULL",					Y6_NULL_HANDLE},            //167
	{"NULL",					Y6_NULL_HANDLE},            //168
	{"NULL",					Y6_NULL_HANDLE},            //169
	{"NULL",					Y6_NULL_HANDLE},            //170
	{"NULL",					Y6_NULL_HANDLE},            //171
	{"NULL",					Y6_NULL_HANDLE},            //172
	{"NULL",					Y6_NULL_HANDLE},            //173
	{"NULL",					Y6_NULL_HANDLE},            //174
	{"NULL",					Y6_NULL_HANDLE},            //175
	{"NULL",					Y6_NULL_HANDLE},            //176
	{"NULL",					Y6_NULL_HANDLE},            //177
	{"NULL",					Y6_NULL_HANDLE},            //178
	{"NULL",					Y6_NULL_HANDLE},            //179
	{"NULL",					Y6_NULL_HANDLE},            //180
	{"NULL",					Y6_NULL_HANDLE},            //181
	{"NULL",					Y6_NULL_HANDLE},            //182
	{"NULL",					Y6_NULL_HANDLE},            //183
	{"NULL",					Y6_NULL_HANDLE},            //184
	{"NULL",					Y6_NULL_HANDLE},            //185
	{"NULL",					Y6_NULL_HANDLE},            //186
	{"NULL",					Y6_NULL_HANDLE},            //187
	{"NULL",					Y6_NULL_HANDLE},            //188
	{"NULL",					Y6_NULL_HANDLE},            //189
	{"NULL",					Y6_NULL_HANDLE},            //190
	{"NULL",					Y6_NULL_HANDLE},             //191
 	{"NULL",					Y6_NULL_HANDLE},             //192  
 	{"NULL",					Y6_NULL_HANDLE},             //193  
 	{"NULL",					Y6_NULL_HANDLE},             //194 
	{"NULL",					Y6_NULL_HANDLE},             //195
	{"NULL",					Y6_NULL_HANDLE},             //196
	{"NULL",					Y6_NULL_HANDLE},             //197
	{"NULL",					Y6_NULL_HANDLE},            //198
	{"NULL",					Y6_NULL_HANDLE},             //199
	{"NULL",					Y6_NULL_HANDLE},             //200
	
	{"NULL",					Y6_NULL_HANDLE},            //201
	{"NULL",					Y6_NULL_HANDLE},            //202
	{"NULL",					Y6_NULL_HANDLE},            //203
	{"NULL",					Y6_NULL_HANDLE},            //204
	{"NULL",					Y6_NULL_HANDLE},            //205
	{"NULL",					Y6_NULL_HANDLE},            //206
	{"NULL",					Y6_NULL_HANDLE},            //207
	{"NULL",					Y6_NULL_HANDLE},            //208
	{"NULL",					Y6_NULL_HANDLE},            //209
	{"NULL",					Y6_NULL_HANDLE},            //210
	{"NULL",					Y6_NULL_HANDLE},            //211
	{"NULL",					Y6_NULL_HANDLE},            //212
	{"NULL",					Y6_NULL_HANDLE},            //213
	{"NULL",					Y6_NULL_HANDLE},            //214
	{"NULL",					Y6_NULL_HANDLE},            //215
	{"NULL",					Y6_NULL_HANDLE},            //216
	{"NULL",					Y6_NULL_HANDLE},            //217
	{"NULL",					Y6_NULL_HANDLE},            //218
	{"NULL",					Y6_NULL_HANDLE},            //219
	{"NULL",					Y6_NULL_HANDLE},            //220
	{"NULL",					Y6_NULL_HANDLE},            //221
	{"NULL",					Y6_NULL_HANDLE},            //222
	{"NULL",					Y6_NULL_HANDLE},            //223
	{"HMISet_Work_Mode",	Y6_HMISet_Work_Mode},            //224   
	{"NULL",					Y6_NULL_HANDLE},            //225
	{"NULL",					Y6_NULL_HANDLE},            //226
	{"NULL",					Y6_NULL_HANDLE},            //227
	{"NULL",					Y6_NULL_HANDLE},            //228 	
	{"NULL",					Y6_NULL_HANDLE},            //229
	{"NULL",					Y6_NULL_HANDLE},            //230
	{"NULL",					Y6_NULL_HANDLE},            //231   
	{"NULL",					Y6_NULL_HANDLE},            //232
	{"NULL",					Y6_NULL_HANDLE},            //233
	{"NULL",					Y6_NULL_HANDLE},            //234
	{"NULL",					Y6_NULL_HANDLE},            //235
	{"NULL",					Y6_NULL_HANDLE},            //236
	{"NULL",					Y6_NULL_HANDLE},            //237
	{"NULL",					Y6_NULL_HANDLE},            //238
	{"NULL",					Y6_NULL_HANDLE},            //239
	{"NULL",					Y6_NULL_HANDLE},            //240
	{"NULL",					Y6_NULL_HANDLE},            //241
	{"NULL",					Y6_NULL_HANDLE},            //242  
	{"NULL",					Y6_NULL_HANDLE},            //243
	{"NULL",					Y6_NULL_HANDLE},            //244
	{"NULL",					Y6_NULL_HANDLE},            //245
	{"NULL",					Y6_NULL_HANDLE},            //246
	{"NULL",					Y6_NULL_HANDLE},            //247
	{"NULL",					Y6_NULL_HANDLE},            //248
	{"NULL",					Y6_NULL_HANDLE},            //249
 	
	
	
};
