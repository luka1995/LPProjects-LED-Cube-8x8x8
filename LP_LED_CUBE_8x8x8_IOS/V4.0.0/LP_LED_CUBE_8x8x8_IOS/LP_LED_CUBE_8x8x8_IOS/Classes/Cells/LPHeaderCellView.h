//
//  LPHeaderCellView.h
//
//  Created by Luka Penger on 10/04/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface LPHeaderCellView : UITableViewCell

@property (nonatomic, strong) IBOutlet UIView *topLineView;
@property (nonatomic, strong) IBOutlet UIView *mainView;
@property (nonatomic, strong) IBOutlet UIView *bottomLineView;
@property (nonatomic, strong) IBOutlet UILabel *rightLabel;
@property (nonatomic, strong) IBOutlet UIImageView *leftImageView;

+ (LPHeaderCellView *)cellFromNibNamed:(NSString *)nibName;

@end
