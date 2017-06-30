typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;
typedef volatile unsigned char vuchar;
typedef volatile unsigned short vushort;
typedef volatile unsigned long vulong;
typedef volatile unsigned int vuint;
typedef volatile int vint;
typedef char	byte;
typedef  unsigned int uint;
typedef int                             bool;
typedef ulong		IPaddr_t;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct {
	//char name[32];
	uchar name[32];
	unsigned long base;
	unsigned long size;	
} FlashRegion;

typedef struct {
	int magic;	/* should be filled with 0x646c7470 (btlp)
                           BOOTLDR_PARTITION_MAGIC */
	int npartitions;

	/* the kernel code uses FlashRegion partition[0] over here,
	 * but because we want to allocate a partition table we'll
	 * have to use a certain maximum amount of partitions. */
	FlashRegion partition[16];
} BootldrFlashPartitionTable;


typedef enum {
	VAR_LONG=32,
	VAR_SHORT=16,
	VAR_CHAR=8
} VAR_TYPE;

