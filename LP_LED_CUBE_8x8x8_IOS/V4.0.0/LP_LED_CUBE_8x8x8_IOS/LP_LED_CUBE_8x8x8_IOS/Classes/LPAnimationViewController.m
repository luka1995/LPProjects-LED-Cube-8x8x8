//
//  LPAnimationViewController.m
//  LP_LED_CUBE_8x8x8
//
//  Created by Luka Penger on 20/06/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPAnimationViewController.h"


@interface LPAnimationViewController ()

@property (nonatomic, strong) NSOutputStream *outputStream;
@property (nonatomic, assign) int selectedRow;

@end


#define headerAnimationNameLeftPadding 6.0f
#define headerDelayNameWidth 100.0f
#define headerLineWidth 1.0f


@implementation LPAnimationViewController

#pragma mark - Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.title = [self.animation.fileName stringByReplacingOccurrencesOfString:@".ani" withString:@""];
    
    self.tableView.separatorInset = UIEdgeInsetsMake(0.0f, 0.0f, 0.0f, 0.0f);
    
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"MoveIcon"] style:UIBarButtonItemStyleBordered target:self action:@selector(moveButtonClicked)];
    
    if (self.backButton) {
        self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"BackButton"] style:UIBarButtonItemStyleBordered target:self action:@selector(backButtonClicked)];
    }
    
    if (self.closeButton) {
        self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"CloseButton"] style:UIBarButtonItemStyleBordered target:self action:@selector(closeButtonClicked)];
    }
    
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad) {
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(receiveCubeEffectSave:) name:@"EditCustomAnimationSave" object:nil];
    }
    
    self.selectedRow = INT16_MAX;
}

#pragma mark - UITableViewDataSource

- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath
{
    return YES;
}

- (UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return UITableViewCellEditingStyleNone;
}

