

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
void infrared_red();
void infrared_red2();
void pump();
void fan();
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
char red_flag = 0; 
int En_count,En_oldcount=0;	
uint8_t red_arr[5]={0},red_arr2[5]={0};
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
					case 9:fan();break;
				}
				printf("key_flag2 =%d\n",key_flag2);
				printf("key_flag = %d\n",key_flag);								
			}
		else 
			Enter_click=0;
		break;
	case 4:	
			printf("key_flag = %d\n",key_flag);
			all_zero();
			guiJumpPage(Test01Page_wID,GUI_NULL,DemoMain_PageEnterEvent);
			Logo=1;
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
		switch(key_flag)
		{
			case 0:en_count(1,4);guiJumpPage(Test01Page_wID,GUI_NULL,DemoMain_PageEnterEvent);break;
			case 1:en_count(1,6);guiJumpPage(Tred_led_wID,GUI_NULL,red_led_PageEnterEvent);break;
			case 2:en_count(1,100);guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent);printf("%d,%d,%d",IMG/100,(IMG/10)%10,IMG%10);break;
			case 3:en_count(1,2);guiJumpPage(infrared_led_wID2,GUI_NULL,infrared_PageEnterEvent2);break;
			case 4:en_count(1,100);guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent);break;
			case 5:en_count(1,2);guiJumpPage(Tred_led_wID2,GUI_NULL,red_led_PageEnterEvent2);break;
			case 6:en_count(1,6);guiJumpPage(Tred_led_wID,GUI_NULL,red_led_PageEnterEvent);break;
			case 7:en_count(1,2);guiJumpPage(Tred_led_wID2,GUI_NULL,red_led_PageEnterEvent2);break;
			case 8:en_count(1,2);guiJumpPage(infrared_led_wID2,GUI_NULL,infrared_PageEnterEvent2);break;
			case 9:en_count(1,2);guiJumpPage(infrared_led_wID2,GUI_NULL,infrared_PageEnterEvent2);break;
		}
	printf("img = %d\n",IMG);
	printf("En_count = %d\n",En_count);
	printf("En_oldcount = %d\n",En_oldcount);

	}
}

