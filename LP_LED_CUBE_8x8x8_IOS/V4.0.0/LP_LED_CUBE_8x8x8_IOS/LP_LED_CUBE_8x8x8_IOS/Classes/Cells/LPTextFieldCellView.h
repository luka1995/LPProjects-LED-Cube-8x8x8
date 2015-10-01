//
//  LPTextFieldCellView.h
//
//  Created by Luka Penger on 10/04/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPTextField.h"


@interface LPTextFieldCellView : UITableViewCell

@property (nonatomic, strong) IBOutlet UIView *mainView;
@property (nonatomic, strong) IBOutlet UIView *topLineView;
@property (nonatomic, strong) IBOutlet UIView *bottomLineView;
@property (nonatomic, strong) IBOutlet UILabel *leftLabel;
@property (nonatomic, strong) IBOutlet LPTextField *rightTextField;
@property (nonatomic, assign) BOOL enableHighlight;

+ (LPTextFieldCellView *)cellFromNibNamed:(NSString *)nibName;

@end
