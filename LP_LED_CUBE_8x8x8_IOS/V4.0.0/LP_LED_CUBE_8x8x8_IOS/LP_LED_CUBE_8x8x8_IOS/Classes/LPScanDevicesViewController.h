//
//  LPScanDevicesViewController.h
//  LP_LED_CUBE_8x8x8
//
//  Created by Luka Penger on 11/06/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <ifaddrs.h>
#import <arpa/inet.h>
#import <CocoaAsyncSocket/GCDAsyncUdpSocket.h>
#import <Reachability/Reachability.h>
#import "LPSharedManager.h"
#import "ProgressHUD.h"
#import <RMPickerViewController/RMPickerViewController.h>
#import "LPToastView.h"
#import "LPAnimationsListViewController.h"
#import <RNFrostedSidebar/RNFrostedSidebar.h>
#import "LPSavedAnimationsListViewController.h"
#import "LPSettingsViewController.h"
#import "LPScanDeviceCellView.h"


@interface LPScanDevicesViewController : UIViewController <UITableViewDataSource, UITableViewDelegate, GCDAsyncUdpSocketDelegate, NSStreamDelegate, UIAlertViewDelegate, RMPickerViewControllerDelegate, RNFrostedSidebarDelegate, UIActionSheetDelegate>

@property (nonatomic, strong) IBOutlet UITableView *tableView;
@property (nonatomic, strong) IBOutlet UIButton *selectIPButton;

- (IBAction)selectIPButtonClicked:(id)sender;

@end
