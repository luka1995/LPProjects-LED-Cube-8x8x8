/****************************************************************************
	Luka Penger 2014
	LED CUBE 8x8x8 Translation
	LPC17xx
	Version 4.0.0
****************************************************************************/

#include "LED_CUBE_8x8x8_Translation.h"

extern volatile unsigned char cube[8][8];

void move_z_fwd (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
	int i=0;
	
	/* first loop can count x1 directly, second loop not */
	for (; x1<=x2; x1++){
		for (i=y1; i<=y2; i++){
			cube[x1][i] = (cube[x1][i] << 1);
		}
	}
}

void move_z_rev (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
	int i=0;
	
	for (; x1<=x2; x1++){
		for (i= y1; i<=y2; i++){
			cube[x1][i] = (cube[x1][i] >> 1);
		}
	}
}

void move_y_fwd (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
	int j=0, k=0, i=0;
	
	for (i=7; i>0; i--){
		for (j=x1; j<=x2; j++){
			for (k=y1; k <= y2; k++) {
				if ((cube[i-1][j] & (1 << k))){
					cube[i][j] |= (1 << k);
					cube[i-1][j] &= ~(1 << k);
				} else {
					cube[i-1][j] &= ~(1 << k);
				}
			}
		}
	}
}

void move_y_rev (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
	int j=0, k=0, i=0;
	
	for (i=1; i<8; i++){
		for (j=x1; j<=x2; j++){
			for (k=y1; k<=y2; k++) {
				if ((cube[i][j] & (1 << k))){
					cube[i-1][j] |= (1 << k);
					cube[i][j] &= ~(1 << k);
				} else {
					cube[i-1][j] &= ~(1 << k);
				}
			}
		}
	}
}

void move_x_fwd (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
	int layer=0, j=0, k=0;
	
	for (layer = y1; layer<=y2; layer++) {
		for (j=7; j>0; j--){
			for (k=x1; k<=x2; k++) {
				if ((cube[layer][j-1] & (1 << k))){
					cube[layer][j] |= (1 << k);
					cube[layer][j-1] &= ~(1 << k);
				} else {
					/* delete the pixel anyway */
					cube[layer][j] &= ~(1 << k);
				}
			}

		}
	}
}

void move_x_rev (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
	int layer=0, j=0, k=0;
	
	for (layer = y1; layer<=y2; layer++) {
		for (j=0; j<7; j++){
			for (k = x1; k<=x2; k++) {
				if ((cube[layer][j+1] & (1 << k))){
					cube[layer][j] |= (1 << k);
					cube[layer][j+1] &= ~(1 << k);
				} else {
					cube[layer][j] &= ~(1 << k);
				}
			}

		}
	}
}

/**************************************************************************
                            End Of File
***************************************************************************/
