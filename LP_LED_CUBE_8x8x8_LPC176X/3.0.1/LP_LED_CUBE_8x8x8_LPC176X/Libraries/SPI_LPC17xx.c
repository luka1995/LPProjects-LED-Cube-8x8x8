/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    SPI_LPC17xx.c
 *      Purpose: Serial Peripheral Interface Driver for NXP LPC17xx
 *      Rev.:    V4.20
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2011 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <File_Config.h>
#include <LPC17xx.H>                 /* LPC17xx Definitions                  */

/*----------------------------------------------------------------------------
  SPI Driver instance definition
   spi0_drv: First SPI driver
   spi1_drv: Second SPI driver
 *---------------------------------------------------------------------------*/

#define __DRV_ID  spi0_drv
#define __PCLK    100000000

/* SPI Driver Interface functions */
static BOOL Init (void);
static BOOL UnInit (void);
static U8   Send (U8 outb);
static BOOL SendBuf (U8 *buf, U32 sz);
static BOOL RecBuf (U8 *buf, U32 sz);
static BOOL BusSpeed (U32 kbaud);
static BOOL SetSS (U32 ss);
static U32  CheckMedia (void);        /* Optional function for SD card check */

/* SPI Device Driver Control Block */
SPI_DRV __DRV_ID = {
  Init,
  UnInit,
  Send,
  SendBuf,
  RecBuf,
  BusSpeed,
  SetSS,
  CheckMedia                          /* Can be NULL if not existing         */
};


/* SSPxSR - bit definitions. */
#define TFE     0x01
#define TNF     0x02
#define RNE     0x04
#define RFF     0x08
#define BSY     0x10

/*--------------------------- Init ------------------------------------------*/

static BOOL Init (void) {
  /* Initialize and enable the SSP Interface module. */

  LPC_SC->PCONP       |= (1 << 21);           /* Enable power to SSPI0 block */

  /* SSEL is GPIO, output set to high. */
  LPC_GPIO0->FIODIR   |=  (1<<16);            /* P0.16 is output             */
  LPC_GPIO0->FIOPIN   |=  (1<<16);            /* set P0.16 high (SSEL inact.)*/
  LPC_PINCON->PINSEL1 &= ~(3<<0);             /* P0.16 SSEL (used as GPIO)   */

  /* SCK, MISO, MOSI are SSP pins. */
  LPC_PINCON->PINSEL0 &= ~(3UL<<30);          /* P0.15 cleared               */
  LPC_PINCON->PINSEL0 |=  (2UL<<30);          /* P0.15 SCK0                  */
  LPC_PINCON->PINSEL1 &= ~((3<<2) | (3<<4));  /* P0.17, P0.18 cleared        */
  LPC_PINCON->PINSEL1 |=  ((2<<2) | (2<<4));  /* P0.17 MISO0, P0.18 MOSI0    */

  LPC_SC->PCLKSEL1    &= ~(3<<10);            /* PCLKSP0 = CCLK/4 ( 25MHz)   */
  LPC_SC->PCLKSEL1    |=  (1<<10);            /* PCLKSP0 = CCLK   (100MHz)   */

  LPC_SSP0->CPSR       = 250;                 /* 100MHz / 250 = 400kBit      */
                                              /* maximum of 18MHz is possible*/    
  LPC_SSP0->CR0        = 0x0007;              /* 8Bit, CPOL=0, CPHA=0        */
  LPC_SSP0->CR1        = 0x0002;              /* SSP0 enable, master         */

  return (__TRUE);
}


/*--------------------------- UnInit ----------------------------------------*/

static BOOL UnInit (void) {
  /* Return SSP interface to default state. */

  LPC_GPIO0->FIODIR   &=  ~(1<<16);           /* P0.16 is input              */
  LPC_PINCON->PINSEL1 &= ~(3<<0);             /* P0.16 SSEL (used as GPIO)   */ 

  LPC_PINCON->PINSEL0 &= ~(3UL<<30);          /* P0.15 GPIO port 0.15        */
  LPC_PINCON->PINSEL1 &= ~((3<<2) | (3<<4));  /* P0.17 and P0.18  GPIO       */

  LPC_SC->PCLKSEL1    &= ~(3<<10);            /* PCLKSP0 = CCLK/4 ( 25MHz)   */

  LPC_SSP0->CPSR      &= ~0xFF; 
  
  LPC_SSP0->CR0       &= ~0xFFFF;   
  LPC_SSP0->CR1       &= ~0x0F;

  return (__TRUE);
}


/*--------------------------- Send ------------------------------------------*/

static U8 Send (U8 outb) {
  /* Write and Read a byte on SPI interface. */

  LPC_SSP0->DR = outb;
  while (LPC_SSP0->SR & BSY);                 /* Wait for transfer to finish */
  return (LPC_SSP0->DR);                      /* Return received value       */
}


/*--------------------------- SendBuf ---------------------------------------*/

static BOOL SendBuf (U8 *buf, U32 sz) {
  /* Send buffer to SPI interface. */
  U32 i;

  for (i = 0; i < sz; i++) {
    LPC_SSP0->DR = buf[i];
    /* Wait if Tx FIFO is full. */
    while (!(LPC_SSP0->SR & TNF));
    LPC_SSP0->DR;
  }
  /* Wait until Tx finished, drain Rx FIFO. */
  while (LPC_SSP0->SR & (BSY | RNE)) {
    LPC_SSP0->DR;
  }		   
  return (__TRUE);
}


/*--------------------------- RecBuf ----------------------------------------*/

static BOOL RecBuf (U8 *buf, U32 sz) {
  /* Receive SPI data to buffer. */
  U32 i;

  for (i = 0; i < sz; i++) {
    LPC_SSP0->DR = 0xFF; 
    /* Wait while Rx FIFO is empty. */
    while (!(LPC_SSP0->SR & RNE));
    buf[i] = LPC_SSP0->DR;
  }
  return (__TRUE);
}

/*--------------------------- BusSpeed --------------------------------------*/

static BOOL BusSpeed (U32 kbaud) {
  /* Set an SPI clock to required baud rate. */
  U32 div;

  div = (__PCLK/1000 + kbaud - 1) / kbaud;
  if (div == 0)   div = 0x02;
  if (div & 1)    div++;
  if (div > 0xFE) div = 0xFE;
  LPC_SSP0->CPSR = div;
  return (__TRUE);
}


/*--------------------------- SetSS -----------------------------------------*/

static BOOL SetSS (U32 ss) {
  /* Enable/Disable SPI Chip Select (drive it high or low). */

  if (ss) {
    /* SSEL is GPIO, output set to high. */
    LPC_GPIO0->FIOSET = 1<<16;
  } 
  else {
    /* SSEL is GPIO, output set to low. */
    LPC_GPIO0->FIOCLR = 1<<16;
  }
  return (__TRUE);
}


/*--------------------------- CheckMedia ------------------------------------*/

static U32 CheckMedia (void) {
  /* Read CardDetect and WriteProtect SD card socket pins. */
  U32 stat = 0;
 
  if (!(LPC_GPIO4->FIOPIN & (1 << 29))) {
    /* Card is inserted (CD=0). */
    stat |= M_INSERTED;
  } 
#if 0
  if ((LPC_GPIO4->FIOPIN & (1 << 29))) {
    /* Write Protect switch is active (WP=1). */
    stat |= M_PROTECTED;
  }
#endif
  return (stat);
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
