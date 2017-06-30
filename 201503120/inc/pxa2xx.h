// Description:  This file contains register base addresses and offsets
//				 and access macros for the PXA255 on-chip peripherals
//

#include "bits.h"

//---------------------------------------
// Memory Controller - offsets and bit 
#define MSC_BASE			0x48000000
#define MSC_REG(_x_)		*(vulong *)(MSC_BASE + _x_)	

//---------------------------------------
// LCD Controller
#define LCD_BASE			0x44000000
#define LCD_REG(_x_)		*(vulong *)(LCD_BASE + _x_)	

//---------------------------------------
// DMA Controller
#define DMA_BASE			0x40000000
#define DMA_REG(_x_)		*(vulong *)(DMA_BASE + _x_)	
#define DMA_DCSR0    		0x000		// DMA Control / Status Register for Channel 0  		
#define DMA_DCSR1    		0x004		// DMA Control / Status Register for Channel 1  		
#define DMA_DCSR2    		0x008		// DMA Control / Status Register for Channel 2  		
#define DMA_DCSR3    		0x00c		// DMA Control / Status Register for Channel 3  		
#define DMA_DCSR4    		0x010		// DMA Control / Status Register for Channel 4  		
#define DMA_DCSR5    		0x014		// DMA Control / Status Register for Channel 5  		
#define DMA_DCSR6    		0x018		// DMA Control / Status Register for Channel 6  		
#define DMA_DCSR7    		0x01c		// DMA Control / Status Register for Channel 7  		
#define DMA_DCSR8    		0x020		// DMA Control / Status Register for Channel 8  		
#define DMA_DCSR9    		0x024		// DMA Control / Status Register for Channel 9  		
#define DMA_DCSR10   		0x028		// DMA Control / Status Register for Channel 10  		
#define DMA_DCSR11   		0x02c		// DMA Control / Status Register for Channel 11  		
#define DMA_DCSR12   		0x030		// DMA Control / Status Register for Channel 12  		
#define DMA_DCSR13   		0x034		// DMA Control / Status Register for Channel 13  		
#define DMA_DCSR14   		0x038		// DMA Control / Status Register for Channel 14  		
#define DMA_DCSR15   		0x03c		// DMA Control / Status Register for Channel 15  		
#define DMA_DINT     		0x0f0		// DMA Interrupt Register  		
#define DMA_DRCMR0   		0x100		// Request to Channel Map Register for DREQ 0 (companion chip request 0)  		
#define DMA_DRCMR1   		0x104		// Request to Channel Map Register for DREQ 1 (companion chip request 1)  		
#define DMA_DRCMR2   		0x108		// Request to Channel Map Register for I2S receive Request  		
#define DMA_DRCMR3   		0x10c		// Request to Channel Map Register for I2S transmit Request  		
#define DMA_DRCMR4   		0x110		// Request to Channel Map Register for BTUART receive Request  		
#define DMA_DRCMR5   		0x114		// Request to Channel Map Register for BTUART transmit Request.  		
#define DMA_DRCMR6   		0x118		// Request to Channel Map Register for FFUART receive Request  		
#define DMA_DRCMR7   		0x11c		// Request to Channel Map Register for FFUART transmit Request  		
#define DMA_DRCMR8   		0x120		// Request to Channel Map Register for AC97 microphone Request  		
#define DMA_DRCMR9   		0x124		// Request to Channel Map Register for AC97 modem receive Request  		
#define DMA_DRCMR10  		0x128		// Request to Channel Map Register for AC97 modem transmit Request  		
#define DMA_DRCMR11  		0x12c		// Request to Channel Map Register for AC97 audio receive Request  		
#define DMA_DRCMR12  		0x130		// Request to Channel Map Register for AC97 audio transmit Request  		
#define DMA_DRCMR13  		0x134		// Request to Channel Map Register for SSP receive Request  		
#define DMA_DRCMR14  		0x138		// Request to Channel Map Register for SSP transmit Request  		
#define DMA_DRCMR15  		0x13c		// Reserved  		
#define DMA_DRCMR16  		0x140		// Reserved  		
#define DMA_DRCMR17  		0x144		// Request to Channel Map Register for ICP receive Request  		
#define DMA_DRCMR18  		0x148		// Request to Channel Map Register for ICP transmit Request  		
#define DMA_DRCMR19  		0x14c		// Request to Channel Map Register for STUART receive Request  		
#define DMA_DRCMR20  		0x150		// Request to Channel Map Register for STUART transmit Request  		
#define DMA_DRCMR21  		0x154		// Request to Channel Map Register for MMC receive Request  		
#define DMA_DRCMR22  		0x158		// Request to Channel Map Register for MMC transmit Request  		
#define DMA_DRCMR23  		0x15c		// RESERVED
#define DMA_DRCMR24  		0x160		// RESERVED
#define DMA_DRCMR25  		0x164		// Request to Channel Map Register for USB endpoint 1 Request
#define DMA_DRCMR26  		0x168		// Request to Channel Map Register for USB endpoint 2 Request
#define DMA_DRCMR27  		0x16c		// Request to Channel Map Register for USB endpoint 3 Request
#define DMA_DRCMR28  		0x170		// Request to Channel Map Register for USB endpoint 4 Request
#define DMA_DRCMR29  		0x174		// RESERVED
#define DMA_DRCMR30  		0x178		// Request to Channel Map Register for USB endpoint 6 Request
#define DMA_DRCMR31  		0x17c		// Request to Channel Map Register for USB endpoint 7 Request
#define DMA_DRCMR32  		0x180		// Request to Channel Map Register for USB endpoint 8 Request
#define DMA_DRCMR33  		0x184		// Request to Channel Map Register for USB endpoint 9 Request
#define DMA_DRCMR34  		0x188		// RESERVED
#define DMA_DRCMR35  		0x18c		// Request to Channel Map Register for USB endpoint 11 Request
#define DMA_DRCMR36  		0x190		// Request to Channel Map Register for USB endpoint 12 Request
#define DMA_DRCMR37  		0x194		// Request to Channel Map Register for USB endpoint 13 Request
#define DMA_DRCMR38  		0x198		// Request to Channel Map Register for USB endpoint 14 Request
#define DMA_DRCMR39  		0x19c		// RESERVED
#define DMA_DDADR0   		0x200		// DMA Descriptor Address Register channel 0
#define DMA_DSADR0   		0x204		// DMA Source Address Register channel 0
#define DMA_DTADR0   		0x208		// DMA Target Address Register channel 0
#define DMA_DCMD0    		0x20c		// DMA Command Address Register channel 0
#define DMA_DDADR1   		0x210		// DMA Descriptor Address Register channel 1
#define DMA_DSADR1   		0x214		// DMA Source Address Register channel 1
#define DMA_DTADR1   		0x218		// DMA Target Address Register channel 1
#define DMA_DCMD1    		0x21c		// DMA Command Address Register channel 1
#define DMA_DDADR2   		0x220		// DMA Descriptor Address Register channel 2
#define DMA_DSADR2   		0x224		// DMA Source Address Register channel 2
#define DMA_DTADR2   		0x228		// DMA Target Address Register channel 2
#define DMA_DCMD2    		0x22c		// DMA Command Address Register channel 2
#define DMA_DDADR3   		0x230		// DMA Descriptor Address Register channel 3
#define DMA_DSADR3   		0x234		// DMA Source Address Register channel 3
#define DMA_DTADR3   		0x238		// DMA Target Address Register channel 3
#define DMA_DCMD3    		0x23c		// DMA Command Address Register channel 3
#define DMA_DDADR4   		0x240		// DMA Descriptor Address Register channel 4
#define DMA_DSADR4   		0x244		// DMA Source Address Register channel 4
#define DMA_DTADR4   		0x248		// DMA Target Address Register channel 4
#define DMA_DCMD4    		0x24c		// DMA Command Address Register channel 4
#define DMA_DDADR5   		0x250		// DMA Descriptor Address Register channel 5
#define DMA_DSADR5   		0x254		// DMA Source Address Register channel 5
#define DMA_DTADR5   		0x258		// DMA Target Address Register channel 5
#define DMA_DCMD5    		0x25c		// DMA Command Address Register channel 5
#define DMA_DDADR6   		0x260		// DMA Descriptor Address Register channel 6
#define DMA_DSADR6   		0x264		// DMA Source Address Register channel 6
#define DMA_DTADR6   		0x268		// DMA Target Address Register channel 6
#define DMA_CMD6     		0x26c		// DMA Command Address Register channel 6
#define DMA_DADR7    		0x270		// DMA Descriptor Address Register channel 7
#define DMA_SADR7    		0x274		// DMA Source Address Register channel 7
#define DMA_TADR7    		0x278		// DMA Target Address Register channel 7
#define DMA_CMD7     		0x27c		// DMA Command Address Register channel 7
#define DMA_DADR8    		0x280		// DMA Descriptor Address Register channel 8
#define DMA_SADR8    		0x284		// DMA Source Address Register channel 8
#define DMA_TADR8    		0x288		// DMA Target Address Register channel 8
#define DMA_CMD8     		0x28c		// DMA Command Address Register channel 8
#define DMA_DADR9    		0x290		// DMA Descriptor Address Register channel 9
#define DMA_SADR9    		0x294		// DMA Source Address Register channel 9
#define DMA_TADR9    		0x298		// DMA Target Address Register channel 9
#define DMA_CMD9     		0x29c		// DMA Command Address Register channel 9
#define DMA_DADR10   		0x2a0		// DMA Descriptor Address Register channel 10
#define DMA_SADR10   		0x2a4		// DMA Source Address Register channel 10
#define DMA_TADR10   		0x2a8		// DMA Target Address Register channel 10
#define DMA_CMD10    		0x2ac		// DMA Command Address Register channel 10
#define DMA_DADR11   		0x2b0		// DMA Descriptor Address Register channel 11
#define DMA_SADR11   		0x2b4		// DMA Source Address Register channel 11
#define DMA_TADR11   		0x2b8		// DMA Target Address Register channel 11
#define DMA_CMD11    		0x2bc		// DMA Command Address Register channel 11
#define DMA_DADR12   		0x2c0		// DMA Descriptor Address Register channel 12
#define DMA_SADR12   		0x2c4		// DMA Source Address Register channel 12     
#define DMA_TADR12   		0x2c8		// DMA Target Address Register channel 12     
#define DMA_CMD12    		0x2cc		// DMA Command Address Register channel 12     
#define DMA_DADR13   		0x2d0		// DMA Descriptor Address Register channel 13     
#define DMA_SADR13   		0x2d4		// DMA Source Address Register channel 13     
#define DMA_TADR13   		0x2d8		// DMA Target Address Register channel 13     
#define DMA_CMD13    		0x2dc		// DMA Command Address Register channel 13     
#define DMA_DADR14   		0x2e0		// DMA Descriptor Address Register channel 14     
#define DMA_SADR14   		0x2e4		// DMA Source Address Register channel 14     
#define DMA_TADR14   		0x2e8		// DMA Target Address Register channel 14     
#define DMA_CMD14    		0x2ec		// DMA Command Address Register channel 14     
#define DMA_DADR15   		0x2f0		// DMA Descriptor Address Register channel 15     
#define DMA_SADR15   		0x2f4		// DMA Source Address Register channel 15     
#define DMA_TADR15   		0x2f8		// DMA Target Address Register channel 15     
#define DMA_CMD15    		0x2fc		// DMA Command Address Register channel 15     

