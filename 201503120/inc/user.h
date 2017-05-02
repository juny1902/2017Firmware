// 201503120 Jun Young Park
// 170501 - Midterm Exam

// Definition of GPIO Registers
#define GPDR1 (*(volatile int *)0x40e00010) // General Purpose Direction Register 1 (GPIO52)
#define GPCR1 (*(volatile int *)0x40e00028) // GP Clear 1
#define GPSR1 (*(volatile int *)0x40e0001c) // GP Set 1
#define GPDR2 (*(volatile int *)0x40e00014) // GP Direction 2 (GPIO82)
#define GPCR2 (*(volatile int *)0x40e0002c) // GP Clear 2
#define GPSR2 (*(volatile int *)0x40e00020) // GP Set 2

#define GPLR1 (*(volatile int *)0x40e00004) // GP Load 1 (GPIO53)
#define GPLR2 (*(volatile int *)0x40e00008) // GP Load 2 (GPIO83)

#define CCCR (*(volatile int *)0x41300000) 
#define MDREFR (*(volatile int *)0x048000004)

#define GEDR1 (*(volatile int *)0x40e0004c) // Edge Detect Register
#define GEDR2 (*(volatile int *)0x40E00050)
#define GRER1 (*(volatile int *)0x40e00034) // Rising Edge Enable Register
#define GRER2 (*(volatile int *)0x40E00038)
#define GFER1 (*(volatile int *)0x40e00040) // Falling Edge Enable Register
#define GFER2 (*(volatile int *)0x40e00044)

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
#define SW1_STAT (!((GPLR1) & (0x00200000))) // To check SW1 status. (Pressed = 1, Released = 0)
#define SW2_STAT (!((GPLR2) & (0x00080000))) // To check SW2 status. 

// Definition of getting from GEDR registers.
#define GET_EDGE_SW1 ((GEDR1) & (0x00200000))
#define GET_EDGE_SW2 ((GEDR2) & (0x00080000))

// Difinition of Intrrupt Registers

#define ICLR (*(volatile int *)0x40D00008)
#define ICCR (*(volatile int *)0x40D00014)
#define ICMR (*(volatile int *)0x40D00004)

// External functions
extern void vinit(void); // To initialize device

// Definition of functions
int IS_SW_PRESSED(void); // Return integer value by SW
int LED_Control(int CTL,int N); // LED control(N = #LED, CTL = Control)
void INIT_DEVICE(void); // Initialize device (Set Direction, LED Initialize)
void Set_Clock(int n); // Set clock frequency ( Range : 2~6 )
void INIT_EDGE(void);
void INIT_INTR(void);
void CLEAR_GEDR(void); // Set 1 on GEDR Bit to clear previous GEDR value.