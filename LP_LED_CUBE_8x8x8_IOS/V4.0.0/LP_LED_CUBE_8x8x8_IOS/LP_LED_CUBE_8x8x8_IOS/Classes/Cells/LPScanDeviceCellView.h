//
//  LPScanDeviceCellView.h
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 02/12/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface LPScanDeviceCellView : UITableViewCell

@property (nonatomic, strong) IBOutlet UILabel *topLabel;
@property (nonatomic, strong) IBOutlet UILabel *bottomLabel;
@property (nonatomic, strong) IBOutlet UIView *mainView;

+ (LPScanDeviceCellView *)cellFromNibNamed:(NSString *)nibName;

@end