//---------------------------------------
//     UARTs
#define FF_UART_BASE		0x40100000	// Full Function UART Base Address
#define FF_UART_REG(_x_)	*(vulong *)(FF_UART_BASE + _x_)	
#define BT_UART_BASE		0x40200000	// Bluetooth UART Base Address
#define BT_UART_REG(_x_)	*(vulong *)(BT_UART_BASE + _x_)	
#define STD_UART_BASE		0x40700000	// Standard UART Base Address
#define STD_UART_REG(_x_)	*(vulong *)(STD_UART_BASE + _x_)	

#define UART_RBR      		0x00        // Receive Buffer Register (read only)     
#define UART_THR      		0x00        // Transmit Holding Register (write only)     
#define UART_IER      		0x04        // Interrupt Enable Register (read/write)     
#define UART_IIR      		0x08        // Interrupt ID Register (read only)     
#define UART_FCR      		0x08        // FIFO Control Register (write only)     
#define UART_LCR      		0x0C        // Line Control Register (read/write)     
#define UART_MCR      		0x10        // Modem Control Register (read/write)     
#define UART_LSR      		0x14        // Line Status Register (read only)     
#define UART_MSR      		0x18        // Modem Status Register (read only)     
#define UART_SPR      		0x1C        // Scratch Pad Register (read/write)     
#define UART_DLL      		0x00        // Baud divisor lower byte (read/write)     
#define UART_DLH      		0x04        // Baud divisor higher byte (read/write)     
#define UART_ISR      		0x20        // Infrared Select Register (read/write)     

