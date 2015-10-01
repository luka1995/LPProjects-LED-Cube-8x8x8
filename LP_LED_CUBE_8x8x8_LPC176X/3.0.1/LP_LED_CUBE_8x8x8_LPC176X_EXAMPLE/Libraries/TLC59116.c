/****************************************************************************
	Luka Penger 2014
	TLC59116
	LPC17xx
****************************************************************************/

#include "TLC59116.h"

extern volatile uint8_t I2C_MasterBuffer[I2C_PORT_NUM][I2C_BUFSIZE];
extern volatile uint8_t I2C_SlaveBuffer[I2C_PORT_NUM][I2C_BUFSIZE];
extern volatile uint32_t I2C_WriteLength[I2C_PORT_NUM];
extern volatile uint32_t I2C_ReadLength[I2C_PORT_NUM];

char rotateByte(char data) {
	char byte = 0x00;
	
	if (data & 0x03) {
		byte |= 0x0C;
	}
	
	if (data & 0x0C) {
		byte |= 0x03;
	}
	
	if (data & 0x30) {
		byte |= 0xC0;
	}
	
	if (data & 0xC0) {
		byte |= 0x30;
	}
	
	return byte;
}

void TLC59116_I2C_Init(char portNum, char address) {
	if(portNum == 0) {
		I2C0_Init(FALSE);
	} else if (portNum == 1) {
		I2C1_Init(FALSE);
	} else {
		I2C2_Init();
	}
	
	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_MODE1, 0x00);

	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_MODE2, 0x00);

	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM0, 0xFF);
	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM1, 0xFF);
	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM2, 0xFF);
	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM3, 0xFF);
	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM4, 0xFF);
	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM5, 0xFF);
	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM6, 0xFF);
	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM7, 0xFF);
	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM8, 0xFF);
	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM9, 0xFF);
	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM10, 0xFF);
	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM11, 0xFF);
	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM12, 0xFF);
	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM13, 0xFF);
	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM14, 0xFF);
	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM15, 0xFF);
	
	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_GRPPWM, 0xFF);

	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_GRPFREQ, 0x00);

	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_LEDOUT0, TLC59116_LED_OUTPUT_OFF);
	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_LEDOUT1, TLC59116_LED_OUTPUT_OFF);
	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_LEDOUT2, TLC59116_LED_OUTPUT_OFF);
	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_LEDOUT3, TLC59116_LED_OUTPUT_OFF);
}

void TLC59116_LEDs_Set(char portNum, char address, char leds1, char leds2) {
	int i=0;
	
	for (i=0; i<8; i++) {
		TLC59116_LED_Set(portNum, address, i, (leds1 & (1<<i)));
	}

	for (i=8; i<16; i++) {
		TLC59116_LED_Set(portNum, address, i, (leds2 & (1<<(i-8))));
	}
}

void TLC59116_LED_Set(char portNum, char address, char ledNum, BOOL state) {
	char data = 0x00, neww = 0x00;

	if (ledNum < 4) {
		data = TLC59116_I2C_ReadRegister(portNum, address, TLC59116_REGISTER_LEDOUT0);
	
		if (state) {	
			data |= (TLC59116_LED_OUTPUT_GROUP << (ledNum * 2));
		} else {
			data &= ~(TLC59116_LED_OUTPUT_GROUP << (ledNum * 2));
		}
		
		TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_LEDOUT0, data);
	} else if (ledNum >= 4 && ledNum < 8) {
		data = TLC59116_I2C_ReadRegister(portNum, address, TLC59116_REGISTER_LEDOUT1);
	
		if (state) {
			data |= (TLC59116_LED_OUTPUT_GROUP << ((ledNum - 4) * 2));
		} else {
			data &= ~(TLC59116_LED_OUTPUT_GROUP << ((ledNum - 4) * 2));
		}
		
		TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_LEDOUT1, data);
	} else if (ledNum >= 8 && ledNum < 12) {
		data = TLC59116_I2C_ReadRegister(portNum, address, TLC59116_REGISTER_LEDOUT2);
		
		neww |= (TLC59116_LED_OUTPUT_GROUP << ((ledNum - 8) * 2));

		if (state) {
			neww = rotateByte(neww);
			
			data |= neww;
		} else {
			neww = ~rotateByte(neww);
			
			data &= neww;
		}

		TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_LEDOUT2, data);
	} else if (ledNum >= 12 && ledNum < 16) {
		data = TLC59116_I2C_ReadRegister(portNum, address, TLC59116_REGISTER_LEDOUT3);
		
		neww |= (TLC59116_LED_OUTPUT_GROUP << ((ledNum - 12) * 2));

		if (state) {
			neww = rotateByte(neww);
			
			data |= neww;
		} else {
			neww = ~rotateByte(neww);
			
			data &= neww;
		}

		TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_LEDOUT3, data);
	}
}

void TLC59116_LED_Brightness_Set(char portNum, char address, char ledNum, char brightness) {
	switch (ledNum) {
		case 0: TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM0, brightness); break;
		case 1: TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM1, brightness); break;
		case 2: TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM2, brightness); break;
		case 3: TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM3, brightness); break;
		case 4: TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM4, brightness); break;
		case 5: TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM5, brightness); break;
		case 6: TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM6, brightness); break;
		case 7: TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM7, brightness); break;
		case 8: TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM8, brightness); break;
		case 9: TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM9, brightness); break;
		case 10: TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM10, brightness); break;
		case 11: TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM11, brightness); break;
		case 12: TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM12, brightness); break;
		case 13: TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM13, brightness); break;
		case 14: TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM14, brightness); break;
		case 15: TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_PWM15, brightness); break;
	}
}

void TLC59116_All_Brightness_Set(char portNum, char address, char value) {
	TLC59116_I2C_WriteRegister(portNum, address, TLC59116_REGISTER_GRPPWM, value);
}

void TLC59116_I2C_WriteRegister(char portNum, char address, char regAdd, char value) {
	I2C_WriteLength[portNum] = 3;
	I2C_ReadLength[portNum] = 0;
	I2C_MasterBuffer[portNum][0] = address;	// I2C Address
	I2C_MasterBuffer[portNum][1] = regAdd;	// Register								 
	I2C_MasterBuffer[portNum][2] = value;	// Configuration port		
	I2C_Engine(portNum);
}

char TLC59116_I2C_ReadRegister(char portNum, char address, char regAdd) {
	I2C_WriteLength[portNum] = 2;
	I2C_ReadLength[portNum] = 0;
	I2C_MasterBuffer[portNum][0] = address;	// I2C Address
	I2C_MasterBuffer[portNum][1] = regAdd;	// Register					
	I2C_Engine(portNum);
	
	I2C_WriteLength[portNum] = 1;
	I2C_ReadLength[portNum] = 1;
	I2C_MasterBuffer[portNum][0] = (address | I2C_READ_BIT);	// I2C Address			
	I2C_Engine(portNum);
	
	return (char)I2C_SlaveBuffer[portNum][0];
}

/**************************************************************************
                            End Of File
***************************************************************************/
