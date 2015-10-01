//
//  LPSplitViewController.h
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 26/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>


@protocol LPSplitViewControllerDelegate;

@interface LPSplitViewController : UIViewController

@property (nonatomic, assign) id<LPSplitViewControllerDelegate> delegate;

@property (nonatomic, strong) UIView *menuView;
@property (nonatomic, strong) UIView *detailsView;

@property (nonatomic, strong) UIViewController *menuViewController;
@property (nonatomic, strong) UIViewController *detailsViewController;

@property (nonatomic, assign) CGFloat menuWidth;

@property (nonatomic, assign) UIColor *menuViewShadowColor;
@property (nonatomic, assign) CGFloat menuViewShadowOpacity;
@property (nonatomic, assign) CGFloat menuViewShadowRadius;

@property (nonatomic, assign) CGFloat separatorLineWidth;

- (id)initWithMenuViewController:(UIViewController*)menuViewController detailsViewController:(UIViewController*)detailsViewController;
- (void)showModalViewController:(UIViewController *)viewController animated:(BOOL)animated;
- (void)hideModalViewControllerAnimated:(BOOL)animated;

@end
