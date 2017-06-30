#include "400x4001.h"
#include "400x4002.h"
#include "player8080.h"

//	BaseFrame
#define LCCR0								(*(volatile unsigned long *)(0x44000000))
#define LCCR1								(*(volatile unsigned long *)(0x44000004))
#define LCCR2								(*(volatile unsigned long *)(0x44000008))
#define LCCR3								(*(volatile unsigned long *)(0x4400000c))
#define LCCR4								(*(volatile unsigned long *)(0x44000010))
#define FDADR0								(*(volatile unsigned long *)(0x44000200))

#define XRES								800
#define YRES								480
#define BPP									16
#define FRAME_BUFFERSIZE					XRES*YRES*BPP/8				
#define FRAME_DESCRIPTOR					0xa2600000
#define FRAME_BUFFER						(FRAME_DESCRIPTOR+0x20)				
#define FRAME_DESCRIPTOR1					0xa2700000
#define FRAME_BUFFER1						(FRAME_DESCRIPTOR1+0x20)				

//	OverLay2
#define XRES_Over2							80
#define YRES_Over2							80
#define XPOS_Over2							100
#define YPOS_Over2							100
#define BPP_Over2							16
#define FDADR2								(*(volatile unsigned long *)(0x44000220))
#define FRAME_BUFFERSIZE2					XRES_Over2*YRES_Over2*BPP_Over2/8					 
#define FRAME_DESCRIPTOR2					0xa2800000
#define FRAME_BUFFER2						(FRAME_DESCRIPTOR2+0x20)	
					
#define OVL2C1								(*(volatile unsigned long *)(0x44000070))
#define OVL2C2 								(*(volatile unsigned long *)(0x44000080))

#define FBR0								(*(volatile unsigned long *)(0x44000020))


volatile struct pxafb_dma_descriptor *fdadr0;
volatile struct pxafb_dma_descriptor *fdadr1;
volatile struct pxafb_dma_descriptor *fdadr2;

int input = 1;
int direction = 1;

struct pxafb_dma_descriptor {
	unsigned int	fdadr;
	unsigned int	fsadr;
	unsigned int	fidr;
	unsigned int	ldcmd;
};

void lcd_init(void)
{
	fdadr0 	= (void *)FRAME_DESCRIPTOR;
	fdadr1 	= (void *)FRAME_DESCRIPTOR1;
	fdadr2 	= (void *)FRAME_DESCRIPTOR2;
	
	fdadr0->fdadr 									= FRAME_DESCRIPTOR;
	fdadr0->fsadr 									= FRAME_BUFFER;
	fdadr0->fidr  									= 0;
	fdadr0->ldcmd 									= FRAME_BUFFERSIZE;
	
	fdadr1->fdadr									= FRAME_DESCRIPTOR1;
	fdadr1->fsadr									= FRAME_BUFFER1;
	fdadr1->fidr									= 0;
	fdadr1->ldcmd									= FRAME_BUFFERSIZE;
	
	fdadr2->fdadr									= FRAME_DESCRIPTOR2;
	fdadr2->fsadr									= FRAME_BUFFER2;
	fdadr2->fidr									= 0;
	fdadr2->ldcmd									= FRAME_BUFFERSIZE2;

	LCCR0 										= 0x023008f8;
	LCCR1 										= 0x1313ec00 | 799;
	LCCR2 										= 0x00004c00 | 479;
	LCCR3 										= 0x00400001 | (4<<24);// |(3<<30);
	
	
	OVL2C2										= (YPOS_Over2-1<<10) | XPOS_Over2-1;
	OVL2C1										= (1<<31) | (4<<20) | (YRES_Over2-1<<10) |XRES_Over2-1;

	
	FDADR0 										= FRAME_DESCRIPTOR;
	FDADR2										= FRAME_DESCRIPTOR2;

	LCCR0 |= 1;

}

void Put_PixelBaseFrame(unsigned int x, unsigned int y, unsigned short color)
{
	unsigned short *fb = (void *)FRAME_BUFFER;
	unsigned int ofs;
	
	ofs = y * XRES;
	
	fb[ofs + x] = color;
}

void Put_PixelBuffer(unsigned int x, unsigned int y, unsigned short color)
{
	unsigned short *fb = (void *)FRAME_BUFFER1;
	unsigned int ofs;
	
	ofs = y * XRES;
	
	fb[ofs + x] = color;
}

void Clear_Buffer(unsigned short color)
{
		unsigned short *fb = (void *)FRAME_BUFFER1;
	int i;
	
	for(i = 0; i < YRES * XRES; i++)
		fb[i] = color;
}


void Clear_BaseFrame(unsigned short color)
{
	unsigned short *fb = (void *)FRAME_BUFFER;
	int i;
	
	for(i = 0; i < YRES * XRES; i++)
		fb[i] = color;
}

/*void Put_PixelOverLay1(unsigned int x, unsigned int y, unsigned short color)
{
	unsigned short *fb = (void *)FRAME_BUFFER2;
	unsigned int ofs;
	
	ofs = y * XRES_Over;
	
	fb[ofs + x] = color;
}

void Clear_OverLay1(unsigned short color)
{
	unsigned short *fb = (void *)FRAME_BUFFER2;
	int i;
	
	for(i = 0; i < YRES_Over * XRES_Over; i++)
		fb[i] = color;
}*/

void Put_PixelOverLay2(unsigned int x, unsigned int y, unsigned short color)
{
	unsigned short *fb = (void *)FRAME_BUFFER2;
	unsigned int ofs;
	
	ofs = y * XRES_Over2;
	
	fb[ofs + x] = color;
}

void Clear_OverLay2(unsigned short color)
{
	unsigned short *fb = (void *)FRAME_BUFFER2;
	int i;
	
	for(i = 0; i < YRES_Over2 * XRES_Over2; i++)
		fb[i] = color;
}

void delay(int ms)
{
	int i ;
	for(i=0;i<100000*ms; i++);
}

void putBitmap()
{
	int i,j,k = 0;
	for(j=400-1;j>=0;j--){
    	for(i=0;i<400;i++){
    		Put_PixelBaseFrame(i,j,bitmap2[k]);
			Put_PixelBuffer(i,j,bitmap1[k]);
    		k++;
    	}
    }
}


void drawPlayer()
{
	int i,j,k = 0;

	for(j=80-1;j>0;j--)
	{
    	for(i=0;i<80;i++)
    	{
    		Put_PixelOverLay2(i,j,player[k]);
			k++;
    	}
    }  
}

// Direct Memory Access
// front -> BaseFrame | OverLay1 | OverLay2 
// 층간의 색이 서로 완전히 덮힐수도, 섞이게 할수도있다.(시간상 생략)
// Last Software, 오늘 나눠준것(this)은 시험에 나오지않는다.
// 기말고사
// Switch ,LED, LCD -> 단순입출력도구
// Interrupt 가 제일 중요하게 다뤄질것 (두개의 interrupt 동시에 사용 나옴 - 중복상황 Check)
// UART 안함

int main(void)
{

	vinit();
	GPIO_init();
	lcd_init();
	Clear_BaseFrame(0x0000);
	Clear_Buffer(0x0000);
	Clear_OverLay2(0x8000);
	putBitmap();
	drawPlayer();
	delay(10);	
	while(1)
	{
		FBR0 = (unsigned int)&fdadr1->fdadr|1;
		delay(10);		
		FBR0 = (unsigned int)&fdadr0->fdadr|1;
		delay(10);
	}
}