//---------------------------------------
//     I2C
#define I2C_BASE			0x40301680
#define I2C_REG(_x_)		*(vulong *)(I2C_BASE + _x_)

#define I2C_ISAR		0x20		// I2C Slave Address Register	
#define I2C_ICR			0x10		// I2C Control Register
#define I2C_IDBR		0x08		// I2C Data Buffer Register
#define I2C_ISR			0X18

//---------------------------------------
//     I2S
#define I2S_BASE		0x40400000   
#define I2S_REG(_x_)		*(vulong *)(I2S_BASE + _x_)	
#define I2S_SACR0      		0x00        // Global Control Register
#define I2S_SACR1      		0x04        // Serial Audio I2S/MSB-Justified Control Register
#define I2S_SASR0      		0x0C        // Serial Audio I2S/MSB-Justified Interface and FIFO Status Register
#define I2S_SAIMR      		0x14        // Serial Audio Interrupt Mask Register
#define I2S_SAICR      		0x18        // Serial Audio Interrupt Clear Register
#define I2S_SAITR      		0x5C        // Serial Audio Interrupt Test Register
#define I2S_SADIV      		0x60        // Audio clock divider register. See section Section 12.3
										// Serial Audio Clocks and Sampling Frequencies on page 12-7.
#define I2S_SADR       		0x80        // Serial Audio Data Register (TX and RX FIFO access register).

