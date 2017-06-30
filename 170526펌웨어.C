//#include "rgb_output.h"
#include "lcd.h"
#include "a.h"
#include "b.h"

/*
void Draw_Bitmap(int x, int y, int imWidth , int imHeight)
{
	int i,j; 
	int k=0,c=0;

	for(i=0;i<imWidth;i++)
		for(j=0;j<imHeight;j++)	{
			Put_PixelBaseFrame(x+j,y+i,myImage[k]&0x07FF);
			k++;
		}
	

}
*/


int main(void)
{
	int x,y;
	volatile int k;
	vinit();
	GPIO_init();
	lcd_init();
	Clear_BaseFrame(); //clear lcd
	
	{
	int x=50;
	int y=50;
	int i,j; 
	int k=0,c=0;

	for(i=0;i<200;i++)
		for(j=0;j<200;j++)	{
		
			// 0x001F
			if(myAImage[k] == 0x1F) // 이미지 A에서 Key 값(blue) 를 찾으면 그부분에 B 출력
				Put_PixelBaseFrame(x+i,y+j,myBImage[k]);
			else
				Put_PixelBaseFrame(x+i,y+j,myAImage[k]); // Key 값이 아니라면 기존 이미지 A 출력.
				
			k++;
		}
	

	}
	
	/*
	{
	int x=50;
	int y=50;
	int i,j; 
	int k=0,c=0;

	for(i=0;i<imWidth;i++)
		for(j=0;j<imHeight;j++)	{
			Put_PixelBaseFrame(x+j,y+i,myAImage[k]);
			k++;
		}
	

	}*/
	
}


