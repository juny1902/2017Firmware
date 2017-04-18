/*
 * except.h
 *
 * High-level exception handling
 *
 * by Nick Patavalis (npat@inaccessnetworks.com)
 *
 * $Id: except.h,v 1.1 2001/05/25 17:51:44 npat Exp $
 */

/***********************************************************************/

#ifndef EXCEPT_H
#define EXCEPT_H

/***********************************************************************/

#define SWINUM_EXCEPTION 0x0000001
//#define SWI_EXCEPTION __asm("swi 0x0000001")
#define SWI_EXCEPTION __asm{swi 0x0000001}


#define SWINUM_BREAKPOINT 0x0000002
#define SWI_BREAKPOINT __asm("swi 0x0000002")

#define SWINUM_MONREBOOT 0x0000003
#define SWI_MONREBOOT __asm("swi 0x0000003")

#define SWINUM_SHOWREGS 0x0000004
#define SWI_SHOWREGS __asm("swi 0x0000004")

#define SWINUM_APP_EXIT 0x0000005
#define SWI_APP_EXIT __asm("swi 0x0000005")

/***********************************************************************/

#define VEC_L0_RST              0
#define VEC_L0_UND              1
#define VEC_L0_SWI              2
#define VEC_L0_ABP              3
#define VEC_L0_ABD              4
#define VEC_L0_IRQ              5
#define VEC_L0_RESERVED         6
#define VEC_L0_FIQ              7

#define VEC_L1_IRQ_IO0          0
#define VEC_L1_IRQ_IO1          1
#define VEC_L1_IRQ_IO2          2
#define VEC_L1_IRQ_IO3          3
#define VEC_L1_IRQ_IO4          4
#define VEC_L1_IRQ_IO5          5
#define VEC_L1_IRQ_IO6          6
#define VEC_L1_IRQ_IO7          7
#define VEC_L1_IRQ_IO8          8
#define VEC_L1_IRQ_IO9          9
#define VEC_L1_IRQ_IO11_27      10
#define VEC_L1_IRQ_IOHI         11
#define VEC_L1_IRQ_LCD          12
#define VEC_L1_IRQ_SER0         13
#define VEC_L1_IRQ_RESERVED     14
#define VEC_L1_IRQ_SER1B        15
#define VEC_L1_IRQ_SER2         16
#define VEC_L1_IRQ_SER3         17
#define VEC_L1_IRQ_SER4A        18
#define VEC_L1_IRQ_SER4B        19
#define VEC_L1_IRQ_DMA0         20
#define VEC_L1_IRQ_DMA1         21
#define VEC_L1_IRQ_DMA2         22
#define VEC_L1_IRQ_DMA3         23
#define VEC_L1_IRQ_DMA4         24
#define VEC_L1_IRQ_DMA5         25
#define VEC_L1_IRQ_OST0         26
#define VEC_L1_IRQ_OST1         27
#define VEC_L1_IRQ_OST2         28
#define VEC_L1_IRQ_OST3         29
#define VEC_L1_IRQ_1HZ          30
#define VEC_L1_IRQ_RTC          31


#define base_addr 0xA4000000
//#define irqtbl(_x_) *(unsigned *)( base_addr + _x_)

#define INT_TIMER0 *(unsigned *)(base_addr + 0x68)
#define INT_TIMER2 *(unsigned *)(base_addr + 0x70)

//irqtbl EQU 0xA40000000

//#define int_timer0 0x68
/***********************************************************************/

typedef void (*isrp_t)(unsigned long a);

extern isrp_t vecconnect (isrp_t f, int lev0, int lev1);

/***********************************************************************/

#define INIT_MAGIC (0x496e6974)		/* "Init" */
#define EXIT_MAGIC (0x45786974)		/* "Exit" */


typedef void(*initfunc_t)(void);


typedef struct {
	u32 magic;
	initfunc_t callback;
	int level;
} vectorlist_t;

#define __irq_vector __attribute__((unused, __section__(".irq_vector")))

#define __irq_vector_set(fn, lvl) \
static vectorlist_t __init_##fn __irq_vector = { \
	magic:    INIT_MAGIC, \
	callback: fn, \
	level:	  lvl }
	
#endif /* of EXCEPT_H */
