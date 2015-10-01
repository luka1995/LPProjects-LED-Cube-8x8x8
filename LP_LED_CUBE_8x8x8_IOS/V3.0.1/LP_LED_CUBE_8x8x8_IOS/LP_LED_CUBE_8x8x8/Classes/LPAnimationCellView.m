//
//  LPAnimationCellView.m
//  LP_LED_CUBE_8x8x8
//
//  Created by Luka Penger on 29/06/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPAnimationCellView.h"


@implementation LPAnimationCellView

+ (LPAnimationCellView *)cellFromNibNamed:(NSString *)nibName
{
    NSArray *nibContents = [[NSBundle mainBundle] loadNibNamed:nibName owner:self options:NULL];
    NSEnumerator *nibEnumerator = [nibContents objectEnumerator];
    LPAnimationCellView *xibBasedCell = nil;
    NSObject* nibItem = nil;
    
    while ((nibItem = [nibEnumerator nextObject]) != nil) {
        if ([nibItem isKindOfClass:[LPAnimationCellView class]]) {
            xibBasedCell = (LPAnimationCellView *)nibItem;
            break;
        }
    }
    
    return xibBasedCell;
}

@end
