/****************************************************************************
	Luka Penger 2013
	UART
	LPC17xx
****************************************************************************/

#include "UART.h"

volatile unsigned int UART_Status[2];
volatile unsigned char UART_TxEmpty[2] = {1, 1};
volatile unsigned char UART_Buffer[2][UART_BUFSIZE];
volatile unsigned int UART_Count[2] = {0, 0};

void UART_RBR_Disable(char portNum) {
	if(portNum == 0) {
		LPC_UART0->IER = UART_IER_THRE | UART_IER_RLS;			/* Disable RBR */
	} else {
		LPC_UART1->IER = UART_IER_THRE | UART_IER_RLS;			/* Disable RBR */
	}
}

void UART_RBR_Enable(char portNum) {
	if(portNum == 0) {
		LPC_UART0->IER = UART_IER_THRE | UART_IER_RLS | UART_IER_RBR;	/* Re-enable RBR */
	} else {
		LPC_UART1->IER = UART_IER_THRE | UART_IER_RLS | UART_IER_RBR;	/* Re-enable RBR */
	}
}

/*****************************************************************************
** Function name:		UART Init
**
** Descriptions:		Initialize UART port, setup pin select,
**									clock, parity, stop bits, FIFO, etc.
**
** parameters:			portNum(0 or 1) and UART baudrate
** Returned value:	true or false, return false only if the 
**									interrupt handler can't be installed to the 
**									VIC table
** 
*****************************************************************************/

BOOL UART_Init(char portNum, unsigned int baudRate) {
	uint32_t Fdiv;
  uint32_t pclkdiv, pclk;

  if (portNum == 0)
  {
		LPC_PINCON->PINSEL0 &= ~0x000000F0;
		LPC_PINCON->PINSEL0 |= 0x00000050;  /* RxD0 is P0.3 and TxD0 is P0.2 */
		/* By default, the PCLKSELx value is zero, thus, the PCLK for
		all the peripherals is 1/4 of the SystemFrequency. */
		/* Bit 6~7 is for UART0 */
		pclkdiv = (LPC_SC->PCLKSEL0 >> 6) & 0x03;
		switch (pclkdiv)
		{
			case 0x00:
			default:
			pclk = SystemCoreClock/4;
			break;
			case 0x01:
			pclk = SystemCoreClock;
			break; 
			case 0x02:
			pclk = SystemCoreClock/2;
			break; 
			case 0x03:
			pclk = SystemCoreClock/8;
			break;
		}

    LPC_UART0->LCR = 0x83;		/* 8 bits, no Parity, 1 Stop bit */
		Fdiv = ( pclk / 16 ) / baudRate ;	/*baud rate */
    LPC_UART0->DLM = Fdiv / 256;							
    LPC_UART0->DLL = Fdiv % 256;
		LPC_UART0->LCR = 0x03;		/* DLAB = 0 */
    LPC_UART0->FCR = 0x07;		/* Enable and reset TX and RX FIFO. */

   	NVIC_EnableIRQ(UART0_IRQn);

    LPC_UART0->IER = UART_IER_RBR | UART_IER_THRE | UART_IER_RLS;	/* Enable UART0 interrupt */
    return TRUE;
  } else if (portNum == 1) {
		LPC_PINCON->PINSEL4 &= ~0x0000000F;
		LPC_PINCON->PINSEL4 |= 0x0000000A;	/* Enable RxD1 P2.1, TxD1 P2.0 */
		
		/* By default, the PCLKSELx value is zero, thus, the PCLK for
		all the peripherals is 1/4 of the SystemFrequency. */
		/* Bit 8,9 are for UART1 */
		pclkdiv = (LPC_SC->PCLKSEL0 >> 8) & 0x03;
		switch (pclkdiv)
		{
			case 0x00:
			default:
			pclk = SystemCoreClock/4;
			break;
			case 0x01:
			pclk = SystemCoreClock;
			break; 
			case 0x02:
			pclk = SystemCoreClock/2;
			break; 
			case 0x03:
			pclk = SystemCoreClock/8;
			break;
		}

    LPC_UART1->LCR = 0x83;		/* 8 bits, no Parity, 1 Stop bit */
		Fdiv = ( pclk / 16 ) / baudRate ;	/*baud rate */
    LPC_UART1->DLM = Fdiv / 256;							
    LPC_UART1->DLL = Fdiv % 256;
		LPC_UART1->LCR = 0x03;		/* DLAB = 0 */
    LPC_UART1->FCR = 0x07;		/* Enable and reset TX and RX FIFO. */

   	NVIC_EnableIRQ(UART1_IRQn);

    LPC_UART1->IER = UART_IER_RBR | UART_IER_THRE | UART_IER_RLS;	/* Enable UART1 interrupt */
    return TRUE;
  }
	return FALSE;
}

