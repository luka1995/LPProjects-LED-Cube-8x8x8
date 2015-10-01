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
        self.columns = malloc(8);
        memset(self.columns, 0x00, 8);
        self.rows = 0xFF;
        self.delay = 0;
        self.name = @"";
    }
    return self;
}

- (id)initWithCoder:(NSCoder *)coder
{
	self = [LPCubeEffect new];
    if (self) {
        self.columns = malloc(8);
        self.columns = (uint8_t *)[coder decodeBytesForKey:@"columns" returnedLength:nil];
        self.rows = [coder decodeIntForKey:@"rows"];
        self.delay = [coder decodeIntForKey:@"delay"];
        self.name = [coder decodeObjectForKey:@"name"];
	}
    
	return self;
}

- (void)encodeWithCoder:(NSCoder *)coder
{
    [coder encodeBytes:self.columns length:8 forKey:@"columns"];
    [coder encodeInt:self.rows forKey:@"rows"];
    [coder encodeInt:self.delay forKey:@"delay"];
    [coder encodeObject:self.name forKey:@"name"];
}

+ (id)cubeEffectWithBuffer:(uint8_t *)buffer
{
    LPCubeEffect *new = [LPCubeEffect new];
    
    new.columns = malloc(8);
    memcpy(new.columns, buffer, 8);

    new.rows = buffer[8];
    new.delay = buffer[9];
    
    NSMutableString *str = [NSMutableString new];
    
    for (int i=0; i<20; i++) {
        uint8_t ch = buffer[i + 10];
        
        if (ch != 0x00) {
            [str appendFormat:@"%c", ch];
        }
    }
    
    new.name = str;
    
    return new;
}

- (NSDictionary *)dictionary
{
    NSMutableDictionary *dictionary = [NSMutableDictionary new];
    
    NSMutableArray *array = [NSMutableArray new];
    for (int i=0; i<8; i++) {
        [array addObject:[NSString stringWithFormat:@"%d", self.columns[i]]];
    }
    [dictionary setObject:array forKey:@"columns"];
    
    [dictionary setObject:[NSString stringWithFormat:@"%d", self.rows] forKey:@"rows"];
    [dictionary setObject:[NSString stringWithFormat:@"%d", self.delay] forKey:@"delay"];
    [dictionary setObject:[NSString stringWithFormat:@"%@", self.name] forKey:@"name"];
    
    return dictionary;
}

- (NSString *)description
{
    return [self dictionary].description;
}

- (id)copyWithZone:(NSZone *)zone
{
    LPCubeEffect *new = [LPCubeEffect new];
    
    new.columns = malloc(8);
    memcpy(new.columns, self.columns, 8);
    [new setRows:self.rows];
    [new setDelay:self.delay];
    [new setName:self.name];
    
    return new;
}

+ (int)size
{
    return 30;
}

- (uint8_t *)getBytes
{
    uint8_t *buffer = malloc([LPCubeEffect size]);
    memset(buffer, 0x00, [LPCubeEffect size]);

    memcpy(buffer, self.columns, 8);
    buffer[8] = self.rows;
    buffer[9] = self.delay;
    
    for (int i=0; i<20; i++) {
        if (i < [self.name length]) {
            buffer[i + 10] = [self.name characterAtIndex:i];
        } else {
            buffer[i + 10] = 0x00;
        }
    }

    return buffer;
}

@end
