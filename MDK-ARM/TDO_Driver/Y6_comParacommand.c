#include "guiFunc.h"
#include "Y6_command.h"
#include "stdio.h"
#include "lcdDriver.h"
#include "Y6.h"
#include "pwm.h"
#include "flashInterface.h"
#include "memoryInterface.h"
#include "Y6_xip_write.h"
#include "Y6_otp.h"
#include "Encryption.h"

 uint8_t Send_head_tail[5] = {0xAA,0xCC,0x33,0xC3,0x3C};
  
 void Cmd_R(uint8_t *charc , uint8_t c_len)	
{
		uint8_t u8cnt;
		uint8_t *rdata=NULL;
		rdata[0]=Send_head_tail[0];
		uint8_t *sdata=charc;

		for(u8cnt = 0; u8cnt < c_len; u8cnt++)
		{
			 rdata[u8cnt+1] =  sdata[u8cnt];
			printf("sdata[%d] = %x\n",u8cnt,sdata[u8cnt]);
		}	
		rdata[c_len+1]=Send_head_tail[1];
		rdata[c_len+2]=Send_head_tail[2];
		rdata[c_len+3]=Send_head_tail[3]; 
		rdata[c_len+4]=Send_head_tail[4];
		Com_Des.outputString(rdata,c_len + 5);
		
}

Y6_CMD_State Y6_Return( uint8_t cmd,const void *charc,uint32_t c_len)
{
		uint8_t *rdata=NULL;
 
 		rdata[0] =	Send_head_tail[0];
		rdata[1] = 'O';//4F
		rdata[2] = 'K';//4B
		rdata[3] = '_';//5F
		rdata[4] = 'V';//56
		rdata[5] = 0x31;//3E
		rdata[6] = '.';//2E
		rdata[7] = 0x30;//30
		rdata[8] = 0;//05
		rdata[9] = 0;//07
		rdata[10]= 0;
		rdata[11]= Send_head_tail[1];
		rdata[12]= Send_head_tail[2];
		rdata[13]= Send_head_tail[3]; 
		rdata[14]= Send_head_tail[4];
		Com_Des.outputString(rdata,15);
		return Y6_OK_CMD;

}
 Y6_CMD_State Y6_ClearScreen( uint8_t cmd,const void *charc,uint32_t c_len)
{
		guiGetRefreshColorTime(lcdPara.backColor);
		return Y6_OK_CMD;
}

Y6_CMD_State Y6_SetHMIColor( uint8_t cmd,const void *charc,uint32_t c_len)
{
	 uint8_t *sdata=(uint8_t *)charc;
		lcdPara.fontcolor = (sdata[0]<<8)+sdata[1];
	 lcdPara.backColor= (sdata[2]<<8)+sdata[3];
		return Y6_OK_CMD;

}
Y6_CMD_State Y6_HMISet_Work_Mode( uint8_t cmd,const void *charc,uint32_t c_len)
{		 
		return Y6_OK_CMD;
}
Y6_CMD_State Y6_HMI_led_Opera( uint8_t cmd,const void *charc,uint32_t c_len)//Backlight adjustment
{
		uint8_t *sdata=(uint8_t *)charc;

		switch(cmd)
		{
			case 0x5E://close   0x5E			
					 SetPwm(0);				
				break;
			case 0x5F://open   AA 5F 64 CC 33 C3 3C
				if(c_len>0){				
					if(sdata[0]>0x63){					
						 SetPwm(100); //Maximum brightness
					}
					else{
						 SetPwm(sdata[0]);
					}
				}
				else{				
						 SetPwm(100);//
				}break;			
		}
		return Y6_OK_CMD;

}

Y6_CMD_State Y6_HMI_RESET( uint8_t cmd,const void *charc,uint32_t c_len)
{
		printf("TU");
			__disable_irq();
		NVIC_SystemReset();
		return Y6_OK_CMD;

} 


