//
//  LPPreview3DViewController.m
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 14/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPPreview3DViewController.h"


@interface LPPreview3DViewController ()

@property (nonatomic, strong) LPGLKViewController *glkViewController;

@end


@implementation LPPreview3DViewController

#pragma mark - Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.title = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"Preview3DTitle"];
    
    self.view.backgroundColor = [UIColor blackColor];
    
    if (self.backButton) {
        self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"BackButton"] style:UIBarButtonItemStyleBordered target:self action:@selector(backButtonClicked)];
    }
    
    if (self.closeButton) {
        self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"CloseButton"] style:UIBarButtonItemStyleBordered target:self action:@selector(closeButtonClicked)];
    }
    
    [self.startStopButton setTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"Preview3DStopAnimationButtonTitle"] forState:UIControlStateNormal];
    [self.rotationHomeButton setTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"Preview3DRotationHomeButtonTItle"] forState:UIControlStateNormal];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
 
    [ProgressHUD show:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"Preview3DLoadingTitle"] Interaction:NO];

    dispatch_async(dispatch_get_main_queue(), ^(void) {
        if (!self.glkViewController) {
            self.glkViewController = [[LPGLKViewController alloc] initWithNibName:@"LPGLKViewController" bundle:nil];
            self.glkViewController.delegateController = self;
            self.glkViewController.animation = self.animation;
            self.glkViewController.view.frame = CGRectMake(0.0f, 0.0f, self.view.frame.size.width, (self.view.frame.size.height - self.buttonsView.frame.size.height));
            
            [self addChildViewController:self.glkViewController];
            [self.view addSubview:self.glkViewController.view];
        }
    });
}

- (void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];

}

#pragma mark - Actions

- (void)closeButtonClicked
{
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        [self dismissViewControllerAnimated:YES completion:nil];
    } else {
        [[[LPSharedManager sharedManager] splitViewControllerIpad] hideModalViewControllerAnimated:YES];
    }
}

- (void)backButtonClicked
{
    [self.navigationController popViewControllerAnimated:YES];
}

- (IBAction)rotationHomeButtonClicked:(id)sender
{
    [self.glkViewController setRotationHome];
}

- (IBAction)startStopButtonClicked:(id)sender
{
    if (self.glkViewController.animationPlayer) {
        [self.glkViewController stopAnimation];
    } else {
        [self.glkViewController startAnimation];
    }
}

#pragma mark - GLK View Delegate

- (void)animationStarted
{
    [self.startStopButton setTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"Preview3DStopAnimationButtonTitle"] forState:UIControlStateNormal];
}

- (void)animationStoped
{
    [self.startStopButton setTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"Preview3DStartAnimationButtonTitle"] forState:UIControlStateNormal];
}

@end
