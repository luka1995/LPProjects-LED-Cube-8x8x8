/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    FS_SPI_FLASHPRG.C 
 *      Purpose: Flash Programming Functions - Atmel Data Flash AT45DB321C (SPI)
 *      Rev.:    V4.20
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2011 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <File_Config.h>

/*----------------------------------------------------------------------------
  SPI Flash Driver instance definition
   sf0_drv: First  SPI Flash drive [S0:]
   sf1_drv: Second SPI Flash drive [S1:]
 *----------------------------------------------------------------------------*/

#define __DRV_ID  sf0_drv

/*----------------------------------------------------------------------------
  Local SPI Driver instance definition
   spi0_drv: no MC-SPI mode drives or MC drives in Native mode used
   spi1_drv: M0 used in SPI mode (spi0_drv is reserved for M0:)
 *----------------------------------------------------------------------------*/

#define __SPI     spi0_drv

/* Embedded Flash Driver Interface functions */
static BOOL Init        (U32 adr, U32 clk);
static BOOL UnInit      (void);
static BOOL ReadData    (U32 adr, U32 sz, U8 *buf);
static BOOL ProgramPage (U32 adr, U32 sz, U8 *buf);
static BOOL EraseSector (U32 adr);

/* Embedded Flash Device Driver Control Block */
EFS_DRV __DRV_ID = {
  Init,
  UnInit,
  ReadData,
  ProgramPage,
  EraseSector,
  NULL
};

/* External SPI driver */
extern SPI_DRV    __SPI;
#define spi     (&__SPI)

/* Local definitions */
#define PAGE_SZ         528             /* Page size                   */
#define BLOCK_SZ        (8*PAGE_SZ)     /* Block size (used for erase) */
#define SECT_SZ         (64*BLOCK_SZ)   /* Virtual sector size         */

/* SPI Data Flash Commands */
#define SPI_READ_DATA           0xE8 //uuu0x0B
#define SPI_READ_STATUS         0xD7
#define SPI_BLOCK_ERASE         0x50
#define SPI_BUF1_WRITE          0x84
#define SPI_PAGE_PROGRAM        0x83
#define SPI_PAGE_READ           0x53

/* Local functions */
static void set_adr (U8 *cbuf, U32 adr);
static void spi_write (U8 cmn, U32 adr, U8 *buf, U32 sz);


/*--------------------------- Init ------------------------------------------*/

static BOOL Init (U32 adr, U32 clk)  {
  /* Initialize flash programming functions. */

  if (spi->Init () == __FALSE) {
    /* SPI driver init failed. */
    return (__FALSE);
  }
  /* Set the clock rate to 33 MHz. */
  return (spi->BusSpeed (33000));
}


/*--------------------------- UnInit ----------------------------------------*/

static BOOL UnInit (void)  {
   /* Uninitialize flash programming functions. */

   return (spi->UnInit ());
}


/*--------------------------- ReadData --------------------------------------*/

static BOOL ReadData (U32 adr, U32 sz, U8 *buf)  {
  /* Read a block of Data from Flash Memory. */ 
  U8  cbuf[8];

  cbuf[0] = SPI_READ_DATA;
  set_adr (&cbuf[1], adr);
      
  spi->SetSS (0);
  spi->SendBuf (cbuf, 8);               /* 4 bytes dont care */
  spi->RecBuf (buf, sz);
  spi->SetSS (1);

  return (__TRUE);
}


/*--------------------------- ProgramPage -----------------------------------*/

static BOOL ProgramPage (U32 adr, U32 sz, U8 *buf) {
  /* Program Page in Flash Memory. */ 
  U32 cnt;
  
  while (sz) {
    /* Read Flash Page to Buf 1. */
    spi_write (SPI_PAGE_READ, adr, NULL, 0);

    cnt = PAGE_SZ - (adr % PAGE_SZ);
    if (cnt > sz) cnt = sz;
    spi_write (SPI_BUF1_WRITE, adr, buf, cnt);
    spi_write (SPI_PAGE_PROGRAM, adr, NULL, 0);

    adr += cnt;
    buf += cnt;
    sz  -= cnt;
  }
  return (__TRUE);
}


/*--------------------------- EraseSector -----------------------------------*/

static BOOL EraseSector (U32 adr) {
  /*  Erase Sector in Flash Memory. */
  U32 i;

  /* Virtual sector size is 16 blocks. */
  for (i = 0; i < (SECT_SZ/BLOCK_SZ); i++) {
    spi_write (SPI_BLOCK_ERASE, adr, NULL, 0);
    adr += BLOCK_SZ;
  }
  return (__TRUE);
}


/*--------------------------- spi_write -------------------------------------*/

static void spi_write (U8 cmd, U32 adr, U8 *buf, U32 sz) {
  /* Send SPI Command to Data Flash. */
  U8  sr,cbuf[4];

  cbuf[0] = cmd;
  set_adr (&cbuf[1], adr);
  spi->SetSS (0);
  spi->SendBuf (cbuf, 4);
  if (cmd == SPI_BUF1_WRITE) {
    spi->SendBuf (buf, sz);
  }
  spi->SetSS (1);  

  /* Wait while device is Busy. */
  spi->SetSS (0);
  spi->Send (SPI_READ_STATUS);
  spi->Send (0xFF);                /* dummy byte */
  do {
    sr = spi->Send (0xFF);
  } while ((sr & 0x80) == 0);
  spi->SetSS (1);
}


/*--------------------------- set_adr ---------------------------------------*/

static void set_adr (U8 *cbuf, U32 adr) {
  /* Convert linear address to segmented Data Flash address */
  U32 bl_adr, pg_adr;

  bl_adr = adr / PAGE_SZ;
  pg_adr = adr % PAGE_SZ;

  adr = (bl_adr << 10) | pg_adr;
  cbuf[0] = (U8)(adr >> 16);
  cbuf[1] = (U8)(adr >> 8 );
  cbuf[2] = (U8)(adr >> 0 );
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
