//
//  LPCubeEffect.h
//  LP_LED_CUBE_8x8x8
//
//  Created by Luka Penger on 27/06/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface LPCubeEffect : NSObject <NSCoding>

@property (nonatomic, assign) uint8_t *cube;
@property (nonatomic, assign) uint8_t view;
@property (nonatomic, assign) uint8_t delay;
@property (nonatomic, assign) uint8_t delayUnit;
@property (nonatomic, strong) NSString *name;

+ (id)cubeEffectWithBuffer:(uint8_t *)buffer;

- (NSDictionary *)dictionary;

- (id)copy;

+ (int)size;
- (uint8_t *)getBytes;

@end
