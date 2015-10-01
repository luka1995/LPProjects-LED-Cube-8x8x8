//
//  LPSharedManager.h
//
//  Created by Luka Penger on 20/03/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>


@interface LPSharedManager : NSObject

@property (nonatomic, strong) NSString *selectedIP;
@property (nonatomic, strong) NSString *ftpUsername;
@property (nonatomic, strong) NSString *ftpPassword;

@property (nonatomic, strong) NSMutableArray *savedConnectedIPs;

+ (id)sharedManager;

+ (int)TCPPort;
+ (int)UDPPort;
unsigned char crc_update(unsigned char icrc, unsigned char data);
unsigned char calcCRC(unsigned char data[], unsigned int length);

+ (int)ftpPort;

- (NSString *)fileSizeFormat:(unsigned long long)value;

@end

@interface UIImage (SharedManagerImage)

- (UIImage *)imageTintedWithColor:(UIColor *)color;
- (UIImage *)changeImageSize:(CGSize)newSize;

@end