;;  Copyright ARM Ltd 2002. All rights reserved.
;;
;;  This code initialises the Integrator board (eg REMAP) before calling
;;  TCM Initialization and MMU Initialization if they exist.
;;  this allows scatter loading to relocate code into the TCMs
;;
;;  This code must be run from a privileged mode


INTOFFSET     EQU    0xA4000000
;INTIRQPR      EQU    0x40D00000

   		PRESERVE8

        AREA   IRQ, CODE, READONLY   ; name this block of code

        ENTRY
        ALIGN	4

        EXPORT IRQ_Handler
		IMPORT handle_irq
		
IRQ_Handler   ;FUNCTION

   ; 모든 User Mode상의 레지스터(r0 ~ r14)를 store to stack (Context 저장)
    
    
    str r14, [sp, #-4]! 		; push link-addr from r14 to stack 
    stmfd sp!, {r0-r14}^    	; push all usr regs to stack
   
  ; Put the exception address in r0
      
    sub r0, r14, #8 ; 위치 계산
        
    
    ; Call the C function to figure out what happened
    
    bl handle_irq ; 모든 레지스터를 stack에 push

    
   ; Restore user-mode processor state and return
      
    ldmfd sp!, {r0-r14}^    ; pop all usr regs from stack
    ldr r14, [sp], #4  	     ; pop link addr from stack to r14 
    subs pc, r14, #4  	     ; return   
        
                                         
        END                                 ; mark the end of this file