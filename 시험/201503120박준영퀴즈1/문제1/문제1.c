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
	int flag=0;
	
	vinit();
	INIT_DEVICE();
	
	
    while(1)
    {	
    	while(IS_SW_PRESSED()==BOTH) // ���� ���� ����ġ�� ���� ���¶�� �� ����
    	{
    		LED_Control(BLK,3); // 1ȸ���� LED�� 1ȸ ������ 
    		flag = 0; // LED�� �ҵ�ǵ��� FLAG�� 0���� ���� 
    	}
    	if(IS_SW_PRESSED()==SW1) // ����ġ 1�� ���ȴٸ�,
    	{
    		flag = 1; // LED�� ����ǵ��� FLAG�� 1�� ����
    	}
    	else if(IS_SW_PRESSED()==SW2) // ����ġ 2�� ���ȴٸ�,
    	{
    		flag = 0; // LED�� �ҵ�ǵ��� FLAG�� 0���� ���� 
    	}
    	
    	if(flag==1) // �÷��װ� ���̸�
    	{
    		LED_Control(ON,3); // LED ���� 
    	}
    	else
    	{
    		LED_Control(OFF,3); // LED �ҵ�
    	}
	}
    return 0;
}