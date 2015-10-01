/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    HTTP_CGI.C
 *      Purpose: HTTP Server CGI Module
 *      Rev.:    V4.20
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2011 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <Net_Config.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <RTL.h>
#include <stdlib.h>
#include <HTML.h>
#include <HELP.h>
#include <SETTINGS.h>
#include <RTC.h>
#include <SNTP.h>
#include <ADMINS.h>
#include <USERS.h>
#include <LED_CUBE_8x8x8.h>


extern char *AnimationFileName;
extern BOOL ANIMATION_PLAY;

extern void Animation_Start (void);
extern void Animation_Stop (void);
	
/*--------------------------- SETTINGS --------------------------------------*/

extern char *SETTINGS_DATA[SETTINGS_STRINGS_NUMBER];

/*--------------------------- USERS -----------------------------------------*/

extern USER Users[MAX_NUMBER_OF_USERS];
extern int USERS_Count(void);

/*--------------------------- ADMINS ----------------------------------------*/

extern ADMIN Admins[MAX_NUMBER_OF_ADMINS];
extern int ADMINS_Count(void);

/*--------------------------- SNTP ------------------------------------------*/

extern char SNTP_Server_IP_1[4];
extern char SNTP_Server_IP_2[4];

extern BOOL SNTP_Server_IP_1_WORKS;
extern BOOL SNTP_Server_IP_2_WORKS;

extern signed char TIME_ZONE_OFFSET_SELECTED_VALUE;

/*---------------------------------------------------------------------------*/

extern void UART_CONSOLE_Send_String(char *string);
extern void SPI_FLASH_Delete_All_Files(void);

/* ---------------------------------------------------------------------------
 * The HTTP server provides a small scripting language.
 *
 * The script language is simple and works as follows. Each script line starts
 * with a command character, either "i", "t", "c", "#" or ".".
 *   "i" - command tells the script interpreter to "include" a file from the
 *         virtual file system and output it to the web browser.
 *   "t" - command should be followed by a line of text that is to be output
 *         to the browser.
 *   "c" - command is used to call one of the C functions from the this file.
 *         It may be followed by the line of text. This text is passed to
 *         'cgi_func()' as a pointer to environment variable.
 *   "#' - command is a comment line and is ignored (the "#" denotes a comment)
 *   "." - denotes the last script line.
 *
 * --------------------------------------------------------------------------*/
 
extern  LOCALM localm[];
#define LocM   localm[NETIF_ETH]

/* Net_Config.c */
extern struct tcp_cfg   tcp_config;
extern struct http_cfg  http_config;
#define tcp_NumSocks    tcp_config.NumSocks
#define tcp_socket      tcp_config.Scb
#define http_EnAuth     http_config.EnAuth
#define http_auth_passw http_config.Passw

/* My structure of CGI status U32 variable. This variable is private for */
/* each HTTP Session and is not altered by HTTP Server. It is only set to  */
/* zero when the cgi_func() is called for the first time.                  */

typedef struct {
  int number;
	int row;
} PCGI_BUF;

#define PCGIBUF(p)        ((PCGI_BUF *)p)

/*--------------------------- cgx_content_type ------------------------------*/

U8 *cgx_content_type (void) {
	return (U8*)"text/xml; charset=utf-8\r\n";
}

/*--------------------------- cgi_process_var -------------------------------*/

void cgi_process_var (U8 *qs) {
  /* This function is called by HTTP server to process the Querry_String   */
  /* for the CGI Form GET method. It is called on SUBMIT from the browser. */
  /*.The Querry_String.is SPACE terminated.                                */
  U8 *var;
  int s[4];
	
  var = (U8 *)alloc_mem (40);
  do {
    /* Loop through all the parameters. */
    qs = http_get_var (qs, var, 40);
    /* Check the returned string, 'qs' now points to the next. */
    if (var[0] != 0) {
      /* Returned string is non 0-length. */
      if (str_scomp (var, (U8 *)"ip=") == __TRUE) {
        /* My IP address parameter. */
        sscanf ((const char *)&var[3], "%d.%d.%d.%d",&s[0],&s[1],&s[2],&s[3]);
        LocM.IpAdr[0]   = s[0];
        LocM.IpAdr[1]   = s[1];
        LocM.IpAdr[2]   = s[2];
        LocM.IpAdr[3]   = s[3];
      }
      else if (str_scomp (var, (U8 *)"msk=") == __TRUE) {
        /* Net mask parameter. */
        sscanf ((const char *)&var[4], "%d.%d.%d.%d",&s[0],&s[1],&s[2],&s[3]);
        LocM.NetMask[0] = s[0];
        LocM.NetMask[1] = s[1];
        LocM.NetMask[2] = s[2];
        LocM.NetMask[3] = s[3];
				
      }
      else if (str_scomp (var, (U8 *)"gw=") == __TRUE) {
        /* Default gateway parameter. */
        sscanf ((const char *)&var[3], "%d.%d.%d.%d",&s[0],&s[1],&s[2],&s[3]);
        LocM.DefGW[0]   = s[0];
        LocM.DefGW[1]   = s[1];
        LocM.DefGW[2]   = s[2];
        LocM.DefGW[3]   = s[3];
      }
      else if (str_scomp (var, (U8 *)"pdns=") == __TRUE) {
        /* Default gateway parameter. */
        sscanf ((const char *)&var[5], "%d.%d.%d.%d",&s[0],&s[1],&s[2],&s[3]);
        LocM.PriDNS[0]  = s[0];
        LocM.PriDNS[1]  = s[1];
        LocM.PriDNS[2]  = s[2];
        LocM.PriDNS[3]  = s[3];
      }
      else if (str_scomp (var, (U8 *)"sdns=") == __TRUE) {
        /* Default gateway parameter. */
        sscanf ((const char *)&var[5], "%d.%d.%d.%d",&s[0],&s[1],&s[2],&s[3]);
        LocM.SecDNS[0]  = s[0];
        LocM.SecDNS[1]  = s[1];
        LocM.SecDNS[2]  = s[2];
        LocM.SecDNS[3]  = s[3];
      }
    }
  }while (qs);
  free_mem ((OS_FRAME *)var);
}

