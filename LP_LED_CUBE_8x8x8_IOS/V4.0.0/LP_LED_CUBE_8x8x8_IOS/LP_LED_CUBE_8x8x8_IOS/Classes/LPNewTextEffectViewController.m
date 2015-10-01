//
//  LPNewTextEffectViewController.m
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 13/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPNewTextEffectViewController.h"


#define MAXLENGTH_NAME 20
#define MAXLENGTH_TEXT 40


@interface LPNewTextEffectViewController ()

@property (nonatomic, assign) int selectedDelayUnit;

@end


@implementation LPNewTextEffectViewController

#pragma mark - Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.title = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"NewTextEffectViewTitle"];
    
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"CloseButton"] style:UIBarButtonItemStyleBordered target:self action:@selector(closeButtonClicked)];
    
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"SaveIcon"] style:UIBarButtonItemStyleBordered target:self action:@selector(saveButtonClicked)];

    self.textLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"EffectTextLabelText"];
    self.delayLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"EffectDelayLabelText"];
    self.textTextField.placeholder = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"EffectTextTextFieldPlaceholder"];
    self.nameLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"EffectNameLabelText"];
    self.nameTextField.placeholder = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"EffectNameTextFieldPlaceholder"];
    
    self.delaySlider.value = 10;
    [self delaySliderValueChanged:nil];
    
    self.selectedDelayUnit = 1;
    [self delayUnitButtonSet:self.selectedDelayUnit];
}

#pragma mark - Actions

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
    
    if (self.nameTextField.text.length > 0) {
        if (self.textTextField.text.length > 0) {
            NSMutableArray *effects = [NSMutableArray new];
            
            if (self.function == 0) {
                NSMutableArray *array = [LPAnimations getArrayStringFrontText:self.textTextField.text delay:self.delaySlider.value delayUnit:self.selectedDelayUnit effectName:self.nameTextField.text];
                
                [effects addObjectsFromArray:array];
            } else if (self.function == 1) {
                NSMutableArray *array = [LPAnimations getArrayStringBeltLeftText:self.textTextField.text delay:self.delaySlider.value delayUnit:self.selectedDelayUnit effectName:self.nameTextField.text];
                
                [effects addObjectsFromArray:array];
            }
            
            if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
                [self dismissViewControllerAnimated:YES completion:nil];
            } else {
                [[[LPSharedManager sharedManager] splitViewControllerIpad] hideModalViewControllerAnimated:YES];
            }
            
            if (self.saveBlock)
                self.saveBlock(effects);
        } else {
            [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"TextEffectTextFieldEmptyToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
        }
    } else {
        [LPToastView toastInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] withText:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"NameEffectTextFieldEmptyToastText"] withPaddingBottom:[LPSharedManager toastViewPadding]];
    }
}

- (void)delaySliderValueChanged:(id)sender
{
    int delay = (int)self.delaySlider.value;
    
    self.delayValueLabel.text = [NSString stringWithFormat:@"%d", delay];
    
    if (delay == self.delaySlider.minimumValue) {
        self.minusDelayButton.enabled = NO;
        self.minusDelayButton.backgroundColor = [UIColor colorWithRed:(50.0/255.0) green:(50.0/255.0) blue:(50.0/255.0) alpha:1.0f];
        
        self.plusDelayButton.enabled = YES;
        self.plusDelayButton.backgroundColor = [UIColor colorWithRed:(0.0/255.0) green:(140.0/255.0) blue:(170.0/255.0) alpha:1.0f];
    } else if (delay == self.delaySlider.maximumValue) {
        self.minusDelayButton.enabled = YES;
        self.minusDelayButton.backgroundColor = [UIColor colorWithRed:(0.0/255.0) green:(140.0/255.0) blue:(170.0/255.0) alpha:1.0f];
        
        self.plusDelayButton.enabled = NO;
        self.plusDelayButton.backgroundColor = [UIColor colorWithRed:(50.0/255.0) green:(50.0/255.0) blue:(50.0/255.0) alpha:1.0f];
    } else {
        self.minusDelayButton.enabled = YES;
        self.minusDelayButton.backgroundColor = [UIColor colorWithRed:(0.0/255.0) green:(140.0/255.0) blue:(170.0/255.0) alpha:1.0f];
        
        self.plusDelayButton.enabled = YES;
        self.plusDelayButton.backgroundColor = [UIColor colorWithRed:(0.0/255.0) green:(140.0/255.0) blue:(170.0/255.0) alpha:1.0f];
    }
}
- (IBAction)delayUnitButtonClicked:(id)sender
{
    UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"DelayUnitActionSheetTitle"] delegate:self cancelButtonTitle:@"Cancel" destructiveButtonTitle:nil otherButtonTitles:[[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"DelayUnitsButton"] objectAtIndex:0], [[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"DelayUnitsButton"] objectAtIndex:1], [[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"DelayUnitsButton"] objectAtIndex:2], [[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"DelayUnitsButton"] objectAtIndex:3], nil];
    actionSheet.accessibilityIdentifier = @"delay_unit_select";
    [actionSheet showInView:self.view];
}

