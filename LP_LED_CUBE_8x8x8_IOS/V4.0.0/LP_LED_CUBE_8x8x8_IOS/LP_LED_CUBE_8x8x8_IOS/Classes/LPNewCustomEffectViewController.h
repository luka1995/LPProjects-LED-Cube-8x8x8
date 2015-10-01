//
//  LPNewCustomEffectViewController.h
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 11/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPSharedManager.h"
#import "LPCubeEffect.h"
#import "LPToastView.h"


@interface LPNewCustomEffectViewController : UIViewController <UICollectionViewDataSource, UICollectionViewDelegate, UICollectionViewDelegateFlowLayout, UITextFieldDelegate, UIActionSheetDelegate>

@property (nonatomic, strong) LPCubeEffect *effect;
@property (nonatomic, assign) BOOL closeButton;
@property (nonatomic, strong) IBOutlet UICollectionView *columnsCollectionView;
@property (nonatomic, strong) IBOutlet UICollectionView *layerCollectionView;
@property (nonatomic, strong) IBOutlet UITextField *nameTextField;
@property (nonatomic, strong) IBOutlet UISlider *delaySlider;
@property (nonatomic, strong) IBOutlet UILabel *delayValueLabel;
@property (nonatomic, strong) IBOutlet UIButton *delayUnitButton;
@property (nonatomic, strong) IBOutlet UILabel *nameLabel;
@property (nonatomic, strong) IBOutlet UILabel *columnsLabel;
@property (nonatomic, strong) IBOutlet UILabel *layersLabel;
@property (nonatomic, strong) IBOutlet UILabel *delayLabel;
@property (nonatomic, strong) IBOutlet UIButton *changeViewButton;
@property (nonatomic, strong) IBOutlet UIButton *minusDelayButton;
@property (nonatomic, strong) IBOutlet UIButton *plusDelayButton;
@property (nonatomic, copy) void (^cancelBlock)(void);
@property (nonatomic, copy) void (^saveBlock)(LPCubeEffect *cubeEffect);

- (IBAction)delaySliderValueChanged:(id)sender;
- (IBAction)delayUnitButtonClicked:(id)sender;
- (IBAction)minusDelayButtonClicked:(id)sender;
- (IBAction)plusDelayButtonClicked:(id)sender;
- (IBAction)changeViewButtonClicked:(id)sender;

@end
