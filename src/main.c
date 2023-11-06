
/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Y6_uart.h"
#include "misc.h"
#include "Y6_gpio.h"
#include "lcddriver.h"
#include "lcdInit.h"
#include "guiFunc.h"
#include "systemuart.h"
#include "systemHeart.h"
#include "lcdInterface.h"
#include "rtcDriver.h"
#include "flashInterface.h"
#include "guiConfig.h"
#include "comInterface.h"
#include "Y6_include_conf.h"
#include "Y6_command.h"
#include "pwm.h"

#include "Y6_utility_i2c.h"
#include "Y6_otp.h"

#include "DemoTest01.h"
#include "ENCODER.h"
#include "Key.h"

int	Key_Scan(void);
void red_led();
void red_led2();
void red_led3();
void red_led4();
void red_light_group();
void red_light_num();
void red_light_on_off();
void infrared_red();
void infrared_red2();
void pump();
void fan();
void fan2();
void all_zero();
void en_count(char first,char late);
void page_init();
void key_control();
void rotary_control();
void outclk_init(void)
{
  GPIO_SetPinMux(GPIO0, GPIO_Pin_25, GPIO_FUNCTION_3);
  RCC->OUTCLKSEL = 0;
  RCC->OUTCLKDIV = 1;
  RCC->OUTCLKUEN = 0;
  RCC->OUTCLKUEN = 1;
}

/**
  * @brief  Main program.asd
  * @param  None
  * @retval None
  */

extern uint8_t time;	
extern  int16_t Encoder_counter;
extern int circle_count;
char Enter_click=0;     //1: Rotate to adjust arcs and numbers 
						// 0:Rotation adjustment function interface
char IMG=1;	
char Logo=1;
char key_flag = 0;//��ťλ��
char key_flag2 = 0;//����λ��
char init_flag = 0; 
int En_count,En_oldcount=0;	
uint8_t red_arr[5]={0},red_arr2[5]={0};
uint8_t printf_arr[7]={0};
uint8_t red_img[5] = {0},red_img2=0;
enum protocol{gP_red_f1=1,gP_red_f2,gP_red_l,gP_infreared,gP_Pump,gP_fun};
enum rotary_funtion{g_page_init=0,g_red_led,g_infrared_red,g_pump,g_fan,g_red_led2,g_red_led3,g_red_led4,g_infrared_red2,g_fan2,g_red_light_group,g_red_light_on_off,g_red_light_num=12};
#define Get_Key()     GPIO_ReadPin(GPIO0,GPIO_Pin_28)
int main()
{
	/*******************Initialize a series of MCU peripherals, then start the GUI*******************/
	uint8_t ret;	
			

	TIM4_EncoderInit();	  //Rotary encoder initialization
	Key_init();		
	LCD_Init();//Initialize LCD	
		
	guiInit();//Initialize GUI lib			
	ret =guiGetRefreshPicTime(0);	
			
	DemoTestPage_Init();     //Knob screen display demo
	GPIO_SetPin(LED_PORT, LED_PIN);	
	IMG = 0;
	while(1){

			guiMainLoop();// GUI event loop	
			Y6_Communication_Loop();
			En_count =  encoder_getCounter ();
			key_control();
			rotary_control();	
			En_oldcount = En_count;							  							
		}
}

uint8_t  key_enable_flag = 0;
void key_control()
{
	switch(Key_Scan())
	{
		case 3:    //Button short press  
		if(Enter_click == 0){
				key_enable_flag=1;			
				switch(key_flag)
				{
					case g_page_init:page_init();key_enable_flag=0;break;
					case g_red_led:red_led();key_enable_flag=0;break;
					case g_infrared_red:infrared_red();key_enable_flag=0;break;
					case g_pump:pump();key_enable_flag=0;break;
					case g_fan:fan();key_enable_flag=0;break;
					case g_red_led2:red_led2();key_enable_flag=0;break;
					case g_red_led3:red_led3();key_enable_flag=0;break;
					case g_red_led4:red_led4();key_enable_flag=0;break;
					case g_infrared_red2:infrared_red2();key_enable_flag=0;break;
					case g_fan2:fan2();key_enable_flag=0;break;
					case g_red_light_group:red_light_group();key_enable_flag=0;break;
					case g_red_light_num:red_light_num();key_enable_flag=0;break;
					case g_red_light_on_off:red_light_on_off();key_enable_flag=0;break;
				}
							
			}
		else 
			Enter_click=0;
		break;
	case 4:	
			
			all_zero();
			guiJumpPage(Test01Page_wID,GUI_NULL,DemoMain_PageEnterEvent);
			Logo=0;
		break;
	default:
		break;			
	}
}

