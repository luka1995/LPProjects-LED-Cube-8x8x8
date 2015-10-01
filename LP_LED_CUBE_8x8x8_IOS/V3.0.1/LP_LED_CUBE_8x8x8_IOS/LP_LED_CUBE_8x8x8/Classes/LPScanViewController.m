//
//  LPScanViewController.m
//  LP_LED_CUBE_8x8x8
//
//  Created by Luka Penger on 11/06/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPScanViewController.h"


@interface LPScanViewController ()

@property (nonatomic, strong) GCDAsyncUdpSocket *udpSocket;
@property (nonatomic, strong) NSMutableArray *objectsArray;
@property (nonatomic, strong) MBProgressHUD *progressHUD;
@property (nonatomic, assign) BOOL udpServerIsRuning;
@property (nonatomic, strong) NSInputStream *inputStream;
@property (nonatomic, strong) NSMutableArray *arrayIP;

@end


@implementation LPScanViewController

#pragma mark - Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.title = @"Devices";
    
    self.tableView.separatorInset = UIEdgeInsetsMake(0.0f, 0.0f, 0.0f, 0.0f);
    
    self.navigationItem.backBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Back" style:UIBarButtonItemStyleBordered target:nil action:nil];

    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Scan" style:UIBarButtonItemStyleBordered target:self action:@selector(buttonScanClicked:)];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationDidEnterBackground) name:UIApplicationDidEnterBackgroundNotification object:NULL];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationDidBecomeActive) name:UIApplicationDidBecomeActiveNotification object:NULL];
    
    self.arrayIP = [NSMutableArray new];
    for (int a=0; a<256; a++) {
        [self.arrayIP addObject:[NSString stringWithFormat:@"%d", a]];
    }
    
    [self startUDP];
    
    [self scanForDevices];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    
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

- (void)applicationDidEnterBackground
{
    [self stopUDP];
}

- (void)applicationDidBecomeActive
{
    [self startUDP];
}

- (void)startUDP
{
    if (!self.udpServerIsRuning) {
        NSError *error = nil;
        
        if (![self.udpSocket bindToPort:[LPSharedManager UDPPort] error:&error]) {
            
            [self showHostIsDownHUD];
            
            NSLog(@"Error starting server (bind): %@", error);
            
            return;
        }
        
        if (![self.udpSocket beginReceiving:&error]) {
            [self.udpSocket close];
            
            [self showHostIsDownHUD];
            
            NSLog(@"Error starting server (recv): %@", error);
            
            return;
        }
        
        NSLog(@"UDP server started on port %hu", [self.udpSocket localPort]);
        
        [self.udpSocket enableBroadcast:YES error:nil];
        
        self.udpServerIsRuning = YES;
    }
}

- (void)stopUDP
{
    if (self.udpServerIsRuning) {
        [self.udpSocket close];
    
        NSLog(@"UDP server stopped");
    
        self.udpServerIsRuning = NO;
    }
}

- (void)showHostIsDownHUD
{
    if (!self.progressHUD) {
        self.progressHUD = [MBProgressHUD showHUDAddedTo:[UIApplication sharedApplication].delegate.window animated:YES];
        
        self.progressHUD.mode = MBProgressHUDModeText;
        self.progressHUD.labelText = @"Host is down";
        self.progressHUD.labelFont = [UIFont boldSystemFontOfSize:14];
        self.progressHUD.margin = 10.f;
        self.progressHUD.yOffset = 0.f;

        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 2 * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
            [self.progressHUD hide:YES];
            [self.progressHUD removeFromSuperview];
            self.progressHUD = nil;
        });
    }
}

- (void)showLoadingHUD
{
    if (!self.progressHUD) {
        self.progressHUD = [MBProgressHUD showHUDAddedTo:[UIApplication sharedApplication].delegate.window animated:YES];
        
        self.progressHUD.labelText = @"Searching...";
        self.progressHUD.labelFont = [UIFont boldSystemFontOfSize:14];
        
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 2 * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
            [self.progressHUD hide:YES];
            [self.progressHUD removeFromSuperview];
            self.progressHUD = nil;
        });
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

#pragma mark - Actions

- (void)buttonScanClicked:(id)sender
{
    [self scanForDevices];
}

- (void)scanForDevices
{
    Reachability *r = [Reachability reachabilityForInternetConnection];
    NetworkStatus internetStatus = [r currentReachabilityStatus];

    if(((internetStatus != ReachableViaWiFi) && (internetStatus != ReachableViaWWAN)) || (internetStatus == NotReachable)) {
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"No Internet Connection" message:@"You require an internet connection via WiFi or cellular network for location finding to work." delegate:nil cancelButtonTitle:@"Close" otherButtonTitles:nil, nil];
        
        [alertView show];
    } else {
        [self showLoadingHUD];
        
        [self.objectsArray removeAllObjects];
    
        [self.tableView reloadData];
        
        NSString *deviceIP = [self getIPAddress];
        
        if ([deviceIP isEqualToString:@"error"]) {
            deviceIP = @"";
        }
        
        unsigned char buffer[[deviceIP length] + 7];
        
        buffer[0] = 0xEE;   // start byte
        buffer[1] = 0xEE;   // start byte
        buffer[2] = 0xCC;   // start byte
        buffer[3] = 0x00;
        buffer[4] = (char)sizeof(buffer);
        buffer[5] = 0x00;   // function
        
        int a;
        
        for (a=0; a<[deviceIP length]; a++) {
            buffer[a+6] = [deviceIP characterAtIndex:a];
        }
        
        buffer[(sizeof(buffer)-1)] = calcCRC(buffer,(sizeof(buffer)-1));
        
        NSString *ip = @"255.255.255.255"; // BROADCAST UDP
        
        [self.udpSocket bindToPort:[LPSharedManager UDPPort] error:nil];
        
        [self.udpSocket sendData:[NSData dataWithBytes:buffer length:sizeof(buffer)] toHost:ip port:[LPSharedManager UDPPort] withTimeout:-1 tag:0];
    }
}

