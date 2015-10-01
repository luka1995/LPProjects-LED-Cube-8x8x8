/****************************************************************************
	Luka Penger 2014
	TCP USERS
****************************************************************************/

#include <TCP_USERS.h>

/*--------------------------- TCP USER SESSIONS ---------------------------------*/

char TCP_Buffer_Send[TCP_BUFFER_SEND_SIZE];
int TCP_Buffer_Send_Length = 0;
TCP_USER_INFO TCP_USER_SESSIONS[TCP_USER_NUMBER_OF_SESSIONS];

void TCP_User_Kill_Session(TCP_USER_INFO *user_s) {
  user_s->State =  TCP_USER_STATE_DISCONNECTED;
	user_s->Wait_ACK = FALSE;
	user_s->Buffer_Receive_Length = 0;
}

char TCP_User_Map_Sessions(U8 socket) {
  int i;
  for (i = 1; i <= TCP_USER_NUMBER_OF_SESSIONS; i++) {
    if (TCP_USER_SESSIONS[i-1].Socket == socket) {
      return (i);
    }
  }
  return (0);
}

void TCP_Socket_Send_Char(char socket, char data) {
	U8 *sendbuf;
	U16 maxlen = 1;

	sendbuf = tcp_get_buf (maxlen);
	memcpy (sendbuf, &data, maxlen);
	tcp_send (socket, sendbuf, maxlen);
}

void TCP_Socket_Send_Buffer(char socket, char data_buf[], int len) {
	U8 *sendbuf;
	U16 maxlen = len;

	sendbuf = tcp_get_buf (maxlen);
	memcpy (sendbuf, data_buf, maxlen);
	tcp_send (socket, sendbuf, maxlen);
}

void TCP_Socket_Send_String(char socket, char *string) {
	U8 *sendbuf;
	U16 maxlen = strlen(string);

	sendbuf = tcp_get_buf (maxlen);
	memcpy (sendbuf, string, maxlen);
	tcp_send (socket, sendbuf, maxlen);
}

void TCP_Socket_Send_NewLine(char socket) {
	TCP_Buffer_Send_Length = 2;
	TCP_Buffer_Send[0] = 0x0D;
	TCP_Buffer_Send[1] = 0x0A;
	TCP_Socket_Send_Buffer(socket, TCP_Buffer_Send, TCP_Buffer_Send_Length);
}

U16 TCP_User_Socket_Listener(U8 socket, U8 event, U8 *buffer, U16 len) {
	TCP_USER_INFO *user_s;
	U8 session;
	
	session =  TCP_User_Map_Sessions(socket);
  if (session == 0) {
    return (__FALSE);
  }

  user_s = &TCP_USER_SESSIONS[session-1];
  switch (event) {
    case TCP_EVT_CONREQ:

      break;
    case TCP_EVT_ABORT:
				TCP_User_Kill_Session(user_s);
		
				user_s->Disconnect_Flag = TRUE;
			break;
    case TCP_EVT_CONNECT:
				user_s->State = TCP_USER_STATE_CONNECTED;

				user_s->Connect_Flag = TRUE;
			break;
    case TCP_EVT_CLOSE:
				TCP_User_Kill_Session(user_s);
		
				user_s->Disconnect_Flag = TRUE;
			break;
    case TCP_EVT_ACK:
				user_s->Wait_ACK = FALSE;
			break;
    case TCP_EVT_DATA:
				if(len <= sizeof(user_s->Buffer_Receive)) {
					memcpy(user_s->Buffer_Receive, buffer, len);
					user_s->Buffer_Receive_Length = len;
					user_s->Received_Flag = TRUE;
				}
			break;
  }
	
  return TRUE;
}

void TCP_Users_Init (int tcpPort) {
  TCP_USER_INFO *user_s;
  int i;

  for (i=0; i<TCP_USER_NUMBER_OF_SESSIONS; i++) {
    user_s = &TCP_USER_SESSIONS[i];
		user_s->Wait_ACK = FALSE;
		user_s->Buffer_Receive_Length = 0;
		user_s->Received_Flag = FALSE;
		user_s->Connect_Flag = FALSE;
		user_s->Disconnect_Flag = FALSE;

    /* Allocate a TCP socket for the session. */
    user_s->Socket = tcp_get_socket (TCP_TYPE_SERVER, 0, 50000, TCP_User_Socket_Listener);
    user_s->State = TCP_USER_STATE_ERROR;
		
    if (user_s->Socket != 0) {
      if (tcp_listen (user_s->Socket, tcpPort) == __TRUE) {
        user_s->State = TCP_USER_STATE_DISCONNECTED;
      }
    }
  }
}

/**************************************************************************
                            End Of File
**************************************************************************/
