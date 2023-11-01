

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
#define Get_Key()     GPIO_ReadPin(GPIO0,GPIO_Pin_28)
int main()
{
	/*******************Initialize a series of MCU peripherals, then start the GUI*******************/
	uint8_t ret;	
			
	printf("start app\n");
	TIM4_EncoderInit();	  //Rotary encoder initialization
	Key_init();		
	LCD_Init();//Initialize LCD	
		
	guiInit();//Initialize GUI lib			
	ret =guiGetRefreshPicTime(0);	
	printf("Refresh image need  %d ms\n",ret);		
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


void key_control()
{
	switch(Key_Scan())
	{
		case 3:    //Button short press  
		if(Enter_click == 0){
			printf("key_flag = %d\n",key_flag);					
				switch(key_flag)
				{
					case 0:page_init();break;
					case 1:red_led();break;
					case 2:infrared_red();break;
					case 3:pump();break;
					case 4:fan();break;
					case 5:red_led2();break;
					case 6:red_led3();break;
					case 7:red_led4();break;
					case 8:infrared_red2();break;
					case 9:fan2();break;
					case 10:red_light_group();break;
					case 11:red_light_num();break;
					case 12:red_light_on_off();break;
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
		printf("img = %d\n",IMG);														
		switch(key_flag)
		{
			case 0:en_count(1,5);guiJumpPage(Test01Page_wID,GUI_NULL,DemoMain_PageEnterEvent);break;
			case 1:en_count(1,6);guiJumpPage(Tred_led_wID,GUI_NULL,red_led_PageEnterEvent);break;
			case 2:en_count(1,100);guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent);printf("%d,%d,%d",IMG/100,(IMG/10)%10,IMG%10);break;
			case 3:en_count(1,2);guiJumpPage(infrared_led_wID2,GUI_NULL,infrared_PageEnterEvent2);break;
			case 4:en_count(1,100);guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent);break;
			case 5:en_count(1,2);guiJumpPage(Tred_led_wID2,GUI_NULL,red_led_PageEnterEvent2);break;
			case 6:en_count(1,6);guiJumpPage(Tred_led_wID,GUI_NULL,red_led_PageEnterEvent);break;
			case 7:en_count(1,2);guiJumpPage(Tred_led_wID2,GUI_NULL,red_led_PageEnterEvent2);break;
			case 8:en_count(1,2);guiJumpPage(infrared_led_wID2,GUI_NULL,infrared_PageEnterEvent2);break;
			case 9:en_count(1,2);guiJumpPage(infrared_led_wID2,GUI_NULL,infrared_PageEnterEvent2);break;
			case 10:en_count(1,4);guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent);break;
			case 11:en_count(1,100);guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent);break;
			case 12:en_count(1,2);guiJumpPage(infrared_led_wID2,GUI_NULL,infrared_PageEnterEvent2);break;
		}
		
	}
	
}

