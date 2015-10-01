/*----------------------------------------------------------------------------
 *      LED CUBE 8x8x8
 *			Copyright 2014
 *			Luka Penger
 *			LPProjects
 *			http://lpprojects.eu
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include <RTL.h>
#include <Net_Config.h>
#include <LPC17xx.H>
#include <string.h>
#include <stdlib.h>
#include <DELAY.h>
#include <rl_usb.h>
#include <LED_CUBE_8x8x8.h>
#include <UART.h>
#include <PROTOCOL.h>
#include <TCP_USERS.h>
#include <RTC.h>
#include <SNTP.h>
#include <SETTINGS.h>
#include <ADMINS.h>
#include <USERS.h>

/*--------------------------- device configuration --------------------------*/

#define STATUS_LED1_PIN													25
#define STATUS_LED2_PIN													26

#define UART_CONSOLE_NUMBER											0
#define UART_CONSOLE_BAUD_RATE									115200

#define UDP_PORT																10023
#define TCP_PORT																10023

/*---------------------------------------------------------------------------*/

char *AnimationFileName;
BOOL ANIMATION_PLAY = FALSE;
int AnimationFileSize = 0;
int AnimationEffectsCount = 0;
int CurrentAnimationEffect = 0;
LED_CUBE_Effect currentEffect;

char DelayValue = 0;

U8 UDP_Socket;
U8 TCP_Socket;

BOOL TICK_10MS;
BOOL TICK_100MS;
BOOL DHCP_TICK;
BOOL DHCP_SUCCESS;

extern struct http_cfg http_config;
#define HTTP_ADMIN_PASSWORD http_config.Passw

extern LOCALM localm[];                       /* Local Machine Settings */
#define DEVICE_IP localm[NETIF_ETH].IpAdr
#define DEVICE_SUBNETMASK localm[NETIF_ETH].NetMask
#define DEVICE_GATEWAY localm[NETIF_ETH].DefGW
#define DEVICE_PriDNS localm[NETIF_ETH].PriDNS
#define DEVICE_SecDNS localm[NETIF_ETH].SecDNS

/*--------------------------- TCP USER SESSIONS ---------------------------------*/

extern TCP_USER_INFO TCP_USER_SESSIONS[TCP_USER_NUMBER_OF_SESSIONS];
extern char TCP_Buffer_Send[TCP_BUFFER_SEND_SIZE];
extern int TCP_Buffer_Send_Length;

/*--------------------------- SETTINGS --------------------------------------*/

extern char *SETTINGS_DATA[SETTINGS_STRINGS_NUMBER];

/*--------------------------- USERS -----------------------------------------*/

extern USER Users[MAX_NUMBER_OF_USERS];
extern int USERS_Count(void);

/*--------------------------- ADMINS ----------------------------------------*/

extern ADMIN Admins[MAX_NUMBER_OF_ADMINS];
extern int ADMINS_Count(void);

/*--------------------------- flash -----------------------------------------*/

void SPI_FLASH_Format (void) {
	fformat("S:");
}

void SPI_FLASH_Delete_All_Files (void) {
	FINFO file_info;
	file_info.fileID = 0;
	
	while(ffind("*.*", &file_info) == 0) {
		fdelete((const char*)file_info.name); 
	}
}

/*--------------------------- uart console ----------------------------------*/

extern volatile unsigned int UART_Status[2];
extern volatile unsigned char UART_TxEmpty[2];
extern volatile unsigned char UART_Buffer[2][UART_BUFSIZE];
extern volatile unsigned int UART_Count[2];

void UART_CONSOLE_Init (void) {
	UART_Init(UART_CONSOLE_NUMBER, UART_CONSOLE_BAUD_RATE);
}

void UART_CONSOLE_Send_Buffer (char *buffer, unsigned int length) {
	UART_SendBuffer(UART_CONSOLE_NUMBER, buffer, length);
}

void UART_CONSOLE_Send_String (char *string) {
	UART_SendBuffer(UART_CONSOLE_NUMBER, string, strlen(string));
}

void UART_CONSOLE_Send_Char (char value) {
	UART_SendChar(UART_CONSOLE_NUMBER, value);
}

/*--------------------------- status leds -----------------------------------*/

