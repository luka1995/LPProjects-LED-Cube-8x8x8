/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    FTP_UIF.C
 *      Purpose: FTP Server User Interface Module
 *      Rev.:    V4.20
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2011 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <Net_Config.h>
#include <File_Config.h>
#include <stdio.h>
#include <rtl.h>
#include <ADMINS.h>
#include <USERS.h>


extern char *AnimationFileName;
extern BOOL ANIMATION_PLAY;

extern void Animation_Start (void);
extern void Animation_Stop (void);

extern void UART_CONSOLE_Send_String(char *string);

/*--------------------------- USERS -----------------------------------------*/

extern USER Users[MAX_NUMBER_OF_USERS];
extern int USERS_Count(void);

/*--------------------------- ADMINS ----------------------------------------*/

extern ADMIN Admins[MAX_NUMBER_OF_ADMINS];
extern int ADMINS_Count(void);

/*----------------------------------------------------------------------------
 * FTP Server File Access CallBack Functions
 *---------------------------------------------------------------------------*/

/*--------------------------- ftp_fopen -------------------------------------*/

void *ftp_fopen (U8 *fname, U8 *mode) {
  /* Open file 'fname' for reading or writing. Return file handle. */
  return (fopen ((const char *)fname, (const char *)mode));
}

/*--------------------------- ftp_fclose ------------------------------------*/

void ftp_fclose (void *file) {
  /* Close the file opened for reading or writing. */
  fclose (file);
}

/*--------------------------- ftp_fread -------------------------------------*/

U16 ftp_fread (void *file, U8 *buf, U16 len) {
  /* Read 'len' bytes from file to buffer 'buf'. The file will be closed, */
  /* when the number of bytes read is less than 'len'. */
  return (fread (buf, 1, len, file));
}

/*--------------------------- ftp_fwrite ------------------------------------*/

U16 ftp_fwrite (void *file, U8 *buf, U16 len) {
  /* Write 'len' bytes from buffer 'buf' to a file. */
  return (fwrite (buf, 1, len, file));
}

/*--------------------------- ftp_fdelete -----------------------------------*/

BOOL ftp_fdelete (U8 *fname) {
  /* Delete a file, return __TRUE on success. */
  if (fdelete((char *)fname) == 0) {

		if (ANIMATION_PLAY && strcmp(AnimationFileName, (const char *)fname + 1) == 0) {
			Animation_Stop();
		}
		
    return (__TRUE);
  }
  return (__FALSE);
}

/*--------------------------- ftp_frename -----------------------------------*/

BOOL ftp_frename (U8 *fname, U8 *newn) {
  /* Rename a file, return __TRUE on success. */
  if (frename((char *)fname, (char *)newn) == 0) {
    return (__TRUE);
  }
  return (__FALSE);
}

/*--------------------------- ftp_ffind -------------------------------------*/

U16 ftp_ffind (U8 code, U8 *buf, U8 *mask, U16 buflen) {
  /* This function is called by the FTP server to find file names and other */
  /* file information. The output data is stored in ascii format to output  */
  /* buffer 'buf' Parameter 'code' specifies requested file information.    */
  /* Values for 'code':                                                     */
  /*    0 - read file size                                                  */
  /*    1 - read last-modified time of a file                               */
  /*    2 - list file names only (first call)                               */
  /*    3 - list file directory in extended format (first call)             */
  /*    4 - list file names only (repeated call)                            */
  /*    5 - list file directory in extended format (repeated call)          */
  static FINFO info;
  U32 rlen,v;
  U8 *tp;

  if (code < 4) {
    /* First call to ffind, initialize the info. */
    info.fileID = 0;
  }

  rlen = 0;
next:
  if ((ftp_get_user_id() == 0 && ffind ((char *)mask, &info) == 0) || (ftp_get_user_id() > 0 && ffind ("*.ani", &info) == 0)) {
    /* File found, print file information. */
    if (info.name[0] == '.') {
      if ((info.name[1] == 0) || (info.name[1] == '.' && info.name[2]) == 0) {
        /* Ignore the '.' and '..' folders. */
        goto next;
      }
    }
    switch (code) {
      case 0:
        /* Return file size as decimal number. */
        rlen = sprintf ((char *)buf,"%d\r\n", info.size);
        break;

      case 1:
        /* Return last-modified time in format "YYYYMMDDhhmmss". */
        rlen  = sprintf ((char *)buf,"%04d%02d%02d",
                         info.time.year, info.time.mon, info.time.day);
        rlen += sprintf ((char *)&buf[rlen],"%02d%02d%02d\r\n",
                         info.time.hr, info.time.min, info.time.sec);
        break;

      case 2:
      case 4:
        /* List file names only. */
        rlen = sprintf ((char *)buf,"%s\r\n", info.name);
        break;

      case 3:
      case 5:
        /* List directory in extended format. */
        rlen  = sprintf ((char *)buf,"%02d-%02d-%02d", 
                         info.time.mon, info.time.day, info.time.year%100);
        /* Convert time to "AM/PM" format. */
        v = info.time.hr % 12;
        if (v == 0) v = 12;
        if (info.time.hr < 12) tp = (U8*)"AM";
        else                   tp = (U8*)"PM";
        rlen += sprintf ((char *)&buf[rlen],"  %02d:%02d%s",v,info.time.min,tp);
        if (info.attrib & ATTR_DIRECTORY) {
          rlen += sprintf ((char *)&buf[rlen],"%-21s","       <DIR>");
        }
        else {
          rlen += sprintf ((char *)&buf[rlen],"%21d", info.size);
        }
        rlen += sprintf ((char *)&buf[rlen]," %s\r\n", info.name);
        break;
    }
  }
  return (rlen);
}

/*--------------------------- ftp_check_account ----------------------------*/

U8 ftp_check_account (U8 code, U8 *id) {
  // This function checks externally provided user account.
  int i;
	
	if (code == 0) {
    /* Check if the username is valid. */
		for (i=0; i<ADMINS_Count(); i++) {
			if ((&Admins[i])->Created == TRUE && strcmp ((char *)id, (&Admins[i])->Username) == 0) {
        return (i+1);
      }
		}
		
		for (i=0; i<USERS_Count(); i++) {
			if ((&Users[i])->Created == TRUE && strcmp ((char *)id, (&Users[i])->Username) == 0) {
        return (i+1+ADMINS_Count());
      }
		}
  } else {
    /* Check the password for user identified with 'code' */
		
		if (code <= ADMINS_Count()) {
			if (strcmp ((char *)id, (&Admins[code-1])->Password) == 0) {
				return (code);
			}
		} else {
			if (strcmp ((char *)id, (&Users[code-1-ADMINS_Count()])->Password) == 0) {
				return (code);
			}
		}
  }
	
  // User account does not exist.
  return (0);
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
