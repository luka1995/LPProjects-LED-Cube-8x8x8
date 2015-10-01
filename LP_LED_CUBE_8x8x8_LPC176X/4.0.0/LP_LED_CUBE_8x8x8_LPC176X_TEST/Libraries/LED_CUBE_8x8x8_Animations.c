/****************************************************************************
	Luka Penger 2014
	LED CUBE 8x8x8 Animations
	LPC17xx
	Version 4.0.0
****************************************************************************/

#include "LED_CUBE_8x8x8_Animations.h"

extern volatile unsigned char cube[8][8];

void LED_CUBE_Animation_Char (char ch, unsigned int z) {
	switch (ch) {
		case '0':
			cube[0][2] |= z;
			cube[0][3] |= z;
			cube[0][4] |= z;
			cube[1][1] |= z;
			cube[1][5] |= z;
			cube[2][1] |= z;
			cube[2][2] |= z;
			cube[2][5] |= z;
			cube[3][1] |= z;
			cube[3][3] |= z;
			cube[3][5] |= z;
			cube[4][1] |= z;
			cube[4][4] |= z;
			cube[4][5] |= z;
			cube[5][1] |= z;
			cube[5][5] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			break;
		case '1':
		  cube[0][2] |= z;
			cube[0][3] |= z;
			cube[0][4] |= z;
			cube[1][3] |= z;
			cube[2][3] |= z;
			cube[3][3] |= z;
			cube[4][3] |= z;
			cube[5][2] |= z;
			cube[5][3] |= z;
			cube[6][3] |= z;
			break;
		case '2':
		  cube[0][1] |= z;
			cube[0][2] |= z;
			cube[0][3] |= z;
			cube[0][4] |= z;
			cube[0][5] |= z;
			cube[1][2] |= z;
			cube[2][3] |= z;
			cube[3][4] |= z;
			cube[4][5] |= z;
			cube[5][1] |= z;
			cube[5][5] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			break;
		case '3':
		  cube[0][2] |= z;
			cube[0][3] |= z;
			cube[0][4] |= z;
			cube[1][1] |= z;
			cube[1][5] |= z;
			cube[2][5] |= z;
			cube[3][4] |= z;
			cube[4][3] |= z;
			cube[5][4] |= z;
			cube[6][1] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			cube[6][5] |= z;
			break;
		case '4':
		  cube[0][4] |= z;
			cube[1][4] |= z;
			cube[2][1] |= z;
			cube[2][2] |= z;
			cube[2][3] |= z;
			cube[2][4] |= z;
			cube[2][5] |= z;
			cube[3][1] |= z;
			cube[3][4] |= z;
			cube[4][2] |= z;
			cube[4][4] |= z;
			cube[5][3] |= z;
			cube[5][4] |= z;
			cube[6][4] |= z;
			break;
		case '5':
		  cube[0][2] |= z;
			cube[0][3] |= z;
			cube[0][4] |= z;
			cube[1][1] |= z;
			cube[1][5] |= z;
			cube[2][5] |= z;
			cube[3][5] |= z;
			cube[4][1] |= z;
			cube[4][2] |= z;
			cube[4][3] |= z;
			cube[4][4] |= z;
			cube[5][1] |= z;
			cube[6][1] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			cube[6][5] |= z;
			break;
		case '6':
		  cube[0][2] |= z;
			cube[0][3] |= z;
			cube[0][4] |= z;
			cube[1][1] |= z;
			cube[1][5] |= z;
			cube[2][1] |= z;
			cube[2][5] |= z;
			cube[3][1] |= z;
			cube[3][2] |= z;
			cube[3][3] |= z;
			cube[3][4] |= z;
			cube[4][1] |= z;
			cube[5][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			break;
		case '7':
		  cube[0][2] |= z;
			cube[1][2] |= z;
			cube[2][2] |= z;
			cube[3][3] |= z;
			cube[4][4] |= z;
			cube[5][5] |= z;
			cube[6][1] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			cube[6][5] |= z;
			break;
		case '8':
		  cube[0][2] |= z;
			cube[0][3] |= z;
			cube[0][4] |= z;
			cube[1][1] |= z;
			cube[1][5] |= z;
			cube[2][1] |= z;
			cube[2][5] |= z;
			cube[3][2] |= z;
			cube[3][3] |= z;
			cube[3][4] |= z;
			cube[4][1] |= z;
			cube[4][5] |= z;
			cube[5][1] |= z;
			cube[5][5] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			break;
		case '9':
		  cube[0][2] |= z;
			cube[0][3] |= z;
			cube[1][4] |= z;
			cube[2][5] |= z;
			cube[3][2] |= z;
			cube[3][3] |= z;
			cube[3][4] |= z;
			cube[3][5] |= z;
			cube[4][1] |= z;
			cube[4][5] |= z;
			cube[5][1] |= z;
			cube[5][5] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			break;

		case '!':
			cube[0][3] |= z;
			cube[3][3] |= z;
			cube[4][3] |= z;
			cube[5][2] |= z;
			cube[5][3] |= z;
			cube[5][4] |= z;
			cube[6][1] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			cube[6][5] |= z;
			break;
		case ':':
			cube[1][2] |= z;
			cube[1][3] |= z;
			cube[2][2] |= z;
			cube[2][3] |= z;
			cube[4][2] |= z;
			cube[4][3] |= z;
			cube[5][2] |= z;
			cube[5][3] |= z;
			break;
		case '.':
			cube[1][2] |= z;
			cube[1][3] |= z;
			cube[2][2] |= z;
			cube[2][3] |= z;
			break;
		case '?':
			cube[0][3] |= z;
			cube[2][3] |= z;
			cube[3][4] |= z;
			cube[4][5] |= z;
			cube[5][1] |= z;
			cube[5][5] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			break;
		case '&':
			cube[0][2] |= z;
			cube[0][3] |= z;
			cube[0][5] |= z;
			cube[1][1] |= z;
			cube[1][4] |= z;
			cube[2][1] |= z;
			cube[2][3] |= z;
			cube[2][5] |= z;
			cube[3][2] |= z;
			cube[4][1] |= z;
			cube[4][3] |= z;
			cube[5][1] |= z;
			cube[5][4] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			break;
		case 'a':
		  cube[0][1] |= z;
			cube[0][5] |= z;
			cube[1][1] |= z;
			cube[1][5] |= z;
			cube[2][1] |= z;
			cube[2][2] |= z;
			cube[2][3] |= z;
			cube[2][4] |= z;
			cube[2][5] |= z;
			cube[3][1] |= z;
			cube[3][5] |= z;
			cube[4][1] |= z;
			cube[4][5] |= z;
			cube[5][1] |= z;
			cube[5][5] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			break;
		case 'b':
		  cube[0][1] |= z;
			cube[0][2] |= z;
			cube[0][3] |= z;
			cube[0][4] |= z;
			cube[1][1] |= z;
			cube[1][5] |= z;
			cube[2][1] |= z;
			cube[2][5] |= z;
			cube[3][1] |= z;
			cube[3][2] |= z;
			cube[3][3] |= z;
			cube[3][4] |= z;
			cube[4][1] |= z;
			cube[4][5] |= z;
			cube[5][1] |= z;
			cube[5][5] |= z;
			cube[6][1] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			break;
		case 'c':
		  cube[0][2] |= z;
			cube[0][3] |= z;
			cube[0][4] |= z;
			cube[1][5] |= z;
			cube[1][1] |= z;
			cube[2][1] |= z;
			cube[3][1] |= z;
			cube[4][1] |= z;
			cube[5][1] |= z;
			cube[5][5] |= z;
			cube[5][1] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			break;
		case 'd':
		  cube[0][1] |= z;
			cube[0][2] |= z;
			cube[0][3] |= z;
			cube[1][1] |= z;
			cube[1][4] |= z;
			cube[2][1] |= z;
			cube[2][5] |= z;
			cube[3][1] |= z;
			cube[3][5] |= z;
			cube[4][1] |= z;
			cube[4][5] |= z;
			cube[5][1] |= z;
			cube[5][4] |= z;
			cube[6][1] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			break;
		case 'e':
			cube[0][1] |= z;
			cube[0][2] |= z;
			cube[0][3] |= z;
			cube[0][4] |= z;
			cube[0][5] |= z;
			cube[1][1] |= z;
			cube[2][1] |= z;
			cube[3][1] |= z;
			cube[3][2] |= z;
			cube[3][3] |= z;
			cube[3][4] |= z;
			cube[4][1] |= z;
			cube[5][1] |= z;
			cube[6][1] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			cube[6][5] |= z;
			break;
		case 'f':
			cube[0][1] |= z;
			cube[1][1] |= z;
			cube[2][1] |= z;
			cube[3][1] |= z;
			cube[3][2] |= z;
			cube[3][3] |= z;
			cube[3][4] |= z;
			cube[4][1] |= z;
			cube[5][1] |= z;
			cube[6][1] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			cube[6][5] |= z;
			break;
		case 'g':
			cube[0][2] |= z;
			cube[0][3] |= z;
			cube[0][4] |= z;
			cube[0][5] |= z;
			cube[1][1] |= z;
			cube[1][5] |= z;
			cube[2][1] |= z;
			cube[2][5] |= z;
			cube[3][1] |= z;
			cube[3][3] |= z;
			cube[3][4] |= z;
			cube[3][5] |= z;
			cube[4][1] |= z;
			cube[5][1] |= z;
			cube[5][5] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			break;
		case 'h':
			cube[0][1] |= z;
			cube[0][5] |= z;
			cube[1][1] |= z;
			cube[1][5] |= z;
			cube[2][1] |= z;
			cube[2][5] |= z;
			cube[3][1] |= z;
			cube[3][2] |= z;
			cube[3][3] |= z;
			cube[3][4] |= z;
			cube[3][5] |= z;
			cube[4][1] |= z;
			cube[4][5] |= z;
			cube[5][1] |= z;
			cube[5][5] |= z;
			cube[6][1] |= z;
			cube[6][5] |= z;
			break;
		case 'i':
			cube[0][2] |= z;
			cube[0][3] |= z;
			cube[0][4] |= z;
			cube[1][3] |= z;
			cube[2][3] |= z;
			cube[3][3] |= z;
			cube[4][3] |= z;
			cube[5][3] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			break;
		case 'j':
			cube[0][2] |= z;
			cube[0][3] |= z;
			cube[1][1] |= z;
			cube[1][4] |= z;
			cube[2][4] |= z;
			cube[3][4] |= z;
			cube[4][4] |= z;
			cube[5][4] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			cube[6][5] |= z;
			break;
		case 'k':
			cube[0][1] |= z;
			cube[0][5] |= z;
			cube[1][1] |= z;
			cube[1][4] |= z;
			cube[2][1] |= z;
			cube[2][3] |= z;
			cube[3][1] |= z;
			cube[3][2] |= z;
			cube[4][1] |= z;
			cube[4][3] |= z;
			cube[5][1] |= z;
			cube[5][4] |= z;
			cube[6][1] |= z;
			cube[6][5] |= z;
			break;
		case 'l':
			cube[0][1] |= z;
			cube[0][2] |= z;
			cube[0][3] |= z;
			cube[0][4] |= z;
			cube[0][5] |= z;
			cube[1][1] |= z;
			cube[2][1] |= z;
			cube[3][1] |= z;
			cube[4][1] |= z;
			cube[5][1] |= z;
			cube[6][1] |= z;
			break;
		case 'm':
			cube[0][1] |= z;
			cube[0][5] |= z;
			cube[1][1] |= z;
			cube[1][5] |= z;
			cube[2][1] |= z;
			cube[2][5] |= z;
			cube[3][1] |= z;
			cube[3][3] |= z;
			cube[3][5] |= z;
			cube[4][1] |= z;
			cube[4][3] |= z;
			cube[4][5] |= z;
			cube[5][1] |= z;
			cube[5][2] |= z;
			cube[5][4] |= z;
			cube[5][5] |= z;
			cube[6][1] |= z;
			cube[6][5] |= z;
			break;
		case 'n':
			cube[0][1] |= z;
			cube[0][5] |= z;
			cube[1][1] |= z;
			cube[1][5] |= z;
			cube[2][1] |= z;
			cube[2][4] |= z;
			cube[2][5] |= z;
			cube[3][1] |= z;
			cube[3][3] |= z;
			cube[3][5] |= z;
			cube[4][1] |= z;
			cube[4][2] |= z;
			cube[4][5] |= z;
			cube[5][1] |= z;
			cube[5][5] |= z;
			cube[6][1] |= z;
			cube[6][5] |= z;
			break;
		case 'o':
			cube[0][2] |= z;
			cube[0][3] |= z;
			cube[0][4] |= z;
			cube[1][1] |= z;
			cube[1][5] |= z;
			cube[2][1] |= z;
			cube[2][5] |= z;
			cube[3][1] |= z;
			cube[3][5] |= z;
			cube[4][1] |= z;
			cube[4][5] |= z;
			cube[5][1] |= z;
			cube[5][5] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			break;
		case 'p':
			cube[0][1] |= z;
			cube[1][1] |= z;
			cube[2][1] |= z;
			cube[3][1] |= z;
			cube[3][2] |= z;
			cube[3][3] |= z;
			cube[3][4] |= z;
			cube[4][1] |= z;
			cube[4][5] |= z;
			cube[5][1] |= z;
			cube[5][5] |= z;
			cube[6][1] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			break;
		case 'q': 
			cube[0][2] |= z;
			cube[0][3] |= z;
			cube[0][5] |= z;
			cube[1][1] |= z;
			cube[1][4] |= z;
			cube[2][1] |= z;
			cube[2][3] |= z;
			cube[2][5] |= z;
			cube[3][1] |= z;
			cube[3][5] |= z;
			cube[4][1] |= z;
			cube[4][5] |= z;
			cube[5][1] |= z;
			cube[5][5] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			break;
		case 'r':
			cube[0][1] |= z;
			cube[0][5] |= z;
			cube[1][1] |= z;
			cube[1][4] |= z;
			cube[2][1] |= z;
			cube[2][3] |= z;
			cube[3][1] |= z;
			cube[3][2] |= z;
			cube[3][3] |= z;
			cube[3][4] |= z;
			cube[4][1] |= z;
			cube[4][5] |= z;
			cube[5][1] |= z;
			cube[5][5] |= z;
			cube[6][1] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			break;
		case 's':
			cube[0][1] |= z;
			cube[0][2] |= z;
			cube[0][3] |= z;
			cube[0][4] |= z;
			cube[1][5] |= z;
			cube[2][5] |= z;
			cube[3][2] |= z;
			cube[3][3] |= z;
			cube[3][4] |= z;
			cube[4][1] |= z;
			cube[5][1] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			cube[6][5] |= z;
			break;
		case 't':
			cube[0][3] |= z;
			cube[1][3] |= z;
			cube[2][3] |= z;
			cube[3][3] |= z;
			cube[4][3] |= z;
			cube[5][3] |= z;
			cube[6][1] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			cube[6][5] |= z;
			break;
		case 'u':
			cube[0][2] |= z;
			cube[0][3] |= z;
			cube[0][4] |= z;
			cube[1][1] |= z;
			cube[1][5] |= z;
			cube[2][1] |= z;
			cube[2][5] |= z;
			cube[3][1] |= z;
			cube[3][5] |= z;
			cube[4][1] |= z;
			cube[4][5] |= z;
			cube[5][1] |= z;
			cube[5][5] |= z;
			cube[6][1] |= z;
			cube[6][5] |= z;
			break;
		case 'v':
			cube[0][3] |= z;
			cube[1][2] |= z;
			cube[1][4] |= z;
			cube[2][1] |= z;
			cube[2][5] |= z;
			cube[3][1] |= z;
			cube[3][5] |= z;
			cube[4][1] |= z;
			cube[4][5] |= z;
			cube[5][1] |= z;
			cube[5][5] |= z;
			cube[6][1] |= z;
			cube[6][5] |= z;
			break;
		case 'w':
			cube[0][2] |= z;
			cube[0][4] |= z;
			cube[1][1] |= z;
			cube[1][3] |= z;
			cube[1][5] |= z;
			cube[2][1] |= z;
			cube[2][3] |= z;
			cube[2][5] |= z;
			cube[3][1] |= z;
			cube[3][3] |= z;
			cube[3][5] |= z;
			cube[4][1] |= z;
			cube[4][5] |= z;
			cube[5][1] |= z;
			cube[5][5] |= z;
			cube[6][1] |= z;
			cube[6][5] |= z;
			break;
		case 'x': 
			cube[0][1] |= z;
			cube[0][5] |= z;
			cube[1][1] |= z;
			cube[1][5] |= z;
			cube[2][2] |= z;
			cube[2][4] |= z;
			cube[3][3] |= z;
			cube[4][2] |= z;
			cube[4][4] |= z;
			cube[5][1] |= z;
			cube[5][5] |= z;
			cube[6][1] |= z;
			cube[6][5] |= z;
			break;
		case 'y':
			cube[0][3] |= z;
			cube[1][3] |= z;
			cube[2][3] |= z;
			cube[3][2] |= z;
			cube[3][4] |= z;
			cube[4][1] |= z;
			cube[4][5] |= z;
			cube[5][1] |= z;
			cube[5][5] |= z;
			cube[6][1] |= z;
			cube[6][5] |= z;
			break;
		case 'z':
			cube[0][1] |= z;
			cube[0][2] |= z;
			cube[0][3] |= z;
			cube[0][4] |= z;
			cube[0][5] |= z;
			cube[1][1] |= z;
			cube[2][2] |= z;
			cube[3][3] |= z;
			cube[4][4] |= z;
			cube[5][5] |= z;
			cube[6][1] |= z;
			cube[6][2] |= z;
			cube[6][3] |= z;
			cube[6][4] |= z;
			cube[6][5] |= z;
			break;
		default:
			break;
	}
}

void LED_CUBE_Animation_String_to_front (char *string) {
	int i=0;

	while (*string) {
		for (i=8; i>0; i--) {
			LED_CUBE_Clear();
			LED_CUBE_Animation_Char(tolower(*string), (1<<(i-1)));
			Delay_ms(100);
		}
		string++;
	}
}

void LED_CUBE_Animation_Move_belt_left (char *belt) {
	int i=0;
	
	for (i=25; i>1; i--){
		belt[i-1] = belt[i-2];
	}
	
	belt[0] = 0;
}

void LED_CUBE_Animation_Show_belt (char *belt) {
	int i=0, j=0;
	
	LED_CUBE_Clear();
	
	/* right side */
	for (i=5; i<=11; i++){
		for (j=0; j<8; j++){
			if (belt[i] & (1 << j))
				cube[j][7] |= (1 << (12-i));
		}
	}
	/* front side */
	for (i=12; i<=17; i++){
		for (j=0; j<8; j++){
			if (belt[i] & (1 << j))
				cube[j][18-i] |= (1 << 0);
		}
	}
	/* left side */
	for (i = 18; i<=24; i++){
		for (j = 0; j<8; j++){
			if (belt[i] & (1 << j))
				cube[j][0] |= (1 << (i-17));
		}
	}
	
	Delay_ms(200);
}

void LED_CUBE_Animation_Set_char_to_belt (char character, char *belt) {
	int layer=0, i=0;
	
	LED_CUBE_Clear();

	LED_CUBE_Animation_Char(tolower(character), 1);
	
	for (layer=0; layer<8; layer++) {
		for (i=1; i<6; i++){
			if (cube[layer][i] & 0x01) 
				belt[5-i] |= (1 << layer);
		}
	}
	
	LED_CUBE_Clear();
}

void LED_CUBE_Animation_String_belt (char *string) {
	/* 2D 
	 * bits are Y, 0 is bottom, 7 is top
	 * 0 is the right end where the chars come in
	 * 20 visible lines, 5 are added to the "beginning"
	 * outside the cube so the chars can move in
	 */
	int i=0;
	char cube_belt[25];
	for (i=0; i<25; i++) {
		cube_belt[i] = 0;
	}

	string++;
	string++;
	
	while(*string){
		LED_CUBE_Animation_Set_char_to_belt(*string, cube_belt);
		for (i=0; i<6; i++){
			LED_CUBE_Animation_Show_belt(cube_belt);
			LED_CUBE_Animation_Move_belt_left(cube_belt);
		}
		string++;
	}
	
	/* move the rest out */
	for (i=0; i<18; i++){
		LED_CUBE_Animation_Show_belt(cube_belt);
		LED_CUBE_Animation_Move_belt_left(cube_belt);
	}
}

void LED_CUBE_Animation_Cube_2_auto (void) {
	char cube2_arr[4][4];
	int i=0, j=0;
	
	LED_CUBE_Clear();

	for (i=0; i<4; i++){
		for (j=0; j<4; j++){
			cube2_arr[i][j] = 0;
		}
	}

	cube2_arr[0][0] |= (1 << 0);
	cube2_arr[0][1] |= (1 << 0);
	cube2_arr[0][2] |= (1 << 0);
	cube2_arr[0][3] |= (1 << 0);

	cube2_arr[1][0] |= (1 << 0);
	cube2_arr[1][1] |= (1 << 0);
	cube2_arr[1][2] |= (1 << 0);
	cube2_arr[1][3] |= (1 << 0);

	cube2_arr[0][0] |= (1 << 1);
	cube2_arr[0][1] |= (1 << 1);
	cube2_arr[0][2] |= (1 << 1);
	cube2_arr[0][3] |= (1 << 1);
	
	cube2_arr[0][0] |= (1 << 2);
	cube2_arr[0][1] |= (1 << 2);
	cube2_arr[0][2] |= (1 << 2);
	cube2_arr[0][3] |= (1 << 2);

	cube2_arr[0][0] |= (1 << 3);
	cube2_arr[0][1] |= (1 << 3);
	cube2_arr[0][2] |= (1 << 3);
	cube2_arr[0][3] |= (1 << 3);
	
	cube2_arr[1][0] |= (1 << 3);
	cube2_arr[1][1] |= (1 << 3);
	cube2_arr[1][2] |= (1 << 3);
	cube2_arr[1][3] |= (1 << 3);
	
	LED_CUBE_Animations_Cube_2_auto_show(cube2_arr);
	
	for (i=0; i<2000; i++) {
		/* TODO: make this faster */
		uint8_t x = rand()%4;
		uint8_t y = rand()%4;
		uint8_t z = rand()%4;
		
		if (cube2_arr[y][x] & (1 << z)) {
			/* 
			 * we have a chosen an existing pixel
			 * now chose a direction and move it until
			 * it hits something
			 */
			/* stay in case until the
			 * transform functions returns != 0
			 */
			switch (rand()%6) {
				case 0:
					/* this checks avoid the pixel gets moved outside
					 * the cube as well as decrementing uint8_t = 0 
					 */
					while(y < 3) {
						if (LED_CUBE_Animations_Cube2_move_y_fwd(cube2_arr, y, x, z) == 0) {
							LED_CUBE_Animations_Cube_2_auto_show(cube2_arr);
							y++; 
						} else { break; }
					}
					break;
				case 1:
					while(y > 0) {
						if (LED_CUBE_Animations_Cube2_move_y_rev(cube2_arr, y, x, z) == 0) {
							LED_CUBE_Animations_Cube_2_auto_show(cube2_arr);
							y--; 
						} else { break; }
					}
					break;
				case 2:
					while(x < 3) {
						if (LED_CUBE_Animations_Cube2_move_x_fwd(cube2_arr, y, x, z) == 0) {
							LED_CUBE_Animations_Cube_2_auto_show(cube2_arr);
							x++; 
						} else { break; }
					}
					break;
				case 3:
					while(x > 0) {
						if (LED_CUBE_Animations_Cube2_move_x_rev(cube2_arr, y, x, z) == 0) {
							LED_CUBE_Animations_Cube_2_auto_show(cube2_arr);
							x--; 
						} else { break; }
					}
					break;
				case 4:
					while(z < 3) {
						if (LED_CUBE_Animations_Cube2_move_z_fwd(cube2_arr, y, x, z) == 0) {
							LED_CUBE_Animations_Cube_2_auto_show(cube2_arr);
							z++; 
						} else { break; }
					}
					break;
				case 5:
					while(z > 0) {
						if (LED_CUBE_Animations_Cube2_move_z_rev(cube2_arr, y, x, z) == 0) {
							LED_CUBE_Animations_Cube_2_auto_show(cube2_arr);
							z--; 
						} else { break; }
					}
					break;
				default:
					break;
			}
		}
	}
}

char LED_CUBE_Animations_Cube2_move_y_fwd (char cube2[4][4], uint8_t y, uint8_t x, uint8_t z) {
	if (!(cube2[y+1][x] & (1 << z))){
		cube2[y][x] &= ~(1 << z);
		cube2[y+1][x] |= (1 << z);
		return 0;
	}
	return 1;
}

char LED_CUBE_Animations_Cube2_move_y_rev (char cube2[4][4], uint8_t y, uint8_t x, uint8_t z) {
	if (!(cube2[y-1][x] & (1 << z))){
		cube2[y][x] &= ~(1 << z);
		cube2[y-1][x] |= (1 << z);
		return 0;
	}
	return 1;
}

char LED_CUBE_Animations_Cube2_move_x_fwd (char cube2[4][4], uint8_t y, uint8_t x, uint8_t z) {
	if (!(cube2[y][x+1] & (1 << z))){
		cube2[y][x] &= ~(1 << z);
		cube2[y][x+1] |= (1 << z);
		return 0;
	}
	return 1;
}

char LED_CUBE_Animations_Cube2_move_x_rev (char cube2[4][4], uint8_t y, uint8_t x, uint8_t z) {
	if (!(cube2[y][x-1] & (1 << z))){
		cube2[y][x] &= ~(1 << z);
		cube2[y][x-1] |= (1 << z);
		return 0;
	}
	return 1;
}

char LED_CUBE_Animations_Cube2_move_z_fwd (char cube2[4][4], uint8_t y, uint8_t x, uint8_t z) {
	if (!(cube2[y][x] & (1 << (z+1)))){
		cube2[y][x] &= ~(1 << z);
		cube2[y][x] |= (1 << (z+1));
		return 0;
	}
	return 1;
}

char LED_CUBE_Animations_Cube2_move_z_rev (char cube2[4][4], uint8_t y, uint8_t x, uint8_t z ) {
	if (!(cube2[y][x] & (1 << (z-1)))){
		cube2[y][x] &= ~(1 << z);
		cube2[y][x] |= (1 << (z-1));
		return 0;
	}
	return 1;
}

void LED_CUBE_Animations_Cube_2_auto_show (char cube2[4][4]) {
	int layer=0, x=0, z=0;
	
	for (layer=0; layer<4; layer++){
	/* avoid flickering, clear 2 layers only */
		LED_CUBE_Clear_layer(layer*2+1);
		LED_CUBE_Clear_layer(layer*2);
		
		for (x=0; x<4; x++){
			for (z=0; z<4; z++){
				if (cube2[layer][x] & ( 1 << z)) {
					cube[layer*2][x*2] |= (1 << (z*2));
					cube[layer*2][x*2] |= (1 << (z*2+1));
					cube[layer*2][x*2+1] |= (1 << (z*2));
					cube[layer*2][x*2+1] |= (1 << (z*2+1));
					cube[layer*2+1][x*2] |= (1 << (z*2));
					cube[layer*2+1][x*2] |= (1 << (z*2+1));
					cube[layer*2+1][x*2+1] |= (1 << (z*2));
					cube[layer*2+1][x*2+1] |= (1 << (z*2+1));
				}
			}
		}
	}
	
	Delay_ms(200);
}

void LED_CUBE_Animations_Cubes_2 (void) {
	int i=0;
	
	LED_CUBE_Clear();
	
	for (i=0; i<8; i++ ){
		cube[0][i] = 0xFF;
		cube[1][i] = 0xFF;
	}
	
	Delay_ms(60);
	
	for (i=0; i<6; i++) {
		move_y_fwd(2,2,3,3);
		move_y_fwd(2,6,3,7);
		move_y_fwd(6,2,7,3);
		move_y_fwd(6,6,7,7);
		Delay_ms(60);
	}
	
	for (i=0; i<4; i++) {
		move_y_fwd(0,0,1,1);
		move_y_fwd(0,4,1,5);
		move_y_fwd(4,0,5,1);
		move_y_fwd(4,4,5,5);
		Delay_ms(60);
	}
	
	for (i=0; i<2; i++) {
		move_y_fwd(2,0,3,1);
		move_y_fwd(6,0,7,1);
		move_y_fwd(2,4,3,5);
		move_y_fwd(6,4,7,5);
		Delay_ms(60);
	}

	for (i=0; i<4; i++) {
		move_y_rev(6,2,7,3);
		Delay_ms(60);
	}
	
	for (i=0; i<2; i++) {
		move_y_rev(4,0,5,1);
		Delay_ms(60);
	}
	
	for (i=0; i<6; i++) {
		move_z_fwd(2,4,3,5);
		Delay_ms(60);
	}
	
	for (i=0; i<2; i++) {
		move_y_rev(2,0,3,1);
		Delay_ms(60);
	}
	
	for (i=0; i<6; i++) {
		move_z_fwd(0,2,1,3);
		Delay_ms(60);
	}
	
	for (i=0; i<4; i++) {
		move_y_fwd(0,2,1,3);
		Delay_ms(60);
	}
	
	for (i=0; i<2; i++) {
		move_x_fwd(2,4,3,5);
		Delay_ms(60);
	}
}

void LED_CUBE_Animations_wipe (void) {
	int layer=0, i=0;
	
	LED_CUBE_Test_y();
	Delay_ms(100);
	
	for (layer=0; layer<7; layer++){	
		for (i=0; i<8; i++){
			cube[layer][i] = 0;
			cube[layer+1][i] = 0xFF;
		}
		Delay_ms(100);
	}
	
	for (layer = 0; layer<7; layer++){	
		move_y_rev(0,0,7,7);
		Delay_ms(100);
	}
}

void LED_CUBE_Animations_explosion (void) {
	char led_state = 0x18;
	int i=0, j=0, k=0;
	
	for (i=0; i<=4; i++){
		for (j=3; j<=(i+3); j++) {
			for (k=3; k<=(i+3); k++){
				cube[j][7-k] = led_state;
				cube[j][k] = led_state;
				cube[7-j][7-k] = led_state;
				cube[7-j][k] = led_state;
			}
		}
		Delay_ms(200);

		led_state |= (1 << (3-i)) | (1 << (4+i));
	}
	
	for (i=0; i<=4; i++){
		led_state &= ~((1 << (3-i)) | (1 << (4+i)));
		
		for (j = 3; j<=(i+3); j++) {
			for (k=3; k<=(i+3); k++){
				cube[j][7-k] = led_state;
				cube[j][k] = led_state;
				cube[7-j][7-k] = led_state;
				cube[7-j][k] = led_state;
			}
		}
		
		Delay_ms(200);
	}
}

void LED_CUBE_Animations_Outline_shrink (void) {
	int i=0;
	
	LED_CUBE_Clear();
	for (i=1; i<7; i++ ){
		cube[i][0] = 0x81;
		cube[i][7] = 0x81;
	}
	for (i=1; i<7; i++){
		cube[0][i] = 0x81;
		cube[7][i] = 0x81;
	}
	cube[0][0] = 0xFF;
	cube[7][0] = 0xFF;
	cube[0][7] = 0xFF;
	cube[7][7] = 0xFF;
	Delay_ms(200);

	for (i=2; i<6; i++ ){
		cube[i][1] = 0x42;
		cube[i][6] = 0x42;
	}
	for (i=2; i<6; i++){
		cube[1][i] = 0x42;
		cube[6][i] = 0x42;
	}
	cube[1][1] = 0x7E;
	cube[6][1] = 0x7E;
	cube[1][6] = 0x7E;
	cube[6][6] = 0x7E;
	Delay_ms(200);

	for (i=3; i<5; i++ ){
		cube[i][2] = 0x24;
		cube[i][5] = 0x24;
	}
	for (i=3; i<5; i++){
		cube[2][i] = 0x24;
		cube[5][i] = 0x24;
	}
	cube[2][2] = 0x3C;
	cube[5][2] = 0x3C;
	cube[2][5] = 0x3C;
	cube[5][5] = 0x3C;
	Delay_ms(200);

	cube[3][3] = 0x18;
	cube[4][3] = 0x18;
	cube[3][4] = 0x18;
	cube[4][4] = 0x18;
	Delay_ms(200);
	
	LED_CUBE_Clear();
	
	Delay_ms(200);
}

void LED_CUBE_Animations_Cubes_4 (void) {
	int fourtimes=0, layer=0;
	
	LED_CUBE_Clear();
	
	for (layer=0; layer<=3; layer++){
		cube[layer][0] = 0x0F;
		cube[layer][1] = 0x0F;
		cube[layer][2] = 0x0F;
		cube[layer][3] = 0x0F;
	}
	for (layer=4; layer<=7; layer++){
		cube[layer][4] = 0xFF;
		cube[layer][5] = 0xFF;
		cube[layer][6] = 0xFF;
		cube[layer][7] = 0xFF;
	}
	Delay_ms(60);
	for (fourtimes=0; fourtimes<=3; fourtimes++){
		move_y_rev(4,0,7,3);
		Delay_ms(60);
	}
	for (fourtimes=0; fourtimes<=3; fourtimes++){
		move_z_fwd(0,0,3,3);
		Delay_ms(60);
	}
	for (fourtimes=0; fourtimes<=3; fourtimes++){
		move_y_fwd(0,4,3,7);	
		Delay_ms(60);
	}
	for (fourtimes=0; fourtimes<=3; fourtimes++){
		move_y_rev(4,4,7,7);
		Delay_ms(60);
	}
	for (fourtimes=0; fourtimes<=3; fourtimes++){
		move_x_rev(0,0,3,3);
		Delay_ms(60);
	}
	for (fourtimes=0; fourtimes<=3; fourtimes++){
		move_z_rev(4,0,7,3);
		Delay_ms(60);
	}
	for (fourtimes=0; fourtimes<=3; fourtimes++){
		move_z_fwd(4,0,7,3);
		Delay_ms(60);
	}
	for (fourtimes=0; fourtimes<=3; fourtimes++){
		move_y_fwd(4,4,7,7);
		Delay_ms(60);
	}
	for (fourtimes=0; fourtimes<=3; fourtimes++){
		move_x_fwd(0,0,3,3);
		Delay_ms(60);
	}
	for (fourtimes=0; fourtimes<=3; fourtimes++){
		move_y_fwd(4,0,7,3);
		Delay_ms(60);
	}
	for (fourtimes=0; fourtimes<=3; fourtimes++){
		move_y_rev(0,4,3,7);
		Delay_ms(60);
	}
	for (fourtimes=0; fourtimes<=3; fourtimes++){
		move_z_rev(0,0,3,3);
		Delay_ms(60);
	}
}

void LED_CUBE_Animations_Cube_stars (void) {
	int i=0, j=0, loops=0;
	
	for (j=1; j<30; j++){
		for (loops = 0; loops < 18; loops++){
			LED_CUBE_Clear();
			
			for (i=0; i<j; i++){
				char randx = (char)rand()%8;
				char randy = (char)rand()%8;
				char randz = (char)rand()%8;
				cube[randy][randx] = (1 << randz);
			}

			Delay_ms(80);
		}
	}
}

void LED_CUBE_Animations_Cube_Outline (void) {
	int i=0;
	
	LED_CUBE_Clear();
	
	Delay_ms(60);
	for (i=0; i<8; i++) {
		cube[0][0] |= (1 << i);
		cube[i][0] |= 1;
		cube[0][i] |= 1;
		Delay_ms(60);
	}
	for (i=1; i<8; i++) {
		cube[7][0] |= (1 << i);
		cube[7][i] |= 1;
		cube[i][0] |= 128;
		cube[0][i] |= 128;
		cube[0][7] |= (1 << i);
		cube[i][7] |= 1;
		Delay_ms(60);
	}
	for (i=1; i<8; i++) {
		cube[7][i] |= 128;
		cube[7][7] |= (1 << i);
		cube[i][7] |= 128;
		Delay_ms(60);
	}
	Delay_ms(30);
	/* shrink */
	LED_CUBE_Clear();
	cube[1][1] = 0x7E;
	cube[1][6] = 0x7E;
	cube[6][1] = 0x7E;
	cube[6][6] = 0x7E;
	for (i=2; i<6; i++) {
		cube[1][i] = 0x42;
		cube[6][i] = 0x42;
		cube[i][1] = 0x42;
		cube[i][6] = 0x42;
	}
	Delay_ms(30);
	rotate_90_auto( 8 );
}

void LED_CUBE_Animations_Cube_waves (void) {
	int i=0;
	
	LED_CUBE_Clear();
	
	for (i=0; i<10; i++){
		move_x_rev(0,0,7,7);
		cube[3][7] |= WAVES_DEPTH;
		Delay_ms(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[2][7] |= WAVES_DEPTH;
		Delay_ms(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[1][7] |= WAVES_DEPTH;
		Delay_ms(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[0][7] |= WAVES_DEPTH;
		Delay_ms(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[0][7] |= WAVES_DEPTH;
		Delay_ms(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[1][7] |= WAVES_DEPTH;
		Delay_ms(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[2][7] |= WAVES_DEPTH;
		Delay_ms(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[3][7] |= WAVES_DEPTH;
		Delay_ms(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[4][7] |= WAVES_DEPTH;
		Delay_ms(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[5][7] |= WAVES_DEPTH;
		Delay_ms(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[6][7] |= WAVES_DEPTH;
		Delay_ms(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[7][7] |= WAVES_DEPTH;
		Delay_ms(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[7][7] |= WAVES_DEPTH;
		Delay_ms(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[6][7] |= WAVES_DEPTH;
		Delay_ms(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[5][7] |= WAVES_DEPTH;
		Delay_ms(WAVES_DELAY);
		move_x_rev(0,0,7,7);
		cube[4][7] |= WAVES_DEPTH;
		Delay_ms(WAVES_DELAY);
	}
}

void LED_CUBE_Animations_Cube_sonic (void) {
	int i=0, layer=0, deg=0;
	char mode, sonic_layers;
	
	for (i=0; i<10; i++){
		LED_CUBE_Clear();
		Delay_ms(60);
		mode = rand()%5;
		sonic_layers = (rand()%8)+1;
		if (mode <= 3){
			LED_CUBE_Clear();
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][0] = 0x80;
			}
			for (deg = 0; deg < mode; deg++){
				rotate_90_deg();
			}
			Delay_ms(SONIC_DELAY);
			
			LED_CUBE_Clear();	
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][0] = 0x40;
				cube[layer][1] = 0x80;
			}
			for (deg = 0; deg < mode; deg++){
				rotate_90_deg();
			}
			Delay_ms(SONIC_DELAY);
			
			LED_CUBE_Clear();	
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][0] = 0x20;
				cube[layer][1] = 0x20;
				cube[layer][2] = 0xC0;
			}
			for (deg = 0; deg < mode; deg++){
				rotate_90_deg();
			}
			Delay_ms(SONIC_DELAY);
			
			LED_CUBE_Clear();	
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][0] = 0x10;
				cube[layer][1] = 0x10;
				cube[layer][2] = 0x20;
				cube[layer][3] = 0xC0;
			}
			for (deg = 0; deg < mode; deg++){
				rotate_90_deg();
			}
			Delay_ms(SONIC_DELAY);
			
			LED_CUBE_Clear();	
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][0] = 0x8;
				cube[layer][1] = 0x8;
				cube[layer][2] = 0x10;
				cube[layer][3] = 0x30;
				cube[layer][4] = 0xC0;
			}
			for (deg = 0; deg < mode; deg++){
				rotate_90_deg();
			}
			Delay_ms(SONIC_DELAY);
			
			LED_CUBE_Clear();	
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][0] = 0x04;
				cube[layer][1] = 0x04;
				cube[layer][2] = 0x04;
				cube[layer][3] = 0x08;
				cube[layer][4] = 0x10;
				cube[layer][5] = 0xE0;
			}
			for (deg = 0; deg < mode; deg++){
				rotate_90_deg();
			}
			Delay_ms(SONIC_DELAY);
			
			LED_CUBE_Clear();	
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][0] = 0x02;
				cube[layer][1] = 0x02;
				cube[layer][2] = 0x02;
				cube[layer][3] = 0x04;
				cube[layer][4] = 0x08;
				cube[layer][5] = 0x10;
				cube[layer][6] = 0xE0;
			}
			for (deg = 0; deg < mode; deg++){
				rotate_90_deg();
			}
			Delay_ms(SONIC_DELAY);

			LED_CUBE_Clear();	
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][0] = 0x01;
				cube[layer][1] = 0x01;
				cube[layer][2] = 0x01;
				cube[layer][3] = 0x02;
				cube[layer][4] = 0x02;
				cube[layer][5] = 0x04;
				cube[layer][6] = 0x18;
				cube[layer][7] = 0xE0;
			}
			for (deg = 0; deg < mode; deg++){
				rotate_90_deg();
			}
			Delay_ms(SONIC_DELAY);

			LED_CUBE_Clear();	
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][4] = 0x01;
				cube[layer][5] = 0x02;
				cube[layer][6] = 0x04;
				cube[layer][7] = 0x08;
			}
			for (deg = 0; deg < mode; deg++){
				rotate_90_deg();
			}
			Delay_ms(SONIC_DELAY);

			LED_CUBE_Clear();	
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][6] = 0x01;
				cube[layer][7] = 0x02;
			}
			for (deg = 0; deg < mode; deg++){
				rotate_90_deg();
			}
			Delay_ms(SONIC_DELAY);

			LED_CUBE_Clear();	
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][7] = 0x01;
			}
			for (deg = 0; deg < mode; deg++){
				rotate_90_deg();
			}
			Delay_ms(SONIC_DELAY);
		} else {
			/* center wave */
			LED_CUBE_Clear();
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][3] = 0x18;
				cube[layer][4] = 0x18;
			}
			Delay_ms(SONIC_DELAY);
			LED_CUBE_Clear();
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][2] = 0x18;
				cube[layer][3] = 0x24;
				cube[layer][4] = 0x24;
				cube[layer][5] = 0x18;
			}
			Delay_ms(SONIC_DELAY);
			LED_CUBE_Clear();
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][1] = 0x18;
				cube[layer][2] = 0x24;
				cube[layer][3] = 0x42;
				cube[layer][4] = 0x42;
				cube[layer][5] = 0x24;
				cube[layer][6] = 0x18;
			}
			Delay_ms(SONIC_DELAY);
			LED_CUBE_Clear();
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][0] = 0x18;
				cube[layer][1] = 0x66;
				cube[layer][2] = 0x42;
				cube[layer][3] = 0x81;
				cube[layer][4] = 0x81;
				cube[layer][5] = 0x42;
				cube[layer][6] = 0x66;
				cube[layer][7] = 0x18;
			}
			Delay_ms(SONIC_DELAY);
			LED_CUBE_Clear();
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][0] = 0x42;
				cube[layer][1] = 0x81;
				cube[layer][6] = 0x81;
				cube[layer][7] = 0x42;
			}
			Delay_ms(SONIC_DELAY);
			LED_CUBE_Clear();
			for (layer = 0; layer < sonic_layers; layer++){
				cube[layer][0] = 0x81;
				cube[layer][7] = 0x81;
			}
			Delay_ms(SONIC_DELAY);
		}
	}
}

