/* 
    201503120 Jun Young Park
    PXA270 user library for Firmware Design
    2017-4-11 Quiz 1

    With considering :
        1. To make easier to use for developers.
        2. Reduce repetitious operations. 

    Word length of PXA270 is int(4byte,32bit)
*/

#include "user.h"
void CLEAR_GEDR(void) // Initialize GEDR by setting it true
{
    GEDR1 |= 0X00200000; // ED 1 Clear
    // GEDR2 |= 0X00080000; // ED 2 Clear
}
void INIT_EDGE(void)
{
		GFER1 |= 0x00200000; // Using GPIO53 as Falling Edge
        // GRER1 |= 0x00200000; // Using GPIO53 as Rising Edge
        // GFER2 |= 0x00080000;
        // GRER2 |= 0x00080000;
}
void INIT_DEVICE(void) // Setting up direction registers and Turning down both LEDs
{
    GPDR1 |= (1 << 20); // Using GPIO52 as Output 
 	GPDR1 &= ~(1 << 18); //Using GPIO53 as Input
    GPDR2 |= (1 << 18); // Using GPIO82 as Output
    GPDR2 &= ~(1 << 19); // Using GPIO83 as Input
    Set_Clock(2); // Initalize Clock
}
int IS_SW_PRESSED(void) // Detect GPIO pin levels when it called.
{
    int dly = 1000; 
    while(dly--); // Debounce
    
    if(SW1_STAT && SW2_STAT) // BOTH Pressed
    {
        return BOTH;
    }
    else if(SW1_STAT) // SW1 Pressed, Left
    {
        return SW1;
    }
    else if(SW2_STAT) // SW2 Pressed, Right
    {  
        return SW2;
    }
    else // Neither Pressed (Neutral)
    {
        return NP; // Equals to '0'
    }
}
int LED_Control(int CTL,int N) // To avoid repetition, Set a flag outside of this function.
{
	int i;
    switch(CTL)
    {
    	case BLK: // Regardless the variable N, Both LED will blink once.
    	 	i = 10000000;
    		GPCR1 |= 0x00100000;
            GPCR2 |= 0x00040000;
            while(i--);
            {
            	if(SW1_STAT || SW2_STAT) return 0;
            }
            i = 10000000;
	        GPSR1 |= 0x00100000;
            GPSR2 |= 0x00040000;
	        while(i--);
            {
            	if(SW1_STAT || SW2_STAT) return 0;
            }
            break;	
        case ON:
            if(N == 1) // Top
            {
            	GPCR1 |= 0x00100000; // LED1 ON 
            	GPSR2 |= 0x00040000; // LED2 OFF
            	
            } 
            else if(N == 2) // Bottom
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
    return 0;
}
void Set_Clock(int n) // Range = (2, 6)
{
		    CCCR = (1<<25) | (n<<7) | (16<<0); // Turbo Variable(2 to 6), (13MHz * L(16) * N(3))
			MDREFR |=((1<<29)|(1<<19)|(1<<17)); // From the manual(Clock Setting)
		    __asm{ // Inline ASM code
		        mrc p14, 0, r0, c6, c0, 0
		        orr r0, r0, #0xb
		        mcr p14, 0, r0, c6, c0, 0
			}		
}
