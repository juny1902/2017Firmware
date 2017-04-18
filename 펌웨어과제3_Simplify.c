/* 

    과제2 : 일정 횟수 (3번)이상 switch 누르면 LED 켜짐 (스위치 누르면 꺼짐)
    과제3 : SW1 누른 횟수만큼 LED 깜빡임. (SW2 누르면 작동)

    다음주 화요일(4/4) 전까지 숙제 
    ㄴ LED 함수 스위치 입력받는 함수 -> 좋은함수로 (1시전까지 메일주소 : judehana0@daum.net) 보고서

    다다음주 화요일 퀴즈 (4/11) - LED와 SW (A반 -> B반 순서)

*/
#include "user.h"
int main()
{
	int i=0;
	int count=0;
	int flag=1;
    INIT_DEVICE();
    while(1)
    {
        if(IS_SW_PRESSED()==SW1) // Add count when SW1 pressed (for once)
        {
       		if(flag) // To avoid repetition when SW1 being pressed
       		{
            	count++;
        	}
        	flag=0;
        }
        else if(IS_SW_PRESSED()==SW2) // Blink
        {
            for(i=0; i<count;i++) // Repeat for 'Count' times
            {
                LED_Control(BLK,3);
            }
            count = 0;
        }
        else // If Neither pressed
        {
        	flag = 1; // Set flag 'True' again
        }
    }
    return 0;
}