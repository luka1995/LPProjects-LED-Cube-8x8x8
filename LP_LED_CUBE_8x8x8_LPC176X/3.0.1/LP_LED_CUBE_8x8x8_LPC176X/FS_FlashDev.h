/***********************************************************************/
/*  This file is part of the ARM Toolchain package                     */
/*  Copyright KEIL ELEKTRONIK GmbH 2003 - 2008                         */
/***********************************************************************/
/*                                                                     */
/*  FlashDev.H:  Device Description for SST39x320x (16-bit Bus)        */
/*                                                                     */
/* Note: Device fragmented to 64K blocks                               */
/***********************************************************************/

#define FLASH_DEVICE                               \
  DFB(0x10000, 0x010000),    /* Block Size 64kB */ \
  DFB(0x10000, 0x020000),    /* Block Size 64kB */ \
  DFB(0x10000, 0x030000),    /* Block Size 64kB */ \
  DFB(0x10000, 0x040000),    /* Block Size 64kB */ \
  DFB(0x10000, 0x050000),    /* Block Size 64kB */ \
  DFB(0x10000, 0x060000),    /* Block Size 64kB */ \
  DFB(0x10000, 0x070000),    /* Block Size 64kB */ \
  DFB(0x10000, 0x080000),    /* Block Size 64kB */ \
  DFB(0x10000, 0x090000),    /* Block Size 64kB */ \
  DFB(0x10000, 0x0A0000),    /* Block Size 64kB */ \
  DFB(0x10000, 0x0B0000),    /* Block Size 64kB */ \
  DFB(0x10000, 0x0C0000),    /* Block Size 64kB */ \
  DFB(0x10000, 0x0D0000),    /* Block Size 64kB */ \
  DFB(0x10000, 0x0E0000),    /* Block Size 64kB */ \
  DFB(0x10000, 0x0F0000),    /* Block Size 64kB */ \
                                                   \

#define FL_NSECT    15
