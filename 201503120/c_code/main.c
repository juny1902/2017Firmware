#include "config.h" 
#include "stddefs.h"
#include "pxa2xx.h"
#include "16c552.h"
#include "typedef.h"
#include "except.h"
#include "user.h"

unsigned char flag = 1;

//-- 인터럽트 벡터 --//
void usr_handle_pjy(unsigned long a)
{
	int i;
	LED_Control(OFF,3);
    CLEAR_GEDR();
    for(i=0; i<7428571; i++);
}
//------------------------------ //

int main()
{
    vinit();
    INIT_DEVICE();
    INIT_EDGE();
    INIT_INTR();
    LED_Control(ON,3);
    while(1)
    {
    	LED_Control(BLK,3);
       
    }

    
    return 0;
}