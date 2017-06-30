#include "config.h" 
#include "stddefs.h"
#include "pxa2xx.h"
#include "16c552.h"
#include "typedef.h"
#include "except.h"
#include "user.h" // 직접 지정한 함수 및 매크로를 불러오기 위해 user.h 헤더 포함.
int wait=148000000; // 기다림을 위한 카운트 다운.
int flag = 0;
int t = 0;
char memory[1000000];
void usr_handle_pjy(unsigned long a) // Interrupt Service Routine 의 정의
{	
		if(SW0_STAT && SW1_STAT) // 양 스위치가 눌러지면
		{
			memory[t] = 3; // 해당 시간위치의 메모리에 3 기록
		}
		else if(SW0_STAT)
		{
			memory[t] = 1; // 해당 시간위치의 메모리에 1 기록
		}
		else if(SW1_STAT)
		{
			memory[t] = 2; // 해당 시간위치의 메모리에 2 기록 
		}
		t++;

	wait = 148000000; // 입력이 들어오면 대기시간 초기화 (약 2초)
	CLEAR_GEDR(); // 다음 엣지를 받기위한 레지스터 클리어 
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
    	if(wait && i<1000000) // 대기시간이 남아있고 입력받은 내용이 제한 공간보다 작은경우 
    	{
    		wait--; // 대기시간 카운트다운
    	}
    	else // 대기시간 만료 혹은 메모리 공간 초과시
    	{
    		while(t) // t 회만큼 반복 
    		{
    			if(memory[t] == 1) // 메모리 배열의 기록에 따라 1이면
    			{
    				LED_Control(ON,1); // LED 1 점등
    				LED_Control(OFF,2);
    			}
    			else if(memory[t] == 2) // 2이면
    			{
    				LED_Control(ON,2); // LED 2 점등
    				LED_Control(OFF,1);
    			}
    			else if(memory[t] == 3) // 3이면
    			{
    				LED_Control(ON,3); // 양측 LED 점등
    			}
    			t--; // 시간 인덱스 하나씩 감소 
    			wait = 148000000;
    		}
    	}
    	LED_Control(OFF,3);
    }    
    return 0;
}