- (IBAction)textTextFieldChanged:(id)sender
{
    if (self.textTextField.text.length > 0) {
        self.textTextField.text = [self.textTextField.text uppercaseString];
    }
}

#pragma mark - Delay Unit Button

- (void)delayUnitButtonSet:(int)value
{
    [self.delayUnitButton setTitle:[[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"DelayUnitsButton"] objectAtIndex:value] forState:UIControlStateNormal];
}

- (IBAction)minusDelayButtonClicked:(id)sender
{
    if (self.delaySlider.value > self.delaySlider.minimumValue) self.delaySlider.value--; else self.delaySlider.value = 0;
    
    self.plusDelayButton.enabled = YES;
    self.plusDelayButton.backgroundColor = [UIColor colorWithRed:(0.0/255.0) green:(140.0/255.0) blue:(170.0/255.0) alpha:1.0f];
    
    if (self.delaySlider.value == self.delaySlider.minimumValue) {
        self.minusDelayButton.enabled = NO;
        
        self.minusDelayButton.backgroundColor = [UIColor colorWithRed:(50.0/255.0) green:(50.0/255.0) blue:(50.0/255.0) alpha:1.0f];
    } else {
        self.minusDelayButton.enabled = YES;
        
        self.minusDelayButton.backgroundColor = [UIColor colorWithRed:(0.0/255.0) green:(140.0/255.0) blue:(170.0/255.0) alpha:1.0f];
    }
    
    self.delayValueLabel.text = [NSString stringWithFormat:@"%d", (int)(self.delaySlider.value)];
}

- (IBAction)plusDelayButtonClicked:(id)sender
{
    if (self.delaySlider.value < self.delaySlider.maximumValue) self.delaySlider.value++; else self.delaySlider.value = self.delaySlider.maximumValue;
    
    self.minusDelayButton.enabled = YES;
    self.minusDelayButton.backgroundColor = [UIColor colorWithRed:(0.0/255.0) green:(140.0/255.0) blue:(170.0/255.0) alpha:1.0f];
    
    if (self.delaySlider.value == self.delaySlider.maximumValue) {
        self.plusDelayButton.enabled = NO;
        
        self.plusDelayButton.backgroundColor = [UIColor colorWithRed:(50.0/255.0) green:(50.0/255.0) blue:(50.0/255.0) alpha:1.0f];
    } else {
        self.plusDelayButton.enabled = YES;
        
        self.plusDelayButton.backgroundColor = [UIColor colorWithRed:(0.0/255.0) green:(140.0/255.0) blue:(170.0/255.0) alpha:1.0f];
    }
    
    self.delayValueLabel.text = [NSString stringWithFormat:@"%d", (int)(self.delaySlider.value)];
}

#pragma mark - UIActionSheetDelegate

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if ([actionSheet.accessibilityIdentifier isEqualToString:@"delay_unit_select"]) {
        if (buttonIndex != actionSheet.cancelButtonIndex) {
            self.selectedDelayUnit = (uint8_t)buttonIndex;
            
            [self delayUnitButtonSet:self.selectedDelayUnit];
        }
    }
}

#pragma mark - UITextFieldDelegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    return YES;
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    if ([textField isEqual:self.textTextField]) {
        int length = (int)[textField.text length];
        if (length >= MAXLENGTH_TEXT && ![string isEqualToString:@""]) {
            textField.text = [textField.text substringToIndex:MAXLENGTH_TEXT];
            return NO;
        }
    } else if ([textField isEqual:self.nameTextField]) {
        int length = (int)[textField.text length];
        if (length >= MAXLENGTH_NAME && ![string isEqualToString:@""]) {
            textField.text = [textField.text substringToIndex:MAXLENGTH_NAME];
            return NO;
        }
    }
    return YES;
}

@end
