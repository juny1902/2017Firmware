#define	LCCR0	(*(volatile unsigned long *) (0x44000000))
#define LCCR1	(*(volatile unsigned long *) (0x44000004))
#define LCCR2	(*(volatile unsigned long *) (0x44000008))
#define LCCR3	(*(volatile unsigned long *) (0x4400000c))
#define FDADR0	(*(volatile unsigned long *) (0x44000200))

// Set resolution 800x480
#define XRES	800 
#define	YRES	480


#define	BPP	16
#define	FRAME_BUFFERSIZE	(XRES*YRES*BPP/8)

#define	FRAME_DESCRIPTOR	0xa2600000 // 프레임의 주소 지정
#define	FRAME_BUFFER		(FRAME_DESCRIPTOR+0x20) // 31을 더한 값을 0,0 으로 지정 (포맷)

struct pxafb_dma_descriptor{
	unsigned int fdadr;
	unsigned int fsadr;
	unsigned int fidr;
	unsigned int ldcmd;
};

//extern (void*) memset(void *str, int c, size_t n);
void Put_PixelBaseFrame(unsigned int x, unsigned int y, unsigned short color); // To print each pixel of the image.
void DrawRectangle(unsigned int offset_x,unsigned int offset_y,unsigned int size_x,unsigned int size_y,unsigned short color); // Draw x,y Rectangle
void DrawCircle(unsigned int offset_x,unsigned int offset_y,unsigned int radius, unsigned short color); // Draw Circle
void DrawCircleFilled(unsigned int offset_x,unsigned int offset_y,int radius, unsigned short color); // Draw filled circle
void lcd_init(void); // To initialze LCD Device
void Clear_BaseFrame(void); // To clear base frame
void PrintBMP(int offset_x,int offset_y,unsigned short * _myImage); // To print BMP file
void RotateImage(int offset_x,int offset_y,unsigned short * _myImage, short angle); // To rotate the image.
unsigned short makeColor(unsigned char r, unsigned char g,unsigned char b); // To make color (r < 32, g < 64, b <32)
void PrintTextScaled(unsigned int x, unsigned int y, int MUL, unsigned int *_myFont, unsigned short _color); // To scale the image
void PrintText(unsigned int x, unsigned int y, unsigned int *_myFont, unsigned short _color); // To print small text.
void PrintTextU(unsigned int x, unsigned int y, unsigned int *_myFont, unsigned short _color); // To print underlined text.
void PrintTextB(unsigned int x, unsigned int y,unsigned int thick, unsigned int *_myFont, unsigned short _color); // To print bold text.
void PrintTextI(unsigned int x, unsigned int y, unsigned int *_myFont, unsigned short _color); // To print italic text