//==========================================================================
//
// pxa255_msc.h
//
// Author(s):    Michael Kelly, Cogent Computer Systems, Inc.
// Contributors: 
// Date:         04/17/2002
// Description:  This file contains register and bit defines for the PXA250
//               Memory Controller
//

//---------------------------------------
//  Memory Controller Register Offsets
#define MSC_MDCNFG     		0x00          			// SDRAM configuration register 0
#define MSC_MDREFR     		0x04          			// SDRAM refresh control register
#define MSC_MSC0       		0x08          			// Static memory control register 0
#define MSC_MSC1       		0x0C          			// Static memory control register 1
#define MSC_MSC2       		0x10          			// Static memory control register 2
#define MSC_MECR       		0x14          			// Expansion memory (PCMCIA / Compact Flash) bus configuration register
#define MSC_SXCNFG     		0x1C          			// Synchronous static memory control register
#define MSC_SXMRS      		0x24          			// MRS value to be written to Synchronous Flash or SMROM
#define MSC_MCMEM0     		0x28          			// Card interface Common Memory Space Socket 0 Timing Configuration
#define MSC_MCMEM1     		0x2C          			// Card interface Common Memory Space Socket 1 Timing Configuration
#define MSC_MCATT0     		0x30          			// Card interface Attribute Space Socket 0 Timing Configuration
#define MSC_MCATT1     		0x34          			// Card interface Attribute Space Socket 1 Timing Configuration
#define MSC_MCIO0      		0x38          			// Card interface I/O Space Socket 0 Timing Configuration
#define MSC_MCIO1      		0x3C          			// Card interface I/O Space Socket 1 Timing Configuration
#define MSC_MDMRS      		0x40          			// MRS value to be written to SDRAM
#define MSC_BOOTDEF    		0x44          			// Read-Only Boot-time register. Contains BOOT_SEL and PKG_SEL values.


