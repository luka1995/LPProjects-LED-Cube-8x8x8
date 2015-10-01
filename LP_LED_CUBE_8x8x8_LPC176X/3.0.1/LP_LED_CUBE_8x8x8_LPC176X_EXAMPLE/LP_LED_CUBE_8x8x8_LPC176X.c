/*----------------------------------------------------------------------------
 *      LED CUBE 8x8x8
 *			Copyright 2014
 *			Luka Penger
 *			LPProjects
 *			http://lpprojects.eu
 *---------------------------------------------------------------------------*/

#include <LPC17xx.H>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <DELAY.h>
#include <UART.h>
#include <LED_CUBE_8x8x8.h>

/*--------------------------- device configuration --------------------------*/

#define STATUS_LED1_PIN													25
#define STATUS_LED2_PIN													26

#define UART_CONSOLE_NUMBER											0
#define UART_CONSOLE_BAUD_RATE									115200

/*--------------------------- systick timer --------------------------*/

volatile uint32_t TimeTick = 0;

void SysTick_Handler (void) {
	TimeTick++;
}

void DelaySysTick (uint32_t tick) {
	uint32_t timetick;
	
	timetick = TimeTick;
	while ((TimeTick - timetick) < tick)
		__WFI();
}

/*--------------------------- UART console ----------------------------------*/

extern volatile unsigned int UART_Status[2];
extern volatile unsigned char UART_TxEmpty[2];
extern volatile unsigned char UART_Buffer[2][UART_BUFSIZE];
extern volatile unsigned int UART_Count[2];

void UART_CONSOLE_Init (void) {
	UART_Init(UART_CONSOLE_NUMBER, UART_CONSOLE_BAUD_RATE);
}

void UART_CONSOLE_Send_Buffer (char *buffer, unsigned int length) {
	UART_SendBuffer(UART_CONSOLE_NUMBER, buffer, length);
}

void UART_CONSOLE_Send_String (char *string) {
	UART_SendBuffer(UART_CONSOLE_NUMBER, string, strlen(string));
}

void UART_CONSOLE_Send_Char (char value) {
	UART_SendChar(UART_CONSOLE_NUMBER, value);
}

/*--------------------------- status leds -----------------------------------*/

void Status_LEDs_Init (void) {
	LPC_GPIO3->FIODIR |= (1<<STATUS_LED1_PIN);
	LPC_GPIO3->FIODIR |= (1<<STATUS_LED2_PIN);
	
	LPC_GPIO3->FIOSET |= (1<<STATUS_LED1_PIN);
	LPC_GPIO3->FIOSET |= (1<<STATUS_LED2_PIN);
}

void Status_LED1_Set (BOOL state) {
	if (state) {
		LPC_GPIO3->FIOCLR |= (1<<STATUS_LED1_PIN);
	} else {
		LPC_GPIO3->FIOSET |= (1<<STATUS_LED1_PIN);
	}
}

void Status_LED2_Set (BOOL state) {
	if (state) {
		LPC_GPIO3->FIOCLR |= (1<<STATUS_LED2_PIN);
	} else {
		LPC_GPIO3->FIOSET |= (1<<STATUS_LED2_PIN);
	}
}

void Status_LED1_Toggle (void) {
	Status_LED1_Set((LPC_GPIO3->FIOPIN & (1<<STATUS_LED1_PIN)));
}

void Status_LED2_Toggle (void) {
	Status_LED2_Set((LPC_GPIO3->FIOPIN & (1<<STATUS_LED2_PIN)));
}

/*--------------------------- init ------------------------------------------*/

void Init (void) {
	SystemInit();

	// SysTick init
	SysTick_Config((SystemCoreClock / 100000)); // 10us	
	
	// UART Init
	UART_CONSOLE_Init();

	// Init status leds
	Status_LEDs_Init();
	
	// Init LED CUBE
	LED_CUBE_Init();
	
	UART_CONSOLE_Send_String("Init\n");
}

/*--------------------------- main ------------------------------------------*/

int main (void) {
	//
	// Variables
	//

	//
	// Init
	//
  Init();

	//
	// While
	//
  while (1) {
		LED_CUBE_Rows_Set(0x00);
		LED_CUBE_Columns_Set(0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF);
	}
}
