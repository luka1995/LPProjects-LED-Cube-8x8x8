//
//  LPSplitViewController.m
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 26/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPSplitViewController.h"


#define pushViewPaddingLeftRight    200.0f
#define pushViewPaddingTopBottom     40.0f


@interface LPSplitViewController ()

@property (nonatomic, strong) UIView *pushView;
@property (nonatomic, strong) UIViewController *pushViewController;

@end


@implementation LPSplitViewController

- (id)initWithMenuViewController:(UIViewController*)menuViewController detailsViewController:(UIViewController*)detailsViewController
{
    self = [super init];
    if (self) {
        self.menuViewController = menuViewController;
        self.detailsViewController = detailsViewController;
        
        self.menuWidth = 360.0f;
        
        self.menuViewShadowColor = [UIColor blackColor];
        self.menuViewShadowRadius = 2.5f;
        self.menuViewShadowOpacity = 1.0f;
        
        self.separatorLineWidth = 1.0f;
    }
    return self;
}

#pragma mark - Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor colorWithWhite:0.1f alpha:1.0f];
    
    self.menuView = [UIView new];
    self.detailsView = [UIView new];
    
    self.menuView.autoresizingMask = (UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight);
    self.detailsView.autoresizingMask = (UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight);
    
    [self.view addSubview:self.detailsView];
    [self.view addSubview:self.menuView];
    
    [self addChildViewController:self.detailsViewController];
    [self addChildViewController:self.menuViewController];
    
    [self.detailsView addSubview:self.detailsViewController.view];
    [self.menuView addSubview:self.menuViewController.view];
}

- (void)viewDidLayoutSubviews
{
    [super viewDidLayoutSubviews];
    
    self.menuView.frame = CGRectMake(0.0f, 0.0f, self.menuWidth, self.view.bounds.size.height);
    self.detailsView.frame = CGRectMake(self.menuWidth + self.separatorLineWidth, 0.0f, (self.view.bounds.size.width - self.menuWidth - self.separatorLineWidth), self.view.bounds.size.height);
    
    self.menuViewController.view.frame = CGRectMake(0.0f, 0.0f, self.menuView.frame.size.width, self.menuView.frame.size.height);
    self.detailsViewController.view.frame = CGRectMake(0.0f, 0.0f, self.detailsView.frame.size.width, self.detailsView.frame.size.height);
}

#pragma mark - Actions

- (void)showModalViewController:(UIViewController *)viewController animated:(BOOL)animated
{
    if (!self.pushView) {
        self.pushView = [UIView new];
        self.pushView.backgroundColor = [UIColor clearColor];
        self.pushView.frame = CGRectMake(0.0f, self.view.bounds.size.height, self.view.bounds.size.width, self.view.bounds.size.height);
        [self.view addSubview:self.pushView];
        
        
        UIView *viewWithShadow = [UIView new];
        viewWithShadow.frame = CGRectMake(pushViewPaddingLeftRight, pushViewPaddingTopBottom, (self.view.bounds.size.width - (pushViewPaddingLeftRight * 2)), (self.view.bounds.size.height - (pushViewPaddingTopBottom * 2)));
        
        UIBezierPath *shadowPath = [UIBezierPath bezierPathWithRect:CGRectMake(0.0f, 0.0f, viewWithShadow.frame.size.width, viewWithShadow.frame.size.height)];
        viewWithShadow.layer.masksToBounds = NO;
        viewWithShadow.layer.shadowColor = [UIColor blackColor].CGColor;
        viewWithShadow.layer.shadowOffset = CGSizeMake(0.0f, 0.0f);
        viewWithShadow.layer.shadowOpacity = 1.0f;
        viewWithShadow.layer.shadowRadius = 7.0f;
        viewWithShadow.layer.shadowPath = shadowPath.CGPath;
        
        [self.pushView addSubview:viewWithShadow];
        
        UIView *viewWithRadius = [UIView new];
        viewWithRadius.frame = CGRectMake(0.0f, 0.0f, viewWithShadow.frame.size.width, viewWithShadow.frame.size.height);
        viewWithRadius.layer.masksToBounds = YES;
        viewWithRadius.layer.cornerRadius = 7.0f;
        [viewWithShadow addSubview:viewWithRadius];
        
        self.pushViewController = viewController;
        
        [self addChildViewController:viewController];
        [viewWithRadius addSubview:viewController.view];
        
        self.pushViewController.view.frame = CGRectMake(0.0f, 0.0f, viewWithRadius.frame.size.width, viewWithRadius.frame.size.height);
        
        if (animated) {
            [UIView beginAnimations:nil context:nil];
            [UIView setAnimationDuration:0.3f];
            
            self.pushView.frame = CGRectMake(0.0f, 0.0f, self.view.bounds.size.width, self.view.bounds.size.height);
            
            [UIView commitAnimations];
        } else {
            self.pushView.frame = CGRectMake(0.0f, 0.0f, self.view.bounds.size.width, self.view.bounds.size.height);
        }
    }
}

- (void)hideModalViewControllerAnimated:(BOOL)animated
{
    if (self.pushView) {
        if (animated) {
            [UIView beginAnimations:nil context:nil];
            [UIView setAnimationDuration:0.3f];
            [UIView setAnimationDelegate:self];
            [UIView setAnimationDidStopSelector:@selector(removePushView)];
            
            self.pushView.frame = CGRectMake(0.0f, self.view.bounds.size.height, self.view.bounds.size.width, self.view.bounds.size.height);
            
            [UIView commitAnimations];
        } else {
            [self removePushView];
        }
    }
}

- (void)removePushView
{
    [self.pushViewController.view removeFromSuperview];
    [self.pushViewController removeFromParentViewController];
    self.pushViewController = nil;
    
    [self.pushView removeFromSuperview];
    self.pushView = nil;
}

@end
