#include "config.h" 
#include "stddefs.h"
#include "pxa2xx.h"
#include "16c552.h"
#include "typedef.h"
#include "except.h"
#include "user.h" // 직접 지정한 함수 및 매크로를 불러오기 위해 user.h 헤더 포함.
// Global Variable
unsigned char Flag = 0;
int i;
void usr_timer_pjy(unsigned long a)
{
	LED_Control(OFF,3);
	_delay_ms(1000);
	LED_Control(ON,3);
	_delay_ms(1000);
	RESET_TIMER();
}
void usr_handle_pjy(unsigned long a) // Interrupt Service Routine 의 정의
{
	
}
int main()
{
    vinit(); // 장치를 초기화 하기 위한 외부 함수.
    INIT_DEVICE(); // 장치를 초기화 하기 위한 함수 (GPIO 핀의 입출력 등을 정의)
    INIT_EDGE(); // 엣지 사용을 위한 설정 함수
    INIT_INTR();
    LED_Control(OFF,3);
    INIT_TIMER();
	while(1) // 주 루프
    {
    	LED_Blink_ms(3,250,1);
	}
    return 0;
}