//
//  LPAnimationsListViewController.m
//  LP_LED_CUBE_8x8x8
//
//  Created by Luka Penger on 26/06/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPAnimationsListViewController.h"


@interface LPAnimationsListViewController ()

@property (nonatomic, strong) GCDAsyncSocket *asyncSocket;
@property (nonatomic, strong) NSInputStream *inputStream;
@property (nonatomic, strong) MBProgressHUD *progressHUD;

@property (nonatomic, assign) int sRowIndex;
@property (nonatomic, strong) NSString *sFileName;

@property (nonatomic, assign) int whichReading;

@end


#define headerAnimationNameLeftPadding 6.0f
#define headerAnimationNameWidth 180.0f
#define headerLineWidth 1.0f

@implementation LPAnimationsListViewController

#pragma mark - Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.title = @"Animations";
    
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Refresh" style:UIBarButtonItemStyleBordered target:self action:@selector(loadAnimationsList)];
    
    self.tableView.separatorInset = UIEdgeInsetsMake(0.0f, 0.0f, 0.0f, 0.0f);
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    
    self.asyncSocket = [[GCDAsyncSocket alloc] initWithDelegate:self delegateQueue:dispatch_get_main_queue()];

    NSError *error = nil;
    if (![self.asyncSocket connectToHost:[[LPSharedManager sharedManager] selectedIP] onPort:[LPSharedManager TCPPort] withTimeout:5.0 error:&error])
    {
        NSLog(@"Error connecting: %@", error);
    } else {
        NSLog(@"Connecting...");
    }
}

- (void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];
    
    if ([self.asyncSocket isConnected]) {
        [self.asyncSocket disconnect];
    }
}

- (void)showLoadingAnimations
{
    if (!self.progressHUD) {
        self.progressHUD = [MBProgressHUD showHUDAddedTo:[UIApplication sharedApplication].delegate.window animated:YES];
        
        self.progressHUD.labelText = @"Loading...";
        self.progressHUD.labelFont = [UIFont boldSystemFontOfSize:14];
    }
}

- (void)showLoadingFile
{
    if (!self.progressHUD) {
        self.progressHUD = [MBProgressHUD showHUDAddedTo:[UIApplication sharedApplication].delegate.window animated:YES];
        
        self.progressHUD.labelText = @"Loading...";
        self.progressHUD.labelFont = [UIFont boldSystemFontOfSize:14];
    }
}

- (IBAction)stopAnimationButtonClicked:(id)sender
{
    [self stopAnimation];
}

- (IBAction)newAnimationButtonClicked:(id)sender
{
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"New animation" message:nil delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Next", nil];
    alertView.accessibilityIdentifier = @"newanimation";
    alertView.alertViewStyle = UIAlertViewStylePlainTextInput;
    [[alertView textFieldAtIndex:0] setPlaceholder:@"Enter animation name"];
    [alertView show];
}

