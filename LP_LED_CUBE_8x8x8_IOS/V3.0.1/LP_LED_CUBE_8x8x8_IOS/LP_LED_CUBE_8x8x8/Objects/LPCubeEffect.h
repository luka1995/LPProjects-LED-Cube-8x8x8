//
//  LPCubeEffect.h
//  LP_LED_CUBE_8x8x8
//
//  Created by Luka Penger on 27/06/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface LPCubeEffect : NSObject <NSCoding>

@property (nonatomic, assign) uint8_t *columns;
@property (nonatomic, assign) uint8_t rows;
@property (nonatomic, assign) uint8_t delay;
@property (nonatomic, strong) NSString *name;

+ (id)cubeEffectWithBuffer:(uint8_t *)buffer;

- (NSDictionary *)dictionary;

- (id)copyWithZone:(NSZone *)zone;

+ (int)size;
- (uint8_t *)getBytes;

@end
