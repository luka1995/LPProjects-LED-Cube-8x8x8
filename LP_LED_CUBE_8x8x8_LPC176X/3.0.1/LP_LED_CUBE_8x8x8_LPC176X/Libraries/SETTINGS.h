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

#define SETTINGS_STRINGS_NUMBER 								10

#define DEVICE_NAME 														0
#define SNTP_SERVER_IP_1												1
#define SNTP_SERVER_IP_2												2
#define TIME_FORMAT															3
#define DATE_FORMAT															4
#define TIME_ZONE_OFFSET_SELECTED								7

#define PLAYED_ANIMATION_NAME										8
#define PLAYED_ANIMATION												9

void SAVE_PARAMETERS_TO_SETTINGS(void);
void LOAD_SETTINGS_TO_PARAMETERS(void);
void SETTINGS_Load(void);
void SETTINGS_Save(void);

#endif /* end __SETTINGS_H */
/****************************************************************************
                            End Of File
****************************************************************************/
