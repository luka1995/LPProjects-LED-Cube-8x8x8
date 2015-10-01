//
//  LPAnimationsLetters.h
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 13/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LPCubeEffect.h"


@interface LPAnimationsLetters : NSObject

+ (uint8_t *)getCubeEffectForLetter:(unichar)letter position:(int)position;

+ (void)setLetter:(unichar)letter toBelt:(uint8_t *)belt;

@end
