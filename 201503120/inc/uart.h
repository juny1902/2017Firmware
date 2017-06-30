#define GPDR1 (*(volatile int *)0x40e00010)
#define GAFR1_L (*(volatile int *)0x40e0005c)

#define FFTHR (*(volatile int *)0x40100000)
#define FFRBR (*(volatile int *)0x40100000)

#define FFDLL (*(volatile int *)0x40100000)
#define FFDLH (*(volatile int *)0x40100004)
#define FFIER (*(volatile int *)0x40100004)
#define FFLSR (*(volatile int *)0x40100014)
#define FFLCR (*(volatile int *)0x4010000C)

void INIT_UART(void);
void UART_TX_CHAR(char);
// void UART_TX_STRING(char *);
char UART_RX_CHAR(void);
// void UART_RX_STRING(void);

void StrClear(char *);
void UART_TX_STRING(char *);
char* UART_RX_STRING(void);