void LED_CUBE_Animtions_Outline_shrink (void) {
	int i=0;
	
	LED_CUBE_Clear();
	
	for (i = 1; i < 7; i++ ){
		cube[i][0] = 0x81;
		cube[i][7] = 0x81;
	}
	for (i = 1; i < 7; i++){
		cube[0][i] = 0x81;
		cube[7][i] = 0x81;
	}
	cube[0][0] = 0xFF;
	cube[7][0] = 0xFF;
	cube[0][7] = 0xFF;
	cube[7][7] = 0xFF;
	Delay_ms(OUT_SHRINK_DELAY);

	for (i = 2; i < 6; i++ ){
		cube[i][1] = 0x42;
		cube[i][6] = 0x42;
	}
	for (i = 2; i < 6; i++){
		cube[1][i] = 0x42;
		cube[6][i] = 0x42;
	}
	cube[1][1] = 0x7E;
	cube[6][1] = 0x7E;
	cube[1][6] = 0x7E;
	cube[6][6] = 0x7E;
	Delay_ms(OUT_SHRINK_DELAY);

	for (i = 3; i < 5; i++ ){
		cube[i][2] = 0x24;
		cube[i][5] = 0x24;
	}
	for (i = 3; i < 5; i++){
		cube[2][i] = 0x24;
		cube[5][i] = 0x24;
	}
	cube[2][2] = 0x3C;
	cube[5][2] = 0x3C;
	cube[2][5] = 0x3C;
	cube[5][5] = 0x3C;
	Delay_ms(OUT_SHRINK_DELAY);

	cube[3][3] = 0x18;
	cube[4][3] = 0x18;
	cube[3][4] = 0x18;
	cube[4][4] = 0x18;	
	Delay_ms(10*OUT_SHRINK_DELAY);
}

