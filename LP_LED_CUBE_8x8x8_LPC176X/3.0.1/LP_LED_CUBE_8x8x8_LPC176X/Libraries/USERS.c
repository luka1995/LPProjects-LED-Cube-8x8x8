/****************************************************************************
	Luka Penger 2013
	USERS
****************************************************************************/

#include "USERS.h"

USER Users[MAX_NUMBER_OF_USERS];

USER_Warning USERS_Check_User(USER *user) {
	if(user->Username != NULL && (int)strlen(user->Username) < USER_USERNAME_MIN_LENGTH) {
		return USER_Warning_Error_Username;
	}
	if(user->Password != NULL && (int)strlen(user->Password) < USER_PASSWORD_MIN_LENGTH) {
		return USER_Warning_Error_Password;
	}
	if(user->First_Name != NULL && (int)strlen(user->First_Name) < USER_FIRST_NAME_MIN_LENGTH) {
		return USER_Warning_Error_First_Name;
	}
	if(user->Last_Name != NULL && (int)strlen(user->Last_Name) < USER_LAST_NAME_MIN_LENGTH) {
		return USER_Warning_Error_Last_Name;
	}
	if(user->Email != NULL && (int)strlen(user->Email) < USER_EMAIL_MIN_LENGTH) {
		return USER_Warning_Error_Email;
	}

	return USER_Warning_OK;
}

USER *USERS_User_Create(char *username, char *password, char *first_name, char *last_name, char *email) {
	USER *user = malloc(sizeof(USER));

	strcpy(user->Username, username);
	strcpy(user->Password, password);
	strcpy(user->First_Name, first_name);
	strcpy(user->Last_Name, last_name);
	strcpy(user->Email, email);

	return user;
}

void USERS_User_Clear(USER *user) {
	strcpy(user->Username, "");
	strcpy(user->Password, "");
	strcpy(user->First_Name, "");
	strcpy(user->Last_Name, "");
	strcpy(user->Email, "");

	user->Created = FALSE;
}

void USERS_Save(void) {
	FILE *file;
	int i=0;

	// write new file
	file = fopen(USERS_SAVED_FILE_NAME,"w");
	if(file != NULL) {
		for(i=0; i<MAX_NUMBER_OF_USERS; i++) {
			fwrite(&Users[i], 1, sizeof(USER), file);
		}

		fclose(file);
	}
}

BOOL USERS_Load(void) {
	FILE *file;
	int i=0;
	
	for(i=0; i<MAX_NUMBER_OF_USERS; i++) {
		USERS_User_Clear(&Users[i]);
	}
	
	file = fopen(USERS_SAVED_FILE_NAME,"r");
	if(file != NULL) {
		fread(&Users, 1, sizeof(Users), file);

		fclose(file);
		return TRUE;
	}
	
	return FALSE;
}

int USERS_Count(void) {
	int count = 0;
	int i = 0;
	
	for(i=0; i<MAX_NUMBER_OF_USERS; i++) {
		if((&Users[i])->Created == TRUE) {
			count++;
		}
	}
	
	return count;
}

USER_Warning USERS_Add_User(USER *user) {
	int i=0;
	BOOL arrayFull = TRUE;
	BOOL usernameAlreadyExist = FALSE;
	USER_Warning warning = USER_Warning_OK;

	warning = USERS_Check_User(user);
	
	if(warning == USER_Warning_OK) {
		for(i=0; i<MAX_NUMBER_OF_USERS; i++) {
			if((&Users[i])->Created == FALSE) {
				arrayFull = FALSE;
			}
			
			if(strcmp((&Users[i])->Username, user->Username) == 0) {
				usernameAlreadyExist = TRUE;
			}
		}
		
		if(arrayFull == FALSE) {
			if(usernameAlreadyExist == FALSE) {	
				for(i=0; i<MAX_NUMBER_OF_USERS; i++) {
					if((&Users[i])->Created == FALSE) {
						user->Created = TRUE;

						Users[i] = *user;
						break;
					}
				}
				
				USERS_Save();
			} else {
				warning = USER_Warning_Username_Already_Exist;
			}
		} else {
			warning = USER_Warning_Array_Full;
		}
	}

	return warning;
}

BOOL USERS_Remove_User_By_Username(char *username) {
	int i=0, j=0;
	
	if(username != NULL && strlen(username) > 0) {
		for(i=0; i<USERS_Count(); i++) {
			if((&Users[i])->Created == TRUE && strcmp((&Users[i])->Username, username) == 0) {
				USERS_User_Clear(&Users[i]);

				for(j=i; j<USERS_Count(); j++) {
					Users[j] = Users[j+1];
					USERS_User_Clear(&Users[j+1]);
				}
				
				USERS_Save();
				
				return TRUE;
			}
		}
	}
	
	return FALSE;
}

BOOL USERS_Remove_User_By_Index(int index) {
	int i = 0;
	
	if(index < USERS_Count()) {
		if((&Users[index])->Created == TRUE) {
			USERS_User_Clear(&Users[index]);

			for(i=index; i<USERS_Count(); i++) {
				Users[i] = Users[i+1];
				USERS_User_Clear(&Users[i+1]);
			}
			
			USERS_Save();
			
			return TRUE;
		}
	}
	
	return FALSE;
}

USER *USERS_User_By_Username(char *username) {
	int i=0;
	
	if(username != NULL && strlen(username) > 0) {
		for(i=0; i<USERS_Count(); i++) {
			if((&Users[i])->Created == TRUE && strcmp((&Users[i])->Username, username) == 0) {
				return &Users[i];
			}
		}
	}

	return NULL;
}

void USERS_Remove_All(void) {
	int i=0;
	for(i=0; i<MAX_NUMBER_OF_USERS; i++) {
		USERS_User_Clear(&Users[i]);
	}
	
	USERS_Save();
}

BOOL USERS_Login_Check(USER *user) {
	int i = 0;

	if(strlen(user->Username) > 0 && strlen(user->Password) > 0) {
		for(i=0; i<MAX_NUMBER_OF_USERS; i++) {
			if((&Users[i])->Created == TRUE && strcmp((&Users[i])->Username, user->Username) == 0 && strcmp((&Users[i])->Password, user->Password) == 0) {
				return TRUE;
			}
		}
	}

	return FALSE;
}

/****************************************************************************
                            End Of File
****************************************************************************/
