//
//  LPAnimationViewController.h
//  LP_LED_CUBE_8x8x8
//
//  Created by Luka Penger on 20/06/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPAnimation.h"
#import "LPCubeEffectCellView.h"
#import "LPSharedManager.h"
#import <MBProgressHUD/MBProgressHUD.h>
#import "LPNewEffectViewController.h"
#import "LPEditEffectViewController.h"


@interface LPAnimationViewController : UIViewController <UITableViewDataSource, UITableViewDelegate, NSStreamDelegate, UIActionSheetDelegate, UIAlertViewDelegate>
{
    int selectedRow;
}

@property (nonatomic, strong) IBOutlet UITableView *tableView;
@property (nonatomic, strong) LPAnimation *animation;

@property (nonatomic, copy)  void (^saveBlock)(LPAnimation *animation);

- (IBAction)addEffectButtonClicked:(id)sender;
- (IBAction)saveAnimationButtonClicked:(id)sender;
- (IBAction)deleteButtonClicked:(id)sender;

@end
