#include "lcd.h"
#include <stdio.h>
#include <string.h>
#include <math.h> // Rotate 관련.

// 사용할 이미지 및 폰트의 크기를 사전에 정함.
#define _IMG_SIZE_X 50
#define _IMG_SIZE_Y 50
#define _FONT_SIZE_X 32
#define _FONT_SIZE_Y 32


unsigned short makeColor(unsigned char r, unsigned char g,unsigned char b) // R,G,B 값을 받아 색 정보 생성
{
	// RRRR RGGG GGGB BBBB - 565 Color Dimension.
	unsigned short color = (r << 11) | (g << 5) | (b << 0); // r<32, g<64, b<32 (BASE 프레임 -> RGB565)
	// OVERRAY 에서는 RGB555
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
	// Baseframe ? : 3개의 레이어 중 하나 ( (눈) -> 베이스 -> 오버레이 -> 오버레이) -> 유리판이 3개 있다고 생각
	// 메모리의 번지를 바꾸며 위치를 지정. (프레임 : 정해진 크기의 메모리 주소의 집합)
	// Virtual Frame : 실제 프레임은 아니지만 미리 로드하여 고속 프레임 처리에 사용
	unsigned short *fb = (void*)FRAME_BUFFER; // Frame Buffer 의 주소
	unsigned int ofs;
	
	ofs = y*XRES; // x,y 의 주소 ? y*x_max 
	fb[ofs +x] = color; // fb 에 color 값을 할당 (배열로 생각)
	
}
void DrawRectangle(unsigned int offset_x,unsigned int offset_y,unsigned int size_x,unsigned int size_y,unsigned short color)
{	
	int i,j;
	for(i=0;i<size_y;i++){
	
		for(j=0;j<size_x;j++){
				
			Put_PixelBaseFrame(j+offset_x,i+offset_y,color); // i,j 각 항목에 있는 색상값을 화면에 출력
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
void PrintBMP(int offset_x,int offset_y,unsigned short * _myImage) // x,y 위치에 이미지 출력
{
	int i,j,k=(_IMG_SIZE_X*_IMG_SIZE_Y); // 초기 인덱스는 끝 요소
	for(i=0;i<_IMG_SIZE_X;i++){
	
		for(j=0;j<_IMG_SIZE_Y;j++){
				
			Put_PixelBaseFrame(j+offset_x,i+offset_y,_myImage[k]); // i,j 각 항목에 있는 색상값을 화면에 출력
			k--;
			
		}
		
	}
}
unsigned short Get_PixelBaseFrame(unsigned int x, unsigned int y)
{
	// (x,y)상에 존재한 Pixel의 색상을 읽어들이는 함수
	// 목표 : getpixel을 이용한 copy&paste(gray)
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
	// Gray = outRed + outGreen + outBlue -> RGB모든값에 Gray값을 대입시켜 출력하면된다.
	int i,j,k=0;
	unsigned int gray = 0;
	unsigned int r,g,b;
	for(i=0;i<_IMG_SIZE_X;i++){
	
		for(j=0;j<_IMG_SIZE_Y;j++){
			
			r = (unsigned int)((Get_PixelBaseFrame(i,j)>>11) * 0.3); // 한 픽셀(i,j)의 특정 색상 성분을 읽어 공식에 따라 변환함. 
			g = (unsigned int)(((Get_PixelBaseFrame(i,j)>>5)&0x3F) * 0.59);
			b = (unsigned int)(((Get_PixelBaseFrame(i,j)&(0x1F))) * 0.11);
			gray = r+g+b; // 각 성분의 값을 모두 합한값이 GRAY.
			
			Put_PixelBaseFrame(x+i,y+j,(unsigned short)((gray>>1)<<11 | gray<<5 | (gray>>1))); // 변환한 GRAY 성분을 R,G,B 각각에 할당.
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
					Put_PixelBaseFrame(b+offset_x,a+offset_y,_myImage[k]); // a,b 각 항목에 있는 색상값을 화면에 출력
				}
			}
			k--;	
		}	
	}
}
void RotateImage(int offset_x,int offset_y,unsigned short *_myImage, short angle) // 0~360도까지 입력받도록 함.
{
	// 각 픽셀의 선형변환을 통하여 20도, 38도 등의 회전을 수행하고자 함.
	int x, y;
    int orig_x, orig_y;
    int pixel;
    double pi = 3.141592;
    double radian = angle*pi/180.0; // math.h 라이브러리의 삼각함수는 라디안을 읽으므로 deg->rad 로 변환 .
    double cc = cos(radian), ss = sin(-radian);
    double xcenter = (double)_IMG_SIZE_X/2.0, ycenter = (double)_IMG_SIZE_Y/2.0;
    for (y = 0; y < _IMG_SIZE_Y; y++)
    {
        for (x = 0; x < _IMG_SIZE_X; x++)
        {
            orig_x = (int)(xcenter + ((double)y - ycenter)*ss + ((double)x - xcenter)*cc); // 이동될 x 축 좌표를 구함
            orig_y = (int)(ycenter + ((double)y - ycenter)*cc - ((double)x - xcenter)*ss); // 이동될 y 축 좌표를 구함
            pixel = 0;
            if ((orig_y >= 0 && orig_y < _IMG_SIZE_Y) && (orig_x >= 0 && orig_x < _IMG_SIZE_X)) // 범위 내에는 변환된 좌표에 원본 이미지의 각 도트를 그림.
            {
            	pixel = _myImage[orig_y*_IMG_SIZE_X+orig_x];
            }
            else // 회전 후 비는 공간에는 하얀색 (전경색) 을 씌움.
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
{ // 텍스트 출력 
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
{ // 'MUL' 배 크기의 텍스트 출력 

	int i,j,a,b,k=0;

	for(i=0; i<_FONT_SIZE_X; i++){ // 행
	
		unsigned int _shift_bit = 1;
	
		for(j=0; j<_FONT_SIZE_Y; j++)
		{ // 열
		
			if(_myFont[k] & _shift_bit)
			{
				for(a=i*MUL;a<(i+1)*MUL;a++) // MUL배의 텍스트를 출력하기 위해 현재 인덱스*MUL + 인덱스 만큼의 점을 찍도록 함
					for(b=j*MUL;b<(j+1)*MUL;b++)
						Put_PixelBaseFrame(x+(_FONT_SIZE_X*MUL-b), y+(_FONT_SIZE_Y*MUL-a), _color);
			}
			_shift_bit = _shift_bit << 1;
		}
		
		k++;
		
	}

}
void PrintTextI(unsigned int x, unsigned int y, unsigned int *_myFont, unsigned short _color)
{ // Italic 체 출력 
	int i,j,k=0;
	for(i=0; i<_FONT_SIZE_X; i++)
	{
		unsigned int _shift_bit = 1;
		for(j=0; j<_FONT_SIZE_Y; j++)
		{
			if(_myFont[k] & _shift_bit)
			{
				Put_PixelBaseFrame(x+(_FONT_SIZE_X-j)+(i/2), y+(_FONT_SIZE_Y-i), _color); // 각 열 인덱스의 절반만큼 x축의 양의 방향으로 쉬프트 하여 출력.
			}
			_shift_bit = _shift_bit << 1;
		}
		
		k++;
	}
}
void PrintTextU(unsigned int x, unsigned int y, unsigned int *_myFont, unsigned short _color)
{ // Underlined 텍스트 출력 

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
{ // 'thick' 두께의 볼드체 텍스트 출력 

	int i,j,m,k=0;
	for(i=0; i<_FONT_SIZE_X; i++){
		unsigned int _shift_bit = 1;
		for(j=0; j<_FONT_SIZE_Y; j++){
			if(_myFont[k] & _shift_bit){
				for(m=0;m<thick;m++) // 설정한 두께 만큼 1픽셀씩 오른쪽으로 출력 
				{
					Put_PixelBaseFrame(x+(_FONT_SIZE_X-j)+m, y+(_FONT_SIZE_Y-i), _color); // x 의 인덱스에 m 을 더한 위치
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
// LCD Clear
void Clear_BaseFrame()
{

	memset(FRAME_BUFFER, 0xFFFFFFFF, FRAME_BUFFERSIZE*8);

}