void rotary_control()
{
	if(En_count !=En_oldcount)
	{	
												
		Logo=0;	
		//printf("img = %d\n",IMG);		
									
		switch(key_flag)
		{
			case g_page_init:page_init();break;
			case g_red_led:red_led();break;
			case g_infrared_red:infrared_red();break;
			case g_pump:pump();break;
			case g_fan:fan();break;
			case g_red_led2:red_led2();break;
			case g_red_led3:red_led3();break;
			case g_red_led4:red_led4();break;
			case g_infrared_red2:infrared_red2();break;
			case g_fan2:fan2();break;
			case g_red_light_group:red_light_group();break;
			case g_red_light_num:red_light_num();break;
			case g_red_light_on_off:red_light_on_off();break;
		}
		
	}
	
}

void page_init()
{
	en_count(1,6);
	guiJumpPage(Test01Page_wID,GUI_NULL,DemoMain_PageEnterEvent);
	if(key_enable_flag==1)
	{
		switch(IMG)
		{
			case 0:guiJumpPage(Test01Page_wID,GUI_NULL,DemoMain_PageEnterEvent);IMG = 1;break;
			case 1: IMG = 1;key_flag=g_red_led;red_led();break;
			case 2: IMG = 1;key_flag=g_red_led3;red_led3();break;
			case 3: IMG = 1;key_flag=g_red_light_group;red_light_group();break;
			case 4: IMG = 1;key_flag=g_infrared_red;infrared_red();break;
			case 5: IMG = 1;key_flag=g_pump;pump();break;
			case 6:IMG = 1; key_flag=g_fan;fan();break;
		}		
	}

				
}
	
uint8_t g_light_group = 0;
void en_count(char first,char late)
{
	if(En_oldcount==0)
	{
		if(En_count==29)
		{
			IMG--;
			if(IMG<first)
				IMG = late;
			
		}	
		if(En_count==1)
		{
			IMG++;
			if(IMG>late)
				IMG = first;
			
		}
	}
	else
	{
		if(En_oldcount < En_count)
		{
			if(En_count==0&&En_oldcount==1)
			{
				IMG--;
				if(IMG<first)
					IMG = late;	
			}
			IMG++;
			if(IMG>late)
				IMG = first;
		}
		if(En_oldcount > En_count)
		{
			if(En_count==0&&En_oldcount==29)
			{
				IMG++;
				if(IMG>late)
					IMG = first;	
			}
			else
			{
				IMG--;
				if(IMG<first)
					IMG = late;
			}

			
		}	
	}	

}
// red_led
uint8_t light_group_key=0;
void red_light_group()
{
	
	en_count(1,4);guiJumpPage(grounp_PicwID2,GUI_NULL,groud1_100EnterEvent);
	if(key_enable_flag==1)
	{
		if(key_flag==g_red_light_group)
		{
			light_group_key++;	
			if(light_group_key>1)
			{
				key_flag = g_red_light_on_off;
				light_group_key=1;
				guiJumpPage(on_off_led_wID2,GUI_NULL,on_off_Event);
				switch (IMG)
				{
				case 1:g_light_group = 1;break;
				case 2:g_light_group = 2;break;
				case 3:g_light_group = 3;break;
				case 4:g_light_group = 4;break;
				default:
					break;
				}
				IMG = 1;
			}
		}		
	}


}
uint8_t light_on_off_key = 0;
void red_light_on_off()
{
	
	en_count(1,2);guiJumpPage(on_off_led_wID2,GUI_NULL,on_off_Event);
	if(key_enable_flag==1)
	{
		if(key_flag==g_red_light_on_off)
		{	
				light_on_off_key=2;
				
				if(IMG == 1)
				{	
					key_flag = g_red_light_num;	
					printf_arr[0] = gP_red_l;printf_arr[1] = 1;printf_arr[6] = g_light_group;	
					guiJumpPage(light_PicwID2,GUI_NULL,light1_100EnterEvent);
				}
				else
				{
					printf_arr[0] = gP_red_l;printf_arr[1] = 0;
					for(int i=0;i<5;i++)
						printf_arr[i+2] = 0;
					for(int i=0;i<7;i++)
					{
						printf("%d",printf_arr[i]);
					}	
					printf("\r\n");	
					key_flag = g_red_light_group;	guiJumpPage(grounp_PicwID2,GUI_NULL,groud1_100EnterEvent);		
				}
					
				IMG = 1;
			
		}		
	}

}