//---------------------------------------
//     AC97
#define AC97_BASE		0x40500000   
#define AC97_REG(_x_)		*(vulong *)(AC97_BASE + _x_)	
#define AC97_POCR        	0x000       // PCM Out Control Register
#define AC97_PICR        	0x004       // PCM In Control Register
#define AC97_MCCR        	0x008       // Mic In Control Register
#define AC97_GCR         	0x00C       // Global Control Register 
#define AC97_POSR        	0x010       // PCM Out Status Register
#define AC97_PISR        	0x014       // PCM In Status Register
#define AC97_MCSR        	0x018       // Mic In Status Register
#define AC97_GSR         	0x01C       // Global Status Register 
#define AC97_CAR         	0x020       // CODEC Access Register 
#define AC97_PCDR       	0x040       // PCM FIFO Data Register 
#define AC97_MCDR       	0x060       // Mic-in FIFO Data Register 
#define AC97_MOCR       	0x100       // MODEM Out Control Register
#define AC97_MICR       	0x108       // MODEM In Control Register
#define AC97_MOSR       	0x110       // MODEM Out Status Register
#define AC97_MISR       	0x118       // MODEM In Status Register
#define AC97_MODR       	0x140       // MODEM FIFO Data Register

//---------------------------------------
//     UDC
#define USB_BASE		0x40600000   
#define USB_REG(_x_)		*(vulong *)(USB_BASE + _x_)	
#define USB_UDCCR      		0x000          	// UDC control register
#define USB_UDCCS0     		0x010          	// UDC Endpoint 0 Control/Status Register
#define USB_UDCCS1     		0x014          	// UDC Endpoint 1 (IN) Control/Status Register
#define USB_UDCCS2     		0x018          	// UDC Endpoint 2 (OUT) Control/Status Register
#define USB_UDCCS3     		0x01C          	// UDC Endpoint 3 (IN) Control/Status Register
#define USB_UDCCS4     		0x020          	// UDC Endpoint 4 (OUT) Control/Status Register
#define USB_UDCCS5     		0x024          	// UDC Endpoint 5 (Interrupt) Control/Status Register
#define USB_UDCCS6     		0x028          	// UDC Endpoint 6 (IN) Control/Status Register
#define USB_UDCCS7     		0x02C          	// UDC Endpoint 7 (OUT) Control/Status Register
#define USB_UDCCS8     		0x030          	// UDC Endpoint 8 (IN) Control/Status Register
#define USB_UDCCS9     		0x034          	// UDC Endpoint 9 (OUT) Control/Status Register
#define USB_UDCCS10    		0x038          	// UDC Endpoint 10 (Interrupt) Control/Status Register
#define USB_UDCCS11    		0x03C          	// UDC Endpoint 11 (IN) Control/Status Register
#define USB_UDCCS12    		0x040          	// UDC Endpoint 12 (OUT) Control/Status Register
#define USB_UDCCS13    		0x044          	// UDC Endpoint 13 (IN) Control/Status Register
#define USB_UDCCS14    		0x048          	// UDC Endpoint 14 (OUT) Control/Status Register
#define USB_UDCCS15    		0x04C          	// UDC Endpoint 15 (Interrupt) Control/Status Register
#define USB_UICR0      		0x050          	// UDC Interrupt Control Register 0
#define USB_UICR1      		0x054          	// UDC Interrupt Control Register 1
#define USB_USIR0      		0x058          	// UDC Status Interrupt Register 0
#define USB_USIR1      		0x05C          	// UDC Status Interrupt Register 1
#define USB_UFNRH      		0x060          	// UDC Frame Number Register High
#define USB_UFNRL      		0x064          	// UDC Frame Number Register Low
#define USB_UDDR0      		0x080          	// UDC Endpoint 0 Data Register
#define USB_UDDR1      		0x100          	// UDC Endpoint 1 Data Register
#define USB_UDDR2      		0x1C0          	// UDC Endpoint 2 Data Register
#define USB_UDDR3      		0x200          	// UDC Endpoint 3 Data Register
#define USB_UDDR4      		0x400          	// UDC Endpoint 4 Data Register
#define USB_UDDR5      		0x0A0          	// UDC Endpoint 5 Data Register
#define USB_UDDR6      		0x600          	// UDC Endpoint 6 Data Register
#define USB_UDDR7      		0x680          	// UDC Endpoint 7 Data Register
#define USB_UDDR8      		0x700          	// UDC Endpoint 8 Data Register
#define USB_UDDR9      		0xA00          	// UDC Endpoint 9 Data Register
#define USB_UDDR10     		0x0C0          	// UDC Endpoint 10 Data Register
#define USB_UDDR11     		0xB00          	// UDC Endpoint 11 Data Register
#define USB_UDDR12     		0xB80          	// UDC Endpoint 12 Data Register
#define USB_UDDR13     		0xC00          	// UDC Endpoint 13 Data Register
#define USB_UDDR14     		0xE00          	// UDC Endpoint 14 Data Register
#define USB_UDDR15     		0x0E0          	// UDC Endpoint 15 Data Register

