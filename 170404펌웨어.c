// 클럭 설정
// (메뉴얼) 클럭주파수 = 12MHz * CCCR(L) * (CCCR(2N)/2)
// -> 프리셋이 제공되므로 표를보고 사용하면된다.

// user.c LED 깜빡이는중에 버튼 입력받으면 탈출하도록 개선 (인터럽트 유사)

// 17/04/11 퀴즈 분반 확인 SW/LED (오픈소스, 컨닝금지!)

#include "config.h" 
#include "stddefs.h"
#include "pxa2xx.h"
#include "16c552.h"
#include "typedef.h"
#include "except.h"

#include "user.h"

extern void vinit(void);
void Set_Speed(int n);
#define LED_ON(n,m) (*(volatile int *)(0x40e00028-(12*m)+4*(n-1))) |= (0x00100000 >> (2*(n-1)))


int main()
{
	int i=2;
	vinit();
	INIT_DEVICE();
	Set_Speed(2); // 초기화
	
    while(1)
    {
        if(IS_SW_PRESSED()==SW1 || IS_SW_PRESSED()==SW2)
        {
            if(i>7) i=2;
            else i++;
            
            Set_Speed(i);
      
        }
        
        LED_Control(BLK,3); // LED 루틴 내에서 SW 작동 안됨.
    }
	
    return 0;
}
void Set_Speed(int n)
{
    CCCR = (1<<25) | (n<<7) | (16<<0); // Turbo 312MHz, (13MHz * L(16) * N(3))
	MDREFR |=((1<<29)|(1<<19)|(1<<17)); // From the manual(Clock Setting)
    __asm{ // Inline ASM code
        mrc p14, 0, r0, c6, c0, 0
        orr r0, r0, #0xb
        mcr p14, 0, r0, c6, c0, 0
    }
}