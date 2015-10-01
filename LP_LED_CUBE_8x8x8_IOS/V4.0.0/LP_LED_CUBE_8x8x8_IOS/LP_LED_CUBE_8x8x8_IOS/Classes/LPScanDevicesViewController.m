//
//  LPScanDevicesViewController.m
//  LP_LED_CUBE_8x8x8
//
//  Created by Luka Penger on 11/06/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPScanDevicesViewController.h"


#define DEVICE_FILE_NAME            @"device.settings"


@interface LPScanDevicesViewController ()

@property (nonatomic, strong) GCDAsyncUdpSocket *udpSocket;
@property (nonatomic, strong) NSMutableArray *objectsArray;
@property (nonatomic, assign) BOOL udpServerIsRuning;
@property (nonatomic, strong) NSInputStream *inputStream;
@property (nonatomic, assign) int inputStreamFunction;
@property (nonatomic, strong) NSMutableArray *arrayIP;
@property (nonatomic, strong) UIView *shadowView;
@property (nonatomic, assign) int selectedRow;
@property (nonatomic, strong) NSTimer *connectionTimeoutTimer;
@property (nonatomic, strong) NSMutableData *mutableBuffer;

@end


@implementation LPScanDevicesViewController

#pragma mark - Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.title = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ScanDevicesViewTitle"];
    
    self.tableView.separatorInset = UIEdgeInsetsMake(0.0f, 0.0f, 0.0f, 0.0f);
    
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"HomeIcon"] style:UIBarButtonItemStyleBordered target:self action:@selector(homeButtonClicked)];

    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"RefreshIcon"] style:UIBarButtonItemStyleBordered target:self action:@selector(refreshButtonClicked)];

    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationDidEnterBackground) name:UIApplicationDidEnterBackgroundNotification object:NULL];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationDidBecomeActive) name:UIApplicationDidBecomeActiveNotification object:NULL];
    
    [self.selectIPButton setTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ConnectToOtherDeviceButtonTitle"] forState:UIControlStateNormal];
    
    self.arrayIP = [NSMutableArray new];
    for (int a=0; a<256; a++) {
        [self.arrayIP addObject:[NSString stringWithFormat:@"%d", a]];
    }
    
    [self startUDPStart];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    
    self.shadowView = [[UIView alloc] initWithFrame:self.navigationController.view.frame];
    self.shadowView.backgroundColor = [UIColor blackColor];
    self.shadowView.alpha = 0.0f;
    [self.navigationController.view addSubview:_shadowView];
    
    [self scanForDevices];
}

- (GCDAsyncUdpSocket *)udpSocket
{
    if (!_udpSocket) {
        _udpSocket = [[GCDAsyncUdpSocket alloc] initWithDelegate:self delegateQueue:dispatch_get_main_queue()];
    }
    
    return _udpSocket;
}

- (NSMutableArray *)objectsArray
{
    if (!_objectsArray) {
        _objectsArray = [NSMutableArray new];
    }

    return _objectsArray;
}