//---------------------------------------
//     Fast Infrared UART
#define IRDA_BASE		0x40800000  
#define IRDA_REG(_x_)		*(vulong *)(IRDA_BASE + _x_)	
#define IRDA_ICCR0      	0x00          	// ICP control register 0
#define IRDA_ICCR1      	0x04          	// ICP control register 1
#define IRDA_ICCR2      	0x08          	// ICP control register 2
#define IRDA_ICDR       	0x0C          	// ICP data register
#define IRDA_ICSR0      	0x14          	// ICP status register 0
#define IRDA_ICSR1      	0x18          	// ICP status register 1

//---------------------------------------
//     RTC
#define RTC_BASE			0x40900000   
#define RTC_REG(_x_)		*(vulong *)(RTC_BASE + _x_)	
#define RTC_RCNR       		0x00          	// RTC count register
#define RTC_RTAR       		0x04          	// RTC alarm register
#define RTC_RTSR       		0x08          	// RTC status register
#define RTC_RTTR       		0x0C          	// RTC timer trim register

//---------------------------------------
//     OS Timer
#define TMR_BASE			0x40A00000   
#define TMR_REG(_x_)		*(vulong *)(TMR_BASE + _x_)	
#define TMR_OSMR0      		0x00          	// OS timer match registers<3:0>
#define TMR_OSMR1      		0x04          	//
#define TMR_OSMR2      		0x08          	//
#define TMR_OSMR3      		0x0C          	//
#define TMR_OSCR       		0x10          	// OS timer counter register
#define TMR_OSSR       		0x14          	// OS timer status register
#define TMR_OWER       		0x18          	// OS timer watchdog enable register
#define TMR_OIER       		0x1C          	// OS timer interrupt enable register