void LED_CUBE_Animations_Show_belt (char *belt) {
	int i=0, j=0;
	
	LED_CUBE_Clear();
	
	/* right side */
	for (i = 5; i <= 11; i++){
		for (j = 0; j < 8; j++){
			if (belt[i] & (1 << j))
				cube[j][7] |= (1 << (12-i));
		}
	}
	/* front side */
	for (i = 12; i <= 17; i++){
		for (j = 0; j < 8; j++){
			if (belt[i] & (1 << j))
				cube[j][18-i] |= (1 << 0);
		}
	}
	/* left side */
	for (i = 18; i <= 24; i++){
		for (j = 0; j < 8; j++){
			if (belt[i] & (1 << j))
				cube[j][0] |= (1 << (i-17));
		}
	}
	Delay_ms(SHOW_BELT_DELAY);
}

void invaders_move_right(unsigned int layer, int *position) {
	int check = 0xC0;
	int i=0;
	
	for (i=0; i<3; i++) {
		/* alway check for 2 bits to make sure its no bullet */
		if ( cube[layer][(*position)] & check && cube[layer-1][(*position)] & check ){
			cube[layer][(*position)] &= ~check;
			cube[layer-1][(*position)] &= ~check;
			cube[layer][(*position)+2] |= check;
			cube[layer-1][(*position)+2] |= check;
		}
		if ( cube[layer][(*position)+3] & check && cube[layer-1][(*position)+3] & check){
			cube[layer][(*position)+3] &= ~check;
			cube[layer-1][(*position)+3] &= ~check;
			cube[layer][(*position)+5] |= check;
			cube[layer-1][(*position)+5] |= check;
		}
		check = (check >> 3);
	}
	(*position)++;
}

