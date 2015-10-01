//
//  LPEditEffectViewController.m
//  LP_LED_CUBE_8x8x8
//
//  Created by Luka Penger on 29/06/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPEditEffectViewController.h"


@interface LPEditEffectViewController ()

@end


#define MAXLENGTH 20

static NSString *ItemIdentifier = @"ItemIdentifier";

@implementation LPEditEffectViewController

#pragma mark - Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.title = @"Edit Effect";
    
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Cancel" style:UIBarButtonItemStyleBordered target:self action:@selector(leftBarButtonClicked:)];
    
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Save" style:UIBarButtonItemStyleBordered target:self action:@selector(rightBarButtonClicked:)];
    
    [self.columnsCollectionView registerClass:[UICollectionViewCell class] forCellWithReuseIdentifier:ItemIdentifier];
    [self.columnsCollectionView.collectionViewLayout invalidateLayout];
    
    self.delaySlider.value = self.cubeEffect.delay;
    [self delaySliderValueChanged:nil];
    self.nameTextField.text = self.cubeEffect.name;
    [self.columnsCollectionView reloadData];
    [self.rowsCollectionView reloadData];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    
}

#pragma mark - Actions

- (void)leftBarButtonClicked:(id)sender
{
    [self dismissViewControllerAnimated:YES completion:^{
        
    }];
}

- (void)rightBarButtonClicked:(id)sender
{
    self.cubeEffect.delay = (int)self.delaySlider.value;
    self.cubeEffect.name = self.nameTextField.text;
    
    [self dismissViewControllerAnimated:YES completion:^{
        
    }];
    
    if (self.saveBlock)
        self.saveBlock(self.cubeEffect);
}

- (void)delaySliderValueChanged:(id)sender
{
    int delay = (int)self.delaySlider.value;
    
    self.delayValueLabel.text = [NSString stringWithFormat:@"%d x 10ms", delay];
}

#pragma mark - UICollectionView DataSource & Delegate methods

- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView
{
    if ([collectionView isEqual:self.columnsCollectionView]) {
        return 8;
    } else {
        return 1;
    }
    
    return 0;
}

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section
{
    if ([collectionView isEqual:self.columnsCollectionView]) {
        return 8;
    } else {
        return 8;
    }
    
    return 0;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath
{
    if ([collectionView isEqual:self.columnsCollectionView]) {
        UICollectionViewCell *cell = (UICollectionViewCell *)[self.columnsCollectionView dequeueReusableCellWithReuseIdentifier:ItemIdentifier forIndexPath:indexPath];
        if (!cell) {
            cell = [UICollectionViewCell new];
        }
        
        BOOL state = self.cubeEffect.columns[indexPath.section] & (1 << indexPath.row);
        
        if (state) {
            [cell setBackgroundColor:[UIColor greenColor]];
        } else {
            [cell setBackgroundColor:[UIColor whiteColor]];
        }
        
        return cell;
    } else {
        UICollectionViewCell *cell = (UICollectionViewCell *)[self.columnsCollectionView dequeueReusableCellWithReuseIdentifier:ItemIdentifier forIndexPath:indexPath];
        if (!cell) {
            cell = [UICollectionViewCell new];
        }
        
        BOOL state =  (self.cubeEffect.rows & (1<<indexPath.row));
        
        if (state) {
            [cell setBackgroundColor:[UIColor greenColor]];
        } else {
            [cell setBackgroundColor:[UIColor whiteColor]];
        }
        
        return cell;
    }
    
    return nil;
}

#pragma mark - UICollectionViewDelegate

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath
{
    if ([collectionView isEqual:self.columnsCollectionView]) {
        self.cubeEffect.columns[indexPath.section] ^= (1 << indexPath.row);
        
        [self.columnsCollectionView reloadData];
    } else {
        self.cubeEffect.rows ^= (1 << indexPath.row);
        
        [self.rowsCollectionView reloadData];
    }
}

- (void)collectionView:(UICollectionView *)colView didHighlightItemAtIndexPath:(NSIndexPath *)indexPath
{
    UICollectionViewCell *cell = [colView cellForItemAtIndexPath:indexPath];
    cell.contentView.backgroundColor = [UIColor colorWithRed:0 green:0 blue:1 alpha:0.5];
}

- (void)collectionView:(UICollectionView *)colView didUnhighlightItemAtIndexPath:(NSIndexPath *)indexPath
{
    UICollectionViewCell *cell = [colView cellForItemAtIndexPath:indexPath];
    cell.contentView.backgroundColor = nil;
}

#pragma mark - UITextFieldDelegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    return YES;
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    int length = [textField.text length] ;
    if (length >= MAXLENGTH && ![string isEqualToString:@""]) {
        textField.text = [textField.text substringToIndex:MAXLENGTH];
        return NO;
    }
    return YES;
}

@end
