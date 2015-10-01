/****************************************************************************
	Luka Penger 2013
	SNTP
****************************************************************************/

#include "SNTP.h"

char SNTP_Server_IP_1[4] = { 0, 0, 0, 0 };
char SNTP_Server_IP_2[4] = { 0, 0, 0, 0 };

BOOL SNTP_Server_IP_1_WORKS = FALSE;
BOOL SNTP_Server_IP_2_WORKS = FALSE;

static void SNTP_Time_Listener_2(U32 time) {
	RTC_Time rtcTime;
	
	if(time == 0) {
		// Error, server not responding or bad response
		SNTP_Server_IP_2_WORKS = FALSE;
	} else {
		// time = seconds elapsed since 1.1.1970
		rtcTime = RTC_Get_Time_From_Seconds(time);
		RTC_Set_Time(rtcTime);
		
		SNTP_Server_IP_2_WORKS = TRUE;
	}
}

void SNTP_Load_Time_Server_2(void) {
	if(SNTP_Server_IP_2[0] != 0 || SNTP_Server_IP_2[1] != 0 || 
		SNTP_Server_IP_2[2] != 0 || SNTP_Server_IP_2[3] != 0) {
		
		if(sntp_get_time((U8*)SNTP_Server_IP_2, SNTP_Time_Listener_2) == TRUE) {
			// SNTP request sent
		} else {
			// Failed, SNTP not ready or bad parameters
			SNTP_Server_IP_2_WORKS = FALSE;
		}
	} else {
		SNTP_Server_IP_2_WORKS = FALSE;
	}
}

static void SNTP_Time_Listener_1(U32 time) {
	RTC_Time rtcTime;
	
	if(time == 0) {
		// Error, server not responding or bad response
		SNTP_Server_IP_1_WORKS = FALSE;
	
		SNTP_Load_Time_Server_2();
	} else {
		// time = seconds elapsed since 1.1.1970
		rtcTime = RTC_Get_Time_From_Seconds(time);
		RTC_Set_Time(rtcTime);
		
		SNTP_Server_IP_1_WORKS = TRUE;
	}
}

void SNTP_Load_Time(void) {
	SNTP_Server_IP_1_WORKS = FALSE;
	SNTP_Server_IP_2_WORKS = FALSE;
	
	if(SNTP_Server_IP_1[0] != 0 || SNTP_Server_IP_1[1] != 0 || 
		SNTP_Server_IP_1[2] != 0 || SNTP_Server_IP_1[3] != 0) {
		
		if(sntp_get_time((U8*)SNTP_Server_IP_1, SNTP_Time_Listener_1) == TRUE) {
			// SNTP request sent
		} else {
			// Failed, SNTP not ready or bad parameters
			SNTP_Server_IP_1_WORKS = FALSE;
		}
	} else {
		SNTP_Server_IP_1_WORKS = FALSE;
		
		SNTP_Load_Time_Server_2();
	}
}

/****************************************************************************
                            End Of File
****************************************************************************/
