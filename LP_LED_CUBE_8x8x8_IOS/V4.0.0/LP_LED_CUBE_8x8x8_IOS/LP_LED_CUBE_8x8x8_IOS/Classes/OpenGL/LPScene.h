//
//  LPScene.h
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 16/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GLKit/GLKit.h>
#import <OpenGLES/ES2/gl.h>


@protocol LPSceneProtocol <NSObject>

-(id)initWithFrame:(CGRect)frame context:(EAGLContext *)context;
-(void)render;
-(void)update;
-(void)setupGL;

@end


@interface LPScene : NSObject

@property (nonatomic, strong) EAGLContext *context;
@property (nonatomic, assign) CGRect bounds;

-(id)initWithFrame:(CGRect)frame context:(EAGLContext *)context;
-(void)render;
-(void)update;
-(void)setupGL;

@end
