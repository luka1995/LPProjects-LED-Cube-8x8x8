/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    TELNET_UIF.C
 *      Purpose: Telnet Server User Interface Module
 *      Rev.:    V4.22
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2011 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <Net_Config.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <Device_Config.h>
#include <Telnet_Commands.h>
#include <Users.h>

/*--------------------------- DEVICE CONFIG ---------------------------------*/

extern DEVICE_CONFIGURATION device_configuration;

/*--------------------------- USERS -----------------------------------------*/

extern char* users[];
extern char* passwords[];

/*--------------------------- NET CONFIG ------------------------------------*/

extern struct tcp_cfg   tcp_config;
extern struct tnet_cfg  tnet_config;
#define tcp_NumSocks    tcp_config.NumSocks
#define tcp_socket      tcp_config.Scb
#define tnet_EnAuth     tnet_config.EnAuth
#define tnet_auth_passw tnet_config.Passw

extern LOCALM localm[];                       /* Local Machine Settings      */
extern SYS_CFG sys_config;

/* ANSI ESC Sequences for terminal control. */
// Colors
#define TBLUE   "\033[37;44m"
#define TNORM   "\033[0m"

/* My structure of a Telnet U32 storage variable. This variable is private */
/* for each Telnet Session and is not altered by Telnet Server. It is only */
/* set to zero when tnet_process_cmd() is called for the first time.       */
typedef struct {
  U8 id;
  U8 nmax;
  U8 idx;
} MY_BUF;
#define MYBUF(p)        ((MY_BUF *)p)

/*----------------------------------------------------------------------------
 *      Telnet CallBack Functions
 *---------------------------------------------------------------------------*/

/*--------------------------- tnet_cbfunc -----------------------------------*/

U16 tnet_cbfunc (U8 code, U8 *buf, U16 buflen) {
  /* This function is called by the Telnet Client to get formated system    */
  /* messages for different code values.                                    */
  /* Values for 'code':                                                     */
  /*    0 - initial header                                                  */
  /*    1 - prompt string                                                   */
  /*    2 - header for login only if authorization is enabled               */
  /*    3 - string 'Username' for login                                     */
  /*    4 - string 'Password' for login                                     */
  /*    5 - message 'Login incorrect'                                       */
  /*    6 - message 'Login timeout'                                         */
  /*    7 - Unsolicited messages from Server (ie. Basic Interpreter)        */
  U16 len = 0;

  switch (code) {
    case 0:
      /* Write initial header after login. */
      len = sprintf((char *)buf, TELNET_CLEAR "\r\n%s\r\nWelcome!\r\n\r\n", device_configuration.long_device_name);
      break;
    case 1:
      /* Write a prompt string. */
			len = sprintf((char *)buf, "\r\n%s#", device_configuration.short_device_name);
      break;
    case 2:
      /* Write Login header. */
      len = sprintf((char *)buf, TELNET_CLEAR "\r\n%s Please login...\r\n", device_configuration.short_device_name);
      break;
    case 3:
      /* Write 'username' prompt. */
      len =  sprintf((char *)buf, "\r\nUsername: ");
      break;
    case 4:
      /* Write 'Password' prompt. */
      len = sprintf((char *)buf, "\r\nPassword: ");
      break;
    case 5:
      /* Write 'Login incorrect'.message. */
      len = sprintf((char *)buf, "\r\nLogin incorrect");
      break;
    case 6:
      /* Write 'Login Timeout' message. */
      len = sprintf((char *)buf, "\r\nLogin timed out after 60 seconds.\r\n");
      break;
		default:
			
			break;
  }
	
  return (len);
}

/*--------------------------- tnet_process_cmd ------------------------------*/

U16 tnet_process_cmd (U8 *cmd, U8 *buf, U16 buflen, U32 *pvar)
{
  /* This is a Telnet Client callback function to make a formatted output   */
  /* for 'stdout'. It returns the number of bytes written to the out buffer.*/
  /* Hi-bit of return value (len is or-ed with 0x8000) is a disconnect flag.*/
  /* Bit 14 (len is or-ed with 0x4000) is a repeat flag for the Tnet client.*/
  /* If this bit is set to 1, the system will call the 'tnet_process_cmd()' */
  /* again with parameter 'pvar' pointing to a 4-byte buffer. This buffer   */
  /* can be used for storing different status variables for this function.  */
  /* It is set to 0 by Telnet server on first call and is not altered by    */
  /* Telnet server for repeated calls. This function should NEVER write     */
  /* more than 'buflen' bytes to the buffer.                                */
  /* Parameters:                                                            */
  /*   cmd    - telnet received command string                              */
  /*   buf    - Telnet transmit buffer                                      */
  /*   buflen - length of this buffer (500-1400 bytes - depends on MSS)     */
  /*   pvar   - pointer to local storage buffer used for repeated loops     */
  /*            This is a U32 variable - size is 4 bytes. Value is:         */
  /*            - on 1st call = 0                                           */
  /*            - 2nd call    = as set by this function on first call       */
  U16 len = 0;

  switch (MYBUF(pvar)->id) {
    case 0:
      /* First call to this function, the value of '*pvar' is 0 */
      break;

    case 1:
			break;
    case 2:
      /* Repeated call, TCP status display. */
			break;
  }

	/* Unknown command, display message */
  len = sprintf((char*)buf, "\r\nUnknown Command");
  return (len);
}

/*--------------------------- tnet_check_account ----------------------------*/

U8 tnet_check_account (U8 code, U8 *id) {
  /* This function checks externally provided user account.  */
  int i;

  if(code == 0) {
    /* Check if the username is valid. */
		
    for (i = 0; i < sizeof(*users); i++) {
      if (strcmp((char *)id, users[i]) == 0) {
        /* Return user index + 1. */
        return (i+1);
      }
    }
  } else {
    /* Check the password for user identified with 'code' */
		
    if (strcmp((char *)id, passwords[code-1]) == 0) {
      /* Return user identification if ok. */
      return (code);
    }
  }
	
  /* User account does not exist. */
  return (0);
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
