//
//  LPLEDCubeAPI.h
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 24/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AFNetworking/AFNetworking.h>


@interface LPLEDCubeAPI : NSObject

- (void)uploadDeviceToken:(NSString *)deviceToken successfulBlock:(void (^)(NSString *responseString))successful failureBlock:(void (^)(NSError *error))failure;

@end
