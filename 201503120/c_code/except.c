/* 
 * except.c:
 *
 * This code handles exceptions that are caught by the exception
 * vectors installed by the monitor. These exception vectors look for
 * user-installed exception handlers and call them if found. Otherwise
 * they issue a software interrupt (trap, SWI) which engages the
 * monitor. In goes like this:
 *
 * by Nick Patavalis (npat@inaccessnetworks.com)
 *
 * General notice: 
 *   This code is part of a boot-monitor package
 *   developed as a generic base platform for embedded system designs.
 *   As such, it is likely to be distributed to various projects
 *   beyond the control of the original author.  Please notify the
 *   author of any enhancements made or bugs found so that all may
 *   benefit from the changes.  In addition, notification back to the
 *   author will allow the new user to pick up changes that may have
 *   been made by other users after this version of the code was
 *   distributed.
 *
 * Micromonitor Author: Ed Sutter
 *   email: esutter@lucent.com (home: lesutter@worldnet.att.net)
 *   phone: 908-582-2351 (home: 908-889-5161) 
 *
 * $Id: except.c,v 1.5 2001/05/25 03:48:35 npat Exp $ 
 */

#include "config.h"
#include "typedef.h"
#include "except.h"
#include "pxa2xx.h"

/***********************************************************************/

ulong   ExceptionAddr;

/***********************************************************************/
//extern u32 __vectorlist_start;
//extern u32 __vectorlist_end;
//extern void usr_handle_sw3(unsigned long a);
//extern void usr_timer(unsigned long a);

static isrp_t usr_handle_und_instr;
static isrp_t usr_handle_abt_prefetch;
static isrp_t usr_handle_abt_data;

static isrp_t irqtbl[32];

/***********************************************************************/

isrp_t
vecconnect (isrp_t f, int lev0, int lev1)
{
    isrp_t of = 0;

    switch (lev0) {
    case VEC_L0_UND:
        of = usr_handle_und_instr;
        usr_handle_und_instr = f;
        break;
    case VEC_L0_ABP:
        of = usr_handle_abt_prefetch;
        usr_handle_abt_prefetch = f;
        break;
    case VEC_L0_ABD:
        of = usr_handle_abt_data;
        usr_handle_abt_data = f;
        break;
    case VEC_L0_IRQ:
    case VEC_L0_FIQ:
        if (lev1 < 0 || lev1 > 31)
            break;
        of = irqtbl[lev1];
        irqtbl[lev1] = f;
        break;
    default:
        break;
    }

    return of;
}

#ifdef EXCEPTION_INCLUDE
/***********************************************************************/

void 
handle_software_interrupt (ulong swinum)
{
    volatile int i;

    switch (swinum) {
    case SWINUM_SHOWREGS:
        showregs();
        break;
    case SWINUM_EXCEPTION:
        monrestart(EXCEPTION);
        break;
    case SWINUM_BREAKPOINT:
        monrestart(BREAKPOINT);
        break;
    case SWINUM_APP_EXIT:
        monreset(APP_EXIT);
        break;
    case SWINUM_MONREBOOT:
    default:
        printf("Unrecognized SWI. Rebooting!\n");
        for(i=0; i<LoopsPerSecond; i++);
        monreboot(INITIALIZE);
        break;
    }
}

/***********************************************************************/

void
handle_undefined_instruction (ulong addr)
{
    if (usr_handle_und_instr) {
        (*usr_handle_und_instr)(addr);
    } else {
        ExceptionAddr = addr;
        SWI_EXCEPTION;
    }
}
    

/***********************************************************************/

void
handle_abort_prefetch (ulong addr)
{
    if (usr_handle_abt_prefetch) {
        (*usr_handle_abt_prefetch)(addr);
    } else {
        ExceptionAddr = addr;
        SWI_EXCEPTION;
    }
}

/***********************************************************************/

void
handle_abort_data (ulong addr)
{
    if (usr_handle_abt_data) {
        (*usr_handle_abt_data)(addr);
    } else {
        ExceptionAddr = addr;
        SWI_EXCEPTION;
    }
}

#endif
/***********************************************************************/

void
handle_irq (ulong addr)
{
#if 1	
    int i, untrapped = 0;   
    for (i=0 ; i < 32; i++)
        if ( (INT_REG(INT_ICFP) & (1L << i)) ) {
            if (irqtbl[i])
                (*irqtbl[i])(i);
            else
                untrapped = 1;
        }
    for (i=0 ; i < 32; i++)
        if ( (INT_REG(INT_ICIP) & (1L << i)) ) {
            if (irqtbl[i])
                (*irqtbl[i])(i);
            else
                untrapped = 1;
        }
    if ( untrapped ) {
        ExceptionAddr = addr;
        SWI_EXCEPTION;
    }
#else
    int i, untrapped = 0;   
    
    for (i=0 ; i < 32; i++)
        if ( (INT_REG(INT_ICIP) & (1L << i)) ) {
            call_funcs(i);
        }	
#endif        
}

#if 0
static void call_funcs(int level)
{
vectorlist_t *item;

	for(item = (vectorlist_t *)&__vectorlist_start; 
			item != (vectorlist_t *)&__vectorlist_end; item++) {
		if(item->magic != INIT_MAGIC) {	
			return;
		}
		
		if(item->level == level) {
			/* call function */
			item->callback();
		}
	}
}
#endif
/***********************************************************************/

void
vinit(void)
{
    int i;

    usr_handle_und_instr = 0;
    usr_handle_abt_prefetch = 0;
    usr_handle_abt_data = 0;

    for ( i=0; i < sizeof(irqtbl) / sizeof(*irqtbl); i++ ) {
        irqtbl[i] = 0;
    }
    
    //irqtbl[10] = usr_handle_sw3;
    //irqtbl[26] = usr_timer;
    
    return;
}

/***********************************************************************/
