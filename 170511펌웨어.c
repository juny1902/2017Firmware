#include "config.h" 
#include "stddefs.h"
#include "pxa2xx.h"
#include "16c552.h"
#include "typedef.h"
#include "except.h"
#include "user.h" // ���� ������ �Լ� �� ��ũ�θ� �ҷ����� ���� user.h ��� ����.
// Global Variable
unsigned char Flag = 0;
int i;
void usr_timer_pjy(unsigned long a)
{
	LED_Control(OFF,3);
	_delay_ms(1000);
	LED_Control(ON,3);
	_delay_ms(1000);
	RESET_TIMER();
}
void usr_handle_pjy(unsigned long a) // Interrupt Service Routine �� ����
{
	
}
int main()
{
    vinit(); // ��ġ�� �ʱ�ȭ �ϱ� ���� �ܺ� �Լ�.
    INIT_DEVICE(); // ��ġ�� �ʱ�ȭ �ϱ� ���� �Լ� (GPIO ���� ����� ���� ����)
    INIT_EDGE(); // ���� ����� ���� ���� �Լ�
    INIT_INTR();
    LED_Control(OFF,3);
    INIT_TIMER();
	while(1) // �� ����
    {
    	LED_Blink_ms(3,250,1);
	}
    return 0;
}