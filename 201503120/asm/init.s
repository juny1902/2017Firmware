;;  Copyright ARM Ltd 2002. All rights reserved.
;;
;;  This code initialises the Integrator board (eg REMAP) before calling
;;  TCM Initialization and MMU Initialization if they exist.
;;  this allows scatter loading to relocate code into the TCMs
;;
;;  This code must be run from a privileged mode

    PRESERVE8

; --- Standard definitions of mode bits and interrupt (I & F) flags in PSRs

Mode_USR        EQU     0x10
Mode_FIQ        EQU     0x11
Mode_IRQ        EQU     0x12
Mode_SVC        EQU     0x13
Mode_ABT        EQU     0x17
Mode_UND        EQU     0x1B
Mode_SYS        EQU     0x1F ; available on ARM Arch 4 and later

I_Bit           EQU     0x80 ; when I bit is set, IRQ is disabled
F_Bit           EQU     0x40 ; when F bit is set, FIQ is disabled





Len_FIQ_Stack    EQU     256
Len_IRQ_Stack    EQU     256
Len_ABT_Stack    EQU     0
Len_UND_Stack    EQU     0
Len_SVC_Stack    EQU     1024
; Len_USR_Stack  EQU     1024

Offset_FIQ_Stack         EQU     0
Offset_IRQ_Stack         EQU     Offset_FIQ_Stack + Len_FIQ_Stack
Offset_ABT_Stack         EQU     Offset_IRQ_Stack + Len_IRQ_Stack
Offset_UND_Stack         EQU     Offset_ABT_Stack + Len_ABT_Stack
Offset_SVC_Stack         EQU     Offset_IRQ_Stack + Len_IRQ_Stack
; Offset_USR_Stack       EQU     Offset_SVC_Stack + Len_SVC_Stack
; For System Configuration

SDRAM_100MHz		EQU	1
stack_base		EQU	0xa2000000
SDRAM_BASE_ADDRESS	EQU	0xa0000000

; select one of PXA255_PRO1, PXA255_PRO2, PXA255_PRO3,PXA255_smart Platform.

	GBLS	PLATFORM
PLATFORM	SETS	"PXA255_PRO3"

; Select one of device that is loaded image. ex) ROM, RAM

	GBLS	ROBASE_DEV
ROBASE_DEV	SETS	"ROM"



        AREA   INIT, CODE, READONLY   ; name this block of code

        ENTRY
        ALIGN	4

        EXPORT  Reset_Handler

Reset_Handler   FUNCTION


	GET ..\inc\asm\pxa255
	
; Initialize core clock & Memory controll reg.

	ldr r0, =0x2001					; 모든 coprocessors에 접근을 허용한다
	mcr 	p15,0,r0,c15,c1,0
	nop
	nop
	nop

	ldr 	r0, =0x00000078				; Disable MMU, caches, write buffer 
	mcr 	p15,0,r0,c1,c0,0		
	nop
	nop
	nop

	ldr 	r0, =0x00000000
	mcr     p15,0,r0,c8,c7,0   		; flush TLB's 
	mcr     p15,0,r0,c7,c7,0   		; flush Caches 
	mcr	p15,0,r0,c7,c10,4		; Flush Write Buffer 
	nop
	nop
	nop

	mvn    r0, #0                   	; grant manager access to all domains 
	mcr    p15,0,r0,c3,c0,0  

	
; PXA250 interrupt controller 를 초기화 한다.
     	 

; Mask off all IRQs and FIQs 

    ldr r1, =(INT_BASE | INT_ICMR)
    ldr r2, =0x0	        	; 모든 interrupt를 mask off 시킨다  
    str r2, [r1]  			

