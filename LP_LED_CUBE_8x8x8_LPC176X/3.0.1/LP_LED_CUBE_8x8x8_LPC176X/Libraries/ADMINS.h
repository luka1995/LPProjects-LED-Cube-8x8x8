/****************************************************************************
	Luka Penger 2013
	ADMINS
****************************************************************************/
#ifndef __ADMINS_H 
#define __ADMINS_H

#include <stdio.h>
#include <RTL.h>
#include <LPC17xx.H>
#include <string.h>
#include <type.h>
#include <stdlib.h>
#include <HELP.h>

#define ADMINS_SAVED_FILE_NAME 							"all.admins"
#define MAX_NUMBER_OF_ADMINS 								2

#define ADMIN_DEFAULT_USERNAME							"admin"
#define ADMIN_DEFAULT_PASSWORD							""
#define ADMIN_DEFAULT_EMAIL									"admin@admin.com"

#define ADMIN_USERNAME_MIN_LENGTH						4
#define ADMIN_PASSWORD_MIN_LENGTH						0
#define ADMIN_EMAIL_MIN_LENGTH							4

#define ADMIN_USERNAME_MAX_LENGTH						40
#define ADMIN_PASSWORD_MAX_LENGTH						40
#define ADMIN_EMAIL_MAX_LENGTH							40

typedef enum {
	ADMIN_Warning_OK,
	ADMIN_Warning_Error_Username,
	ADMIN_Warning_Error_Password,
	ADMIN_Warning_Error_Email,
	ADMIN_Warning_Username_Already_Exist,
	ADMIN_Warning_Array_Full,
} ADMIN_Warning;

typedef struct {
	BOOL Created;
	char Username[ADMIN_USERNAME_MAX_LENGTH];
	char Password[ADMIN_PASSWORD_MAX_LENGTH];
	char Email[ADMIN_EMAIL_MAX_LENGTH];
} ADMIN;

ADMIN_Warning ADMINS_Check_Admin(ADMIN *admin);
ADMIN *ADMINS_Admin_Create(char *username, char *password, char *email);
void ADMINS_Admin_Clear(ADMIN *admin);
void ADMINS_Save(void);
BOOL ADMINS_Load(void);
int ADMINS_Count(void);
ADMIN_Warning ADMINS_Add_Admin(ADMIN *admin);
BOOL ADMINS_Remove_Admin_By_Username(char *username);
BOOL ADMINS_Remove_Admin_By_Index(int index);
ADMIN *ADMINS_Admin_By_Username(char *username);
ADMIN_Warning ADMINS_Create_Default_Admin(void);
void ADMINS_Remove_All(void);

#endif /* end __ADMINS_H */
/****************************************************************************
                            End Of File
****************************************************************************/
