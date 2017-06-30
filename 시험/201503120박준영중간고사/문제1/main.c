#include "config.h" 
#include "stddefs.h"
#include "pxa2xx.h"
#include "16c552.h"
#include "typedef.h"
#include "except.h"
#include "user.h" // ���� ������ �Լ� �� ��ũ�θ� �ҷ����� ���� user.h ��� ����.
int flag = 0;
void usr_handle_pjy(unsigned long a) // Interrupt Service Routine �� ����
{
	if(GET_EDGE_SW0) // ���ͷ�Ʈ ��ƾ���� SW0 �� Rising Edge �� �����Ǹ�
	{
		flag = 1; // �÷��׸� 1�� �������ش�.
	}
	CLEAR_GEDR(); // �ѹ� ���� �������� GEDR�� �������� �ʵ��� GEDR�� Ŭ���� ���ش�.
}
int main()
{
    vinit(); // ��ġ�� �ʱ�ȭ �ϱ� ���� �ܺ� �Լ�.
    INIT_DEVICE(); // ��ġ�� �ʱ�ȭ �ϱ� ���� �Լ� (GPIO ���� ����� ���� ����)
    INIT_EDGE(); // ���� ����� ���� ���� �Լ�
    // SW0 �� ������ ������ �����ϱ� ���� GPIO53�� Rising Edge ����.
    INIT_INTR(); // ���ͷ�Ʈ ����� ���� ���� �Լ�
    while(1) // �� ����
    {
    	LED_Blink_ms(3,250,1); // ���� LED�� 500MS �������� �����δ�.
    	if(flag == 1) // ���ͷ�Ʈ�� ���� �÷��װ� 1�� ���ϸ�
    	{
    		if(SW1_STAT) // ����ġ 1�� �����ִ��� ���θ� Ȯ���Ͽ�
    		{ 
    			LED_Control(ON,3); // ���������� LED�� 
    			_delay_ms(2000); // 2�ʰ� �����ϰ�
    			flag = 0; // �÷��׸� �ٽ� ������. 
    		}
    		else
    		{
    			LED_Control(OFF,3); // �������� ������ LED��
    			_delay_ms(2000); // 2�ʰ� �ҵ��ϰ�
    			flag = 0; // �÷��׸� �ٽ� ������.
    		}
    	}
    	
    }    
    return 0;
}