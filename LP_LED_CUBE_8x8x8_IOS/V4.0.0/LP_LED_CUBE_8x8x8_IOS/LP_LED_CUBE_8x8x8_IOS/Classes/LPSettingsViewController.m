//
//  LPSettingsViewController.m
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 30/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPSettingsViewController.h"


#define MAXLENGTH_DEVICE_NAME       40
#define MAXLENGTH_IP                15

#define DEVICE_FILE_NAME            @"device.settings"


@interface LPSettingsViewController ()

@property (nonatomic, strong) NSOutputStream *outputStream;

@end


@implementation LPSettingsViewController


#pragma mark - Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.title = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SettingsTitle"];
    
    if (self.backButton) {
        self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"BackButton"] style:UIBarButtonItemStyleBordered target:self action:@selector(backButtonClicked)];
    }
    
    if (self.closeButton) {
        self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"CloseButton"] style:UIBarButtonItemStyleBordered target:self action:@selector(closeButtonClicked)];
    }
    
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"SaveIcon"] style:UIBarButtonItemStyleBordered target:self action:@selector(saveButtonClicked)];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillHide:) name:UIKeyboardWillHideNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillShow:) name:UIKeyboardWillShowNotification object:nil];
    
    [self.tableView reloadData];
}

- (LPDeviceSettings *)deviceSettings
{
    if (!_deviceSettings) {
        _deviceSettings = [LPDeviceSettings new];
    }
    
    return _deviceSettings;
}

#pragma mark - Keyboard Notifications

- (void)keyboardWillHide:(NSNotification*)notification
{
    self.tableView.contentInset = UIEdgeInsetsMake(0.0f, 0.0f, 0.0f, 0.0f);
}

- (void)keyboardWillShow:(NSNotification*)notification
{
    NSDictionary *keyboardInfo = [notification userInfo];
    NSValue *keyboardFrameBegin = [keyboardInfo valueForKey:UIKeyboardFrameBeginUserInfoKey];
    CGRect keyboardFrameBeginRect = [keyboardFrameBegin CGRectValue];
    
    self.tableView.contentInset = UIEdgeInsetsMake(0.0f, 0.0f, keyboardFrameBeginRect.size.height, 0.0f);
}

#pragma mark - Actions

- (void)backButtonClicked
{
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)closeButtonClicked
{
    [self.view endEditing:YES];
    
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        [self dismissViewControllerAnimated:YES completion:nil];
    } else {
        [[[LPSharedManager sharedManager] splitViewControllerIpad] hideModalViewControllerAnimated:YES];
    }
}

- (void)saveButtonClicked
{
    [self.view endEditing:YES];
    
    BOOL state = YES;
    
    if (![self isValidIpAddress:self.deviceSettings.ipAddress]) {
        state = NO;
    }
    
    if (![self isValidIpAddress:self.deviceSettings.subnetMask]) {
        state = NO;
    }
    
    if (![self isValidIpAddress:self.deviceSettings.defaultGatewayAddress]) {
        state = NO;
    }
    
    if (![self isValidIpAddress:self.deviceSettings.priDNSAddress]) {
        state = NO;
    }
    
    if (![self isValidIpAddress:self.deviceSettings.secDNSAddress]) {
        state = NO;
    }
    
    if (state) {
        NSMutableArray *strings = [self.deviceSettings getFileStrings];
        
        NSString *linedStrings = [strings componentsJoinedByString:@"\n"];
        
        NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:@"ftp://%@:%@@%@/%@", [LPSharedManager ftpUsername], [LPSharedManager ftpPassword], [[LPSharedManager sharedManager] selectedIP], DEVICE_FILE_NAME]];

        CFWriteStreamRef stream = CFWriteStreamCreateWithFTPURL(NULL, (__bridge CFURLRef) url);
        self.outputStream = (__bridge_transfer NSOutputStream *)stream;
        [self.outputStream open];
        
        NSInteger nwritten = [self.outputStream write:(const uint8_t *)[linedStrings UTF8String] maxLength:[linedStrings length]];
        
        if (nwritten == -1) {
            NSLog(@"Error writing to stream: %@", [self.outputStream streamError]);
            
            if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"CanNotConnectToHostToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
            } else {
                [LPToastView toastInView:self.view withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"CanNotConnectToHostToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
            }
        } else {
            NSLog(@"Wrote %lld bytes to stream", (long long)nwritten);
     
            [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SettingsSavedToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];

            if (self.backButton) {
                [self.navigationController popViewControllerAnimated:YES];
            }
            
            if (self.closeButton) {
                if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                    [self dismissViewControllerAnimated:YES completion:nil];
                } else {
                    [[[LPSharedManager sharedManager] splitViewControllerIpad] hideModalViewControllerAnimated:YES];
                }
            }
        }

        [self.outputStream close];
        self.outputStream = nil;
    } else {
        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
            [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SettingsEnterCorrectDataToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
        } else {
            [LPToastView toastInView:self.view withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SettingsEnterCorrectDataToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
        }
    }
}

