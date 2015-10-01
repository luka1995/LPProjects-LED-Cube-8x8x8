//
//  LPScanViewController.h
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
#import <MBProgressHUD/MBProgressHUD.h>
#import "LPAnimationsListViewController.h"
#import <RMPickerViewController/RMPickerViewController.h>


@interface LPScanViewController : UIViewController <UITableViewDataSource, UITableViewDelegate, GCDAsyncUdpSocketDelegate, NSStreamDelegate, UIAlertViewDelegate, RMPickerViewControllerDelegate>

@property (nonatomic, strong) IBOutlet UITableView *tableView;
@property (nonatomic, strong) IBOutlet UIButton *selectIPButton;

- (IBAction)selectIPButtonClicked:(id)sender;

@end