- (void)handleConnectionTimeout:(NSTimer *)timer
{
    if (self.inputStream) {
        [self.inputStream close];
        [self.inputStream removeFromRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        self.inputStream = nil;
        
        [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"CanNotConnectToHostToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
        
        [ProgressHUD dismiss];
    }
}

- (void)applicationDidEnterBackground
{
    [self stopUDPServer];
}

- (void)applicationDidBecomeActive
{
    [self startUDPStart];
}

- (void)startUDPStart
{
    if (!self.udpServerIsRuning) {
        NSError *error = nil;
        
        if (![self.udpSocket bindToPort:[LPSharedManager UDPPort] error:&error]) {
            if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"CanNotConnectToHostToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
            } else {
                [LPToastView toastInView:self.view withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"CanNotConnectToHostToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
            }
            
            NSLog(@"Error starting server (bind): %@", error);
            
            return;
        }
        
        if (![self.udpSocket beginReceiving:&error]) {
            [self.udpSocket close];
            
            if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"CanNotConnectToHostToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
            } else {
                [LPToastView toastInView:self.view withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"CanNotConnectToHostToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
            }
            
            NSLog(@"Error starting server (recv): %@", error);
            
            return;
        }
        
        NSLog(@"UDP server started on port %hu", [self.udpSocket localPort]);
        
        [self.udpSocket enableBroadcast:YES error:nil];
        
        self.udpServerIsRuning = YES;
    }
}

- (void)stopUDPServer
{
    if (self.udpServerIsRuning) {
        [self.udpSocket close];
        self.udpSocket = nil;
        
        self.udpServerIsRuning = NO;
    }
}

#pragma mark - Actions

- (void)homeButtonClicked
{
    NSArray *images = @[
                        [UIImage imageNamed:@"FolderIcon"],
                        [UIImage imageNamed:@"ShareIcon"],
                        [UIImage imageNamed:@"InfoIcon"]
                        ];
    
    RNFrostedSidebar *frostedSidebar = [[RNFrostedSidebar alloc] initWithImages:images selectedIndices:[NSIndexSet indexSetWithIndex:([images count] - 1)] borderColors:[NSArray arrayWithObjects:[UIColor clearColor],[UIColor clearColor], [UIColor colorWithRed:(20.0/255.0) green:(180.0/255.0) blue:(210.0/255.0) alpha:1.0], nil]];
    frostedSidebar.delegate = self;
    [frostedSidebar show];
}

- (void)refreshButtonClicked
{
    [self scanForDevices];
}

- (void)scanForDevices
{
    [self.objectsArray removeAllObjects];
    
    [self.tableView reloadData];

    unsigned char buffer[7];
    
    buffer[0] = 0xEE;   // start byte
    buffer[1] = 0xEE;   // start byte
    buffer[2] = 0xCC;   // start byte
    buffer[3] = 0x00;
    buffer[4] = (char)sizeof(buffer);
    buffer[5] = 0x00;   // function
    buffer[(sizeof(buffer)-1)] = (unsigned char)calcCRC(buffer, ((int)sizeof(buffer)-1));
    
    NSString *ip = @"255.255.255.255"; // BROADCAST UDP
    
    [self.udpSocket bindToPort:[LPSharedManager UDPPort] error:nil];
    
    [self.udpSocket sendData:[NSData dataWithBytes:buffer length:sizeof(buffer)] toHost:ip port:[LPSharedManager UDPPort] withTimeout:-1 tag:0];
}

- (IBAction)selectIPButtonClicked:(id)sender
{
    [RMPickerViewController setLocalizedTitleForSelectButton:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetConnectButton"]];
    [RMPickerViewController setLocalizedTitleForCancelButton:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetCancelButton"]];
    
    RMPickerViewController *pickerVC = [RMPickerViewController pickerController];
    pickerVC.delegate = self;
    
    if (![[self getIPAddress] isEqualToString:@"error"]) {
        NSArray *array = [[self getIPAddress] componentsSeparatedByString:@"."];
        if ([array count] == 4) {
            [pickerVC.picker selectRow:[[array objectAtIndex:0] intValue] inComponent:0 animated:NO];
            [pickerVC.picker selectRow:[[array objectAtIndex:1] intValue] inComponent:1 animated:NO];
            [pickerVC.picker selectRow:[[array objectAtIndex:2] intValue] inComponent:2 animated:NO];
            [pickerVC.picker selectRow:[[array objectAtIndex:3] intValue] inComponent:3 animated:NO];
        }
    }
    
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        [pickerVC showWithSelectionHandler:nil andCancelHandler:nil];
    } else {
        [pickerVC showFromViewController:self];
    }
}

#pragma mark - UITableViewDataSource

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 60.0f;
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
    LPScanDeviceCellView *cell = [LPScanDeviceCellView cellFromNibNamed:@"LPScanDeviceCellView"];
    
    cell.topLabel.text = [[[self objectsArray] objectAtIndex:indexPath.row] objectAtIndex:1];
    
    if (cell.topLabel.text && cell.topLabel.text.length > 0) {
        cell.bottomLabel.text = [[[self objectsArray] objectAtIndex:indexPath.row] objectAtIndex:0];
    } else {
        cell.topLabel.text = [[[self objectsArray] objectAtIndex:indexPath.row] objectAtIndex:0];
        cell.topLabel.frame = CGRectMake(0.0f, 0.0f, cell.frame.size.width, cell.frame.size.height);
        cell.bottomLabel.hidden = YES;
    }
    
    return cell;
}

#pragma mark - UITableViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [self.tableView deselectRowAtIndexPath:indexPath animated:NO];
    
    self.selectedRow = (int)indexPath.row;
    
    NSString *selectedIP = [[self.objectsArray objectAtIndex:self.selectedRow] objectAtIndex:0];
    
    [[LPSharedManager sharedManager] setSelectedIP:selectedIP];
    
    UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:nil delegate:self cancelButtonTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetCancelButton"] destructiveButtonTitle:nil otherButtonTitles:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetAnimationsListButton"], [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetDeviceSettingsButton"], nil];
    actionSheet.accessibilityIdentifier = @"device_options";
    [actionSheet showInView:self.view];
}

#pragma mark - UIActionSheetDelegate

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if ([actionSheet.accessibilityIdentifier isEqualToString:@"device_options"]) {
        switch (buttonIndex) {
            case 0:
            {
                [self connectToHost:[[LPSharedManager sharedManager] selectedIP] username:[LPSharedManager ftpUsername] password:[LPSharedManager ftpPassword]];
                break;
            }
            case 1:
            {
                self.inputStreamFunction = 1;
                
                NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:@"ftp://%@:%@@%@/%@", [LPSharedManager ftpUsername], [LPSharedManager ftpPassword], [[LPSharedManager sharedManager] selectedIP], DEVICE_FILE_NAME]];
                
                CFReadStreamRef stream = CFReadStreamCreateWithFTPURL(NULL, (__bridge CFURLRef) url);
                
                self.inputStream = (__bridge_transfer NSInputStream *)stream;
                [self.inputStream setDelegate:self];
                [self.inputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
                [self.inputStream open];
                
                self.connectionTimeoutTimer = [NSTimer scheduledTimerWithTimeInterval:4.0 target:self selector:@selector(handleConnectionTimeout:) userInfo:nil repeats:NO];
                
                [ProgressHUD show:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"LoadingDeviceSettingsProgressHUDTitle"] Interaction:NO];
                
                break;
            }
        }
    }
}

