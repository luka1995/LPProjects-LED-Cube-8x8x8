//
//  LPCollectionViewFlowSmallLayout.m
//  LFlash
//
//  Created by Luka Penger on 7/1/13.
//  Copyright (c) 2013 LukaPenger. All rights reserved.
//

#import "LPCollectionViewFlowSmallLayout.h"

@implementation LPCollectionViewFlowSmallLayout

-(id)init
{
    self = [super init];
    if (self) {
        self.itemSize = CGSizeMake(8, 8);
        self.sectionInset = UIEdgeInsetsMake(1, 1, 1, 1);
        self.minimumInteritemSpacing = 1.0f;
        self.minimumLineSpacing = 1.0f;
    }

    return self;
}

@end