- (BOOL)tableView:(UITableView *)tableview shouldIndentWhileEditingRowAtIndexPath:(NSIndexPath *)indexPath
{
    return NO;
}

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
    return [[self.animation effectsList] count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    LPCubeEffect *cubeEffect = (LPCubeEffect *)[[self.animation effectsList] objectAtIndex:indexPath.row];
    
    LPCubeEffectCustomCellView *cell = [LPCubeEffectCustomCellView cellFromNibNamed:@"LPCubeEffectCustomCellView"];
    
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    
    if (!cell.mainView) {
        cell.mainView = [[UIView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, tableView.frame.size.width, cell.frame.size.height)];
        [cell addSubview:cell.mainView];
    }
    
    if (!cell.effectNameLabel) {
        cell.effectNameLabel = [[UILabel alloc] initWithFrame:CGRectMake(headerAnimationNameLeftPadding, 0.0f, (self.tableView.frame.size.width - headerDelayNameWidth), cell.mainView.frame.size.height)];
        cell.effectNameLabel.backgroundColor = [UIColor clearColor];
        cell.effectNameLabel.text = [NSString stringWithFormat:@"%@", cubeEffect.name];
        cell.effectNameLabel.font = [UIFont boldSystemFontOfSize:16.0f];
        cell.effectNameLabel.textColor = [UIColor blackColor];
        cell.effectNameLabel.textAlignment = NSTextAlignmentLeft;
        [cell.mainView addSubview:cell.effectNameLabel];
    }
    
    if (!cell.delayLabel) {
        cell.delayLabel = [[UILabel alloc] initWithFrame:CGRectMake(cell.effectNameLabel.frame.size.width, 0.0f, headerDelayNameWidth, cell.mainView.frame.size.height)];
        cell.delayLabel.backgroundColor = [UIColor clearColor];
        if (cubeEffect.delayUnit < 4) {
            cell.delayLabel.text = [NSString stringWithFormat:@"%d %@", (cubeEffect.delay * [[[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"DelayUnitsMultiplierText"] objectAtIndex:cubeEffect.delayUnit] intValue]), [[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"DelayUnitsMultiplierUnits"] objectAtIndex:cubeEffect.delayUnit]];
        }
        cell.delayLabel.font = [UIFont boldSystemFontOfSize:13.0f];
        cell.delayLabel.textColor = [UIColor blackColor];
        cell.delayLabel.textAlignment = NSTextAlignmentCenter;
        [cell.mainView addSubview:cell.delayLabel];
    }
    
    if (!cell.line1) {
        cell.line1 = [[UILabel alloc] initWithFrame:CGRectMake(cell.effectNameLabel.frame.size.width, 0.0f, headerLineWidth, cell.mainView.frame.size.height)];
        cell.line1.backgroundColor = [UIColor lightGrayColor];
        [cell.mainView addSubview:cell.line1];
    }
    
    cell.backgroundColor = [UIColor colorWithRed:(230.0/255.0) green:(230.0/255.0) blue:(230.0/255.0) alpha:1.0];
    [cell setDefaultColor:cell.backgroundColor];
    
    __block int row = (int)indexPath.row;
    
    UIColor *greenColor = [UIColor colorWithRed:(0.0/255.0) green:(190.0/255.0) blue:(140.0/255.0) alpha:1.0];
    [cell setSwipeGestureWithView:[self viewWithImageName:@"CopyIcon"] color:greenColor mode:MCSwipeTableViewCellModeSwitch state:MCSwipeTableViewCellState3 completionBlock:^(MCSwipeTableViewCell *cell, MCSwipeTableViewCellState state, MCSwipeTableViewCellMode mode) {
        LPCubeEffect *object = (LPCubeEffect *)[[self.animation effectsList] objectAtIndex:row];
        
        LPCubeEffect *copyObject = [object copy];
        
        copyObject.name = [NSString stringWithFormat:@"%@*", copyObject.name];
        
        [[self.animation effectsList] addObject:copyObject];
        
        [self.tableView insertRowsAtIndexPaths:[NSArray arrayWithObject:[NSIndexPath indexPathForRow:([[self.animation effectsList] count] - 1) inSection:0]] withRowAnimation:UITableViewRowAnimationAutomatic];
        
        [self.tableView scrollToRowAtIndexPath:[NSIndexPath indexPathForRow:([[self.animation effectsList] count] - 1) inSection:0] atScrollPosition:UITableViewScrollPositionBottom animated:YES];
    }];
    
    UIColor *redColor = [UIColor colorWithRed:232.0 / 255.0 green:61.0 / 255.0 blue:14.0 / 255.0 alpha:1.0];
    [cell setSwipeGestureWithView:[self viewWithImageName:@"TrashIcon"] color:redColor mode:MCSwipeTableViewCellModeExit state:MCSwipeTableViewCellState1 completionBlock:^(MCSwipeTableViewCell *cell, MCSwipeTableViewCellState state, MCSwipeTableViewCellMode mode) {
        [[self.animation effectsList] removeObjectAtIndex:row];
        
        [self.tableView reloadData];
        
        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad) {
            if (self.selectedRow == row) {
                self.selectedRow = INT16_MAX;
                
                UINavigationController *navCon = (UINavigationController *)[[[LPSharedManager sharedManager] splitViewControllerIpad] detailsViewController];
                LPEditCustomEffectViewController *editCustomEffectViewController = (LPEditCustomEffectViewController *)[[navCon viewControllers] objectAtIndex:0];
                [editCustomEffectViewController setCubeEffect:nil animated:YES];
            } else if (self.selectedRow >= [self.animation.effectsList count] && [self.animation.effectsList count] > 0) {
                self.selectedRow--;
            }
        }
    }];
    
    return cell;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    UIView *view = [[UIView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, tableView.frame.size.width, [self tableView:tableView heightForHeaderInSection:section])];
    [view setBackgroundColor:[UIColor lightGrayColor]];
    
    UILabel *animationNameLabel = [[UILabel alloc] initWithFrame:CGRectMake(headerAnimationNameLeftPadding, 0.0f, (self.tableView.frame.size.width - headerDelayNameWidth), view.frame.size.height)];
    animationNameLabel.backgroundColor = [UIColor clearColor];
    animationNameLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"TableViewSectionEffectNameTitle"];
    animationNameLabel.font = [UIFont boldSystemFontOfSize:14.0f];
    animationNameLabel.textColor = [UIColor blackColor];
    animationNameLabel.textAlignment = NSTextAlignmentLeft;
    [view addSubview:animationNameLabel];
    
    UILabel *delayLabel = [[UILabel alloc] initWithFrame:CGRectMake(animationNameLabel.frame.size.width, 0.0f, headerDelayNameWidth, view.frame.size.height)];
    delayLabel.backgroundColor = [UIColor clearColor];
    delayLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"TableViewSectionDelayTitle"];
    delayLabel.font = [UIFont boldSystemFontOfSize:13.0f];
    delayLabel.textColor = [UIColor blackColor];
    delayLabel.textAlignment = NSTextAlignmentCenter;
    [view addSubview:delayLabel];
    
    UIView *line1 = [[UIView alloc] initWithFrame:CGRectMake(animationNameLabel.frame.size.width, 0.0f, headerLineWidth, view.frame.size.height)];
    line1.backgroundColor = [UIColor grayColor];
    [view addSubview:line1];

    return view;
}

