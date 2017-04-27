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
void usr_handle_pjy(unsigned long a)
{
	if(GET_EDGE_SW1)
	{
		flag = 1;
	} 
	else if(GET_EDGE_SW2)
	{
		flag = 2;
	}
	
    CLEAR_GEDR();
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
    		int i;
			for(i=0;i<2;i++)
			{
				LED_Control(BLK,3);
			}
			flag = 0;
    	}
    	else if(flag == 2)
    	{
    		LED_Control(OFF,3);
    		_delay_ms(2000);
    		flag = 0;
    	}
    	else
    	{
    		LED_Control(ON,3);
    	}
    }    
    return 0;
}