void Status_LEDs_Init (void) {
	LPC_GPIO3->FIODIR |= (1<<STATUS_LED1_PIN);
	LPC_GPIO3->FIODIR |= (1<<STATUS_LED2_PIN);
	
	LPC_GPIO3->FIOSET |= (1<<STATUS_LED1_PIN);
	LPC_GPIO3->FIOSET |= (1<<STATUS_LED2_PIN);
}

void Status_LED1_Set (BOOL state) {
	if (state) {
		LPC_GPIO3->FIOCLR |= (1<<STATUS_LED1_PIN);
	} else {
		LPC_GPIO3->FIOSET |= (1<<STATUS_LED1_PIN);
	}
}

void Status_LED2_Set (BOOL state) {
	if (state) {
		LPC_GPIO3->FIOCLR |= (1<<STATUS_LED2_PIN);
	} else {
		LPC_GPIO3->FIOSET |= (1<<STATUS_LED2_PIN);
	}
}

void Status_LED1_Toggle (void) {
	Status_LED1_Set((LPC_GPIO3->FIOPIN & (1<<STATUS_LED1_PIN)));
}

void Status_LED2_Toggle (void) {
	Status_LED2_Set((LPC_GPIO3->FIOPIN & (1<<STATUS_LED2_PIN)));
}

/*--------------------------- udp socket ------------------------------------*/

U8 UDP_Socket;

char UDP_Socket_Buffer_Send[100];
char UDP_Socket_Buffer_Receive[100];
int UDP_Socket_Receive_Length = 0;
int UDP_Socket_Send_Length = 0;
BOOL UDP_Socket_Listener_Data_Received = FALSE;
char UDP_Socket_Remote_IP[4];

void UDP_Socket_Send (char udp_msg[], int len, char remip[])
{
	U8 *sendbuf;
	sendbuf = udp_get_buf (len);
	memcpy(sendbuf,udp_msg,len);
	udp_send(UDP_Socket, (U8 *)remip, UDP_PORT, sendbuf, len);
}

U16 UDP_Socket_Listener (U8 socket, U8 *remip, U16 port, U8 *buffer, U16 len)
{
	if (len <= sizeof(UDP_Socket_Buffer_Receive))
	{
		memcpy(UDP_Socket_Remote_IP, remip, 4); // Save remote ip
		memcpy(UDP_Socket_Buffer_Receive, buffer, len);
		UDP_Socket_Receive_Length = len;
		UDP_Socket_Listener_Data_Received = TRUE;
	}
	
  return TRUE;
}

void UDP_Socket_Init (void) {
	UDP_Socket = udp_get_socket(0, UDP_OPT_SEND_CS | UDP_OPT_CHK_CS, UDP_Socket_Listener);
	udp_open(UDP_Socket, UDP_PORT);
}

/*--------------------------- timer_poll ------------------------------------*/
char timer10s_tick = 0;

void timer_poll (void) {
  /* System tick timer running in poll mode */

  if (SysTick->CTRL & 0x10000) {
    /* Timer tick every 10 ms */
    timer_tick();
		
    DHCP_TICK = __TRUE;
		TICK_10MS = __TRUE;
		
		if (timer10s_tick >= 10) {
			timer10s_tick = 0;
			TICK_100MS = __TRUE;
		} else {
			timer10s_tick++;
		}
  }
}

/*--------------------------- dhcp_check ------------------------------------*/

void DHCP_Check (void) {
  /* Monitor DHCP IP address assignment. */

	if (DHCP_TICK == __TRUE) {
		DHCP_TICK = __FALSE;

		if (mem_test(&DEVICE_IP, 0, IP_ADRLEN) == __FALSE && DHCP_SUCCESS == __FALSE) {
			/* Success, DHCP has already got the IP address. */
			DHCP_SUCCESS = __TRUE;
			return;
		}
	}
}

/*--------------------------- animation -------------------------------------*/

