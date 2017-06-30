// Definition of GPIO Registers
#define GPDR1 (*(volatile int *)0x40e00010)
#define GPCR1 (*(volatile int *)0x40e00028) 
#define GPSR1 (*(volatile int *)0x40e0001c)
#define GPDR2 (*(volatile int *)0x40e00014)
#define GPCR2 (*(volatile int *)0x40e0002c)
#define GPSR2 (*(volatile int *)0x40e00020)
#define GPLR1 (*(volatile int *)0x40e00004)
#define GPLR2 (*(volatile int *)0x40e00008)

// Numeric definition for LED Control
#define BLK 2
#define ON 1
#define OFF 0

// Numeric definition for Switch level detection
#define BOTH 3
#define SW2 2
#define SW1 1
#define NP 0

// Definition of reading from GPLR registers. 
#define SW1_STAT (!((GPLR1) & (0x00200000)))
#define SW2_STAT (!((GPLR2) & (0x00080000)))

// Definition of functions
int IS_SW_PRESSED(void);
void LED_Control(int CTL,int N);
void INIT_DEVICE(void);