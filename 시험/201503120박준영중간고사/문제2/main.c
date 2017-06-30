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
    vinit(); // ��ġ�� �ʱ�ȭ �ϱ� ���� �ܺ� �Լ�.
    INIT_DEVICE(); // ��ġ�� �ʱ�ȭ �ϱ� ���� �Լ� (GPIO ���� ����� ���� ����)
    INIT_EDGE(); // ���� ����� ���� ���� �Լ�
    while(1) // �� ����
    {
    	LED_Blink_ms(3,250,1); // ���� LED�� 250MS �������� �����δ�.
    	if(GET_EDGE_SW0) // GPIO53 �� Rising Edge�� �����ϸ� 
    	{
    		if(SW1_STAT) // ����ġ 1�� �����ִ��� ���θ� Ȯ���Ͽ�
    		{
    			LED_Control(ON,3); // ���������� LED�� 
    			_delay_ms(2000); // 2�ʰ� �����Ѵ�.
    		}
    		else
    		{
    			LED_Control(OFF,3); // �������� ������ LED��
    			_delay_ms(2000); // 2�ʰ� �ҵ��Ѵ�.
    		}
    	}
    	
    }    
    return 0;
}