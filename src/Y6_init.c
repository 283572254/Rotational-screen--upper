#include "SystemHeart.h"
#include "SystemUart.h"
#include "pwm.h"
#include "Led.h"
void init_pro(void)
{
		
		SystemHeart_Init();
	    SystemUart_Init(115200);    
		Led_init();	
}
 
	
void $Sub$$main(void)
{
	  init_pro();
	
      $Super$$main();
}