- (IBAction)selectIPButtonClicked:(id)sender
{
    [RMPickerViewController setLocalizedTitleForSelectButton:@"Connect"];
    [RMPickerViewController setLocalizedTitleForCancelButton:@"Cancel"];
    
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
    
    [pickerVC show];
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
    
    if ([[[LPSharedManager sharedManager] savedConnectedIPs] containsObject:selectedIP]) {
        [self connectToHost:[[LPSharedManager sharedManager] selectedIP] username:[[LPSharedManager sharedManager] ftpUsername] password:[[LPSharedManager sharedManager] ftpPassword]];
    } else {
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"Login"
                                                            message:nil
                                                           delegate:self
                                                  cancelButtonTitle:@"Cancel"
                                                  otherButtonTitles:@"Continue", nil];
        alertView.accessibilityIdentifier = @"login";
        [alertView setAlertViewStyle:UIAlertViewStyleLoginAndPasswordInput];
        
        [alertView show];
    }
}

- (void)pickerViewControllerDidCancel:(RMPickerViewController *)vc
{
    NSLog(@"Selection was canceled");
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
    UITableViewCell *cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"cell"];
    
    cell.textLabel.text = [[self objectsArray] objectAtIndex:indexPath.row];
    cell.textLabel.textAlignment = NSTextAlignmentCenter;
    
    cell.backgroundColor = [UIColor colorWithRed:(100.0/255.0) green:(240.0/255.0) blue:(170.0/255.0) alpha:0.5];

    return cell;
}

#pragma mark - UITableViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [self.tableView deselectRowAtIndexPath:indexPath animated:NO];
    
    NSString *selectedIP = [self.objectsArray objectAtIndex:indexPath.row];
    
    [[LPSharedManager sharedManager] setSelectedIP:selectedIP];
    
    if ([[[LPSharedManager sharedManager] savedConnectedIPs] containsObject:selectedIP]) {
        [self connectToHost:[[LPSharedManager sharedManager] selectedIP] username:[[LPSharedManager sharedManager] ftpUsername] password:[[LPSharedManager sharedManager] ftpPassword]];
    } else {
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"Login"
                                                            message:nil
                                                           delegate:self
                                                  cancelButtonTitle:@"Cancel"
                                                  otherButtonTitles:@"Continue", nil];
        alertView.accessibilityIdentifier = @"login";
        [alertView setAlertViewStyle:UIAlertViewStyleLoginAndPasswordInput];
        
        [alertView show];
    }
}

#pragma mark - UIAlertViewDelegate

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if ([alertView.accessibilityIdentifier isEqualToString:@"login"]) {
        if (buttonIndex == 1) {
            NSString *username = [[alertView textFieldAtIndex:0] text];
            NSString *password = [[alertView textFieldAtIndex:1] text];
            
            [[LPSharedManager sharedManager] setFtpUsername:username];
            [[LPSharedManager sharedManager] setFtpPassword:password];
            
            [self connectToHost:[[LPSharedManager sharedManager] selectedIP] username:[[LPSharedManager sharedManager] ftpUsername] password:[[LPSharedManager sharedManager] ftpPassword]];
        }
    }
}

#pragma mark - Connect

- (void)connectToHost:(NSString *)host username:(NSString *)username password:(NSString *)password
{
    [self showLoadingAnimations];
    
    NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:@"ftp://%@:%@@%@", username, password, host]];
    
    CFReadStreamRef stream = CFReadStreamCreateWithFTPURL(NULL, (__bridge CFURLRef) url);
    
    self.inputStream = (__bridge_transfer NSInputStream *)stream;
    [self.inputStream setDelegate:self];
    [self.inputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    [self.inputStream open];
}

#pragma mark - GCDAsyncUdpSocketDelegate

- (void)udpSocket:(GCDAsyncUdpSocket *)sock didReceiveData:(NSData *)data fromAddress:(NSData *)address withFilterContext:(id)filterContext
{
    [self.udpSocket bindToPort:[LPSharedManager UDPPort] error:nil];

    NSString *host = [GCDAsyncUdpSocket hostFromAddress:address];
    
    if (![host isEqualToString:[self getIPAddress]] && ![host hasPrefix:@"::ffff:"]) {
        [self.objectsArray addObject:host];
        
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
                uint8_t buffer[1024];
                int len;
                
                while ([self.inputStream hasBytesAvailable]) {
                    len = [self.inputStream read:buffer maxLength:sizeof(buffer)];
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
                            
                            //NSLog(@"%@", [listFin description]);
                            
                            LPAnimationsListViewController *animationsListViewController = [[LPAnimationsListViewController alloc] initWithNibName:@"LPAnimationsListViewController_iPhone" bundle:nil];
                            animationsListViewController.objectsArray = listFin;
                            
                            [self.navigationController pushViewController:animationsListViewController animated:YES];
                            
                            if (![[[LPSharedManager sharedManager] savedConnectedIPs] containsObject:[[LPSharedManager sharedManager] selectedIP]]) {
                                [[[LPSharedManager sharedManager] savedConnectedIPs] addObject:[[LPSharedManager sharedManager] selectedIP]];
                            }
                        }
                    }
                }
            }
            break;
        }
        case NSStreamEventErrorOccurred:
        {
            NSLog(@"Can not connect to the host!");
            
            UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"Error" message:@"Can not connect to the host! Try again" delegate:nil cancelButtonTitle:@"Cancel" otherButtonTitles:nil, nil];
            [alertView show];
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

@end
