//
//  LPCubeEffectCellView.m
//  LP_LED_CUBE_8x8x8
//
//  Created by Luka Penger on 28/06/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPCubeEffectCellView.h"


static NSString *ItemIdentifier = @"ItemIdentifier";

@implementation LPCubeEffectCellView

+ (LPCubeEffectCellView *)cellFromNibNamed:(NSString *)nibName
{
    NSArray *nibContents = [[NSBundle mainBundle] loadNibNamed:nibName owner:self options:NULL];
    NSEnumerator *nibEnumerator = [nibContents objectEnumerator];
    LPCubeEffectCellView *xibBasedCell = nil;
    NSObject* nibItem = nil;
    
    while ((nibItem = [nibEnumerator nextObject]) != nil) {
        if ([nibItem isKindOfClass:[LPCubeEffectCellView class]]) {
            xibBasedCell = (LPCubeEffectCellView *)nibItem;
            break;
        }
    }
    
    return xibBasedCell;
}

-(void)awakeFromNib
{
    self.smallLayout = [LPCollectionViewFlowSmallLayout new];
        
    [self.collectionView setCollectionViewLayout:self.smallLayout];
    [self.collectionView registerClass:[UICollectionViewCell class] forCellWithReuseIdentifier:ItemIdentifier];
    
    [self.collectionView.collectionViewLayout invalidateLayout];
}

- (void)setColumnsBytes:(uint8_t *)columnsBytes
{
    _columnsBytes = columnsBytes;
    
    [self.collectionView reloadData];
}

- (void)setRowsBytes:(char)rowsBytes
{
    _rowsBytes = rowsBytes;

    _row1.backgroundColor = (rowsBytes & 0x01) ? [UIColor greenColor] : [UIColor blackColor];
    _row2.backgroundColor = (rowsBytes & 0x02) ? [UIColor greenColor] : [UIColor blackColor];
    _row3.backgroundColor = (rowsBytes & 0x04) ? [UIColor greenColor] : [UIColor blackColor];
    _row4.backgroundColor = (rowsBytes & 0x08) ? [UIColor greenColor] : [UIColor blackColor];
    _row5.backgroundColor = (rowsBytes & 0x10) ? [UIColor greenColor] : [UIColor blackColor];
    _row6.backgroundColor = (rowsBytes & 0x20) ? [UIColor greenColor] : [UIColor blackColor];
    _row7.backgroundColor = (rowsBytes & 0x40) ? [UIColor greenColor] : [UIColor blackColor];
    _row8.backgroundColor = (rowsBytes & 0x80) ? [UIColor greenColor] : [UIColor blackColor];
}

- (void)setHighlighted:(BOOL)highlighted animated:(BOOL)animated
{
    if (highlighted) {
        self.backgroundColor = [UIColor colorWithWhite:0.87 alpha:1.0];
    } else {
        self.backgroundColor = [UIColor whiteColor];
    }
}

#pragma mark - UICollectionView DataSource & Delegate methods

- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView
{
    return 8;
}

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section
{
    return 8;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath
{
    UICollectionViewCell *cell = (UICollectionViewCell *)[self.collectionView dequeueReusableCellWithReuseIdentifier:ItemIdentifier forIndexPath:indexPath];
    if (!cell) {
        cell = [UICollectionViewCell new];
    }

    BOOL state = self.columnsBytes[indexPath.section] & (1 << indexPath.row);
    
    if (state) {
        [cell setBackgroundColor:[UIColor greenColor]];
    } else {
        [cell setBackgroundColor:[UIColor whiteColor]];
    }
    
    return cell;
}

@end
