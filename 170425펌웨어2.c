#include "config.h" 
#include "stddefs.h"
#include "pxa2xx.h"
#include "16c552.h"
#include "typedef.h"
#include "except.h"
#include "user.h"
int flag = 0;

//-- ���ͷ�Ʈ ���� --//
/* 
	GEDR�� ���� �����Ŀ� ���� ���� ������ 
    �� ������ ���� ��� IRQ �� ���� ��.
    ���� �ѹ� ������ �а� ���� GEDR �� �ʱ�ȭ �Ͽ�
    �ٽ� ������ ���� �غ� �ؾ� ��.
    
    ISR�� �ּ�ȭ �սô�
    
    �������� : �켱������ ���� ���μ����� ���� ���μ����� �������.
*/
void usr_handle_pjy(unsigned long a) // To minimalize routine for ISR, We use flag for each switches.
{
	if(GET_EDGE_SW1) // When SW1 Edge Detected
	{
		flag = 1;
	}
	else if(GET_EDGE_SW2) // When SW2 Edge Detected
	{
		flag = 2;
	}

	
    CLEAR_GEDR(); // Initialize GEDR To clear previous edge data to avoid refrain ISR.
}
//------------------------------ //

int main()
{
    vinit();
    INIT_DEVICE();
    INIT_EDGE();
    INIT_INTR();
    while(1)
    {
    	if(flag == 1)
    	{
			LED_Control(BLK,3);
			flag = 2;
			
    	}
    	else if(flag == 2)
    	{
    		if(SW1_STAT)
    			LED_Control(ON,3);
    		else
    			flag = 0;
    	}
    	else
    	{
    		LED_Control(OFF,3);
    	}
    }    
    return 0;
}