void invaders_move_left (unsigned int  layer, int *position) {
	uint8_t check = 0xC0;
	int i=0;
	
	for (i = 0; i < 3; i++){
		if ( cube[layer][(*position)+1] & check && cube[layer-1][(*position)+1] & check){
			cube[layer][(*position)+1] &= ~check;
			cube[layer-1][(*position)+1] &= ~check;
			cube[layer][(*position)-1] |= check;
			cube[layer-1][(*position)-1] |= check;
		}
		if ( cube[layer][(*position)+4] & check && cube[layer-1][(*position)+4] & check){
			cube[layer][(*position)+4] &= ~check;
			cube[layer-1][(*position)+4] &= ~check;
			cube[layer][(*position)+2] |= check;
			cube[layer-1][(*position)+2] |= check;
		}
		check = (check >> 3);
	}
	(*position)--;
}

void invaders_move_down (unsigned int *layer, int position) {
	int check = 0xC0;
	int i=0;
	
	for (i=0; i<3; i++){
		if ( cube[(*layer)][position] & check ){
			cube[(*layer) ][position] &= ~check;
			cube[(*layer)][position+1] &= ~check;
			cube[(*layer-2)][position] |= check;
			cube[(*layer-2)][position+1] |= check;
		}
		if ( cube[(*layer)][position+3] & check ){
			cube[(*layer)][position+3] &= ~check;
			cube[(*layer)][position+4] &= ~check;
			cube[(*layer-2)][position+3] |= check;
			cube[(*layer-2)][position+4] |= check;
		}
		check = (check >> 3);
	}
	(*layer)--;
}