#pragma mark - UITableViewDataSource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return 12;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    switch (indexPath.row) {
        case 0:
        {
            LPHeaderCellView *cell = [LPHeaderCellView cellFromNibNamed:@"LPHeaderCellView"];
            
            cell.topLineView.hidden = NO;
            
            cell.rightLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SettingsGeneralHeaderTitle"];
            cell.leftImageView.image = [UIImage imageNamed:@"GeneralIcon"];
            
            return cell;
        }
        case 1:
        {
            LPTextFieldCellView *cell = [LPTextFieldCellView cellFromNibNamed:@"LPTextFieldCellView"];
            
            cell.leftLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SettingsDeviceNameLabelTitle"];
            
            cell.rightTextField.accessibilityIdentifier = @"device_name";
            cell.rightTextField.placeholder = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SettingsDeviceNameTextFieldPlaceholder"];
            cell.rightTextField.delegate = self;
            
            [cell.rightTextField setEditingChangedBlock:^(UITextField *textField) {
                self.deviceSettings.deviceName = textField.text;
            }];
            
            cell.rightTextField.text = self.deviceSettings.deviceName;
            
            return cell;
        }
        case 2:
        {
            LPHeaderCellView *cell = [LPHeaderCellView cellFromNibNamed:@"LPHeaderCellView"];
            
            cell.rightLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SettingsNetworkHeaderTitle"];
            cell.leftImageView.image = [UIImage imageNamed:@"NetworkIcon"];
            
            return cell;
        }
        case 3:
        {
            LPSwitchCellView *cell = [LPSwitchCellView cellFromNibNamed:@"LPSwitchCellView"];
            
            cell.leftLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SettingsDHCPLabelTitle"];
            
            [cell.rightSwitch setValueChangedBlock:^(UISwitch *swi) {
                self.deviceSettings.dhcpEnabled = swi.on;
            }];
            
            cell.rightSwitch.on = self.deviceSettings.dhcpEnabled;
            
            return cell;
        }
        case 4:
        {
            LPTextFieldCellView *cell = [LPTextFieldCellView cellFromNibNamed:@"LPTextFieldCellView"];
            
            cell.leftLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SettingsIPAddressLabelTitle"];
            
            cell.rightTextField.accessibilityIdentifier = @"ip_mask";
            cell.rightTextField.placeholder = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SettingsIPAddressTextFieldPlaceholder"];
            cell.rightTextField.delegate = self;
            cell.rightTextField.keyboardType = UIKeyboardTypeNumbersAndPunctuation;
            
            [cell.rightTextField setEditingChangedBlock:^(UITextField *textField) {
                if ([self isValidIpAddress:textField.text]) {
                    textField.textColor = [UIColor blackColor];
                } else {
                    textField.textColor = [UIColor redColor];
                }
                
                self.deviceSettings.ipAddress = textField.text;
            }];
            
            cell.rightTextField.text = self.deviceSettings.ipAddress;
            
            if ([self isValidIpAddress:cell.rightTextField.text]) {
                cell.rightTextField.textColor = [UIColor blackColor];
            } else {
                cell.rightTextField.textColor = [UIColor redColor];
            }
            
            return cell;
        }
        case 5:
        {
            LPTextFieldCellView *cell = [LPTextFieldCellView cellFromNibNamed:@"LPTextFieldCellView"];
            
            cell.leftLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SettingsSubnetMaskLabelTitle"];
            
            cell.rightTextField.accessibilityIdentifier = @"ip_mask";
            cell.rightTextField.placeholder = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SettingsSubnetMaskTextFieldPlaceholder"];
            cell.rightTextField.delegate = self;
            cell.rightTextField.keyboardType = UIKeyboardTypeNumbersAndPunctuation;
            
            [cell.rightTextField setEditingChangedBlock:^(UITextField *textField) {
                if ([self isValidIpAddress:textField.text]) {
                    textField.textColor = [UIColor blackColor];
                } else {
                    textField.textColor = [UIColor redColor];
                }
                
                self.deviceSettings.subnetMask = textField.text;
            }];
            
            cell.rightTextField.text = self.deviceSettings.subnetMask;
            
            if ([self isValidIpAddress:cell.rightTextField.text]) {
                cell.rightTextField.textColor = [UIColor blackColor];
            } else {
                cell.rightTextField.textColor = [UIColor redColor];
            }
            
            return cell;
        }
        case 6:
        {
            LPTextFieldCellView *cell = [LPTextFieldCellView cellFromNibNamed:@"LPTextFieldCellView"];
            
            cell.leftLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SettingsDefaultGatewayLabelTitle"];
            
            cell.rightTextField.accessibilityIdentifier = @"ip_mask";
            cell.rightTextField.placeholder = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SettingsDefaultGatewayTextFieldPlaceholder"];
            cell.rightTextField.delegate = self;
            cell.rightTextField.keyboardType = UIKeyboardTypeNumbersAndPunctuation;
            
            [cell.rightTextField setEditingChangedBlock:^(UITextField *textField) {
                if ([self isValidIpAddress:textField.text]) {
                    textField.textColor = [UIColor blackColor];
                } else {
                    textField.textColor = [UIColor redColor];
                }
                
                self.deviceSettings.defaultGatewayAddress = textField.text;
            }];
            
            cell.rightTextField.text = self.deviceSettings.defaultGatewayAddress;
            
            if ([self isValidIpAddress:cell.rightTextField.text]) {
                cell.rightTextField.textColor = [UIColor blackColor];
            } else {
                cell.rightTextField.textColor = [UIColor redColor];
            }
            
            return cell;
        }
        case 7:
        {
            LPTextFieldCellView *cell = [LPTextFieldCellView cellFromNibNamed:@"LPTextFieldCellView"];
            
            cell.leftLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SettingsPriDNSAddressLabelTitle"];
            
            cell.rightTextField.accessibilityIdentifier = @"ip_mask";
            cell.rightTextField.placeholder = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SettingsPriDNSAddressTextFieldPlaceholder"];
            cell.rightTextField.delegate = self;
            cell.rightTextField.keyboardType = UIKeyboardTypeNumbersAndPunctuation;
            
            [cell.rightTextField setEditingChangedBlock:^(UITextField *textField) {
                if ([self isValidIpAddress:textField.text]) {
                    textField.textColor = [UIColor blackColor];
                } else {
                    textField.textColor = [UIColor redColor];
                }
                
                self.deviceSettings.priDNSAddress = textField.text;
            }];
            
            cell.rightTextField.text = self.deviceSettings.priDNSAddress;
            
            if ([self isValidIpAddress:cell.rightTextField.text]) {
                cell.rightTextField.textColor = [UIColor blackColor];
            } else {
                cell.rightTextField.textColor = [UIColor redColor];
            }
            
            return cell;
        }
        case 8:
        {
            LPTextFieldCellView *cell = [LPTextFieldCellView cellFromNibNamed:@"LPTextFieldCellView"];
            
            cell.leftLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SettingsSecDNSAddressLabelTitle"];
            
            cell.rightTextField.accessibilityIdentifier = @"ip_mask";
            cell.rightTextField.placeholder = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SettingsSecDNSAddressTextFieldPlaceholder"];
            cell.rightTextField.delegate = self;
            cell.rightTextField.keyboardType = UIKeyboardTypeNumbersAndPunctuation;
            
            [cell.rightTextField setEditingChangedBlock:^(UITextField *textField) {
                if ([self isValidIpAddress:textField.text]) {
                    textField.textColor = [UIColor blackColor];
                } else {
                    textField.textColor = [UIColor redColor];
                }
                
                self.deviceSettings.secDNSAddress = textField.text;
            }];
            
            cell.rightTextField.text = self.deviceSettings.secDNSAddress;
            
            if ([self isValidIpAddress:cell.rightTextField.text]) {
                cell.rightTextField.textColor = [UIColor blackColor];
            } else {
                cell.rightTextField.textColor = [UIColor redColor];
            }
            
            return cell;
        }
        case 9:
        {
            LPHeaderCellView *cell = [LPHeaderCellView cellFromNibNamed:@"LPHeaderCellView"];
            
            cell.rightLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SettingsInfoHeaderTitle"];
            cell.leftImageView.image = [UIImage imageNamed:@"Info1Icon"];

            return cell;
        }
        case 10:
        {
            LPTextFieldCellView *cell = [LPTextFieldCellView cellFromNibNamed:@"LPTextFieldCellView"];
            
            cell.leftLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SettingsFirmwareVersionLabelTitle"];
            
            cell.rightTextField.enabled = NO;

            cell.rightTextField.text = self.deviceSettings.firmwareVersion;
            
            return cell;
        }
        case 11:
        {
            LPTextFieldCellView *cell = [LPTextFieldCellView cellFromNibNamed:@"LPTextFieldCellView"];
            
            cell.leftLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"SettingsMACAddressLabelTitle"];
            
            cell.rightTextField.enabled = NO;
            
            cell.rightTextField.text = self.deviceSettings.macAddress;
            
            return cell;
        }
    }
    
    return nil;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 60.0f;
}

