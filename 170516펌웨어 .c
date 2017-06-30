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

	char a[256];

    vinit(); // ��ġ�� �ʱ�ȭ �ϱ� ���� �ܺ� �Լ�.
    GPIO_init();
    INIT_DEVICE(); // ��ġ�� �ʱ�ȭ �ϱ� ���� �Լ� (GPIO ���� ����� ���� ����)
    INIT_EDGE(); // ���� ����� ���� ���� �Լ�
    lcd_init();
    Clear_BaseFrame();
    INIT_UART();
    LED_Control(OFF,3);
    
    UART_TX_STRING(UART_RX_STRING()); // RX �߰����� �ʿ� 
    
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