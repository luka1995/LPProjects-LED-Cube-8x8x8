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
@property (nonatomic, strong) NSString *sFileName;
@property (nonatomic, assign) int whichReading;
@property (nonatomic, assign) int selectedRow;
@property (nonatomic, strong) NSString *renameAnimationNameNew;
@property (nonatomic, strong) NSString *renameAnimationNameOld;
@property (nonatomic, strong) NSMutableData *mutableBuffer;

@end


#define headerAnimationNameLeftPadding 6.0f
#define headerAnimationNameWidth 180.0f
#define headerLineWidth 1.0f


@implementation LPAnimationsListViewController

#pragma mark - Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.title = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationsViewTitle"];
    
    self.tableView.separatorInset = UIEdgeInsetsMake(0.0f, 0.0f, 0.0f, 0.0f);

    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"RefreshIcon"] style:UIBarButtonItemStyleBordered target:self action:@selector(loadAnimationsList)];

    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"BackButton"] style:UIBarButtonItemStyleBordered target:self action:@selector(backButtonClicked)];
    
    [self.stopAnimationButton setTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"StopAnimationButtonTitle"] forState:UIControlStateNormal];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad) {
        UINavigationController *navCon = (UINavigationController *)[[[LPSharedManager sharedManager] splitViewControllerIpad] detailsViewController];
        LPEditCustomEffectViewController *editCustomEffectViewController = (LPEditCustomEffectViewController *)[[navCon viewControllers] objectAtIndex:0];
        [editCustomEffectViewController setCubeEffect:nil animated:YES];
    }
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
        
        [self loadAnimationsList];
    }
}

- (void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];

    if (self.asyncSocket && [self.asyncSocket isConnected]) {
        [self.asyncSocket disconnect];
    }
}

#pragma mark - Actions

- (IBAction)uploadSavedAnimationButtonClicked:(id)sender
{
    self.asyncSocket.delegate = nil;
    self.asyncSocket = nil;
    
    LPSavedAnimationsListViewController *savedAnimationsListViewController = [[LPSavedAnimationsListViewController alloc] initWithNibName:@"LPSavedAnimationsListViewController" bundle:nil];
    savedAnimationsListViewController.canUpload = YES;
    
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        savedAnimationsListViewController.closeButton = YES;
        
        UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:savedAnimationsListViewController];
        [self presentViewController:navigationController animated:YES completion:nil];
    } else {
        savedAnimationsListViewController.backButton = YES;
        [self.navigationController pushViewController:savedAnimationsListViewController animated:YES];
    }
}

- (IBAction)stopAnimationButtonClicked:(id)sender
{
    [self stopAnimation];
}

- (IBAction)newAnimationButtonClicked:(id)sender
{
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewNewAnimationTitle"] message:nil delegate:self cancelButtonTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewCancelButton"] otherButtonTitles:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewNextButton"], nil];
    alertView.accessibilityIdentifier = @"new_animation";
    alertView.alertViewStyle = UIAlertViewStylePlainTextInput;
    [[alertView textFieldAtIndex:0] setPlaceholder:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewNewAnimationTextFieldPlaceholder"]];
    [alertView show];
}

