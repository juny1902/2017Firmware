;;  Copyright ARM Ltd 2002. All rights reserved.
;;
;;  This implementation of __user_initial_stackheap places the
;;  heap at the location of the symbol bottom_of_heap.  
;;  This symbol is placed by the scatter file.  
;;
;;  It assumes that the application mode stack has been placed
;;  in the reset handler.  
;;
        PRESERVE8

        AREA   UISH, CODE, READONLY      ; name this block of code

	ALIGN	4
heap_base       DCD     0xa1f00000
;stack_base	DCD	0xa2000000

        EXPORT __user_initial_stackheap

__user_initial_stackheap FUNCTION
    LDR   r0,heap_base
;    LDR   r1,stack_base
    MOV   pc,lr
    ENDFUNC
    
        END
        

;; The following is the equivalent implementation of the above in C
;;
;; extern unsigned int bottom_of_heap;    //defined in heap.s
;;
;; __value_in_regs struct __initial_stackheap __user_initial_stackheap(
;;         unsigned R0, unsigned SP, unsigned R2, unsigned SL)
;; {
;;     struct __initial_stackheap config;
;;
;;     config.heap_base = (unsigned int)&bottom_of_heap; // defined in heap.s
;;                                                       // placed by scatterfile
;;     config.stack_base = SP;   // inherit SP from the execution environment
;;
;;     return config;
;; }

; 응용 프로그램 스택 및 힙은 C 라이브러리를 초기화하는 동안 설정됩니다. 스택 및
  힙을 설정하는 루틴을 다시 구현하여 스택 및 힙 배치를 조정할 수 있습니다. ARM C
  라이브러리에서 이 루틴은 __user_initial_stackheap()입니다.