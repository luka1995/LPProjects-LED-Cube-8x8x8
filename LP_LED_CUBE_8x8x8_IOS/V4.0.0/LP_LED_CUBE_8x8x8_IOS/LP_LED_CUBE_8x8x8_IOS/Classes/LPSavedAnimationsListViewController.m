//
//  LPSavedAnimationsListViewController.m
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 12/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPSavedAnimationsListViewController.h"


@interface LPSavedAnimationsListViewController ()

@property (nonatomic, strong) NSOutputStream *outputStream;
@property (nonatomic, assign) int selectedRow;
@property (nonatomic, strong) HTTPServer *httpServer;

@end


#define headerAnimationNameLeftPadding 6.0f
#define headerAnimationNameWidth 180.0f
#define headerLineWidth 1.0f


@implementation LPSavedAnimationsListViewController

#pragma mark - Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.title = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SavedAnimationsViewTitle"];
    
    self.tableView.separatorInset = UIEdgeInsetsMake(0.0f, 0.0f, 0.0f, 0.0f);

    if (self.backButton) {
        self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"BackButton"] style:UIBarButtonItemStyleBordered target:self action:@selector(backButtonClicked)];
    }
    
    if (self.closeButton) {
        self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"CloseButton"] style:UIBarButtonItemStyleBordered target:self action:@selector(closeButtonClicked)];
    }
    
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"NewIcon"] style:UIBarButtonItemStyleBordered target:self action:@selector(newAnimationButtonClicked)];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(webServerReloadTableView) name:@"WebServerReloadTableView" object:nil];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    [self setWEBServerButtonText];
    
    [[LPSharedManager sharedManager] loadSavedAnimations];
    [self.tableView reloadData];
    
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad) {
        UINavigationController *navCon = (UINavigationController *)[[[LPSharedManager sharedManager] splitViewControllerIpad] detailsViewController];
        LPEditCustomEffectViewController *editCustomEffectViewController = (LPEditCustomEffectViewController *)[[navCon viewControllers] objectAtIndex:0];
        [editCustomEffectViewController setCubeEffect:nil animated:YES];
    }
}