/*****************************************************************************
** Function name:		UART Send char
**
** Descriptions:		Send a block of data to the UART 0 port based
**									on the data length
**
** parameters:			portNum, value
** Returned value:	None
** 
*****************************************************************************/

void UART_SendChar(char portNum, char value) {
	if(portNum == 0)
  {
		/* THRE status, contain valid data */
		while(!(UART_TxEmpty[portNum] & 0x01) );	
		LPC_UART0->THR = value;
		UART_TxEmpty[portNum] = 0;	/* not empty in the THR until it shifts out */
  } else {
		/* THRE status, contain valid data */
		while(!(UART_TxEmpty[portNum] & 0x01) );	
		LPC_UART1->THR = value;
		UART_TxEmpty[portNum] = 0;	/* not empty in the THR until it shifts out */
  }
}

/*****************************************************************************
** Function name:		UART Send buffer
**
** Descriptions:		Send a block of data to the UART 0 port based
**									on the data length
**
** parameters:			portNum, buffer pointer, and data length
** Returned value:	None
** 
*****************************************************************************/

void UART_SendBuffer(char portNum, char *buffer, unsigned int length) {
	while (length != 0)
	{
		UART_SendChar(portNum, *buffer);
		buffer++;
		length--;
	}
}

/*****************************************************************************
** Function name:		UART Read char
**
** Descriptions:		Send a block of data to the UART 0 port based
**									on the data length
**
** parameters:			portNum
** Returned value:	None
** 
*****************************************************************************/

char UART_GetChar(char portNum) {
	if(portNum == 0)
  {
		while (!(LPC_UART0->LSR & 0x01));
		return (LPC_UART0->RBR);
  } else {
		while (!(LPC_UART1->LSR & 0x01));
		return (LPC_UART1->RBR);
  }
}

/*****************************************************************************
** Function name:		UART0_IRQHandler
**
** Descriptions:		UART0 interrupt handler
**
** parameters:			None
** Returned value:	None
** 
*****************************************************************************/