- (void)backButtonClicked
{
    [self.navigationController popViewControllerAnimated:YES];
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

    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    
    if (!cell.mainView) {
        cell.mainView = [[UIView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, tableView.frame.size.width, cell.frame.size.height)];
        [cell addSubview:cell.mainView];
    }
    
    if (!cell.animationNameLabel) {
        cell.animationNameLabel = [[UILabel alloc] initWithFrame:CGRectMake(0.0f, 0.0f, headerAnimationNameWidth, cell.mainView.frame.size.height)];
        cell.animationNameLabel.backgroundColor = [UIColor clearColor];
        cell.animationNameLabel.text = [NSString stringWithFormat:@"  %@", [[file objectForKey:(id)kCFFTPResourceName] stringByReplacingOccurrencesOfString:@".ani" withString:@""]];
        cell.animationNameLabel.font = [UIFont boldSystemFontOfSize:14.0f];
        cell.animationNameLabel.textColor = [UIColor blackColor];
        cell.animationNameLabel.textAlignment = NSTextAlignmentLeft;
        cell.animationNameLabel.numberOfLines = 2;
        [cell.mainView addSubview:cell.animationNameLabel];
    }
    
    if (!cell.fileSizeLabel) {
        cell.fileSizeLabel = [[UILabel alloc] initWithFrame:CGRectMake(headerAnimationNameWidth, 0.0f, ((tableView.frame.size.width - headerAnimationNameWidth) /2), cell.mainView.frame.size.height)];
        cell.fileSizeLabel.backgroundColor = [UIColor clearColor];
        cell.fileSizeLabel.text = [[LPSharedManager sharedManager] fileSizeFormat:sizeOrginal];
        cell.fileSizeLabel.font = [UIFont boldSystemFontOfSize:13.0f];
        cell.fileSizeLabel.textColor = [UIColor blackColor];
        cell.fileSizeLabel.textAlignment = NSTextAlignmentCenter;
        [cell.mainView addSubview:cell.fileSizeLabel];
    }
    
    if (!cell.countLabel) {
        cell.countLabel = [[UILabel alloc] initWithFrame:CGRectMake(headerAnimationNameWidth + ((tableView.frame.size.width - headerAnimationNameWidth) /2), 0.0f, ((tableView.frame.size.width - headerAnimationNameWidth) /2), cell.mainView.frame.size.height)];
        cell.countLabel.backgroundColor = [UIColor clearColor];
        cell.countLabel.text = [NSString stringWithFormat:@"%d", (int)(sizeOrginal / [LPCubeEffect size])];
        cell.countLabel.font = [UIFont boldSystemFontOfSize:13.0f];
        cell.countLabel.textColor = [UIColor blackColor];
        cell.countLabel.textAlignment = NSTextAlignmentCenter;
        [cell.mainView addSubview:cell.countLabel];
    }
    
    if (!cell.line1) {
        cell.line1 = [[UILabel alloc] initWithFrame:CGRectMake(headerAnimationNameWidth, 0.0f, headerLineWidth, cell.mainView.frame.size.height)];
        cell.line1.backgroundColor = [UIColor lightGrayColor];
        [cell.mainView addSubview:cell.line1];
    }
    
    if (!cell.line2) {
        cell.line2 = [[UILabel alloc] initWithFrame:CGRectMake(headerAnimationNameWidth + ((tableView.frame.size.width - headerAnimationNameWidth) /2), 0.0f, headerLineWidth, cell.mainView.frame.size.height)];
        cell.line2.backgroundColor = [UIColor lightGrayColor];
        [cell.mainView addSubview:cell.line2];
    }

    return cell;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    UIView *view = [[UIView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, tableView.frame.size.width, [self tableView:tableView heightForHeaderInSection:section])];
    [view setBackgroundColor:[UIColor lightGrayColor]];
    
    UILabel *animationNameLabel = [[UILabel alloc] initWithFrame:CGRectMake(headerAnimationNameLeftPadding, 0.0f, (headerAnimationNameWidth - headerAnimationNameLeftPadding), view.frame.size.height)];
    animationNameLabel.backgroundColor = [UIColor clearColor];
    animationNameLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"TableViewSectionAnimationNameTitle"];
    animationNameLabel.font = [UIFont boldSystemFontOfSize:13.0f];
    animationNameLabel.textColor = [UIColor blackColor];
    animationNameLabel.textAlignment = NSTextAlignmentLeft;
    [view addSubview:animationNameLabel];
    
    UILabel *fileSizeLabel = [[UILabel alloc] initWithFrame:CGRectMake(headerAnimationNameWidth, 0.0f, ((tableView.frame.size.width - headerAnimationNameWidth) /2), view.frame.size.height)];
    fileSizeLabel.backgroundColor = [UIColor clearColor];
    fileSizeLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"TableViewSectionFileSizeTitle"];
    fileSizeLabel.font = [UIFont boldSystemFontOfSize:13.0f];
    fileSizeLabel.textColor = [UIColor blackColor];
    fileSizeLabel.textAlignment = NSTextAlignmentCenter;
    [view addSubview:fileSizeLabel];
    
    UILabel *countLabel = [[UILabel alloc] initWithFrame:CGRectMake(headerAnimationNameWidth + ((tableView.frame.size.width - headerAnimationNameWidth) /2), 0.0f, ((tableView.frame.size.width - headerAnimationNameWidth) /2), view.frame.size.height)];
    countLabel.backgroundColor = [UIColor clearColor];
    countLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"TableViewSectionEffectsCountTitle"];
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
    
    self.selectedRow = (int)indexPath.row;

    self.sFileName = [[self.objectsArray objectAtIndex:self.selectedRow] objectForKey:(id)kCFFTPResourceName];
    
    UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:nil delegate:self cancelButtonTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetCancelButton"] destructiveButtonTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetDeleteAnimationButton"] otherButtonTitles:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetStartAnimationButton"], [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetEditAnimationButton"], [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetSaveAnimationToPhoneButton"], nil];
    actionSheet.accessibilityIdentifier = @"animation_options";
    [actionSheet showInView:self.view];
}

