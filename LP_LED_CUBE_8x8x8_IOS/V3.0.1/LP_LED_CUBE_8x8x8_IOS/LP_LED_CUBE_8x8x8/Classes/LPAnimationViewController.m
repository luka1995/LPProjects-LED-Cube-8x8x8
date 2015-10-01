//
//  LPAnimationViewController.m
//  LP_LED_CUBE_8x8x8
//
//  Created by Luka Penger on 20/06/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPAnimationViewController.h"


@interface LPAnimationViewController ()

@property (nonatomic, strong) MBProgressHUD *progressHUD;
@property (nonatomic, strong) NSOutputStream *outputStream;

@end


@implementation LPAnimationViewController

#pragma mark - Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.title = self.animation.fileName;
    
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Move" style:UIBarButtonItemStyleBordered target:self action:@selector(buttonEditClicked:)];
    
    self.tableView.separatorInset = UIEdgeInsetsMake(0.0f, 0.0f, 0.0f, 0.0f);
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}

- (void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];
}

- (void)showLoadingSaveAnimation
{
    if (!self.progressHUD) {
        self.progressHUD = [MBProgressHUD showHUDAddedTo:[UIApplication sharedApplication].delegate.window animated:YES];
        
        self.progressHUD.labelText = @"Saving...";
        self.progressHUD.labelFont = [UIFont boldSystemFontOfSize:14];
    }
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
    return 84.0f;
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
    LPCubeEffectCellView *cell = [LPCubeEffectCellView cellFromNibNamed:@"LPCubeEffectCellView"];
    
    LPCubeEffect *cubeEffect = (LPCubeEffect *)[[self.animation effectsList] objectAtIndex:indexPath.row];
    
    [cell setColumnsBytes:cubeEffect.columns];
    [cell setRowsBytes:cubeEffect.rows];
    [cell.titleLabel setText:cubeEffect.name];
    [cell.delayLabel setText:[NSString stringWithFormat:@"Delay: %d x 10ms", cubeEffect.delay]];
    [cell.numLabel setText:[NSString stringWithFormat:@"%d", (indexPath.row + 1)]];
    
    return cell;
}

#pragma mark - UITableViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [self.tableView deselectRowAtIndexPath:indexPath animated:NO];

    selectedRow = indexPath.row;
    
    UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:nil delegate:self cancelButtonTitle:@"Cancel" destructiveButtonTitle:@"Delete" otherButtonTitles:@"Edit", @"Copy", nil];
    [actionSheet showInView:self.view];
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
    [self.navigationItem.rightBarButtonItem setTitle:@"Done"];
    [self.tableView setEditing:YES animated:YES];
}

- (void)tableView:(UITableView *)tableView didEndEditingRowAtIndexPath:(NSIndexPath *)indexPath
{
    [self.navigationItem.rightBarButtonItem setTitle:@"Move"];
    [self.tableView setEditing:NO animated:YES];
}

#pragma mark - Actions

- (void)buttonEditClicked:(id)sender
{
    if([[self.animation effectsList] count] > 0)
    {
        if ([self.tableView isEditing]) {
            [self.navigationItem.rightBarButtonItem setTitle:@"Edit"];
            [self.tableView setEditing:NO animated:YES];
        } else {
            [self.navigationItem.rightBarButtonItem setTitle:@"Done"];
            [self.tableView setEditing:YES animated:YES];
        }
    } else if([self.tableView isEditing]) {
        [self.navigationItem.rightBarButtonItem setTitle:@"Edit"];
        [self.tableView setEditing:NO animated:YES];
    }
}

- (IBAction)addEffectButtonClicked:(id)sender
{
    LPNewEffectViewController *newEffectViewController = [[LPNewEffectViewController alloc] initWithNibName:@"LPNewEffectViewController_iPhone" bundle:nil];
    
    [newEffectViewController setCancelBlock:^{
        
    }];
    
    [newEffectViewController setAddBlock:^(LPCubeEffect *cubeEffect) {
        [[self.animation effectsList] addObject:cubeEffect];
        [self.tableView reloadData];
        [self.tableView scrollToRowAtIndexPath:[NSIndexPath indexPathForRow:([[self.animation effectsList] count] - 1) inSection:0] atScrollPosition:UITableViewScrollPositionBottom animated:YES];
    }];
    
    UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:newEffectViewController];
    [self presentViewController:navigationController animated:YES completion:^{
        
    }];
}