uint8_t light_num_key = 0;
void red_light_num()
{
	
	en_count(1,100);guiJumpPage(light_PicwID2,GUI_NULL,light1_100EnterEvent);
	if(key_enable_flag==1)
	{
		if(key_flag==g_red_light_num)
		{
			light_num_key++;	
			if(light_num_key>0)
			{
				key_flag = g_red_light_group;
				light_num_key=0;
				light_group_key = 1;
				guiJumpPage(grounp_PicwID2,GUI_NULL,groud1_100EnterEvent);
				IMG = 1;	
			}
		}		
	}
	else
	{
		printf_arr[2] = IMG/100;
		printf_arr[3] = (IMG/10)%10;
		printf_arr[4] = IMG%10;
		for(int i=0;i<7;i++)
		{
			printf("%d",printf_arr[i]);
		}printf("\r\n");	
	}
}
uint8_t g_red_led1_key=0;
void red_led()
{
	en_count(1,6);guiJumpPage(Tred_led_wID,GUI_NULL,red_led_PageEnterEvent);
	if(key_enable_flag==1)
	{
		g_red_led1_key++;
		if(g_red_led1_key>1)
		{
			g_red_led1_key=1;
			if(key_flag==g_red_led)
			{
				//guiJumpPage(Tred_led_wID,GUI_NULL,red_led_PageEnterEvent);
				switch(IMG)
				{
					case 1:red_arr[0]=1;red_img[0]=1;break;
					case 2:red_arr[1]=1;red_img[1]=2;break;
					case 3:red_arr[2]=1;red_img[2]=5;break;
					case 4:red_arr[3]=1;red_img[3]=8;break;
					case 5:red_arr[4]=1;red_img[4]=10;break;
					case 6:key_flag=g_red_led2;guiJumpPage(Tred_led_wID2,GUI_NULL,red_led_PageEnterEvent2);IMG=1;break;
					default:break;
				}
			}				
		}
	
	}
}	
void red_led2()
{
	en_count(1,2);guiJumpPage(Tred_led_wID2,GUI_NULL,red_led_PageEnterEvent2);
	if(key_enable_flag==1)
	{
		if(key_flag==5)
		{			
			key_flag2++;	
			if(key_flag2>0)
			{
				for(int i=0;i<5;i++)
				{
					printf_arr[i+2] = red_arr[i];
					red_img[i] = 0;
					red_arr[i] = 0;
				}
				key_flag2=0;
				key_flag =1;
				guiJumpPage(Tred_led_wID,GUI_NULL,red_led_PageEnterEvent);	
				
				if(IMG==1)
				{
					printf_arr[0] = gP_red_f1;printf_arr[1] = 1;
					for(int i=0;i<7;i++)
					{
						printf("%d",printf_arr[i]);	
					}
					printf("\r\n");	
				}
				else
				{
					printf_arr[0] = gP_red_f1;printf_arr[1] = 0;
					for(int i=0;i<5;i++)
						printf_arr[i+2] = 0;
					for(int i=0;i<7;i++)
					{
						printf("%d",printf_arr[i]);	
					}printf("\r\n");	
				}
				IMG = 1;		
			}
		}		
	}

}
uint8_t g_red_led3_key=0;
void red_led3()
{
	en_count(1,6);guiJumpPage(Tred_led_wID,GUI_NULL,red_led_PageEnterEvent);
	if(key_enable_flag==1)
	{
		g_red_led3_key++;
		if(g_red_led3_key>1)
		{
			g_red_led3_key=1;
			if(key_flag==g_red_led3)
			{
				switch(IMG)
				{
					case 1:red_arr2[0]=1;red_img[0]=1;break;
					case 2:red_arr2[1]=1;red_img[1]=2;break;
					case 3:red_arr2[2]=1;red_img[2]=5;break;
					case 4:red_arr2[3]=1;red_img[3]=8;break;
					case 5:red_arr2[4]=1;red_img[4]=10;break;
					case 6:key_flag=7;guiJumpPage(Tred_led_wID2,GUI_NULL,red_led_PageEnterEvent2);IMG=1;break;//��ת��ȷ�Ͻ���,��ʾ��ѡ�������
					default:break;
				}
			}			
		}
		
	}


}	
void red_led4()
{
	en_count(1,2);guiJumpPage(Tred_led_wID2,GUI_NULL,red_led_PageEnterEvent2);
	if(key_enable_flag==1)
	{
		if(key_flag==7)
		{	
			
			key_flag2++;	
			if(key_flag2>0)
			{
				for(int i=0;i<5;i++)
				{
					printf_arr[i+2] = red_arr2[i];
					red_img[i] = 0;
					red_arr2[i] = 0;
				}				
				key_flag2=0;
				key_flag =6;
				guiJumpPage(Tred_led_wID,GUI_NULL,red_led_PageEnterEvent);	
				if(IMG==1)
				{
					printf_arr[0] = gP_red_f2;printf_arr[1] = 1;
					for(int i=0;i<7;i++)
					{
						printf("%d",printf_arr[i]);	
					}printf("\r\n");	
				}
				else
				{
					printf_arr[0] = gP_red_f2;printf_arr[1] = 0;
					for(int i=0;i<5;i++)
						printf_arr[i+2] = 0;
					for(int i=0;i<7;i++)
					{
						printf("%d",printf_arr[i]);	
					}printf("\r\n");	
				}
					IMG = 1;
			}
		}		
	}

}
uint8_t infrared_led_key=0;
void infrared_red()
{
	
	en_count(1,2);guiJumpPage(on_off_led_wID2,GUI_NULL,on_off_Event);
	if(key_enable_flag==1)
	{
		if(key_flag==g_infrared_red)
		{
			infrared_led_key++;	
			if(infrared_led_key>1)
			{
				
				infrared_led_key=1;
				
				if(IMG == 1)
				{
					key_flag = g_infrared_red2;
					printf_arr[0] = gP_infreared;printf_arr[1] = 1;
					guiJumpPage(num1_100_led_wID,GUI_NULL,num1_100EnterEvent);
				}
				else
				{
					printf_arr[0] = gP_infreared;printf_arr[1] = 0;
					for(int i=0;i<5;i++)
						printf_arr[i+2] = 0;
					for(int i=0;i<7;i++)
					{
						printf("%d",printf_arr[i]);
					}printf("\r\n");					
				}
					
				IMG = 1;
			}
		}		
	}
}
uint8_t infrared_led_key2=0;
void infrared_red2()
{
	
	en_count(1,100);
	guiJumpPage(num1_100_led_wID,GUI_NULL,num1_100EnterEvent);
	if(key_enable_flag==1)
	{
		if(key_flag==g_infrared_red2)
		{
			infrared_led_key2++;	
			if(infrared_led_key2>0)
			{
				key_flag = g_infrared_red;
				infrared_led_key2=0;
				guiJumpPage(on_off_led_wID2,GUI_NULL,on_off_Event);
				IMG = 1;
			}

		}			
	}
	else
	{
		printf_arr[2] = IMG/100;
		printf_arr[3] = (IMG/10)%10;
		printf_arr[4] = IMG%10;
		for(int i=0;i<7;i++)
		{
			printf("%d",printf_arr[i]);
		}printf("\r\n");			
	}
	
	//printf("key_enable_flag = %d\n",key_enable_flag);
	
}
uint8_t pump_key=0;
void pump()
{
	
	en_count(1,2);guiJumpPage(on_off_led_wID2,GUI_NULL,on_off_Event);
	if(key_enable_flag==1)
	{
		if(key_flag==g_pump)
		{
			pump_key++;	
			if(pump_key>1)
			{
				key_flag = g_page_init;
				pump_key=0;
				guiJumpPage(Test01Page_wID,GUI_NULL,DemoMain_PageEnterEvent);
				
				
				if(IMG==1)
				{
					printf_arr[0] = gP_Pump;printf_arr[1] = 1;
					for(int i=0;i<7;i++)
					{
						printf("%d",printf_arr[i]);	
					}printf("\r\n");	
				}
				else
				{
					printf_arr[0] = gP_Pump;printf_arr[1] = 0;
					for(int i=0;i<5;i++)
						printf_arr[i+2] = 0;
					for(int i=0;i<7;i++)
					{
						printf("%d",printf_arr[i]);
					}	printf("\r\n");	

				}
							
			}
		}		
	}

}
uint8_t fan_key = 0;
void fan()
{
	
	en_count(1,2);guiJumpPage(on_off_led_wID2,GUI_NULL,on_off_Event);
	if(key_enable_flag==1)
	{
		if(key_flag==g_fan)
		{
			fan_key++;	
			if(fan_key>1)
			{
				
				fan_key=1;
				
				if(IMG == 1)
				{
					key_flag = g_fan2;
					printf_arr[0] = gP_fun;printf_arr[1] = 1;
					guiJumpPage(num1_100_led_wID,GUI_NULL,num1_100EnterEvent);
				IMG = 50;
				}
				else
				{
					printf_arr[0] = gP_fun;printf_arr[1] = 0;
					for(int i=0;i<5;i++)
						printf_arr[i+2] = 0;
					for(int i=0;i<7;i++)
					{
						printf("%d",printf_arr[i]);
					}printf("\r\n");		
					IMG = 1;			
				}
					
				
			}
		}		
	}
	
}
uint8_t fan_key2 = 0;
void fan2()
{

	en_count(1,100);
	if(init_flag==0)
	{
		IMG = 50;
		init_flag = 1;
	}
	guiJumpPage(num1_100_led_wID,GUI_NULL,num1_100EnterEvent);
	if(key_enable_flag==1)
	{

		guiJumpPage(num1_100_led_wID,GUI_NULL,num1_100EnterEvent);

		if(key_flag==g_fan2)
		{
			fan_key2++;	
			if(fan_key2>0)
			{
				key_flag = g_fan;
				fan_key2=0;
				IMG = 1;
				guiJumpPage(on_off_led_wID2,GUI_NULL,on_off_Event);	
			}
		}
	
	}
	else
	{
		printf_arr[2] = IMG/100;
		printf_arr[3] = (IMG/10)%10;
		printf_arr[4] = IMG%10;
		for(int i=0;i<7;i++)
		{
			printf("%d",printf_arr[i]);
		}printf("\r\n");			
	}	


	
}

