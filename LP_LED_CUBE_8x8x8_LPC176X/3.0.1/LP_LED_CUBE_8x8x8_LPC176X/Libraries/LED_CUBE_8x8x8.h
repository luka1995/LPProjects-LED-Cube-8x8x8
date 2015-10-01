/****************************************************************************
	Luka Penger 2014
	LED CUBE 8x8x8
	LPC17xx
****************************************************************************/
#ifndef __LED_CUBE_8x8x8_H 
#define __LED_CUBE_8x8x8_H

#include <LPC17xx.H>
#include <HELP.h>
#include <TLC59116.h>

#define LED_CUBE_I2C_PORT_NUM					0
#define LED_CUBE_IC1_I2C_ADDRESS			0xC0
#define LED_CUBE_IC2_I2C_ADDRESS			0xD0
#define LED_CUBE_IC3_I2C_ADDRESS			0xC8
#define LED_CUBE_IC4_I2C_ADDRESS			0xD8

typedef struct {
	char columns[8];
	char rows;
	char delay;
	char name[20];
} LED_CUBE_Effect;

void LED_CUBE_Rows_Set(char rows);
void LED_CUBE_Row_Set(int rowNum, BOOL state);
void LED_CUBE_Columns_Set(char columns1, char columns2, char columns3, char columns4, char columns5, char columns6, char columns7, char columns8);
void LED_CUBE_Column_Set(int ledNum, BOOL state);
void LED_CUBE_Init(void);
char LED_CUBE_Effect_Log(LED_CUBE_Effect effect, char *buffer);

#endif /* end __LED_CUBE_8x8x8_H */
/**************************************************************************
                            End Of File
***************************************************************************/