void Animation_Read_Effect (void) {
	FILE *file;

	if (CurrentAnimationEffect <= AnimationEffectsCount) {
		file = fopen(AnimationFileName,"r");
		
		if (file != NULL) {
			fseek(file, (sizeof(LED_CUBE_Effect) * CurrentAnimationEffect), SEEK_SET);
			fread(&currentEffect, 1, sizeof(LED_CUBE_Effect), file);
			
			LED_CUBE_Rows_Set(currentEffect.rows);
			LED_CUBE_Columns_Set(currentEffect.columns[0], currentEffect.columns[1], currentEffect.columns[2], currentEffect.columns[3], currentEffect.columns[4], currentEffect.columns[5], currentEffect.columns[6], currentEffect.columns[7]);
			
			fclose(file);
		}
	}
}

void Animation_Start (void) {
	FILE *file = fopen(AnimationFileName,"r");
	FINFO file_info;
	file_info.fileID = 0;

	CurrentAnimationEffect = 0;
	DelayValue = 0;
	
	if (file != NULL) {
			if (ffind(AnimationFileName, &file_info) == 0) {
				AnimationFileSize = file_info.size;

				if (AnimationFileSize >= sizeof(LED_CUBE_Effect)) {
					ANIMATION_PLAY = TRUE;
					
					AnimationEffectsCount = (AnimationFileSize / sizeof(LED_CUBE_Effect));
					
					Animation_Read_Effect();					
				} else {
					ANIMATION_PLAY = FALSE;
					AnimationFileName = "";
				}
			} else {
				ANIMATION_PLAY = FALSE;
				AnimationFileName = "";
			}

		fclose(file);
	} else {
		ANIMATION_PLAY = FALSE;
		AnimationFileName = "";
	}

	SETTINGS_Save();
}

