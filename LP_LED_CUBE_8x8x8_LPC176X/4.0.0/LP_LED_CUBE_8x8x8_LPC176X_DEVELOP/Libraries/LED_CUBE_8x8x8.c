/****************************************************************************
	Luka Penger 2014
	LED CUBE 8x8x8
	LPC17xx
	Version 4.0.0
****************************************************************************/

#include "LED_CUBE_8x8x8.h"

// Functions

volatile unsigned char cube[8][8];

void LED_CUBE_Frame_show (void) {
	int i=0, j=0;
	
	LED_CUBE_Layers_Set(0x00);
	
	__nop();
	
	for (i=0; i<8 ;i++) {
		for (j=0; j<8; j++) {
			LED_CUBE_Outputs_Set(~cube[i][j]);
			__nop();
			LED_CUBE_Clock_Set(j, TRUE);
			__nop();
			LED_CUBE_Clock_Set(j, FALSE);
			__nop();
		}
		
		LED_CUBE_Layer_Set(i, TRUE);
		Delay_us(100);
		LED_CUBE_Layers_Set(0x00);
		
		__nop();
	}
}

void LED_CUBE_Timer (void) {
	int j=0;
	static int cube_show_layer = 0;
	
	LED_CUBE_Layers_Set(0x00);
	
	__nop();
	
	for (j=0; j<8; j++) {
		LED_CUBE_Outputs_Set(~cube[cube_show_layer][j]);
		__nop();
		LED_CUBE_Clock_Set(j, TRUE);
		__nop();
		LED_CUBE_Clock_Set(j, FALSE);
		__nop();
	}

	LED_CUBE_Layer_Set(cube_show_layer, TRUE);
	Delay_us(100);
	LED_CUBE_Layers_Set(0x00);

	__nop();
	
	if (cube_show_layer < 7) {
		cube_show_layer++;
	} else {
		cube_show_layer = 0;
	}
}

void LED_CUBE_Clear (void) {
	int i=0, j=0;
	
	for (i=0; i<8; i++) {
		for (j=0; j<8; j++){
			cube[i][j] = 0x00;
		}
	}
}

void LED_CUBE_Clear_layer (uint8_t layer) {
	int j=0;
	
	for (j=0; j<8; j++){
		cube[layer][j] = 0x00;
	}
}

void LED_CUBE_Full (void) {
	int i=0, j=0;
	
	for (i=0; i<8; i++){
		for (j=0; j<8; j++){
			cube[i][j] = 0xFF;
		}
	}
}

void LED_CUBE_Cube_3 (void) {
	cube[0][0] = 7;
	cube[0][1] = 7;
	cube[0][2] = 7;
	cube[1][0] = 7;
	cube[1][1] = 7;
	cube[1][2] = 7;
	cube[2][0] = 7;
	cube[2][1] = 7;
	cube[2][2] = 7;
}

void LED_CUBE_Cube_4_line (void) {
	cube[0][0] = 15;
	cube[0][1] = 9;
	cube[0][2] = 9;
	cube[0][3] = 15;
	cube[1][0] = 9;
	cube[1][3] = 9;
	cube[2][0] = 9;
	cube[2][3] = 9;
	cube[3][0] = 15;
	cube[3][1] = 9;
	cube[3][2] = 9;
	cube[3][3] = 15;
}

void LED_CUBE_Random (void) {
	int i=0, j=0;
	
	for (i=0; i<8; i++ ){
		for (j=0; j<8; j++) {
			cube[i][j] = (rand() % 255);
		}
	}
}

// one layer

void LED_CUBE_Test_z (void) {
	int i=0, j=0;
	
	for (i=0; i<8; i++){
		for (j=0; j<8; j++){
			cube[i][j] = 1;
		}
	}
}

void LED_CUBE_Test_y (void) {
	int i=0;
	
	for (i=0; i<8; i++){
		cube[0][i] = 255;
	}
}

void LED_CUBE_Test_x (void) {
	int i=0;
	
	for (i=0; i<8; i++) {
		cube[i][0] = 255;
	}
}

// HW Functions