- (void)viewDidDisappear:(BOOL)animated
{
    if ([self.httpServer isRunning]) {
        [self.httpServer stop];
    }
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
    return [[[LPSharedManager sharedManager] savedAnimations] count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    LPAnimationCellView *cell = [LPAnimationCellView cellFromNibNamed:@"LPAnimationCellView"];
    
    LPAnimation *animation = [[[LPSharedManager sharedManager] savedAnimations] objectAtIndex:indexPath.row];
    
    unsigned long long sizeOrginal = (unsigned long long)[animation getBytesLength];
    
    if (!cell.animationNameLabel) {
        cell.animationNameLabel = [[UILabel alloc] initWithFrame:CGRectMake(0.0f, 0.0f, headerAnimationNameWidth, cell.frame.size.height)];
        cell.animationNameLabel.backgroundColor = [UIColor clearColor];
        cell.animationNameLabel.text = [NSString stringWithFormat:@"  %@", [animation.fileName stringByReplacingOccurrencesOfString:@".ani" withString:@""]];
        cell.animationNameLabel.font = [UIFont boldSystemFontOfSize:14.0f];
        cell.animationNameLabel.textColor = [UIColor blackColor];
        cell.animationNameLabel.textAlignment = NSTextAlignmentLeft;
        cell.animationNameLabel.numberOfLines = 2;
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
    
    cell.backgroundColor = [UIColor colorWithRed:(230.0/255.0) green:(230.0/255.0) blue:(230.0/255.0) alpha:1.0];
    
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
    
    if (self.canUpload) {
        UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:nil delegate:self cancelButtonTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetCancelButton"] destructiveButtonTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetDeleteAnimationButton"] otherButtonTitles:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetEditAnimationButton"], [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetRenameAnimationButton"], [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetShareAnimationButton"], [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetUploadAnimationButton"], nil];
        actionSheet.accessibilityIdentifier = @"animation_options";
        [actionSheet showInView:self.view];
    } else if (self.canAppend) {
        UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:nil delegate:self cancelButtonTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetCancelButton"] destructiveButtonTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetDeleteAnimationButton"] otherButtonTitles:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetEditAnimationButton"], [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetRenameAnimationButton"], [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetShareAnimationButton"], [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetAppendAnimationButton"], nil];
        actionSheet.accessibilityIdentifier = @"animation_options";
        [actionSheet showInView:self.view];
    } else {
        UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:nil delegate:self cancelButtonTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetCancelButton"] destructiveButtonTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetDeleteAnimationButton"] otherButtonTitles:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetEditAnimationButton"], [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetRenameAnimationButton"], [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetShareAnimationButton"], nil];
        actionSheet.accessibilityIdentifier = @"animation_options";
        [actionSheet showInView:self.view];
    }
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
            default:
            {
                if (((self.canUpload || self.canAppend) && buttonIndex == 1) || ((!self.canUpload && !self.canAppend) && buttonIndex == 1)) {
                    // Edit

                    LPAnimation *animation = [[[LPSharedManager sharedManager] savedAnimations] objectAtIndex:self.selectedRow];
                    
                    LPAnimationViewController *animationViewController = [[LPAnimationViewController alloc] initWithNibName:@"LPAnimationViewController" bundle:nil];
                    animationViewController.saveBlockOnly = YES;
                    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                        animationViewController.closeButton = YES;
                    } else {
                        animationViewController.backButton = YES;
                    }
                    animationViewController.animation = [animation copy];
                    
                    __block int saveSelectedRow = self.selectedRow;
                    
                    [animationViewController setSaveBlock:^(LPAnimation *animationSave) {
                        [[[LPSharedManager sharedManager] savedAnimations] replaceObjectAtIndex:saveSelectedRow withObject:animationSave];
                        
                        [[LPSharedManager sharedManager] saveSavedAnimations];
                    }];
                    
                    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                        UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:animationViewController];
                        
                        [self presentViewController:navigationController animated:YES completion:nil];
                    } else {
                        [self.navigationController pushViewController:animationViewController animated:YES];
                    }
                } else if (((self.canUpload || self.canAppend) && buttonIndex == 2) || ((!self.canUpload && !self.canAppend) && buttonIndex == 2)) {
                    // Rename
                    
                    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewRenameAnimationTitle"] message:nil delegate:self cancelButtonTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewCancelButton"] otherButtonTitles:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewSaveButton"], nil];
                    alertView.accessibilityIdentifier = @"rename_animation";
                    alertView.alertViewStyle = UIAlertViewStylePlainTextInput;
                    [[alertView textFieldAtIndex:0] setPlaceholder:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewRenameAnimationTextFieldPlaceholder"]];
                    [alertView show];
                } else if (((self.canUpload || self.canAppend) && buttonIndex == 3) || ((!self.canUpload && !self.canAppend) && buttonIndex == 3)) {
                    // Share
                    
                    LPAnimation *animation = [[[LPSharedManager sharedManager] savedAnimations] objectAtIndex:self.selectedRow];
                    
                    if ([animation.effectsList count] == 0) {
                        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                            [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationEmptyToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                        } else {
                            [LPToastView toastInView:self.view withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationEmptyToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                        }
                    } else {
                        MFMailComposeViewController *mailController = [MFMailComposeViewController new];
                        mailController.mailComposeDelegate = self;

                        NSData *vcfData = [NSData dataWithBytes:[animation getBytes] length:[animation getBytesLength]];
                        
                        [mailController addAttachmentData:vcfData mimeType:@"application/octet-stream" fileName:animation.fileName];

                        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad) {
                            [[[LPSharedManager sharedManager] splitViewControllerIpad] showModalViewController:mailController animated:YES];
                        } else {
                            [self presentViewController:mailController animated:YES completion:nil];
                        }
                    }
                } else if (self.canUpload && buttonIndex == 4) {
                    // Upload
                    
                    LPAnimation *animation = [[[LPSharedManager sharedManager] savedAnimations] objectAtIndex:self.selectedRow];
                    
                    if ([animation.effectsList count] == 0) {
                        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                            [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationEmptyToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                        } else {
                            [LPToastView toastInView:self.view withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationEmptyToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                        }
                    } else {
                        NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:@"ftp://%@:%@@%@/%@", [LPSharedManager ftpUsername], [LPSharedManager ftpPassword], [[LPSharedManager sharedManager] selectedIP], animation.fileName]];
                        
                        CFWriteStreamRef stream = CFWriteStreamCreateWithFTPURL(NULL, (__bridge CFURLRef) url);
                        
                        self.outputStream = (__bridge_transfer NSOutputStream *)stream;
                        
                        [self.outputStream open];
                        
                        NSInteger nwritten = [self.outputStream write:[animation getBytes] maxLength:[animation getBytesLength]];
                        
                        if (nwritten == -1) {
                            NSLog(@"Error writing to stream: %@", [self.outputStream streamError]);
                            
                            if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                                [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"CanNotConnectToHostToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                            } else {
                                [LPToastView toastInView:self.view withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"CanNotConnectToHostToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                            }
                        } else {
                            NSLog(@"Wrote %lld bytes to stream", (long long)nwritten);
                            
                            if (self.backButton) {
                                [self.navigationController popViewControllerAnimated:YES];
                            }
                            
                            if (self.closeButton) {
                                [self dismissViewControllerAnimated:YES completion:nil];
                            }
                            
                            if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                                [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationUploadedToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                            } else {
                                [LPToastView toastInView:self.view withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationUploadedToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                            }
                        }
                        
                        [self.outputStream close];
                        self.outputStream = nil;
                    }
                } else if (self.canAppend && buttonIndex == 4) {
                    // Append
                    
                    LPAnimation *animation = [[[LPSharedManager sharedManager] savedAnimations] objectAtIndex:self.selectedRow];
                    
                    if (self.appendBlock)
                        self.appendBlock(animation);
                    
                    if (self.closeButton) {
                        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                            [self dismissViewControllerAnimated:YES completion:nil];
                        } else {
                            [[[LPSharedManager sharedManager] splitViewControllerIpad] hideModalViewControllerAnimated:YES];
                        }
                    }
                    
                    if (self.backButton) {
                        [self.navigationController popViewControllerAnimated:YES];
                    }
                }
            }
        }
    }
}

