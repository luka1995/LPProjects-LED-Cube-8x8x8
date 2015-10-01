/****************************************************************************
	Luka Penger 2013
	SETTINGS
****************************************************************************/

#include <SETTINGS.h>


extern char *AnimationFileName;
extern BOOL ANIMATION_PLAY;

/*--------------------------- SNTP -----------------------------------------*/

extern char SNTP_Server_IP_1[4];
extern char SNTP_Server_IP_2[4];

extern BOOL SNTP_Server_IP_1_WORKS;
extern BOOL SNTP_Server_IP_2_WORKS;

signed char TIME_ZONE_OFFSET_SELECTED_VALUE = 0;

/*--------------------------------------------------------------------------*/

char *SETTINGS_DATA[SETTINGS_STRINGS_NUMBER] = {
	"LP LED Cube 8x8x8",
	"0.0.0.0",
	"0.0.0.0",
	"%H:%M:%S",
	"%d/%b/%Y",
	"0",
	"0",
	"0",
	"",
	"0",
};

/*--------------------------------------------------------------------------*/

void SAVE_PARAMETERS_TO_SETTINGS(void) {
	char buffer[20];
	// SNTP IP 1
	sprintf(buffer, "%d.%d.%d.%d", SNTP_Server_IP_1[0], SNTP_Server_IP_1[1], SNTP_Server_IP_1[2], SNTP_Server_IP_1[3]);
	SETTINGS_DATA[SNTP_SERVER_IP_1] = malloc(strlen(buffer) + 1);
	strcpy(SETTINGS_DATA[SNTP_SERVER_IP_1], buffer);
	// SNTP IP 2
	sprintf(buffer, "%d.%d.%d.%d", SNTP_Server_IP_2[0], SNTP_Server_IP_2[1], SNTP_Server_IP_2[2], SNTP_Server_IP_2[3]);
	SETTINGS_DATA[SNTP_SERVER_IP_2] = malloc(strlen(buffer) + 1);
	strcpy(SETTINGS_DATA[SNTP_SERVER_IP_2], buffer);
	// TIME ZONE OFFSET
	SETTINGS_DATA[TIME_ZONE_OFFSET_SELECTED] = malloc(4);
	sprintf(buffer, "%d", TIME_ZONE_OFFSET_SELECTED_VALUE);
	strcpy(SETTINGS_DATA[TIME_ZONE_OFFSET_SELECTED], buffer);
	// ANIMATION NAME
	SETTINGS_DATA[PLAYED_ANIMATION_NAME] = malloc(strlen(AnimationFileName));
	strcpy(SETTINGS_DATA[PLAYED_ANIMATION_NAME], AnimationFileName);
	// ANIMATION
	SETTINGS_DATA[PLAYED_ANIMATION] = malloc(1);
	if(ANIMATION_PLAY == TRUE) {
		strcpy(SETTINGS_DATA[PLAYED_ANIMATION], "1");
	} else {
		strcpy(SETTINGS_DATA[PLAYED_ANIMATION], "0");
	}
}

void LOAD_SETTINGS_TO_PARAMETERS(void) {
	// SNTP IP 1
	sscanf(SETTINGS_DATA[SNTP_SERVER_IP_1], "%d.%d.%d.%d", (int*)&SNTP_Server_IP_1[0], (int*)&SNTP_Server_IP_1[1], (int*)&SNTP_Server_IP_1[2], (int*)&SNTP_Server_IP_1[3]);
	// SNTP IP 2
	sscanf(SETTINGS_DATA[SNTP_SERVER_IP_2], "%d.%d.%d.%d", (int*)&SNTP_Server_IP_2[0], (int*)&SNTP_Server_IP_2[1], (int*)&SNTP_Server_IP_2[2], (int*)&SNTP_Server_IP_2[3]);
	// TIME ZONE OFFSET
	TIME_ZONE_OFFSET_SELECTED_VALUE = atoi(SETTINGS_DATA[TIME_ZONE_OFFSET_SELECTED]);
	// ANIMATION NAME
	AnimationFileName = malloc(strlen(SETTINGS_DATA[PLAYED_ANIMATION_NAME]));
	strcpy(AnimationFileName, SETTINGS_DATA[PLAYED_ANIMATION_NAME]);
	// ANIMATION
	if(strcmp(SETTINGS_DATA[PLAYED_ANIMATION], "1") == 0) {
		ANIMATION_PLAY = TRUE;
	} else {
		ANIMATION_PLAY = FALSE;
	}
}

void SETTINGS_Load(void) {
	FILE *file;
	char line[SETTINGS_FILE_LINE_MAX_LENGTH];
	int len=0, i=0;

	file = fopen(SETTINGS_FILE_NAME,"r");
	if (file != NULL) {
		fclose(file);
	} else {
		// CREATE DEFAULT FILE
		
		SETTINGS_Save();
	}

	// READ
	file = fopen(SETTINGS_FILE_NAME,"r");
	if (file != NULL) {
		i = 0;
		len = 0;
		
		while(fgets(line, sizeof(line), file) != NULL) {
			if(line[0] != 0x2F && line[1] != 0x2F && strcmp(line, "\n") != 0 && strcmp(line, "\r\n") != NULL) {
				len = strlen(line);

				line[len-1] = '\0';

				SETTINGS_DATA[i] = malloc(len + 1);
				strcpy(SETTINGS_DATA[i], line);

				i++;

				if(i > SETTINGS_STRINGS_NUMBER) {
					break;
				}
			}
		}

		fclose(file);
		
		LOAD_SETTINGS_TO_PARAMETERS();
	}
}

void SETTINGS_Save(void) {
	FILE *file;
	int i = 0;
	
	SAVE_PARAMETERS_TO_SETTINGS();
	
	file = fopen(SETTINGS_FILE_NAME,"w");
	if (file != NULL) {
		for(i=0; i<SETTINGS_STRINGS_NUMBER; i++) {
			fputs(SETTINGS_DATA[i], file);
			fputs("\n", file);
		}
		
		fclose(file);
	}
}

/****************************************************************************
                            End Of File
****************************************************************************/
