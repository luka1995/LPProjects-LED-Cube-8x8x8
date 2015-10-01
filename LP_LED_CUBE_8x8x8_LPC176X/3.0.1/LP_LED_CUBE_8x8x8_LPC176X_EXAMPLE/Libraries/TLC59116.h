/****************************************************************************
	Luka Penger 2014
	TLC59116
	LPC17xx
****************************************************************************/
#ifndef __TLC59116_H 
#define __TLC59116_H

#include <LPC17xx.H>
#include <I2C.h>

#define TLC59116_REGISTER_MODE1 								0x00
#define TLC59116_REGISTER_MODE2 								0x01
#define TLC59116_REGISTER_PWM0 									0x02
#define TLC59116_REGISTER_PWM1 									0x03
#define TLC59116_REGISTER_PWM2 									0x04
#define TLC59116_REGISTER_PWM3									0x05
#define TLC59116_REGISTER_PWM4 									0x06
#define TLC59116_REGISTER_PWM5 									0x07
#define TLC59116_REGISTER_PWM6 									0x08
#define TLC59116_REGISTER_PWM7 									0x09
#define TLC59116_REGISTER_PWM8 									0x0A
#define TLC59116_REGISTER_PWM9 									0x0B
#define TLC59116_REGISTER_PWM10 								0x0C
#define TLC59116_REGISTER_PWM11 								0x0D
#define TLC59116_REGISTER_PWM12 								0x0E
#define TLC59116_REGISTER_PWM13 								0x0F
#define TLC59116_REGISTER_PWM14 								0x10
#define TLC59116_REGISTER_PWM15 								0x11

#define TLC59116_REGISTER_GRPPWM 								0x12
#define TLC59116_REGISTER_GRPFREQ								0x13
#define TLC59116_REGISTER_LEDOUT0 							0x14
#define TLC59116_REGISTER_LEDOUT1 							0x15
#define TLC59116_REGISTER_LEDOUT2 							0x16
#define TLC59116_REGISTER_LEDOUT3 							0x17
#define TLC59116_REGISTER_SUBADR1 							0x18
#define TLC59116_REGISTER_SUBADR2 							0x19
#define TLC59116_REGISTER_SUBADR3 							0x1A
#define TLC59116_REGISTER_ALLCALLADR 						0x1B
#define TLC59116_REGISTER_IREF 									0x1C
#define TLC59116_REGISTER_EFLAG1 								0x1D
#define TLC59116_REGISTER_EFLAG2 								0x1E

#define TLC59116_LED_OUTPUT_OFF                 0x00
#define TLC59116_LED_OUTPUT_GROUP               0x03
#define TLC59116_LED_OUTPUT_ALL               	0xFF

void TLC59116_I2C_Init(char portNum, char address);
void TLC59116_LEDs_Set(char portNum, char address, char leds1, char leds2);
void TLC59116_LED_Set(char portNum, char address, char ledNum, BOOL state);
void TLC59116_LED_Brightness_Set(char portNum, char address, char ledNum, char brightness);
void TLC59116_All_Brightness_Set(char portNum, char address, char value);
void TLC59116_I2C_WriteRegister(char portNum, char address, char regAdd, char value);
char TLC59116_I2C_ReadRegister(char portNum, char address, char regAdd);

#endif /* end __TLC59116_H */
/***************************************************************************
                            End Of File
***************************************************************************/
