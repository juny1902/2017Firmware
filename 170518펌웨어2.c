#include "config.h" 
#include "stddefs.h"
#include "pxa2xx.h"
#include "16c552.h"
#include "typedef.h"
#include "except.h"
#include "user.h" // 직접 지정한 함수 및 매크로를 불러오기 위해 user.h 헤더 포함.
#include "lcd.h" // lcd header
#include "uart.h"

// Global Variable
unsigned char Flag = 0;
int i,j;
extern void GPIO_init(void);
int main()
{

	// char a[256];

    vinit(); // 장치를 초기화 하기 위한 외부 함수.
    GPIO_init();
    INIT_DEVICE(); // 장치를 초기화 하기 위한 함수 (GPIO 핀의 입출력 등을 정의)
    INIT_EDGE(); // 엣지 사용을 위한 설정 함수
    lcd_init();
    Clear_BaseFrame();
    INIT_UART();
    LED_Control(OFF,3);
    UART_TX_STRING("INPUT AWAIT (R,G,B)");
    
    
    while(1)
	{
	    // 1 : 그라데이션 (왼쪽 빨강 , 오른쪽 파랑)
	    // 2 : 그라데이션 (왼쪽 빨강 , 오른쪽 파랑, 초록은 상하 그라데이션) 
	    for(i=0; i<400; i++)
	    {
	    	for(j=0; j<240; j++)
	    	{
	    		Put_PixelBaseFrame(i,j,makeColor(31-(i/13),63-(j/4),0)); // 13 이 나온 이유 ? : 가로 크기 400 / 31 색 
	    	}
	    	for(j=240; j<480; j++)
	    	{
	    		Put_PixelBaseFrame(i,j,makeColor(31-(i/13),63-(480-j)/4,0)); // 13 이 나온 이유 ? : 가로 크기 400 / 31 색 
	    	} 
	    }
	   	for(i=400; i<800; i++)
	   	{
	    	for(j=0; j<240; j++)
	    	{
	    		Put_PixelBaseFrame(i,j,makeColor(0,63-(j/4),31-((800-i)/13)));
	    	}
	    	for(j=240; j<480; j++)
	    	{
	    		Put_PixelBaseFrame(i,j,makeColor(0,63-(480-j)/4,31-((800-i)/13)));
	    	}
	    }
    }
    
    return 0;
}