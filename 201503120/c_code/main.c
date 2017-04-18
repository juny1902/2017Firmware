#include "config.h" 
#include "stddefs.h"
#include "pxa2xx.h"
#include "16c552.h"
#include "typedef.h"
#include "except.h"
#include "user.h"

extern void vinit(void);


int main()
{
	vinit();
	INIT_DEVICE();
	
    while(1)
    {	
    }
	
    return 0;
}