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
#include <TCP_USERS.h>
#include <SETTINGS.h>
#include <PROTOCOL.h>
#include <math.h>


#define SOFTWARE_VERSION			"4.0.0"


/*--------------------------- device configuration --------------------------*/

#define RESET_BUTTON_PIN												20

#define STATUS_LED1_PIN													25
#define STATUS_LED2_PIN													26

#define UART_CONSOLE_NUMBER											0
#define UART_CONSOLE_BAUD_RATE									115200

#define UDP_PORT																14350
#define TCP_PORT																14350

/*---------------------------------------------------------------------------*/

extern BOOL ftpFileClose;
extern BOOL ftpFileWrite;
extern U8 *ftpFileOpen;

extern volatile unsigned char cube[8][8];

char *AnimationFileName = "";
BOOL ANIMATION_PLAY = FALSE;
int AnimationFileSize = 0;
int AnimationEffectsCount = 0;
int CurrentAnimationEffect = 0;
LED_CUBE_Effect currentEffect;

unsigned int DelayValue = 0;

U8 UDP_Socket;
U8 TCP_Socket;

BOOL DHCP_TICK;
BOOL DHCP_SUCCESS;
BOOL TICK_1MS;
BOOL TICK_10MS;
BOOL TICK_100MS;
BOOL TICK_1S;

extern struct http_cfg http_config;
#define HTTP_ADMIN_PASSWORD http_config.Passw

extern LOCALM localm[];                       /* Local Machine Settings */
#define DEVICE_IP localm[NETIF_ETH].IpAdr
#define DEVICE_SUBNETMASK localm[NETIF_ETH].NetMask
#define DEVICE_GATEWAY localm[NETIF_ETH].DefGW
#define DEVICE_PriDNS localm[NETIF_ETH].PriDNS
#define DEVICE_SecDNS localm[NETIF_ETH].SecDNS

extern U8 own_hw_adr[ETH_ADRLEN];

/*--------------------------- TCP USER SESSIONS ---------------------------------*/

extern TCP_USER_INFO TCP_USER_SESSIONS[TCP_USER_NUMBER_OF_SESSIONS];
extern char TCP_Buffer_Send[TCP_BUFFER_SEND_SIZE];
extern int TCP_Buffer_Send_Length;

/*--------------------------- SETTINGS --------------------------------------*/

extern char *SETTINGS_DATA[SETTINGS_STRINGS_NUMBER];

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

char UART_DATA_Buffer[100];

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

/*--------------------------- reset button ----------------------------------*/

