//
//  LPEditCustomEffectViewController.m
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 12/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPEditCustomEffectViewController.h"


#define MAXLENGTH 20

static NSString *ItemIdentifierColumns = @"ItemIdentifierColumns";
static NSString *ItemIdentifierLayers = @"ItemIdentifierLayers";

#define selectedColor [UIColor colorWithRed:(0.0/255.0) green:(190.0/255.0) blue:(140.0/255.0) alpha:1.0]
#define normalColor [UIColor whiteColor]

#define ALPHA_NULL_VIEW     0.5f


@interface LPEditCustomEffectViewController ()

@property (nonatomic, assign) int selectedLayer;
@property (nonatomic, assign) int selectedDelayUnit;
@property (nonatomic, strong) LPCubeEffect *effect;
@property (nonatomic, assign) BOOL effectNull;
@property (nonatomic, strong) UIView *nullView;
@property (nonatomic, assign) int selectedView;

@end


@implementation LPEditCustomEffectViewController

#pragma mark - Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.effectNull = YES;
    
    self.title = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"EditCustomEffectViewTitle"];

    if (self.backButton) {
        self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"BackButton"] style:UIBarButtonItemStyleBordered target:self action:@selector(backButtonClicked)];
    }
    
    if (self.closeButton) {
        self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"CloseButton"] style:UIBarButtonItemStyleBordered target:self action:@selector(closeButtonClicked)];
    }
    
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"SaveIcon"] style:UIBarButtonItemStyleBordered target:self action:@selector(saveButtonClicked)];

    [self.columnsCollectionView registerClass:[UICollectionViewCell class] forCellWithReuseIdentifier:ItemIdentifierColumns];
    [self.columnsCollectionView.collectionViewLayout invalidateLayout];
    
    [self.layerCollectionView registerClass:[UICollectionViewCell class] forCellWithReuseIdentifier:ItemIdentifierLayers];
    [self.layerCollectionView.collectionViewLayout invalidateLayout];

    UIPanGestureRecognizer *pgr = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(handlePan:)];
    [self.columnsCollectionView addGestureRecognizer:pgr];
    
    self.nameLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"EffectNameLabelText"];
    self.columnsLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"EffectColumnsLabelText"];
    self.layersLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"EffectLayersLabelText"];
    self.delayLabel.text = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"EffectDelayLabelText"];
    self.nameTextField.placeholder = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"EffectNameTextFieldPlaceholder"];
    
    self.nullView = [[UIView alloc] initWithFrame:self.view.frame];
    self.nullView.backgroundColor = [UIColor blackColor];
    self.nullView.alpha = 0.0f;
    [self.view addSubview:self.nullView];
    
    [self setCubeEffect:self.effect animated:NO];
}

- (void)viewDidLayoutSubviews
{
    [super viewDidLayoutSubviews];

    self.nullView.frame = CGRectMake(0.0f, 0.0f, self.view.frame.size.width, self.view.frame.size.height);
}

- (void)setCubeEffect:(LPCubeEffect *)cubeEffect animated:(BOOL)animated
{
    if (cubeEffect) {
        self.effectNull = NO;
        
        self.effect = cubeEffect;
        
        self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"SaveIcon"] style:UIBarButtonItemStyleBordered target:self action:@selector(saveButtonClicked)];
    } else {
        self.effectNull = YES;
        
        self.effect = [LPCubeEffect new];
        
        self.navigationItem.rightBarButtonItem = nil;
    }
    
    self.delaySlider.value = self.effect.delay;
    [self delaySliderValueChanged:nil];
    
    self.selectedDelayUnit = self.effect.delayUnit;
    [self delayUnitButtonSet:self.selectedDelayUnit];
    
    self.nameTextField.text = self.effect.name;
    
    self.selectedLayer = 0;
    [self.layerCollectionView reloadData];
    [self.columnsCollectionView reloadData];
    
    self.selectedView = self.effect.view;
    [self setChangeViewButtonText:self.selectedView];

    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone || !animated) {
        if (cubeEffect) {
            self.nullView.alpha = 0.0f;
        } else {
            self.nullView.alpha = ALPHA_NULL_VIEW;
        }
    } else {
        [UIView beginAnimations:nil context:nil];
        [UIView setAnimationDuration:0.5];
        
        if (cubeEffect) {
            self.nullView.alpha = 0.0f;
        } else {
            self.nullView.alpha = ALPHA_NULL_VIEW;
        }
        
        [UIView commitAnimations];
    }
}

