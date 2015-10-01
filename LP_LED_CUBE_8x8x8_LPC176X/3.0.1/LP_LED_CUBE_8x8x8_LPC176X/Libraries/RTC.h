/****************************************************************************
	Luka Penger 2013
	RTC
****************************************************************************/
#ifndef __RTC_H 
#define __RTC_H

#include <stdio.h>
#include <RTL.h>
#include <LPC17xx.H>
#include <string.h>
#include <type.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    uint32_t Sec;     /* Second value - [0,59] */
    uint32_t Min;     /* Minute value - [0,59] */
    uint32_t Hour;    /* Hour value - [0,23] */
    uint32_t Mday;    /* Day of the month value - [1,31] */
    uint32_t Mon;     /* Month value - [1,12] */
    uint32_t Year;    /* Year value - [0,4095] */
    uint32_t Wday;    /* Day of week value - [0,6] */
    uint32_t Yday;    /* Day of year value - [1,365] */
} RTC_Time;

#define IMSEC                			0x00000001
#define IMMIN                			0x00000002
#define IMHOUR               			0x00000004
#define IMDOM                			0x00000008
#define IMDOW                			0x00000010
#define IMDOY                			0x00000020
#define IMMON                			0x00000040
#define IMYEAR                		0x00000080

#define PREINT_RTC        				0x000001C8  /* Prescaler value, integer portion, 
                                    PCLK = 15Mhz */
#define PREFRAC_RTC        				0x000061C0  /* Prescaler value, fraction portion, 
                                    PCLK = 15Mhz */
#define ILR_RTCCIF        				0x01
#define ILR_RTCALF        				0x02

#define CCR_CLKEN        					0x01
#define CCR_CTCRST        				0x02
#define CCR_CLKSRC        				0x10

extern void RTC_IRQHandler(void);
void RTC_Init(void);
void RTC_Start(void);
void RTC_Stop(void);
void RTC_CTC_Reset(void);
void RTC_Reset_Time(void);
void RTC_Set_Time(RTC_Time time);
void RTC_Set_Alarm(RTC_Time alarm);
RTC_Time RTC_Get_Time(void);
struct tm *RTC_Get_TimeInfo(RTC_Time rtc_time);
RTC_Time RTC_Get_Time_From_Seconds(uint32_t seconds);
void RTC_Set_Alarm_Mask(uint32_t AlarmMask);

#endif /* end __RTC_H */
/****************************************************************************
                            End Of File
****************************************************************************/
