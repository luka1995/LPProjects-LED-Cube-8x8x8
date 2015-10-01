//
//  WEBServerConnection.h
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 23/12/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "HTTPConnection.h"
#import <Foundation/Foundation.h>
#import "LPSharedManager.h"

#import <CocoaHTTPServer/HTTPMessage.h>
#import <CocoaHTTPServer/DDNumber.h>
#import <CocoaHTTPServer/HTTPDynamicFileResponse.h>
#import <CocoaHTTPServer/HTTPDataResponse.h>
#import <CocoaHTTPServer/MultipartFormDataParser.h>
#import <CocoaHTTPServer/MultipartMessageHeaderField.h>
#import <CocoaHTTPServer/HTTPFileResponse.h>


@class MultipartFormDataParser;

@interface WEBServerConnection : HTTPConnection
{
    MultipartFormDataParser *parser;
    NSMutableData *mutableData;
    NSString *fileName;
}

@end