- (UIView *)viewWithImageName:(NSString *)imageName
{
    UIImage *image = [UIImage imageNamed:imageName];
    UIImageView *imageView = [[UIImageView alloc] initWithImage:image];
    imageView.contentMode = UIViewContentModeCenter;
    return imageView;
}

#pragma mark - UITableViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [self.tableView deselectRowAtIndexPath:indexPath animated:NO];

    self.selectedRow = (int)indexPath.row;
    
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        LPEditCustomEffectViewController *editCustomEffectViewController = [[LPEditCustomEffectViewController alloc] initWithNibName:@"LPEditCustomEffectViewController" bundle:nil];
        editCustomEffectViewController.closeButton = YES;
        [editCustomEffectViewController setCubeEffect:[[self.animation.effectsList objectAtIndex:indexPath.row] copy] animated:NO];
        
        [editCustomEffectViewController setSaveBlock:^(LPCubeEffect *cubeEffect) {
            [[self.animation effectsList] replaceObjectAtIndex:indexPath.row withObject:cubeEffect];
            [self.tableView reloadData];
        }];
        
        UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:editCustomEffectViewController];
        [self presentViewController:navigationController animated:YES completion:nil];
    } else {
        UINavigationController *navCon = (UINavigationController *)[[[LPSharedManager sharedManager] splitViewControllerIpad] detailsViewController];
        LPEditCustomEffectViewController *editCustomEffectViewController = (LPEditCustomEffectViewController *)[[navCon viewControllers] objectAtIndex:0];
        [editCustomEffectViewController setCubeEffect:[[self.animation.effectsList objectAtIndex:indexPath.row] copy] animated:YES];
    }
}

- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)sourceIndexPath toIndexPath:(NSIndexPath *)destinationIndexPath
{
    if ([[self.animation effectsList] count] > 1) {
        LPCubeEffect *moveObject = [[self.animation effectsList] objectAtIndex:sourceIndexPath.row];
        
        [[self.animation effectsList] removeObjectAtIndex:sourceIndexPath.row];
        [[self.animation effectsList] insertObject:moveObject atIndex:destinationIndexPath.row];
        
        [self.tableView reloadData];
    }
}

- (void)tableView:(UITableView *)tableView willBeginEditingRowAtIndexPath:(NSIndexPath *)indexPath
{
    [self.tableView setEditing:YES animated:YES];
}

- (void)tableView:(UITableView *)tableView didEndEditingRowAtIndexPath:(NSIndexPath *)indexPath
{
    [self.tableView setEditing:NO animated:YES];
}

#pragma mark - Actions

- (void)receiveCubeEffectSave:(NSNotification *)notification
{
    if (self.selectedRow < [[self.animation effectsList] count]) {
        LPCubeEffect *cubeEffect = (LPCubeEffect *)[notification object];
        [[self.animation effectsList] replaceObjectAtIndex:self.selectedRow withObject:cubeEffect];
        [self.tableView reloadRowsAtIndexPaths:[NSArray arrayWithObject:[NSIndexPath indexPathForRow:self.selectedRow inSection:0]] withRowAnimation:UITableViewRowAnimationAutomatic];
        
        UINavigationController *navCon = (UINavigationController *)[[[LPSharedManager sharedManager] splitViewControllerIpad] detailsViewController];
        LPEditCustomEffectViewController *editCustomEffectViewController = (LPEditCustomEffectViewController *)[[navCon viewControllers] objectAtIndex:0];
        [editCustomEffectViewController setCubeEffect:nil animated:YES];
    }
}

