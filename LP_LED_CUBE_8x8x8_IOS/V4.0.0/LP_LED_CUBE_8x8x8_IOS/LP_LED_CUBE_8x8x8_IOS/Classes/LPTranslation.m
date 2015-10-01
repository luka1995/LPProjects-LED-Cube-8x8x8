//
//  LPTranslation.m
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 22/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPTranslation.h"


@implementation LPTranslation

+ (uint8_t *)move_x_revCube:(uint8_t *)cube X1:(uint8_t)x1 Y1:(uint8_t)y1 X2:(uint8_t)x2 Y2:(uint8_t)y2
{
    char newCube[8][8];

    for (int a=0; a<8; a++) {
        for (int b=0; b<8; b++) {
            newCube[a][b] = cube[((a * 8) + b)];
        }
    }

    for (int layer = y1; layer<=y2; layer++) {
        for (int j=0; j<7; j++){
            for (int k = x1; k<=x2; k++) {
                if ((newCube[layer][j+1] & (1 << k))){
                    newCube[layer][j] |= (1 << k);
                    newCube[layer][j+1] &= ~(1 << k);
                } else {
                    newCube[layer][j] &= ~(1 << k);
                }
            }
            
        }
    }

    uint8_t *returnCube = malloc(64);
    for (int a=0; a<8; a++) {
        for (int b=0; b<8; b++) {
            returnCube[((a * 8) + b)] = newCube[a][b];
        }
    }
    
    return returnCube;
}

+ (uint8_t *)move_y_revCube:(uint8_t *)cube X1:(uint8_t)x1 Y1:(uint8_t)y1 X2:(uint8_t)x2 Y2:(uint8_t)y2
{
    char newCube[8][8];
    
    for (int a=0; a<8; a++) {
        for (int b=0; b<8; b++) {
            newCube[a][b] = cube[((a * 8) + b)];
        }
    }
    
    for (int i=1; i<8; i++){
        for (int j=x1; j<=x2; j++){
            for (int k=y1; k<=y2; k++) {
                if ((newCube[i][j] & (1 << k))){
                    newCube[i-1][j] |= (1 << k);
                    newCube[i][j] &= ~(1 << k);
                } else {
                    newCube[i-1][j] &= ~(1 << k);
                }
            }
        }
    }
        
    uint8_t *returnCube = malloc(64);
    for (int a=0; a<8; a++) {
        for (int b=0; b<8; b++) {
            returnCube[((a * 8) + b)] = newCube[a][b];
        }
    }
    
    return returnCube;
}

+ (uint8_t *)move_z_revCube:(uint8_t *)cube X1:(uint8_t)x1 Y1:(uint8_t)y1 X2:(uint8_t)x2 Y2:(uint8_t)y2
{
    char newCube[8][8];
    
    for (int a=0; a<8; a++) {
        for (int b=0; b<8; b++) {
            newCube[a][b] = cube[((a * 8) + b)];
        }
    }

    for (; x1<=x2; x1++) {
        for (int i=y1; i<=y2; i++) {
            newCube[x1][i] = (newCube[x1][i] >> 1);
        }
    }
    
    uint8_t *returnCube = malloc(64);
    for (int a=0; a<8; a++) {
        for (int b=0; b<8; b++) {
            returnCube[((a * 8) + b)] = newCube[a][b];
        }
    }
    
    return returnCube;
}

+ (uint8_t *)move_x_fwdCube:(uint8_t *)cube X1:(uint8_t)x1 Y1:(uint8_t)y1 X2:(uint8_t)x2 Y2:(uint8_t)y2
{
    char newCube[8][8];
    
    for (int a=0; a<8; a++) {
        for (int b=0; b<8; b++) {
            newCube[a][b] = cube[((a * 8) + b)];
        }
    }
    
    for (int layer = y1; layer<=y2; layer++) {
        for (int j=7; j>0; j--){
            for (int k=x1; k<=x2; k++) {
                if ((newCube[layer][j-1] & (1 << k))){
                    newCube[layer][j] |= (1 << k);
                    newCube[layer][j-1] &= ~(1 << k);
                } else {
                    /* delete the pixel anyway */
                    newCube[layer][j] &= ~(1 << k);
                }
            }
            
        }
    }
    
    uint8_t *returnCube = malloc(64);
    for (int a=0; a<8; a++) {
        for (int b=0; b<8; b++) {
            returnCube[((a * 8) + b)] = newCube[a][b];
        }
    }
    
    return returnCube;
}

+ (uint8_t *)move_y_fwdCube:(uint8_t *)cube X1:(uint8_t)x1 Y1:(uint8_t)y1 X2:(uint8_t)x2 Y2:(uint8_t)y2
{
    char newCube[8][8];
    
    for (int a=0; a<8; a++) {
        for (int b=0; b<8; b++) {
            newCube[a][b] = cube[((a * 8) + b)];
        }
    }
    
    for (int i=7; i>0; i--){
        for (int j=x1; j<=x2; j++){
            for (int k=y1; k <= y2; k++) {
                if ((newCube[i-1][j] & (1 << k))){
                    newCube[i][j] |= (1 << k);
                    newCube[i-1][j] &= ~(1 << k);
                } else {
                    newCube[i-1][j] &= ~(1 << k);
                }
            }
        }
    }
    
    uint8_t *returnCube = malloc(64);
    for (int a=0; a<8; a++) {
        for (int b=0; b<8; b++) {
            returnCube[((a * 8) + b)] = newCube[a][b];
        }
    }
    
    return returnCube;
}

+ (uint8_t *)move_z_fwdCube:(uint8_t *)cube X1:(uint8_t)x1 Y1:(uint8_t)y1 X2:(uint8_t)x2 Y2:(uint8_t)y2
{
    char newCube[8][8];
    
    for (int a=0; a<8; a++) {
        for (int b=0; b<8; b++) {
            newCube[a][b] = cube[((a * 8) + b)];
        }
    }
    
    for (; x1<=x2; x1++){
        for (int i=y1; i<=y2; i++){
            newCube[x1][i] = (newCube[x1][i] << 1);
        }
    }
    
    uint8_t *returnCube = malloc(64);
    for (int a=0; a<8; a++) {
        for (int b=0; b<8; b++) {
            returnCube[((a * 8) + b)] = newCube[a][b];
        }
    }
    
    return returnCube;
}

@end
