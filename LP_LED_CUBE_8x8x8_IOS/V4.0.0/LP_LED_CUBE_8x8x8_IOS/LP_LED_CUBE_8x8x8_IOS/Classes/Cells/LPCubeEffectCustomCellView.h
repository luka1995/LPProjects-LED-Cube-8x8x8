//
//  LPCubeEffectCustomCellView.h
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 11/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MCSwipeTableViewCell/MCSwipeTableViewCell.h>


@interface LPCubeEffectCustomCellView : MCSwipeTableViewCell

@property (nonatomic, strong) UILabel *effectNameLabel;
@property (nonatomic, strong) UILabel *delayLabel;
@property (nonatomic, strong) UIView *line1;
@property (nonatomic, strong) UIView *mainView;

+ (LPCubeEffectCustomCellView *)cellFromNibNamed:(NSString *)nibName;

@end