#pragma mark - UITableViewDataSource

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 60.0f;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    return 26.0f;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [[self objectsArray] count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    LPAnimationCellView *cell = [LPAnimationCellView cellFromNibNamed:@"LPAnimationCellView"];

    NSDictionary *file = [self.objectsArray objectAtIndex:indexPath.row];
    
    unsigned long long sizeOrginal = [[file objectForKey:(id)kCFFTPResourceSize] unsignedLongLongValue];

    if (!cell.animationNameLabel) {
        cell.animationNameLabel = [[UILabel alloc] initWithFrame:CGRectMake(0.0f, 0.0f, headerAnimationNameWidth, cell.frame.size.height)];
        cell.animationNameLabel.backgroundColor = [UIColor clearColor];
        cell.animationNameLabel.text = [NSString stringWithFormat:@"  %@",[file objectForKey:(id)kCFFTPResourceName]];
        cell.animationNameLabel.font = [UIFont boldSystemFontOfSize:16.0f];
        cell.animationNameLabel.textColor = [UIColor blackColor];
        cell.animationNameLabel.textAlignment = NSTextAlignmentLeft;
        [cell.contentView addSubview:cell.animationNameLabel];
    }
    
    if (!cell.fileSizeLabel) {
        cell.fileSizeLabel = [[UILabel alloc] initWithFrame:CGRectMake(headerAnimationNameWidth, 0.0f, ((tableView.frame.size.width - headerAnimationNameWidth) /2), cell.frame.size.height)];
        cell.fileSizeLabel.backgroundColor = [UIColor clearColor];
        cell.fileSizeLabel.text = [[LPSharedManager sharedManager] fileSizeFormat:sizeOrginal];
        cell.fileSizeLabel.font = [UIFont boldSystemFontOfSize:13.0f];
        cell.fileSizeLabel.textColor = [UIColor blackColor];
        cell.fileSizeLabel.textAlignment = NSTextAlignmentCenter;
        [cell.contentView addSubview:cell.fileSizeLabel];
    }
    
    if (!cell.countLabel) {
        cell.countLabel = [[UILabel alloc] initWithFrame:CGRectMake(headerAnimationNameWidth + ((tableView.frame.size.width - headerAnimationNameWidth) /2), 0.0f, ((tableView.frame.size.width - headerAnimationNameWidth) /2), cell.frame.size.height)];
        cell.countLabel.backgroundColor = [UIColor clearColor];
        cell.countLabel.text = [NSString stringWithFormat:@"%d", (int)(sizeOrginal / [LPCubeEffect size])];
        cell.countLabel.font = [UIFont boldSystemFontOfSize:13.0f];
        cell.countLabel.textColor = [UIColor blackColor];
        cell.countLabel.textAlignment = NSTextAlignmentCenter;
        [cell.contentView addSubview:cell.countLabel];
    }
    
    if (!cell.line1) {
        cell.line1 = [[UILabel alloc] initWithFrame:CGRectMake(headerAnimationNameWidth, 0.0f, headerLineWidth, cell.frame.size.height)];
        cell.line1.backgroundColor = [UIColor lightGrayColor];
        [cell.contentView addSubview:cell.line1];
    }
    
    if (!cell.line2) {
        cell.line2 = [[UILabel alloc] initWithFrame:CGRectMake(headerAnimationNameWidth + ((tableView.frame.size.width - headerAnimationNameWidth) /2), 0.0f, headerLineWidth, cell.frame.size.height)];
        cell.line2.backgroundColor = [UIColor lightGrayColor];
        [cell.contentView addSubview:cell.line2];
    }
    
    cell.animationNameLabel.backgroundColor = [UIColor colorWithRed:(250.0/255.0) green:(180.0/255.0) blue:(120.0/255.0) alpha:0.5];
    cell.fileSizeLabel.backgroundColor = [UIColor colorWithRed:(200.0/255.0) green:(255.0/255.0) blue:(150.0/255.0) alpha:0.5];
    cell.countLabel.backgroundColor = [UIColor colorWithRed:(140.0/255.0) green:(255.0/255.0) blue:(240.0/255.0) alpha:0.5];

    cell.backgroundColor = cell.countLabel.backgroundColor;
    
    return cell;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    UIView *view = [[UIView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, tableView.frame.size.width, [self tableView:tableView heightForHeaderInSection:section])];
    [view setBackgroundColor:[UIColor lightGrayColor]];
    
    UILabel *animationNameLabel = [[UILabel alloc] initWithFrame:CGRectMake(headerAnimationNameLeftPadding, 0.0f, (headerAnimationNameWidth - headerAnimationNameLeftPadding), view.frame.size.height)];
    animationNameLabel.backgroundColor = [UIColor clearColor];
    animationNameLabel.text = @"Animation Name";
    animationNameLabel.font = [UIFont boldSystemFontOfSize:13.0f];
    animationNameLabel.textColor = [UIColor blackColor];
    animationNameLabel.textAlignment = NSTextAlignmentLeft;
    [view addSubview:animationNameLabel];
    
    UILabel *fileSizeLabel = [[UILabel alloc] initWithFrame:CGRectMake(headerAnimationNameWidth, 0.0f, ((tableView.frame.size.width - headerAnimationNameWidth) /2), view.frame.size.height)];
    fileSizeLabel.backgroundColor = [UIColor clearColor];
    fileSizeLabel.text = @"File Size";
    fileSizeLabel.font = [UIFont boldSystemFontOfSize:13.0f];
    fileSizeLabel.textColor = [UIColor blackColor];
    fileSizeLabel.textAlignment = NSTextAlignmentCenter;
    [view addSubview:fileSizeLabel];
    
    UILabel *countLabel = [[UILabel alloc] initWithFrame:CGRectMake(headerAnimationNameWidth + ((tableView.frame.size.width - headerAnimationNameWidth) /2), 0.0f, ((tableView.frame.size.width - headerAnimationNameWidth) /2), view.frame.size.height)];
    countLabel.backgroundColor = [UIColor clearColor];
    countLabel.text = @"Count";
    countLabel.font = [UIFont boldSystemFontOfSize:13.0f];
    countLabel.textColor = [UIColor blackColor];
    countLabel.textAlignment = NSTextAlignmentCenter;
    [view addSubview:countLabel];
    
    UIView *line1 = [[UIView alloc] initWithFrame:CGRectMake(headerAnimationNameWidth, 0.0f, headerLineWidth, view.frame.size.height)];
    line1.backgroundColor = [UIColor grayColor];
    [view addSubview:line1];
    
    UIView *line2 = [[UIView alloc] initWithFrame:CGRectMake(headerAnimationNameWidth + ((tableView.frame.size.width - headerAnimationNameWidth) /2), 0.0f, headerLineWidth, view.frame.size.height)];
    line2.backgroundColor = [UIColor grayColor];
    [view addSubview:line2];
    
    return view;
}

