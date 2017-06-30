#include "config.h" 
#include "stddefs.h"
#include "pxa2xx.h"
#include "16c552.h"
#include "typedef.h"
#include "except.h"
#include "user.h" // 직접 지정한 함수 및 매크로를 불러오기 위해 user.h 헤더 포함.
int flag = 0;
void usr_handle_pjy(unsigned long a) // Interrupt Service Routine 의 정의
{
	if(GET_EDGE_SW0) // 인터럽트 루틴에서 SW0 의 Rising Edge 가 감지되면
	{
		flag = 1; // 플래그를 1로 설정해준다.
	}
	CLEAR_GEDR(); // 한번 읽은 엣지값이 GEDR에 남아있지 않도록 GEDR을 클리어 해준다.
}
int main()
{
    vinit(); // 장치를 초기화 하기 위한 외부 함수.
    INIT_DEVICE(); // 장치를 초기화 하기 위한 함수 (GPIO 핀의 입출력 등을 정의)
    INIT_EDGE(); // 엣지 사용을 위한 설정 함수
    // SW0 이 떼지는 순간을 감지하기 위해 GPIO53의 Rising Edge 감지.
    INIT_INTR(); // 인터럽트 사용을 위한 설정 함수
    while(1) // 주 루프
    {
    	LED_Blink_ms(3,250,1); // 양측 LED를 500MS 간격으로 깜빡인다.
    	if(flag == 1) // 인터럽트에 의해 플래그가 1로 변하면
    	{
    		if(SW1_STAT) // 스위치 1이 눌려있는지 여부를 확인하여
    		{ 
    			LED_Control(ON,3); // 눌려있으면 LED를 
    			_delay_ms(2000); // 2초간 점등하고
    			flag = 0; // 플래그를 다시 내린다. 
    		}
    		else
    		{
    			LED_Control(OFF,3); // 눌려있지 않으면 LED를
    			_delay_ms(2000); // 2초간 소등하고
    			flag = 0; // 플래그를 다시 내린다.
    		}
    	}
    	
    }    
    return 0;
}