// SDRAM configuration register 0
// Pair 2/3
#define MDCNFG_DSA1111_1	BIT28					// Use SA1111 Addressing Muxing Mode for pair 2/3.
#define MDCNFG_DLATCH1		BIT27					// Return Data from SDRAM latching scheme for pair 2/3, must be 1
#define MDCNFG_DADDR1		BIT26					// Use alternate addressing for pair 2/3
#define MDCNFG_DTC1_0		(0x00 << 24)			// 00 - tRP = 2 clks, CL = 2, tRCD = 1 clks, tRAS(min) = 3 clks, tRC = 4 clks
#define MDCNFG_DTC1_1		(0x01 << 24)			// 01 - tRP = 2 clks, CL = 2, tRCD = 2 clks, tRAS(min) = 5 clks, tRC = 8 clks
#define MDCNFG_DTC1_2		(0x02 << 24)			// 10 - tRP = 3 clks, CL = 3, tRCD = 3 clks, tRAS(min) =7 clks, tRC=10 clks
#define MDCNFG_DTC1_3		(0x03 << 24)			// 11 - tRP = 3 clks, CL = 3, tRCD = 3 clks, tRAS(min) = 7 clks, tRC = 11 clks
#define MDCNFG_DNB1			BIT23					// Number of banks in partition pair 2/3, 0 = 2, 1 = 4
#define MDCNFG_DRAC1_11		(0x00 << 21)			// SDRAM row address bit count for partition pair 2/3
#define MDCNFG_DRAC1_12		(0x01 << 21)
#define MDCNFG_DRAC1_13		(0x02 << 21)
#define MDCNFG_DCAC1_8		(0x00 << 19)			// Number of Column Address bits for partition pair 2/3
#define MDCNFG_DCAC1_9		(0x01 << 19)
#define MDCNFG_DCAC1_10		(0x02 << 19)
#define MDCNFG_DCAC1_11		(0x03 << 19)
#define MDCNFG_DWID2_16		BIT18					// SDRAM data bus width for partition pair 2/3
#define MDCNFG_DE3			BIT17					// SDRAM enable for partition 3
#define MDCNFG_DE2			BIT16					// SDRAM enable for partition 2
// Pair 0/1
#define MDCNFG_DSA1111_0	BIT12					// Use SA1111 Addressing Muxing Mode for pair 0/1.
#define MDCNFG_DLATCH0		BIT11					// Return Data from SDRAM latching scheme for pair 0/1, must be 1
#define MDCNFG_DADDR0		BIT10					// Use alternate addressing for pair 0/1
#define MDCNFG_DTC0_0		(0x00 << 8)				// 00 - tRP = 2 clks, CL = 2, tRCD = 1 clks, tRAS(min) = 3 clks, tRC = 4 clks
#define MDCNFG_DTC0_1		(0x01 << 8)				// 01 - tRP = 2 clks, CL = 2, tRCD = 2 clks, tRAS(min) = 5 clks, tRC = 8 clks
#define MDCNFG_DTC0_2		(0x02 << 8)				// 10 - tRP = 3 clks, CL = 3, tRCD = 3 clks, tRAS(min) =7 clks, tRC=10 clks
#define MDCNFG_DTC0_3		(0x03 << 8)				// 11 - tRP = 3 clks, CL = 3, tRCD = 3 clks, tRAS(min) = 7 clks, tRC = 11 clks
#define MDCNFG_DNB0			BIT7					// Number of banks in partition pair 0/1, 0 = 2, 1 = 4
#define MDCNFG_DRAC0_11		(0x00 << 5)				// SDRAM row address bit count for partition pair 0/1
#define MDCNFG_DRAC0_12		(0x01 << 5)
#define MDCNFG_DRAC0_13		(0x02 << 5)
#define MDCNFG_DCAC0_8		(0x00 << 3)				// Number of Column Address bits for partition pair 0/1
#define MDCNFG_DCAC0_9		(0x01 << 3)
#define MDCNFG_DCAC0_10		(0x02 << 3)
#define MDCNFG_DCAC0_11		(0x03 << 3)
#define MDCNFG_DWID0_16		BIT2					// SDRAM data bus width for partition pair 0/1, 0 = 32, 1 = 16
#define MDCNFG_DE1			BIT1					// SDRAM enable for partition 1
#define MDCNFG_DE0			BIT0					// SDRAM enable for partition 0

// SDRAM refresh control register
#define MDREFR_K2FREE		BIT25					// 1 = SDCLK2 is free-running (ignores MDREFR[APD] or MDREFR[K2RUN] bits)
#define MDREFR_K1FREE		BIT24					// 1 = SDCLK1 is free-running (ignores MDREFR[APD] or MDREFR[K1RUN] bits)
#define MDREFR_K0FREE		BIT23					// 1 = SDCLK0 is free-running (ignores MDREFR[APD] or MDREFR[K0RUN] bits)
#define MDREFR_SLFRSH		BIT22					// 1 = SDRAM Self-Refresh Enabled
#define MDREFR_APD			BIT20					// 1 = SDRAM/Synchronous Static Memory Auto-Power-Down Enable.
#define MDREFR_K2DB2		BIT19					// SDCLK2 Divide by 2, 1 = Divide by 2
#define MDREFR_K2RUN		BIT18					// SDCLK2 Run Control, 1 = Run
#define MDREFR_K1DB2		BIT17					// SDCLK1 Divide by 2, 1 = Divide by 2
#define MDREFR_K1RUN		BIT16					// SDCLK1 Run Control, 1 = Run
#define MDREFR_E1PIN		BIT15					// SDCKE1 Level Control, 1 = Enabled
#define MDREFR_K0DB2		BIT14					// SDCLK0 Divide by 2, 1 = Divide by 2
#define MDREFR_K0RUN		BIT13					// SDCLK0 Run Control, 1 = Run
#define MDREFR_E0PIN		BIT12					// SDCKE0 Level Control, 1 = Enabled
#define MDREFR_DRI(_x_)		(_x_ & 0xfff)			// Refresh Interval = (Refresh time/rows) x (MEMCLK/32)

