//
//  LPScene.m
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 16/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPScene.h"


@implementation LPScene

-(id)initWithFrame:(CGRect)frame context:(EAGLContext *)context
{
    self = [super init];
    if(self){
        self.bounds = frame;
        self.context = context;
    }
    return self;
}


-(void)update
{
    NSLog(@"ERROR! Child class to implement");
    assert(NO);
}

-(void)render
{
    NSLog(@"ERROR! Child class to implement");
    assert(NO);
}

- (void)setupGL
{
    NSLog(@"ERROR! Child child class to implement");
    assert(NO);
}

@end