/*--------------------------- cgi_process_data ------------------------------*/

void cgi_process_data (U8 code, U8 *dat, U16 len) {
  /* This function is called by HTTP server to process the returned Data    */
  /* for the CGI Form POST method. It is called on SUBMIT from the browser. */
  /* Parameters:                                                            */
  /*   code  - callback context code                                        */
  /*           0 = www-url-encoded form data                                */
  /*           1 = filename for file upload (0-terminated string)           */
  /*           2 = file upload raw data                                     */
  /*           3 = end of file upload (file close requested)                */
  /*           4 = any xml encoded POST data (single or last stream)        */
  /*           5 = the same as 4, but with more xml data to follow          */
  /*               Use http_get_content_type() to check the content type    */  
  /*   dat   - pointer to POST received data                                */
  /*   len   - received data length  */ 
  static FILE *f = NULL;
  U32 n;
  U8 *var,*p;
	
	BOOL format_flash = FALSE;
	BOOL settings_save = FALSE;
	
	BOOL sntp_time_configurations_load = FALSE;
	RTC_Time rtc_time;
	BOOL rtc_save = FALSE;
	BOOL add_admin = FALSE, add_user = FALSE;
	
	BOOL save_user = FALSE, delete_user = FALSE, delete_users = FALSE;
	BOOL save_admin = FALSE, delete_admin = FALSE;
	
	int admin_number = 0;
	int user_number = 0;
	USER *user = malloc(sizeof(USER));
	ADMIN *admin = malloc(sizeof(ADMIN));

	static FINFO file_info;

	//ADMIN *admin = malloc(sizeof(ADMIN));
	//USER *user = malloc(sizeof(USER));
	
  switch (code) {
    case 0:
      /* Url encoded form data received. */
      break;
    case 1:
      /* Filename for file upload received as encoded by the browser. */
      /* It might contain an absolute path to a file from the sending */
      /* host. Open a file for writing. */
      var = dat;
      /* Remove path info from filename, keep only the name. */
      for (p = dat; *p; p++) {
        if (*p == '\\') var = p + 1;
      }
      if (*var == 0) {
        /* Send was clicked but a filename was not selected. */
        return;
      }
      /* Filename is OK, initialize the card. */
      if (finit(NULL) != 0) {
        f = NULL;
        return;
      }
      /* Files will be stored to the root directory of SD card. */
      f = fopen ((const char *)var,"w");
      return;
    case 2:
      /* File content data received. Write data to a file. */
      /* This function will be called several times with   */
      /* code 2 when a big file is being uploaded.         */
      if (f != NULL) {
        /* Write in 512 byte blocks. This is the optimal way for */
        /* the FAT FS with caching enabled. For cache buffer     */
        /* size of 4KB the file write speed is 1.2 MByte/sec.    */
        while ((n = len) > 0) {
          if (n > 512) n = 512;
          fwrite (dat,1,n,f);
          dat += n;
          len -= n;
        }
      }
      return;
    case 3:
      /* File upload finished. Close a file. */
      if (f != NULL) {
        fclose (f);
      }
      return;
    default:
      /* Ignore all other codes. */
      return;
  }

  if (len == 0) {
    /* No data or all items (radio, checkbox) are off. */
    return;
  }
	
  var = (U8 *)alloc_mem (40);

  do {
    /* Parse all returned parameters. */
    dat = http_get_var (dat, var, 40);
    if (var[0] != 0) {
			if (str_scomp(var, (const U8*)"file_delete=") == TRUE) { // FILE DELETE
        fdelete((const char *)var+12);
      } else if (str_scomp(var, (const U8*)"format_flash=yes") == TRUE) { // FORMAT FLASH
        format_flash = TRUE;
      } else if (str_scomp(var, (const U8*)"ani_file_delete=") == TRUE) { // ANIMATION FILE DELETE
				if (fdelete((const char *)var+16) == 0) {
					if (ANIMATION_PLAY && strcmp(AnimationFileName, (const char *)var+16) == 0) {
						Animation_Stop();
					}
				}
			} else if (str_scomp(var, (const U8*)"delete_all_ani=yes") == TRUE) {
				while (ffind("*.ani", &file_info) == 0) {
					fdelete((const char*)file_info.name);
				}
			}
			
			// USERS & ADMINS COMMANDS
			if(str_scomp(var, (const U8*)"delete_user=") == TRUE) {
				sscanf((const char *)var+12, "%d", &user_number);
				delete_user = TRUE;
			} else if(str_scomp(var, (const U8*)"delete_users=") == TRUE) {
				delete_users = TRUE;
      } else if(str_scomp(var, (const U8*)"save_user=") == TRUE) {
				sscanf((const char *)var+10, "%d", &user_number);
				save_user = TRUE;
			} else if (str_scomp(var, (const U8*)"add_user=yes") == TRUE) {
				add_user = TRUE;
			}
			
			if(str_scomp(var, (const U8*)"delete_admin=") == TRUE) {
				sscanf((const char *)var+12, "%d", &admin_number);
				delete_admin = TRUE;
      } else if(str_scomp(var, (const U8*)"save_admin=") == TRUE) {
				sscanf((const char *)var+10, "%d", &admin_number);
				save_admin = TRUE;
			} else if (str_scomp(var, (const U8*)"add_admin=yes") == TRUE) {
				add_admin = TRUE;
			}
			
			if(str_scomp(var, (const U8*)"username=") == TRUE) {
				strcpy(user->Username, (const char *)var+9);
				strcpy(admin->Username, (const char *)var+9);
			} else if(str_scomp(var, (const U8*)"password=") == TRUE) {
				strcpy(user->Password, (const char *)var+9);
				strcpy(admin->Password, (const char *)var+9);
			} else if(str_scomp(var, (const U8*)"first_name=") == TRUE) {
				strcpy(user->First_Name, (const char *)var+11);
			} else if(str_scomp(var, (const U8*)"last_name=") == TRUE) {
				strcpy(user->Last_Name, (const char *)var+10);
			} else if(str_scomp(var, (const U8*)"email=") == TRUE) {
				strcpy(user->Email, (const char *)var+6);
				strcpy(admin->Email, (const char *)var+6);
			}
			
			// SNTP TIME COMMANDS
			if(str_scomp(var, (const U8*)"sntp_time_load=yes") == TRUE) {
				sntp_time_configurations_load = TRUE;
				settings_save = TRUE;
			} else if(str_scomp(var, (const U8*)"sntp_ip_1_0=") == TRUE) {
				sscanf((const char *)var+12, "%d", (int*)&SNTP_Server_IP_1[0]);
			} else if(str_scomp(var, (const U8*)"sntp_ip_1_1=") == TRUE) {
				sscanf((const char *)var+12, "%d", (int*)&SNTP_Server_IP_1[1]);
			} else if(str_scomp(var, (const U8*)"sntp_ip_1_2=") == TRUE) {
				sscanf((const char *)var+12, "%d", (int*)&SNTP_Server_IP_1[2]);
			} else if(str_scomp(var, (const U8*)"sntp_ip_1_3=") == TRUE) {
				sscanf((const char *)var+12, "%d", (int*)&SNTP_Server_IP_1[3]);
			} else if(str_scomp(var, (const U8*)"sntp_ip_2_0=") == TRUE) {
				sscanf((const char *)var+12, "%d", (int*)&SNTP_Server_IP_2[0]);
			} else if(str_scomp(var, (const U8*)"sntp_ip_2_1=") == TRUE) {
				sscanf((const char *)var+12, "%d", (int*)&SNTP_Server_IP_2[1]);
			} else if(str_scomp(var, (const U8*)"sntp_ip_2_2=") == TRUE) {
				sscanf((const char *)var+12, "%d", (int*)&SNTP_Server_IP_2[2]);
			} else if(str_scomp(var, (const U8*)"sntp_ip_2_3=") == TRUE) {
				sscanf((const char *)var+12, "%d", (int*)&SNTP_Server_IP_2[3]);
			}
			
			// TIME COMMANDS
			if(str_scomp(var, (const U8*)"time_format=") == TRUE) {
				strcpy(SETTINGS_DATA[TIME_FORMAT], (const char *)var+12);
				settings_save = TRUE;
			} else if(str_scomp(var, (const U8*)"date_format=") == TRUE) {
				strcpy(SETTINGS_DATA[DATE_FORMAT], (const char *)var+12);
				settings_save = TRUE;
			} else if(str_scomp(var, (const U8*)"timezone_offset_select=") == TRUE) {
				TIME_ZONE_OFFSET_SELECTED_VALUE = atoi((const char *)var+23);
				settings_save = TRUE;
			}

			// MANUAL TIME COMMANDS
			if(str_scomp(var, (const U8*)"manual_time=") == TRUE) {
				sscanf((const char *)var+12, "%d:%d", (int*)&rtc_time.Hour, (int*)&rtc_time.Min);
				rtc_save = TRUE;
				settings_save = TRUE;
			} else if(str_scomp(var, (const U8*)"manual_date=") == TRUE) {
				sscanf((const char *)var+12, "%d-%d-%d", (int*)&rtc_time.Year, (int*)&rtc_time.Mon, (int*)&rtc_time.Mday);
				rtc_save = TRUE;
				settings_save = TRUE;
			}
			
			// ANIMATION
			if(str_scomp(var, (const U8*)"animation_start=") == TRUE) {
				AnimationFileName = (char *)malloc(strlen((const char *)var)-15);
				strcpy(AnimationFileName, (const char *)var+16);
				Animation_Start();
			} else if(str_scomp(var, (const U8*)"animation_stop=yes") == TRUE) {
				Animation_Stop();
			}
    }
  } while (dat);
  free_mem ((OS_FRAME *)var);
	
	if (format_flash == TRUE) {
		SPI_FLASH_Delete_All_Files();
	} else if (sntp_time_configurations_load == TRUE) {
		SNTP_Load_Time();
	} else if (rtc_save == TRUE) {
		TIME_ZONE_OFFSET_SELECTED_VALUE = 0;		
		RTC_Set_Time(rtc_time);
	} else if(save_user == TRUE) {
		if(USERS_Check_User(user) == USER_Warning_OK) {
			strcpy((&Users[user_number])->Username, user->Username);
			strcpy((&Users[user_number])->Password, user->Password);
			strcpy((&Users[user_number])->First_Name, user->First_Name);
			strcpy((&Users[user_number])->Last_Name, user->Last_Name);
			strcpy((&Users[user_number])->Email, user->Email);

			USERS_Save();
		}
	}	else if(save_admin == TRUE) {
		if(ADMINS_Check_Admin(admin) == ADMIN_Warning_OK) {
			strcpy((&Admins[admin_number])->Username, admin->Username);
			strcpy((&Admins[admin_number])->Password, admin->Password);
			strcpy((&Admins[admin_number])->Email, admin->Email);

			ADMINS_Save();
		}
	} else if(delete_user == TRUE) {
		USERS_Remove_User_By_Index(user_number);
	} else if(delete_admin == TRUE) {
		ADMINS_Remove_Admin_By_Index(admin_number);
	} else if (add_admin == TRUE) {
		ADMINS_Add_Admin(admin);
	} else if (add_user == TRUE) {
		USERS_Add_User(user);
	} else if(delete_users == TRUE) {
		USERS_Remove_All();
	}
	
	if (settings_save == TRUE) {
		SETTINGS_Save();
	}
	
	free(user);
	free(admin);
}

