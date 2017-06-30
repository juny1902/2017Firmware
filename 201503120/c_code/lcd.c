#include "lcd.h"
#include <stdio.h>
#include <string.h>
#include <math.h> // Rotate ����.

// ����� �̹��� �� ��Ʈ�� ũ�⸦ ������ ����.
#define _IMG_SIZE_X 50
#define _IMG_SIZE_Y 50
#define _FONT_SIZE_X 32
#define _FONT_SIZE_Y 32


unsigned short makeColor(unsigned char r, unsigned char g,unsigned char b) // R,G,B ���� �޾� �� ���� ����
{
	// RRRR RGGG GGGB BBBB - 565 Color Dimension.
	unsigned short color = (r << 11) | (g << 5) | (b << 0); // r<32, g<64, b<32 (BASE ������ -> RGB565)
	// OVERRAY ������ RGB555
	return color;
}
void lcd_init()
{
	volatile struct pxafb_dma_descriptor *fdadr0 = (void*)FRAME_DESCRIPTOR;
	fdadr0->fdadr = FRAME_DESCRIPTOR;
	fdadr0->fsadr = FRAME_BUFFER;
	fdadr0->fidr = 0;
	fdadr0->ldcmd = FRAME_BUFFERSIZE;
	FDADR0 = FRAME_DESCRIPTOR;
	
	LCCR0 = 0x023008f8;
	LCCR1 = 0x1313ec00 | 799;
	LCCR2 = 0x00004c00 | 479;
	LCCR3 = 0x00400001 | (4<<24);
	LCCR0 |= 1;

}
void Put_PixelBaseFrame(unsigned int x, unsigned int y, unsigned short color)
{
	// Baseframe ? : 3���� ���̾� �� �ϳ� ( (��) -> ���̽� -> �������� -> ��������) -> �������� 3�� �ִٰ� ����
	// �޸��� ������ �ٲٸ� ��ġ�� ����. (������ : ������ ũ���� �޸� �ּ��� ����)
	// Virtual Frame : ���� �������� �ƴ����� �̸� �ε��Ͽ� ��� ������ ó���� ���
	unsigned short *fb = (void*)FRAME_BUFFER; // Frame Buffer �� �ּ�
	unsigned int ofs;
	
	ofs = y*XRES; // x,y �� �ּ� ? y*x_max 
	fb[ofs +x] = color; // fb �� color ���� �Ҵ� (�迭�� ����)
	
}
void DrawRectangle(unsigned int offset_x,unsigned int offset_y,unsigned int size_x,unsigned int size_y,unsigned short color)
{	
	int i,j;
	for(i=0;i<size_y;i++){
	
		for(j=0;j<size_x;j++){
				
			Put_PixelBaseFrame(j+offset_x,i+offset_y,color); // i,j �� �׸� �ִ� ������ ȭ�鿡 ���
		}
	}
}
void DrawCircle(unsigned int offset_x,unsigned int offset_y,unsigned int radius, unsigned short color)
{
	double rad;
	int x,y,i;
	for(i=0; i<360; i++) // 2*PI[rad] = 360[deg]
	{
		rad = (double)i * 3.141592 / 180; // Conv DEG -> RAD
 		x = radius* sin(rad); // get x coordinate
 		y = radius * cos(rad); // get y coordinate
		Put_PixelBaseFrame(x+offset_x,y+offset_y,color);
	}
}
void DrawCircleFilled(unsigned int offset_x,unsigned int offset_y,int radius, unsigned short color)
{
	int x,y;
	for(y=(-1)*(radius); y<radius; y++) // -rad ~ +rad
	{
		for(x=(-1)*(radius); x<radius; x++) // -rad ~ +rad
		{
			if(x*x + y*y <= radius*radius)
			{
				Put_PixelBaseFrame(offset_x+x,y+offset_y,color);
			}
		}
	}
}
void PrintBMP(int offset_x,int offset_y,unsigned short * _myImage) // x,y ��ġ�� �̹��� ���
{
	int i,j,k=(_IMG_SIZE_X*_IMG_SIZE_Y); // �ʱ� �ε����� �� ���
	for(i=0;i<_IMG_SIZE_X;i++){
	
		for(j=0;j<_IMG_SIZE_Y;j++){
				
			Put_PixelBaseFrame(j+offset_x,i+offset_y,_myImage[k]); // i,j �� �׸� �ִ� ������ ȭ�鿡 ���
			k--;
			
		}
		
	}
}
unsigned short Get_PixelBaseFrame(unsigned int x, unsigned int y)
{
	// (x,y)�� ������ Pixel�� ������ �о���̴� �Լ�
	// ��ǥ : getpixel�� �̿��� copy&paste(gray)
	unsigned short *fb = (void*)FRAME_BUFFER;
	unsigned int ofs;
	
	ofs = y*XRES;
	
	return (unsigned short)fb[ofs +x];
}