void Animation_Stop (void) {
	AnimationFileName = "";
	ANIMATION_PLAY = FALSE;
	
	LED_CUBE_Rows_Set(0x00);
	LED_CUBE_Columns_Set(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	
	SETTINGS_Save();
}

/*--------------------------- init ------------------------------------------*/

void Init (void) {
	SystemInit();

	// Setup and enable the SysTick timer for 10ms.
  SysTick->LOAD = (SystemCoreClock / 100) - 1;
  SysTick->CTRL = 0x05;
	
	// Initialize all enabled drives.
  finit(NULL);

	// Init TcpNet
  init_TcpNet();
	
	// UDP Init
	UDP_Socket_Init();
	
	// TCP Users Init
	TCP_Users_Init(TCP_PORT);
	
	// UART Init
	UART_CONSOLE_Init();
	
	// Real time clock init
	RTC_Init();
	
	RTC_Start();

	// Load settings
	SETTINGS_Load();
	
	// Load admins
	ADMINS_Load();
	ADMINS_Create_Default_Admin();

	// Load users
	USERS_Load();

	// Init status leds
	Status_LEDs_Init();
	
	// Init LED CUBE
	LED_CUBE_Init();
	
	UART_CONSOLE_Send_String("Init\n");
}

/*--------------------------- main ------------------------------------------*/

int main (void) {
	//
	// Variables
	//
	char TCP_USER_i = 0;
	TCP_USER_INFO *TCP_USER;
	BOOL TCP_Connected = FALSE;
	
	//
	// Init
	//
  Init();

	// Play saved animation
	if (ANIMATION_PLAY) {
		Animation_Start();
	}
	
	//
	// While
	//

  while (1) {
    timer_poll();
    main_TcpNet();
    DHCP_Check();

		/*****************************************************************************
		** 10 ms timer
		*****************************************************************************/
		
		if (TICK_10MS == __TRUE) {
			TICK_10MS = __FALSE;
			
			if (ANIMATION_PLAY) {
				if (DelayValue >= currentEffect.delay) {
					DelayValue = 0;
					
					if (CurrentAnimationEffect >= AnimationEffectsCount - 1) {
						CurrentAnimationEffect = 0;
					} else {
						CurrentAnimationEffect++;
					}
					
					Animation_Read_Effect();
				} else {
					DelayValue++;
				}
			}
		}
		
		/*****************************************************************************
		** 100 ms timer
		*****************************************************************************/
		
		if (TICK_100MS == __TRUE) {
			TICK_100MS = __FALSE;
			
			if (ANIMATION_PLAY) {
				Status_LED2_Toggle();
			} else {
				Status_LED2_Set(FALSE);
			}
			
			if (TCP_Connected) {
				Status_LED1_Set(TRUE);
			} else {
				Status_LED1_Set(FALSE);
			}
		}
				
		/*****************************************************************************
		** UDP Socket Listener
		*****************************************************************************/
		
		if (UDP_Socket_Listener_Data_Received == TRUE) {
			UDP_Socket_Listener_Data_Received = FALSE; // Clear listener

			switch (UDP_Receive_Check(UDP_Socket_Buffer_Receive, UDP_Socket_Receive_Length)) {
				case PROTOCOL_UDP_ReceiveCheckWhich_search_device:	
						UDP_Socket_Send_Length = UDP_Send_Search_Device(UDP_Socket_Buffer_Send, (char*)DEVICE_IP);
						
						UDP_Socket_Send(UDP_Socket_Buffer_Send, UDP_Socket_Send_Length, UDP_Socket_Remote_IP);
					break;
				default:
					break;
			}
		}
		
		/*****************************************************************************
		** TCP Users Listener
		*****************************************************************************/
		
		TCP_Connected = FALSE;
		
		for (TCP_USER_i=0; TCP_USER_i<TCP_USER_NUMBER_OF_SESSIONS; TCP_USER_i++) {
			TCP_USER = &TCP_USER_SESSIONS[TCP_USER_i];
			
			if (TCP_USER->State == TCP_USER_STATE_CONNECTED) {
				TCP_Connected = TRUE;
			}
			
			/* ------------------- CONNECT ------------------ */
			if (TCP_USER->Connect_Flag == TRUE) {
				TCP_USER->Connect_Flag = FALSE; // Clear interrupt flag

			}

			/* ------------------- DISCONNECT --------------- */
			if (TCP_USER->Disconnect_Flag == TRUE) {
				TCP_USER->Disconnect_Flag = FALSE; // Clear interrupt flag

			}
			
			/* ------------------- RECEIVE ------------------ */
			if (TCP_USER->Received_Flag == TRUE) {
				TCP_USER->Received_Flag = FALSE; // Clear interrupt flag
				
				switch (TCP_Receive_Check(TCP_USER->Buffer_Receive, TCP_USER->Buffer_Receive_Length)) {
					case PROTOCOL_TCP_ReceiveCheckWhich_start_animation:
						AnimationFileName = GetAnimationFileNameFromBuffer(TCP_USER->Buffer_Receive, TCP_USER->Buffer_Receive_Length);
						
						Animation_Start();
						break;
					case PROTOCOL_TCP_ReceiveCheckWhich_stop_animation:
						
						Animation_Stop();
						break;
					case PROTOCOL_TCP_ReceiveCheckWhich_row_set:
						LED_CUBE_Row_Set(TCP_USER->Buffer_Receive[6], TCP_USER->Buffer_Receive[7]);
						break;
					case PROTOCOL_TCP_ReceiveCheckWhich_rows_set:
						LED_CUBE_Rows_Set(TCP_USER->Buffer_Receive[6]);
						break;
					case PROTOCOL_TCP_ReceiveCheckWhich_column_set:
						LED_CUBE_Column_Set(TCP_USER->Buffer_Receive[6], TCP_USER->Buffer_Receive[7]);
						break;
					case PROTOCOL_TCP_ReceiveCheckWhich_columns_set:
						LED_CUBE_Columns_Set(TCP_USER->Buffer_Receive[6], TCP_USER->Buffer_Receive[7], TCP_USER->Buffer_Receive[8], TCP_USER->Buffer_Receive[9],
																 TCP_USER->Buffer_Receive[10], TCP_USER->Buffer_Receive[11], TCP_USER->Buffer_Receive[12], TCP_USER->Buffer_Receive[13]);
						break;
					default:
						break;
				}
			}
		}
		
		/*****************************************************************************
		** UART CONSOLE Listener
		*****************************************************************************/
		
		if (UART_Count[UART_CONSOLE_NUMBER] > 0) {
			UART_RBR_Disable(UART_CONSOLE_NUMBER);
			
			UART_Count[UART_CONSOLE_NUMBER] = 0;
			
			// program

			// ...
			
			// end
			
			UART_RBR_Enable(UART_CONSOLE_NUMBER);
		}
  }
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