#pragma mark - UITableViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [self.tableView deselectRowAtIndexPath:indexPath animated:NO];
    
    selectedRow = indexPath.row;

    self.sFileName = [[self.objectsArray objectAtIndex:selectedRow] objectForKey:(id)kCFFTPResourceName];
    
    UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:nil delegate:self cancelButtonTitle:@"Cancel" destructiveButtonTitle:@"Delete Animation" otherButtonTitles:@"Start Animation", @"Edit Animation", nil];
    [actionSheet showInView:self.view];
}

#pragma mark - UIActionSheetDelegate

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 0) {
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"Warning" message:@"Are you sure you want to delete animation?" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Delete", nil];
        alertView.accessibilityIdentifier = @"deletefile";
        [alertView show];
    } else if (buttonIndex == 1) {
        [self startAnimation:self.sFileName];
    } else if (buttonIndex == 2) {
        self.sFileName = [[self.objectsArray objectAtIndex:selectedRow] objectForKey:(id)kCFFTPResourceName];
        
        self.whichReading = 1;
        
        NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:@"ftp://%@:%@@%@/%@", [[LPSharedManager sharedManager] ftpUsername], [[LPSharedManager sharedManager] ftpPassword], [[LPSharedManager sharedManager] selectedIP], self.sFileName]];
        
        CFReadStreamRef stream = CFReadStreamCreateWithFTPURL(NULL, (__bridge CFURLRef) url);
        
        self.inputStream = (__bridge_transfer NSInputStream *)stream;
        [self.inputStream setDelegate:self];
        [self.inputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        [self.inputStream open];
        
        [self showLoadingFile];
    }
}

#pragma mark - UIAlertViewDelegate

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if ([alertView.accessibilityIdentifier isEqualToString:@"deletefile"]) {
        if (buttonIndex == 1) {
            NSURL *url = [[NSURL alloc] initWithString:[NSString stringWithFormat:@"ftp://%@:%@@%@/%@", [[LPSharedManager sharedManager] ftpUsername], [[LPSharedManager sharedManager] ftpPassword], [[LPSharedManager sharedManager] selectedIP], self.sFileName]];
            Boolean status = CFURLDestroyResource((__bridge CFURLRef)url, nil);
            
            if (status) {
                NSLog(@"deletion success");
                
                [self.objectsArray removeObjectAtIndex:self.sRowIndex];
                [self.tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:[NSIndexPath indexPathForRow:self.sRowIndex inSection:0]] withRowAnimation:UITableViewRowAnimationFade];
            } else {
                NSLog(@"deletion failed");
            }
        }
    } else if ([alertView.accessibilityIdentifier isEqualToString:@"newanimation"]) {
        if (buttonIndex == 1) {
            if ([[[alertView textFieldAtIndex:0] text] length] > 0) {
                self.asyncSocket.delegate = nil;
                self.asyncSocket = nil;
                
                LPAnimation *animation = [LPAnimation new];
                animation.fileName = [NSString stringWithFormat:@"%@.ani", [[alertView textFieldAtIndex:0] text]];
                
                LPAnimationViewController *animationViewController = [[LPAnimationViewController alloc] initWithNibName:@"LPAnimationViewController_iPhone" bundle:nil];
                animationViewController.animation = animation;
                
                [animationViewController setSaveBlock:^(LPAnimation *animationSave) {
                    NSMutableDictionary *newFile = [NSMutableDictionary new];
                    [newFile setObject:animationSave.fileName forKey:(id)kCFFTPResourceName];
                    [newFile setObject:[NSNumber numberWithInt:[animationSave getBytesLength]] forKey:(id)kCFFTPResourceSize];
                    
                    if (![self.objectsArray containsObject:newFile]) {
                        [self.objectsArray addObject:newFile];
                        
                        [self.tableView insertRowsAtIndexPaths:[NSArray arrayWithObject:[NSIndexPath indexPathForRow:([self.objectsArray count] - 1) inSection:0]] withRowAnimation:UITableViewRowAnimationAutomatic];
                        [self.tableView scrollToRowAtIndexPath:[NSIndexPath indexPathForRow:([self.objectsArray count] - 1) inSection:0] atScrollPosition:UITableViewScrollPositionBottom animated:YES];
                    }
                }];
                
                [self.navigationController pushViewController:animationViewController animated:YES];
            }
        }
    }
}

