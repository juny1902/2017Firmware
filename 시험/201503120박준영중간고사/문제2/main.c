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
    vinit(); // 장치를 초기화 하기 위한 외부 함수.
    INIT_DEVICE(); // 장치를 초기화 하기 위한 함수 (GPIO 핀의 입출력 등을 정의)
    INIT_EDGE(); // 엣지 사용을 위한 설정 함수
    while(1) // 주 루프
    {
    	LED_Blink_ms(3,250,1); // 양측 LED를 250MS 간격으로 깜빡인다.
    	if(GET_EDGE_SW0) // GPIO53 의 Rising Edge를 감지하면 
    	{
    		if(SW1_STAT) // 스위치 1이 눌려있는지 여부를 확인하여
    		{
    			LED_Control(ON,3); // 눌려있으면 LED를 
    			_delay_ms(2000); // 2초간 점등한다.
    		}
    		else
    		{
    			LED_Control(OFF,3); // 눌려있지 않으면 LED를
    			_delay_ms(2000); // 2초간 소등한다.
    		}
    	}
    	
    }    
    return 0;
}