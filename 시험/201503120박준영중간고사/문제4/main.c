#include "config.h" 
#include "stddefs.h"
#include "pxa2xx.h"
#include "16c552.h"
#include "typedef.h"
#include "except.h"
#include "user.h" // ���� ������ �Լ� �� ��ũ�θ� �ҷ����� ���� user.h ��� ����.
void usr_handle_pjy(unsigned long a) // Interrupt Service Routine �� ����
{
}
int main()
{
	int j = 0;
	int flag = 0;
    vinit(); // ��ġ�� �ʱ�ȭ �ϱ� ���� �ܺ� �Լ�.
    INIT_DEVICE(); // ��ġ�� �ʱ�ȭ �ϱ� ���� �Լ� (GPIO ���� ����� ���� ����)
    INIT_EDGE(); // ���� ����� ���� ���� �Լ�
    INIT_INTR();
    LED_Control(OFF,3);
    while(1) // �� ����
    {
    	if(flag==1)
    	{
    		LED_Control(3,ON);
    		_delay_ms(2000);
    		flag = 0;
    	}
    	LED_Control(1,OFF);
	    _delay_ms(1000);
	    	
	    LED_Control(1,ON);
		_delay_ms(1000);
	}
    return 0;
}