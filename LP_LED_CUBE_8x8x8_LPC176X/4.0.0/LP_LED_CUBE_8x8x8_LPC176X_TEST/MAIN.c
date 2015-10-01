/*----------------------------------------------------------------------------
 *      LED CUBE 8x8x8
 *			Copyright 2014
 *			Luka Penger
 *			LPProjects
 *			http://lpprojects.eu
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include <RTL.h>
#include <LPC17xx.H>
#include <string.h>
#include <stdlib.h>
#include <LED_CUBE_8x8x8.h>
#include <LED_CUBE_8x8x8_Animations.h>
#include <UART.h>
#include <DELAY.h>

/*--------------------------- device configuration --------------------------*/

#define STATUS_LED1_PIN																25
#define STATUS_LED2_PIN																26

#define UART_CONSOLE_NUMBER														0
#define UART_CONSOLE_BAUD_RATE												115200

/*--------------------------- variables -------------------------------------*/

BOOL TICK_10MS;
BOOL TICK_100MS;
BOOL TICK_1S;

/*--------------------------- uart console ----------------------------------*/

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

/*--------------------------- timer_poll ------------------------------------*/
volatile int timerLEDCube_tick = 0, timer10s_tick = 0, timer100s_tick = 0, timer1s_tick = 0;

void SysTick_Handler (void) {
	if (SysTick->CTRL & 0x10000) {
    // Timer tick every 10 ms

		if (timerLEDCube_tick >= 20) {
			timerLEDCube_tick = 0;
			LED_CUBE_Timer();
		} else {
			timerLEDCube_tick++;
		}
		
		if (timer10s_tick >= 10) {
			timer10s_tick = 0;
			TICK_10MS = __TRUE;
			
			if (timer100s_tick >= 10) {
				timer100s_tick = 0;
				TICK_100MS = __TRUE;
				
				if (timer1s_tick >= 10) {
					timer1s_tick = 0;
					TICK_1S = __TRUE;
					
				} else {
					timer1s_tick++;
				}
			} else {
				timer100s_tick++;
			}
		} else {
			timer10s_tick++;
		}
	}
}

/*--------------------------- init ------------------------------------------*/

void Init (void) {
	SystemInit();

	// Setup and enable the SysTick timer for 1ms.
	SysTick_Config((SystemCoreClock / 10000)); // 10us

	// UART Init
	UART_CONSOLE_Init();
	
	// Init status leds
	Status_LEDs_Init();

	// Init LED Cube
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

	Status_LED1_Set(TRUE);
	Status_LED2_Set(TRUE);

	//
	// While
	//

  while (1) {
		//timer_poll();

		LED_CUBE_Animation_String_belt("  lpprojects");
		
		LED_CUBE_Animation_String_to_front(" 2014 ");
		
		LED_CUBE_Animations_Cube_waves();
		
		LED_CUBE_Animations_wipe();
		
		LED_CUBE_Animations_Cubes_4();
		
		/*
		LED_CUBE_Animation_Cube_2_auto();
		
		LED_CUBE_Animations_wipe();
		
		LED_CUBE_Animations_explosion();
		
		LED_CUBE_Animations_Cubes_4();
	
		LED_CUBE_Animations_Cubes_2();
		
		LED_CUBE_Animations_Cube_stars();
		
		LED_CUBE_Animations_Cube_Outline();
		
		LED_CUBE_Animations_Cube_waves();
		
		LED_CUBE_Animations_Cube_sonic();
		
		LED_CUBE_Animtions_Outline_shrink();
		
		LED_CUBE_Animations_Cube_invaders();
		
		LED_CUBE_Animations_Cube_block_wipe();
		LED_CUBE_Animations_Cube_stripes();
		*/
		/*****************************************************************************
		** 10 ms timer
		*****************************************************************************/
		
		if (TICK_10MS == __TRUE) {
			TICK_10MS = __FALSE;

		}
		
		/*****************************************************************************
		** 100 ms timer
		*****************************************************************************/
		
		if (TICK_100MS == __TRUE) {
			TICK_100MS = __FALSE;

		}
		
		/*****************************************************************************
		** 1 s timer
		*****************************************************************************/
		
		if (TICK_1S == __TRUE) {
			TICK_1S = __FALSE;
			
		}
  }
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
