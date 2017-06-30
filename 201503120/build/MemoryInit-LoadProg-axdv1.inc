comment Huins Ltd. PXA255-PRO3 Memory map initializing scripts for 100MHz operation
comment edited by jhkim at 2005-10-11 

comment notice to axd debugger stack base address
let $top_of_memory 0xa2000000


comment disable all IRQs & FIQs
setreg cpsr 0xd3

comment set MSC0 comment changed wait state
setmem  0x48000008  0x123412c0 32
comment setmem  0x48000008  0x12345af0 32 
comment setmem  0x48000008  0x12347ff0 32 
comment setmem  0x48000008  0x12343ff0 32

comment set MSC1
setmem  0x4800000c  0x3ff923e9 32

comment set MSC2
setmem  0x48000010  0x3ff97ff9 32

comment set SDRAM controller to 100MHz
comment build MDREFR in a specific order
setmem  0x48000004  0x03c00fff 32

comment REF rate - (64MS/8128 Rows) * 100MHz/32 = 18
setmem  0x48000004  0x03c00018 32

comment set KORUN, K1RUN and K2RUN
setmem  0x48000004  0x03c52018 32

comment clear self refresh
setmem  0x48000004  0x03852018 32

comment set EOPIN and E1PIN
setmem  0x48000004  0x0385b018 32

comment set MDCNFG
setmem  0x48000000  0x09c809c8 32

comment delay for 200usec : pause for 1 seconds (alternative)
comment pause 1 

comment SDRAM refresh(CBR), 9 cycles

setmem  0xa0000000  0xa0000000 32
setmem  0xa0000000  0xa0000000 32
setmem  0xa0000000  0xa0000000 32
setmem  0xa0000000  0xa0000000 32
setmem  0xa0000000  0xa0000000 32

setmem  0xa0000000  0xa0000000 32
setmem  0xa0000000  0xa0000000 32
setmem  0xa0000000  0xa0000000 32
setmem  0xa0000000  0xa0000000 32


comment MSC_MDCNFG
setmem  0x48000000  0x0acb0acb 32

comment MSC_MDMRS
setmem  0x48000040  0x00000000 32

comment set stack pointer
setreg r13 0xa0400000