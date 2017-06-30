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
	
	int flag=1;
	int status=0;
	
    GPDR1 |= 0x00100000;
 	GPDR1 |= 0;//To ensure what is output.  
    GPDR2 |= 0x00040000;
    GPDR2 |= 0;
    LED_Control(OFF,3); // Initialization
        
    while(1)
    {
    	// 스위치가 PULL-UP 상태이므로 눌리면 0 출력.
        if((((GPLR1 & 0x00200000)==0) || ((GPLR2 & 0x00080000)==0)) == 1) // 둘중 하나 누르면
        {
        	if(flag)
        	{
	        	for(dly=0;dly<1000000;dly++); // Debounce
	        	status++;
	        	if(status>3) status=0;
			}	
	        flag = 0;
        	
        }
        else
        {
        	flag = 1;
        }
        switch(status)
        {
        	case 1:
	    		LED_Control(ON,1);
	    		break;
	    	case 2:
	    		LED_Control(ON,2);
	    		break;
	    	case 3:
	    		LED_Control(ON,3);
	    		break;
	    	default:
	    		LED_Control(OFF,3);
        		break;
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