void page_init()
{
	for(int i=0;i<7;i++)
	{
		printf("%d",printf_arr[i]);
	}
	
	switch(IMG)
	{
		case 0:guiJumpPage(Test01Page_wID,GUI_NULL,DemoMain_PageEnterEvent);IMG = 1;break;
		case 1: key_flag=1;guiJumpPage(Tred_led_wID,GUI_NULL,red_led_PageEnterEvent);IMG = 1;break;
		case 2: key_flag=6;guiJumpPage(Tred_led_wID,GUI_NULL,red_led_PageEnterEvent);IMG = 1;break;
		case 3: key_flag=10;guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent);IMG = 1;break;
		case 4: key_flag=2;guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent);IMG = 1;break;
		case 5: key_flag=3;guiJumpPage(infrared_led_wID2,GUI_NULL,infrared_PageEnterEvent2);IMG = 1;break;
		case 6: key_flag=4;en_count(1,100);IMG = 50;guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent);break;
	}
				
}
	
	
void en_count(char first,char late)
{
	if(En_oldcount==0)
	{
		if(En_count==29)
		{
			IMG--;
			if(IMG<first)
				IMG = late;
			printf("IMG--");
		}	
		if(En_count==1)
		{
			IMG++;
			if(IMG>late)
				IMG = first;
			printf("img++");
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
void red_light_group()
{
	guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent);
	if(key_flag==10)
	{
		key_flag2++;	
		if(key_flag2>0)
		{
			key_flag = 11;
			key_flag2=0;
			guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent2);
			printf_arr[2] = IMG/100;
			printf_arr[3] = (IMG/10)%10;
			printf_arr[4] = IMG%10;
			IMG = 1;
			
		}
	}
}
void red_light_num()
{
	guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent);
	if(key_flag==11)
	{
		key_flag2++;	
		if(key_flag2>0)
		{
			key_flag = 12;
			key_flag2=0;
			guiJumpPage(infrared_led_wID2,GUI_NULL,infrared_PageEnterEvent2);
			printf_arr[2] = IMG/100;
			printf_arr[3] = (IMG/10)%10;
			printf_arr[4] = IMG%10;
			IMG = 1;
			
		}
	}
}
void red_light_on_off()
{
	if(key_flag==12)
	{
		key_flag2++;	
		if(key_flag2>0)
		{
			key_flag = 10;
			key_flag2=0;
			guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent);

			printf("img = %d\n",IMG);
			if(IMG == 1)
			{
				printf_arr[0] = 3;printf_arr[1] = 1;
				for(int i=0;i<7;i++)
				{
					printf("%d",printf_arr[i]);
				}
			}
			else
			{
				printf_arr[0] = 3;printf_arr[1] = 0;
				for(int i=0;i<5;i++)
					printf_arr[i+2] = 0;
				for(int i=0;i<7;i++)
				{
					printf("%d",printf_arr[i]);
				}				
			}
				
			IMG = 1;
		}
	}
}
void red_led()
{
	
	if(key_flag==1)
	{
		guiJumpPage(Tred_led_wID,GUI_NULL,red_led_PageEnterEvent);
		switch(IMG)
		{
			case 1:red_arr[0]=1;red_img[0]=1;break;
			case 2:red_arr[1]=1;red_img[1]=2;break;
			case 3:red_arr[2]=1;red_img[2]=5;break;
			case 4:red_arr[3]=1;red_img[3]=8;break;
			case 5:red_arr[4]=1;red_img[4]=10;break;
			case 6:key_flag=5;guiJumpPage(Tred_led_wID2,GUI_NULL,red_led_PageEnterEvent2);IMG=1;break;
			default:break;
		}
	}

}	
void red_led2()
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
			printf("img = %d\n",IMG);
			if(IMG==1)
			{
				printf_arr[0] = 1;printf_arr[1] = 1;
				for(int i=0;i<7;i++)
				{
					printf("%d",printf_arr[i]);	
				}
			}
			else
			{
				printf_arr[0] = 1;printf_arr[1] = 0;
				for(int i=0;i<5;i++)
					printf_arr[i+2] = 0;
				for(int i=0;i<7;i++)
				{
					printf("%d",printf_arr[i]);	
				}
			}
			IMG = 1;		
		}
	}
}
void red_led3()
{
	
	if(key_flag==6)
	{
		guiJumpPage(Tred_led_wID,GUI_NULL,red_led_PageEnterEvent);
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
void red_led4()
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
			printf("img = %d\n",IMG);
			if(IMG==1)
			{
				printf_arr[0] = 2;printf_arr[1] = 1;
				for(int i=0;i<7;i++)
				{
					printf("%d",printf_arr[i]);	
				}
			}
			else
			{
				printf_arr[0] = 1;printf_arr[1] = 0;
				for(int i=0;i<5;i++)
					printf_arr[i+2] = 0;
				for(int i=0;i<7;i++)
				{
					printf("%d",printf_arr[i]);	
				}
			}
				IMG = 1;
		}
	}
}