#pragma mark - Load Animations List

- (void)loadAnimationsList
{
    self.whichReading = 0;
    
    NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:@"ftp://%@:%@@%@", [[LPSharedManager sharedManager] ftpUsername], [[LPSharedManager sharedManager] ftpPassword], [[LPSharedManager sharedManager] selectedIP]]];
    
    CFReadStreamRef stream = CFReadStreamCreateWithFTPURL(NULL, (__bridge CFURLRef) url);
    
    self.inputStream = (__bridge_transfer NSInputStream *)stream;
    [self.inputStream setDelegate:self];
    [self.inputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    [self.inputStream open];

    [self showLoadingAnimations];
}

#pragma mark - NSStreamDelegate

- (void)stream:(NSStream *)theStream handleEvent:(NSStreamEvent)streamEvent
{
    switch (streamEvent) {
        case NSStreamEventOpenCompleted:
        {
            NSLog(@"Stream opened");
            break;
        }
        case NSStreamEventHasBytesAvailable:
        {
            if (theStream == self.inputStream) {
                uint8_t buffer[100000];
                int len;
                
                while ([self.inputStream hasBytesAvailable]) {
                    len = [self.inputStream read:buffer maxLength:sizeof(buffer)];
                    
                    if (self.whichReading == 0) { // List
                        NSLog(@"List readed");
                        
                        if (len > 0) {
                            NSString *output = [[[NSString alloc] initWithBytes:buffer length:len encoding:NSASCIIStringEncoding] stringByReplacingOccurrencesOfString:@"\n" withString:@" "];
                            
                            if (output) {
                                NSMutableArray *list = [NSMutableArray new];
                                NSMutableArray *listFin = [NSMutableArray new];
                                
                                NSArray *array = [output componentsSeparatedByString:@" "];
                                
                                [array enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
                                    if (![obj isEqualToString:@""]) {
                                        [list addObject:[obj stringByTrimmingCharactersInSet: [NSCharacterSet whitespaceAndNewlineCharacterSet]]];
                                    }
                                }];
                                
                                for (int i=0; i<[list count]; i=i+4) {
                                    if ([[list objectAtIndex:3+i] hasSuffix:@".ani"]) {
                                        NSMutableDictionary *dic = [NSMutableDictionary new];
                                        
                                        [dic setObject:@([[list objectAtIndex:2+i] longLongValue]) forKey:(id)kCFFTPResourceSize];
                                        [dic setObject:[list objectAtIndex:3+i] forKey:(id)kCFFTPResourceName];
                                        
                                        [listFin addObject:dic];
                                    }
                                }
                                
                                self.objectsArray = listFin;
                                [self.tableView reloadData];
                            }
                        }
                    } else if (self.whichReading == 1) { // File
                        NSLog(@"File readed - length: %d", len);
                        
                        if (len > 0) {
                            self.asyncSocket.delegate = nil;
                            self.asyncSocket = nil;
                            
                            LPAnimation *animation = [LPAnimation animationWithBuffer:buffer length:len];
                            animation.fileName = self.sFileName;
                            
                            LPAnimationViewController *animationViewController = [[LPAnimationViewController alloc] initWithNibName:@"LPAnimationViewController_iPhone" bundle:nil];
                            animationViewController.animation = animation;
                            
                            __block int saveSelectedRow = selectedRow;
                            
                            [animationViewController setSaveBlock:^(LPAnimation *animationSave) {
                                NSMutableDictionary *updateFile = [NSMutableDictionary new];
                                [updateFile setObject:animationSave.fileName forKey:(id)kCFFTPResourceName];
                                [updateFile setObject:[NSNumber numberWithInt:[animationSave getBytesLength]] forKey:(id)kCFFTPResourceSize];

                                [self.objectsArray replaceObjectAtIndex:saveSelectedRow withObject:updateFile];
                                [self.tableView reloadData];
                            }];
                            
                            [self.navigationController pushViewController:animationViewController animated:YES];
                            
                            [theStream close];
                            [theStream removeFromRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
                            theStream = nil;
                        } else {
                            UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"Error" message:@"Animation file is empty" delegate:nil cancelButtonTitle:@"Cancel" otherButtonTitles:nil, nil];
                            [alertView show];
                        }
                    }
                }
            }
            break;
        }
        case NSStreamEventErrorOccurred:
        {
            NSLog(@"Can not connect to the host!");
            
            if (self.whichReading == 1) { // File
                UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"Error" message:@"Can not load animation file! Try again" delegate:nil cancelButtonTitle:@"Cancel" otherButtonTitles:nil, nil];
                [alertView show];
            }
            
            break;
        }
        case NSStreamEventEndEncountered:
        {
            [theStream close];
            [theStream removeFromRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
            theStream = nil;
            break;
        }
        default:
        {
            NSLog(@"Unknown event");
            break;
        }
    }
    
    [self.progressHUD hide:YES];
    [self.progressHUD removeFromSuperview];
    self.progressHUD = nil;
}

