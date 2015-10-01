//
//  LPAnimationViewController.h
//  LP_LED_CUBE_8x8x8
//
//  Created by Luka Penger on 20/06/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPAnimation.h"
#import "LPSharedManager.h"
#import "LPToastView.h"
#import "LPCubeEffectCustomCellView.h"
#import "ProgressHUD.h"
#import "LPNewCustomEffectViewController.h"
#import "LPEditCustomEffectViewController.h"
#import "LPNewTextEffectViewController.h"
#import "LPPreview3DViewController.h"
#import "LPNewDefaultEffectViewController.h"
#import "LPSavedAnimationsListViewController.h"


@interface LPAnimationViewController : UIViewController <UITableViewDataSource, UITableViewDelegate, NSStreamDelegate, UIActionSheetDelegate, UIAlertViewDelegate>

@property (nonatomic, assign) BOOL saveBlockOnly;
@property (nonatomic, assign) BOOL backButton, closeButton;
@property (nonatomic, strong) IBOutlet UITableView *tableView;
@property (nonatomic, strong) LPAnimation *animation;
@property (nonatomic, copy)  void (^saveBlock)(LPAnimation *animation);
@property (nonatomic, strong) IBOutlet UIButton *deleteButton;
@property (nonatomic, strong) IBOutlet UIButton *preview3DButton;
@property (nonatomic, strong) IBOutlet UIButton *effectNewButton;
@property (nonatomic, strong) IBOutlet UIButton *saveAnimationButton;

- (IBAction)newEffectButtonClicked:(id)sender;
- (IBAction)saveAnimationButtonClicked:(id)sender;
- (IBAction)deleteButtonClicked:(id)sender;
- (IBAction)Preview3DButtonClicked:(id)sender;

@end
