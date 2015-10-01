//
//  LPAnimationsLetters.m
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 13/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPAnimationsLetters.h"


@implementation LPAnimationsLetters

+ (uint8_t *)getCubeEffectForLetter:(unichar)letter position:(int)position
{
    uint8_t cube[8][8];
    
    for (int a=0; a<8; a++) {
        for (int b=0; b<8; b++) {
            cube[a][b] = 0x00;
        }
    }
    
    uint8_t *buffer = malloc(64);
    memset(buffer, 0x00, 64);

    position = (1 << position);
    
    switch (letter) {
        case '0':
            cube[0][2] |= position;
            cube[0][3] |= position;
            cube[0][4] |= position;
            cube[1][1] |= position;
            cube[1][5] |= position;
            cube[2][1] |= position;
            cube[2][2] |= position;
            cube[2][5] |= position;
            cube[3][1] |= position;
            cube[3][3] |= position;
            cube[3][5] |= position;
            cube[4][1] |= position;
            cube[4][4] |= position;
            cube[4][5] |= position;
            cube[5][1] |= position;
            cube[5][5] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            break;
        case '1':
            cube[0][2] |= position;
            cube[0][3] |= position;
            cube[0][4] |= position;
            cube[1][3] |= position;
            cube[2][3] |= position;
            cube[3][3] |= position;
            cube[4][3] |= position;
            cube[5][2] |= position;
            cube[5][3] |= position;
            cube[6][3] |= position;
            break;
        case '2':
            cube[0][1] |= position;
            cube[0][2] |= position;
            cube[0][3] |= position;
            cube[0][4] |= position;
            cube[0][5] |= position;
            cube[1][2] |= position;
            cube[2][3] |= position;
            cube[3][4] |= position;
            cube[4][5] |= position;
            cube[5][1] |= position;
            cube[5][5] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            break;
        case '3':
            cube[0][2] |= position;
            cube[0][3] |= position;
            cube[0][4] |= position;
            cube[1][1] |= position;
            cube[1][5] |= position;
            cube[2][5] |= position;
            cube[3][4] |= position;
            cube[4][3] |= position;
            cube[5][4] |= position;
            cube[6][1] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            cube[6][5] |= position;
            break;
        case '4':
            cube[0][4] |= position;
            cube[1][4] |= position;
            cube[2][1] |= position;
            cube[2][2] |= position;
            cube[2][3] |= position;
            cube[2][4] |= position;
            cube[2][5] |= position;
            cube[3][1] |= position;
            cube[3][4] |= position;
            cube[4][2] |= position;
            cube[4][4] |= position;
            cube[5][3] |= position;
            cube[5][4] |= position;
            cube[6][4] |= position;
            break;
        case '5':
            cube[0][2] |= position;
            cube[0][3] |= position;
            cube[0][4] |= position;
            cube[1][1] |= position;
            cube[1][5] |= position;
            cube[2][5] |= position;
            cube[3][5] |= position;
            cube[4][1] |= position;
            cube[4][2] |= position;
            cube[4][3] |= position;
            cube[4][4] |= position;
            cube[5][1] |= position;
            cube[6][1] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            cube[6][5] |= position;
            break;
        case '6':
            cube[0][2] |= position;
            cube[0][3] |= position;
            cube[0][4] |= position;
            cube[1][1] |= position;
            cube[1][5] |= position;
            cube[2][1] |= position;
            cube[2][5] |= position;
            cube[3][1] |= position;
            cube[3][2] |= position;
            cube[3][3] |= position;
            cube[3][4] |= position;
            cube[4][1] |= position;
            cube[5][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            break;
        case '7':
            cube[0][2] |= position;
            cube[1][2] |= position;
            cube[2][2] |= position;
            cube[3][3] |= position;
            cube[4][4] |= position;
            cube[5][5] |= position;
            cube[6][1] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            cube[6][5] |= position;
            break;
        case '8':
            cube[0][2] |= position;
            cube[0][3] |= position;
            cube[0][4] |= position;
            cube[1][1] |= position;
            cube[1][5] |= position;
            cube[2][1] |= position;
            cube[2][5] |= position;
            cube[3][2] |= position;
            cube[3][3] |= position;
            cube[3][4] |= position;
            cube[4][1] |= position;
            cube[4][5] |= position;
            cube[5][1] |= position;
            cube[5][5] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            break;
        case '9':
            cube[0][2] |= position;
            cube[0][3] |= position;
            cube[1][4] |= position;
            cube[2][5] |= position;
            cube[3][2] |= position;
            cube[3][3] |= position;
            cube[3][4] |= position;
            cube[3][5] |= position;
            cube[4][1] |= position;
            cube[4][5] |= position;
            cube[5][1] |= position;
            cube[5][5] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            break;
        case '>':
            cube[1][2] |= position;
            cube[2][3] |= position;
            cube[3][4] |= position;
            cube[4][4] |= position;
            cube[5][3] |= position;
            cube[6][2] |= position;
            break;
        case '<':
            cube[1][5] |= position;
            cube[2][4] |= position;
            cube[3][3] |= position;
            cube[4][3] |= position;
            cube[5][4] |= position;
            cube[6][5] |= position;
            break;
        case '!':
            cube[0][3] |= position;
            cube[3][3] |= position;
            cube[4][3] |= position;
            cube[5][2] |= position;
            cube[5][3] |= position;
            cube[5][4] |= position;
            cube[6][1] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            cube[6][5] |= position;
            break;
        case ':':
            cube[1][2] |= position;
            cube[1][3] |= position;
            cube[2][2] |= position;
            cube[2][3] |= position;
            cube[4][2] |= position;
            cube[4][3] |= position;
            cube[5][2] |= position;
            cube[5][3] |= position;
            break;
        case '.':
            cube[1][2] |= position;
            cube[1][3] |= position;
            cube[2][2] |= position;
            cube[2][3] |= position;
            break;
        case '?':
            cube[0][3] |= position;
            cube[2][3] |= position;
            cube[3][4] |= position;
            cube[4][5] |= position;
            cube[5][1] |= position;
            cube[5][5] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            break;
        case '&':
            cube[0][2] |= position;
            cube[0][3] |= position;
            cube[0][5] |= position;
            cube[1][1] |= position;
            cube[1][4] |= position;
            cube[2][1] |= position;
            cube[2][3] |= position;
            cube[2][5] |= position;
            cube[3][2] |= position;
            cube[4][1] |= position;
            cube[4][3] |= position;
            cube[5][1] |= position;
            cube[5][4] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            break;
        case 'a':
            cube[0][1] |= position;
            cube[0][5] |= position;
            cube[1][1] |= position;
            cube[1][5] |= position;
            cube[2][1] |= position;
            cube[2][2] |= position;
            cube[2][3] |= position;
            cube[2][4] |= position;
            cube[2][5] |= position;
            cube[3][1] |= position;
            cube[3][5] |= position;
            cube[4][1] |= position;
            cube[4][5] |= position;
            cube[5][1] |= position;
            cube[5][5] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            break;
        case 'b':
            cube[0][1] |= position;
            cube[0][2] |= position;
            cube[0][3] |= position;
            cube[0][4] |= position;
            cube[1][1] |= position;
            cube[1][5] |= position;
            cube[2][1] |= position;
            cube[2][5] |= position;
            cube[3][1] |= position;
            cube[3][2] |= position;
            cube[3][3] |= position;
            cube[3][4] |= position;
            cube[4][1] |= position;
            cube[4][5] |= position;
            cube[5][1] |= position;
            cube[5][5] |= position;
            cube[6][1] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            break;
        case 'c':
            cube[0][2] |= position;
            cube[0][3] |= position;
            cube[0][4] |= position;
            cube[1][5] |= position;
            cube[1][1] |= position;
            cube[2][1] |= position;
            cube[3][1] |= position;
            cube[4][1] |= position;
            cube[5][1] |= position;
            cube[5][5] |= position;
            cube[5][1] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            break;
        case 'd':
            cube[0][1] |= position;
            cube[0][2] |= position;
            cube[0][3] |= position;
            cube[1][1] |= position;
            cube[1][4] |= position;
            cube[2][1] |= position;
            cube[2][5] |= position;
            cube[3][1] |= position;
            cube[3][5] |= position;
            cube[4][1] |= position;
            cube[4][5] |= position;
            cube[5][1] |= position;
            cube[5][4] |= position;
            cube[6][1] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            break;
        case 'e':
            cube[0][1] |= position;
            cube[0][2] |= position;
            cube[0][3] |= position;
            cube[0][4] |= position;
            cube[0][5] |= position;
            cube[1][1] |= position;
            cube[2][1] |= position;
            cube[3][1] |= position;
            cube[3][2] |= position;
            cube[3][3] |= position;
            cube[3][4] |= position;
            cube[4][1] |= position;
            cube[5][1] |= position;
            cube[6][1] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            cube[6][5] |= position;
            break;
        case 'f':
            cube[0][1] |= position;
            cube[1][1] |= position;
            cube[2][1] |= position;
            cube[3][1] |= position;
            cube[3][2] |= position;
            cube[3][3] |= position;
            cube[3][4] |= position;
            cube[4][1] |= position;
            cube[5][1] |= position;
            cube[6][1] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            cube[6][5] |= position;
            break;
        case 'g':
            cube[0][2] |= position;
            cube[0][3] |= position;
            cube[0][4] |= position;
            cube[0][5] |= position;
            cube[1][1] |= position;
            cube[1][5] |= position;
            cube[2][1] |= position;
            cube[2][5] |= position;
            cube[3][1] |= position;
            cube[3][3] |= position;
            cube[3][4] |= position;
            cube[3][5] |= position;
            cube[4][1] |= position;
            cube[5][1] |= position;
            cube[5][5] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            break;
        case 'h':
            cube[0][1] |= position;
            cube[0][5] |= position;
            cube[1][1] |= position;
            cube[1][5] |= position;
            cube[2][1] |= position;
            cube[2][5] |= position;
            cube[3][1] |= position;
            cube[3][2] |= position;
            cube[3][3] |= position;
            cube[3][4] |= position;
            cube[3][5] |= position;
            cube[4][1] |= position;
            cube[4][5] |= position;
            cube[5][1] |= position;
            cube[5][5] |= position;
            cube[6][1] |= position;
            cube[6][5] |= position;
            break;
        case 'i':
            cube[0][2] |= position;
            cube[0][3] |= position;
            cube[0][4] |= position;
            cube[1][3] |= position;
            cube[2][3] |= position;
            cube[3][3] |= position;
            cube[4][3] |= position;
            cube[5][3] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            break;
        case 'j':
            cube[0][2] |= position;
            cube[0][3] |= position;
            cube[1][1] |= position;
            cube[1][4] |= position;
            cube[2][4] |= position;
            cube[3][4] |= position;
            cube[4][4] |= position;
            cube[5][4] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            cube[6][5] |= position;
            break;
        case 'k':
            cube[0][1] |= position;
            cube[0][5] |= position;
            cube[1][1] |= position;
            cube[1][4] |= position;
            cube[2][1] |= position;
            cube[2][3] |= position;
            cube[3][1] |= position;
            cube[3][2] |= position;
            cube[4][1] |= position;
            cube[4][3] |= position;
            cube[5][1] |= position;
            cube[5][4] |= position;
            cube[6][1] |= position;
            cube[6][5] |= position;
            break;
        case 'l':
            cube[0][1] |= position;
            cube[0][2] |= position;
            cube[0][3] |= position;
            cube[0][4] |= position;
            cube[0][5] |= position;
            cube[1][1] |= position;
            cube[2][1] |= position;
            cube[3][1] |= position;
            cube[4][1] |= position;
            cube[5][1] |= position;
            cube[6][1] |= position;
            break;
        case 'm':
            cube[0][1] |= position;
            cube[0][5] |= position;
            cube[1][1] |= position;
            cube[1][5] |= position;
            cube[2][1] |= position;
            cube[2][5] |= position;
            cube[3][1] |= position;
            cube[3][3] |= position;
            cube[3][5] |= position;
            cube[4][1] |= position;
            cube[4][3] |= position;
            cube[4][5] |= position;
            cube[5][1] |= position;
            cube[5][2] |= position;
            cube[5][4] |= position;
            cube[5][5] |= position;
            cube[6][1] |= position;
            cube[6][5] |= position;
            break;
        case 'n':
            cube[0][1] |= position;
            cube[0][5] |= position;
            cube[1][1] |= position;
            cube[1][5] |= position;
            cube[2][1] |= position;
            cube[2][4] |= position;
            cube[2][5] |= position;
            cube[3][1] |= position;
            cube[3][3] |= position;
            cube[3][5] |= position;
            cube[4][1] |= position;
            cube[4][2] |= position;
            cube[4][5] |= position;
            cube[5][1] |= position;
            cube[5][5] |= position;
            cube[6][1] |= position;
            cube[6][5] |= position;
            break;
        case 'o':
            cube[0][2] |= position;
            cube[0][3] |= position;
            cube[0][4] |= position;
            cube[1][1] |= position;
            cube[1][5] |= position;
            cube[2][1] |= position;
            cube[2][5] |= position;
            cube[3][1] |= position;
            cube[3][5] |= position;
            cube[4][1] |= position;
            cube[4][5] |= position;
            cube[5][1] |= position;
            cube[5][5] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            break;
        case 'p':
            cube[0][1] |= position;
            cube[1][1] |= position;
            cube[2][1] |= position;
            cube[3][1] |= position;
            cube[3][2] |= position;
            cube[3][3] |= position;
            cube[3][4] |= position;
            cube[4][1] |= position;
            cube[4][5] |= position;
            cube[5][1] |= position;
            cube[5][5] |= position;
            cube[6][1] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            break;
        case 'q': 
            cube[0][2] |= position;
            cube[0][3] |= position;
            cube[0][5] |= position;
            cube[1][1] |= position;
            cube[1][4] |= position;
            cube[2][1] |= position;
            cube[2][3] |= position;
            cube[2][5] |= position;
            cube[3][1] |= position;
            cube[3][5] |= position;
            cube[4][1] |= position;
            cube[4][5] |= position;
            cube[5][1] |= position;
            cube[5][5] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            break;
        case 'r':
            cube[0][1] |= position;
            cube[0][5] |= position;
            cube[1][1] |= position;
            cube[1][4] |= position;
            cube[2][1] |= position;
            cube[2][3] |= position;
            cube[3][1] |= position;
            cube[3][2] |= position;
            cube[3][3] |= position;
            cube[3][4] |= position;
            cube[4][1] |= position;
            cube[4][5] |= position;
            cube[5][1] |= position;
            cube[5][5] |= position;
            cube[6][1] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            break;
        case 's':
            cube[0][1] |= position;
            cube[0][2] |= position;
            cube[0][3] |= position;
            cube[0][4] |= position;
            cube[1][5] |= position;
            cube[2][5] |= position;
            cube[3][2] |= position;
            cube[3][3] |= position;
            cube[3][4] |= position;
            cube[4][1] |= position;
            cube[5][1] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            cube[6][5] |= position;
            break;
        case 't':
            cube[0][3] |= position;
            cube[1][3] |= position;
            cube[2][3] |= position;
            cube[3][3] |= position;
            cube[4][3] |= position;
            cube[5][3] |= position;
            cube[6][1] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            cube[6][5] |= position;
            break;
        case 'u':
            cube[0][2] |= position;
            cube[0][3] |= position;
            cube[0][4] |= position;
            cube[1][1] |= position;
            cube[1][5] |= position;
            cube[2][1] |= position;
            cube[2][5] |= position;
            cube[3][1] |= position;
            cube[3][5] |= position;
            cube[4][1] |= position;
            cube[4][5] |= position;
            cube[5][1] |= position;
            cube[5][5] |= position;
            cube[6][1] |= position;
            cube[6][5] |= position;
            break;
        case 'v':
            cube[0][3] |= position;
            cube[1][2] |= position;
            cube[1][4] |= position;
            cube[2][1] |= position;
            cube[2][5] |= position;
            cube[3][1] |= position;
            cube[3][5] |= position;
            cube[4][1] |= position;
            cube[4][5] |= position;
            cube[5][1] |= position;
            cube[5][5] |= position;
            cube[6][1] |= position;
            cube[6][5] |= position;
            break;
        case 'w':
            cube[0][2] |= position;
            cube[0][4] |= position;
            cube[1][1] |= position;
            cube[1][3] |= position;
            cube[1][5] |= position;
            cube[2][1] |= position;
            cube[2][3] |= position;
            cube[2][5] |= position;
            cube[3][1] |= position;
            cube[3][3] |= position;
            cube[3][5] |= position;
            cube[4][1] |= position;
            cube[4][5] |= position;
            cube[5][1] |= position;
            cube[5][5] |= position;
            cube[6][1] |= position;
            cube[6][5] |= position;
            break;
        case 'x': 
            cube[0][1] |= position;
            cube[0][5] |= position;
            cube[1][1] |= position;
            cube[1][5] |= position;
            cube[2][2] |= position;
            cube[2][4] |= position;
            cube[3][3] |= position;
            cube[4][2] |= position;
            cube[4][4] |= position;
            cube[5][1] |= position;
            cube[5][5] |= position;
            cube[6][1] |= position;
            cube[6][5] |= position;
            break;
        case 'y':
            cube[0][3] |= position;
            cube[1][3] |= position;
            cube[2][3] |= position;
            cube[3][2] |= position;
            cube[3][4] |= position;
            cube[4][1] |= position;
            cube[4][5] |= position;
            cube[5][1] |= position;
            cube[5][5] |= position;
            cube[6][1] |= position;
            cube[6][5] |= position;
            break;
        case 'z':
            cube[0][1] |= position;
            cube[0][2] |= position;
            cube[0][3] |= position;
            cube[0][4] |= position;
            cube[0][5] |= position;
            cube[1][1] |= position;
            cube[2][2] |= position;
            cube[3][3] |= position;
            cube[4][4] |= position;
            cube[5][5] |= position;
            cube[6][1] |= position;
            cube[6][2] |= position;
            cube[6][3] |= position;
            cube[6][4] |= position;
            cube[6][5] |= position;
            break;
        default:
            break;
    }
    
    for (int a=0; a<8; a++) {
        for (int b=0; b<8; b++) {
            buffer[((a * 8) + b)] = cube[a][b];
        }
    }

    return buffer;
}

+ (void)setLetter:(unichar)letter toBelt:(uint8_t *)belt
{
    uint8_t *cubeLetter = [LPAnimationsLetters getCubeEffectForLetter:letter position:0];
    
    for (int layer=0; layer<8; layer++) {
        for (int i=1; i<6; i++){
            if (cubeLetter[(layer * 8) + i] & 0x01) {
                belt[5-i] |= (1 << layer);
            }
        }
    }
    
    free(cubeLetter);
}

@end