void page_init()
{
		switch(IMG)
		{
			case 0:guiJumpPage(Test01Page_wID,GUI_NULL,DemoMain_PageEnterEvent);break;
			case 1: key_flag=1;printf("key_flag = %d\n",key_flag);guiJumpPage(Tred_led_wID,GUI_NULL,red_led_PageEnterEvent);break;
			case 2: key_flag=2;printf("key_flag = %d\n",key_flag);guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent);break;
			case 3: key_flag=3;printf("key_flag = %d\n",key_flag);guiJumpPage(infrared_led_wID2,GUI_NULL,infrared_PageEnterEvent2);break;
			case 4: key_flag=4;printf("key_flag = %d\n",key_flag);guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent);break;
		}
		IMG = 1;			
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
//��ɫled����
void red_led()
{
	printf("red_led1\n");
	if(key_flag==1)
	{
		guiJumpPage(Tred_led_wID,GUI_NULL,red_led_PageEnterEvent);
		switch(IMG)
		{
			case 1:red_arr[0]=1;red_img[0]=1;printf("red_img[0] = %d",red_img[0]);break;
			case 2:red_arr[1]=1;red_img[1]=2;printf("red_img[1] = %d",red_img[1]);break;
			case 3:red_arr[2]=1;red_img[2]=5;printf("red_img[2] = %d",red_img[2]);break;
			case 4:red_arr[3]=1;red_img[3]=8;printf("red_img[3] = %d",red_img[3]);break;
			case 5:red_arr[4]=1;red_img[4]=0;printf("red_img[4] = %d",red_img[4]);break;
			case 6:key_flag=5;guiJumpPage(Tred_led_wID2,GUI_NULL,red_led_PageEnterEvent2);break;//��ת��ȷ�Ͻ���,��ʾ��ѡ�������
			default:break;
		}
	}

}	
void red_led2()
{
	printf("red_led2\n");
	if(key_flag==5)
	{	
		printf("red_arr\n");
		key_flag2++;	
		if(key_flag2>0)
		{
				for(int i=0;i<5;i++)
				{
					printf("%d",red_arr[i]);
					red_img[i] = 0;
				}
			key_flag2=0;
			key_flag =6;
			guiJumpPage(Tred_led_wID,GUI_NULL,red_led_PageEnterEvent);	
			IMG = 1;
		}
	}
}
void red_led3()
{
	printf("red_led3\n");
	if(key_flag==6)
	{
		guiJumpPage(Tred_led_wID,GUI_NULL,red_led_PageEnterEvent);
		switch(IMG)
		{
			case 1:red_arr2[0]=1;red_img[0]=1;printf("red_img[0] = %d",red_img[0]);break;
			case 2:red_arr2[1]=1;red_img[1]=2;printf("red_img[1] = %d",red_img[1]);break;
			case 3:red_arr2[2]=1;red_img[2]=5;printf("red_img[2] = %d",red_img[2]);break;
			case 4:red_arr2[3]=1;red_img[3]=8;printf("red_img[3] = %d",red_img[3]);break;
			case 5:red_arr2[4]=1;red_img[4]=0;printf("red_img[4] = %d",red_img[4]);break;
			case 6:key_flag=7;guiJumpPage(Tred_led_wID2,GUI_NULL,red_led_PageEnterEvent2);break;//��ת��ȷ�Ͻ���,��ʾ��ѡ�������
			default:break;
		}
	}
	else
		printf("red_led3 red_flag = %d\n",red_flag);

}	
void red_led4()
{
	printf("red_led4\n");
	if(key_flag==7)
	{	
		printf("red_arr2\n");
		key_flag2++;	
		if(key_flag2>0)
		{
			for(int i=0;i<5;i++)
			{
				printf("%d",red_arr2[i]);
				red_img[i] = 0;
			}				
			key_flag2=0;
			key_flag =1;
			guiJumpPage(Tred_led_wID,GUI_NULL,red_led_PageEnterEvent);	
			IMG = 1;
		}
	}
}
//����led����
void infrared_red()
{
	printf("infrared red\n");
	
	guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent);
	if(key_flag==2)
	{
		key_flag2++;	
		if(key_flag2>0)
		{
			key_flag = 8;
			key_flag2=0;
			guiJumpPage(infrared_led_wID2,GUI_NULL,infrared_PageEnterEvent2);
			IMG = 1;
		}
	}
	
}

void infrared_red2()
{
	printf("infrared_red2\n");
	if(key_flag==8)
	{
		key_flag2++;	
		if(key_flag2>0)
		{
			key_flag = 2;
			key_flag2=0;
			guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent);
			IMG = 1;
		}
	}
	
}
//���ù���
void pump()
{
	printf("pump\n");
	guiJumpPage(infrared_led_wID2,GUI_NULL,infrared_PageEnterEvent2);
	if(key_flag==3)
	{
		key_flag2++;	
		if(key_flag2>0)
		{
			key_flag = 0;
			key_flag2=0;
			guiJumpPage(Test01Page_wID,GUI_NULL,DemoMain_PageEnterEvent);
		}
	}
}
//���ȹ���
void fan()
{
	printf("fan\n");
	guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent);
	if(key_flag==4)
	{
		key_flag2++;	
		if(key_flag2>0)
		{
			key_flag = 9;
			key_flag2=0;
			guiJumpPage(infrared_led_wID2,GUI_NULL,infrared_PageEnterEvent2);
			IMG = 1;
		}
	}	
}

void fan2()
{
	printf("fan2\n");
	if(key_flag==9)
	{
		key_flag2++;	
		if(key_flag2>0)
		{
			key_flag = 4;
			key_flag2=0;
			guiJumpPage(infrared_led_wID,GUI_NULL,infrared_PageEnterEvent);
			IMG = 1;
		}
	}
	
}

void all_zero()
{
	for(int i=0;i<5;i++)
	{
		red_arr[i]=0;printf("%d",red_arr[i]);
		red_img[i]=0;
	}
	red_flag =0;
	key_flag2 = 0;
	key_flag = 0;
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

                if(key_time >= 24000)   //If the key press time exceeds the set long press time, it will be judged as long press.
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