#define MONSTER_RIGHT invaders_move_right((*m_layer), m_pos)
#define MONSTER_LEFT invaders_move_left((*m_layer), m_pos)
#define MONSTER_DOWN  invaders_move_down(m_layer, (*m_pos))
#define INV_DELAY invader_show_loop(&shot_layer, &shot_pos, &monster_layer, &monster_pos)
#define DEF_RIGHT move_x_fwd( 0, 0, 7, 1); defender_pos += 0x10;
#define DEF_LEFT move_x_rev( 0, 0, 7, 1); defender_pos -= 0x10;
#define DEF_BACK move_z_fwd( 0, 0, 1, 7); defender_pos += 0x01;
#define DEF_FWD move_z_rev( 0, 0, 1, 7); defender_pos -= 0x01;
#define DEF_FIRE def_fire( &shot_layer, &shot_pos, defender_pos )

static void def_fire (unsigned int *layer, unsigned int *position, unsigned int defender_position) {
	(*position) = defender_position; 
	(*layer) = 2; 
	cube[(*layer)][(((*position) & 0xF0) >> 4)] |= (1 << ((*position) & 0x0F));
	Delay_ms(INVADERS_DELAY); /*otherwise first pixel could not be seen */
}

/* usual delay combined with moving the bullet one up */
static void invader_show_loop (unsigned int *layer, unsigned int *position, unsigned int *m_layer, int *m_pos) {
	static int prescaler = 1;
	static int direction = 0;
	int current_layer;
	
	if ( (*layer) < 7){
		(*layer)++;
		/* check if monster is hit */ 
		if (cube[(*layer)][(((*position) & 0xF0) >> 4)] & ( 1 << ((*position) & 0x0F)) ) {
		/* flash all pixels around the bullet */
			current_layer = (*layer)-1;
			while ( (current_layer <= ((*layer)+1)) && (current_layer < 8)){
				cube[current_layer][(((*position) & 0xF0) >> 4)+1] |= (7 << (((*position) & 0x0F)-1));
				cube[current_layer][(((*position) & 0xF0) >> 4)] |= (7 << (((*position) & 0x0F)-1));
				cube[current_layer][(((*position) & 0xF0) >> 4)-1] |= (7 << (((*position) & 0x0F)-1));
				current_layer++;
			}
			Delay_ms(INVADERS_DELAY);
			
			current_layer = (*layer)-1;
			while ( (current_layer <= ((*layer)+1)) && (current_layer < 8)){
				cube[current_layer][(((*position) & 0xF0) >> 4)+1] &= ~(7 << (((*position) & 0x0F)-1));
				cube[current_layer][(((*position) & 0xF0) >> 4)] &= ~(7 << (((*position) & 0x0F)-1));
				cube[current_layer][(((*position) & 0xF0) >> 4)-1] &= ~(7 << (((*position) & 0x0F)-1));
				current_layer++;
			}
		} else {
			/* no monster, move up, layer already incremented */
			cube[(*layer)-1][(((*position) & 0xF0) >> 4)] &= ~(1 << ((*position) & 0x0F)); 
			/* always inside the cube, checked by layer < 7*/
			cube[(*layer)][(((*position) & 0xF0) >> 4)] |= (1 << ((*position) & 0x0F)); 
			Delay_ms(INVADERS_DELAY);
		}
	} else {
		/* delete shot, increment layer to avoid counting up to inf */
		if ( (*layer) < 8) { 
			cube[(*layer)++][(((*position) & 0xF0) >> 4)] &= ~(1 << ((*position) & 0x0F)); 
		}
		Delay_ms(INVADERS_DELAY);
	}

	if ((prescaler % 6) == 0){
		if (((*m_pos) < 3) && (direction == 0)) {
			MONSTER_RIGHT;
		} else if (((*m_pos) >= 1) && (direction == 1)){
			MONSTER_LEFT;
		}

		if ((*m_pos) == 3) {
			direction = 1;
		} else if ((*m_pos) == 0) {
			direction = 0;
		}
	}
	if ((prescaler % 128) == 0){
		if ((*m_layer) > 2)
			MONSTER_DOWN;
	}
	if (prescaler < 255)
		prescaler++;
	else 
		prescaler = 0;
}