#pragma mark - MFMailComposeViewControllerDelegate

- (void)mailComposeController:(MFMailComposeViewController *)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError *)error
{
    switch (result) {
        case MFMailComposeResultCancelled:
        NSLog(@"Mail cancelled: you cancelled the operation and no email message was queued.");
        break;
        case MFMailComposeResultSaved:
        NSLog(@"Mail saved: you saved the email message in the drafts folder.");
        break;
        case MFMailComposeResultSent:
        NSLog(@"Mail send: the email message is queued in the outbox. It is ready to send.");
        break;
        case MFMailComposeResultFailed:
        NSLog(@"Mail failed: the email message was not saved or queued, possibly due to an error.");
        break;
        default:
        NSLog(@"Mail not sent.");
        break;
    }
    
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad) {
        [[[LPSharedManager sharedManager] splitViewControllerIpad] hideModalViewControllerAnimated:YES];
    } else {
        [controller dismissViewControllerAnimated:YES completion:nil];
    }
}

#pragma mark - UIAlertViewDelegate

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if ([alertView.accessibilityIdentifier isEqualToString:@"delete_file"]) {
        if (buttonIndex == 1) {
            [[[LPSharedManager sharedManager] savedAnimations] removeObjectAtIndex:self.selectedRow];
            [[LPSharedManager sharedManager] saveSavedAnimations];
            
            [self.tableView reloadData];
        }
    } else if ([alertView.accessibilityIdentifier isEqualToString:@"rename_animation"]) {
        if (buttonIndex == 1) {
            [[alertView textFieldAtIndex:0] resignFirstResponder];
            
            if ([[[alertView textFieldAtIndex:0] text] length] > 0) {
                NSString *name = [[[alertView textFieldAtIndex:0] text] stringByReplacingOccurrencesOfString:@" " withString:@""];
                
                LPAnimation *animation = [[[LPSharedManager sharedManager] savedAnimations] objectAtIndex:self.selectedRow];
                animation.fileName = [NSString stringWithFormat:@"%@.ani", name];
                
                [[LPSharedManager sharedManager] saveSavedAnimations];
                
                [self.tableView reloadData];
            }
        }
    } else if ([alertView.accessibilityIdentifier isEqualToString:@"new_animation"]) {
        if (buttonIndex == 1) {
            [[alertView textFieldAtIndex:0] resignFirstResponder];
            
            if ([[[alertView textFieldAtIndex:0] text] length] > 0) {
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
                animationViewController.saveBlockOnly = YES;
                
                [animationViewController setSaveBlock:^(LPAnimation *animation) {
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
                    
                    [self.tableView reloadData];
                }];
                
                if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                    UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:animationViewController];
                    [self presentViewController:navigationController animated:YES completion:nil];
                } else {
                    [self.navigationController pushViewController:animationViewController animated:YES];
                }
            }
        }
    } else if ([alertView.accessibilityIdentifier isEqualToString:@"clear_list"]) {
        if (buttonIndex == 1) {
            [[[LPSharedManager sharedManager] savedAnimations] removeAllObjects];
            [[LPSharedManager sharedManager] saveSavedAnimations];
            [self.tableView reloadData];
        }
    }
}