#pragma mark - Actions

- (void)closeButtonClicked
{
    [self.view endEditing:YES];
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)backButtonClicked
{
    [self.view endEditing:YES];
    
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)saveButtonClicked
{
    if (self.nameTextField.text.length > 0) {
        self.effect.delayUnit = (uint8_t)self.selectedDelayUnit;
        self.effect.delay = (uint8_t)self.delaySlider.value;
        self.effect.name = self.nameTextField.text;
        
        [self.view endEditing:YES];
        
        [self dismissViewControllerAnimated:YES completion:nil];
        
        if (self.saveBlock)
            self.saveBlock(self.effect);
        
        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad) {
            [[NSNotificationCenter defaultCenter] postNotificationName:@"EditCustomAnimationSave" object:self.effect];
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
    UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"DelayUnitActionSheetTitle"] delegate:self cancelButtonTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"ActionSheetCancelButton"] destructiveButtonTitle:nil otherButtonTitles:[[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"DelayUnitsButton"] objectAtIndex:0], [[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"DelayUnitsButton"] objectAtIndex:1], [[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"DelayUnitsButton"] objectAtIndex:2], [[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"DelayUnitsButton"] objectAtIndex:3], nil];
    actionSheet.accessibilityIdentifier = @"delay_unit_select";
    [actionSheet showInView:self.view];
}

- (IBAction)changeViewButtonClicked:(id)sender
{
    self.selectedLayer = 0;
    
    if (self.selectedView >= 2) self.selectedView = 0; else self.selectedView++;
    [self setChangeViewButtonText:self.selectedView];
    
    [self.columnsCollectionView reloadData];
    [self.layerCollectionView reloadData];
}

- (void)setChangeViewButtonText:(int)value
{
    if (self.selectedView == 0) {
        [self.changeViewButton setTitle:@"Y" forState:UIControlStateNormal];
    } else if (self.selectedView == 1) {
        [self.changeViewButton setTitle:@"X" forState:UIControlStateNormal];
    } else {
        [self.changeViewButton setTitle:@"Z" forState:UIControlStateNormal];
    }
}

static int xPoint = INT32_MAX, yPoint = INT32_MAX;

-(void)handlePan:(UIPanGestureRecognizer*)pgr
{
    if (pgr.state == UIGestureRecognizerStateChanged) {
        CGPoint point = [pgr locationInView:pgr.view];
        
        for (int x=0; x<8; x++) {
            for (int y=0; y<8; y++) {
                UICollectionViewLayoutAttributes *attributes = [self.columnsCollectionView layoutAttributesForItemAtIndexPath:[NSIndexPath indexPathForRow:x inSection:y]];
                
                UICollectionViewCell *cell = [self.columnsCollectionView cellForItemAtIndexPath:[NSIndexPath indexPathForRow:x inSection:y]];
                
                BOOL state = CGRectContainsPoint(attributes.frame, point);
                
                if (state) {
                    if (x != xPoint || y != yPoint) {
                        xPoint = x; yPoint = y;
                        
                        if (self.selectedView == 0) { // Y
                            self.effect.cube[y + (self.selectedLayer * 8)] ^= (1 << x);
                            
                            if (self.effect.cube[y + (self.selectedLayer * 8)] & (1 << x)) {
                                cell.backgroundColor = selectedColor;
                            } else {
                                cell.backgroundColor = normalColor;
                            }
                        } else if (self.selectedView == 1) { // X
                            self.effect.cube[[self rotate8Number:self.selectedLayer] + ([self rotate8Number:y] * 8)] ^= (1 << x);
                            
                            if (self.effect.cube[[self rotate8Number:self.selectedLayer] + ([self rotate8Number:y] * 8)] & (1 << x)) {
                                cell.backgroundColor = selectedColor;
                            } else {
                                cell.backgroundColor = normalColor;
                            }
                        } else { // Z
                            self.effect.cube[x + ([self rotate8Number:(int)y] * 8)] ^= (1 << self.selectedLayer);
                            
                            if (self.effect.cube[x + ([self rotate8Number:(int)y] * 8)] & (1 << self.selectedLayer)) {
                                cell.backgroundColor = selectedColor;
                            } else {
                                cell.backgroundColor = normalColor;
                            }
                        }
                    }
                }
            }
        }
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
        UICollectionViewCell *cell = (UICollectionViewCell *)[self.columnsCollectionView dequeueReusableCellWithReuseIdentifier:ItemIdentifierColumns forIndexPath:indexPath];
        if (!cell) {
            cell = [UICollectionViewCell new];
        }
        
        BOOL state = NO;
        
        if (self.selectedView == 0) { // Y
            state = self.effect.cube[indexPath.section + (self.selectedLayer * 8)] & (1 << indexPath.row);
        } else if (self.selectedView == 1) { // X
            state = self.effect.cube[[self rotate8Number:self.selectedLayer] + ([self rotate8Number:(int)indexPath.section] * 8)] & (1 << indexPath.row);
        } else { // Z
            state = self.effect.cube[indexPath.row + ([self rotate8Number:(int)indexPath.section] * 8)] & (1 << self.selectedLayer);
        }
        
        if (state) {
            [cell setBackgroundColor:selectedColor];
        } else {
            [cell setBackgroundColor:normalColor];
        }
        
        return cell;
    } else {
        UICollectionViewCell *cell = (UICollectionViewCell *)[self.layerCollectionView dequeueReusableCellWithReuseIdentifier:ItemIdentifierLayers forIndexPath:indexPath];
        if (!cell) {
            cell = [UICollectionViewCell new];
        }
        
        BOOL state =  indexPath.row == self.selectedLayer ? YES : NO;
        
        if (state) {
            [cell setBackgroundColor:selectedColor];
        } else {
            [cell setBackgroundColor:normalColor];
        }
        
        return cell;
    }
    
    return nil;
}

