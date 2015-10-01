//
//  LPTranslation.h
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 22/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface LPTranslation : NSObject

+ (uint8_t *)move_x_revCube:(uint8_t *)cube X1:(uint8_t)x1 Y1:(uint8_t)y1 X2:(uint8_t)x2 Y2:(uint8_t)y2;

+ (uint8_t *)move_y_revCube:(uint8_t *)cube X1:(uint8_t)x1 Y1:(uint8_t)y1 X2:(uint8_t)x2 Y2:(uint8_t)y2;

+ (uint8_t *)move_z_revCube:(uint8_t *)cube X1:(uint8_t)x1 Y1:(uint8_t)y1 X2:(uint8_t)x2 Y2:(uint8_t)y2;

+ (uint8_t *)move_x_fwdCube:(uint8_t *)cube X1:(uint8_t)x1 Y1:(uint8_t)y1 X2:(uint8_t)x2 Y2:(uint8_t)y2;

+ (uint8_t *)move_y_fwdCube:(uint8_t *)cube X1:(uint8_t)x1 Y1:(uint8_t)y1 X2:(uint8_t)x2 Y2:(uint8_t)y2;

+ (uint8_t *)move_z_fwdCube:(uint8_t *)cube X1:(uint8_t)x1 Y1:(uint8_t)y1 X2:(uint8_t)x2 Y2:(uint8_t)y2;

@end