// Static memory control register 0/1/2
// Chip Selects 1/3/5
#define MSC_RBUFF1			BIT31					// Return Data Buffer vs. Streaming behavior.
#define MSC_RRR1(_x_)		((_x_ & 0x7) << 28) 	// ROM/SRAM recovery time.
#define MSC_RDN1(_x_)		((_x_ & 0xf) << 24) 	// ROM delay next access
#define MSC_RDF1(_x_)		((_x_ & 0xf) << 20) 	// ROM delay first access (0-11, 12 = 13, 13 = 15, 14 = 18, 15 = 23)
#define MSC_RBW1_16			BIT19					// ROM bus width, 0 = 32, 1 = 16
#define MSC_RT1_NBROM		(0x0 << 16)				// ROM Type, Nonburst ROM or Flash Memory
#define MSC_RT1_SRAM		(0x1 << 16)				// SRAM
#define MSC_RT1_B4ROM		(0x2 << 16)				// Burst-of-four ROM or Flash (with non-burst writes)
#define MSC_RT1_B8ROM		(0x3 << 16)				// Burst-of-eight ROM or Flash (with non-burst writes)
#define MSC_RT1_VLIO		(0x4 << 16)				// Variable Latency I/O (VLIO)
// Chip Selects 0/2/4
#define MSC_RBUFF0			BIT15					// Return Data Buffer vs. Streaming behavior.
#define MSC_RRR0(_x_)		((_x_ & 0x7) << 12) 	// ROM/SRAM recovery time.
#define MSC_RDN0(_x_)		((_x_ & 0xf) << 8) 		// ROM delay next access
#define MSC_RDF0(_x_)		((_x_ & 0xf) << 4) 		// ROM delay first access (0-11, 12 = 13, 13 = 15, 14 = 18, 15 = 23)
#define MSC_RBW0_16			BIT3					// ROM bus width, 0 = 32, 1 = 16
#define MSC_RT0_NBROM		(0x0 << 0)				// ROM Type, Nonburst ROM or Flash Memory
#define MSC_RT0_SRAM		(0x1 << 0)				// SRAM
#define MSC_RT0_B4ROM		(0x2 << 0)				// Burst-of-four ROM or Flash (with non-burst writes)
#define MSC_RT0_B8ROM		(0x3 << 0)				// Burst-of-eight ROM or Flash (with non-burst writes)
#define MSC_RT0_VLIO		(0x4 << 0)				// Variable Latency I/O (VLIO)

