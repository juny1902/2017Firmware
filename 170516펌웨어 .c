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

	char a[256];

    vinit(); // 장치를 초기화 하기 위한 외부 함수.
    GPIO_init();
    INIT_DEVICE(); // 장치를 초기화 하기 위한 함수 (GPIO 핀의 입출력 등을 정의)
    INIT_EDGE(); // 엣지 사용을 위한 설정 함수
    lcd_init();
    Clear_BaseFrame();
    INIT_UART();
    LED_Control(OFF,3);
    
    UART_TX_STRING(UART_RX_STRING()); // RX 추가구현 필요 
    
    while(1)
	{
	    for(i=0; i<400; i++)
	    {
	    	for(j=0; j<480; j++)
	    	{
	    		Put_PixelBaseFrame(i,j,makeColor(31,0,0));
	    	} 
	    }
	    for(i=400; i<800; i++)
	    {
	    	for(j=0; j<480; j++)
	    	{
	    		Put_PixelBaseFrame(i,j,makeColor(0,63,0));
	    	} 
	    }
	    for(i=270; i<540; i++)
	    {
	    	for(j=0; j<480; j++)
	    	{
	    		Put_PixelBaseFrame(i,j,makeColor(0,0,31));
	    	} 
	    }
    }
    
    return 0;
}