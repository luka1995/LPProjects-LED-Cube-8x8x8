//
//  LPAnimations.m
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 13/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPAnimations.h"


#define WAVES_DEPTH 0xFF


@implementation LPAnimations

+ (NSMutableArray *)getArrayStringFrontText:(NSString *)text delay:(uint8_t)delay delayUnit:(uint8_t)delayUnit effectName:(NSString *)effectName
{
    NSMutableArray *array = [NSMutableArray new];

    if (text) {
        text = [text lowercaseString];
        
        int count = 1;
        
        for (int i=0; i<[text length]; i++) {
            unichar letter = [[text lowercaseString] characterAtIndex:i];
            
            for (int z=7; z>=0; z--) {
                LPCubeEffect *cubeEffect = [LPCubeEffect new];
                cubeEffect.cube = [LPAnimationsLetters getCubeEffectForLetter:letter position:z];
                cubeEffect.name = [[NSString stringWithFormat:@"%@ - %c - %d", effectName, letter, count++] uppercaseString];
                cubeEffect.delay = delay;
                cubeEffect.delayUnit = delayUnit;
                
                [array addObject:cubeEffect];
            }
        }
    }
    
    return array;
}

+ (NSMutableArray *)getArrayWavesDelay:(uint8_t)delay delayUnit:(uint8_t)delayUnit repeats:(uint8_t)repeats effectName:(NSString *)effectName
{
    NSMutableArray *array = [NSMutableArray new];
    
    uint8_t *cube = malloc(64);
    memset(cube, 0x00, 64);
    
    int count = 1;
    
    for (int i=0; i<repeats; i++) {
        for (int a=3; a>=0; a--) {
            LPCubeEffect *cubeEffect = [LPCubeEffect new];
            cubeEffect.name = [[NSString stringWithFormat:@"%@ - %d", effectName, count++] uppercaseString];
            cubeEffect.delay = delay;
            cubeEffect.delayUnit = delayUnit;
            
            cube = [LPTranslation move_x_revCube:cube X1:0 Y1:0 X2:7 Y2:7];
            cube[(a * 8) + 7] |= WAVES_DEPTH;
            cubeEffect.cube = cube;
            
            [array addObject:cubeEffect];
        }
        
        for (int a=0; a<=7; a++) {
            LPCubeEffect *cubeEffect = [LPCubeEffect new];
            cubeEffect.name = [[NSString stringWithFormat:@"%@ - %d", effectName, count++] uppercaseString];
            cubeEffect.delay = delay;
            cubeEffect.delayUnit = delayUnit;
            
            cube = [LPTranslation move_x_revCube:cube X1:0 Y1:0 X2:7 Y2:7];
            cube[(a * 8) + 7] |= WAVES_DEPTH;
            cubeEffect.cube = cube;
            
            [array addObject:cubeEffect];
        }
        
        for (int a=7; a>=4; a--) {
            LPCubeEffect *cubeEffect = [LPCubeEffect new];
            cubeEffect.name = [[NSString stringWithFormat:@"%@ - %d", effectName, count++] uppercaseString];
            cubeEffect.delay = delay;
            cubeEffect.delayUnit = delayUnit;
            
            cube = [LPTranslation move_x_revCube:cube X1:0 Y1:0 X2:7 Y2:7];
            cube[(a * 8) + 7] |= WAVES_DEPTH;
            cubeEffect.cube = cube;
            
            [array addObject:cubeEffect];
        }
    }
    
    return array;
}