- (void)closeButtonClicked
{
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)backButtonClicked
{
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)moveButtonClicked
{
    if ([[self.animation effectsList] count] > 0) {
        if ([self.tableView isEditing]) {
            [self.tableView setEditing:NO animated:YES];
            
            self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"MoveIcon"] style:UIBarButtonItemStyleBordered target:self action:@selector(moveButtonClicked)];
            
            self.deleteButton.enabled = YES;
            self.preview3DButton.enabled = YES;
            self.effectNewButton.enabled = YES;
            self.saveAnimationButton.enabled = YES;
        } else {
            [self.tableView setEditing:YES animated:YES];
            
            self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"MoveSelectedIcon"] style:UIBarButtonItemStyleBordered target:self action:@selector(moveButtonClicked)];
            
            self.deleteButton.enabled = NO;
            self.preview3DButton.enabled = NO;
            self.effectNewButton.enabled = NO;
            self.saveAnimationButton.enabled = NO;

            if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad) {
                self.selectedRow = INT16_MAX;
                
                UINavigationController *navCon = (UINavigationController *)[[[LPSharedManager sharedManager] splitViewControllerIpad] detailsViewController];
                LPEditCustomEffectViewController *editCustomEffectViewController = (LPEditCustomEffectViewController *)[[navCon viewControllers] objectAtIndex:0];
                [editCustomEffectViewController setCubeEffect:nil animated:YES];
            }
        }
    } else if([self.tableView isEditing]) {
        [self.tableView setEditing:NO animated:YES];
        
        self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"MoveIcon"] style:UIBarButtonItemStyleBordered target:self action:@selector(moveButtonClicked)];
        
        self.deleteButton.enabled = YES;
        self.preview3DButton.enabled = YES;
        self.effectNewButton.enabled = YES;
        self.saveAnimationButton.enabled = YES;
    }
}

- (IBAction)newEffectButtonClicked:(id)sender
{
    UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetNewEffectTitle"] delegate:self cancelButtonTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetCancelButton"] destructiveButtonTitle:[[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetNewEffectTitles"] objectAtIndex:0] otherButtonTitles:[[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetNewEffectTitles"] objectAtIndex:1], [[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetNewEffectTitles"] objectAtIndex:2], [[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetNewEffectTitles"] objectAtIndex:3], [[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetNewEffectTitles"] objectAtIndex:4], [[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetNewEffectTitles"] objectAtIndex:5], nil];
    actionSheet.accessibilityIdentifier = @"new_effect";
    [actionSheet showInView:self.view];
}

