/* 
    201503120 Jun Young Park
    PXA270 user library for Firmware Design
    2017-03-31 

    With considering :
        1. To make easy to use for developers.
        2. Reduce repetitious operations.

    Word length of PXA270 is int(4byte,32bit)
*/

#include "user.h"

void INIT_DEVICE(void) // Setting up direction registers and Turning down both LEDs
{
    GPDR1 |= 0x00100000;
 	GPDR1 |= 0; //To ensure what is output.  
    GPDR2 |= 0x00040000;
    GPDR2 |= 0;

    GPSR1 |= 0x00100000; // To make LED1,2 set to turn off (1)
    GPSR2 |= 0x00040000;
}
int IS_SW_PRESSED(void) // Detect GPIO pin levels when it called.
{
    int dly = 1000;
    while(dly--);
    
    if(SW1_STAT && SW2_STAT) // BOTH Pressed
    {
        return BOTH;
    }
    else if(SW1_STAT) // SW1 Pressed
    {
        return SW1;
    }
    else if(SW2_STAT) // SW2 Pressed
    {  
        return SW2;
    }
    else // Neither Pressed (Neutral)
    {
        return NP; // Equals to '0'
    }
}
void LED_Control(int CTL,int N) // To avoid repetition, Set a flag outside of this function.
{
	int i;
    switch(CTL)
    {
    	case BLK: // Regardless the variable N, Both LED will blink once.
    		GPCR1 |= 0x00100000;
            GPCR2 |= 0x00040000;
	        for(i=0;i<500000;i++);
	        GPSR1 |= 0x00100000;
            GPSR2 |= 0x00040000;
	        for(i=0;i<500000;i++);
            break;	
        case ON:
            if(N == 1)
            {
            	GPCR1 |= 0x00100000; // LED1 ON 
            	GPSR2 |= 0x00040000; // LED2 OFF
            	
            } 
            else if(N == 2)
            {
            	GPCR2 |= 0x00040000; // LED2 ON
            	GPSR1 |= 0x00100000; // LED1 OFF
            	
            }
            else if(N == 3)
            {
                GPCR1 |= 0x00100000; // Both LEDs ON
                GPCR2 |= 0x00040000;
            }
           	break;
        case OFF:
            if(N == 1)
            {
                GPSR1 |= 0x00100000; // LED1 OFF
            }
            else if(N == 2)
            {
                GPSR2 |= 0x00040000;
            } // LED2 OFF
            else if(N == 3)
            {
                GPSR1 |= 0x00100000; // Both LEDs OFF
                GPSR2 |= 0x00040000;
            }
            break;
    }
}