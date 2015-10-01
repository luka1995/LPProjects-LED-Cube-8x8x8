//
//  LPSharedManager.m
//
//  Created by Luka Penger on 20/03/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//


#import "LPSharedManager.h"


static LPSharedManager *sharedMyManager = nil;

@implementation LPSharedManager

+ (id)sharedManager
{
    @synchronized(self) {
        if(!sharedMyManager) {
            sharedMyManager = [[super allocWithZone:NULL] init];
        }
    }
    return sharedMyManager;
}

+ (id)allocWithZone:(NSZone *)zone
{
    return [self sharedManager];
}

- (id)copyWithZone:(NSZone *)zone
{
    return self;
}

- (id)init
{
    self = [super init];
    if (self) {
        self.languageISO2Code = [[NSLocale preferredLanguages] objectAtIndex:0];
        
        self.languageDefaultISO2Code = @"en";
        
        [self readLanguageData];
    }
    return self;
}

- (void)readLanguageData
{
    NSString *errorDesc;
    NSPropertyListFormat format;
    NSString *plistPath;
    NSString *rootPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,
                                                              NSUserDomainMask, YES) objectAtIndex:0];
    plistPath = [rootPath stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.plist",self.languageISO2Code]];
    if (![[NSFileManager defaultManager] fileExistsAtPath:plistPath]) {
        plistPath = [[NSBundle mainBundle] pathForResource:self.languageISO2Code ofType:@"plist"];
    }
    
    NSData *plistXML = [[NSFileManager defaultManager] contentsAtPath:plistPath];
    
    self.languageDictionary = [[NSDictionary alloc] initWithDictionary:[NSPropertyListSerialization
                                                                        propertyListFromData:plistXML
                                                                        mutabilityOption:NSPropertyListMutableContainersAndLeaves
                                                                        format:&format
                                                                        errorDescription:&errorDesc]];
    
    if([self.languageDictionary count] == 0 || self.languageDictionary == nil) {
        self.languageISO2Code = self.languageDefaultISO2Code;
        
        NSString *errorDesc;
        NSPropertyListFormat format;
        NSString *plistPath;
        NSString *rootPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,
                                                                  NSUserDomainMask, YES) objectAtIndex:0];
        plistPath = [rootPath stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.plist",self.languageISO2Code]];
        if (![[NSFileManager defaultManager] fileExistsAtPath:plistPath]) {
            plistPath = [[NSBundle mainBundle] pathForResource:self.languageISO2Code ofType:@"plist"];
        }
        NSData *plistXML = [[NSFileManager defaultManager] contentsAtPath:plistPath];
        
        self.languageDictionary = [[NSDictionary alloc] initWithDictionary:[NSPropertyListSerialization
                                                                            propertyListFromData:plistXML
                                                                            mutabilityOption:NSPropertyListMutableContainersAndLeaves
                                                                            format:&format
                                                                            errorDescription:&errorDesc]];
    }
    
    NSLog(@"Language: %@", self.languageISO2Code);
    
    if (!self.languageDictionary) {
        NSLog(@"Error reading Language plist: %@", errorDesc);
    }
}

- (LPLEDCubeAPI *)ledCubeAPI
{
    if (!_ledCubeAPI) {
        _ledCubeAPI = [LPLEDCubeAPI new];
    }
    return _ledCubeAPI;
}

+ (int)WEBServerPort
{
    return 80;
}

+ (int)TCPPort
{
    return 14350;
}

+ (int)UDPPort
{
    return 14350;
}

+ (NSString *)ftpUsername
{
    return @"";
}

+ (NSString *)ftpPassword
{
    return @"";
}

unsigned char crc_update(unsigned char icrc, unsigned char data)
{
    icrc = (unsigned char)(icrc ^ data);
    
    for (int i=0; i<8; i++) {
        if (icrc & 0x01)
            icrc = (unsigned char)((icrc >> 1) ^ 0x8C);
        else
            icrc = icrc >> 1;
    }
    
    
    return icrc;
}

unsigned char calcCRC(unsigned char data[], unsigned int length)
{
    unsigned char icrc = 0x42;
    
    for (int i=0; i<length; i++)
        icrc = crc_update(icrc,data[i]);
    
    return icrc;
}

+ (int)ftpPort
{
    return 21;
}

- (NSString *)fileSizeFormat:(unsigned long long)value
{
    NSString *string = @"";
    
    if(value >= (unsigned long long)1e9) {
        value %= (unsigned long long)1e9;
        value %= (unsigned long long)1e6;
        string = [NSString stringWithFormat:@"%03d.%03d GB", (unsigned int)(value / 1000), (unsigned int) (value % 1000)];
    } else if (value >= (unsigned long long)1e6) {
        value %= (unsigned long long)1e6;
        value %= (unsigned long long)1e6;
        string = [NSString stringWithFormat:@"%03d.%03d MB", (unsigned int)(value / 1000), (unsigned int) (value % 1000)];
    } else if (value >= 1000) {
        string = [NSString stringWithFormat:@"%d.%03d kB", (unsigned int)(value / 1000), (unsigned int)(value % 1000)];
    } else {
        string = [NSString stringWithFormat:@"%d B", (unsigned int)value];
	}
    
    return string;
}

+ (float)toastViewPadding
{
    return 10.0f;
}

- (NSMutableArray *)savedAnimations
{
    if (!_savedAnimations) {
        return _savedAnimations = [NSMutableArray new];
    }
    
    return _savedAnimations;
}

- (void)loadSavedAnimations
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    
    if ([userDefaults objectForKey:@"SavedAnimations"]) {
        NSData *encodedObject = [userDefaults objectForKey:@"SavedAnimations"];
        self.savedAnimations = (NSMutableArray *)[NSKeyedUnarchiver unarchiveObjectWithData:encodedObject];
    }
}

- (void)saveSavedAnimations
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSData *encodedObject = [NSKeyedArchiver archivedDataWithRootObject:self.savedAnimations];
    [userDefaults setObject:encodedObject forKey:@"SavedAnimations"];
    [userDefaults synchronize];
}

- (BOOL)checkIfSavedAnimationExists:(NSString *)fileName
{
    NSMutableArray *array = [self savedAnimations];
    
    for (LPAnimation *animation in array) {
        if ([animation.fileName isEqualToString:fileName]) {
            return YES;
            break;
        }
    }
    
    return NO;
}

@end

@implementation UIImage (SharedManagerImage)

- (UIImage *)imageTintedWithColor:(UIColor *)color
{
	if (color) {
		UIGraphicsBeginImageContextWithOptions([self size], NO, 0.0f);
		
		CGRect rect = CGRectZero;
		rect.size = [self size];
		
		[color set];
		UIRectFill(rect);
		
		[self drawInRect:rect blendMode:kCGBlendModeDestinationIn alpha:1.0f];
		
		UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
		UIGraphicsEndImageContext();
		
		return image;
	}
	
	return self;
}

- (UIImage *)changeImageSize:(CGSize)newSize
{
    UIGraphicsBeginImageContext(newSize);
    [self drawInRect:CGRectMake(0, 0, newSize.width, newSize.height)];
    UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    return newImage;
}

@end