void LED_CUBE_Layers_Set (char value) {
	if (value & 0x80) {
		LPC_GPIO2->FIOSET |= (1<<12);
	} else {
		LPC_GPIO2->FIOCLR |= (1<<12);
	}
	
	if (value & 0x40) {
		LPC_GPIO2->FIOSET |= (1<<13);
	} else {
		LPC_GPIO2->FIOCLR |= (1<<13);
	}
	
	if (value & 0x20) {
		LPC_GPIO0->FIOSET |= (1<<11);
	} else {
		LPC_GPIO0->FIOCLR |= (1<<11);
	}
	
	if (value & 0x10) {
		LPC_GPIO2->FIOSET |= (1<<11);
	} else {
		LPC_GPIO2->FIOCLR |= (1<<11);
	}
		
	if (value & 0x08) {
		LPC_GPIO0->FIOSET |= (1<<21);
	} else {
		LPC_GPIO0->FIOCLR |= (1<<21);
	}
		
	if (value & 0x04) {
		LPC_GPIO0->FIOSET |= (1<<22);
	} else {
		LPC_GPIO0->FIOCLR |= (1<<22);
	}
		
	if (value & 0x02) {
		LPC_GPIO2->FIOSET |= (1<<8);
	} else {
		LPC_GPIO2->FIOCLR |= (1<<8);
	}
		
	if (value & 0x01) {
		LPC_GPIO2->FIOSET |= (1<<9);
	} else {
		LPC_GPIO2->FIOCLR |= (1<<9);
	}
}

void LED_CUBE_Layer_Set (int layerNum, BOOL state) {
	if(state) {
		switch (layerNum) {
			case 0:
				LPC_GPIO2->FIOSET |= (1<<12);
				break;
			case 1:
				LPC_GPIO2->FIOSET |= (1<<13);
				break;
			case 2:
				LPC_GPIO0->FIOSET |= (1<<11);
				break;
			case 3:
				LPC_GPIO2->FIOSET |= (1<<11);
				break;
			case 4:
				LPC_GPIO0->FIOSET |= (1<<21);
				break;
			case 5:
				LPC_GPIO0->FIOSET |= (1<<22);
				break;
			case 6:
				LPC_GPIO2->FIOSET |= (1<<8);
				break;
			case 7:
				LPC_GPIO2->FIOSET |= (1<<9);
				break;
		}
	} else {
		switch (layerNum) {
			case 0:
				LPC_GPIO2->FIOCLR |= (1<<12);
				break;
			case 1:
				LPC_GPIO2->FIOCLR |= (1<<13);
				break;
			case 2:
				LPC_GPIO0->FIOCLR |= (1<<11);
				break;
			case 3:
				LPC_GPIO2->FIOCLR |= (1<<11);
				break;
			case 4:
				LPC_GPIO0->FIOCLR |= (1<<21);
				break;
			case 5:
				LPC_GPIO0->FIOCLR |= (1<<22);
				break;
			case 6:
				LPC_GPIO2->FIOCLR |= (1<<8);
				break;
			case 7:
				LPC_GPIO2->FIOCLR |= (1<<9);
				break;
		}
	}
}

void LED_CUBE_Clocks_Set (char value) {
	if (value & 0x01) {
		LPC_GPIO2->FIOSET |= (1<<1);
	} else {
		LPC_GPIO2->FIOCLR |= (1<<1);
	}
	
	if (value & 0x02) {
		LPC_GPIO2->FIOSET |= (1<<0);
	} else {
		LPC_GPIO2->FIOCLR |= (1<<0);
	}
	
	if (value & 0x04) {
		LPC_GPIO2->FIOSET |= (1<<3);
	} else {
		LPC_GPIO2->FIOCLR |= (1<<3);
	}
	
	if (value & 0x08) {
		LPC_GPIO2->FIOSET |= (1<<2);
	} else {
		LPC_GPIO2->FIOCLR |= (1<<2);
	}
		
	if (value & 0x10) {
		LPC_GPIO2->FIOSET |= (1<<5);
	} else {
		LPC_GPIO2->FIOCLR |= (1<<5);
	}
		
	if (value & 0x20) {
		LPC_GPIO2->FIOSET |= (1<<4);
	} else {
		LPC_GPIO2->FIOCLR |= (1<<4);
	}
		
	if (value & 0x40) {
		LPC_GPIO2->FIOSET |= (1<<7);
	} else {
		LPC_GPIO2->FIOCLR |= (1<<7);
	}
		
	if (value & 0x80) {
		LPC_GPIO2->FIOSET |= (1<<6);
	} else {
		LPC_GPIO2->FIOCLR |= (1<<6);
	}
}