void infrared_red()
{

	guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent);
	if(key_flag==2)
	{
		key_flag2++;	
		if(key_flag2>0)
		{
			key_flag = 8;
			key_flag2=0;
			guiJumpPage(infrared_led_wID2,GUI_NULL,infrared_PageEnterEvent2);
			printf_arr[2] = IMG/100;
			printf_arr[3] = (IMG/10)%10;
			printf_arr[4] = IMG%10;
			IMG = 1;
			
		}
	}
	
}

void infrared_red2()
{
	if(key_flag==8)
	{
		key_flag2++;	
		if(key_flag2>0)
		{
			key_flag = 2;
			key_flag2=0;
			guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent);

			printf("img = %d\n",IMG);
			if(IMG == 1)
			{
				printf_arr[0] = 3;printf_arr[1] = 1;
				for(int i=0;i<7;i++)
				{
					printf("%d",printf_arr[i]);
				}
			}
			else
			{
				printf_arr[0] = 3;printf_arr[1] = 0;
				for(int i=0;i<5;i++)
					printf_arr[i+2] = 0;
				for(int i=0;i<7;i++)
				{
					printf("%d",printf_arr[i]);
				}				
			}
				
			IMG = 1;
		}
	}
	
}
//���ù���
void pump()
{

	guiJumpPage(infrared_led_wID2,GUI_NULL,infrared_PageEnterEvent2);
	if(key_flag==3)
	{
		key_flag2++;	
		if(key_flag2>0)
		{
			key_flag = 0;
			key_flag2=0;
			guiJumpPage(Test01Page_wID,GUI_NULL,DemoMain_PageEnterEvent);
			
			printf("img = %d\n",IMG);
			if(IMG==1)
			{
				printf_arr[0] = 4;printf_arr[1] = 1;
				for(int i=0;i<7;i++)
				{
					printf("%d",printf_arr[i]);	
				}
			}
			else
			{
				printf_arr[0] = 4;printf_arr[1] = 0;
				for(int i=0;i<5;i++)
					printf_arr[i+2] = 0;
				for(int i=0;i<7;i++)
				{
					printf("%d",printf_arr[i]);
				}	

			}
						
		}
	}
}
//���ȹ���
void fan()
{
	if(init_flag==0)
	{
		IMG = 50;
		init_flag = 1;
	}
	guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent);
	printf(" fan img = %d\n",IMG);
	if(key_flag==4)
	{
		key_flag2++;	
		if(key_flag2>0)
		{
			key_flag = 9;
			key_flag2=0;
			guiJumpPage(infrared_led_wID2,GUI_NULL,infrared_PageEnterEvent2);
			printf_arr[2] = IMG/100;
			printf_arr[3] = (IMG/10)%10;
			printf_arr[4] = IMG%10;
			IMG = 1;
		}
	}	
}

void fan2()
{
	
	if(key_flag==9)
	{
		key_flag2++;	
		if(key_flag2>0)
		{
			key_flag = 4;
			key_flag2=0;
			guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent);
			printf("img = %d\n",IMG);
			if(IMG==1)
			{
				printf_arr[0] = 5;printf_arr[1] = 1;
				for(int i=0;i<7;i++)
				{
					printf("%d",printf_arr[i]);	
				}
			}
			else
			{
				printf_arr[0] = 5;printf_arr[1] = 0;
				for(int i=0;i<5;i++)
					printf_arr[i+2] = 0;
				for(int i=0;i<7;i++)
				{
					printf("%d",printf_arr[i]);
				}	
			}
			en_count(1,100);				
			IMG = 50;
		}
	}
	
}

void all_zero()
{
	for(int i=0;i<5;i++)
	{
		red_arr[i]=0;red_arr2[i]=0;
		red_img[i]=0;
	}
	init_flag =0;
	key_flag2 = 0;
	key_flag = 0;
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