- (IBAction)saveAnimationButtonClicked:(id)sender
{
    if ([self.animation.effectsList count] == 0) {
        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
            [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationEmptyToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
        } else {
            [LPToastView toastInView:self.view withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationEmptyToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
        }
    } else {
        if (self.saveBlockOnly) {
            if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationSavedToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
            } else {
                [LPToastView toastInView:self.view withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationSavedToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
            }
            
            if (self.backButton) {
                [self.navigationController popViewControllerAnimated:YES];
            }
            
            if (self.closeButton) {
                [self dismissViewControllerAnimated:YES completion:nil];
            }
            
            if (self.saveBlock)
                self.saveBlock(self.animation);
        } else {
            NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:@"ftp://%@:%@@%@/%@", [LPSharedManager ftpUsername], [LPSharedManager ftpPassword], [[LPSharedManager sharedManager] selectedIP], self.animation.fileName]];
            
            CFWriteStreamRef stream = CFWriteStreamCreateWithFTPURL(NULL, (__bridge CFURLRef) url);
            self.outputStream = (__bridge_transfer NSOutputStream *)stream;
            [self.outputStream open];
            
            NSInteger nwritten = [self.outputStream write:[self.animation getBytes] maxLength:[self.animation getBytesLength]];
            
            if (nwritten == -1) {
                NSLog(@"Error writing to stream: %@", [self.outputStream streamError]);
                
                if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                    [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"CanNotConnectToHostToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                } else {
                    [LPToastView toastInView:self.view withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"CanNotConnectToHostToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                }
            } else {
                NSLog(@"Wrote %lld bytes to stream", (long long)nwritten);
                
                if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                    [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationSavedToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                } else {
                    [LPToastView toastInView:self.view withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationSavedToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
                }

                if (self.backButton) {
                    [self.navigationController popViewControllerAnimated:YES];
                }
                
                if (self.closeButton) {
                    [self dismissViewControllerAnimated:YES completion:nil];
                }
                
                if (self.saveBlock)
                    self.saveBlock(self.animation);
            }
            
            [self.outputStream close];
            self.outputStream = nil;
        }
    }
}

- (IBAction)deleteButtonClicked:(id)sender
{
    if ([[self.animation effectsList] count] > 0) {
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewClearListAnimationsTitle"] message:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewClearListAnimationsMessage"] delegate:self cancelButtonTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewCancelButton"] otherButtonTitles:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewClearButton"], nil];
        alertView.accessibilityIdentifier = @"clear_list";
        [alertView show];
    }
}

- (IBAction)Preview3DButtonClicked:(id)sender
{
    if ([self.animation.effectsList count] > 0) {
        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
            LPPreview3DViewController *preview3DViewController = [[LPPreview3DViewController alloc] initWithNibName:@"LPPreview3DViewController" bundle:nil];
            preview3DViewController.closeButton = YES;
            preview3DViewController.animation = self.animation;
            UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:preview3DViewController];
            [self presentViewController:navigationController animated:YES completion:nil];
        } else {
            LPPreview3DViewController *preview3DViewController = [[LPPreview3DViewController alloc] initWithNibName:@"LPPreview3DViewController" bundle:nil];
            preview3DViewController.closeButton = YES;
            preview3DViewController.animation = self.animation;
            UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:preview3DViewController];
            [[[LPSharedManager sharedManager] splitViewControllerIpad] showModalViewController:navigationController animated:YES];
        }
    } else {
        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
            [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationEmptyToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
        } else {
            [LPToastView toastInView:self.view withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AnimationEmptyToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
        }
    }
}

#pragma mark - UIActionSheetDelegate

