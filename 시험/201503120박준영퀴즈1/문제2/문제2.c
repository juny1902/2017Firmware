#include "config.h" 
#include "stddefs.h"
#include "pxa2xx.h"
#include "16c552.h"
#include "typedef.h"
#include "except.h"
#include "user.h"

extern void vinit(void);

int main()
{
	vinit();
	INIT_DEVICE();
	
	
    while(1)
    {	
    	while(IS_SW_PRESSED()==BOTH) // ���� ���� ����ġ�� ���� ���¶�� �� ����
    	{
    		while(IS_SW_PRESSED()==SW1) // �� �� �ϳ��� ����ġ���� ���� ����
    		{
    			LED_Control(BLK,3); // �� ���°� �����Ǵ� ������ LED�� ������.
    		}
    	}
    	LED_Control(OFF,3); // LED�� �ʱ� ���´� OFF
	}
    return 0;
}