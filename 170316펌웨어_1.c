/* 

    170316 펌웨어 설계

    S2 - SWITCH00 - BB_OB_STB - BB_OB_STB_GPIO53
    S3 - SWITCH01 - BB_IB_CLK - BB_IB_CLK_GPIO83

    목표 : Switch Device의 Register, Firmware 이해

	명확하게 하드웨어를 이해하며 코딩하자

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
	int flag1 = 0, flag2 = 0;
    GPDR1 |= 0x00100000; // GPDR1 의 해당 비트(GPIO52)에 True를 마스킹 (OUTPUT 으로 사용)
	GPDR2 |= 0x00040000; // GPDR2 의 해당 비트(GPIO82)에 True를 마스킹 (OUTPUT 으로 사용)
	GPSR1 |= 0x00100000; // 초기값은 참 (LED 꺼짐)
	GPSR2 |= 0x00040000;
	
    while(1)
    {
        if(GPLR1 & 0x00200000) // GPLR1 의 해당 핀 (GPIO53)의 레벨이 0 (PULL-UP 이므로 버튼이 눌린상태) 이면
        {
			for(i=0; i<1000; i++); // Debounce 를 위한 지연

			if(flag1 == 0) flag1 = 1 ; // 플래그1 = 참
			else flag1 = 0;
        }
		if(GPLR2 & 0x00080000) // GPLR2 의 해당 핀 (GPIO83)의 레벨이 0 (PULL-UP 이므로 버튼이 눌린상태) 이면
        {
			for(i=0; i<1000; i++); // Debounce 를 위한 지연

			if(flag2 == 0) flag2 = 1 ;
			else flag2 = 0;
        }

        if(flag1 == 1)
		{
			GPSR1 |= 0x00100000;
		}
		else if(flag1 == 0)
		{
			GPCR1 |= 0x00100000;
		}
		if(flag2 == 1)
		{
			GPSR2 |= 0x00040000;
		}
		else if(flag2 == 0)
		{
			GPCR2 |= 0x00040000;
		}
        
    }
    return 0;
}