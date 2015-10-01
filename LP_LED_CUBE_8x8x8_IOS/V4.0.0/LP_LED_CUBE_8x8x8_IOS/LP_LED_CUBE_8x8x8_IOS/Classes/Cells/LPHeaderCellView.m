//
//  LPHeaderCellView.m
//
//  Created by Luka Penger on 10/04/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPHeaderCellView.h"


@implementation LPHeaderCellView

+ (LPHeaderCellView *)cellFromNibNamed:(NSString *)nibName
{
    NSArray *nibContents = [[NSBundle mainBundle] loadNibNamed:nibName owner:self options:NULL];
    NSEnumerator *nibEnumerator = [nibContents objectEnumerator];
    LPHeaderCellView  *xibBasedCell = nil;
    NSObject* nibItem = nil;
    
    while ((nibItem = [nibEnumerator nextObject]) != nil) {
        if ([nibItem isKindOfClass:[LPHeaderCellView class]]) {
            xibBasedCell = (LPHeaderCellView *)nibItem;
            break;
        }
    }
    
    return xibBasedCell;
}

@end