#pragma mark - GCDAsyncUdpSocketDelegate

- (void)udpSocket:(GCDAsyncUdpSocket *)socket didReceiveData:(NSData *)data fromAddress:(NSData *)address withFilterContext:(id)filterContext
{
    [self.udpSocket bindToPort:[LPSharedManager UDPPort] error:nil];

    NSString *host = [GCDAsyncUdpSocket hostFromAddress:address];
    
    if (![host isEqualToString:[self getIPAddress]] && ![host hasPrefix:@"::ffff:"]) {
        char *bytes = (char *)[data bytes];
        
        NSString *deviceName = [[NSString alloc] initWithBytes:(bytes + 10) length:([data length] - 11) encoding:NSASCIIStringEncoding];
        
        if (!deviceName) deviceName = @"";
        
        NSMutableArray *array = [NSMutableArray new];
        [array addObject:host];
        [array addObject:deviceName];
        
        [self.objectsArray addObject:array];
        
        [self.tableView reloadData];
    }
}

#pragma mark - Help

- (NSString *)getIPAddress
{
    NSString *address = @"error";
    struct ifaddrs *interfaces = NULL;
    struct ifaddrs *temp_addr = NULL;
    int success = 0;
    // retrieve the current interfaces - returns 0 on success
    success = getifaddrs(&interfaces);
    if (success == 0) {
        // Loop through linked list of interfaces
        temp_addr = interfaces;
        while(temp_addr != NULL) {
            if(temp_addr->ifa_addr->sa_family == AF_INET) {
                // Check if interface is en0 which is the wifi connection on the iPhone
                if([[NSString stringWithUTF8String:temp_addr->ifa_name] isEqualToString:@"en0"]) {
                    // Get NSString from C String
                    address = [NSString stringWithUTF8String:inet_ntoa(((struct sockaddr_in *)temp_addr->ifa_addr)->sin_addr)];
                }
            }
            temp_addr = temp_addr->ifa_next;
        }
    }
    // Free memory
    freeifaddrs(interfaces);
    return address;
}