extern void UART0_IRQHandler(void) {
	unsigned char IIRValue, LSRValue;
  unsigned char Dummy = Dummy;
	
  IIRValue = LPC_UART0->IIR;
    
  IIRValue >>= 1;			/* skip pending bit in IIR */
  IIRValue &= 0x07;			/* check bit 1~3, interrupt identification */
	
  if(IIRValue == UART_IIR_RLS)		/* Receive Line Status */
  {
		LSRValue = LPC_UART0->LSR;
		/* Receive Line Status */
		if(LSRValue & (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE | UART_LSR_RXFE | UART_LSR_BI))
		{
			/* There are errors or break interrupt */
			/* Read LSR will clear the interrupt */
			UART_Status[0] = LSRValue;
			Dummy = LPC_UART0->RBR;		/* Dummy read on RX to clear 
								interrupt, then bail out */
			return;
		}
		
		if(LSRValue & UART_LSR_RDR)	/* Receive Data Ready */			
		{
			/* If no error on RLS, normal ready, save into the data buffer. */
			/* Note: read RBR will clear the interrupt */
			UART_Buffer[0][UART_Count[0]] = LPC_UART0->RBR;
			UART_Count[0]++;
			if (UART_Count[0] == UART_BUFSIZE)
			{
				UART_Count[0] = 0;		/* buffer overflow */
			}	
		}
  } else if(IIRValue == UART_IIR_RDA)	{	/* Receive Data Available */
		/* Receive Data Available */
		UART_Buffer[0][UART_Count[0]] = LPC_UART0->RBR;
		UART_Count[0]++;
		
		if(UART_Count[0] == UART_BUFSIZE)
		{
			UART_Count[0] = 0;		/* buffer overflow */
		}
	}	else if (IIRValue == UART_IIR_CTI)	{ /* Character timeout indicator */
		/* Character Time-out indicator */
		UART_Status[0] |= 0x100;		/* Bit 9 as the CTI error */
	} else if(IIRValue == UART_IIR_THRE) { /* THRE, transmit holding register empty */
		/* THRE interrupt */
		LSRValue = LPC_UART0->LSR;		/* Check status in the LSR to see if
										valid data in U0THR or not */
		if (LSRValue & UART_LSR_THRE)
		{
			UART_TxEmpty[0] = 1;
		}
		else
		{
			UART_TxEmpty[0] = 0;
		}
  }
}

/*****************************************************************************
** Function name:		UART1_IRQHandler
**
** Descriptions:		UART1 interrupt handler
**
** parameters:			None
** Returned value:	None
** 
*****************************************************************************/

extern void UART1_IRQHandler(void) {
	unsigned char IIRValue, LSRValue;
  unsigned char Dummy = Dummy;
	
  IIRValue = LPC_UART1->IIR;
    
  IIRValue >>= 1;			/* skip pending bit in IIR */
  IIRValue &= 0x07;			/* check bit 1~3, interrupt identification */
	
  if(IIRValue == UART_IIR_RLS)		/* Receive Line Status */
  {
		LSRValue = LPC_UART1->LSR;
		/* Receive Line Status */
		if(LSRValue & (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE | UART_LSR_RXFE | UART_LSR_BI))
		{
			/* There are errors or break interrupt */
			/* Read LSR will clear the interrupt */
			UART_Status[1] = LSRValue;
			Dummy = LPC_UART1->RBR;		/* Dummy read on RX to clear 
								interrupt, then bail out */
			return;
		}
		
		if(LSRValue & UART_LSR_RDR)	/* Receive Data Ready */			
		{
			/* If no error on RLS, normal ready, save into the data buffer. */
			/* Note: read RBR will clear the interrupt */
			UART_Buffer[1][UART_Count[1]] = LPC_UART1->RBR;
			UART_Count[1]++;
			if (UART_Count[1] == UART_BUFSIZE)
			{
				UART_Count[1] = 0;		/* buffer overflow */
			}	
		}
  } else if(IIRValue == UART_IIR_RDA)	{	/* Receive Data Available */
		/* Receive Data Available */
		UART_Buffer[1][UART_Count[1]] = LPC_UART1->RBR;
		UART_Count[1]++;
		
		if(UART_Count[1] == UART_BUFSIZE)
		{
			UART_Count[1] = 0;		/* buffer overflow */
		}
	}	else if (IIRValue == UART_IIR_CTI)	{ /* Character timeout indicator */
		/* Character Time-out indicator */
		UART_Status[1] |= 0x100;		/* Bit 9 as the CTI error */
	} else if(IIRValue == UART_IIR_THRE) { /* THRE, transmit holding register empty */
		/* THRE interrupt */
		LSRValue = LPC_UART1->LSR;		/* Check status in the LSR to see if
										valid data in U0THR or not */
		if (LSRValue & UART_LSR_THRE)
		{
			UART_TxEmpty[1] = 1;
		}
		else
		{
			UART_TxEmpty[1] = 0;
		}
  }
}

/****************************************************************************
                            End Of File
****************************************************************************/
