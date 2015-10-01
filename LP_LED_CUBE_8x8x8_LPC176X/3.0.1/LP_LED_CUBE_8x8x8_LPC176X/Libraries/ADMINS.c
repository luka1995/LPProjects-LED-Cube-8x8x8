/****************************************************************************
	Luka Penger 2013
	ADMINS
****************************************************************************/

#include "ADMINS.h"

ADMIN Admins[MAX_NUMBER_OF_ADMINS];

ADMIN_Warning ADMINS_Check_Admin(ADMIN *admin) {
	if(admin->Username != NULL && (int)strlen(admin->Username) < ADMIN_USERNAME_MIN_LENGTH) {
		return ADMIN_Warning_Error_Username;
	}
	if(admin->Password != NULL && (int)strlen(admin->Password) < ADMIN_PASSWORD_MIN_LENGTH) {
		return ADMIN_Warning_Error_Password;
	}
	if(admin->Email != NULL && (int)strlen(admin->Email) < ADMIN_EMAIL_MIN_LENGTH) {
		return ADMIN_Warning_Error_Email;
	}

	return ADMIN_Warning_OK;
}

ADMIN *ADMINS_Admin_Create(char *username, char *password, char *email) {
	ADMIN *admin = malloc(sizeof(ADMIN));
	
	strcpy(admin->Username, username);
	strcpy(admin->Password, password);
	strcpy(admin->Email, email);

	return admin;
}

void ADMINS_Admin_Clear(ADMIN *admin) {
	strcpy(admin->Username, "");
	strcpy(admin->Password, "");
	strcpy(admin->Email, "");
	admin->Created = FALSE;
}

void ADMINS_Save(void) {
	FILE *file;
	int i=0;

	// write new file
	file = fopen(ADMINS_SAVED_FILE_NAME,"w");
	if(file != NULL) {
		for(i=0; i<MAX_NUMBER_OF_ADMINS; i++) {
			fwrite(&Admins[i], 1, sizeof(ADMIN), file);
		}

		fclose(file);
	}
}

BOOL ADMINS_Load(void) {
	FILE *file;
	int i=0;
	
	for(i=0; i<MAX_NUMBER_OF_ADMINS; i++) {
		ADMINS_Admin_Clear(&Admins[i]);
	}
	
	file = fopen(ADMINS_SAVED_FILE_NAME,"r");
	if(file != NULL) {
		fread(&Admins, 1, sizeof(Admins), file);

		fclose(file);
		return TRUE;
	}
	
	return FALSE;
}

int ADMINS_Count(void) {
	int count = 0;
	int i = 0;
	
	for(i=0; i<MAX_NUMBER_OF_ADMINS; i++) {
		if((&Admins[i])->Created == TRUE) {
			count++;
		}
	}
	
	return count;
}

ADMIN_Warning ADMINS_Add_Admin(ADMIN *admin) {
	int i=0;
	BOOL arrayFull = TRUE;
	BOOL usernameAlreadyExist = FALSE;
	ADMIN_Warning warning = ADMIN_Warning_OK;

	warning = ADMINS_Check_Admin(admin);
	
	if(warning == ADMIN_Warning_OK) {
		for(i=0; i<MAX_NUMBER_OF_ADMINS; i++) {
			if((&Admins[i])->Created == FALSE) {
				arrayFull = FALSE;
			}
			
			if(strcmp((&Admins[i])->Username, admin->Username) == 0) {
				usernameAlreadyExist = TRUE;
			}
		}
		
		if(arrayFull == FALSE) {
			if(usernameAlreadyExist == FALSE) {	
				for(i=0; i<MAX_NUMBER_OF_ADMINS; i++) {
					if((&Admins[i])->Created == FALSE) {
						admin->Created = TRUE;

						Admins[i] = *admin;
						break;
					}
				}
				
				ADMINS_Save();
			} else {
				warning = ADMIN_Warning_Username_Already_Exist;
			}
		} else {
			warning = ADMIN_Warning_Array_Full;
		}
	}

	return warning;
}

BOOL ADMINS_Remove_Admin_By_Username(char *username) {
	int i=0, j=0;
	
	if(username != NULL && strlen(username) > 0) {
		for(i=0; i<ADMINS_Count(); i++) {
			if((&Admins[i])->Created == TRUE && strcmp((&Admins[i])->Username, username) == 0) {
				ADMINS_Admin_Clear(&Admins[i]);

				for(j=i; j<ADMINS_Count(); j++) {
					Admins[j] = Admins[j+1];
					ADMINS_Admin_Clear(&Admins[j+1]);
				}
				
				ADMINS_Save();
				
				return TRUE;
			}
		}
	}
	
	return FALSE;
}

BOOL ADMINS_Remove_Admin_By_Index(int index) {
	int i = 0;
	
	if(index < ADMINS_Count()) {
		if((&Admins[index])->Created == TRUE) {
			ADMINS_Admin_Clear(&Admins[index]);
			
			for(i=index; i<ADMINS_Count(); i++) {
				Admins[i] = Admins[i+1];
				ADMINS_Admin_Clear(&Admins[i+1]);
			}
			
			ADMINS_Save();
			
			return TRUE;
		}
	}
	
	return FALSE;
}

ADMIN *ADMINS_Admin_By_Username(char *username) {
	int i=0;
	
	if(username != NULL && strlen(username) > 0) {
		for(i=0; i<ADMINS_Count(); i++) {
			if((&Admins[i])->Created == TRUE && strcmp((&Admins[i])->Username, username) == 0) {
				return &Admins[i];
			}
		}
	}

	return NULL;
}

ADMIN_Warning ADMINS_Create_Default_Admin(void) {
	ADMIN_Warning warning = ADMIN_Warning_OK;
	ADMIN *admin;
	
	if(ADMINS_Count() == 0) {
		admin = ADMINS_Admin_Create(ADMIN_DEFAULT_USERNAME,
														 ADMIN_DEFAULT_PASSWORD,
														 ADMIN_DEFAULT_EMAIL);

		warning = ADMINS_Add_Admin(admin);
	}
	
	return warning;
}

void ADMINS_Remove_All(void) {
	int i=0;
	for(i=0; i<MAX_NUMBER_OF_ADMINS; i++) {
		ADMINS_Admin_Clear(&Admins[i]);
	}
	
	ADMINS_Save();
}

/****************************************************************************
                            End Of File
****************************************************************************/
