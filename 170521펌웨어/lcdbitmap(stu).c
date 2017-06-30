#include "rgb_output.h"


//lcd���� �������� ���� �ּ� �Ҵ� 
#define LCCR0 	(*(volatile unsigned long *) (0x44000000)) 
#define LCCR1 	(*(volatile unsigned long *) (0x44000004))
#define LCCR2 	(*(volatile unsigned long *) (0x44000008))
#define LCCR3 	(*(volatile unsigned long *) (0x4400000c))
#define FDADR0 	(*(volatile unsigned long *) (0x44000200))


#define XRES	800 //x ����
#define YRES	480 //y ���� 
#define BPP		16  //Bit per pixel
//Base Frame ����/// 
#define FRAME_BUFFERSIZE	XRES*YRES*BPP/8
#define FRAME_DESCRIPTOR 	0xa2600000
#define FRAME_BUFFER 		(FRAME_DESCRIPTOR+0x20) 

struct pxafb_dma_descriptor{
	unsigned int	fdadr;
	unsigned int 	fsadr;
	unsigned int	fidr;
	unsigned int	ldcmd;
};
///////////////////

void Put_PixelBaseFrame(unsigned int x, unsigned y, unsigned short color);
void lcd_init();
void Clear_BaseFrame();
void Draw_Bitmap(int x, int y, int imWidth , int imHeight);
//////////////////


// lcd ��� �ϱ� ���� �� ����  
void lcd_init(){

	volatile struct pxafb_dma_descriptor *fdadr0 = (void *)FRAME_DESCRIPTOR;
	fdadr0->fdadr = FRAME_DESCRIPTOR;
	fdadr0->fsadr = FRAME_BUFFER;
	fdadr0->fidr  = 0;
	fdadr0->ldcmd = FRAME_BUFFERSIZE;
	FDADR0		  = FRAME_DESCRIPTOR;
	
	LCCR0		  = 0x023008f8;
	LCCR1 		  = 0x1313ec00 | 799;
	LCCR2		  = 0x00004c00 | 479;
	LCCR3		  = 0x00400001 | (4<<24);
	LCCR0 		 |= 1;	
}

// �� ��� 
void Put_PixelBaseFrame(unsigned int x, unsigned y, unsigned short color)
{
	unsigned short *fb = (void*)FRAME_BUFFER;
	unsigned int ofs;
	
	ofs = y*XRES;
	fb[ofs +x] = color;
}
// ȭ�� ������� �ʱ�ȭ 
void Clear_BaseFrame()
{	
	memset(FRAME_BUFFER,0xFFFFFFFF,FRAME_BUFFERSIZE);
}

// drawBitmap 

void Draw_Bitmap(int x, int y, int imWidth , int imHeight)
{
	int i,j; 
	int k=0,c=0;

	for()
		for()	{
			Put_PixelBaseFrame(x+i,y+j,myImage[k]);
			
		}
	

}



int main(void)
{
	int x,y;
	volatile int k;
	vinit();
	GPIO_init();
	lcd_init();
	Clear_BaseFrame(); //clear lcd
	
	Draw_Bitmap(50,50,200,200);
}


