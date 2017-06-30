#
#
#	Created by jhkim from Huin Ltd.
#	e-mail : jhkim@huins.com
#		2005-10-12
#



CC=armcc
AS=armasm
LD=armlink
AR=armar
FE=fromelf


all: pxa255-pro3.bin
# for Unix
#	@echo Build completed
# for Windows
	@if exist *.bin echo Build completed

rebuild: clean all

clean:
# for Unix
#	rm -f ..\obj\*.o ..\obj\*.axf ..\obj\*.bin
# for Windows
	if exist *.o del ..\obj\*.o
	if exist *.axf del ..\obj\*.axf
	if exist *.bin del ..\obj\*.bin
	if exist *.txt del ..\list\*.txt 


CFLAGS = -c -cpu xscale -g -O0 -Otime -W -Ono_inline -DMSC_CLOCK -I..\inc
#LFLAGS = -info totals -info unused -map -list ..\list\list.txt -first vectors.o(Vect) -entry Reset_Handler -ro-base 0xa0000000
#LFLAGS = -info totals -info unused -map -v -d -p -x -list ..\list\list.txt -entry Reset_Handler -scatter scatter.scf
LFLAGS = -info totals -info unused -map -list ..\list\list.txt -entry Reset_Handler -scatter scatter-rom.scf
AFLAGS = -g -cpu xscale -i..\inc\asm


pxa255-pro3.bin: pxa255-pro3.axf
	$(FE) ..\obj\pxa255-pro3.axf -bin -o ..\obj\pxa255-pro3.bin


pxa255-pro3.axf: ..\obj\main.o ..\obj\embed_uish.o ..\obj\init.o ..\obj\vectors.o ..\obj\lcd.o ..\obj\chario.o ..\obj\mprintf.o ..\obj\pxa250_gpio.o
	$(LD) $(LFLAGS) ..\obj\vectors.o ..\obj\init.o ..\obj\embed_uish.o ..\obj\main.o ..\obj\chario.o ..\obj\mprintf.o ..\obj\lcd.o ..\obj\pxa250_gpio.o -o ..\obj\pxa255-pro3.axf


#arm-asm

..\obj\vectors.o: ..\init\vectors.s
	$(AS) $(AFLAGS) ..\init\vectors.s -o ..\obj\vectors.o

..\obj\init.o: ..\init\init.s
	$(AS) $(AFLAGS) ..\init\init.s -o ..\obj\init.o

..\obj\embed_uish.o: ..\init\embed_uish.s
	$(AS) $(AFLAGS) ..\init\embed_uish.s -o ..\obj\embed_uish.o
	
# armcc	
		
..\obj\pxa250_gpio.o: ..\init\pxa250_gpio.c                                           
	$(CC) $(CFLAGS) ..\init\pxa250_gpio.c -o ..\obj\pxa250_gpio.o
			
..\obj\chario.o: ..\init\chario.c
	$(CC) $(CFLAGS) ..\init\chario.c -o ..\obj\chario.o			

..\obj\mprintf.o: ..\init\mprintf.c
	$(CC) $(CFLAGS) ..\init\mprintf.c -o ..\obj\mprintf.o			

..\obj\lcd.o: ..\init\lcd.c
	$(CC) $(CFLAGS) ..\init\lcd.c -o ..\obj\lcd.o	  
				
..\obj\main.o: ..\diag\main.c
	$(CC) $(CFLAGS) ..\diag\main.c -o ..\obj\main.o   