/* PXA255-PRO Configuration Parameter Defined Header File */

#define ON				1
#define OFF				0

#define ACUMEN			ON

#define RESET				0x00000000
#define RESETFUNC()			((void(*)())RESET)

#define SDRAM_100MHz			ON 	/* SDRAM 100MHz 동작 모드 */
#define SDRAM_50MHz			OFF	/* SDRAM 50MHz 동작 모드 */

#define FLASH_BASE			0x00000000	/* FLASH Base Address  */
#define MONITOR_RAM_BASE		0xa0000000	/* Monitoring Program Start Address */
#define MONITOR_LEN			0x20000		/* Monitoring Program Length Is 128Kbyte */

#define START_UP_LEN			0x1000		/* Start Up Code Length Is 4Kbye */
#define PARAM_OFFSET			0x20000		/* Parameter Offset is 128Kbyte */
#define MONITOR_ROM_BASE		(FLASH_BASE + START_UP_LEN)
#define PARAM_FLASH_BASE		(MONITOR_ROM_BASE + MONITOR_LEN + PARAM_OFFSET)

#define INITIALIZE			(3<<4)

#define VOUT_DPRAM2_BASE		0x5000000  
#define VOUT_DP2_DATA(_x_)		*(unsigned short *)(VOUT_DPRAM2_BASE + _x_)   // vout data in dpram2

#define MMU_BUFF			0xa0500000  
#define MMU_BUFF_DATA(_x_)		*(unsigned long *)(MMU_BUFF + _x_)   // vout data in dpram2

#define VOUT_DPRAM3_BASE		0x5800000
#define VOUT_DP3_DATA(_x_)		*(unsigned short *)(VOUT_DPRAM3_BASE + _x_)   // vout data in dpram2

#define FRAME_BUFF_START		0xa1000000 
#define FRAM_BUFF_SAVE(_x_,_y_)	*(unsigned short *)((FRAME_BUFF_START+_y_*0x100000) + _x_)
#define FRAME_SAVE(_x_)		*(unsigned short *)(FRAME_BUFF_START + _x_)

#define  I2C_SETING_INCLUDE		0

#define GPIO_WAKE_UP			25
#define GPIO_DP_MnS			7
#define GPIO_DPU46_nSEML		57

// LCD Size
#ifdef ACUMEN
#define TFT_LCD_640X480		OFF
#define TFT_LCD_240X320		OFF
#define TFT_LCD_480X272		OFF
#define TFT_LCD_800X480		ON
#endif

// Platform Type
#ifdef ACUMEN
#define TYPE_ACUMEN			1
#define PLATFORM_STRING		"Acumen"
#endif

// LED Blinking Interval
#define BLINKING_TIME		0x180

/* XBUFCNT & RBUFCNT:
 *  Number of transmit and receive buffers allocated to ethernet.
 *  The total of XBUFCNT+RBUFCNT should not exceed MAXEBDS
 */
#define XBUFCNT				8
#define RBUFCNT				8
#define XBUFSIZE			2048
#define RBUFSIZE			2048


// Data Cache Enable or Disable
#define DATA_CACHE_ENABLE		ON

#define INCLUDE_FF_UART			ON
#define INCLUDE_INTERRUPT		ON
#define INCLUDE_IR_UART			ON
#define INCLUDE_LED_BLINK		ON
#define INCLUDE_CACHE			ON