+ (NSMutableArray *)getArrayCubes4Delay:(uint8_t)delay delayUnit:(uint8_t)delayUnit repeats:(uint8_t)repeats effectName:(NSString *)effectName
{
    NSMutableArray *array = [NSMutableArray new];
    
    uint8_t *cube = malloc(64);
    memset(cube, 0x00, 64);

    for (int layer=0; layer<=3; layer++) {
        cube[(layer * 8) + 0] = 0x0F;
        cube[(layer * 8) + 1] = 0x0F;
        cube[(layer * 8) + 2] = 0x0F;
        cube[(layer * 8) + 3] = 0x0F;
    }
    
    for (int layer=4; layer<=7; layer++) {
        cube[(layer * 8) + 4] = 0xFF;
        cube[(layer * 8) + 5] = 0xFF;
        cube[(layer * 8) + 6] = 0xFF;
        cube[(layer * 8) + 7] = 0xFF;
    }

    int count = 1;
    
    LPCubeEffect *cubeEffect = [LPCubeEffect new];
    cubeEffect.name = [[NSString stringWithFormat:@"%@ - %d", effectName, count++] uppercaseString];
    cubeEffect.delay = delay;
    cubeEffect.delayUnit = delayUnit;
    uint8_t *cubeSave = malloc(64);
    memcpy(cubeSave, cube, 64);
    cubeEffect.cube = cubeSave;
    [array addObject:cubeEffect];
    
    for (int i=0; i<repeats; i++) {
        for (int a=0; a<12; a++) {
            for (int fourtimes=0; fourtimes<=3; fourtimes++) {
                LPCubeEffect *cubeEffect = [LPCubeEffect new];
                cubeEffect.name = [[NSString stringWithFormat:@"%@ - %d", effectName, count++] uppercaseString];
                cubeEffect.delay = delay;
                cubeEffect.delayUnit = delayUnit;

                switch (a) {
                    case 0: cube = [LPTranslation move_y_revCube:cube X1:4 Y1:0 X2:7 Y2:3]; break;
                    case 1: cube = [LPTranslation move_z_fwdCube:cube X1:0 Y1:0 X2:3 Y2:3]; break;
                    case 2: cube = [LPTranslation move_y_fwdCube:cube X1:0 Y1:4 X2:3 Y2:7]; break;
                    case 3: cube = [LPTranslation move_y_revCube:cube X1:4 Y1:4 X2:7 Y2:7]; break;
                    case 4: cube = [LPTranslation move_x_revCube:cube X1:0 Y1:0 X2:3 Y2:3]; break;
                    case 5: cube = [LPTranslation move_z_revCube:cube X1:4 Y1:0 X2:7 Y2:3]; break;
                    case 6: cube = [LPTranslation move_z_fwdCube:cube X1:4 Y1:0 X2:7 Y2:3]; break;
                    case 7: cube = [LPTranslation move_y_fwdCube:cube X1:4 Y1:4 X2:7 Y2:7]; break;
                    case 8: cube = [LPTranslation move_x_fwdCube:cube X1:0 Y1:0 X2:3 Y2:3]; break;
                    case 9: cube = [LPTranslation move_y_fwdCube:cube X1:4 Y1:0 X2:7 Y2:3]; break;
                    case 10: cube = [LPTranslation move_y_revCube:cube X1:0 Y1:4 X2:3 Y2:7]; break;
                    case 11: cube = [LPTranslation move_z_revCube:cube X1:0 Y1:0 X2:3 Y2:3]; break;
                }

                uint8_t *cubeSave = malloc(64);
                memcpy(cubeSave, cube, 64);
                cubeEffect.cube = cubeSave;
                [array addObject:cubeEffect];
            }
        }
    }
    
    free(cube);
    
    return array;
}

+ (void)moveBeltLeft:(uint8_t *)belt
{
    for (int i=25; i>1; i--){
        belt[i-1] = belt[i-2];
    }
    
    belt[0] = 0;
}

+ (uint8_t *)getCubeFromBelt:(uint8_t *)belt
{
    uint8_t *cube = malloc(64);
    memset(cube, 0x00, 64);
    
    /* right side */
    for (int i=5; i<=11; i++){
        for (int j=0; j<8; j++){
            if (belt[i] & (1 << j))
                cube[(j * 8) + 7] |= (1 << (12-i));
        }
    }
    /* front side */
    for (int i=12; i<=17; i++){
        for (int j=0; j<8; j++){
            if (belt[i] & (1 << j))
                cube[(j * 8) + (18 - i)] |= (1 << 0);
        }
    }
    /* left side */
    for (int i = 18; i<=24; i++){
        for (int j = 0; j<8; j++){
            if (belt[i] & (1 << j))
                cube[(j * 8) + 0] |= (1 << (i-17));
        }
    }
    
    return cube;
}

+ (NSMutableArray *)getArrayStringBeltLeftText:(NSString *)text delay:(uint8_t)delay delayUnit:(uint8_t)delayUnit effectName:(NSString *)effectName
{
    NSMutableArray *array = [NSMutableArray new];
    
    if (text) {
        text = [text lowercaseString];


        uint8_t *cubeBelt = malloc(25);
        memset(cubeBelt, 0x00, 25);
        
        
        int count = 1;
        
        for (int i=0; i<[text length]; i++) {
            unichar letter = [text characterAtIndex:i];
            
            [LPAnimationsLetters setLetter:letter toBelt:cubeBelt];
            
            for (int a=0; a<6; a++) {
                LPCubeEffect *cubeEffect = [LPCubeEffect new];
                cubeEffect.name = [NSString stringWithFormat:@"%@ - %d", effectName, count++];
                cubeEffect.delay = delay;
                cubeEffect.delayUnit = delayUnit;

                cubeEffect.cube = [LPAnimations getCubeFromBelt:cubeBelt];

                [array addObject:cubeEffect];
                
                [LPAnimations moveBeltLeft:cubeBelt];
            }
        }
        
        for (int i=0; i<18; i++) {
            LPCubeEffect *cubeEffect = [LPCubeEffect new];
            cubeEffect.name = [NSString stringWithFormat:@"%@ - %d", effectName, count++];
            cubeEffect.delay = delay;
            cubeEffect.delayUnit = delayUnit;
            
            cubeEffect.cube = [LPAnimations getCubeFromBelt:cubeBelt];
            
            [array addObject:cubeEffect];
            
            [LPAnimations moveBeltLeft:cubeBelt];
        }
    }
    
    return array;
}

@end