void all_zero()
{
	for(int i=0;i<5;i++)
	{
		red_arr[i]=0;red_arr2[i]=0;
		red_img[i]=0;
	}
	for(int i=0;i<7;i++)
	{
		printf_arr[i] = 0;
	}
	init_flag =0;
	key_flag2 = 0;
	key_flag = 0;
	light_group_key = 0;light_on_off_key = 0;light_num_key = 0;g_red_led1_key=0;g_red_led3_key=0;
	infrared_led_key=0;infrared_led_key2=0;pump_key=0; fan_key = 0;fan_key2 = 0;
	IMG = 1;
}


int	Key_Scan(void)
{
    static unsigned char key_state = 0;         // Key Status Variables
    static unsigned int key_time = 0;           // Key Timing Variables
    unsigned char key_press, key_return; 

    key_return = 0;                         //  Return key value
    key_press = Get_Key();                      // Retrieve the current key value

    switch (key_state)     
    {       
        case 0:                       //Key Status 0: Determine if there is a key pressed
            if (!key_press)                    
            {
                key_time = 0;                   
                key_state = 1;       
            }        
            break;

        case 1:                       // Key Status 1: Software de-jittering (to determine if the key is valid and not a mis-touch).
            if (!key_press)                     
            {
                key_time++;                   
                if(key_time>=100)  
                {
                    key_state = 2;    
                }
            }         
            else key_state = 0;       
            break; 

        case 2:                       // Key Status 2: Determine what kind of key is valid: click, or long press
            if(key_press)                     
            { 
                 key_return = 3;           
                 key_state = 0;       
            } 
            else
            {
                key_time++;                     

                if(key_time >= 10000)   //If the key press time exceeds the set long press time, it will be judged as long press.
                {
                    key_return = 4;         
                    key_state = 3;    
                }
            }
            break;

      case 3:                         // Waiting for key release
          if (key_press) 
          {
              key_state = 0;          
          }         
          break; 

        default:                            
            key_state = 0;
            break;
    }
	if(Logo == 1 && key_return!=0) Logo = 0;	
    return key_return;                       
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  printf("Wrong parameters value: file %s on line %d\r\n", file, line);
  /* Infinite loop */
  while (1)
  {
  }
}
#endif
