/****************************************************************************
	Luka Penger 2014
	LED CUBE 8x8x8
	LPC17xx
****************************************************************************/

#include "LED_CUBE_8x8x8.h"

void LED_CUBE_Rows_Set(char rows) {
	if (rows & 0x01) {
		LPC_GPIO0->FIOSET |= (1<<6);
	} else {
		LPC_GPIO0->FIOCLR |= (1<<6);
	}
	
	if (rows & 0x02) {
		LPC_GPIO0->FIOSET |= (1<<5);
	} else {
		LPC_GPIO0->FIOCLR |= (1<<5);
	}
	
	if (rows & 0x04) {
		LPC_GPIO4->FIOSET |= (1<<28);
	} else {
		LPC_GPIO4->FIOCLR |= (1<<28);
	}
	
	if (rows & 0x08) {
		LPC_GPIO0->FIOSET |= (1<<4);
	} else {
		LPC_GPIO0->FIOCLR |= (1<<4);
	}
		
	if (rows & 0x10) {
		LPC_GPIO2->FIOSET |= (1<<0);
	} else {
		LPC_GPIO2->FIOCLR |= (1<<0);
	}
		
	if (rows & 0x20) {
		LPC_GPIO0->FIOSET |= (1<<9);
	} else {
		LPC_GPIO0->FIOCLR |= (1<<9);
	}
		
	if (rows & 0x40) {
		LPC_GPIO0->FIOSET |= (1<<7);
	} else {
		LPC_GPIO0->FIOCLR |= (1<<7);
	}
		
	if (rows & 0x80) {
		LPC_GPIO0->FIOSET |= (1<<8);
	} else {
		LPC_GPIO0->FIOCLR |= (1<<8);
	}
}

void LED_CUBE_Row_Set(int rowNum, BOOL state) {
	if(state) {
		switch (rowNum) {
			case 0:
				LPC_GPIO0->FIOSET |= (1<<6);
				break;
			case 1:
				LPC_GPIO0->FIOSET |= (1<<5);
				break;
			case 2:
				LPC_GPIO4->FIOSET |= (1<<28);
				break;
			case 3:
				LPC_GPIO0->FIOSET |= (1<<4);
				break;
			case 4:
				LPC_GPIO2->FIOSET |= (1<<0);
				break;
			case 5:
				LPC_GPIO0->FIOSET |= (1<<9);
				break;
			case 6:
				LPC_GPIO0->FIOSET |= (1<<7);
				break;
			case 7:
				LPC_GPIO0->FIOSET |= (1<<8);
				break;
		}
	} else {
		switch (rowNum) {
			case 0:
				LPC_GPIO0->FIOCLR |= (1<<6);
				break;
			case 1:
				LPC_GPIO0->FIOCLR |= (1<<5);
				break;
			case 2:
				LPC_GPIO4->FIOCLR |= (1<<28);
				break;
			case 3:
				LPC_GPIO0->FIOCLR |= (1<<4);
				break;
			case 4:
				LPC_GPIO2->FIOCLR |= (1<<0);
				break;
			case 5:
				LPC_GPIO0->FIOCLR |= (1<<9);
				break;
			case 6:
				LPC_GPIO0->FIOCLR |= (1<<7);
				break;
			case 7:
				LPC_GPIO0->FIOCLR |= (1<<8);
				break;
		}
	}
}

void LED_CUBE_Columns_Set(char columns1, char columns2, char columns3, char columns4, char columns5, char columns6, char columns7, char columns8) {
	TLC59116_LEDs_Set(LED_CUBE_I2C_PORT_NUM, LED_CUBE_IC1_I2C_ADDRESS, columns1, columns2);
	TLC59116_LEDs_Set(LED_CUBE_I2C_PORT_NUM, LED_CUBE_IC2_I2C_ADDRESS, columns3, columns4);
	TLC59116_LEDs_Set(LED_CUBE_I2C_PORT_NUM, LED_CUBE_IC3_I2C_ADDRESS, columns5, columns6);
	TLC59116_LEDs_Set(LED_CUBE_I2C_PORT_NUM, LED_CUBE_IC4_I2C_ADDRESS, columns7, columns8);
}

void LED_CUBE_Column_Set(int numLed, BOOL state) {
	if (numLed < 16) {
		TLC59116_LED_Set(LED_CUBE_I2C_PORT_NUM, LED_CUBE_IC1_I2C_ADDRESS, numLed, state);
	} else if (numLed >= 16 && numLed < 32) {
		TLC59116_LED_Set(LED_CUBE_I2C_PORT_NUM, LED_CUBE_IC2_I2C_ADDRESS, (numLed - 16), state);
	} else if (numLed >= 32 && numLed < 48) {
		TLC59116_LED_Set(LED_CUBE_I2C_PORT_NUM, LED_CUBE_IC3_I2C_ADDRESS, (numLed - 32), state);
	} else if (numLed >= 48 && numLed < 64) {
		TLC59116_LED_Set(LED_CUBE_I2C_PORT_NUM, LED_CUBE_IC4_I2C_ADDRESS, (numLed - 48), state);
	}
}

void LED_CUBE_Init(void) {
	LPC_GPIO0->FIODIR |= (1<<4) | (1<<5) | (1<<6) | (1<<7) | (1<<8) | (1<<9);
	LPC_GPIO4->FIODIR |= (1<<28);
	LPC_GPIO2->FIODIR |= (1<<0);
	
	LED_CUBE_Row_Set(0, FALSE);
	LED_CUBE_Row_Set(1, FALSE);
	LED_CUBE_Row_Set(2, FALSE);
	LED_CUBE_Row_Set(3, FALSE);
	LED_CUBE_Row_Set(4, FALSE);
	LED_CUBE_Row_Set(5, FALSE);
	LED_CUBE_Row_Set(6, FALSE);
	LED_CUBE_Row_Set(7, FALSE);
	
	TLC59116_I2C_Init(LED_CUBE_I2C_PORT_NUM, LED_CUBE_IC1_I2C_ADDRESS);
	TLC59116_I2C_Init(LED_CUBE_I2C_PORT_NUM, LED_CUBE_IC2_I2C_ADDRESS);
	TLC59116_I2C_Init(LED_CUBE_I2C_PORT_NUM, LED_CUBE_IC3_I2C_ADDRESS);
	TLC59116_I2C_Init(LED_CUBE_I2C_PORT_NUM, LED_CUBE_IC4_I2C_ADDRESS);
}

/**************************************************************************
                            End Of File
***************************************************************************/
