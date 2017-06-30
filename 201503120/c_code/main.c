#include "config.h" 
#include "stddefs.h"
#include "pxa2xx.h"
#include "16c552.h"
#include "typedef.h"
#include "except.h"
#include "user.h" // ��ġ ���� ���� ����� ���
#include "numbers.h" // ���� ��Ʈ ��� (numbers[10][32])
#include "lcd.h" // LCD ���� ����� ���
void usr_handle_pjy(unsigned long a)
{

}
void usr_timer_pjy(unsigned long a)
{
}
int main(void)
{
	vinit(); // ��ġ �ʱ�ȭ�� ����
	GPIO_init(); // GPIO �� �ʱ⼳���� ����
	lcd_init(); // LCD �ʱ�ȭ�� ���� 
	INIT_INTR();
	INIT_DEVICE();
	INIT_EDGE();
	Clear_BaseFrame(); // Baseframe Ŭ����
	
	
	DrawRectangle(200,200,100,100,0);
	DrawCircleFilled(200+50,200+50,50,makeColor(31,0,0));
	DrawCircle(200+50,200+50,30,makeColor(0,0,31));
	DrawCircle(200+50,200+50,15,makeColor(0,0,31));
	DrawCircle(200+50,200+50,10,makeColor(0,0,31));
}