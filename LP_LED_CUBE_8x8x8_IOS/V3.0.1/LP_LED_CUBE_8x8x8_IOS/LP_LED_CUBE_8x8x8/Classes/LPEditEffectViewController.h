//
//  LPEditEffectViewController.h
//  LP_LED_CUBE_8x8x8
//
//  Created by Luka Penger on 29/06/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPSharedManager.h"
#import "LPCubeEffect.h"


@interface LPEditEffectViewController : UIViewController <UICollectionViewDataSource, UICollectionViewDelegate, UICollectionViewDelegateFlowLayout, UITextFieldDelegate>

@property (nonatomic, strong) LPCubeEffect *cubeEffect;
@property (nonatomic, strong) IBOutlet UICollectionView *columnsCollectionView;
@property (nonatomic, strong) IBOutlet UICollectionView *rowsCollectionView;
@property (nonatomic, strong) IBOutlet UITextField *nameTextField;
@property (nonatomic, strong) IBOutlet UISlider *delaySlider;
@property (nonatomic, strong) IBOutlet UILabel *delayValueLabel;

@property (nonatomic, copy)  void (^cancelBlock)(void);
@property (nonatomic, copy)  void (^saveBlock)(LPCubeEffect *cubeEffect);

- (IBAction)delaySliderValueChanged:(id)sender;

@end