#pragma mark - GCDAsyncSocketDelegate

- (void)socket:(GCDAsyncSocket *)sock didConnectToHost:(NSString *)host port:(uint16_t)port
{
    NSLog(@"Socket - Did connect");
}

- (void)socketDidDisconnect:(GCDAsyncSocket *)sock withError:(NSError *)err
{
    NSLog(@"Socket - Did disconnect");
    
    [self.navigationController popToRootViewControllerAnimated:YES];
}

#pragma mark - TCP Write Commands

- (void)startAnimation:(NSString *)animationFileName
{
    if ([self.asyncSocket isConnected] && [animationFileName length] > 0) {
        int size = 7 + [animationFileName length];
        
        unsigned char buffer[size];
        
        buffer[0] = 0xEE;
        buffer[1] = 0xEE;
        buffer[2] = 0xCC;
        buffer[3] = (char)(size / 255);
        buffer[4] = (char)(size - (buffer[3] * 255));
        buffer[5] = 0x10;
        
        for (int i=0; i<[animationFileName length]; i++) {
            buffer[6 + i] = [animationFileName characterAtIndex:i];
        }
        
        buffer[size - 1] = calcCRC(buffer, size - 1);
        
        NSData *data = [NSData dataWithBytes:buffer length:size];
        

        NSMutableString *hex = [NSMutableString stringWithCapacity:size];
        for (int i=0; i < size; i++) {
            [hex appendFormat:@"%02X", buffer[i]];
            if (i != (size -1)) [hex appendString:@"-"];
        }
        NSLog(@"Bytes sent: %@", hex);

        [self.asyncSocket writeData:data withTimeout:5.0 tag:0];
    }
}

- (void)stopAnimation
{
    if ([self.asyncSocket isConnected]) {
        int size = 7;;
        
        unsigned char buffer[size];
        
        buffer[0] = 0xEE;
        buffer[1] = 0xEE;
        buffer[2] = 0xCC;
        buffer[3] = (char)(size / 255);
        buffer[4] = (char)(size - (buffer[3] * 255));
        buffer[5] = 0x11;
        buffer[size - 1] = calcCRC(buffer, size - 1);
        
        NSData *data = [NSData dataWithBytes:buffer length:size];

        NSMutableString *hex = [NSMutableString stringWithCapacity:size];
        for (int i=0; i < size; i++) {
            [hex appendFormat:@"%02X", buffer[i]];
            if (i != (size -1)) [hex appendString:@"-"];
        }
        NSLog(@"Bytes sent: %@", hex);
        
        [self.asyncSocket writeData:data withTimeout:5.0 tag:0];
    }
}

@end
