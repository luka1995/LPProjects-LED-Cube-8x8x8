//
//  LPNewDefaultEffectViewController.h
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 22/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPSharedManager.h"
#import "LPCubeEffect.h"
#import "LPAnimations.h"
#import "LPAnimationsLetters.h"
#import "LPToastView.h"


@interface LPNewDefaultEffectViewController : UIViewController <UIActionSheetDelegate>

@property (nonatomic, assign) uint8_t function;
@property (nonatomic, strong) IBOutlet UITextField *nameTextField;
@property (nonatomic, strong) IBOutlet UILabel *nameLabel;
@property (nonatomic, strong) IBOutlet UISlider *delaySlider;
@property (nonatomic, strong) IBOutlet UILabel *delayValueLabel;
@property (nonatomic, strong) IBOutlet UIButton *delayUnitButton;
@property (nonatomic, strong) IBOutlet UISlider *repeatsSlider;
@property (nonatomic, strong) IBOutlet UILabel *repeatsValueLabel;
@property (nonatomic, strong) IBOutlet UILabel *repeatsLabel;
@property (nonatomic, strong) IBOutlet UILabel *delayLabel;
@property (nonatomic, strong) IBOutlet UIButton *minusDelayButton;
@property (nonatomic, strong) IBOutlet UIButton *plusDelayButton;
@property (nonatomic, copy) void (^cancelBlock)(void);
@property (nonatomic, copy) void (^saveBlock)(NSMutableArray *arrayEffects);

- (IBAction)delaySliderValueChanged:(id)sender;
- (IBAction)delayUnitButtonClicked:(id)sender;
- (IBAction)minusDelayButtonClicked:(id)sender;
- (IBAction)plusDelayButtonClicked:(id)sender;
- (IBAction)repeatsSliderValueChanged:(id)sender;

@end