void LED_CUBE_Animations_Cube_invaders (void) {
	unsigned int monster_layer = 7; /* vert.  monster layer,  */
	int monster_pos = 1; /* hor. monster layer position */
	unsigned int defender_pos = 0x43; /* high nibble: x, low nibble: y */
	/* limit to only one shot at once, only defender is able to fire */
	unsigned int shot_pos = 0; /* save last shot position */
	unsigned int shot_layer = 9; /* current shot layer */
	int i=0;
	
	LED_CUBE_Clear();
	
	cube[0][3] |= 0x1C;
	cube[0][4] |= 0x1C;
	cube[0][5] |= 0x1C;
	cube[1][4] |= 0x08;
	
	cube[6][1] |= 0xDB;
	cube[7][1] |= 0xDB;
	cube[6][2] |= 0xDB;
	cube[7][2] |= 0xDB;
	
	cube[6][4] |= 0xDB;
	cube[7][4] |= 0xDB;
	cube[6][5] |= 0xDB;
	cube[7][5] |= 0xDB;

	while ( monster_layer > 2 ) {
		for (i = 0; i < 20; i++){
			switch (rand()%4){
				case 0:
					if ((defender_pos & 0xF0) < 0x60) { DEF_RIGHT; }
					break;
				case 1:
					if ((defender_pos & 0xF0) > 0x10) { DEF_LEFT; }
					break;
				case 2: 
					if ((defender_pos & 0x0F) > 0x01) { DEF_FWD; }
					break;
				case 3:
					if ((defender_pos & 0x0F) < 0x06) { DEF_BACK; }
					break;
				default:
					break;
			}
			INV_DELAY;
			INV_DELAY;
		}
		DEF_FIRE;
	}
}

