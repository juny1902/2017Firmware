#include "config.h" 
#include "stddefs.h"
#include "pxa2xx.h"
#include "16c552.h"
#include "typedef.h"
#include "except.h"
#include "user.h" // ���� ������ �Լ� �� ��ũ�θ� �ҷ����� ���� user.h ��� ����.
#include "lcd.h" // lcd header
#include "uart.h"

// Global Variable
unsigned char Flag = 0;
int i,j;
extern void GPIO_init(void);
int main()
{

	// char a[256];

    vinit(); // ��ġ�� �ʱ�ȭ �ϱ� ���� �ܺ� �Լ�.
    GPIO_init();
    INIT_DEVICE(); // ��ġ�� �ʱ�ȭ �ϱ� ���� �Լ� (GPIO ���� ����� ���� ����)
    INIT_EDGE(); // ���� ����� ���� ���� �Լ�
    lcd_init();
    Clear_BaseFrame();
    INIT_UART();
    LED_Control(OFF,3);
    UART_TX_STRING("INPUT AWAIT (R,G,B)");
    
    
    while(1)
	{
	    // 1 : �׶��̼� (���� ���� , ������ �Ķ�)
	    // 2 : �׶��̼� (���� ���� , ������ �Ķ�, �ʷ��� ���� �׶��̼�) 
	    for(i=0; i<400; i++)
	    {
	    	for(j=0; j<240; j++)
	    	{
	    		Put_PixelBaseFrame(i,j,makeColor(31-(i/13),63-(j/4),0)); // 13 �� ���� ���� ? : ���� ũ�� 400 / 31 �� 
	    	}
	    	for(j=240; j<480; j++)
	    	{
	    		Put_PixelBaseFrame(i,j,makeColor(31-(i/13),63-(480-j)/4,0)); // 13 �� ���� ���� ? : ���� ũ�� 400 / 31 �� 
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