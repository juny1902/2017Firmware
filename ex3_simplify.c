/*

     Firmware Design

     Example 3 - Control both LEDs

*/

#include "user.h"

int main()
{
	int state=0;
    INIT_DEVICE(); // Initialize GPDR/GPSR Register
    while(1)
    {
        switch(IS_SW_PRESSED()) // Read from switches
        {
            case BOTH: // If both pressed..
                if(state)
                {
                    LED_Control(BLK,3);
                }
                state=0;
                break;
            case SW1: // If SW1 pressed..
                if(state)
                {
                    LED_Control(OFF,1);
                    LED_Control(ON,2);
                }
        	    state=0;
                break;
            case SW2: // If SW2 pressed..
                if(state)
                {
                    LED_Control(ON,1);
                    LED_Control(OFF,2);
                }
                state=0;
                break;
            default: // If neither pressed..
                if(state==1)
                {
                    LED_Control(OFF,3);
                }
                state = 0;
                break;
        }
        state = 1;
    }
    return 0;
}