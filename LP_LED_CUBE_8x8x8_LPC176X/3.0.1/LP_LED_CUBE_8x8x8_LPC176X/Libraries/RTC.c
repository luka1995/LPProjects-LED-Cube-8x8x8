/****************************************************************************
	Luka Penger 2013
	RTC
****************************************************************************/

#include <RTC.h>

extern signed char TIME_ZONE_OFFSET_SELECTED_VALUE;

volatile uint32_t alarm_on = 0;

extern void RTC_IRQHandler(void) {
	LPC_RTC->ILR |= ILR_RTCCIF;                /* clear interrupt flag */
  alarm_on = 1;
  return;
}

void RTC_Init(void) {
  alarm_on = 0;

  /* Enable CLOCK into RTC */
  LPC_SC->PCONP |= (1 << 9);

  /* If RTC is stopped, clear STOP bit. */
  if(LPC_RTC->RTC_AUX & (0x1<<4)) {
		LPC_RTC->RTC_AUX |= (0x1<<4);        
  }
  
  /*--- Initialize registers ---*/    
  LPC_RTC->AMR = 0;
  LPC_RTC->CIIR = 0;
  LPC_RTC->CCR = 0;
  return;
}

void RTC_Start(void) {
  /*--- Start RTC counters ---*/
  LPC_RTC->CCR |= CCR_CLKEN;
  LPC_RTC->ILR = ILR_RTCCIF;
}

void RTC_Stop(void) {   
  /*--- Stop RTC counters ---*/
  LPC_RTC->CCR &= ~CCR_CLKEN;
} 

void RTC_CTC_Reset(void) {
  /*--- Reset CTC ---*/
  LPC_RTC->CCR |= CCR_CTCRST;
}

void RTC_Set_Time(RTC_Time time) {
	LPC_RTC->SEC = time.Sec;
  LPC_RTC->MIN = time.Min;
  LPC_RTC->HOUR = time.Hour;
  LPC_RTC->DOM = time.Mday;
  LPC_RTC->DOW = time.Wday;
  LPC_RTC->DOY = time.Yday;
  LPC_RTC->MONTH = time.Mon;
  LPC_RTC->YEAR = time.Year; 
}

void RTC_Set_Alarm(RTC_Time alarm) {   
  LPC_RTC->ALSEC = alarm.Sec;
  LPC_RTC->ALMIN = alarm.Min;
  LPC_RTC->ALHOUR = alarm.Hour;
  LPC_RTC->ALDOM = alarm.Mday;
  LPC_RTC->ALDOW = alarm.Wday;
  LPC_RTC->ALDOY = alarm.Yday;
  LPC_RTC->ALMON = alarm.Mon;
  LPC_RTC->ALYEAR = alarm.Year;
}

RTC_Time RTC_Get_Time(void) {
  RTC_Time time;
    
	time.Sec = LPC_RTC->SEC;
  time.Min = LPC_RTC->MIN;
  time.Hour = LPC_RTC->HOUR;
  time.Mday = LPC_RTC->DOM;
  time.Wday = LPC_RTC->DOW;
  time.Yday = LPC_RTC->DOY;
	time.Mon = LPC_RTC->MONTH;
  time.Year = LPC_RTC->YEAR;

  return time;    
}

void RTC_Reset_Time(void) {
	LPC_RTC->SEC = 0;
  LPC_RTC->MIN = 0;
  LPC_RTC->HOUR = 0;
  LPC_RTC->DOM = 0;
  LPC_RTC->DOW = 0;
  LPC_RTC->DOY = 0;
  LPC_RTC->MONTH = 0;
  LPC_RTC->YEAR = 0; 
}

struct tm *RTC_Get_TimeInfo(RTC_Time rtc_time) {
	struct tm timeinfo;
	struct tm *time_st;
	time_t timesec;
	
	timeinfo.tm_sec = rtc_time.Sec;
	timeinfo.tm_min = rtc_time.Min;
	timeinfo.tm_hour = rtc_time.Hour + TIME_ZONE_OFFSET_SELECTED_VALUE;
	timeinfo.tm_mday = rtc_time.Mday;
	timeinfo.tm_wday = rtc_time.Wday;
	timeinfo.tm_yday = rtc_time.Yday;
	timeinfo.tm_mon = (rtc_time.Mon - 1);
	timeinfo.tm_year = (rtc_time.Year - 1900);
	
	timesec = mktime(&timeinfo);
	
	time_st = localtime(&timesec);

	return time_st;
}

extern void UART_CONSOLE_Send_String(char *string);

RTC_Time RTC_Get_Time_From_Seconds(uint32_t seconds) {
  RTC_Time time;
	time_t rawtime = seconds;
	struct tm *timeinfo;

	timeinfo = localtime(&rawtime);
	
	time.Sec = timeinfo->tm_sec;
  time.Min = timeinfo->tm_min;
  time.Hour = timeinfo->tm_hour;
  time.Mday = timeinfo->tm_mday;
  time.Wday = timeinfo->tm_wday;
  time.Yday = timeinfo->tm_yday;
	time.Mon = (timeinfo->tm_mon + 1);
  time.Year = (1900 + timeinfo->tm_year);

  return time;    
}

void RTC_Set_Alarm_Mask(uint32_t AlarmMask) {
  /*--- Set alarm mask ---*/    
  LPC_RTC->AMR = AlarmMask;
}

/****************************************************************************
                            End Of File
****************************************************************************/
