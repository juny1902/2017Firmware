#include "config.h" 
#include "stddefs.h"
#include "pxa2xx.h"
#include "16c552.h"
#include "typedef.h"
#include "except.h"
#include "user.h" // 직접 지정한 함수 및 매크로를 불러오기 위해 user.h 헤더 포함.
void usr_handle_pjy(unsigned long a) // Interrupt Service Routine 의 정의
{
}
int main()
{
	int j = 0;
	int flag = 0;
    vinit(); // 장치를 초기화 하기 위한 외부 함수.
    INIT_DEVICE(); // 장치를 초기화 하기 위한 함수 (GPIO 핀의 입출력 등을 정의)
    INIT_EDGE(); // 엣지 사용을 위한 설정 함수
    INIT_INTR();
    LED_Control(OFF,3);
    while(1) // 주 루프
    {
    	if(flag==1)
    	{
    		LED_Control(3,ON);
    		_delay_ms(2000);
    		flag = 0;
    	}
    	LED_Control(1,OFF);
	    _delay_ms(1000);
	    	
	    LED_Control(1,ON);
		_delay_ms(1000);
	}
    return 0;
}