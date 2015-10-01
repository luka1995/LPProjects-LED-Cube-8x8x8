//
//  LPSettingsViewController.h
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 30/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPSharedManager.h"
#import "LPHeaderCellView.h"
#import "LPTextFieldCellView.h"
#import "LPSwitchCellView.h"
#import "LPToastView.h"
#import "ProgressHUD.h"
#import "LPDeviceSettings.h"
#include <arpa/inet.h>


@interface LPSettingsViewController : UIViewController <UITableViewDataSource, UITableViewDelegate, UITextFieldDelegate>

@property (nonatomic, assign) BOOL backButton, closeButton;
@property (nonatomic, strong) IBOutlet UITableView *tableView;
@property (nonatomic, strong) LPDeviceSettings *deviceSettings;
@property (nonatomic, copy)  void (^saveBlock)(LPDeviceSettings *deviceSettings);

@end