; PXA250 Clock Register 를 초기화 한다.
     	 
    ldr r1, =CLK_BASE		; base of clock registers 
    ldr r2, =0x00000241		; memory clock:100MHz, nomal core clock:200MHz, turbo mode:400MHz 
    str r2, [r1, #CLK_CCCR]		
    		
; PXA250 Core Clock를 Turbo Mode로 설정한다.
     	 
	ldr r0,=0
	mrc p14,0,r0,c6,c0,0
	ldr r0,=3
	mcr p14,0,r0,c6,c0,0

; OS Timer를 초기화 한다. ;/

	ldr r1, =TMR_BASE		; reset the OS Timer Count to zero 
	mov r2, #0
	str r2, [r1, #TMR_OSCR]
	ldr r4, =0x300			; really 0x2E1 (0.27uS ; 0x2E1 = 198uS) is about 200usec,  
							; so 0x300 should be plenty :Wait OS Timer Stabilize        
1
	ldr r2, [r1, #TMR_OSCR]
	cmp r4, r2
	;bgt %b1    
	
; PXA250 Memory Controller를 초기화 한다.                     
                                                              
	ldr r1, =MSC_BASE		; base of memory controller   

	IF	ROBASE_DEV = "RAM"
		
		nop
				
	ELSE    
			
		; static memory controller를 초기화 한다  ;/
		        	
				
		IF	PLATFORM = "ACUMEN"
		ldr r2, =0x28a428a0		; CS0 : flash , CS1 : SMSC LAN91C1111   
		str r2, [r1, #MSC_MSC0]		   
		ldr r3, [r1, #MSC_MSC0]
	
		ldr r2, =0x7ff07ff8		; CS2 : TD242(USB2.0) , CS3 : 확장 보드(fpga board,iom board) 
		str r2, [r1, #MSC_MSC1]
		ldr r3, [r1, #MSC_MSC1]
		
		ldr r2, =0x7ff47ff8             ; CS4 : SL811HS(USB1.0) , CS5 : KEY PAD  	
		str r2, [r1, #MSC_MSC2]
		ldr r3, [r1, #MSC_MSC2]		
		ENDIF
			
		; SDRAM Controller를 100MHz 로 초기화 한다 ;/    
		
		IF :DEF: SDRAM_100MHz        
		
		ldr r2, =0x03c00fff    		; build MDREFR in a specific order 
		str r2, [r1, #MSC_MDREFR]    
			
		ldr r2, =0x03c00018  		; REF Rate = (64MS/8192 Rows) ; 100MHz /32 = 24 
		str r2, [r1, #MSC_MDREFR]
			
		ldr r2, =0x03c52018    		; Set K0RUN, K1RUN and K2RUN 
		str r2, [r1, #MSC_MDREFR]    
			
		ldr r2, =0x03852018      	; Clear Self Refresh 
		str r2, [r1, #MSC_MDREFR]    
			
		ldr r2, =0x0385b018		; Set E0PIN and E1PIN 
		str r2, [r1, #MSC_MDREFR]
		
		ldr r2, =0x0ac80ac8   		; Set CNFG, but don't enable just yet,CL =3,tRP=3clk,tRC=10clk,tRAS=7clk,tRCD=3clk    
		str r2, [r1, #MSC_MDCNFG]
		
		ENDIF	; SDRAM_100MHz ;/
	
		; SDRAM Controller를 50MHz 로 초기화 한다     
		
		IF :DEF: SDRAM_50MHz 
		
		ldr r2, =0x03ca4fff    
		str r2, [r1, #MSC_MDREFR]    
		
		ldr r2, =0x03ca4013		; REF Rate = (64MS/8192 Rows);50MHz/32 = 12 
		str r2, [r1, #MSC_MDREFR]
		
		ldr r2, =0x03cf6013 		; Set K0RUN, K1RUN and K2RUN 
		str r2, [r1, #MSC_MDREFR] 	
		
		ldr r2, =0x038f6013		; Clear Self Refresh 	
		str r2, [r1, #MSC_MDREFR] 
		
		ldr r2, =0x038ff013		; Set E0PIN and E1PIN 
		str r2, [r1, #MSC_MDREFR]	  
				 
		ldr r2, =0x0ac80ac8
		str r2, [r1, #MSC_MDCNFG]
		
		ENDIF  ; SDRAM_50MHz   
		
		; pause for ~200usec for SDRAM to init 
		ldr r1, =TMR_BASE		; reset the OS Timer Count to zero 
		mov r2, #0
		str r2, [r1, #TMR_OSCR]
		ldr r4, =0x300			; really 0x2E1 (0.27uS ; 0x2E1 = 198uS) is about 200usec,   
					; so 0x300 should be plenty        
1
		ldr r2, [r1, #TMR_OSCR]
		cmp r4, r2
		;bgt %b1    

		; force 9 cycles to SDRAM : 모든 sdram bank에 CBR(refrash cycle)이 발생한다. 
		ldr     r2, =SDRAM_BASE_ADDRESS
		str     r2, [r2]
		str     r2, [r2]
		str     r2, [r2]
		str     r2, [r2]
		str     r2, [r2]
		str     r2, [r2]
		str     r2, [r2]
		str     r2, [r2]
		str     r2, [r2]
		
		ldr r1, =MSC_BASE		; base of memory controller 
		
		ldr r2, =0x0acb0acb		; now enable SDRAM   
	    	str r2, [r1, #MSC_MDCNFG]
	
		; and do an MRS ;/
	    	ldr r2, =0x00000000
	    	str r2, [r1, #MSC_MDMRS]
	   	
	    ; sdram initialize 완료   	
	    		    	
	ENDIF	;IF	ROBASE_DEV="RAM"
	    
     
      ; 동작 모드를 SVC 모드로 설정하고 stack pointer
      ; 를 설정한다
            	 


; stack_base could be defined above, or located in a scatter file
        LDR     r0, =stack_base ;

; Enter each mode in turn and set up the stack pointer
        MSR     CPSR_c, #Mode_FIQ:OR:I_Bit:OR:F_Bit
        SUB     sp, r0, #Offset_FIQ_Stack

        MSR     CPSR_c, #Mode_IRQ:OR:I_Bit:OR:F_Bit
        SUB     sp, r0, #Offset_IRQ_Stack
        
        MSR     CPSR_c, #Mode_ABT:OR:I_Bit:OR:F_Bit ; No interrupts
        SUB     sp, r0, #Offset_ABT_Stack

        MSR     CPSR_c, #Mode_UND:OR:I_Bit:OR:F_Bit ; No interrupts
        SUB     sp, r0, #Offset_UND_Stack

        ;MSR     CPSR_c, #Mode_SVC:OR:I_Bit:OR:F_Bit
        MSR		CPSR_c,	 #Mode_SVC	;supervisor mode에서 인터럽트 마스크 제거
        SUB     sp, r0, #Offset_SVC_Stack

		
; Leave core in SVC mode
                                                                                           
; Branch to C Library entry point

        IMPORT  __main                      ; before MMU enabled import label to __main
;        LDR     r12,=__main                 ; save this in register for possible long jump

;        BX      r12                         ; branch to __main
	LDR		pc, =__main
        ENDFUNC
        
                                         
        END                                 ; mark the end of this file