//---------------------------------------
//     PWM 
#define PWM0_BASE		0x40B00000  
#define PWM0_REG(_x_)		*(vulong *)(PWM0_BASE + _x_)	
#define PWM1_BASE		0x40C00000  
#define PWM1_REG(_x_)		*(vulong *)(PWM1_BASE + _x_)	
#define PWM_PWMCTRL   		0x00          	// PWM Control Register
#define PWM_PWDUTY    		0x04          	// PWM Duty Cycle Register
#define PWM_PERVAL    		0x08          	// PWM Period Control Register

//---------------------------------------
//     Interrupt Control   
#define INT_BASE   		0x40D00000      // Interrupt controller IRQ pending register
#define INT_REG(_x_)		*(vulong *)(INT_BASE + _x_)	
#define INT_ICIP       		0x00      		// Interrupt controller IRQ pending register
#define INT_ICMR       		0x04      		// Interrupt controller mask register
#define INT_ICLR       		0x08      		// Interrupt controller level register
#define INT_ICFP       		0x0C      		// Interrupt controller FIQ pending register
#define INT_ICPR       		0x10      		// Interrupt controller pending register
#define INT_ICCR       		0x14      		// Interrupt controller control register

//---------------------------------------
// GPIO - Register offsets and bit 
#define GPIO_BASE		0x40E00000
#define GPIO_REG(_x_)		*(vulong *)(GPIO_BASE + _x_)	

//---------------------------------------
//     Power Manager and Reset Control
#define PWR_CTL_BASE		0x40F00000  	 
#define PWR_REG(_x_)		*(vulong *)(PWR_CTL_BASE + _x_)	
#define PWR_PMCR       		0x00      // Power Manager Control register
#define PWR_PSSR       		0x04      // Power Manager Sleep Status register
#define PWR_PSPR       		0x08      // Power Manager Scratch Pad register
#define PWR_PWER       		0x0C      // Power Manager Wake-up Enable register
#define PWR_PRER       		0x10      // Power Manager GPIO Rising-edge Detect Enable register
#define PWR_PFER       		0x14      // Power Manager GPIO Falling-edge Detect Enable register
#define PWR_PEDR       		0x18      // Power Manager GPIO Edge Detect Status register
#define PWR_PCFR       		0x1C      // Power Manager General Configuration register
#define PWR_PGSRx      		0x20      // Power Manager GPIO Sleep State register for GP[31-0]
#define PWR_PGSRy      		0x24      // Power Manager GPIO Sleep State register for GP[63-32]
#define PWR_PGSRz      		0x28      // Power Manager GPIO Sleep State register for GP[84-64]
#define PWR_RCSR       		0x30      // Reset controller status register

