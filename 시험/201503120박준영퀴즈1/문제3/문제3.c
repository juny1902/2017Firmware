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
	int cnt = 0;
	int flag = 1;
	vinit();
	INIT_DEVICE();
	LED_Control(OFF,3);

    while(1)
    {
    	if((IS_SW_PRESSED() == SW1)) // SW1 �� ���� �� ����
    	{
    		if(flag == 1)
    		{
    			cnt++; // ī��Ʈ �ϳ��� ����
    			flag = 0;
    		}
    		flag = 0;
    	}
    	if(((cnt%2)==0) && (IS_SW_PRESSED() == SW2))
    	/* ���� Ƚ���� ¦���϶� ����ġ 2���� ������ */
    	{
    		LED_Control(BLK,3); // LED 1ȸ ���� 
    		LED_Control(BLK,3); // LED 1ȸ ����
    		cnt = 0; // ī��Ʈ �ʱ�ȭ
    	}
    	flag = 1;
    	    
    }
}