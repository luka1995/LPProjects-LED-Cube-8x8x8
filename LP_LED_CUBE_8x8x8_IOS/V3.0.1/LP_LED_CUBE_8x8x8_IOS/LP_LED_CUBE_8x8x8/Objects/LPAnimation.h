//
//  LPAnimation.h
//  LP_LED_CUBE_8x8x8
//
//  Created by Luka Penger on 27/06/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LPCubeEffect.h"


@interface LPAnimation : NSObject <NSCoding>

@property (nonatomic, strong) NSMutableArray *effectsList;
@property (nonatomic, strong) NSString *fileName;

+ (id)animationWithBuffer:(uint8_t *)buffer length:(int)length;

- (NSDictionary *)dictionary;

- (id)copyWithZone:(NSZone *)zone;

- (uint8_t *)getBytes;
- (int)getBytesLength;

@end
