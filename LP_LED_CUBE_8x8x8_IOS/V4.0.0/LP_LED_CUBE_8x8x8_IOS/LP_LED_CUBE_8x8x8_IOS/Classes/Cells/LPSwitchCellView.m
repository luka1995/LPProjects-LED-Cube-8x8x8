//
//  LPSwitchCellView.m
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 01/12/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPSwitchCellView.h"


@implementation LPSwitchCellView

+ (LPSwitchCellView *)cellFromNibNamed:(NSString *)nibName
{
    NSArray *nibContents = [[NSBundle mainBundle] loadNibNamed:nibName owner:self options:NULL];
    NSEnumerator *nibEnumerator = [nibContents objectEnumerator];
    LPSwitchCellView *xibBasedCell = nil;
    NSObject* nibItem = nil;
    
    while ((nibItem = [nibEnumerator nextObject]) != nil) {
        if ([nibItem isKindOfClass:[LPSwitchCellView class]]) {
            xibBasedCell = (LPSwitchCellView *)nibItem;
            break;
        }
    }
    
    return xibBasedCell;
}

@end
