#include "config.h" 
#include "stddefs.h"
#include "pxa2xx.h"
#include "16c552.h"
#include "typedef.h"
#include "except.h"
#include "user.h" // 장치 제어 관련 사용자 헤더
#include "lcd.h" // LCD 관련 사용자 헤더
#include "rgb_output.h"
#include "font_output.h" // 폰트 헤더 (도트매트릭스 형태)
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
	vinit(); // 장치 초기화를 위함
	GPIO_init(); // GPIO 핀 초기설정을 위함
	lcd_init(); // LCD 초기화를 위함 
	INIT_INTR();
	// INIT_TIMER(); // LCD는 타이머와 함께 작동 불가
	INIT_DEVICE();
	INIT_EDGE();
	Clear_BaseFrame(); // Baseframe 클리어
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