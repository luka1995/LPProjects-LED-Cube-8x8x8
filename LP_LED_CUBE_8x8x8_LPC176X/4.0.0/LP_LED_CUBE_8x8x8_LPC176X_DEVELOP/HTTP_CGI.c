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
#include <LED_CUBE_8x8x8.h>


extern char *AnimationFileName;
extern BOOL ANIMATION_PLAY;

extern void Animation_Start (void);
extern void Animation_Stop (void);

/*--------------------------- SETTINGS --------------------------------------*/

extern char *SETTINGS_DATA[SETTINGS_STRINGS_NUMBER];

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

  var = (U8 *)alloc_mem (40);
  do {
    /* Loop through all the parameters. */
    qs = http_get_var (qs, var, 40);
    /* Check the returned string, 'qs' now points to the next. */
    if (var[0] != 0) {
      /* Returned string is non 0-length. */

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
	
	static FINFO file_info;

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
	}
}

/*--------------------------- cgi_func --------------------------------------*/

U16 cgi_func (U8 *env, U8 *buf, U16 buflen, U32 *pcgi) {
  U16 len = 0;
	static FINFO file_info;
	static int file_number;
	char file_size[16];
	
	switch (env[0]) {
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
		// Footer
		case 'Z':
			len += sprintf((char *)buf+len, "<a href='index.cgi'>Animations</a><br> &#149; ");
			break;
	}
	
  return (len);
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
