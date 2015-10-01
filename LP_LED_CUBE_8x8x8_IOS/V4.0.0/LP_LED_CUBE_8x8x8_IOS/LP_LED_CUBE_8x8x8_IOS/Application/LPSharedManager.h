//
//  LPSharedManager.h
//
//  Created by Luka Penger on 20/03/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "LPAnimation.h"
#import "LPLEDCubeAPI.h"
#import "LPSplitViewController.h"


@interface LPSharedManager : NSObject

@property (nonatomic, strong) NSDictionary *languageDictionary;
@property (nonatomic, strong) NSString *languageISO2Code;
@property (nonatomic, strong) NSString *languageDefaultISO2Code;
@property (nonatomic, strong) NSString *selectedIP;
@property (nonatomic, strong) LPLEDCubeAPI *ledCubeAPI;
@property (nonatomic, strong) LPSplitViewController *splitViewControllerIpad;

+ (id)sharedManager;

+ (int)WEBServerPort;
+ (int)TCPPort;
+ (int)UDPPort;
+ (NSString *)ftpUsername;
+ (NSString *)ftpPassword;

unsigned char crc_update(unsigned char icrc, unsigned char data);
unsigned char calcCRC(unsigned char data[], unsigned int length);

+ (int)ftpPort;

- (NSString *)fileSizeFormat:(unsigned long long)value;

+ (float)toastViewPadding;

@property (nonatomic, strong) NSMutableArray *savedAnimations;
- (void)loadSavedAnimations;
- (void)saveSavedAnimations;
- (BOOL)checkIfSavedAnimationExists:(NSString *)fileName;

@end

@interface UIImage (SharedManagerImage)

- (UIImage *)imageTintedWithColor:(UIColor *)color;
- (UIImage *)changeImageSize:(CGSize)newSize;

@end