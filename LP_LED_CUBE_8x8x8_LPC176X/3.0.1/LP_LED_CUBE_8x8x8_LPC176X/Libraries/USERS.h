/****************************************************************************
	Luka Penger 2013
	USERS
****************************************************************************/
#ifndef __USERS_H 
#define __USERS_H

#include <stdio.h>
#include <RTL.h>
#include <LPC17xx.H>
#include <string.h>
#include <type.h>
#include <stdlib.h>
#include <HELP.h>

#define USERS_SAVED_FILE_NAME 							"all.users"
#define MAX_NUMBER_OF_USERS 								4

#define USER_USERNAME_MIN_LENGTH						4
#define USER_PASSWORD_MIN_LENGTH						0
#define USER_FIRST_NAME_MIN_LENGTH					4
#define USER_LAST_NAME_MIN_LENGTH						4
#define USER_EMAIL_MIN_LENGTH								4

#define USER_USERNAME_MAX_LENGTH						40
#define USER_PASSWORD_MAX_LENGTH						40
#define USER_FIRST_NAME_MAX_LENGTH					40
#define USER_LAST_NAME_MAX_LENGTH						40
#define USER_EMAIL_MAX_LENGTH								40

typedef enum {
	USER_Warning_OK,
	USER_Warning_Error_Username,
	USER_Warning_Error_Password,
	USER_Warning_Error_First_Name,
	USER_Warning_Error_Last_Name,
	USER_Warning_Error_Email,
	USER_Warning_Username_Already_Exist,
	USER_Warning_Array_Full,
} USER_Warning;

typedef struct {
	BOOL Created;
	char Username[USER_USERNAME_MAX_LENGTH];
	char Password[USER_PASSWORD_MAX_LENGTH];
	char First_Name[USER_FIRST_NAME_MAX_LENGTH];
	char Last_Name[USER_LAST_NAME_MAX_LENGTH];
	char Email[USER_EMAIL_MAX_LENGTH];
} USER;

USER_Warning USERS_Check_User(USER *user);
USER *USERS_User_Create(char *username, char *password, char *first_name, char *last_name, char *email);
void USERS_User_Clear(USER *user);
void USERS_Save(void);
BOOL USERS_Load(void);
int USERS_Count(void);
USER_Warning USERS_Add_User(USER *user);
BOOL USERS_Remove_User_By_Username(char *username);
BOOL USERS_Remove_User_By_Index(int index);
USER *USERS_User_By_Username(char *username);
void USERS_Remove_All(void);
BOOL USERS_Login_Check(USER *user);

#endif /* end __USERS_H */
/****************************************************************************
                            End Of File
****************************************************************************/