#pragma mark - Actions

- (void)newAnimationButtonClicked
{
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewNewAnimationTitle"] message:nil delegate:self cancelButtonTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewCancelButton"] otherButtonTitles:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewNextButton"], nil];
    alertView.accessibilityIdentifier = @"new_animation";
    alertView.alertViewStyle = UIAlertViewStylePlainTextInput;
    [[alertView textFieldAtIndex:0] setPlaceholder:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewNewAnimationTextFieldPlaceholder"]];
    [alertView show];
}

- (void)closeButtonClicked
{
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        [self dismissViewControllerAnimated:YES completion:nil];
    } else {
        [[[LPSharedManager sharedManager] splitViewControllerIpad] hideModalViewControllerAnimated:YES];
    }
}

- (void)backButtonClicked
{
    [self.navigationController popViewControllerAnimated:YES];
}

- (IBAction)deleteButtonClicked:(id)sender
{
    if ([[[LPSharedManager sharedManager] savedAnimations] count] > 0) {
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewClearListAnimationsTitle"] message:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewClearListAnimationsMessage"] delegate:self cancelButtonTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewCancelButton"] otherButtonTitles:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewClearButton"], nil];
        alertView.accessibilityIdentifier = @"clear_list";
        [alertView show];
    }
}

- (IBAction)startStopServerButtonClicked:(id)sender
{
    [self startStopServer];
}

#pragma mark - WEB Server

- (void)setWEBServerButtonText
{
    if ([self.httpServer isRunning]) {
        [self.startStopWEBServerButton setTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"StopWEBServerButtonTitle"] forState:UIControlStateNormal];
    } else {
        [self.startStopWEBServerButton setTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"StartWEBServerButtonTitle"] forState:UIControlStateNormal];
    }
}

- (HTTPServer *)httpServer
{
    if (!_httpServer) {
        _httpServer = [HTTPServer new];
    
        [_httpServer setConnectionClass:[WEBServerConnection class]];
    }
    return _httpServer;
}

- (void)startStopServer
{
    [LPToastView removeToastFromView];

    if ([self.httpServer isRunning]) {
        [self.httpServer stop];
        
        NSString *text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"WEBServerClosedAlertView"];
        
        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
            [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:text withPaddingBottom:[LPSharedManager toastViewPadding]];
        } else {
            [LPToastView toastInView:self.view withText:text withPaddingBottom:[LPSharedManager toastViewPadding]];
        }
    } else {
        [self.httpServer setPort:[LPSharedManager WEBServerPort]];
        [self.httpServer setType:@"_http._tcp."];
        
        NSString *webPath = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"Web"];
        [self.httpServer setDocumentRoot:webPath];
        
        NSError *errorr;
        if ([self.httpServer start:&errorr]) {
            NSString *text = [NSString stringWithFormat:@"http://%@", [self getIPAddress]];
            
            if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:text withPaddingBottom:[LPSharedManager toastViewPadding]];
            } else {
                [LPToastView toastInView:self.view withText:text withPaddingBottom:[LPSharedManager toastViewPadding]];
            }
        } else {
            NSString *text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ErrorStartingWEBServerAlertView"];
            
            if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:text withPaddingBottom:[LPSharedManager toastViewPadding]];
            } else {
                [LPToastView toastInView:self.view withText:text withPaddingBottom:[LPSharedManager toastViewPadding]];
            }
        }
    }
    
    [self setWEBServerButtonText];
}

- (void)webServerReloadTableView
{
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0),
                   ^{
                       dispatch_async(dispatch_get_main_queue(),
                                      ^{    //back on main thread
                                          [[LPSharedManager sharedManager] loadSavedAnimations];
                                          [self.tableView reloadData];
                                      });});
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

@end
