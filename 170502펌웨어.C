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
void usr_handle_pjy(unsigned long a) // Interrupt Service Routine 의 정의
{
	if(Flag == 1)
	{
		LED_Control(OFF,3);
		return;
	}

	/* GEDR을 ISR 초반에서 초기화한 경우 
	이 시점에서 GEDR에 엣지가 기록되어도 
	인터럽트가 재귀되진 않음. 따라서 ISR을 모두 마친 후
	GEDR에 의해 인터럽트 다시 발생 */
	
	Flag = 1;
	LED_Control(OFF,3);
	
	for(i=0;i<200000;i++)	// GEDR을 ISR DELAY간에서 초기화한 경우
	{						// 스위치를 DELAY간에 스위치를 눌러도
		CLEAR_GEDR();		// GEDR값이 계속 초기화되므로
	}						// EDGE가 생겼다 판단하지못해 ISR이 끝나도
							// 다시 ISR로 들어오지않는다.
							// 결과적으로 2초만 DELAY된다.	
	Flag = 0;
	LED_Control(ON,3);
	_delay_ms(500);
}
int main()
{
    vinit(); // 장치를 초기화 하기 위한 외부 함수.
    INIT_DEVICE(); // 장치를 초기화 하기 위한 함수 (GPIO 핀의 입출력 등을 정의)
    INIT_EDGE(); // 엣지 사용을 위한 설정 함수
    INIT_INTR(); // 
    LED_Control(OFF,3);
	while(1) // 주 루프
    {
    	LED_Blink_ms(3,250,1);
	}
    return 0;
}