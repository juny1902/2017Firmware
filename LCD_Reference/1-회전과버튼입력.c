#include "config.h" 
#include "stddefs.h"
#include "pxa2xx.h"
#include "16c552.h"
#include "typedef.h"
#include "except.h"
#include "user.h" // ��ġ ���� ���� ����� ���
#include "lcd.h" // LCD ���� ����� ���
#include "rgb_output.h"
#include "font_output.h" // ��Ʈ ��� (��Ʈ��Ʈ���� ����)
int flag=0;
void usr_handle_pjy(unsigned long a)
{
	if(GET_EDGE_SW0 && GET_EDGE_SW1)
	{
		flag = 3;
	}
	else if(GET_EDGE_SW1)
	{
		flag = 2;
	}
	else if(GET_EDGE_SW0)
	{
		flag = 1;
	}
	CLEAR_GEDR();
}
void usr_timer_pjy(unsigned long a)
{
}
int main(void)
{
	int angle = 0;
	vinit(); // ��ġ �ʱ�ȭ�� ����
	GPIO_init(); // GPIO �� �ʱ⼳���� ����
	lcd_init(); // LCD �ʱ�ȭ�� ���� 
	INIT_INTR();
	// INIT_TIMER(); // LCD�� Ÿ�̸ӿ� �Բ� �۵� �Ұ�
	INIT_DEVICE();
	INIT_EDGE();
	Clear_BaseFrame(); // Baseframe Ŭ����
	PrintBMP(400-50,200-50,myImage);
	
	while(1)
	{
		if(flag == 3)
		{
			angle = 0;
			PrintBMP(400-50,200-50,myImage);
			flag = 0;
		}
		else if(flag == 1)
		{
			angle -= 30;
			angle = angle%360;
			LED_Control(ON,1);
			RotateImage(400-50,200-50,myImage,angle);
			LED_Control(OFF,1);
			flag = 0;
		}
		else if(flag == 2)
		{
			angle += 30;
			angle = angle%360;
			LED_Control(ON,2);
			RotateImage(400-50,200-50,myImage,angle);
			LED_Control(OFF,2);
			flag = 0;
		}
	}
}