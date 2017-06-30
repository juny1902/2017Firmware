#include "config.h" 
#include "stddefs.h"
#include "pxa2xx.h"
#include "16c552.h"
#include "typedef.h"
#include "except.h"
#include "user.h" // ���� ������ �Լ� �� ��ũ�θ� �ҷ����� ���� user.h ��� ����.
int wait=148000000; // ��ٸ��� ���� ī��Ʈ �ٿ�.
int flag = 0;
int t = 0;
char memory[1000000];
void usr_handle_pjy(unsigned long a) // Interrupt Service Routine �� ����
{	
		if(SW0_STAT && SW1_STAT) // �� ����ġ�� ��������
		{
			memory[t] = 3; // �ش� �ð���ġ�� �޸𸮿� 3 ���
		}
		else if(SW0_STAT)
		{
			memory[t] = 1; // �ش� �ð���ġ�� �޸𸮿� 1 ���
		}
		else if(SW1_STAT)
		{
			memory[t] = 2; // �ش� �ð���ġ�� �޸𸮿� 2 ��� 
		}
		t++;

	wait = 148000000; // �Է��� ������ ���ð� �ʱ�ȭ (�� 2��)
	CLEAR_GEDR(); // ���� ������ �ޱ����� �������� Ŭ���� 
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
    	if(wait && i<1000000) // ���ð��� �����ְ� �Է¹��� ������ ���� �������� ������� 
    	{
    		wait--; // ���ð� ī��Ʈ�ٿ�
    	}
    	else // ���ð� ���� Ȥ�� �޸� ���� �ʰ���
    	{
    		while(t) // t ȸ��ŭ �ݺ� 
    		{
    			if(memory[t] == 1) // �޸� �迭�� ��Ͽ� ���� 1�̸�
    			{
    				LED_Control(ON,1); // LED 1 ����
    				LED_Control(OFF,2);
    			}
    			else if(memory[t] == 2) // 2�̸�
    			{
    				LED_Control(ON,2); // LED 2 ����
    				LED_Control(OFF,1);
    			}
    			else if(memory[t] == 3) // 3�̸�
    			{
    				LED_Control(ON,3); // ���� LED ����
    			}
    			t--; // �ð� �ε��� �ϳ��� ���� 
    			wait = 148000000;
    		}
    	}
    	LED_Control(OFF,3);
    }    
    return 0;
}