// Synchronous static memory control register
// Pair 2/3
#define SXCNFG_SXLATCH2		BIT15					// SXMEM latching scheme for pair 2/3, must be 1
#define SXCNFG_SXTP2_SMROM	(0x0 << 13) 			// SX Memory type for pair 2/3, Sync Masked ROM
#define SXCNFG_SXTP2_NONSD	(0x2 << 13)				// Non-SDRAM type Sync FLASH
#define SXCNFG_SXCA2_7		(0x0 << 11)				// SX Memory column address bit count for pair 2/3
#define SXCNFG_SXCA2_8		(0x1 << 11)
#define SXCNFG_SXCA2_9		(0x2 << 11)
#define SXCNFG_SXCA2_10		(0x3 << 11)
#define SXCNFG_SXRA2_12		(0x0 << 9)				// SX Memory row address bit count for pair 2/3
#define SXCNFG_SXRA2_13		(0x1 << 9)
#define SXCNFG_SXRL2(_x_)	((_x_ & 0x7) << 21) 	// RAS Latency for pair 2/3. Must be 0x7 for SXCNFG_SXTP2_NONSD
#define SXCNFG_SXCL2_3		(0x2 << 18)				// CAS Latency for pair 2/3
#define SXCNFG_SXCL2_4		(0x3 << 18)
#define SXCNFG_SXCL2_5		(0x4 << 18)
#define SXCNFG_SXCL2_6		(0x5 << 18)
#define SXCNFG_SXCL2_7		(0x6 << 18)				// SXCNFG_SXTP2_NONSD only
#define SXCNFG_SXEN3		BIT17					// Enable Bit for Partition 3
#define SXCNFG_SXEN2		BIT16					// Enable Bit for Partition 2
// Pair 0/1
#define SXCNFG_SXLATCH0		BIT14					// SXMEM latching scheme for pair 0/1, must be 1
#define SXCNFG_SXTP0_SMROM	(0x0 << 12) 			// SX Memory type for pair 0/1, Sync Masked ROM
#define SXCNFG_SXTP0_NONSD	(0x2 << 12)				// Non-SDRAM type Sync FLASH
#define SXCNFG_SXCA0_7		(0x0 << 10)				// SX Memory column address bit count for pair 0/1
#define SXCNFG_SXCA0_8		(0x1 << 10)
#define SXCNFG_SXCA0_9		(0x2 << 10)
#define SXCNFG_SXCA0_10		(0x3 << 10)
#define SXCNFG_SXRA0_12		(0x0 << 8)				// SX Memory row address bit count for pair 0/1
#define SXCNFG_SXRA0_13		(0x1 << 8)
#define SXCNFG_SXRL0(_x_)	((_x_ & 0x7) << 5) 		// RAS Latency for pair 0/1. Must be 0x7 for SXCNFG_SXTP2_NONSD
#define SXCNFG_SXCL0_3		(0x2 << 2)				// CAS Latency for pair 0/1
#define SXCNFG_SXCL0_4		(0x3 << 2)
#define SXCNFG_SXCL0_5		(0x4 << 2)
#define SXCNFG_SXCL0_6		(0x5 << 2)
#define SXCNFG_SXCL0_7		(0x6 << 2)				// SXCNFG_SXTP2_NONSD only
#define SXCNFG_SXEN1		BIT1					// Enable Bit for Partition 1
#define SXCNFG_SXEN0		BIT0					// Enable Bit for Partition 0

// MRS value to be written to Synchronous Flash or SMROM
#define SXMRS_SXMRS2(_x_)	((_x_ & 0x7fff) << 16)	// Value to write for SX Memory requiring and MRS, pair 2/3
#define SXMRS_SXMRS0(_x_)	((_x_ & 0x7fff) << 0)	// Value to write for SX Memory requiring and MRS, pair 0/1

// Memory Card Interface Timing Configurations
// Values are valid for MEMC0/1, MCATT0/1 and MCIO0/1
#define MCTMG_HOLD(_x_)		((_x_ & 0x3f) << 14)	// # MEMCLKs to hold address after command deassertion
#define MCTMG_ASST(_x_)		((_x_ & 0x1f) << 7)		// Code for the command assertion time. See Table 6-26.
#define MCTMG_SET(_x_)		((_x_ & 0x7f) << 0)		// # MEMCLKs to set up address before command assertion

// Expansion memory (PCMCIA / Compact Flash) bus configuration register
// MECR_CIT must be set appropriately by software after card detection 
// is complete
#define MECR_CIT			BIT1					// Card-Is-There, 0 - No card inserted, 1 - Card inserted
#define MECR_NOS			BIT0					// Number-of-Sockets, 0 - 1 Socket, 1 - 2 Sockets

// Read-Only Boot-time register. Contains BOOT_SEL and PKG_SEL values.
#define BOOTDEF_PKG_TYPE	BIT3					// Processor type. 1 - PXA250 application processor
#define BOOTDEF_BOOT_SEL	0x7						// BOOT_SEL[2:0] pins