void Reset_Button_Init (void) {
	LPC_GPIO1->FIODIR &= ~(1<<RESET_BUTTON_PIN);
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

char UDP_Socket_Buffer_Send[100];
char UDP_Socket_Buffer_Receive[100];
int UDP_Socket_Receive_Length = 0;
int UDP_Socket_Send_Length = 0;
BOOL UDP_Socket_Listener_Data_Received = FALSE;
char UDP_Socket_Remote_IP[4];

void UDP_Socket_Send (char udp_msg[], int len, char remip[]) {
	U8 *sendbuf;
	sendbuf = udp_get_buf (len);
	memcpy(sendbuf,udp_msg,len);
	udp_send(UDP_Socket, (U8 *)remip, UDP_PORT, sendbuf, len);
}

U16 UDP_Socket_Listener (U8 socket, U8 *remip, U16 port, U8 *buffer, U16 len) {
	if (len <= sizeof(UDP_Socket_Buffer_Receive)) {
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
volatile int timerLEDCube_tick = 0, timer1ms_tick = 0, timer10ms_tick = 0, timer100ms_tick = 0, timer1s_tick = 0;

void SysTick_Handler (void) {
	// Every 100us

	if (timerLEDCube_tick >= 20) {
		timerLEDCube_tick = 0;
		// Every 2ms
		
		LED_CUBE_Timer();
	} else {
		timerLEDCube_tick++;
	}

	if (timer1ms_tick >= 10) {
		timer1ms_tick = 0;
		// Every 1ms
		
		TICK_1MS = TRUE;
		
		if (timer10ms_tick >= 10) {
			timer10ms_tick = 0;
			// Every 10ms
			
			TICK_10MS = TRUE;
			
			if (timer100ms_tick >= 10) {
				timer100ms_tick = 0;
				// Every 100ms
				
				TICK_100MS = TRUE;
				
				timer_tick();
				DHCP_TICK = __TRUE;
				
				if (timer1s_tick >= 10) {
					timer1s_tick = 0;
					// Every 1s
					
					TICK_1S = TRUE;
				} else {
					timer1s_tick++;
				}
			} else {
				timer100ms_tick++;
			}
		} else {
			timer10ms_tick++;
		}
	} else {
		timer1ms_tick++;
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

/*--------------------------- init ------------------------------------------*/

void Setup_MAC_Address (void) {
	unsigned char data[6];
	memset(data, 0x00, 6);
	
	sscanf(SETTINGS_DATA[ETHERNET_MAC_ADDRESS], "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5]);

	if ((data[0] != 0xFF || data[1] != 0xFF || data[2] != 0xFF || data[3] != 0xFF || data[4] != 0xFF || data[5] != 0xFF) && 
		(data[0] != 0x00 || data[1] != 0x00 || data[2] != 0x00 || data[3] != 0x00 || data[4] != 0x00 || data[5] != 0x00)) {
		own_hw_adr[0] = data[0];
		own_hw_adr[1] = data[1];
		own_hw_adr[2] = data[2];
		own_hw_adr[3] = data[3];
		own_hw_adr[4] = data[4];
		own_hw_adr[5] = data[5];
	}
}

void Setup_Settings (void) {
	unsigned char data[6];
	memset(data, 0x00, 6);
	
	if (strstr(SETTINGS_DATA[DHCP_ENABLE], "0")) {
		dhcp_disable();
	
		sscanf(SETTINGS_DATA[IP_ADDRESS], "%d.%d.%d.%d", (int *)&data[0], (int *)&data[1], (int *)&data[2], (int *)&data[3]);
		memcpy(DEVICE_IP, data, 4);
		memset(data, 0x00, 4);

		sscanf(SETTINGS_DATA[SUBNET_MASK], "%d.%d.%d.%d", (int *)&data[0], (int *)&data[1], (int *)&data[2], (int *)&data[3]);
		memcpy(DEVICE_SUBNETMASK, data, 4);
		memset(data, 0x00, 4);
		
		sscanf(SETTINGS_DATA[DEFAULT_GATEWAY], "%d.%d.%d.%d", (int *)&data[0], (int *)&data[1], (int *)&data[2], (int *)&data[3]);
		memcpy(DEVICE_GATEWAY, data, 4);
		memset(data, 0x00, 4);
		
		
		sscanf(SETTINGS_DATA[PRI_DNS_ADDRESS], "%d.%d.%d.%d", (int *)&data[0], (int *)&data[1], (int *)&data[2], (int *)&data[3]);
		memcpy(DEVICE_PriDNS, data, 4);
		memset(data, 0x00, 4);
		
		sscanf(SETTINGS_DATA[SEC_DNS_ADDRESS], "%d.%d.%d.%d", (int *)&data[0], (int *)&data[1], (int *)&data[2], (int *)&data[3]);
		memcpy(DEVICE_SecDNS, data, 4);
		memset(data, 0x00, 4);
	}
}

void Init (void) {
	SystemInit();

	// Setup and enable the SysTick timer for 100us.
  SysTick_Config((SystemCoreClock / 10000)); // 100us
	
	// Initialize all enabled drives.
  finit(NULL);
	
	// Init status leds
	Status_LEDs_Init();
		
	// UART Init
	UART_CONSOLE_Init();
	
	// Load settings
	SETTINGS_Load();

	// Save FIRMWARE Version to Device Settings file
	SETTINGS_DATA[FIRMWARE_VERSION] = malloc(strlen(SOFTWARE_VERSION));
	strcpy(SETTINGS_DATA[FIRMWARE_VERSION], SOFTWARE_VERSION);
	SETTINGS_Save();
	
	// Setup MAC Address
	Setup_MAC_Address();
	
	// Init TcpNet
  init_TcpNet();

	// Setup Settings
	Setup_Settings();

	// Reset button init
	Reset_Button_Init();
	
	// UDP Init
	UDP_Socket_Init();
	
	// TCP Users Init
	TCP_Users_Init(TCP_PORT);

	// Init LED CUBE
	LED_CUBE_Init();
	
	UART_CONSOLE_Send_String("Init\n");
}

/*--------------------------- animation -------------------------------------*/

void Animation_Read_Effect (void) {
	FILE *file;
	int a = 0, b = 0;
	
	if (CurrentAnimationEffect <= AnimationEffectsCount) {
		file = fopen(AnimationFileName,"r");
		
		if (file != NULL) {
			fseek(file, (sizeof(LED_CUBE_Effect) * CurrentAnimationEffect), SEEK_SET);
			fread(&currentEffect, 1, sizeof(LED_CUBE_Effect), file);
			
			for (a=0; a<8; a++) {
				for (b=0; b<8; b++) {
					cube[a][b] = currentEffect.cube[((a * 8) + b)];
				}
			}

			fclose(file);
		} else {
			for (a=0; a<8; a++) {
				for (b=0; b<8; b++) {
					cube[a][b] = 0x00;
				}
			}
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
	int a = 0, b = 0;
	
	AnimationFileName = "";
	ANIMATION_PLAY = FALSE;
	
	for (a=0; a<8; a++) {
		for (b=0; b<8; b++) {
			cube[a][b] = 0x00;
		}
	}
	
	SETTINGS_Save();
}

int getDelayUnitValue (int delayUnit) {
	switch (delayUnit) {
		case 0:
			return 1;
		case 1:
			return 10;
		case 2:
			return 100;
		case 3:
			return 1000;
		default:
			return 1;
	}
}

/*--------------------------- main ------------------------------------------*/

int main (void) {
	//
	// Variables
	//
	char TCP_USER_i = 0;
	TCP_USER_INFO *TCP_USER;
	BOOL TCP_Connected = FALSE;
	int a = 0, b = 0;
	int RESET_VALUE_SEC = 0;

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
    main_TcpNet();
    DHCP_Check();
		

		if (ftpFileClose == __TRUE && ftpFileWrite == __TRUE) {
			ftpFileClose = __FALSE;
			ftpFileWrite = __FALSE;

			if (strstr((char *)ftpFileOpen, "device.settings")) {
				Delay_ms(2000);
				NVIC_SystemReset();
			}
		}
		
		/*****************************************************************************
		** 1 ms timer
		*****************************************************************************/
		
		if (TICK_1MS == __TRUE) {
			TICK_1MS = __FALSE;
					
			if (ANIMATION_PLAY) {
				if (DelayValue >= ((currentEffect.delay+1) * getDelayUnitValue(currentEffect.delayUnit))) {
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
		** 10 ms timer
		*****************************************************************************/
		
		if (TICK_10MS == __TRUE) {
			TICK_10MS = __FALSE;

		}
		
		/*****************************************************************************
		** 100 ms timer
		*****************************************************************************/
		
		if (TICK_100MS == __TRUE) {
			TICK_100MS = __FALSE;

			/*****************************************************************************
			** reset button
			*****************************************************************************/
			
			if (!(LPC_GPIO1->FIOPIN & (1<<RESET_BUTTON_PIN))) {		
				if (RESET_VALUE_SEC >= 5) {
					RESET_VALUE_SEC = 0;
					
					Status_LED1_Set(TRUE);
					Status_LED2_Set(TRUE);
				
					while (!(LPC_GPIO1->FIOPIN & (1<<RESET_BUTTON_PIN)));
					
					SPI_FLASH_Delete_All_Files();
					NVIC_SystemReset();
					
					Status_LED1_Set(FALSE);
					Status_LED2_Set(FALSE);
				}
			} else {
				RESET_VALUE_SEC = 0;
			}
		}
		
		/*****************************************************************************
		** 1 s timer
		*****************************************************************************/
		
		if (TICK_1S == __TRUE) {
			TICK_1S = __FALSE;

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
			
			if (!(LPC_GPIO1->FIOPIN & (1<<RESET_BUTTON_PIN))) {
				RESET_VALUE_SEC++;
			}
		}
		
		/*****************************************************************************
		** UDP Socket Listener
		*****************************************************************************/
		
		if (UDP_Socket_Listener_Data_Received == TRUE) {
			UDP_Socket_Listener_Data_Received = FALSE; // Clear listener

			switch (UDP_Receive_Check(UDP_Socket_Buffer_Receive, UDP_Socket_Receive_Length)) {
				case PROTOCOL_UDP_ReceiveCheckWhich_search_device:	
					UDP_Socket_Send_Length = UDP_Send_Search_Device(UDP_Socket_Buffer_Send, (char *)DEVICE_IP, (char *)SETTINGS_DATA[DEVICE_NAME]);
					
					UDP_Socket_Send(UDP_Socket_Buffer_Send, UDP_Socket_Send_Length, UDP_Socket_Remote_IP);
					break;
				case PROTOCOL_UDP_ReceiveCheckWhich_cube_set:
					if (ANIMATION_PLAY == FALSE) {
						for (a=0; a<8; a++) {
							for (b=0; b<8; b++) {
								cube[a][b] = UDP_Socket_Buffer_Receive[(((a * 8) + b) + 6)];
							}
						}
					}
					break;
				case PROTOCOL_UDP_ReceiveCheckWhich_reset_device:
					NVIC_SystemReset();
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
					case PROTOCOL_TCP_ReceiveCheckWhich_cube_set:
						if (ANIMATION_PLAY == FALSE) {
							for (a=0; a<8; a++) {
								for (b=0; b<8; b++) {
									cube[a][b] = TCP_USER->Buffer_Receive[(((a * 8) + b)+6)];
								}
							}
						}
						break;
					case PROTOCOL_TCP_ReceiveCheckWhich_start_animation:
						AnimationFileName = GetAnimationFileNameFromBuffer(TCP_USER->Buffer_Receive, TCP_USER->Buffer_Receive_Length);
						
						Animation_Start();
						break;
					case PROTOCOL_TCP_ReceiveCheckWhich_stop_animation:
						
						Animation_Stop();
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
			
			// program


			// end
			
			UART_Count[UART_CONSOLE_NUMBER] = 0;
			
			UART_RBR_Enable(UART_CONSOLE_NUMBER);
		}
  }
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
