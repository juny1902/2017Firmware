/*
        170407 펌웨어 설계
        Edge를 활용한 스위치 제어

        누를때 반응 안시키는 이유 (잘못되거나, 카운트를 잘못할까봐 유저에게 딜레이를 줌)
    
        1. 레벨 감지가 아닌 변화되는 순간을 감지 (0->1, 1->0)
        2. CPU에게 계속 폴링을 시키는 것을 방지 (인터럽트)
        3. 누르는 순간 떼는 순간을 감지

        용도 : 여러번 눌림 방지, 클럭의 수 확인, 키가 눌려진 시간 확인, 누를때마다 LED ON
        
        레지스터 : GEDR,GRDR,GFER 사용
        GEDR : Edge : 읽는다. (0-미검출, 1-검출), 쓴다 (0-아무것도아님,1-검출내역초기화) // 한번 읽고나면 초기화
        GRDR : Rising : 상승엣지 검출을 원하는 부분에 세팅(GPIO)
        GFDR : Falling : 하강엣지 검출을 원하는 부분에 세팅(GPIO)
        RD or FR 세팅 -> 해당하는 엣지 발생시 GEDR의 값 변화. -> 우리는 그거를 읽는다.
        
        어려운 문제 : 엣지를 쓰지 않고 LED 깜빡이는 중에 버튼 입력받기

        다음주 화요일 퀴즈 (LED,SW,클럭)
        A팀 B팀 월요일에 공지, 실습시험 -> 사이버에 올림 -> 올리고 나서 다운로드 받아 체크 

        1시간 20분, 4문제, 목요일 공강.

        중간고사 기간 -> 정상수업

        5.1 월요일 저녁 2시간 중간고사
        5.2 화요일 수업 -> 5.4 고민해봄

*/

#include "config.h" 
#include "stddefs.h"
#include "pxa2xx.h"
#include "16c552.h"
#include "typedef.h"
#include "except.h"
#include "user.h"
int main()
{
    char flag = 1;
    vinit();
    INIT_DEVICE();
    INIT_EDGE();
    LED_Control(OFF,3);
    while(1)
    {
        if(GET_EDGE_SW1)
        {
            if(flag)
            {
                LED_Control(ON,1);
                flag = 0;
            }
            else
            {
                LED_Control(OFF,1);
                flag = 1;
            }
            CLEAR_GEDR();
            
        }
        
    }
    
    return 0;
}