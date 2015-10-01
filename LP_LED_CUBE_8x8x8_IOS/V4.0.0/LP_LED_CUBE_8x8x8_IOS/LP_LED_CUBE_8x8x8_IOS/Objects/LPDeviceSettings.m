//
//  LPDeviceSettings.m
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 01/12/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "LPDeviceSettings.h"


@interface LPDeviceSettings ()

@end


@implementation LPDeviceSettings

+ (id)deviceSettingsWithString:(NSString *)string
{
    LPDeviceSettings *new = [LPDeviceSettings new];
    
    if (string) {
        NSArray *array = [string componentsSeparatedByCharactersInSet:
                                    [NSCharacterSet newlineCharacterSet]];
        
        if ([array count] > 0) {
            new.deviceName = [array objectAtIndex:0];
        }
        
        if ([array count] > 1) {
            new.firmwareVersion = [array objectAtIndex:1];
        }
        
        if ([array count] > 2) {
            new.macAddress = [array objectAtIndex:2];
        }
        
        if ([array count] > 3) {
            new.ipAddress = [array objectAtIndex:3];
        }
        
        if ([array count] > 4) {
            new.subnetMask = [array objectAtIndex:4];
        }
        
        if ([array count] > 5) {
            new.defaultGatewayAddress = [array objectAtIndex:5];
        }
        
        if ([array count] > 6) {
            new.priDNSAddress = [array objectAtIndex:6];
        }
        
        if ([array count] > 7) {
            new.secDNSAddress = [array objectAtIndex:7];
        }
        
        if ([array count] > 8) {
            if ([[array objectAtIndex:8] isEqualToString:@"1"]) {
                new.dhcpEnabled = YES;
            } else {
                new.dhcpEnabled = NO;
            }
        }
            
        if ([array count] > 9) {
            new.playedAnimationName = [array objectAtIndex:9];
        }
        
        if ([array count] > 10) {
            if ([[array objectAtIndex:10] isEqualToString:@"1"]) {
                new.playedAnimation = YES;
            } else {
                new.playedAnimation = NO;
            }
        }
    }
    
    return new;
}

- (NSDictionary *)dictionary
{
    NSMutableDictionary *dictionary = [NSMutableDictionary new];

    [dictionary setObject:[NSString stringWithFormat:@"%@", self.deviceName] forKey:@"deviceName"];
    [dictionary setObject:[NSString stringWithFormat:@"%@", self.firmwareVersion] forKey:@"firmwareVersion"];
    [dictionary setObject:[NSString stringWithFormat:@"%@", self.macAddress] forKey:@"macAddress"];
    [dictionary setObject:[NSString stringWithFormat:@"%@", self.ipAddress] forKey:@"ipAddress"];
    [dictionary setObject:[NSString stringWithFormat:@"%@", self.subnetMask] forKey:@"subnetMask"];
    [dictionary setObject:[NSString stringWithFormat:@"%@", self.defaultGatewayAddress] forKey:@"defaultGatewayAddress"];
    [dictionary setObject:[NSString stringWithFormat:@"%@", self.priDNSAddress] forKey:@"priDNSAddress"];
    [dictionary setObject:[NSString stringWithFormat:@"%@", self.secDNSAddress] forKey:@"secDNSAddress"];
    [dictionary setObject:[NSString stringWithFormat:@"%@", self.dhcpEnabled ? @"YES" : @"NO"] forKey:@"macAddress"];
    [dictionary setObject:[NSString stringWithFormat:@"%@", self.playedAnimationName] forKey:@"playedAnimationName"];
    [dictionary setObject:[NSString stringWithFormat:@"%@", self.playedAnimation ? @"YES" : @"NO"] forKey:@"playedAnimation"];
    
    return dictionary;
}

- (NSMutableArray *)getFileStrings
{
    NSMutableArray *array = [NSMutableArray new];
    
    [array addObject:self.deviceName];
    [array addObject:self.firmwareVersion];
    [array addObject:self.macAddress];
    [array addObject:self.ipAddress];
    [array addObject:self.subnetMask];
    [array addObject:self.defaultGatewayAddress];
    [array addObject:self.priDNSAddress];
    [array addObject:self.secDNSAddress];
    [array addObject:self.dhcpEnabled ? @"1" : @"0"];
    [array addObject:self.playedAnimationName];
    [array addObject:self.playedAnimation ? @"1" : @"0"];

    return array;
}

@end
