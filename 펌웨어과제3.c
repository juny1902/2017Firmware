/* 

    과제2 : 일정 횟수 (3번)이상 switch 누르면 LED 켜짐 (스위치 누르면 꺼짐)
    과제3 : SW1 누른 횟수만큼 LED 깜빡임. (SW2 누르면 작동)

    다음주 화요일(4/4) 전까지 숙제 
    ㄴ LED 함수 스위치 입력받는 함수 -> 좋은함수로 (1시전까지 메일주소 : judehana0@daum.net) 보고서

    다다음주 화요일 퀴즈 (4/11) - LED와 SW (A반 -> B반 순서)

*/
#define GPDR1 (*(volatile int *)0x40e00010)
#define GPCR1 (*(volatile int *)0x40e00028) 
#define GPSR1 (*(volatile int *)0x40e0001c)
#define GPDR2 (*(volatile int *)0x40e00014)
#define GPCR2 (*(volatile int *)0x40e0002c)
#define GPSR2 (*(volatile int *)0x40e00020)
#define GPLR1 (*(volatile int *)0x40e00004)
#define GPLR2 (*(volatile int *)0x40e00008)

#define BLK 2
#define ON 1
#define OFF 0

#define BOTH 3
#define SW2 2
#define SW1 1
#define NP 0
char IS_SW_PRESSED(void);
void LED_Control(int CTL,int N);
int main()
{
	int i=0;
	int dly=0;
	int count=0;
	int flag=1;
	
    GPDR1 |= 0x00100000;
 	GPDR1 |= 0; //To ensure what is output.  
    GPDR2 |= 0x00040000;
    GPDR2 |= 0;
    LED_Control(OFF,3); // Initialization
    while(1)
    {
        if(IS_SW_PRESSED()==SW1) // 스위치 1 누르면 카운트 ++ 
        {
       		if(flag)
       		{
            	count++;
        	}
        	flag=0;
        }
        else if(IS_SW_PRESSED()==SW2) // 스위치 2 누르면 카운트 만큼 Blink
        {
            for(i=0; i<count;i++)
            {
                LED_Control(BLK,3);
            }
            count = 0;
        }
        else // 어느 버튼도 누르지 않으면
        {
        	flag = 1; // 반복방지를 위한 플래그를 다시 세움
        }
    }
    return 0;
}
char IS_SW_PRESSED(void);
{
    for(dly=0;dly<1000;dly++); // Debounce를 위한 Delay

    if((((GPLR1 & 0x00200000)==0) && ((GPLR2 & 0x00080000)==0)) == 1)
    {
        return BOTH;
    }
    else if((GPLR1 & 0x00200000)==0)
    {
        return SW1;
    }
    else if((GPLR2 & 0x00080000)==0)
    {  
        return SW2;
    }
    else
    {
        return NP;
    }
}
void LED_Control(int CTL,int N)
{
	int i;
    switch(CTL)
    {
    	case BLK: // 1회 Blink
    		GPCR1 |= 0x00100000;
            GPCR2 |= 0x00040000;
	        for(i=0;i<500000;i++);
	        GPSR1 |= 0x00100000;
            GPSR2 |= 0x00040000;
	        for(i=0;i<500000;i++);	
        case ON:
            if(N == 1)
            {
            	GPCR1 |= 0x00100000; // LED1 점등
            	GPSR2 |= 0x00040000; // LED2 소등
            	
            } 
            else if(N == 2)
            {
            	GPCR2 |= 0x00040000; // LED2 점등
            	GPSR1 |= 0x00100000; // LED1 소등
            	
            }
            else if(N == 3)
            {
                GPCR1 |= 0x00100000; // LED1&2 소등
                GPCR2 |= 0x00040000;
            }
           	break;
        case OFF:
            if(N == 1) GPSR1 |= 0x00100000; // LED1 소등
            else if(N == 2) GPSR2 |= 0x00040000; // LED2 소등
            else
            {
                GPSR1 |= 0x00100000; // LED1&2 소등
                GPSR2 |= 0x00040000;
            }
            break;
    }
}
