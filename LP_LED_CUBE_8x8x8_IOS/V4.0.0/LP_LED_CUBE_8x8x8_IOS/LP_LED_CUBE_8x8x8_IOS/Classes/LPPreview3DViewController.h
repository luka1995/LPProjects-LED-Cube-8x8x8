//
//  LPPreview3DViewController.h
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 14/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPAnimation.h"
#import "LPToastView.h"
#import "LPSharedManager.h"
#import <GLKit/GLKit.h>
#import "LPCubeScene.h"
#import "ProgressHUD.h"
#import "LPGLKViewController.h"


@interface LPPreview3DViewController : UIViewController <LPGLKViewControllerDelegate>

@property (nonatomic, assign) BOOL backButton, closeButton;
@property (nonatomic, strong) LPAnimation *animation;
@property (nonatomic, strong) IBOutlet UIView *buttonsView;
@property (nonatomic, strong) IBOutlet UIButton *rotationHomeButton, *startStopButton;

- (IBAction)rotationHomeButtonClicked:(id)sender;
- (IBAction)startStopButtonClicked:(id)sender;

@end
