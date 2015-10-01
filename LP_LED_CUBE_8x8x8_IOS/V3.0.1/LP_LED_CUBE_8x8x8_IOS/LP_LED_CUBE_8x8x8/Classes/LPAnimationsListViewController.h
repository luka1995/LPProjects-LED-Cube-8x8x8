//
//  LPAnimationsListViewController.h
//  LP_LED_CUBE_8x8x8
//
//  Created by Luka Penger on 26/06/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPSharedManager.h"
#import <MBProgressHUD/MBProgressHUD.h>
#import <CocoaAsyncSocket/GCDAsyncSocket.h>
#import "LPAnimation.h"
#import "LPAnimationViewController.h"
#import "LPAnimationCellView.h"


@interface LPAnimationsListViewController : UIViewController <UITableViewDataSource, UITableViewDelegate, NSStreamDelegate, GCDAsyncSocketDelegate, UIAlertViewDelegate, UIActionSheetDelegate>
{
    int selectedRow;
}

@property (nonatomic, strong) IBOutlet UITableView *tableView;
@property (nonatomic, strong) NSMutableArray *objectsArray;

- (IBAction)stopAnimationButtonClicked:(id)sender;
- (IBAction)newAnimationButtonClicked:(id)sender;

@end
