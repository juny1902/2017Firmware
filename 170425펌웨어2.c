#include "config.h" 
#include "stddefs.h"
#include "pxa2xx.h"
#include "16c552.h"
#include "typedef.h"
#include "except.h"
#include "user.h"
int flag = 0;

//-- 인터럽트 벡터 --//
/* 
	GEDR로 값을 읽은후에 값이 남아 있으면 
    그 값으로 인해 계속 IRQ 로 가게 됨.
    따라서 한번 엣지를 읽고 나면 GEDR 을 초기화 하여
    다시 엣지를 받을 준비를 해야 함.
    
    ISR은 최소화 합시다
    
    역전현상 : 우선순위가 낮은 프로세스에 높은 프로세스가 지장받음.
*/
void usr_handle_pjy(unsigned long a)
{
	if(GET_EDGE_SW1)
	{
		flag = 1;
	} 
	else if(GET_EDGE_SW2)
	{
		flag = 2;
	}
	
    CLEAR_GEDR();
}
//------------------------------ //

int main()
{
    vinit();
    INIT_DEVICE();
    INIT_EDGE();
    INIT_INTR();
    while(1)
    {
    	if(flag == 1)
    	{
    		int i;
			for(i=0;i<2;i++)
			{
				LED_Control(BLK,3);
			}
			flag = 0;
    	}
    	else if(flag == 2)
    	{
    		LED_Control(OFF,3);
    		_delay_ms(2000);
    		flag = 0;
    	}
    	else
    	{
    		LED_Control(ON,3);
    	}
    }    
    return 0;
}