#pragma mark - RMPickerViewControllerDatasource

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView
{
    return 4;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent :(NSInteger)component
{
    return [self.arrayIP count];
}

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component
{
    return [self.arrayIP objectAtIndex:row];
}

#pragma mark - RMPickerViewControllerDelegate

- (void)pickerViewController:(RMPickerViewController *)vc didSelectRows:(NSArray *)selectedRows
{
    NSLog(@"Successfully selected rows: %@", selectedRows);
    
    [vc dismiss]; // This fix bug
    
    NSString *selectedIP = [NSString stringWithFormat:@"%@.%@.%@.%@", [selectedRows objectAtIndex:0], [selectedRows objectAtIndex:1], [selectedRows objectAtIndex:2], [selectedRows objectAtIndex:3]];
    
    [[LPSharedManager sharedManager] setSelectedIP:selectedIP];
    
    [self connectToHost:[[LPSharedManager sharedManager] selectedIP] username:[LPSharedManager ftpUsername] password:[LPSharedManager ftpPassword]];
}

- (void)pickerViewControllerDidCancel:(RMPickerViewController *)vc
{
    NSLog(@"Selection was canceled");
}

#pragma mark - Connect

- (void)connectToHost:(NSString *)host username:(NSString *)username password:(NSString *)password
{
    [ProgressHUD show:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ProgressHUDLoadingTitle"] Interaction:NO];
    
    self.inputStreamFunction = 0;
    
    NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:@"ftp://%@:%@@%@", username, password, host]];
    
    CFReadStreamRef stream = CFReadStreamCreateWithFTPURL(NULL, (__bridge CFURLRef) url);
    
    self.inputStream = (__bridge_transfer NSInputStream *)stream;
    [self.inputStream setDelegate:self];
    [self.inputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    [self.inputStream open];
    
    self.connectionTimeoutTimer = [NSTimer scheduledTimerWithTimeInterval:4.0 target:self selector:@selector(handleConnectionTimeout:) userInfo:nil repeats:NO];
}

#pragma mark - NSStreamDelegate

- (void)stream:(NSStream *)theStream handleEvent:(NSStreamEvent)streamEvent
{
    switch (streamEvent) {
        case NSStreamEventOpenCompleted:
        {
            NSLog(@"Stream opened");
            
            self.mutableBuffer = [NSMutableData new];
            
            break;
        }
        case NSStreamEventHasBytesAvailable:
        {
            uint8_t buffer[1024];
            int len;
            
            if ([self.inputStream hasBytesAvailable]) {
                len = (int)[self.inputStream read:buffer maxLength:sizeof(buffer)];
                
                [self.mutableBuffer appendBytes:buffer length:len];
            }
            break;
        }
        case NSStreamEventEndEncountered:
        {
            if (self.inputStreamFunction == 0) {
                NSString *output = [[[NSString alloc] initWithBytes:[self.mutableBuffer bytes] length:[self.mutableBuffer length] encoding:NSASCIIStringEncoding] stringByReplacingOccurrencesOfString:@"\n" withString:@" "];
                
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
                    
                    LPAnimationsListViewController *animationsListViewController = [[LPAnimationsListViewController alloc] initWithNibName:@"LPAnimationsListViewController" bundle:nil];
                    animationsListViewController.objectsArray = listFin;
                    
                    [self.navigationController pushViewController:animationsListViewController animated:YES];
                }
            } else if (self.inputStreamFunction == 1) {
                LPSettingsViewController *settingsViewController = [[LPSettingsViewController alloc] initWithNibName:@"LPSettingsViewController" bundle:nil];
                settingsViewController.closeButton = YES;
                
                NSString *output = [[NSString alloc] initWithBytes:(uint8_t *)[self.mutableBuffer bytes] length:[self.mutableBuffer length] encoding:NSASCIIStringEncoding];
                LPDeviceSettings *deviceSettings = [LPDeviceSettings deviceSettingsWithString:output];
                settingsViewController.deviceSettings = deviceSettings;
                
                UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:settingsViewController];
                
                if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                    [self presentViewController:navigationController animated:YES completion:nil];
                } else {
                    [[[LPSharedManager sharedManager] splitViewControllerIpad] showModalViewController:navigationController animated:YES];
                }
            }
            
            [ProgressHUD dismiss];
            
            if (self.inputStream) {
                [self.inputStream close];
                [self.inputStream removeFromRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
                self.inputStream = nil;
            }
            
            break;
        }
        default:
        {
            if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"CanNotConnectToHostToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
            } else {
                [LPToastView toastInView:self.view withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"CanNotConnectToHostToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
            }
            
            [self.inputStream close];
            [self.inputStream removeFromRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
            self.inputStream = nil;

            [ProgressHUD dismiss];

            break;
        }
    }
}