//---------------------------------------
//     Clocks Manager
#define CLK_BASE		0x41300000   
#define CLK_REG(_x_)		*(vulong *)(CLK_BASE + _x_)	
#define CLK_CCCR       		0x00          // Core Clock Configuration Register
#define CLK_CKEN       		0x04          // Clock Enable Register
#define CLK_OSCC       		0x08          // Oscillator Configuration Register

//---------------------------------------
//     SSP
#define SSP_BASE		0x41000000  
#define SSP_REG(_x_)		*(vulong *)(SSP_BASE + _x_)	
#define SSP_SSCR0      		0x00          	// SSP Control Register 0
#define SSP_SSCR1      		0x04          	// SSP Control Register 1 
#define SSP_SSSR       		0x08          	// SSP Status Register
#define SSP_SSITR      		0x0C          	// SSP Interrupt Test Register
#define SSP_SSDR       		0x10          	// SSP Data Write Register/SSP Data Read Register

//---------------------------------------
//     MMC 
#define MMC_BASE		0x41100000  
#define MMC_REG(_x_)		*(vulong *)(MMC_BASE + _x_)	
#define MMC_MMCSTRPCL  		0x00          	// Control to start and stop MMC clock	
#define MMC_MMCSTAT    		0x04          	// MMC status register (read only)	
#define MMC_MMCCLKRT   		0x08          	// MMC clock rate 	
#define MMC_MMCSPI     		0x0c          	// SPI mode control bits	
#define MMC_MMCCMDAT   		0x10          	// Command/response/data sequence control	
#define MMC_MMCRESTO   		0x14          	// Expected response time out	
#define MMC_MMCRDTO    		0x18          	// Expected data read time out	
#define MMC_MMCBLKLEN  		0x1c          	// Block length of data transaction	
#define MMC_MMCNOB     		0x20          	// "Number of blocksfor block mode"	
#define MMC_MMCPRTBUF  		0x24          	// Partial MMC_TXFIFO FIFO written	
#define MMC_MMCIMASK   		0x28          	// Interrupt Mask	
#define MMC_MMCIREG    		0x2c          	// Interrupt Register (read only)	
#define MMC_MMCCMD     		0x30          	// Index of current command	
#define MMC_MMCARGH    		0x34          	// MSW part of the current command argument	
#define MMC_MMCARGL    		0x38          	// LSW part of the current command argument	
#define MMC_MMCRES     		0x3c          	// Response FIFO (read only)	
#define MMC_MMCRXFIFO  		0x40          	// Receive FIFO (read only)	
#define MMC_MMCTXFIFO  		0x44          	// Transmit FIFO (write only)	

//----------------------------------------
//    Interrupt Source

#define INT_HWUART		7
#define INT_GPIO0		8
#define INT_GPIO1		9
#define INT_GPIO2_84		10
#define INT_USB_SLAVE		11
#define INT_PMU			12
#define INT_I2S			13
#define INT_AC97		14
#define INT_NSSP		16
#define INT_LCD			17
#define INT_I2C			18
#define INT_ICP			19
#define INT_STUART		20
#define INT_BTUART		21
#define INT_FFUART		22
#define INT_MMC			23
#define INT_SSP			24
#define INT_DMA			25
#define INT_OSTIMER_M0		26
#define INT_OSTIMER_M1		27
#define INT_OSTIMER_M2		28
#define INT_OSTIMER_M3		29
#define INT_RTC_HZ		30
#define INT_RTC_ALARM		31

#define DMA_CH0			BIT0
#define DMA_CH1			BIT1
#define DMA_CH2			BIT2
#define DMA_CH3			BIT3
#define DMA_CH4			BIT4
#define DMA_CH5			BIT5
#define DMA_CH6			BIT6
#define DMA_CH7			BIT7
#define DMA_CH8			BIT8
#define DMA_CH9			BIT9
#define DMA_CH10		BIT10
#define DMA_CH11		BIT11
#define DMA_CH12		BIT12
#define DMA_CH13		BIT13
#define DMA_CH14		BIT14
#define DMA_CH15		BIT15
//------------------------------------------------
// Bring in the individual peripheral files here
#include "pxa2xx_msc.h"
#include "pxa2xx_gpio.h"

