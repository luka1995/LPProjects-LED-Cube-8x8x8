//
//  LPSwitchCellView.h
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 01/12/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPSwitch.h"


@interface LPSwitchCellView : UITableViewCell

@property (nonatomic, strong) IBOutlet UIView *mainView;
@property (nonatomic, strong) IBOutlet UIView *bottomLineView;
@property (nonatomic, strong) IBOutlet LPSwitch *rightSwitch;
@property (nonatomic, strong) IBOutlet UILabel *leftLabel;

+ (LPSwitchCellView *)cellFromNibNamed:(NSString *)nibName;

@end
