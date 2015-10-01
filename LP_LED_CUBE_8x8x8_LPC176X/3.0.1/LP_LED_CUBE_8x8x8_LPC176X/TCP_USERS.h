/****************************************************************************
	Luka Penger 2014
	TCP USERS
****************************************************************************/
#ifndef __TCP_USERS_H 
#define __TCP_USERS_H

#include <LPC17xx.H>
#include <type.h>
#include <String.h>
#include <RTL.h>

#define TCP_USER_NUMBER_OF_SESSIONS 			2

#define TCP_BUFFER_SEND_SIZE							100
#define TCP_BUFFER_RECEIVE_SIZE						100

#define TCP_USER_STATE_ERROR 							1
#define TCP_USER_STATE_DISCONNECTED 			2
#define TCP_USER_STATE_CONNECTED 					3

typedef struct {
	BOOL Wait_ACK;
	char Socket;
	char State;
	char Buffer_Receive[TCP_BUFFER_RECEIVE_SIZE];
	int Buffer_Receive_Length;
	BOOL Received_Flag;
	BOOL Connect_Flag;
	BOOL Disconnect_Flag;
} TCP_USER_INFO;

void TCP_User_Kill_Session (TCP_USER_INFO *user_s);
char TCP_User_Map_Sessions (U8 socket);
void TCP_Socket_Send_Char (char socket, char data);
void TCP_Socket_Send_Buffer (char socket, char data_buf[], int len);
void TCP_Socket_Send_NewLine (char socket);
void TCP_Users_Init (int tcpPort);

#endif /* end __TCP_USERS_H */
/**************************************************************************
                            End Of File
**************************************************************************/
