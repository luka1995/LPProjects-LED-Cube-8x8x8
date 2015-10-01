/***********************************************************************/
/*  This file is part of the ARM Toolchain package                     */
/*  Copyright KEIL ELEKTRONIK GmbH 2003 - 2008                         */
/***********************************************************************/
/*                                                                     */
/*  FlashDev.H:  Device Description for Atmel 32MBit Serial Flash      */
/*                                            Memory (AT45DB321C)      */
/*                                                                     */
/* Note: Device fragmented to 66K virtual sectors for the FlashFS.     */
/***********************************************************************/

#define SPI_FLASH_DEVICE                             \
	DSB(0x10800, 0x000000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x010800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x021000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x031800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x042000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x052800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x063000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x073800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x084000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x094800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x0A5000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x0B5800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x0C6000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x0D6800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x0E7000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x0F7800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x108000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x118800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x129000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x139800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x14A000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x15A800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x16B000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x17B800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x18C000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x19C800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x1AD000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x1BD800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x1CE000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x1DE800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x1EF000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x1FF800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x210000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x220800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x231000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x241800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x252000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x262800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x273000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x283800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x294000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x2A4800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x2B5000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x2C5800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x2D6000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x2E6800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x2F7000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x307800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x318000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x328800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x339000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x349800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x35A000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x36A800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x37B000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x38B800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x39C000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x3AC800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x3BD000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x3CD800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x3DE000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x3EE800),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x3FF000),     /* Sector Size 66kB */ \
  DSB(0x10800, 0x40F800),     /* Sector Size 66kB */ \

#define SF_NSECT    64

