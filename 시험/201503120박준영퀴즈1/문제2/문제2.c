#include "config.h" 
#include "stddefs.h"
#include "pxa2xx.h"
#include "16c552.h"
#include "typedef.h"
#include "except.h"
#include "user.h"

extern void vinit(void);

int main()
{
	vinit();
	INIT_DEVICE();
	
	
    while(1)
    {	
    	while(IS_SW_PRESSED()==BOTH) // 만일 양측 스위치가 눌린 상태라면 그 동안
    	{
    		while(IS_SW_PRESSED()==SW1) // 그 뒤 하나의 스위치에서 손을 떼면
    		{
    			LED_Control(BLK,3); // 그 상태가 유지되는 순간만 LED를 깜빡임.
    		}
    	}
    	LED_Control(OFF,3); // LED의 초기 상태는 OFF
	}
    return 0;
}