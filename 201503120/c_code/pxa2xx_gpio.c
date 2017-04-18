//==========================================================================
//
// pxa255_gpio.c
//
//
// Author(s):    Michael Kelly, Cogent Computer Systems, Inc.
// Contributors: 
// Date:         02/05/2002
// Description:  This file contains code to intialize the PXA250 GPIO
//               section as well as set, clear and test functions
//               for manipulating the GPIO bits
//
//--------------------------------------------------------------------------

#include "config.h"
#include "stddefs.h"
#include "pxa2xx.h"
#include "typedef.h"   // Function Prototypes
#include "pxa2xx_gpio.h"

void GPIO_init(void);
int GPIO_set(int);
int GPIO_clr(int);
int GPIO_tst(int);
int GPIO_in(int);
int GPIO_out(int);


void pxa_gpio_mode (int gpio_mode)
{
	int gpio = gpio_mode & GPIO_MD_MASK_NR;
	int fn = (gpio_mode & GPIO_MD_MASK_FN) >> 8;
	int gafr;

	if (gpio_mode & GPIO_DFLT_LOW)
		rGPCR(gpio) = GPIO_bit(gpio);
	else if (gpio_mode & GPIO_DFLT_HIGH)
		rGPSR(gpio) = GPIO_bit(gpio);
	if (gpio_mode & GPIO_MD_MASK_DIR)
		rGPDR(gpio) |= GPIO_bit(gpio);
	else
		rGPDR(gpio) &= ~GPIO_bit(gpio);
	gafr = rGAFR(gpio) & ~(0x3 << (((gpio) & 0xf)*2));
	rGAFR(gpio) = gafr |  (fn  << (((gpio) & 0xf)*2));
}

//--------------------------------------------------------
// GPIO_init()
//
// This function sets the startup state for the PXA250
// as used on the CSB226
//

void
GPIO_init()
{

	// First set the output values to a safe/disabled state before we change any GPIO's to outputs
	// start by setting all of them high which is the safest for most signals
	GPIO_REG(GPIO_GPSR0) = 0xffffffff;
	GPIO_REG(GPIO_GPSR1) = 0xffffffff;
	GPIO_REG(GPIO_GPSR2) = 0xffffffff;

	// Next, set the correct direction for our functions.  A one means output.
	GPIO_REG(GPIO_GPDR0) = 0xc3828000;
	GPIO_REG(GPIO_GPDR1) = 0xfcdfab83;
	GPIO_REG(GPIO_GPDR2) = 0x02e5ffff;

	// Finally, set the alternate function registers to the correct state
	GPIO_REG(GPIO_GAFR0L) = 0x80000000;
	GPIO_REG(GPIO_GAFR0U) = 0xa51a8010;
	GPIO_REG(GPIO_GAFR1L) = 0x699a955a;
	GPIO_REG(GPIO_GAFR1U) = 0xaaa5a0aa;
	GPIO_REG(GPIO_GAFR2L) = 0xaaaaaaaa;
	GPIO_REG(GPIO_GAFR2U) = 0x01090402;
	GPIO_REG(GPIO_GAFR3L) = 0x54000000;
	GPIO_REG(GPIO_GAFR3U) = 0x00001409;

	// finally, clear the RDH bit (by writing 1 to it) in the PSSR to enable GPIO inputs
	PWR_REG(PWR_PSSR) = 0x20;
}

//--------------------------------------------------------
// GPIO_set()
//
// This function sets the desired bit passed in.  It first 
// tests to see if the bit is an actual output.  If not,
// it returns a -1, otherwise it returns 0.  NOTE: We do not
// test to see if setting the bit would screw up any alternate
// functions.  Use this function with caution!
//

int GPIO_set(int gpio_bit)
{
	// quick sanity test
	if (gpio_bit > 120) return -1;

	// First find out which group the bit belongs to
	if (gpio_bit < 32)
	{
		// Get the direction and see if it's an output
		if (!(GPIO_REG(GPIO_GPDR0) & (1 << gpio_bit)))
			return -1;

		// if yes, then set it
		GPIO_REG(GPIO_GPSR0) = (1 << gpio_bit);
	}
	else if (gpio_bit < 64)
	{
		// Get the direction and see if it's an output
		if (!(GPIO_REG(GPIO_GPDR1) & (1 << (gpio_bit - 32))))
			return -1;

		// if yes, then set it
		GPIO_REG(GPIO_GPSR1) = (1 << (gpio_bit - 32));
	}
	else
	{
		// Get the direction and see if it's an output
		if (!(GPIO_REG(GPIO_GPDR2) & (1 << (gpio_bit - 64))))
			return -1;

		// if yes, then set it
		GPIO_REG(GPIO_GPSR2) = (1 << (gpio_bit - 64));
	}
	return 0;
}

