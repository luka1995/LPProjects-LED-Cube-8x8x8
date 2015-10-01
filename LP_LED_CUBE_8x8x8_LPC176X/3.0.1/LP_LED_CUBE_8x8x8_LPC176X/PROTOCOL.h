/****************************************************************************
	Luka Penger 2014
	Protocol
	Ethernet serial
	LPC17xx
****************************************************************************/

#ifndef __Protocol_H 
#define __Protocol_H

#include <LPC17xx.H>
#include <type.h>
#include <string.h>
#include <stdlib.h>

#define PROTOCOL_Start_Byte1 									0xEE
#define PROTOCOL_Start_Byte2 									0xEE
#define PROTOCOL_Start_Byte3 									0xCC

typedef enum {
	PROTOCOL_UDP_ReceiveCheckWhich_none,
	PROTOCOL_UDP_ReceiveCheckWhich_search_device,
} PROTOCOL_UDP_ReceiveCheckWhich;

typedef enum {
	PROTOCOL_TCP_ReceiveCheckWhich_none,
	PROTOCOL_TCP_ReceiveCheckWhich_start_animation,
	PROTOCOL_TCP_ReceiveCheckWhich_stop_animation,
	PROTOCOL_TCP_ReceiveCheckWhich_row_set,
	PROTOCOL_TCP_ReceiveCheckWhich_rows_set,
	PROTOCOL_TCP_ReceiveCheckWhich_column_set,
	PROTOCOL_TCP_ReceiveCheckWhich_columns_set,
} PROTOCOL_TCP_ReceiveCheckWhich;

// CRC
char CRC_Update(unsigned char icrc, unsigned char data);
char CRC_Calculate(char data[], unsigned int length);

// UDP
PROTOCOL_UDP_ReceiveCheckWhich UDP_Receive_Check(char buffer[], int length);
int UDP_Send_Search_Device(char buffer[], char ipAddressBytes[]);

// TCP
PROTOCOL_TCP_ReceiveCheckWhich TCP_Receive_Check(char buffer[], int length);

// Other
char *GetAnimationFileNameFromBuffer(char buffer[], int length);
char GetRowNumberFromBuffer(char buffer[], int length);

#endif /* end __PROTOCOL_H */
/******************************************************************************
**                            End Of File
******************************************************************************/
