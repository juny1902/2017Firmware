#include "config.h" 
#include "stddefs.h"
#include "pxa2xx.h"
#include "16c552.h"
#include "typedef.h"
#include "except.h"
#include "user.h" // 장치 제어 관련 사용자 헤더
#include "numbers.h" // 숫자 폰트 어레이 (numbers[10][32])
#include "lcd.h" // LCD 관련 사용자 헤더
void usr_handle_pjy(unsigned long a)
{

}
void usr_timer_pjy(unsigned long a)
{
}
int main(void)
{
	vinit(); // 장치 초기화를 위함
	GPIO_init(); // GPIO 핀 초기설정을 위함
	lcd_init(); // LCD 초기화를 위함 
	INIT_INTR();
	INIT_DEVICE();
	INIT_EDGE();
	Clear_BaseFrame(); // Baseframe 클리어
	
	
	DrawRectangle(200,200,100,100,0);
	DrawCircleFilled(200+50,200+50,50,makeColor(31,0,0));
	DrawCircle(200+50,200+50,30,makeColor(0,0,31));
	DrawCircle(200+50,200+50,15,makeColor(0,0,31));
	DrawCircle(200+50,200+50,10,makeColor(0,0,31));
}