#pragma mark - UICollectionViewDelegate

- (int)rotate8Number:(int)number
{
    switch (number) {
        case 0: return 7;
        case 1: return 6;
        case 2: return 5;
        case 3: return 4;
        case 4: return 3;
        case 5: return 2;
        case 6: return 1;
        case 7: return 0;
    }
    
    return 0;
}

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath
{
    if ([collectionView isEqual:self.columnsCollectionView]) {
        if (self.selectedView == 0) { // Y
            self.effect.cube[(indexPath.section + (self.selectedLayer * 8))] ^= (1 << indexPath.row);
        } else if (self.selectedView == 1) { // X
            self.effect.cube[[self rotate8Number:self.selectedLayer] + ([self rotate8Number:(int)indexPath.section] * 8)] ^= (1 << indexPath.row);
        } else { // Z
            self.effect.cube[(indexPath.row + ([self rotate8Number:(int)indexPath.section] * 8))] ^= (1 << self.selectedLayer);
        }
        
        [self.columnsCollectionView reloadData];
    } else {
        self.selectedLayer = (int)indexPath.row;
        
        [self.layerCollectionView reloadData];
        [self.columnsCollectionView reloadData];
    }
}

- (void)collectionView:(UICollectionView *)colView didHighlightItemAtIndexPath:(NSIndexPath *)indexPath
{
    UICollectionViewCell *cell = [colView cellForItemAtIndexPath:indexPath];
    cell.contentView.backgroundColor = [UIColor colorWithRed:(0.0/255.0) green:(140.0/255.0) blue:(170.0/255.0) alpha:1.0f];
}

- (void)collectionView:(UICollectionView *)colView didUnhighlightItemAtIndexPath:(NSIndexPath *)indexPath
{
    UICollectionViewCell *cell = [colView cellForItemAtIndexPath:indexPath];
    cell.contentView.backgroundColor = nil;
}

- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout sizeForItemAtIndexPath:(NSIndexPath *)indexPath
{
    UICollectionViewFlowLayout *flow = (UICollectionViewFlowLayout*)collectionView.collectionViewLayout;

    if ([collectionView isEqual:self.columnsCollectionView]) {
        return CGSizeMake(((self.columnsCollectionView.frame.size.width - ((8+1)*flow.minimumInteritemSpacing))/8), ((self.columnsCollectionView.frame.size.height - ((8+1)*flow.minimumInteritemSpacing))/8));
    } else {
        return CGSizeMake(((self.layerCollectionView.frame.size.width - ((8+1)*flow.minimumInteritemSpacing))/8), ((self.layerCollectionView.frame.size.height - ((1+1)*flow.minimumInteritemSpacing))/1));
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
    int length = (int)[textField.text length];
    if (length >= MAXLENGTH && ![string isEqualToString:@""]) {
        textField.text = [textField.text substringToIndex:MAXLENGTH];
        return NO;
    }
    return YES;
}

@end
