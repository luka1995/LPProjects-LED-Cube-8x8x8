/****************************************************************************
	Luka Penger 2014
	LED CUBE 8x8x8 Rotation
	LPC17xx
	Version 4.0.0
****************************************************************************/

#include "LED_CUBE_8x8x8_Rotation.h"

extern volatile unsigned char cube[8][8];

void rotate_90_auto (char cycle) {
	int loopcnt=0, i=0, j=0, x=0, y=0, layer=0;
	
	for (loopcnt=0; loopcnt<cycle; loopcnt++) {
		char cube_org[8][8];
		
		for (i=0; i<8; i++){
			for (j=0; j<8; j++){
				cube_org[i][j] = cube[i][j];
			}
		}
		
		LED_CUBE_Clear();
		
		/* 15 deg */
		for (i=0; i<8; i++){
			if ( cube_org[i][0] & (1 << 2 ) )
			   cube[i][0] |= ( 1 << 3);
			if ( cube_org[i][0] & (1 << 3 ) )
			   cube[i][0] |= ( 1 << 4);
			if ( cube_org[i][0] & (1 << 4 ) )
			   cube[i][0] |= ( 1 << 5);
			if ( cube_org[i][0] & (1 << 5 ) )
			   cube[i][1] |= ( 1 << 6);
			if ( cube_org[i][0] & (1 << 6 ) )
			   cube[i][1] |= ( 1 << 7);
			if ( cube_org[i][1] & (1 << 0 ) )
			   cube[i][0] |= ( 1 << 1);
			if ( cube_org[i][1] & (1 << 1 ) )
			   cube[i][0] |= ( 1 << 2);
			if ( cube_org[i][1] & (1 << 2 ) )
			   cube[i][1] |= ( 1 << 3);
			if ( cube_org[i][1] & (1 << 3 ) )
			   cube[i][1] |= ( 1 << 4);
			if ( cube_org[i][1] & (1 << 4 ) )
			   cube[i][1] |= ( 1 << 5);
			if ( cube_org[i][1] & (1 << 5 ) )
			   cube[i][1] |= ( 1 << 6);
			if ( cube_org[i][1] & (1 << 6 ) )
			   cube[i][2] |= ( 1 << 7);
			if ( cube_org[i][2] & (1 << 0 ) )
			   cube[i][1] |= ( 1 << 1);
			if ( cube_org[i][2] & (1 << 1 ) )
			   cube[i][1] |= ( 1 << 1);
			if ( cube_org[i][2] & (1 << 2 ) )
			   cube[i][2] |= ( 1 << 2);
			if ( cube_org[i][2] & (1 << 3 ) )
			   cube[i][2] |= ( 1 << 3);
			if ( cube_org[i][2] & (1 << 4 ) )
			   cube[i][2] |= ( 1 << 4);
			if ( cube_org[i][2] & (1 << 5 ) )
			   cube[i][2] |= ( 1 << 5);
			if ( cube_org[i][2] & (1 << 6 ) )
			   cube[i][3] |= ( 1 << 6);
			if ( cube_org[i][2] & (1 << 7 ) )
			   cube[i][3] |= ( 1 << 7);
			if ( cube_org[i][3] & (1 << 0 ) )
			   cube[i][2] |= ( 1 << 0);
			if ( cube_org[i][3] & (1 << 1 ) )
			   cube[i][2] |= ( 1 << 1);
			if ( cube_org[i][3] & (1 << 2 ) )
			   cube[i][3] |= ( 1 << 2);
			if ( cube_org[i][3] & (1 << 3 ) )
			   cube[i][3] |= ( 1 << 3);
			if ( cube_org[i][3] & (1 << 4 ) )
			   cube[i][3] |= ( 1 << 4);
			if ( cube_org[i][3] & (1 << 5 ) )
			   cube[i][3] |= ( 1 << 5);
			if ( cube_org[i][3] & (1 << 6 ) )
			   cube[i][4] |= ( 1 << 6);
			if ( cube_org[i][3] & (1 << 7 ) )
			   cube[i][4] |= ( 1 << 7);
			if ( cube_org[i][4] & (1 << 0 ) )
			   cube[i][3] |= ( 1 << 0);
			if ( cube_org[i][4] & (1 << 1 ) )
			   cube[i][3] |= ( 1 << 1);
			if ( cube_org[i][4] & (1 << 2 ) )
			   cube[i][4] |= ( 1 << 2);
			if ( cube_org[i][4] & (1 << 3 ) )
			   cube[i][4] |= ( 1 << 3);
			if ( cube_org[i][4] & (1 << 4 ) )
			   cube[i][4] |= ( 1 << 4);
			if ( cube_org[i][4] & (1 << 5 ) )
			   cube[i][4] |= ( 1 << 5);
			if ( cube_org[i][4] & (1 << 6 ) )
			   cube[i][5] |= ( 1 << 6);
			if ( cube_org[i][4] & (1 << 7 ) )
			   cube[i][5] |= ( 1 << 7);
			if ( cube_org[i][5] & (1 << 0 ) )
			   cube[i][4] |= ( 1 << 0);
			if ( cube_org[i][5] & (1 << 1 ) )
			   cube[i][4] |= ( 1 << 1);
			if ( cube_org[i][5] & (1 << 2 ) )
			   cube[i][5] |= ( 1 << 2);
			if ( cube_org[i][5] & (1 << 3 ) )
			   cube[i][5] |= ( 1 << 3);
			if ( cube_org[i][5] & (1 << 4 ) )
			   cube[i][5] |= ( 1 << 4);
			if ( cube_org[i][5] & (1 << 5 ) )
			   cube[i][5] |= ( 1 << 5);
			if ( cube_org[i][5] & (1 << 6 ) )
			   cube[i][6] |= ( 1 << 6);
			if ( cube_org[i][5] & (1 << 7 ) )
			   cube[i][6] |= ( 1 << 6);
			if ( cube_org[i][6] & (1 << 1 ) )
			   cube[i][5] |= ( 1 << 0);
			if ( cube_org[i][6] & (1 << 2 ) )
			   cube[i][6] |= ( 1 << 1);
			if ( cube_org[i][6] & (1 << 3 ) )
			   cube[i][6] |= ( 1 << 2);
			if ( cube_org[i][6] & (1 << 4 ) )
			   cube[i][6] |= ( 1 << 3);
			if ( cube_org[i][6] & (1 << 5 ) )
			   cube[i][6] |= ( 1 << 4);
			if ( cube_org[i][6] & (1 << 6 ) )
			   cube[i][7] |= ( 1 << 5);
			if ( cube_org[i][6] & (1 << 7 ) )
			   cube[i][7] |= ( 1 << 6);
			if ( cube_org[i][7] & (1 << 1 ) )
			   cube[i][6] |= ( 1 << 0);
			if ( cube_org[i][7] & (1 << 2 ) )
			   cube[i][6] |= ( 1 << 1);
			if ( cube_org[i][7] & (1 << 3 ) )
			   cube[i][7] |= ( 1 << 2);
			if ( cube_org[i][7] & (1 << 4 ) )
			   cube[i][7] |= ( 1 << 3);
			if ( cube_org[i][7] & (1 << 5 ) )
			   cube[i][7] |= ( 1 << 4);
		}
		
		Delay_ms(80);
		LED_CUBE_Clear();
		
		/* 30 deg */
		for (i=0; i<8; i++){
			if ( cube_org[i][0] & (1 << 2 ) )
			   cube[i][0] |= ( 1 << 4);
			if ( cube_org[i][0] & (1 << 3 ) )
			   cube[i][0] |= ( 1 << 5);
			if ( cube_org[i][0] & (1 << 4 ) )
			   cube[i][1] |= ( 1 << 6);
			if ( cube_org[i][0] & (1 << 5 ) )
			   cube[i][1] |= ( 1 << 7);
			if ( cube_org[i][0] & (1 << 6 ) )
			   cube[i][2] |= ( 1 << 7);
			if ( cube_org[i][1] & (1 << 0 ) )
			   cube[i][0] |= ( 1 << 2);
			if ( cube_org[i][1] & (1 << 1 ) )
			   cube[i][0] |= ( 1 << 3);
			if ( cube_org[i][1] & (1 << 2 ) )
			   cube[i][1] |= ( 1 << 3);
			if ( cube_org[i][1] & (1 << 3 ) )
			   cube[i][1] |= ( 1 << 4);
			if ( cube_org[i][1] & (1 << 4 ) )
			   cube[i][2] |= ( 1 << 5);
			if ( cube_org[i][1] & (1 << 5 ) )
			   cube[i][2] |= ( 1 << 6);
			if ( cube_org[i][1] & (1 << 6 ) )
			   cube[i][3] |= ( 1 << 7);
			if ( cube_org[i][2] & (1 << 0 ) )
			   cube[i][0] |= ( 1 << 1);
			if ( cube_org[i][2] & (1 << 1 ) )
			   cube[i][1] |= ( 1 << 2);
			if ( cube_org[i][2] & (1 << 2 ) )
			   cube[i][1] |= ( 1 << 3);
			if ( cube_org[i][2] & (1 << 3 ) )
			   cube[i][2] |= ( 1 << 4);
			if ( cube_org[i][2] & (1 << 4 ) )
			   cube[i][2] |= ( 1 << 5);
			if ( cube_org[i][2] & (1 << 5 ) )
			   cube[i][3] |= ( 1 << 6);
			if ( cube_org[i][2] & (1 << 6 ) )
			   cube[i][3] |= ( 1 << 6);
			if ( cube_org[i][2] & (1 << 7 ) )
			   cube[i][4] |= ( 1 << 7);
			if ( cube_org[i][3] & (1 << 0 ) )
			   cube[i][1] |= ( 1 << 1);
			if ( cube_org[i][3] & (1 << 1 ) )
			   cube[i][2] |= ( 1 << 2);
			if ( cube_org[i][3] & (1 << 2 ) )
			   cube[i][2] |= ( 1 << 2);
			if ( cube_org[i][3] & (1 << 3 ) )
			   cube[i][3] |= ( 1 << 3);
			if ( cube_org[i][3] & (1 << 4 ) )
			   cube[i][3] |= ( 1 << 4);
			if ( cube_org[i][3] & (1 << 5 ) )
			   cube[i][4] |= ( 1 << 5);
			if ( cube_org[i][3] & (1 << 6 ) )
			   cube[i][4] |= ( 1 << 6);
			if ( cube_org[i][3] & (1 << 7 ) )
			   cube[i][5] |= ( 1 << 7);
			if ( cube_org[i][4] & (1 << 0 ) )
			   cube[i][2] |= ( 1 << 0);
			if ( cube_org[i][4] & (1 << 1 ) )
			   cube[i][3] |= ( 1 << 1);
			if ( cube_org[i][4] & (1 << 2 ) )
			   cube[i][3] |= ( 1 << 2);
			if ( cube_org[i][4] & (1 << 3 ) )
			   cube[i][4] |= ( 1 << 3);
			if ( cube_org[i][4] & (1 << 4 ) )
			   cube[i][4] |= ( 1 << 4);
			if ( cube_org[i][4] & (1 << 5 ) )
			   cube[i][5] |= ( 1 << 5);
			if ( cube_org[i][4] & (1 << 6 ) )
			   cube[i][5] |= ( 1 << 5);
			if ( cube_org[i][4] & (1 << 7 ) )
			   cube[i][6] |= ( 1 << 6);
			if ( cube_org[i][5] & (1 << 0 ) )
			   cube[i][3] |= ( 1 << 0);
			if ( cube_org[i][5] & (1 << 1 ) )
			   cube[i][4] |= ( 1 << 1);
			if ( cube_org[i][5] & (1 << 2 ) )
			   cube[i][4] |= ( 1 << 1);
			if ( cube_org[i][5] & (1 << 3 ) )
			   cube[i][5] |= ( 1 << 2);
			if ( cube_org[i][5] & (1 << 4 ) )
			   cube[i][5] |= ( 1 << 3);
			if ( cube_org[i][5] & (1 << 5 ) )
			   cube[i][6] |= ( 1 << 4);
			if ( cube_org[i][5] & (1 << 6 ) )
			   cube[i][6] |= ( 1 << 5);
			if ( cube_org[i][5] & (1 << 7 ) )
			   cube[i][7] |= ( 1 << 6);
			if ( cube_org[i][6] & (1 << 1 ) )
			   cube[i][4] |= ( 1 << 0);
			if ( cube_org[i][6] & (1 << 2 ) )
			   cube[i][5] |= ( 1 << 1);
			if ( cube_org[i][6] & (1 << 3 ) )
			   cube[i][5] |= ( 1 << 2);
			if ( cube_org[i][6] & (1 << 4 ) )
			   cube[i][6] |= ( 1 << 3);
			if ( cube_org[i][6] & (1 << 5 ) )
			   cube[i][6] |= ( 1 << 4);
			if ( cube_org[i][6] & (1 << 6 ) )
			   cube[i][7] |= ( 1 << 4);
			if ( cube_org[i][6] & (1 << 7 ) )
			   cube[i][7] |= ( 1 << 5);
			if ( cube_org[i][7] & (1 << 1 ) )
			   cube[i][5] |= ( 1 << 0);
			if ( cube_org[i][7] & (1 << 2 ) )
			   cube[i][6] |= ( 1 << 0);
			if ( cube_org[i][7] & (1 << 3 ) )
			   cube[i][6] |= ( 1 << 1);
			if ( cube_org[i][7] & (1 << 4 ) )
			   cube[i][7] |= ( 1 << 2);
			if ( cube_org[i][7] & (1 << 5 ) )
			   cube[i][7] |= ( 1 << 3);
		}
		
		Delay_ms(80);
		LED_CUBE_Clear();

		/* 45 deg */
		for (i=0; i<8; i++){
			if ( cube_org[i][0] & (1 << 2 ) )
			   cube[i][0] |= ( 1 << 5);
			if ( cube_org[i][0] & (1 << 3 ) )
			   cube[i][1] |= ( 1 << 6);
			if ( cube_org[i][0] & (1 << 4 ) )
			   cube[i][1] |= ( 1 << 6);
			if ( cube_org[i][0] & (1 << 5 ) )
			   cube[i][2] |= ( 1 << 7);
			if ( cube_org[i][1] & (1 << 1 ) )
			   cube[i][0] |= ( 1 << 4);
			if ( cube_org[i][1] & (1 << 2 ) )
			   cube[i][1] |= ( 1 << 4);
			if ( cube_org[i][1] & (1 << 3 ) )
			   cube[i][1] |= ( 1 << 5);
			if ( cube_org[i][1] & (1 << 4 ) )
			   cube[i][2] |= ( 1 << 6);
			if ( cube_org[i][1] & (1 << 5 ) )
			   cube[i][3] |= ( 1 << 6);
			if ( cube_org[i][1] & (1 << 6 ) )
			   cube[i][4] |= ( 1 << 7);
			if ( cube_org[i][2] & (1 << 0 ) )
			   cube[i][0] |= ( 1 << 2);
			if ( cube_org[i][2] & (1 << 1 ) )
			   cube[i][1] |= ( 1 << 3);
			if ( cube_org[i][2] & (1 << 2 ) )
			   cube[i][1] |= ( 1 << 4);
			if ( cube_org[i][2] & (1 << 3 ) )
			   cube[i][2] |= ( 1 << 4);
			if ( cube_org[i][2] & (1 << 4 ) )
			   cube[i][3] |= ( 1 << 5);
			if ( cube_org[i][2] & (1 << 5 ) )
			   cube[i][4] |= ( 1 << 6);
			if ( cube_org[i][2] & (1 << 6 ) )
			   cube[i][4] |= ( 1 << 6);
			if ( cube_org[i][2] & (1 << 7 ) )
			   cube[i][5] |= ( 1 << 7);
			if ( cube_org[i][3] & (1 << 0 ) )
			   cube[i][1] |= ( 1 << 1);
			if ( cube_org[i][3] & (1 << 1 ) )
			   cube[i][1] |= ( 1 << 2);
			if ( cube_org[i][3] & (1 << 2 ) )
			   cube[i][2] |= ( 1 << 3);
			if ( cube_org[i][3] & (1 << 3 ) )
			   cube[i][3] |= ( 1 << 4);
			if ( cube_org[i][3] & (1 << 4 ) )
			   cube[i][4] |= ( 1 << 4);
			if ( cube_org[i][3] & (1 << 5 ) )
			   cube[i][4] |= ( 1 << 5);
			if ( cube_org[i][3] & (1 << 6 ) )
			   cube[i][5] |= ( 1 << 6);
			if ( cube_org[i][3] & (1 << 7 ) )
			   cube[i][6] |= ( 1 << 6);
			if ( cube_org[i][4] & (1 << 0 ) )
			   cube[i][1] |= ( 1 << 1);
			if ( cube_org[i][4] & (1 << 1 ) )
			   cube[i][2] |= ( 1 << 1);
			if ( cube_org[i][4] & (1 << 2 ) )
			   cube[i][3] |= ( 1 << 2);
			if ( cube_org[i][4] & (1 << 3 ) )
			   cube[i][4] |= ( 1 << 3);
			if ( cube_org[i][4] & (1 << 4 ) )
			   cube[i][4] |= ( 1 << 4);
			if ( cube_org[i][4] & (1 << 5 ) )
			   cube[i][5] |= ( 1 << 4);
			if ( cube_org[i][4] & (1 << 6 ) )
			   cube[i][6] |= ( 1 << 5);
			if ( cube_org[i][4] & (1 << 7 ) )
			   cube[i][6] |= ( 1 << 6);
			if ( cube_org[i][5] & (1 << 0 ) )
			   cube[i][2] |= ( 1 << 0);
			if ( cube_org[i][5] & (1 << 1 ) )
			   cube[i][3] |= ( 1 << 1);
			if ( cube_org[i][5] & (1 << 2 ) )
			   cube[i][4] |= ( 1 << 1);
			if ( cube_org[i][5] & (1 << 3 ) )
			   cube[i][4] |= ( 1 << 2);
			if ( cube_org[i][5] & (1 << 4 ) )
			   cube[i][5] |= ( 1 << 3);
			if ( cube_org[i][5] & (1 << 5 ) )
			   cube[i][6] |= ( 1 << 4);
			if ( cube_org[i][5] & (1 << 6 ) )
			   cube[i][6] |= ( 1 << 4);
			if ( cube_org[i][5] & (1 << 7 ) )
			   cube[i][7] |= ( 1 << 5);
			if ( cube_org[i][6] & (1 << 1 ) )
			   cube[i][4] |= ( 1 << 0);
			if ( cube_org[i][6] & (1 << 2 ) )
			   cube[i][4] |= ( 1 << 1);
			if ( cube_org[i][6] & (1 << 3 ) )
			   cube[i][5] |= ( 1 << 1);
			if ( cube_org[i][6] & (1 << 4 ) )
			   cube[i][6] |= ( 1 << 2);
			if ( cube_org[i][6] & (1 << 5 ) )
			   cube[i][6] |= ( 1 << 3);
			if ( cube_org[i][6] & (1 << 6 ) )
			   cube[i][7] |= ( 1 << 4);
			if ( cube_org[i][7] & (1 << 2 ) )
			   cube[i][5] |= ( 1 << 0);
			if ( cube_org[i][7] & (1 << 3 ) )
			   cube[i][6] |= ( 1 << 1);
			if ( cube_org[i][7] & (1 << 4 ) )
			   cube[i][6] |= ( 1 << 1);
			if ( cube_org[i][7] & (1 << 5 ) )
			   cube[i][7] |= ( 1 << 2);

		}
		
		Delay_ms(80);
		LED_CUBE_Clear();
		
		/* 60 deg */
		for (i=0; i<8; i++){
			if ( cube_org[i][0] & (1 << 1 ) )
			   cube[i][0] |= ( 1 << 5);
			if ( cube_org[i][0] & (1 << 2 ) )
			   cube[i][0] |= ( 1 << 6);
			if ( cube_org[i][0] & (1 << 3 ) )
			   cube[i][1] |= ( 1 << 6);
			if ( cube_org[i][0] & (1 << 4 ) )
			   cube[i][2] |= ( 1 << 7);
			if ( cube_org[i][0] & (1 << 5 ) )
			   cube[i][3] |= ( 1 << 7);
			if ( cube_org[i][1] & (1 << 1 ) )
			   cube[i][0] |= ( 1 << 4);
			if ( cube_org[i][1] & (1 << 2 ) )
			   cube[i][1] |= ( 1 << 5);
			if ( cube_org[i][1] & (1 << 3 ) )
			   cube[i][2] |= ( 1 << 5);
			if ( cube_org[i][1] & (1 << 4 ) )
			   cube[i][3] |= ( 1 << 6);
			if ( cube_org[i][1] & (1 << 5 ) )
			   cube[i][4] |= ( 1 << 6);
			if ( cube_org[i][1] & (1 << 6 ) )
			   cube[i][4] |= ( 1 << 7);
			if ( cube_org[i][1] & (1 << 7 ) )
			   cube[i][5] |= ( 1 << 7);
			if ( cube_org[i][2] & (1 << 0 ) )
			   cube[i][0] |= ( 1 << 3);
			if ( cube_org[i][2] & (1 << 1 ) )
			   cube[i][1] |= ( 1 << 4);
			if ( cube_org[i][2] & (1 << 2 ) )
			   cube[i][1] |= ( 1 << 4);
			if ( cube_org[i][2] & (1 << 3 ) )
			   cube[i][2] |= ( 1 << 5);
			if ( cube_org[i][2] & (1 << 4 ) )
			   cube[i][3] |= ( 1 << 5);
			if ( cube_org[i][2] & (1 << 5 ) )
			   cube[i][4] |= ( 1 << 6);
			if ( cube_org[i][2] & (1 << 6 ) )
			   cube[i][5] |= ( 1 << 6);
			if ( cube_org[i][2] & (1 << 7 ) )
			   cube[i][6] |= ( 1 << 7);
			if ( cube_org[i][3] & (1 << 0 ) )
			   cube[i][0] |= ( 1 << 2);
			if ( cube_org[i][3] & (1 << 1 ) )
			   cube[i][1] |= ( 1 << 3);
			if ( cube_org[i][3] & (1 << 2 ) )
			   cube[i][2] |= ( 1 << 3);
			if ( cube_org[i][3] & (1 << 3 ) )
			   cube[i][3] |= ( 1 << 4);
			if ( cube_org[i][3] & (1 << 4 ) )
			   cube[i][4] |= ( 1 << 4);
			if ( cube_org[i][3] & (1 << 5 ) )
			   cube[i][5] |= ( 1 << 5);
			if ( cube_org[i][3] & (1 << 6 ) )
			   cube[i][5] |= ( 1 << 5);
			if ( cube_org[i][3] & (1 << 7 ) )
			   cube[i][6] |= ( 1 << 6);
			if ( cube_org[i][4] & (1 << 0 ) )
			   cube[i][1] |= ( 1 << 1);
			if ( cube_org[i][4] & (1 << 1 ) )
			   cube[i][2] |= ( 1 << 2);
			if ( cube_org[i][4] & (1 << 2 ) )
			   cube[i][2] |= ( 1 << 2);
			if ( cube_org[i][4] & (1 << 3 ) )
			   cube[i][3] |= ( 1 << 3);
			if ( cube_org[i][4] & (1 << 4 ) )
			   cube[i][4] |= ( 1 << 3);
			if ( cube_org[i][4] & (1 << 5 ) )
			   cube[i][5] |= ( 1 << 4);
			if ( cube_org[i][4] & (1 << 6 ) )
			   cube[i][6] |= ( 1 << 4);
			if ( cube_org[i][4] & (1 << 7 ) )
			   cube[i][7] |= ( 1 << 5);
			if ( cube_org[i][5] & (1 << 0 ) )
			   cube[i][1] |= ( 1 << 0);
			if ( cube_org[i][5] & (1 << 1 ) )
			   cube[i][2] |= ( 1 << 1);
			if ( cube_org[i][5] & (1 << 2 ) )
			   cube[i][3] |= ( 1 << 1);
			if ( cube_org[i][5] & (1 << 3 ) )
			   cube[i][4] |= ( 1 << 2);
			if ( cube_org[i][5] & (1 << 4 ) )
			   cube[i][5] |= ( 1 << 2);
			if ( cube_org[i][5] & (1 << 5 ) )
			   cube[i][6] |= ( 1 << 3);
			if ( cube_org[i][5] & (1 << 6 ) )
			   cube[i][6] |= ( 1 << 3);
			if ( cube_org[i][5] & (1 << 7 ) )
			   cube[i][7] |= ( 1 << 4);
			if ( cube_org[i][6] & (1 << 0 ) )
			   cube[i][2] |= ( 1 << 0);
			if ( cube_org[i][6] & (1 << 1 ) )
			   cube[i][3] |= ( 1 << 0);
			if ( cube_org[i][6] & (1 << 2 ) )
			   cube[i][3] |= ( 1 << 1);
			if ( cube_org[i][6] & (1 << 3 ) )
			   cube[i][4] |= ( 1 << 1);
			if ( cube_org[i][6] & (1 << 4 ) )
			   cube[i][5] |= ( 1 << 2);
			if ( cube_org[i][6] & (1 << 5 ) )
			   cube[i][6] |= ( 1 << 2);
			if ( cube_org[i][6] & (1 << 6 ) )
			   cube[i][7] |= ( 1 << 3);
			if ( cube_org[i][7] & (1 << 2 ) )
			   cube[i][4] |= ( 1 << 0);
			if ( cube_org[i][7] & (1 << 3 ) )
			   cube[i][5] |= ( 1 << 0);
			if ( cube_org[i][7] & (1 << 4 ) )
			   cube[i][6] |= ( 1 << 1);
			if ( cube_org[i][7] & (1 << 5 ) )
			   cube[i][7] |= ( 1 << 1);
			if ( cube_org[i][7] & (1 << 6 ) )
			   cube[i][7] |= ( 1 << 2);

		}

		Delay_ms(80);
		LED_CUBE_Clear();
		
		/* 75 deg */
		for (i=0; i<8; i++){
			if ( cube_org[i][0] & (1 << 1 ) )
			   cube[i][0] |= ( 1 << 6);
			if ( cube_org[i][0] & (1 << 2 ) )
			   cube[i][1] |= ( 1 << 6);
			if ( cube_org[i][0] & (1 << 3 ) )
			   cube[i][2] |= ( 1 << 7);
			if ( cube_org[i][0] & (1 << 4 ) )
			   cube[i][3] |= ( 1 << 7);
			if ( cube_org[i][0] & (1 << 5 ) )
			   cube[i][4] |= ( 1 << 7);
			if ( cube_org[i][1] & (1 << 1 ) )
			   cube[i][0] |= ( 1 << 5);
			if ( cube_org[i][1] & (1 << 2 ) )
			   cube[i][1] |= ( 1 << 6);
			if ( cube_org[i][1] & (1 << 3 ) )
			   cube[i][2] |= ( 1 << 6);
			if ( cube_org[i][1] & (1 << 4 ) )
			   cube[i][3] |= ( 1 << 6);
			if ( cube_org[i][1] & (1 << 5 ) )
			   cube[i][4] |= ( 1 << 6);
			if ( cube_org[i][1] & (1 << 6 ) )
			   cube[i][5] |= ( 1 << 7);
			if ( cube_org[i][1] & (1 << 7 ) )
			   cube[i][6] |= ( 1 << 7);
			if ( cube_org[i][2] & (1 << 0 ) )
			   cube[i][0] |= ( 1 << 4);
			if ( cube_org[i][2] & (1 << 1 ) )
			   cube[i][1] |= ( 1 << 4);
			if ( cube_org[i][2] & (1 << 2 ) )
			   cube[i][2] |= ( 1 << 5);
			if ( cube_org[i][2] & (1 << 3 ) )
			   cube[i][3] |= ( 1 << 5);
			if ( cube_org[i][2] & (1 << 4 ) )
			   cube[i][4] |= ( 1 << 5);
			if ( cube_org[i][2] & (1 << 5 ) )
			   cube[i][5] |= ( 1 << 5);
			if ( cube_org[i][2] & (1 << 6 ) )
			   cube[i][6] |= ( 1 << 6);
			if ( cube_org[i][2] & (1 << 7 ) )
			   cube[i][6] |= ( 1 << 6);
			if ( cube_org[i][3] & (1 << 0 ) )
			   cube[i][0] |= ( 1 << 3);
			if ( cube_org[i][3] & (1 << 1 ) )
			   cube[i][1] |= ( 1 << 3);
			if ( cube_org[i][3] & (1 << 2 ) )
			   cube[i][2] |= ( 1 << 4);
			if ( cube_org[i][3] & (1 << 3 ) )
			   cube[i][3] |= ( 1 << 4);
			if ( cube_org[i][3] & (1 << 4 ) )
			   cube[i][4] |= ( 1 << 4);
			if ( cube_org[i][3] & (1 << 5 ) )
			   cube[i][5] |= ( 1 << 4);
			if ( cube_org[i][3] & (1 << 6 ) )
			   cube[i][6] |= ( 1 << 5);
			if ( cube_org[i][3] & (1 << 7 ) )
			   cube[i][7] |= ( 1 << 5);
			if ( cube_org[i][4] & (1 << 0 ) )
			   cube[i][0] |= ( 1 << 2);
			if ( cube_org[i][4] & (1 << 1 ) )
			   cube[i][1] |= ( 1 << 2);
			if ( cube_org[i][4] & (1 << 2 ) )
			   cube[i][2] |= ( 1 << 3);
			if ( cube_org[i][4] & (1 << 3 ) )
			   cube[i][3] |= ( 1 << 3);
			if ( cube_org[i][4] & (1 << 4 ) )
			   cube[i][4] |= ( 1 << 3);
			if ( cube_org[i][4] & (1 << 5 ) )
			   cube[i][5] |= ( 1 << 3);
			if ( cube_org[i][4] & (1 << 6 ) )
			   cube[i][6] |= ( 1 << 4);
			if ( cube_org[i][4] & (1 << 7 ) )
			   cube[i][7] |= ( 1 << 4);
			if ( cube_org[i][5] & (1 << 0 ) )
			   cube[i][1] |= ( 1 << 1);
			if ( cube_org[i][5] & (1 << 1 ) )
			   cube[i][1] |= ( 1 << 1);
			if ( cube_org[i][5] & (1 << 2 ) )
			   cube[i][2] |= ( 1 << 2);
			if ( cube_org[i][5] & (1 << 3 ) )
			   cube[i][3] |= ( 1 << 2);
			if ( cube_org[i][5] & (1 << 4 ) )
			   cube[i][4] |= ( 1 << 2);
			if ( cube_org[i][5] & (1 << 5 ) )
			   cube[i][5] |= ( 1 << 2);
			if ( cube_org[i][5] & (1 << 6 ) )
			   cube[i][6] |= ( 1 << 3);
			if ( cube_org[i][5] & (1 << 7 ) )
			   cube[i][7] |= ( 1 << 3);
			if ( cube_org[i][6] & (1 << 0 ) )
			   cube[i][1] |= ( 1 << 0);
			if ( cube_org[i][6] & (1 << 1 ) )
			   cube[i][2] |= ( 1 << 0);
			if ( cube_org[i][6] & (1 << 2 ) )
			   cube[i][3] |= ( 1 << 1);
			if ( cube_org[i][6] & (1 << 3 ) )
			   cube[i][4] |= ( 1 << 1);
			if ( cube_org[i][6] & (1 << 4 ) )
			   cube[i][5] |= ( 1 << 1);
			if ( cube_org[i][6] & (1 << 5 ) )
			   cube[i][6] |= ( 1 << 1);
			if ( cube_org[i][6] & (1 << 6 ) )
			   cube[i][7] |= ( 1 << 2);
			if ( cube_org[i][7] & (1 << 2 ) )
			   cube[i][3] |= ( 1 << 0);
			if ( cube_org[i][7] & (1 << 3 ) )
			   cube[i][4] |= ( 1 << 0);
			if ( cube_org[i][7] & (1 << 4 ) )
			   cube[i][5] |= ( 1 << 0);
			if ( cube_org[i][7] & (1 << 5 ) )
			   cube[i][6] |= ( 1 << 1);
			if ( cube_org[i][7] & (1 << 6 ) )
			   cube[i][7] |= ( 1 << 1);
		}
		
		Delay_ms(80);
		LED_CUBE_Clear();

		for (layer=0; layer<8; layer++) {
			for (x=0; x<8; x++) {
				for (y=0; y<8; y++) {
					if (cube_org[layer][y] & (0x80 >> x)) 
						cube[layer][(7-x)] |= (1 << (7-y));
				}
			}
		}
		Delay_ms(80);
	}
}

void rotate_90_deg (void) {
	char cube_org[8][8];
	int i=0, j=0, x=0, y=0, layer=0;
	
	for (i=0; i<8; i++){
		for (j=0; j<8; j++){
		     cube_org[i][j] = cube[i][j];
		}
	}
	
	LED_CUBE_Clear();
	
	for (layer=0; layer<8; layer++) {
		for (x=0; x<8; x++) {
			for (y=0; y<8; y++) {
				if (cube_org[layer][y] & (0x80 >> x)) 
					cube[layer][(7-x)] |= (1 << (7-y));
			}
		}
	}
}

/**************************************************************************
                            End Of File
***************************************************************************/
