//
//  LPCubeEffectCellView.h
//  LP_LED_CUBE_8x8x8
//
//  Created by Luka Penger on 28/06/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LPCollectionViewFlowSmallLayout.h"


@interface LPCubeEffectCellView : UITableViewCell <UICollectionViewDataSource,UICollectionViewDelegate,UICollectionViewDelegateFlowLayout>

@property (nonatomic, strong) IBOutlet UICollectionView *collectionView;
@property (nonatomic, strong) LPCollectionViewFlowSmallLayout *smallLayout;
@property (nonatomic, strong) IBOutlet UILabel *titleLabel;
@property (nonatomic, strong) IBOutlet UILabel *delayLabel;
@property (nonatomic, strong) IBOutlet UILabel *numLabel;

@property (nonatomic, assign) uint8_t *columnsBytes;
@property (nonatomic, assign) char rowsBytes;

@property (nonatomic, strong) IBOutlet UIView *row1, *row2, *row3, *row4, *row5, *row6, *row7, *row8;

+ (LPCubeEffectCellView *)cellFromNibNamed:(NSString *)nibName;

@end
