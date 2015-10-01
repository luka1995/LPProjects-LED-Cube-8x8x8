//
//  LPAnimationCellView.h
//  LP_LED_CUBE_8x8x8
//
//  Created by Luka Penger on 29/06/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface LPAnimationCellView : UITableViewCell

@property (nonatomic, strong) UILabel *animationNameLabel;
@property (nonatomic, strong) UILabel *fileSizeLabel;
@property (nonatomic, strong) UILabel *countLabel;
@property (nonatomic, strong) UIView *line1, *line2;
@property (nonatomic, strong) UIView *mainView;

+ (LPAnimationCellView *)cellFromNibNamed:(NSString *)nibName;

@end