void ConvertAndPrintToGray(int x,int y)
{
	// Gray Effect
	// outRed = 0.3 * Red
	// outGreen = 0.59 * Green
	// outBlue = 0.11 * Blue
	// Gray = outRed + outGreen + outBlue -> RGB��簪�� Gray���� ���Խ��� ����ϸ�ȴ�.
	int i,j,k=0;
	unsigned int gray = 0;
	unsigned int r,g,b;
	for(i=0;i<_IMG_SIZE_X;i++){
	
		for(j=0;j<_IMG_SIZE_Y;j++){
			
			r = (unsigned int)((Get_PixelBaseFrame(i,j)>>11) * 0.3); // �� �ȼ�(i,j)�� Ư�� ���� ������ �о� ���Ŀ� ���� ��ȯ��. 
			g = (unsigned int)(((Get_PixelBaseFrame(i,j)>>5)&0x3F) * 0.59);
			b = (unsigned int)(((Get_PixelBaseFrame(i,j)&(0x1F))) * 0.11);
			gray = r+g+b; // �� ������ ���� ��� ���Ѱ��� GRAY.
			
			Put_PixelBaseFrame(x+i,y+j,(unsigned short)((gray>>1)<<11 | gray<<5 | (gray>>1))); // ��ȯ�� GRAY ������ R,G,B ������ �Ҵ�.
			k++;
			
		}
		
	}
}
void ScaledImage(int offset_x,int offset_y,unsigned short *_myImage, short MUL)
{

	int i,j,a,b,k=(_IMG_SIZE_X*_IMG_SIZE_Y);
	for(i=0;i<_IMG_SIZE_X;i++){
	
		for(j=0;j<_IMG_SIZE_Y;j++){
			
			for(a=i*MUL; a<(i+1)*MUL;a++)
			{
				for(b=j*MUL; b<(j+1)*MUL;b++)
				{
					Put_PixelBaseFrame(b+offset_x,a+offset_y,_myImage[k]); // a,b �� �׸� �ִ� ������ ȭ�鿡 ���
				}
			}
			k--;	
		}	
	}
}
void RotateImage(int offset_x,int offset_y,unsigned short *_myImage, short angle) // 0~360������ �Է¹޵��� ��.
{
	// �� �ȼ��� ������ȯ�� ���Ͽ� 20��, 38�� ���� ȸ���� �����ϰ��� ��.
	int x, y;
    int orig_x, orig_y;
    int pixel;
    double pi = 3.141592;
    double radian = angle*pi/180.0; // math.h ���̺귯���� �ﰢ�Լ��� ������ �����Ƿ� deg->rad �� ��ȯ .
    double cc = cos(radian), ss = sin(-radian);
    double xcenter = (double)_IMG_SIZE_X/2.0, ycenter = (double)_IMG_SIZE_Y/2.0;
    for (y = 0; y < _IMG_SIZE_Y; y++)
    {
        for (x = 0; x < _IMG_SIZE_X; x++)
        {
            orig_x = (int)(xcenter + ((double)y - ycenter)*ss + ((double)x - xcenter)*cc); // �̵��� x �� ��ǥ�� ����
            orig_y = (int)(ycenter + ((double)y - ycenter)*cc - ((double)x - xcenter)*ss); // �̵��� y �� ��ǥ�� ����
            pixel = 0;
            if ((orig_y >= 0 && orig_y < _IMG_SIZE_Y) && (orig_x >= 0 && orig_x < _IMG_SIZE_X)) // ���� ������ ��ȯ�� ��ǥ�� ���� �̹����� �� ��Ʈ�� �׸�.
            {
            	pixel = _myImage[orig_y*_IMG_SIZE_X+orig_x];
            }
            else // ȸ�� �� ��� �������� �Ͼ�� (�����) �� ����.
            {
            	pixel = makeColor(31,63,31);
            }
            Put_PixelBaseFrame(y+offset_x,x+offset_y,pixel);
        }
    }
}
// Print Text
// 32*32 size Text Font
void PrintText(unsigned int x, unsigned int y, unsigned int *_myFont, unsigned short _color)
{ // �ؽ�Ʈ ��� 
	int i,j,k=0;
	for(i=0; i<_FONT_SIZE_X; i++){
		unsigned int _shift_bit = 1;
		for(j=0; j<_FONT_SIZE_Y; j++){
			if(_myFont[k] & _shift_bit){
				 Put_PixelBaseFrame(x+(_FONT_SIZE_X-j), y+(_FONT_SIZE_Y-i), _color);
			}
			_shift_bit = _shift_bit << 1;
		}
		k++;
	}
}
void PrintTextScaled(unsigned int x, unsigned int y, int MUL, unsigned int *_myFont, unsigned short _color)
{ // 'MUL' �� ũ���� �ؽ�Ʈ ��� 

	int i,j,a,b,k=0;

	for(i=0; i<_FONT_SIZE_X; i++){ // ��
	
		unsigned int _shift_bit = 1;
	
		for(j=0; j<_FONT_SIZE_Y; j++)
		{ // ��
		
			if(_myFont[k] & _shift_bit)
			{
				for(a=i*MUL;a<(i+1)*MUL;a++) // MUL���� �ؽ�Ʈ�� ����ϱ� ���� ���� �ε���*MUL + �ε��� ��ŭ�� ���� �ﵵ�� ��
					for(b=j*MUL;b<(j+1)*MUL;b++)
						Put_PixelBaseFrame(x+(_FONT_SIZE_X*MUL-b), y+(_FONT_SIZE_Y*MUL-a), _color);
			}
			_shift_bit = _shift_bit << 1;
		}
		
		k++;
		
	}

}
void PrintTextI(unsigned int x, unsigned int y, unsigned int *_myFont, unsigned short _color)
{ // Italic ü ��� 
	int i,j,k=0;
	for(i=0; i<_FONT_SIZE_X; i++)
	{
		unsigned int _shift_bit = 1;
		for(j=0; j<_FONT_SIZE_Y; j++)
		{
			if(_myFont[k] & _shift_bit)
			{
				Put_PixelBaseFrame(x+(_FONT_SIZE_X-j)+(i/2), y+(_FONT_SIZE_Y-i), _color); // �� �� �ε����� ���ݸ�ŭ x���� ���� �������� ����Ʈ �Ͽ� ���.
			}
			_shift_bit = _shift_bit << 1;
		}
		
		k++;
	}
}
void PrintTextU(unsigned int x, unsigned int y, unsigned int *_myFont, unsigned short _color)
{ // Underlined �ؽ�Ʈ ��� 

	int i,j,k=0;
	for(i=0; i<_FONT_SIZE_X; i++){
		unsigned int _shift_bit = 1;
		for(j=0; j<_FONT_SIZE_Y; j++){
			if(_myFont[k] & _shift_bit){
				 Put_PixelBaseFrame(x+(_FONT_SIZE_X-j), y+(_FONT_SIZE_Y-i), _color);
			}
			_shift_bit = _shift_bit << 1;
		}
		Put_PixelBaseFrame(x+i, y+_FONT_SIZE_Y, _color); // Draw Underline
		k++;
	}
}
void PrintTextB(unsigned int x, unsigned int y,unsigned int thick, unsigned int *_myFont, unsigned short _color)
{ // 'thick' �β��� ����ü �ؽ�Ʈ ��� 

	int i,j,m,k=0;
	for(i=0; i<_FONT_SIZE_X; i++){
		unsigned int _shift_bit = 1;
		for(j=0; j<_FONT_SIZE_Y; j++){
			if(_myFont[k] & _shift_bit){
				for(m=0;m<thick;m++) // ������ �β� ��ŭ 1�ȼ��� ���������� ��� 
				{
					Put_PixelBaseFrame(x+(_FONT_SIZE_X-j)+m, y+(_FONT_SIZE_Y-i), _color); // x �� �ε����� m �� ���� ��ġ
				}
			
			}
			_shift_bit = _shift_bit << 1;
		}
		k++;
	}
}
void LCD_TEST(void)
{
	int i,j;
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
// LCD Clear
void Clear_BaseFrame()
{

	memset(FRAME_BUFFER, 0xFFFFFFFF, FRAME_BUFFERSIZE*8);

}