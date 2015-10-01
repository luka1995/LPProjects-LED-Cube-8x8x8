/****************************************************************************
	Luka Penger 2013
	SETTINGS
****************************************************************************/
#ifndef __SETTINGS_H 
#define __SETTINGS_H

#include <stdio.h>
#include <RTL.h>
#include <LPC17xx.H>
#include <string.h>
#include <type.h>
#include <stdlib.h>
#include <assert.h>
#include <HELP.h>

#define SETTINGS_FILE_NAME											"device.settings"
#define SETTINGS_FILE_LINE_MAX_LENGTH 					200

// STRINGS

#define SETTINGS_STRINGS_NUMBER 								11

#define DEVICE_NAME 														0
#define FIRMWARE_VERSION												1
#define ETHERNET_MAC_ADDRESS										2
#define IP_ADDRESS															3
#define SUBNET_MASK															4
#define DEFAULT_GATEWAY													5
#define PRI_DNS_ADDRESS													6
#define SEC_DNS_ADDRESS													7
#define DHCP_ENABLE															8
#define PLAYED_ANIMATION_NAME										9
#define PLAYED_ANIMATION												10

void SAVE_PARAMETERS_TO_SETTINGS (void);
void LOAD_SETTINGS_TO_PARAMETERS (void);
void SETTINGS_Load (void);
void SETTINGS_Save (void);

#endif /* end __SETTINGS_H */
/****************************************************************************
                            End Of File
****************************************************************************/
