//
//  LPTextFieldCellView.m
//
//  Created by Luka Penger on 10/04/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPTextFieldCellView.h"


@implementation LPTextFieldCellView

+ (LPTextFieldCellView *)cellFromNibNamed:(NSString *)nibName
{    
    NSArray *nibContents = [[NSBundle mainBundle] loadNibNamed:nibName owner:self options:NULL];
    NSEnumerator *nibEnumerator = [nibContents objectEnumerator];
    LPTextFieldCellView  *xibBasedCell = nil;
    NSObject* nibItem = nil;
    
    while ((nibItem = [nibEnumerator nextObject]) != nil) {
        if ([nibItem isKindOfClass:[LPTextFieldCellView class]]) {
            xibBasedCell = (LPTextFieldCellView *)nibItem;
            break;
        }
    }
    
    return xibBasedCell;
}

@end
