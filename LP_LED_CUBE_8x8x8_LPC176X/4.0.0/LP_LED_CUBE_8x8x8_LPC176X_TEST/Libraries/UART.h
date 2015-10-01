/****************************************************************************
	Luka Penger 2013
	UART
	LPC17xx
****************************************************************************/
#ifndef __UART_H 
#define __UART_H

#include <LPC17xx.h>
#include "type.h"

#define UART_BUFSIZE 		64

#define UART_IER_RBR		0x01
#define UART_IER_THRE		0x02
#define UART_IER_RLS		0x04

#define UART_IIR_PEND		0x01
#define UART_IIR_RLS		0x03
#define UART_IIR_RDA		0x02
#define UART_IIR_CTI		0x06
#define UART_IIR_THRE		0x01

#define UART_LSR_RDR		0x01
#define UART_LSR_OE			0x02
#define UART_LSR_PE			0x04
#define UART_LSR_FE			0x08
#define UART_LSR_BI			0x10
#define UART_LSR_THRE		0x20
#define UART_LSR_TEMT		0x40
#define UART_LSR_RXFE		0x80

void UART_RBR_Disable(char portNum);
void UART_RBR_Enable(char portNum);
BOOL UART_Init(char portNum, unsigned int baudRate);
void UART_SendChar(char portNum, char value);
void UART_SendBuffer(char portNum, char *buffer, unsigned int length);
char UART_GetChar(char portNum);
extern void UART0_IRQHandler(void);
extern void UART1_IRQHandler(void);

#endif /* end __UART_H */
/***************************************************************************
                            End Of File
***************************************************************************/
