/****************************************************************************
	Luka Penger 2013
	SETTINGS
****************************************************************************/

#include <SETTINGS.h>

/*--------------------------------------------------------------------------*/

extern char *AnimationFileName;
extern BOOL ANIMATION_PLAY;

char *SETTINGS_DATA[SETTINGS_STRINGS_NUMBER] = {
	"LP LED Cube 8x8x8",
	"",
	"00:00:00:00:00:00",
	"192.168.2.100",
	"255.255.255.0",
	"192.168.2.1",
	"192.168.2.1",
	"192.168.2.1",
	"1",
	"",
	"0",
};

/*--------------------------------------------------------------------------*/

void SAVE_PARAMETERS_TO_SETTINGS (void) {
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

void LOAD_SETTINGS_TO_PARAMETERS (void) {
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

void SETTINGS_Load (void) {
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
		
		while (fgets(line, sizeof(line), file) != NULL) {
			len = strlen(line);

			line[len-1] = '\0';

			SETTINGS_DATA[i] = malloc(len + 1);
			strcpy(SETTINGS_DATA[i], line);

			i++;

			if (i > SETTINGS_STRINGS_NUMBER) {
				break;
			}
		}

		fclose(file);
		
		LOAD_SETTINGS_TO_PARAMETERS();
	}
}

void SETTINGS_Save (void) {
	FILE *file;
	int i = 0;
	
	SAVE_PARAMETERS_TO_SETTINGS();
	
	file = fopen(SETTINGS_FILE_NAME,"w");
	if (file != NULL) {
		for (i=0; i<SETTINGS_STRINGS_NUMBER; i++) {
			fputs(SETTINGS_DATA[i], file);
			fputs("\n", file);
		}
		
		fclose(file);
	}
}

/****************************************************************************
                            End Of File
****************************************************************************/
