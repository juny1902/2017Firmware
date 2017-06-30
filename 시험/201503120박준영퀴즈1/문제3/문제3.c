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
	int cnt = 0;
	int flag = 1;
	vinit();
	INIT_DEVICE();
	LED_Control(OFF,3);

    while(1)
    {
    	if((IS_SW_PRESSED() == SW1)) // SW1 을 누를 때 마다
    	{
    		if(flag == 1)
    		{
    			cnt++; // 카운트 하나씩 증가
    			flag = 0;
    		}
    		flag = 0;
    	}
    	if(((cnt%2)==0) && (IS_SW_PRESSED() == SW2))
    	/* 누른 횟수가 짝수일때 스위치 2번을 누르면 */
    	{
    		LED_Control(BLK,3); // LED 1회 점멸 
    		LED_Control(BLK,3); // LED 1회 점멸
    		cnt = 0; // 카운트 초기화
    	}
    	flag = 1;
    	    
    }
}