//
//  LPCubeScene.h
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 16/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPScene.h"


@interface LPCubeScene : LPScene

@property (nonatomic, assign) float zoom;
@property (nonatomic, assign) GLKVector3 translate, rotate, scale;
@property (nonatomic, assign) BOOL enabled;
@property (nonatomic, strong) GLKBaseEffect *effect;

@end
