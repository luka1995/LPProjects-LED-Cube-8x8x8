//
//  LPCubeEffect.m
//  LP_LED_CUBE_8x8x8
//
//  Created by Luka Penger on 27/06/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPCubeEffect.h"


@implementation LPCubeEffect

- (id)init
{
    if (self = [super init]) {
        self.cube = malloc(64);
        memset(self.cube, 0x00, 64);
        self.view = 0;
        self.delay = 10;
        self.delayUnit = 1;
        self.name = @"";
    }
    
    return self;
}

- (id)initWithCoder:(NSCoder *)coder
{
	self = [LPCubeEffect new];
    
    if (self) {
        self.cube = malloc(64);
        NSData *data = (NSData *)[coder decodeObjectForKey:@"cube"];
        memcpy(self.cube, [data bytes], 64);
        self.view = [coder decodeIntForKey:@"view"];
        self.delay = [coder decodeIntForKey:@"delay"];
        self.delayUnit = [coder decodeIntForKey:@"delayUnit"];
        self.name = [coder decodeObjectForKey:@"name"];
	}
    
	return self;
}

- (void)encodeWithCoder:(NSCoder *)coder
{
    [coder encodeObject:[NSData dataWithBytes:self.cube length:64] forKey:@"cube"];
    [coder encodeInt:self.view forKey:@"view"];
    [coder encodeInt:self.delay forKey:@"delay"];
    [coder encodeInt:self.delayUnit forKey:@"delayUnit"];
    [coder encodeObject:self.name forKey:@"name"];
}

+ (id)cubeEffectWithBuffer:(uint8_t *)buffer
{
    LPCubeEffect *new = [LPCubeEffect new];
    
    new.cube = malloc(64);
    memcpy(new.cube, buffer, 64);
    
    NSMutableString *str = [NSMutableString new];
    for (int i=0; i<20; i++) {
        uint8_t ch = buffer[i + 64];
        
        if (ch != 0x00) {
            [str appendFormat:@"%c", ch];
        }
    }
    new.name = str;

    new.delay = buffer[84];
    new.delayUnit = buffer[85];
    new.view = buffer[86];
    
    return new;
}

- (NSDictionary *)dictionary
{
    NSMutableDictionary *dictionary = [NSMutableDictionary new];
    
    NSMutableArray *array = [NSMutableArray new];
    for (int i=0; i<64; i++) {
        [array addObject:[NSString stringWithFormat:@"%d", self.cube[i]]];
    }
    [dictionary setObject:array forKey:@"cube"];

    [dictionary setObject:[NSString stringWithFormat:@"%d", self.view] forKey:@"view"];
    [dictionary setObject:[NSString stringWithFormat:@"%d", self.delay] forKey:@"delay"];
    [dictionary setObject:[NSString stringWithFormat:@"%d", self.delayUnit] forKey:@"delayUnit"];
    [dictionary setObject:[NSString stringWithFormat:@"%@", self.name] forKey:@"name"];

    return dictionary;
}

- (NSString *)description
{
    return [self dictionary].description;
}

- (id)copy
{
    LPCubeEffect *new = [LPCubeEffect new];
    
    new.cube = malloc(64);
    memcpy(new.cube, self.cube, 64);
    [new setName:self.name];
    [new setDelay:self.delay];
    [new setDelayUnit:self.delayUnit];
    [new setView:self.view];
    
    return new;
}

+ (int)size
{
    return 90;
}

- (uint8_t *)getBytes
{
    uint8_t *buffer = malloc([LPCubeEffect size]);
    memset(buffer, 0x00, [LPCubeEffect size]);

    memcpy(buffer, self.cube, 64);
    
    for (int i=0; i<20; i++) {
        if (i < [self.name length]) {
            buffer[i + 64] = [self.name characterAtIndex:i];
        } else {
            buffer[i + 64] = 0x00;
        }
    }

    buffer[84] = self.delay;
    buffer[85] = self.delayUnit;
    buffer[86] = self.view;
    
    // 3 bytes are reserved
    
    return buffer;
}

@end
