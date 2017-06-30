#include "uart.h"
#include <stdio.h>
#include <string.h>

char inputString[20];

void INIT_UART()
{
	int divisor;
	int d_high;
	int d_low;
	
	divisor = 14745600 / 16;
	divisor = divisor / 115200;
	d_low = divisor & 0x000000ff;
	d_high = divisor & 0x0000ff00;
	d_high = d_high >> 8;
	
	GPDR1 |= (3 << 8) | (8 << 4);
	GAFR1_L |= (10 << 16) | (9 << 12) | (5 << 8) | (5 << 4);
	
	FFLCR |= (1 << 7);
	FFDLL = d_low;
	FFDLH = d_high;
	
	FFLCR &= !(1 << 7);
	FFLCR |= (3 << 0);
	
	FFIER |= (1 << 6);
}
void UART_TX_CHAR(char c)
{
	while(!(FFLSR & 0x00000020));
	FFTHR = c;
}
char UART_RX_CHAR(void)
{
	char c;
	while(!(FFLSR & 0x00000001));
	c = FFRBR;
	return c;
}
void StrClear(char *str)
{
	int i;
	for(i=0; i<20; i++)
	{
		str[i] = 0;
	}
}

// _str = ":aaa" = char a[] = *(_str+i) = a
void UART_TX_STRING(char * _str){

	int i=0;
	while((*(_str+i)) != 0){
		UART_TX_CHAR(*(_str+i));
		i++;
	}

}

char * UART_RX_STRING(void){

	int i = 0;
	char buff[256] = {0,};
	
	for(i=0; i<256; i++){
	
		char RX_Byte = UART_RX_CHAR();
		
		if(RX_Byte == '\n'){
			buff[i] = 0;
			break;
		}
		else
			buff[i] = RX_Byte;
			
	}
	
	return buff;

}