- (void)actionSheetFunctionSelect
{
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad) {
        self.selectedRow = INT16_MAX;
        
        UINavigationController *navCon = (UINavigationController *)[[[LPSharedManager sharedManager] splitViewControllerIpad] detailsViewController];
        LPEditCustomEffectViewController *editCustomEffectViewController = (LPEditCustomEffectViewController *)[[navCon viewControllers] objectAtIndex:0];
        [editCustomEffectViewController setCubeEffect:nil animated:YES];
    }
}

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if ([actionSheet.accessibilityIdentifier isEqualToString:@"new_effect"]) {
        uint8_t effectFunction = (uint8_t)buttonIndex;
        
        if (effectFunction == 0) { // Append saved effect
            if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                LPSavedAnimationsListViewController *savedAnimationsListViewController = [[LPSavedAnimationsListViewController alloc] initWithNibName:@"LPSavedAnimationsListViewController" bundle:nil];
                savedAnimationsListViewController.closeButton = YES;
                savedAnimationsListViewController.canAppend = YES;
                
                [savedAnimationsListViewController setAppendBlock:^(LPAnimation *animation) {
                    [self.animation.effectsList addObjectsFromArray:animation.effectsList];
                }];
                UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:savedAnimationsListViewController];
                
                [self presentViewController:navigationController animated:YES completion:nil];
            } else {
                LPSavedAnimationsListViewController *savedAnimationsListViewController = [[LPSavedAnimationsListViewController alloc] initWithNibName:@"LPSavedAnimationsListViewController" bundle:nil];
                savedAnimationsListViewController.backButton = YES;
                savedAnimationsListViewController.canAppend = YES;
                
                [savedAnimationsListViewController setAppendBlock:^(LPAnimation *animation) {
                    [self.animation.effectsList addObjectsFromArray:animation.effectsList];
                }];

                [self.navigationController pushViewController:savedAnimationsListViewController animated:YES];
            }
        } else if (effectFunction == 1) { // Custom
            if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                LPNewCustomEffectViewController *newCustomEffectViewController = [[LPNewCustomEffectViewController alloc] initWithNibName:@"LPNewCustomEffectViewController" bundle:nil];
                newCustomEffectViewController.closeButton = YES;
                
                [newCustomEffectViewController setSaveBlock:^(LPCubeEffect *cubeEffect) {
                    [[self.animation effectsList] addObject:cubeEffect];
                    [self.tableView reloadData];
                    [self.tableView scrollToRowAtIndexPath:[NSIndexPath indexPathForRow:([[self.animation effectsList] count] - 1) inSection:0] atScrollPosition:UITableViewScrollPositionBottom animated:YES];
                }];
                
                UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:newCustomEffectViewController];
                [self presentViewController:navigationController animated:YES completion:nil];
            } else {
                [self actionSheetFunctionSelect];
                
                LPNewCustomEffectViewController *newCustomEffectViewController = [[LPNewCustomEffectViewController alloc] initWithNibName:@"LPNewCustomEffectViewController" bundle:nil];
                newCustomEffectViewController.closeButton = YES;
                
                [newCustomEffectViewController setSaveBlock:^(LPCubeEffect *cubeEffect) {
                    [[self.animation effectsList] addObject:cubeEffect];
                    [self.tableView reloadData];
                    [self.tableView scrollToRowAtIndexPath:[NSIndexPath indexPathForRow:([[self.animation effectsList] count] - 1) inSection:0] atScrollPosition:UITableViewScrollPositionBottom animated:YES];
                }];
                
                UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:newCustomEffectViewController];
                [[[LPSharedManager sharedManager] splitViewControllerIpad] showModalViewController:navigationController animated:YES];
            }
        } else if (effectFunction == 2) { // Front Text
            if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                LPNewTextEffectViewController *newTextEffectViewController = [[LPNewTextEffectViewController alloc] initWithNibName:@"LPNewTextEffectViewController" bundle:nil];
                newTextEffectViewController.function = 0;
                
                [newTextEffectViewController setSaveBlock:^(NSMutableArray *arrayEffects) {
                    [self.animation.effectsList addObjectsFromArray:arrayEffects];
                    
                    [self.tableView reloadData];
                }];
                
                UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:newTextEffectViewController];
                [self presentViewController:navigationController animated:YES completion:nil];
            } else {
                [self actionSheetFunctionSelect];
                
                LPNewTextEffectViewController *newTextEffectViewController = [[LPNewTextEffectViewController alloc] initWithNibName:@"LPNewTextEffectViewController" bundle:nil];
                newTextEffectViewController.function = 0;

                [newTextEffectViewController setSaveBlock:^(NSMutableArray *arrayEffects) {
                    [self.animation.effectsList addObjectsFromArray:arrayEffects];
                    
                    [self.tableView reloadData];
                }];
                
                UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:newTextEffectViewController];
                [[[LPSharedManager sharedManager] splitViewControllerIpad] showModalViewController:navigationController animated:YES];
            }
        } else if (effectFunction == 3) { // Move Belt Left Text
            if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                LPNewTextEffectViewController *newTextEffectViewController = [[LPNewTextEffectViewController alloc] initWithNibName:@"LPNewTextEffectViewController" bundle:nil];
                newTextEffectViewController.function = 1;
                
                [newTextEffectViewController setSaveBlock:^(NSMutableArray *arrayEffects) {
                    [self.animation.effectsList addObjectsFromArray:arrayEffects];
                    
                    [self.tableView reloadData];
                }];
                
                UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:newTextEffectViewController];
                [self presentViewController:navigationController animated:YES completion:nil];
            } else {
                [self actionSheetFunctionSelect];
                
                LPNewTextEffectViewController *newTextEffectViewController = [[LPNewTextEffectViewController alloc] initWithNibName:@"LPNewTextEffectViewController" bundle:nil];
                newTextEffectViewController.function = 1;
                
                [newTextEffectViewController setSaveBlock:^(NSMutableArray *arrayEffects) {
                    [self.animation.effectsList addObjectsFromArray:arrayEffects];
                    
                    [self.tableView reloadData];
                }];
                
                UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:newTextEffectViewController];
                [[[LPSharedManager sharedManager] splitViewControllerIpad] showModalViewController:navigationController animated:YES];
            }
        } else if (effectFunction == 4) { // Waves
            if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                LPNewDefaultEffectViewController *newDefaultEffectViewController = [[LPNewDefaultEffectViewController alloc] initWithNibName:@"LPNewDefaultEffectViewController" bundle:nil];
                newDefaultEffectViewController.function = 0;
                
                [newDefaultEffectViewController setSaveBlock:^(NSMutableArray *arrayEffects) {
                    [self.animation.effectsList addObjectsFromArray:arrayEffects];
                    
                    [self.tableView reloadData];
                }];
                
                UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:newDefaultEffectViewController];
                [self presentViewController:navigationController animated:YES completion:nil];
            } else {
                [self actionSheetFunctionSelect];
                
                LPNewDefaultEffectViewController *newDefaultEffectViewController = [[LPNewDefaultEffectViewController alloc] initWithNibName:@"LPNewDefaultEffectViewController" bundle:nil];
                newDefaultEffectViewController.function = 0;
                
                [newDefaultEffectViewController setSaveBlock:^(NSMutableArray *arrayEffects) {
                    [self.animation.effectsList addObjectsFromArray:arrayEffects];
                    
                    [self.tableView reloadData];
                }];

                UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:newDefaultEffectViewController];
                [[[LPSharedManager sharedManager] splitViewControllerIpad] showModalViewController:navigationController animated:YES];
            }
        } else if (effectFunction == 5) { // Cubes 4
            if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                LPNewDefaultEffectViewController *newDefaultEffectViewController = [[LPNewDefaultEffectViewController alloc] initWithNibName:@"LPNewDefaultEffectViewController" bundle:nil];
                newDefaultEffectViewController.function = 1;
                
                [newDefaultEffectViewController setSaveBlock:^(NSMutableArray *arrayEffects) {
                    [self.animation.effectsList addObjectsFromArray:arrayEffects];
                    
                    [self.tableView reloadData];
                }];
                
                UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:newDefaultEffectViewController];
                [self presentViewController:navigationController animated:YES completion:nil];
            } else {
                [self actionSheetFunctionSelect];
                
                LPNewDefaultEffectViewController *newDefaultEffectViewController = [[LPNewDefaultEffectViewController alloc] initWithNibName:@"LPNewDefaultEffectViewController" bundle:nil];
                newDefaultEffectViewController.function = 1;
                
                [newDefaultEffectViewController setSaveBlock:^(NSMutableArray *arrayEffects) {
                    [self.animation.effectsList addObjectsFromArray:arrayEffects];
                    
                    [self.tableView reloadData];
                }];
                
                UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:newDefaultEffectViewController];
                [[[LPSharedManager sharedManager] splitViewControllerIpad] showModalViewController:navigationController animated:YES];
            }
        }
    }
}

#pragma mark - UIAlertViewDelegate

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if ([alertView.accessibilityIdentifier isEqualToString:@"clear_list"]) {
        if (buttonIndex == 1) {
            self.selectedRow = INT16_MAX;
            
            [[self.animation effectsList] removeAllObjects];
            [self.tableView reloadData];
            
            if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad) {
                UINavigationController *navCon = (UINavigationController *)[[[LPSharedManager sharedManager] splitViewControllerIpad] detailsViewController];
                LPEditCustomEffectViewController *editCustomEffectViewController = (LPEditCustomEffectViewController *)[[navCon viewControllers] objectAtIndex:0];
                [editCustomEffectViewController setCubeEffect:nil animated:YES];
            }
        }
    }
}

@end