//--------------------------------------------------------
// GPIO_clr()
//
// This function clears the desired bit passed in.  It first 
// tests to see if the bit is an actual output.  If not,
// it returns a -1, otherwise it returns 0.  NOTE: We do not
// test to see if clearing the bit would screw up any alternate
// functions.  Use this function with caution!
//

int GPIO_clr(int gpio_bit)
{
	// quick sanity test
	if (gpio_bit > 120) return -1;

	// First find out which group the bit belongs to
	if (gpio_bit < 32)
	{
		// Get the direction and see if it's an output
		if (!(GPIO_REG(GPIO_GPDR0) & (1 << gpio_bit)))
			return -1;

		// if yes, then set it
		GPIO_REG(GPIO_GPCR0) = (1 << gpio_bit);
	}
	else if (gpio_bit < 64)
	{
		// Get the direction and see if it's an output
		if (!(GPIO_REG(GPIO_GPDR1) & (1 << (gpio_bit - 32))))
			return -1;

		// if yes, then clear it
		GPIO_REG(GPIO_GPCR1) = (1 << (gpio_bit - 32));
	}
	else
	{
		// Get the direction and see if it's an output
		if (!(GPIO_REG(GPIO_GPDR2) & (1 << (gpio_bit - 64))))
			return -1;

		// if yes, then clear it
		GPIO_REG(GPIO_GPCR2) = (1 << (gpio_bit - 64));
	}
	return 0;
}
//--------------------------------------------------------
// GPIO_tst()
//
// This function returns the state of desired bit passed in.
// It does not test to see if it's an input or output and thus
// can be used to verify if an output set/clr has taken place
// as well as for testing an input state.
//

int GPIO_tst(int gpio_bit)
{
	// First find out which group the bit belongs to
	if (gpio_bit < 32)
	{
		// Get the state
		if (GPIO_REG(GPIO_GPLR0) & (1 << gpio_bit)) return 1;
	}
	else if (gpio_bit < 64)
	{
		// Get the state
		if (GPIO_REG(GPIO_GPLR1) & (1 << (gpio_bit - 32))) return 1;
	}
	else
	{
		// Get the state
		if (GPIO_REG(GPIO_GPLR2) & (1 << (gpio_bit - 64))) return 1;
	}
	return 0; // bit was not set
}

//--------------------------------------------------------
// GPIO_in()
//
// This function changes the direction of the desired bit 
// to input.  NOTE: We do not test to see if changing the
// direction of the bit would screw up anything.  Use this
// function with caution!
int GPIO_in(int gpio_bit)
{
	// quick sanity test
	if (gpio_bit > 120) return -1;

	// now find out which group the bit belongs to
	if (gpio_bit < 32)
	{
		GPIO_REG(GPIO_GPDR0) &= ~(1 << gpio_bit);
	}
	else if (gpio_bit < 64)
	{
		GPIO_REG(GPIO_GPDR1) &= ~(1 << (gpio_bit - 32));
	}
	else
	{
		GPIO_REG(GPIO_GPDR2) &= ~(1 << (gpio_bit - 64));
	}
	return 0;
}

//--------------------------------------------------------
// GPIO_out()
//
// This function changes the direction of the desired bit 
// to output.  NOTE: We do not test to see if changing the
// direction of the bit would screw up anything.  Use this
// function with caution!
int GPIO_out(int gpio_bit)
{
	// quick sanity test
	if (gpio_bit > 120) return -1;
	
	// now find out which group the bit belongs to
	if (gpio_bit < 32)
	{
		GPIO_REG(GPIO_GPDR0) |= (1 << gpio_bit);
	}
	else if (gpio_bit < 64)
	{
		GPIO_REG(GPIO_GPDR1) |= (1 << (gpio_bit - 32));
	}
	else
	{
		GPIO_REG(GPIO_GPDR2) |= (1 << (gpio_bit - 64));
	}
	return 0;
}



