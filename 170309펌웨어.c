/* 

펌웨어 설계 2강
보강이 생기면 - 월요일 저녁

다음주 - 화요일 - 평소대로(세팅하고 314로), 
     ㄴ  목요일 - 3시~6시 (3시간 보강)
다다음주 - 수업 없음.

-목표-
1. LED Device 회로 보고 이해
2. LED Device의 Register 이해
3. LED Firmware 제작

-미션-
1.  자료실에서 메뉴얼, 회로도 확인

*/

// 그냥 한번 해 봅시다. (F7, Make 이용 컴파일)

#define GPDR1 (*(volatile int *)0x40e00010) // GPDR1(GPIO Direction Register 1) 를 해당 번지에 있는 4바이트의 값으로 정의
#define GPCR1 (*(volatile int *)0x40e00028) // GPCR1(GPIO Control Register 1) 를 해당 번지에 있는 4바이트의 값으로 정의
#define GPSR1 (*(volatile int *)0x40e0001c) // GPSR1 를 해당 번지에 있는 4바이트의 값으로 정의
#define GPDR2 (*(volatile int *)0x40e00014)
#define GPCR2 (*(volatile int *)0x40e0002c) 
#define GPSR2 (*(volatile int *)0x40e00020) // GPDR1,2 / GPCR1,2 간의 규칙으로 추론하여 값 얻어냄 (0x1c + 0x04 = 0x20)

int main(void)
{

    GPDR1 | = 0x00100000; // OR(|) 연산으로 해당 비트 매스킹
    GPDR2 | = 0x00040000; // ::
   
   while(true)
   {
        GPCR1 | = 0x00100000; // 아래에서 2번째 LED 점등
        for(int i=0; i<=10000000; i++);
        GPSR1 | = 0x00100000; // 아래에서 2번째 LED 소등
        GPCR2 | = 0x00040000;
        for(int i=0; i<=10000000; i++);
        GPSR2 | = 0x00040000;
   }
    return 0;
}