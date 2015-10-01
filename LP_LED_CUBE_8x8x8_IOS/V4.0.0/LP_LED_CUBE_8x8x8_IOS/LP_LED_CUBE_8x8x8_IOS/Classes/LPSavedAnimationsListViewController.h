//
//  LPSavedAnimationsListViewController.h
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 12/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPSharedManager.h"
#import "LPAnimation.h"
#import "LPAnimationCellView.h"
#import "LPToastView.h"
#import "LPAnimationViewController.h"
#import <MessageUI/MessageUI.h>
#import <ifaddrs.h>
#import <arpa/inet.h>
#import <CocoaHTTPServer/HTTPServer.h>
#import "WEBServerConnection.h"


@interface LPSavedAnimationsListViewController : UIViewController <UITableViewDataSource, UITableViewDelegate, UIAlertViewDelegate, UIActionSheetDelegate, MFMailComposeViewControllerDelegate>

@property (nonatomic, assign) BOOL backButton, closeButton, canUpload, canAppend;
@property (nonatomic, strong) IBOutlet UITableView *tableView;
@property (nonatomic, copy) void (^appendBlock)(LPAnimation *animation);
@property (nonatomic, strong) IBOutlet UIButton *startStopWEBServerButton;

- (IBAction)deleteButtonClicked:(id)sender;
- (IBAction)startStopServerButtonClicked:(id)sender;

@end
