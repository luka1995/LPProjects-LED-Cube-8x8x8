//
//  LPLEDCubeAPI.m
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 24/11/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPLEDCubeAPI.h"


NSString *const LEDCubeAPIURL = @"http://api.led-cube.eu/";
NSString *const UploadDeviceTokenPath = @"v1/devicetoken.php";


@implementation LPLEDCubeAPI

- (void)uploadDeviceToken:(NSString *)deviceToken successfulBlock:(void (^)(NSString *responseString))successful failureBlock:(void (^)(NSError *error))failure
{
    AFHTTPRequestOperationManager *manager = [AFHTTPRequestOperationManager manager];
    manager.requestSerializer = [AFJSONRequestSerializer serializer];
    manager.responseSerializer = [AFHTTPResponseSerializer serializer];
    
    NSMutableDictionary *parameters = [NSMutableDictionary new];
    
    [parameters setObject:deviceToken forKey:@"deviceToken"];
    [parameters setObject:[[UIDevice currentDevice] name] forKey:@"deviceName"];
    [parameters setObject:[[UIDevice currentDevice] model] forKey:@"deviceModel"];
    [parameters setObject:[[UIDevice currentDevice] systemVersion] forKey:@"deviceSystemVersion"];
    [parameters setObject:[[UIDevice currentDevice] systemName] forKey:@"deviceSystemName"];
    [parameters setObject:[[NSDate date] description] forKey:@"uploadDate"];

    [manager POST:[NSString stringWithFormat:@"%@%@", LEDCubeAPIURL, UploadDeviceTokenPath] parameters:parameters success:^(AFHTTPRequestOperation *operation, id responseObject) {

        if (successful)
            successful(operation.responseString);
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        if (failure)
            failure(error);
    }];
}

@end
