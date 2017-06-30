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
	int flag=0;
	
	vinit();
	INIT_DEVICE();
	
	
    while(1)
    {	
    	while(IS_SW_PRESSED()==BOTH) // 만일 양측 스위치가 눌린 상태라면 그 동안
    	{
    		LED_Control(BLK,3); // 1회전당 LED를 1회 깜빡임 
    		flag = 0; // LED가 소등되도록 FLAG를 0으로 설정 
    	}
    	if(IS_SW_PRESSED()==SW1) // 스위치 1이 눌렸다면,
    	{
    		flag = 1; // LED가 점등되도록 FLAG를 1로 설정
    	}
    	else if(IS_SW_PRESSED()==SW2) // 스위치 2가 눌렸다면,
    	{
    		flag = 0; // LED가 소등되도록 FLAG를 0으로 설정 
    	}
    	
    	if(flag==1) // 플래그가 참이면
    	{
    		LED_Control(ON,3); // LED 점등 
    	}
    	else
    	{
    		LED_Control(OFF,3); // LED 소등
    	}
	}
    return 0;
}