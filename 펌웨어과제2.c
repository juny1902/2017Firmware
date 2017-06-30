/* 

    과제2 : 일정 횟수 (3번)이상 switch 누르면 LED 켜짐 (스위치 누르면 꺼짐)
    과제3 : SW1 누른 횟수만큼 LED 깜빡임. (SW2 누르면 작동)

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

void LED_Control(int CTL,int N);
int main()
{
	int dly=0;
	int count=0;
	int flag=1;
	
    GPDR1 |= 0x00100000;
 	GPDR1 |= 0;//To ensure what is output.  
    GPDR2 |= 0x00040000;
    GPDR2 |= 0;
    LED_Control(OFF,3); // Initialization
    while(1)
    {
        if((GPLR1 & 0x00200000)==0) // 스위치 1 누르면 카운트 ++ 
        {
       		for(dly=0;dly<1000;dly++);
       		if(flag) count++;
        	flag=0;
        }
        else if((GPLR2 & 0x00080000)==0) // 스위치 2 누르면
        {
            for(dly=0;dly<1000;dly++);
            if(flag) LED_Control(OFF,3);
            flag=0;
            count = 0;
        }
        else
        {
        	flag = 1;
        }

        if(count>=2)
        {
            LED_Control(ON,3);
        }
        else
        {
       		LED_Control(OFF,3); // Initialization
    	}
    }
    return 0;
}
void LED_Control(int CTL,int N)
{
	int i;
    switch(CTL)
    {
    	case BLK:
    		GPCR1 |= 0x00100000;
            GPCR2 |= 0x00040000;
	        for(i=0;i<500000;i++);
	        GPSR1 |= 0x00100000;
            GPSR2 |= 0x00040000;
	        for(i=0;i<500000;i++);	
        case ON:
            if(N == 1)
            {
            	GPCR1 |= 0x00100000; // LED 점등
            	GPSR2 |= 0x00040000;
            	
            } 
            else if(N == 2)
            {
            	GPCR2 |= 0x00040000;
            	GPSR1 |= 0x00100000;
            	
            }
            else
            {
                GPCR1 |= 0x00100000;
                GPCR2 |= 0x00040000;
            }
           	break;
        case OFF:
            if(N == 1){GPSR1 |= 0x00100000;} // LED 소등
            else if(N == 2){GPSR2 |= 0x00040000;}
            else
            {
                GPSR1 |= 0x00100000;
                GPSR2 |= 0x00040000;
            }
            break;
    }
}