void LED_CUBE_Clock_Set (int clockNum, BOOL state) {
	if(state) {
		switch (clockNum) {
			case 0:
				LPC_GPIO2->FIOSET |= (1<<1);
				break;
			case 1:
				LPC_GPIO2->FIOSET |= (1<<0);
				break;
			case 2:
				LPC_GPIO2->FIOSET |= (1<<3);
				break;
			case 3:
				LPC_GPIO2->FIOSET |= (1<<2);
				break;
			case 4:
				LPC_GPIO2->FIOSET |= (1<<5);
				break;
			case 5:
				LPC_GPIO2->FIOSET |= (1<<4);
				break;
			case 6:
				LPC_GPIO2->FIOSET |= (1<<7);
				break;
			case 7:
				LPC_GPIO2->FIOSET |= (1<<6);
				break;
		}
	} else {
		switch (clockNum) {
			case 0:
				LPC_GPIO2->FIOCLR |= (1<<1);
				break;
			case 1:
				LPC_GPIO2->FIOCLR |= (1<<0);
				break;
			case 2:
				LPC_GPIO2->FIOCLR |= (1<<3);
				break;
			case 3:
				LPC_GPIO2->FIOCLR |= (1<<2);
				break;
			case 4:
				LPC_GPIO2->FIOCLR |= (1<<5);
				break;
			case 5:
				LPC_GPIO2->FIOCLR |= (1<<4);
				break;
			case 6:
				LPC_GPIO2->FIOCLR |= (1<<7);
				break;
			case 7:
				LPC_GPIO2->FIOCLR |= (1<<6);
				break;
		}
	}
}

void LED_CUBE_Outputs_Set (char value) {
	if (value & 0x01) {
		LPC_GPIO4->FIOSET |= (1<<28);
	} else {
		LPC_GPIO4->FIOCLR |= (1<<28);
	}
	
	if (value & 0x02) {
		LPC_GPIO4->FIOSET |= (1<<29);
	} else {
		LPC_GPIO4->FIOCLR |= (1<<29);
	}
	
	if (value & 0x04) {
		LPC_GPIO0->FIOSET |= (1<<5);
	} else {
		LPC_GPIO0->FIOCLR |= (1<<5);
	}
	
	if (value & 0x08) {
		LPC_GPIO0->FIOSET |= (1<<4);
	} else {
		LPC_GPIO0->FIOCLR |= (1<<4);
	}
		
	if (value & 0x10) {
		LPC_GPIO0->FIOSET |= (1<<7);
	} else {
		LPC_GPIO0->FIOCLR |= (1<<7);
	}
		
	if (value & 0x20) {
		LPC_GPIO0->FIOSET |= (1<<6);
	} else {
		LPC_GPIO0->FIOCLR |= (1<<6);
	}
		
	if (value & 0x40) {
		LPC_GPIO0->FIOSET |= (1<<9);
	} else {
		LPC_GPIO0->FIOCLR |= (1<<9);
	}
		
	if (value & 0x80) {
		LPC_GPIO0->FIOSET |= (1<<8);
	} else {
		LPC_GPIO0->FIOCLR |= (1<<8);
	}
}

void LED_CUBE_Init (void) {
	// Layers
	LPC_GPIO2->FIODIR |= (1<<8) | (1<<9) | (1<<11) | (1<<12) | (1<<13);
	LPC_GPIO0->FIODIR |= (1<<21) | (1<<22) | (1<<11);
	
	LPC_GPIO2->FIOCLR |= (1<<8) | (1<<9) | (1<<11) | (1<<12) | (1<<13);
	LPC_GPIO0->FIOCLR |= (1<<21) | (1<<22) | (1<<11);;
	
	// Clocks
	LPC_GPIO2->FIODIR |= (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);
	
	LPC_GPIO2->FIOCLR |= (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);
	
	// Outputs
	LPC_GPIO0->FIODIR |= (1<<4) | (1<<5) | (1<<6) | (1<<7) | (1<<8) | (1<<9);
	LPC_GPIO4->FIODIR |= (1<<28) | (1<<29);
	
	LPC_GPIO0->FIOSET |= (1<<4) | (1<<5) | (1<<6) | (1<<7) | (1<<8) | (1<<9);
	LPC_GPIO4->FIOSET |= (1<<28) | (1<<29);
	
	
	LED_CUBE_Clear();
}

/**************************************************************************
                            End Of File
***************************************************************************/