void LED_CUBE_Animations_Cube_belt_wipe (void) {
	int i=0, layer;
	for (layer = 8; layer != 0; layer--){
		cube[layer-1][0] |= 0xFF;
		cube[layer-1][7] |= 0xFF;
		for (i = 1; i < 7; i++){ cube[layer-1][i] |= 0x81; }
		Delay_ms(BELT_WIPE_DELAY);
	}
	for (layer = 8; layer != 0; layer--){
		for (i = 0; i < 8; i++){ cube[layer-1][i] = 0x00; }
		Delay_ms(BELT_WIPE_DELAY);
	}
}

void LED_CUBE_Animations_Cube_block_wipe (void) {
	int i=0, layer=0;
	
	for (i = 0; i < 8; i++){
		move_x_fwd(0,0,7,7);
		for(layer = 0; layer < 8; layer++){
			cube[layer][0] |= 0xFF;
		}
		Delay_ms(BLOCK_WIPE_DELAY);
	}
	Delay_ms(BLOCK_WIPE_DELAY);
	for (i = 8; i != 0; i--){
		for(layer = 0; layer < 8; layer++){
			cube[layer][i-1] = 0x00;
		}
		Delay_ms(BLOCK_WIPE_DELAY);
	}
		
}

void LED_CUBE_Animations_Cube_stripes (void) {
	int i=0, j=0;
	
	LED_CUBE_Clear();
	
	for (i = 0; i < 8; i++) {
		cube[0][0] |= ( 1 << i );
		cube[1][7] |= ( 1 << (7-i) );
		cube[2][0] |= ( 1 << i );
		cube[3][7] |= ( 1 << (7-i) );
		cube[4][0] |= ( 1 << i );
		cube[5][7] |= ( 1 << (7-i) );
		cube[6][0] |= ( 1 << i );
		cube[7][7] |= ( 1 << (7-i) );
		Delay_ms(STRIPES_DELAY);
	}
	for (j = 1; j < 8; j++) {
		LED_CUBE_Clear();
		for (i = 0; i < 8; i++) {
			cube[0][j] |= ( 1 << i );
			cube[1][7-j] |= ( 1 << i );
			cube[2][j] |= ( 1 << i );
			cube[3][7-j] |= ( 1 << i );
			cube[4][j] |= ( 1 << i );
			cube[5][7-j] |= ( 1 << i );
			cube[6][j] |= ( 1 << i );
			cube[7][7-j] |= ( 1 << i );
		}
		Delay_ms(STRIPES_DELAY);
	}
}

/**************************************************************************
                            End Of File
***************************************************************************/
