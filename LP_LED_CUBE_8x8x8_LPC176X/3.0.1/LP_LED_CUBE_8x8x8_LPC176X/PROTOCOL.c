/****************************************************************************
	Luka Penger 2013
	Protocol
****************************************************************************/

#include "PROTOCOL.h"

/******************************************************************
** CRC Calculation
******************************************************************/

char CRC_Update(unsigned char icrc, unsigned char data) {	
	int i;
	icrc = (unsigned char)(icrc ^ data);

	for(i=0; i<8; i++) {
		if(icrc & 0x01)
			icrc = (unsigned char) ((icrc >> 1) ^ 0x8C);
		else
			icrc = icrc >> 1;
	}
	
	return icrc;
}

char CRC_Calculate(char data[], unsigned int length) {
	int i;
	unsigned char icrc = 0x42;

	for(i=0; i<length; i++)
		icrc = CRC_Update(icrc,data[i]);

	return icrc;
}

/******************************************************************
** UDP Check
******************************************************************/

PROTOCOL_UDP_ReceiveCheckWhich UDP_Receive_Check(char buffer[], int length) {
	if(buffer[0] == PROTOCOL_Start_Byte1 && buffer[1] == PROTOCOL_Start_Byte2 && buffer[2] == PROTOCOL_Start_Byte3) {
		if(CRC_Calculate((char*)buffer, length-1) == buffer[length-1] && (((buffer[3] & 0x00FF) << 8) + buffer[4]) == length) {
			switch (buffer[5]) {
				case 0x00: // Broadcast search device
					return PROTOCOL_UDP_ReceiveCheckWhich_search_device;
			}
		}
	}

	return PROTOCOL_UDP_ReceiveCheckWhich_none;
}

int UDP_Send_Search_Device(char buffer[], char ipAddressBytes[]) {
	int length = 11;
	buffer[0] = PROTOCOL_Start_Byte1;
	buffer[1] = PROTOCOL_Start_Byte2;
	buffer[2] = PROTOCOL_Start_Byte3;
	buffer[3] = (char)(length / 255);
	buffer[4] = (char)(length - (buffer[3] * 255));
	buffer[5] = 0x00; // Function
	buffer[6] = ipAddressBytes[0];
	buffer[7] = ipAddressBytes[1];
	buffer[8] = ipAddressBytes[2];
	buffer[9] = ipAddressBytes[3];
	buffer[length - 1] = CRC_Calculate(buffer, length - 1);
	return length;
}

/******************************************************************
** TCP Check
******************************************************************/

PROTOCOL_TCP_ReceiveCheckWhich TCP_Receive_Check(char buffer[], int length) {
	if(buffer[0] == PROTOCOL_Start_Byte1 && buffer[1] == PROTOCOL_Start_Byte2 && buffer[2] == PROTOCOL_Start_Byte3) {
		if(CRC_Calculate((char*)buffer, length-1) == buffer[length-1] && (((buffer[3] & 0x00FF) << 8) + buffer[4]) == length) {
			switch (buffer[5]) {
				case 0x10: // Start Animation
					return PROTOCOL_TCP_ReceiveCheckWhich_start_animation;
				case 0x11: // Stop Animation
					return PROTOCOL_TCP_ReceiveCheckWhich_stop_animation;
				case 0x12: // Row set
					return PROTOCOL_TCP_ReceiveCheckWhich_row_set;
				case 0x13: // Rows set
					return PROTOCOL_TCP_ReceiveCheckWhich_rows_set;
				case 0x14: // Column set
					return PROTOCOL_TCP_ReceiveCheckWhich_column_set;
				case 0x15: // Columns set
					return PROTOCOL_TCP_ReceiveCheckWhich_columns_set;
			}
		}
	}

	return PROTOCOL_TCP_ReceiveCheckWhich_none;
}

/******************************************************************
** Other
******************************************************************/

char *GetAnimationFileNameFromBuffer(char buffer[], int length) {
	char *string = (char *)malloc(length - 6);
	
	strncpy(string, (char *)buffer + 6, (length - 7));
	string[length - 7] = '\0';

	return string;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