#pragma mark - UIActionSheetDelegate

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if ([actionSheet.accessibilityIdentifier isEqualToString:@"animation_options"]) {
        switch (buttonIndex) {
            case 0:
            {
                UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewDeleteAnimationWarningTitle"] message:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewDeleteAnimationWarningMessage"] delegate:self cancelButtonTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewCancelButton"] otherButtonTitles:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewDeleteButton"], nil];
                alertView.accessibilityIdentifier = @"delete_file";
                [alertView show];
                break;
            }
            case 1:
            {
                [self startAnimation:self.sFileName];
                break;
            }
            case 2:
            {
                self.sFileName = [[self.objectsArray objectAtIndex:self.selectedRow] objectForKey:(id)kCFFTPResourceName];
                self.whichReading = 1;
                
                NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:@"ftp://%@:%@@%@/%@", [LPSharedManager ftpUsername], [LPSharedManager ftpPassword], [[LPSharedManager sharedManager] selectedIP], self.sFileName]];
                
                CFReadStreamRef stream = CFReadStreamCreateWithFTPURL(NULL, (__bridge CFURLRef) url);
                
                self.inputStream = (__bridge_transfer NSInputStream *)stream;
                [self.inputStream setDelegate:self];
                [self.inputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
                [self.inputStream open];
                
                break;
            }
            case 3:
            {
                self.sFileName = [[self.objectsArray objectAtIndex:self.selectedRow] objectForKey:(id)kCFFTPResourceName];
                self.whichReading = 2;
                
                NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:@"ftp://%@:%@@%@/%@", [LPSharedManager ftpUsername], [LPSharedManager ftpPassword], [[LPSharedManager sharedManager] selectedIP], self.sFileName]];
                
                CFReadStreamRef stream = CFReadStreamCreateWithFTPURL(NULL, (__bridge CFURLRef) url);
                
                self.inputStream = (__bridge_transfer NSInputStream *)stream;
                [self.inputStream setDelegate:self];
                [self.inputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
                [self.inputStream open];
                
                break;
            }
        }
    }
}

#pragma mark - UIAlertViewDelegate

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if ([alertView.accessibilityIdentifier isEqualToString:@"delete_file"]) {
        if (buttonIndex == 1) {
            NSURL *url = [[NSURL alloc] initWithString:[NSString stringWithFormat:@"ftp://%@:%@@%@/%@", [LPSharedManager ftpUsername], [LPSharedManager ftpPassword], [[LPSharedManager sharedManager] selectedIP], self.sFileName]];
#pragma GCC diagnostic ignored "-Wdeprecated"
            Boolean status = CFURLDestroyResource((__bridge CFURLRef)url, nil);
            
            if (status) {
                [self.objectsArray removeObjectAtIndex:self.selectedRow];
                [self.tableView reloadData];
                
                if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                    [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationDeletionSuccessfulToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                } else {
                    [LPToastView toastInView:self.view withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationDeletionSuccessfulToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                }
            } else {
                if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                    [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationDeletionFailedToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                } else {
                    [LPToastView toastInView:self.view withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationDeletionFailedToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                }
            }
        }
    } else if ([alertView.accessibilityIdentifier isEqualToString:@"new_animation"]) {
        if (buttonIndex == 1) {
            [[alertView textFieldAtIndex:0] resignFirstResponder];
            
            if ([[[alertView textFieldAtIndex:0] text] length] > 0) {
                self.asyncSocket.delegate = nil;
                self.asyncSocket = nil;
                
                NSString *name = [[[alertView textFieldAtIndex:0] text] stringByReplacingOccurrencesOfString:@" " withString:@""];
                
                LPAnimation *animation = [LPAnimation new];
                animation.fileName = [NSString stringWithFormat:@"%@.ani", name];

                LPAnimationViewController *animationViewController = [[LPAnimationViewController alloc] initWithNibName:@"LPAnimationViewController" bundle:nil];
                animationViewController.animation = animation;
                if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                    animationViewController.closeButton = YES;
                } else {
                    animationViewController.backButton = YES;
                }

                if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                    UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:animationViewController];
                    [self presentViewController:navigationController animated:YES completion:nil];
                } else {
                    [self.navigationController pushViewController:animationViewController animated:YES];
                }
            }
        }
    }
}

