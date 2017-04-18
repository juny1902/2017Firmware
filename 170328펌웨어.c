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

// 과제(3/30) : 과제1번 -> 아무버튼 누를때마다 00 01 10 11 으로 LED 이동 

void LED_CTL(int nLED, int CTL);

int state1,state2;

int main()
{
    
    if(GPLR1 & 0x00200000)
    { // 1번 스위치
    	state1 = 1;
    	if(state1!=1)
    	{ 
        	LED_CTL(ON,1);
        }
        
    }
    if(GPLR2 & 0x00080000)
    { // 2번 스위치
    	state2 = 1;
    	if(state2!=1)
    	{ 
        	LED_CTL(ON,2);
    	}
    	
    }
    state1 = 0;
    state2 = 0;
    
}
void LED_CTL(int CTL, int nLED)
{
    switch(nLED)
    {
        case 2:
            if(CTL==ON)
            {
                GPCR1 |= 0x00100000;
            }
            else if(CTL==OFF)
            {
                GPSR1 |= 0x00100000;
            }
            break;
        case 1:
            if(CTL==ON)
            {
                GPCR2 |= 0x00040000;
            }
            else if(CTL==OFF)
            {
                GPSR2 |= 0x00040000;
            }
            break;
    }
}