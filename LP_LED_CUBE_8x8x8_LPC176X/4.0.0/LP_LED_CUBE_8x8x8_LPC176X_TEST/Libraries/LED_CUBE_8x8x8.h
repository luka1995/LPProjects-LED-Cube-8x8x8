/****************************************************************************
	Luka Penger 2014
	LED CUBE 8x8x8
	LPC17xx
	Version 4.0.0
****************************************************************************/
#ifndef __LED_CUBE_8x8x8_H 
#define __LED_CUBE_8x8x8_H

#include <LPC17xx.H>
#include <HELP.h>
#include <DELAY.h>

void LED_CUBE_Frame_show (void);
void LED_CUBE_Timer (void);
void LED_CUBE_Clear (void);
void LED_CUBE_Clear_layer (uint8_t layer);
void LED_CUBE_Full (void);
void LED_CUBE_Cube_3 (void);
void LED_CUBE_Cube_4_line (void);
void LED_CUBE_Random (void);
void LED_CUBE_Test_z (void);
void LED_CUBE_Test_y (void);
void LED_CUBE_Test_x (void);

void LED_CUBE_Layers_Set (char value);
void LED_CUBE_Layer_Set (int layerNum, BOOL state);
void LED_CUBE_Clocks_Set (char value);
void LED_CUBE_Clock_Set (int clockNum, BOOL state);
void LED_CUBE_Outputs_Set (char value);
void LED_CUBE_Init (void);

#endif /* end __LED_CUBE_8x8x8_H */
/**************************************************************************
                            End Of File
***************************************************************************/
