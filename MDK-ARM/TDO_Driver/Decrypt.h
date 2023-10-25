# ifndef _decrypt_h_
# define _decrypt_h_
#include "stdint.h"
#include "Y6_command.h"

#define DATA_LEN 4 

void Decrypt_pro(void);

Y6_CMD_State Y6_Set_Key( uint8_t cmd,const void *charc,uint32_t c_len);


#endif
