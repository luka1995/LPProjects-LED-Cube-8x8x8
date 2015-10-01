//
//  LPGLKViewController.h
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 30/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <GLKit/GLKit.h>
#import "LPAnimation.h"
#import "LPToastView.h"
#import "LPSharedManager.h"
#import <GLKit/GLKit.h>
#import "LPCubeScene.h"
#import "ProgressHUD.h"

@protocol LPGLKViewControllerDelegate;

@interface LPGLKViewController : GLKViewController

@property (nonatomic, weak) id<LPGLKViewControllerDelegate> delegateController;
@property (nonatomic, assign, readonly) BOOL animationPlayer;
@property (nonatomic, strong) LPAnimation *animation;

- (void)startAnimation;
- (void)stopAnimation;
- (void)setRotationHome;

@end


@protocol LPGLKViewControllerDelegate <NSObject>

@optional

- (void)animationStarted;
- (void)animationStoped;

@end