/*--------------------------- cgi_func --------------------------------------*/

U16 cgi_func (U8 *env, U8 *buf, U16 buflen, U32 *pcgi) {
  U16 len = 0;
	static FINFO file_info;
	static int file_number;
	char file_size[16];
	char currentTimeDate[20];
	ADMIN *admin;
	USER *user;
	
  switch (env[0]) {
    // directory.cgi
    case 'A':
			// List of files
			switch (env[2]) {
				case 'A':
					if (PCGIBUF(pcgi)->number == 0) {
						// First Call, set initial value for 'ffind' function.
						file_info.fileID = 0;
						file_number = 0;
						
						if (finit(NULL) != 0) {
							// No card or failed to initialize.
							break;
						}
					}
					
					switch (PCGIBUF(pcgi)->row) {
						case 0:
							if (ffind("*.*", &file_info) == 0) {
								file_size_format(file_info.size, file_size);
								
								len += sprintf((char *)buf+len, "<tr align='center' bgcolor='#DCDCDC'><td>%d.</td>"
																								"<td align='left'><a href='%s'>%s</a></td>"
																								"<td>%s</td>",
															(file_number + 1), // Number
															file_info.name, file_info.name, // Name
															file_size); // File size

								file_number++;
								PCGIBUF(pcgi)->row++;
								PCGIBUF(pcgi)->number++;
								len |= 0x8000;
							}
							break;
						default:
							len += sprintf((char *)buf+len, "<form method='post'><td><input type='submit' value='Delete'><input type='hidden' name='file_delete' value='%s'/></td></form></tr>",
															file_info.name); // Name

							PCGIBUF(pcgi)->row = 0;
							PCGIBUF(pcgi)->number++;
							len |= 0x8000;
							break;
					}
					break;
			}
      break;
		// index.cgi
		case 'B':
			switch (env[2]) {
				case 'A':
					if (PCGIBUF(pcgi)->number == 0) {
						// First Call, set initial value for 'ffind' function.
						file_info.fileID = 0;
						file_number = 0;
						
						if (finit(NULL) != 0) {
							// No card or failed to initialize.
							break;
						}
					}
					
					switch (PCGIBUF(pcgi)->row) {
						case 0:
							if (ffind("*.ani", &file_info) == 0) {
								file_size_format(file_info.size, file_size);
								
								len += sprintf((char *)buf+len, "<tr align='center'><td class=\"table_data_row\">%d.</td>"
																								"<td align='left' class=\"table_data_row\"><a href='%s'>%s</a></td>"
																								"<td class=\"table_data_row\">%s</td>"
																								"<td class=\"table_data_row\">%d</td>",
															(file_number + 1), // Number
															file_info.name, file_info.name, // Name
															file_size,	// File size
															(file_info.size / sizeof(LED_CUBE_Effect))); // Count

								file_number++;
								PCGIBUF(pcgi)->row++;
								PCGIBUF(pcgi)->number++;
								len |= 0x8000;
							}
							break;
						default:
							len += sprintf((char *)buf+len, "<form method='post'><td class=\"table_data_row\"><input type='submit' value='Delete'><input type='hidden' name='ani_file_delete' value='%s'/></td></form>", file_info.name);
						
							if (ANIMATION_PLAY && strcmp(AnimationFileName, (const char *)file_info.name) == 0) {
								len += sprintf((char *)buf+len, "<form method='post'><td class=\"table_data_row\"><input type='submit' value='Stop'><input type='hidden' name='animation_stop' value='yes'/></td></form></tr>");
							} else {
								len += sprintf((char *)buf+len, "<form method='post'><td class=\"table_data_row\"><input type='submit' value='Start'><input type='hidden' name='animation_start' value='%s'/></td></form></tr>", file_info.name);
							}
							
							PCGIBUF(pcgi)->row = 0;
							PCGIBUF(pcgi)->number++;
							len |= 0x8000;
							break;
					}
					break;
			}
			break;
		// time.cgi
		case 'C':
			switch (env[2]) {
				case 'A':
					switch (env[4]) {
						case '0':
							switch (env[6]) {
								case '0':
									strftime(currentTimeDate, sizeof(currentTimeDate), SETTINGS_DATA[TIME_FORMAT], RTC_Get_TimeInfo(RTC_Get_Time()));
									len += sprintf((char *)buf+len, (const char *)&env[8], currentTimeDate);
									break;
								case '1':
									strftime(currentTimeDate, sizeof(currentTimeDate), SETTINGS_DATA[DATE_FORMAT], RTC_Get_TimeInfo(RTC_Get_Time()));
									len += sprintf((char *)buf+len, (const char *)&env[8], currentTimeDate);
									break;
							}
							break;
					}
					break;
				case 'B':
					switch (env[4]) {
						case '0':
							switch (env[6]) {
								case '0':
									len += sprintf((char *)buf+len, (const char *)&env[8], SETTINGS_DATA[TIME_FORMAT]);
									break;
								case '1':
									len += sprintf((char *)buf+len, (const char *)&env[8], SETTINGS_DATA[DATE_FORMAT]);
									break;
							}
							break;
						case '1': // Time zone offset
							switch (env[6]) {
								case '0':
									switch (env[8]) {
										case '0': if(TIME_ZONE_OFFSET_SELECTED_VALUE == -12) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
										case '1': if(TIME_ZONE_OFFSET_SELECTED_VALUE == -11) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
										case '2': if(TIME_ZONE_OFFSET_SELECTED_VALUE == -10) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
										case '3': if(TIME_ZONE_OFFSET_SELECTED_VALUE == -9) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
										case '4': if(TIME_ZONE_OFFSET_SELECTED_VALUE == -8) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
										case '5': if(TIME_ZONE_OFFSET_SELECTED_VALUE == -7) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
										case '6': if(TIME_ZONE_OFFSET_SELECTED_VALUE == -6) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
										case '7': if(TIME_ZONE_OFFSET_SELECTED_VALUE == -5) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
										case '8': if(TIME_ZONE_OFFSET_SELECTED_VALUE == -4) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
										case '9': if(TIME_ZONE_OFFSET_SELECTED_VALUE == -3) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
									}
									break;
								case '1':
									switch (env[8]) {
										case '0': if(TIME_ZONE_OFFSET_SELECTED_VALUE == -2) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
										case '1': if(TIME_ZONE_OFFSET_SELECTED_VALUE == -1) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
										case '2': if(TIME_ZONE_OFFSET_SELECTED_VALUE == 0) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
										case '3': if(TIME_ZONE_OFFSET_SELECTED_VALUE == 1) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
										case '4': if(TIME_ZONE_OFFSET_SELECTED_VALUE == 2) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
										case '5': if(TIME_ZONE_OFFSET_SELECTED_VALUE == 3) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
										case '6': if(TIME_ZONE_OFFSET_SELECTED_VALUE == 4) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
										case '7': if(TIME_ZONE_OFFSET_SELECTED_VALUE == 5) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
										case '8': if(TIME_ZONE_OFFSET_SELECTED_VALUE == 6) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
										case '9': if(TIME_ZONE_OFFSET_SELECTED_VALUE == 7) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
									}
									break;
								case '2':
									switch (env[8]) {
										case '0': if(TIME_ZONE_OFFSET_SELECTED_VALUE == 8) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
										case '1': if(TIME_ZONE_OFFSET_SELECTED_VALUE == 9) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
										case '2': if(TIME_ZONE_OFFSET_SELECTED_VALUE == 10) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
										case '3': if(TIME_ZONE_OFFSET_SELECTED_VALUE == 11) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
										case '4': if(TIME_ZONE_OFFSET_SELECTED_VALUE == 12) len += sprintf((char *)buf+len, HTML_ATTRIBUTE_SELECTED); break;
									}
									break;
							}
							break;
					}
					break;
				case 'C':
					switch (env[4]) {
						case '0':
							switch (env[6]) {
								case '0':
									len += sprintf((char *)buf+len, (const char *)&env[8], SNTP_Server_IP_1[0]);
									break;
								case '1':
									len += sprintf((char *)buf+len, (const char *)&env[8], SNTP_Server_IP_1[1]);
									break;
								case '2':
									len += sprintf((char *)buf+len, (const char *)&env[8], SNTP_Server_IP_1[2]);
									break;
								case '3':
									len += sprintf((char *)buf+len, (const char *)&env[8], SNTP_Server_IP_1[3]);
									break;
								case '4':
									if(SNTP_Server_IP_1_WORKS) {
										len += sprintf((char *)buf+len,  "<img src=\"status_led_green.png\" class=\"sntp_status_led\"/>");
									} else {
										len += sprintf((char *)buf+len,  "<img src=\"status_led_red.png\" class=\"sntp_status_led\"/>");
									}
									break;
								case '5':
									len += sprintf((char *)buf+len, (const char *)&env[8], SNTP_Server_IP_2[0]);
									break;
								case '6':
									len += sprintf((char *)buf+len, (const char *)&env[8], SNTP_Server_IP_2[1]);
									break;
								case '7':
									len += sprintf((char *)buf+len, (const char *)&env[8], SNTP_Server_IP_2[2]);
									break;
								case '8':
									len += sprintf((char *)buf+len, (const char *)&env[8], SNTP_Server_IP_2[3]);
									break;
								case '9':
									if(SNTP_Server_IP_2_WORKS) {
										len += sprintf((char *)buf+len,  "<img src=\"status_led_green.png\" class=\"sntp_status_led\"/>");
									} else {
										len += sprintf((char *)buf+len,  "<img src=\"status_led_red.png\" class=\"sntp_status_led\"/>");
									}
									break;
							}
							break;
					}
					break;
			}
			break;
		// admins.cgi
		case 'D':
			switch (env[2]) {
				case 'A':
					// Repeat for all admins
					if(PCGIBUF(pcgi)->number < ADMINS_Count() && ADMINS_Count() > 0) {
						//admin = malloc(sizeof(ADMIN));
						admin = &Admins[PCGIBUF(pcgi)->number];

						switch (PCGIBUF(pcgi)->row) {
							case 0:
								len += sprintf((char *)buf+len, "<table class='table_data' style=\"cursor: pointer;\">"
																								"<tr align='left'><td class='table_data_header' onclick=\"toggleTable('table_admin_%d')\">ADMIN %d - %s</td></tr>"
																								"</table>", PCGIBUF(pcgi)->number,
																				(PCGIBUF(pcgi)->number+1), admin->Username);
								PCGIBUF(pcgi)->row++;
								break;
							case 1:
								len += sprintf((char *)buf+len, "<table class='table_data' id='table_admin_%d' style=\"display: none;\"><tr align='left'><form method='post'><td class='table_data_row' width='40%%'>Username *</td><td class='table_data_row'><input type='text' name='username' maxlength='%d' value='%s'/></td></tr>",
																PCGIBUF(pcgi)->number, ADMIN_USERNAME_MAX_LENGTH, admin->Username);
								PCGIBUF(pcgi)->row++;
								break;
							case 2:
								len += sprintf((char *)buf+len, "<tr align='left'><td class='table_data_row'>Password *</td><td class='table_data_row'><input type='text' name='password' maxlength='%d' value='%s'/></td></tr>",
																ADMIN_PASSWORD_MAX_LENGTH, admin->Password);
								PCGIBUF(pcgi)->row++;
								break;
							case 3:
								len += sprintf((char *)buf+len, "<tr align='left'><td class='table_data_row'>E-mail *</td><td class='table_data_row'><input type='text' name='email' maxlength='%d' value='%s'/></td></tr>",
																ADMIN_EMAIL_MAX_LENGTH, admin->Email);
								PCGIBUF(pcgi)->row++;
								break;
							case 4: // save button
								len += sprintf((char *)buf+len, "<tr>"
																								"<td class='table_data_footer' colspan='2' align='center'>"
																								"<input type='hidden' name='save_admin' value='%d'/>",
																PCGIBUF(pcgi)->number);
								PCGIBUF(pcgi)->row++;
								break;
							case 5:
								len += sprintf((char *)buf+len, "<input type='button' value='Save' onclick=\"confirmForm(this.form, 'Are you sure you want to save admin?')\"/>"
																								"</td></form></tr>");
								
								if(ADMINS_Count() > 1) {	
									PCGIBUF(pcgi)->row++;
								} else {
									PCGIBUF(pcgi)->row += 3;
								}
								break;
							case 6: // delete button
								len += sprintf((char *)buf+len, "<tr>"
																								"<form method='post'>"
																								"<td class='table_data_footer' colspan='2' align='center'>"
																								"<input type='hidden' name='delete_admin' value='%d'/>",
																PCGIBUF(pcgi)->number);
								PCGIBUF(pcgi)->row++;
								break;
							case 7:
								len += sprintf((char *)buf+len, "<input type='button' value='Delete' onclick=\"confirmForm(this.form, 'Are you sure you want to delete admin?')\"/>"
																								"</td></form></tr>");
								PCGIBUF(pcgi)->row++;
								break;
							default:
								len += sprintf((char *)buf+len, "</table><br>");
								PCGIBUF(pcgi)->row = 0;
								PCGIBUF(pcgi)->number++;
								break;
						}

						len |= 0x8000;
						
						//free(admin);
					}
					break;
				case 'B':
					switch (env[4]) {
						case '0':
							len += sprintf((char *)buf+len, (const char *)&env[6], ADMIN_USERNAME_MAX_LENGTH);
							break;
						case '1':
							len += sprintf((char *)buf+len, (const char *)&env[6], ADMIN_PASSWORD_MAX_LENGTH);
							break;
						case '2':
							len += sprintf((char *)buf+len, (const char *)&env[6], ADMIN_EMAIL_MAX_LENGTH);
							break;
					}
					break;
			}
			break;
		// users.cgi
		case 'E':
			switch (env[2]) {
				// Users list
				case 'A':				
					// Repeat for all users
					if (PCGIBUF(pcgi)->number < USERS_Count() && USERS_Count() > 0) {
						user = &Users[PCGIBUF(pcgi)->number];

						switch (PCGIBUF(pcgi)->row) {
							case 0:
								len += sprintf((char *)buf+len, "<table class='table_data' style=\"cursor: pointer;\">"
																								"<tr align='left'><td class='table_data_header' onclick=\"toggleTable('table_user_%d')\">USER %d - %s</td></tr>"
																								"</table>", PCGIBUF(pcgi)->number, (PCGIBUF(pcgi)->number+1), user->Username);
								PCGIBUF(pcgi)->row++;
								break;
							case 1:
								len += sprintf((char *)buf+len, "<table class='table_data' id='table_user_%d' style=\"display: none;\"><tr align='left'><form method='post'><td class='table_data_row' width='40%%'>Username *</td><td class='table_data_row'><input type='text' name='username' maxlength='%d' value='%s'/></td></tr>",
																PCGIBUF(pcgi)->number, USER_USERNAME_MAX_LENGTH, user->Username);
								PCGIBUF(pcgi)->row++;
								break;
							case 2:
								len += sprintf((char *)buf+len, "<tr align='left'><td class='table_data_row'>Password *</td><td class='table_data_row'><input type='text' name='password' maxlength='%d' value='%s'/></td></tr>",
																USER_PASSWORD_MAX_LENGTH, user->Password);
								PCGIBUF(pcgi)->row++;
								break;
							case 3:
								len += sprintf((char *)buf+len, "<tr align='left'><td class='table_data_row'>First name *</td><td class='table_data_row'><input type='text' name='first_name' maxlength='%d' value='%s'/></th></tr>",
																sizeof(user->First_Name), user->First_Name);
								PCGIBUF(pcgi)->row++;
								break;
							case 4:
								len += sprintf((char *)buf+len, "<tr align='left'><td class='table_data_row'>Last name *</td><td class='table_data_row'><input type='text' name='last_name' maxlength='%d' value='%s'/></td></tr>",
																sizeof(user->Last_Name), user->Last_Name);
								PCGIBUF(pcgi)->row++;
								break;
							case 5:
								len += sprintf((char *)buf+len, "<tr align='left'><td class='table_data_row'>E-mail *</td><td class='table_data_row'><input type='text' name='email' maxlength='%d' value='%s'/></td></tr>",
																sizeof(user->Email), user->Email);
								PCGIBUF(pcgi)->row++;
								break;
							case 6: // save button
								len += sprintf((char *)buf+len, "<tr>"
																								"<td class='table_data_footer' colspan='2' align='center'>"
																								"<input type='hidden' name='save_user' value='%d'/>",
																PCGIBUF(pcgi)->number);
								PCGIBUF(pcgi)->row++;
								break;
							case 7:
								len += sprintf((char *)buf+len, "<input type='button' value='Save' onclick=\"confirmForm(this.form, 'Are you sure you want to save user?')\"/>"
																								"</td></form></tr>");
								PCGIBUF(pcgi)->row++;
								break;
							case 8: // delete button
								len += sprintf((char *)buf+len, "<tr>"
																								"<form method='post'>"
																								"<td class='table_data_footer' colspan='2' align='center'>"
																								"<input type='hidden' name='delete_user' value='%d'/>",
																PCGIBUF(pcgi)->number);
								PCGIBUF(pcgi)->row++;
								break;
							case 9:
								len += sprintf((char *)buf+len, "<input type='button' value='Delete' onclick=\"confirmForm(this.form, 'Are you sure you want to delete user?')\"/>"
																								"</td></form></tr>");
								PCGIBUF(pcgi)->row++;
								break;
							default:
								len += sprintf((char *)buf+len, "</table><br>");
								PCGIBUF(pcgi)->row = 0;
								PCGIBUF(pcgi)->number++;
								break;
						}

						len |= 0x8000;
					}
					break;
				case 'B':
					switch (env[4]) {
						case '0':
							len += sprintf((char *)buf+len, (const char *)&env[6], USER_USERNAME_MAX_LENGTH);
							break;
						case '1':
							len += sprintf((char *)buf+len, (const char *)&env[6], USER_PASSWORD_MAX_LENGTH);
							break;
						case '2':
							len += sprintf((char *)buf+len, (const char *)&env[6], USER_FIRST_NAME_MAX_LENGTH);
							break;
						case '3':
							len += sprintf((char *)buf+len, (const char *)&env[6], USER_LAST_NAME_MAX_LENGTH);
							break;
						case '4':
							len += sprintf((char *)buf+len, (const char *)&env[6], USER_EMAIL_MAX_LENGTH);
							break;
					}
					break;
			}
			break;
		// Network Settings
		case 'F':
			switch (env[2]) {
				case '0':
					len = sprintf((char *)buf,(const char *)&env[4],LocM.IpAdr[0],
                        LocM.IpAdr[1],LocM.IpAdr[2],LocM.IpAdr[3]);
					break;
				case '1':
					len = sprintf((char *)buf,(const char *)&env[4],LocM.NetMask[0],
                        LocM.NetMask[1],LocM.NetMask[2],LocM.NetMask[3]);
					break;
				case '2':
					len = sprintf((char *)buf,(const char *)&env[4],LocM.DefGW[0],
                        LocM.DefGW[1],LocM.DefGW[2],LocM.DefGW[3]);
					break;
				case '3':
					len = sprintf((char *)buf,(const char *)&env[4],LocM.PriDNS[0],
                        LocM.PriDNS[1],LocM.PriDNS[2],LocM.PriDNS[3]);
					break;
				case '4':
					len = sprintf((char *)buf,(const char *)&env[4],LocM.SecDNS[0],
                        LocM.SecDNS[1],LocM.SecDNS[2],LocM.SecDNS[3]);
					break;
			}
			break;
		// Footer
		case 'Z':
			if (http_get_user_id() == 0) { // Manufacturer
				len += sprintf((char *)buf+len, "<a href='index.cgi'>Home</a> &#149; "
																				"<a href='admins.cgi'>Admins Settings</a> &#149; "
																				"<a href='users.cgi'>Users Settings</a> &#149; "
																				"<a href='time.cgi'>Time Settings</a>  &#149; "
																				"<a href='network.cgi'>Network Settings</a>  &#149; "
																				"<a href='directory.cgi'>Directory</a><br>");
			} else if (http_get_user_id() > 0 && http_get_user_id() <= ADMINS_Count()) { // Admin
				len += sprintf((char *)buf+len, "<a href='index.cgi'>Home</a> &#149; "
																				"<a href='users.cgi'>Users Settings</a> &#149; "
																				"<a href='time.cgi'>Time Settings</a>  &#149; "
																				"<a href='network.cgi'>Network Settings</a><br>");
			}
			break;
  }

  return (len);
}

