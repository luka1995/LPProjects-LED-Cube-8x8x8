//
//  LPAnimations.h
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 13/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LPAnimationsLetters.h"
#import "LPTranslation.h"


@interface LPAnimations : NSObject

+ (NSMutableArray *)getArrayStringFrontText:(NSString *)text delay:(uint8_t)delay delayUnit:(uint8_t)delayUnit effectName:(NSString *)effectName;

+ (NSMutableArray *)getArrayWavesDelay:(uint8_t)delay delayUnit:(uint8_t)delayUnit repeats:(uint8_t)repeats effectName:(NSString *)effectName;

+ (NSMutableArray *)getArrayCubes4Delay:(uint8_t)delay delayUnit:(uint8_t)delayUnit repeats:(uint8_t)repeats effectName:(NSString *)effectName;

+ (NSMutableArray *)getArrayStringBeltLeftText:(NSString *)text delay:(uint8_t)delay delayUnit:(uint8_t)delayUnit effectName:(NSString *)effectName;

@end