#pragma mark - UITableViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [self.tableView deselectRowAtIndexPath:indexPath animated:YES];
}

#pragma mark - UITextFieldDelegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    return YES;
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    if ([textField.accessibilityIdentifier isEqualToString:@"device_name"]) {
        int length = (int)[textField.text length];
        if (length >= MAXLENGTH_DEVICE_NAME && ![string isEqualToString:@""]) {
            textField.text = [textField.text substringToIndex:MAXLENGTH_DEVICE_NAME];
            return NO;
        }
    } else if ([textField.accessibilityIdentifier isEqualToString:@"ip_mask"]) {
        int length = (int)[textField.text length];
        if (length >= MAXLENGTH_IP && ![string isEqualToString:@""]) {
            textField.text = [textField.text substringToIndex:MAXLENGTH_IP];
            return NO;
        }
    }
    return YES;
}

- (BOOL)isValidIpAddress:(NSString *)ip
{
    if (!ip || ip.length == 0) return NO;
    
    const char *utf8 = [ip UTF8String];
    
    // Check valid IPv4.
    struct in_addr dst;
    int success = inet_pton(AF_INET, utf8, &(dst.s_addr));
    if (success != 1) {
        // Check valid IPv6.
        struct in6_addr dst6;
        success = inet_pton(AF_INET6, utf8, &dst6);
    }
    
    return (success == 1);
}

@end
