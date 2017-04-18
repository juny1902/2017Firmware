/* 

    170316 펌웨어 설계

    S2 - SWITCH00 - BB_OB_STB - BB_OB_STB_GPIO53
    S3 - SWITCH01 - BB_IB_CLK - BB_IB_CLK_GPIO83

    목표 : Switch Device의 Register, Firmware 이해

    문제점 :
    GPLR1을 계속 검출하는 현상.
*/

#define GPDR1 (*(volatile int *)0x40e00010)
#define GPCR1 (*(volatile int *)0x40e00028) 
#define GPSR1 (*(volatile int *)0x40e0001c)
#define GPDR2 (*(volatile int *)0x40e00014)
#define GPCR2 (*(volatile int *)0x40e0002c)
#define GPSR2 (*(volatile int *)0x40e00020)
#define GPLR1 (*(volatile int *)0x40e00004)
#define GPLR2 (*(volatile int *)0x40e00008)

int main(void)
{
	int i;
	volatile int flag1 = 0;
	volatile int flag2 = 0;
    GPDR1 |= 0x00100000; // GPDR1 의 해당 비트(GPIO52)에 True를 마스킹 (OUTPUT 으로 사용)
	GPDR2 |= 0x00040000; // GPDR2 의 해당 비트(GPIO82)에 True를 마스킹 (OUTPUT 으로 사용)
    while(1)
    {
        if(GPLR1 & 0x00200000) // GPLR1 의 해당 핀 (GPIO53)의 레벨 검출
        {
        	if(flag1 == 1) flag1 = 0;
        	else flag1 = 1;
        }
        if(GPLR2 & 0x00080000) // GPLR2 의 해당 핀 (GPIO83)의 레벨 검출
        {
        	if(flag2 == 1) flag2 = 0;
        	else flag2 = 1;
        }
        if(flag1 == 1)
        {
        	GPCR1 |= 0x00100000;	
        }
        else
        {
        	GPSR1 |= 0x00100000;
        }
        	
        
       	if(flag2 == 1)
        { 
        	GPCR2 |= 0x00040000;
        }
        else
        {
        	GPSR2 |= 0x00040000;
        }  
    }
    return 0;
}