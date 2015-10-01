//
//  LPAnimation.m
//  LP_LED_CUBE_8x8x8
//
//  Created by Luka Penger on 27/06/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPAnimation.h"


@implementation LPAnimation

- (id)init
{
    if (self = [super init]) {
        self.fileName = @"";
    }
    
    return self;
}

- (id)initWithCoder:(NSCoder *)coder
{
	self = [LPAnimation new];
    
    if (self) {
        self.fileName = [coder decodeObjectForKey:@"fileName"];
        self.effectsList = [coder decodeObjectForKey:@"effectsList"];
	}
    
	return self;
}

- (void)encodeWithCoder:(NSCoder *)coder
{
    [coder encodeObject:self.fileName forKey:@"fileName"];
    [coder encodeObject:self.effectsList forKey:@"effectsList"];
}

+ (id)animationWithBuffer:(uint8_t *)buffer length:(int)length
{
    LPAnimation *new = [LPAnimation new];

    if (length > 0) {
        int count = (length / [LPCubeEffect size]);
        
        for (int i=0; i<count; i++) {
            uint8_t data[[LPCubeEffect size]];
            
            memcpy(data, buffer + (i * [LPCubeEffect size]), [LPCubeEffect size]);
            
            LPCubeEffect *effect = [LPCubeEffect cubeEffectWithBuffer:data];
            
            [new.effectsList addObject:effect];
        }
    }
    
    return new;
}

- (NSMutableArray *)effectsList
{
    if (!_effectsList) {
        _effectsList = [NSMutableArray new];
    }
    return _effectsList;
}

- (NSDictionary *)dictionary
{
    NSMutableDictionary *dictionary = [NSMutableDictionary new];
    
    if (self.effectsList && ![self.effectsList isKindOfClass:[NSNull class]]) {
        NSMutableArray *array = [NSMutableArray new];
        
        for (int i=0; i<[self.effectsList count]; i++) {
            [array addObject:((LPCubeEffect *)[self.effectsList objectAtIndex:i]).dictionary];
        }
        
        [dictionary setObject:array forKey:@"effectsList"];
    }
    
    [dictionary setObject:[NSString stringWithFormat:@"%@", self.fileName] forKey:@"fileName"];
    
    return dictionary;
}

- (NSString *)description
{
    return [self dictionary].description;
}

- (id)copy
{
    LPAnimation *new = [LPAnimation new];
    
    [new setEffectsList:[[NSMutableArray alloc] initWithArray:self.effectsList]];
    [new setFileName:self.fileName];
    
    return new;
}

- (uint8_t *)getBytes
{
    uint8_t *buffer = malloc([self getBytesLength]);
    memset(buffer, 0x00, [self getBytesLength]);

    for (int i=0; i<[self.effectsList count]; i++) {
        LPCubeEffect *cubeEffect = (LPCubeEffect *)[self.effectsList objectAtIndex:i];

        uint8_t *bytes = [cubeEffect getBytes];
        memcpy(buffer + (i * [LPCubeEffect size]), bytes, [LPCubeEffect size]);
    }
    
    return buffer;
}

- (int)getBytesLength
{
    return ((int)[self.effectsList count] * [LPCubeEffect size]);
}

@end