#pragma mark - Load Animations List

- (void)loadAnimationsList
{
    self.whichReading = 0;
    
    NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:@"ftp://%@:%@@%@", [LPSharedManager ftpUsername], [LPSharedManager ftpPassword], [[LPSharedManager sharedManager] selectedIP]]];
    
    CFReadStreamRef stream = CFReadStreamCreateWithFTPURL(NULL, (__bridge CFURLRef) url);
    
    self.inputStream = (__bridge_transfer NSInputStream *)stream;
    [self.inputStream setDelegate:self];
    [self.inputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    [self.inputStream open];
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
            if (self.whichReading == 0) { // List
                if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                    [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationListLoadedToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                } else {
                    [LPToastView toastInView:self.view withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationListLoadedToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                }
                
                if ([self.mutableBuffer length] > 0) {
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
                        
                        self.objectsArray = listFin;
                        [self.tableView reloadData];
                    }
                }
            } else if (self.whichReading == 1) { // File
                self.asyncSocket.delegate = nil;
                self.asyncSocket = nil;
                
                LPAnimation *animation = [LPAnimation animationWithBuffer:(uint8_t *)[self.mutableBuffer bytes] length:(int)[self.mutableBuffer length]];
                animation.fileName = self.sFileName;

                LPAnimationViewController *animationViewController = [[LPAnimationViewController alloc] initWithNibName:@"LPAnimationViewController" bundle:nil];
                if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                    animationViewController.closeButton = YES;
                } else {
                    animationViewController.backButton = YES;
                }
                animationViewController.animation = animation;
                
                __block int saveSelectedRow = self.selectedRow;
                
                [animationViewController setSaveBlock:^(LPAnimation *animationSave) {
                    NSMutableDictionary *updateFile = [NSMutableDictionary new];
                    [updateFile setObject:animationSave.fileName forKey:(id)kCFFTPResourceName];
                    [updateFile setObject:[NSNumber numberWithInt:[animationSave getBytesLength]] forKey:(id)kCFFTPResourceSize];
                    
                    [self.objectsArray replaceObjectAtIndex:saveSelectedRow withObject:updateFile];
                    [self.tableView reloadData];
                }];
                
                if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                    UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:animationViewController];
                    
                    [self presentViewController:navigationController animated:YES completion:nil];
                } else {
                    [self.navigationController pushViewController:animationViewController animated:YES];
                }
            } else if (self.whichReading == 2) { // Save Animation to phone
                if ([self.mutableBuffer length] > 0) {
                    LPAnimation *animation = [LPAnimation animationWithBuffer:(uint8_t *)[self.mutableBuffer bytes] length:(int)[self.mutableBuffer length]];
                    animation.fileName = self.sFileName;
                    
                    if (![[LPSharedManager sharedManager] checkIfSavedAnimationExists:animation.fileName]) {
                        [[[LPSharedManager sharedManager] savedAnimations] addObject:animation];
                        
                        [[LPSharedManager sharedManager] saveSavedAnimations];
                        
                        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                            [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationSavedToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                        } else {
                            [LPToastView toastInView:self.view withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationSavedToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                        }
                    } else {
                        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                            [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationAlreadyExistsToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                        } else {
                            [LPToastView toastInView:self.view withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationAlreadyExistsToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                        }
                    }
                } else {
                    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                        [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationEmptyToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                    } else {
                        [LPToastView toastInView:self.view withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationEmptyToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                    }
                }
            }
            
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
            
            if (self.inputStream) {
                [self.inputStream close];
                [self.inputStream removeFromRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
                self.inputStream = nil;
            }
            
            break;
        }
    }
    
    [ProgressHUD dismiss];
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
        int size = (7 + (int)[animationFileName length]);
        
        unsigned char buffer[size];
        
        buffer[0] = 0xEE;
        buffer[1] = 0xEE;
        buffer[2] = 0xCC;
        buffer[3] = (char)(size / 255);
        buffer[4] = (char)(size - (buffer[3] * 255));
        buffer[5] = 0x02;
        
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
        buffer[5] = 0x03;
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