#pragma mark - RMPickerViewControllerDelegate

- (void)sidebar:(RNFrostedSidebar *)sidebar didTapItemAtIndex:(NSUInteger)index
{
    [sidebar dismissAnimated:YES];
    
    switch (index) {
        case 0:
        {
            LPSavedAnimationsListViewController *savedAnimationsListViewController =[[LPSavedAnimationsListViewController alloc] initWithNibName:@"LPSavedAnimationsListViewController" bundle:nil];
            
            if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                savedAnimationsListViewController.closeButton = YES;
                UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:savedAnimationsListViewController];
                [self presentViewController:navigationController animated:YES completion:nil];
            } else {
                savedAnimationsListViewController.backButton = YES;
                [self.navigationController pushViewController:savedAnimationsListViewController animated:YES];
            }
            break;
        }
        case 1:
        {
            NSMutableArray *shareItems = [NSMutableArray new];
            
            [shareItems addObject:@"LPProjects LED Cube 8x8x8"];
            [shareItems addObject:[NSURL URLWithString:@"http://led-cube.eu"]];

            UIActivityViewController *shareController = [[UIActivityViewController alloc] initWithActivityItems:shareItems applicationActivities:nil];

            if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                [self presentViewController:shareController animated:YES completion:nil];
            } else {
                CGRect cellRect = CGRectMake(([[[[UIApplication sharedApplication] windows] objectAtIndex:0] frame].size.width/2), [[[[UIApplication sharedApplication] windows] objectAtIndex:0] frame].size.height-20, 1, 1);
                
                if ([shareController respondsToSelector:@selector(popoverPresentationController)]) {
                    UIPopoverPresentationController *presentationController = [shareController popoverPresentationController];
                    presentationController.sourceView = self.view;
                }
                
                UIPopoverController *popoverController = [[UIPopoverController alloc] initWithContentViewController:shareController];
                
                [popoverController presentPopoverFromRect:cellRect inView:self.view permittedArrowDirections:UIPopoverArrowDirectionDown animated:YES];
            }
            break;
        }
        default:
        {
            [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://led-cube.eu"]];
            break;
        }
    }
}

- (void)sidebar:(RNFrostedSidebar *)sidebar willShowOnScreenAnimated:(BOOL)animatedYesOrNo
{
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationDuration:sidebar.animationDuration];
    [UIView setAnimationCurve:UIViewAnimationCurveEaseOut];

    self.shadowView.alpha = 0.6f;
    
    [UIView commitAnimations];
}

- (void)sidebar:(RNFrostedSidebar *)sidebar willDismissFromScreenAnimated:(BOOL)animatedYesOrNo
{
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationDuration:sidebar.animationDuration];
    [UIView setAnimationCurve:UIViewAnimationCurveEaseOut];
    
    self.shadowView.alpha = 0.0f;
    
    [UIView commitAnimations];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad) {
        
        if (interfaceOrientation == UIInterfaceOrientationLandscapeLeft || interfaceOrientation == UIInterfaceOrientationLandscapeRight) {
            return YES;
        }
        
    }
    else {
        
        if (interfaceOrientation == UIInterfaceOrientationPortrait) {
            return YES;
        }
    }
    
    return NO;
}

@end