/*--------------------------- http_check_account ----------------------------*/

U8 http_check_account (U8 *username, U8 *password) {
  // This function checks externally provided user account.
  int i;
	
  for (i=0; i<ADMINS_Count(); i++) {
    if ((&Admins[i])->Created == TRUE && strcmp((char *)username, (&Admins[i])->Username) == 0 &&
        strcmp((char *)password, (&Admins[i])->Password) == 0) {
      return (i+1);
    }
  }
	
	for (i=0; i<USERS_Count(); i++) {
    if ((&Users[i])->Created == TRUE && strcmp((char *)username, (&Users[i])->Username) == 0 &&
        strcmp((char *)password, (&Users[i])->Password) == 0) {
      return (i+1+ADMINS_Count());
    }
  }
	
  // User account does not exist.
  return (0);
}

/*--------------------------- http_file_access ------------------------------*/

BOOL http_file_access (U8 *fname, U8 user_id) {
  // This function checks if file access for the user is allowed. 
  // 'user_id' is the same as returned from htp_check_account().  

	if (user_id == 0) { // manufacturer
		return TRUE;
	} else if (user_id > 0 && user_id <= ADMINS_Count()) { // admins
		if (strcmp((char *)fname, "directory.cgi") == 0) {
			return FALSE;
		} else if (strcmp((char *)fname, "admins.cgi") == 0) {
			return FALSE;
		}
	} else { // user
		if (strcmp((char *)fname, "admins.cgi") == 0) {
			return FALSE;
		} else if(strcmp((char *)fname, "users.cgi") == 0) {
			return FALSE;
		} else if(strcmp((char *)fname, "time.cgi") == 0) {
			return FALSE;
		} else if (strcmp((char *)fname, "directory.cgi") == 0) {
			return FALSE;
		} else if (strcmp((char *)fname, "network.cgi") == 0) {
			return FALSE;
		}
	}
	
  return TRUE;
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