- (IBAction)saveAnimationButtonClicked:(id)sender
{
    NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:@"ftp://%@:%@@%@/%@", [[LPSharedManager sharedManager] ftpUsername], [[LPSharedManager sharedManager] ftpPassword], [[LPSharedManager sharedManager] selectedIP], self.animation.fileName]];
    
    CFWriteStreamRef stream = CFWriteStreamCreateWithFTPURL(NULL, (__bridge CFURLRef) url);
    
    self.outputStream = (__bridge_transfer NSOutputStream *)stream;

    [self.outputStream open];

    NSInteger nwritten = [self.outputStream write:[self.animation getBytes] maxLength:[self.animation getBytesLength]];
    
    if (nwritten == -1) {
        NSLog(@"Error writing to stream: %@", [self.outputStream streamError]);
        
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"Error" message:@"Can not connect to the host! Try again" delegate:nil cancelButtonTitle:@"Cancel" otherButtonTitles:nil, nil];
        [alertView show];
    } else {
        NSLog(@"Wrote %lld bytes to stream", (long long)nwritten);

        [self.navigationController popViewControllerAnimated:YES];
        
        if (self.saveBlock)
            self.saveBlock(self.animation);
    }
}

- (IBAction)deleteButtonClicked:(id)sender
{
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"Clear List" message:@"Are you sure you want to clear list?" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Clear", nil];
    alertView.accessibilityIdentifier = @"clearlist";
    [alertView show];
}

#pragma mark - UIAlertViewDelegate

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if ([alertView.accessibilityIdentifier isEqualToString:@"clearlist"]) {
        if (buttonIndex == 1) {
            [[self.animation effectsList] removeAllObjects];
            [self.tableView reloadData];
        }
    }
}

#pragma mark - UIActionSheetDelegate

- (void)actionSheetCancel:(UIActionSheet *)actionSheet
{
    
}

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 0) {
        [[self.animation effectsList] removeObjectAtIndex:selectedRow];
        
        [self.tableView reloadData];
    } else if (buttonIndex == 1) {
        LPEditEffectViewController *editEffectViewController = [[LPEditEffectViewController alloc] initWithNibName:@"LPEditEffectViewController_iPhone" bundle:nil];
        [editEffectViewController setCubeEffect:[[self.animation effectsList] objectAtIndex:selectedRow]];
        
        [editEffectViewController setCancelBlock:^{
            
        }];

        [editEffectViewController setSaveBlock:^(LPCubeEffect *cubeEffect) {
            [[self.animation effectsList] replaceObjectAtIndex:selectedRow withObject:cubeEffect];
            [self.tableView reloadData];
        }];
        
        UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:editEffectViewController];
        [self presentViewController:navigationController animated:YES completion:^{
            
        }];
    } else if (buttonIndex == 2) {
        LPCubeEffect *object = (LPCubeEffect *)[[self.animation effectsList] objectAtIndex:selectedRow];
        
        LPCubeEffect *copyObject = [object copy];

        NSString *copyText = @"(C)";
        
        if (![copyObject.name hasSuffix:copyText]) {
            if ([copyObject.name isEqualToString:@""]) {
                copyObject.name = copyText;
            } else {
                if ([copyObject.name length] + [copyText length] <= 20) {
                    copyObject.name = [NSString stringWithFormat:@"%@ %@", copyObject.name, copyText];
                } else {
                    copyObject.name = [NSString stringWithFormat:@"%@ %@", [copyObject.name substringToIndex:16], copyText];
                }
            }
        }
        
        [[self.animation effectsList] addObject:copyObject];
        
        [self.tableView insertRowsAtIndexPaths:[NSArray arrayWithObject:[NSIndexPath indexPathForRow:([[self.animation effectsList] count] - 1) inSection:0]] withRowAnimation:UITableViewRowAnimationAutomatic];
        
        [self.tableView scrollToRowAtIndexPath:[NSIndexPath indexPathForRow:([[self.animation effectsList] count] - 1) inSection:0] atScrollPosition:UITableViewScrollPositionBottom animated:YES];
    }
}

@end
