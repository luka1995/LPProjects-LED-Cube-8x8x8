//
//  LPNewEffectViewController.h
//  LP_LED_CUBE_8x8x8
//
//  Created by Luka Penger on 20/06/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPSharedManager.h"
#import "LPCubeEffect.h"


@interface LPNewEffectViewController : UIViewController <UICollectionViewDataSource, UICollectionViewDelegate, UICollectionViewDelegateFlowLayout, UITextFieldDelegate>

@property (nonatomic, strong) IBOutlet UICollectionView *columnsCollectionView;
@property (nonatomic, strong) IBOutlet UICollectionView *rowsCollectionView;
@property (nonatomic, strong) IBOutlet UITextField *nameTextField;
@property (nonatomic, strong) IBOutlet UISlider *delaySlider;
@property (nonatomic, strong) IBOutlet UILabel *delayValueLabel;

@property (nonatomic, copy)  void (^cancelBlock)(void);
@property (nonatomic, copy)  void (^addBlock)(LPCubeEffect *cubeEffect);

- (IBAction)delaySliderValueChanged:(id)sender;

@end
