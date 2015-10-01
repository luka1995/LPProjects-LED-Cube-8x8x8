//
//  LPDeviceSettings.h
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 01/12/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface LPDeviceSettings : NSObject

@property (nonatomic, strong) NSString *deviceName;
@property (nonatomic, strong) NSString *firmwareVersion;
@property (nonatomic, strong) NSString *macAddress;
@property (nonatomic, strong) NSString *ipAddress;
@property (nonatomic, strong) NSString *subnetMask;
@property (nonatomic, strong) NSString *defaultGatewayAddress;
@property (nonatomic, strong) NSString *priDNSAddress;
@property (nonatomic, strong) NSString *secDNSAddress;
@property (nonatomic, assign) BOOL dhcpEnabled;
@property (nonatomic, strong) NSString *playedAnimationName;
@property (nonatomic, assign) BOOL playedAnimation;

+ (id)deviceSettingsWithString:(NSString *)string;

- (NSDictionary *)dictionary;

- (NSMutableArray *)getFileStrings;

@end
