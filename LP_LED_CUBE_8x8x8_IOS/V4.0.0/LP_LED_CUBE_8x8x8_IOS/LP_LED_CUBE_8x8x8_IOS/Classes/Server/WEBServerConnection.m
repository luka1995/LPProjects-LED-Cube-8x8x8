//
//  WEBServerConnection.m
//  LP_LED_CUBE_8x8x8_IOS
//
//  Created by Luka Penger on 23/12/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "WEBServerConnection.h"


@implementation WEBServerConnection

- (BOOL)supportsMethod:(NSString *)method atPath:(NSString *)path
{
    if ([method isEqualToString:@"POST"]){
        if ([path isEqualToString:@"/index.html"])
        {
            return YES;
        }
    }
    
    return [super supportsMethod:method atPath:path];
}

- (BOOL)expectsRequestBodyFromMethod:(NSString *)method atPath:(NSString *)path
{
    if ([method isEqualToString:@"POST"] && [path isEqualToString:@"/index.html"]) {
        NSString* contentType = [request headerField:@"Content-Type"];
        NSUInteger paramsSeparator = [contentType rangeOfString:@";"].location;
        if (NSNotFound != paramsSeparator) {
            if (paramsSeparator < contentType.length - 1) {
                NSString* type = [contentType substringToIndex:paramsSeparator];
                if ([type isEqualToString:@"multipart/form-data"]) {
                    NSArray* params = [[contentType substringFromIndex:paramsSeparator + 1] componentsSeparatedByString:@";"];
                    for( NSString* param in params ) {
                        paramsSeparator = [param rangeOfString:@"="].location;
                        if( (NSNotFound == paramsSeparator) || paramsSeparator >= param.length - 1 ) {
                            continue;
                        }
                        NSString* paramName = [param substringWithRange:NSMakeRange(1, paramsSeparator-1)];
                        NSString* paramValue = [param substringFromIndex:paramsSeparator+1];
                        
                        if( [paramName isEqualToString: @"boundary"] ) {
                            // let's separate the boundary from content-type, to make it more handy to handle
                            [request setHeaderField:@"boundary" value:paramValue];
                        }
                    }
                    // check if boundary specified
                    [request headerField:@"boundary"];
                }
            }
        }

        return YES;
    }
    
    return [super expectsRequestBodyFromMethod:method atPath:path];
}

- (NSObject<HTTPResponse> *)httpResponseForMethod:(NSString *)method URI:(NSString *)path
{
    NSString *filePath = [self filePathForURI:path];
    
    // Convert to relative path
    
    NSString *documentRoot = [config documentRoot];
    
    if (![filePath hasPrefix:documentRoot]) {
        // Uh oh.
        // HTTPConnection's filePathForURI was supposed to take care of this for us.
        return nil;
    }
    
    NSString *relativePath = [filePath substringFromIndex:[documentRoot length]];

    if ([relativePath isEqualToString:@"/index.html"]) {
        if ([method isEqualToString:@"POST"]) {
            NSData *postData = [request body];
            
            if (postData) {
                NSString *postStr = [[NSString alloc] initWithData:postData encoding:NSUTF8StringEncoding];
                
                NSRange range = [postStr rangeOfString:@"="];
                if ([[postStr substringToIndex:range.location] isEqualToString:@"DELETE_FILE"]) {
                    NSString *filename = [postStr substringFromIndex:range.location+1];
                    
                    int i = 0;
                    int deleteIndex = 0;
                    BOOL delete = NO;
                    
                    for (LPAnimation *animation in [[LPSharedManager sharedManager] savedAnimations]) {
                        if ([animation.fileName isEqualToString:filename]) {
                            deleteIndex = i;
                            delete = YES;
                        }
                        i++;
                    }
                    
                    if (delete) {
                        [[[LPSharedManager sharedManager] savedAnimations] removeObjectAtIndex:deleteIndex];
                        [[LPSharedManager sharedManager] saveSavedAnimations];
                        
                        [[NSNotificationCenter defaultCenter] postNotificationName:@"WebServerReloadTableView" object:nil];
                    }
                }
            }
        }
        
        [[LPSharedManager sharedManager] loadSavedAnimations];
        
        NSMutableString *animationsList = [NSMutableString new];
        
        NSDictionary *dic = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"WEBServer"];
        
        int i = 1;
        
        for (LPAnimation *animation in [[LPSharedManager sharedManager] savedAnimations]) {
            [animationsList appendString:[NSString stringWithFormat:@"<tr align='center'><td class=\"table_data_row\">%d.</td>", i++]];
            [animationsList appendString:[NSString stringWithFormat:@"<td align='left' class=\"table_data_row\">%@</td>", animation.fileName]];
            [animationsList appendString:[NSString stringWithFormat:@"<td class=\"table_data_row\">%@</td>", [[LPSharedManager sharedManager] fileSizeFormat:[animation getBytesLength]]]];
            [animationsList appendString:[NSString stringWithFormat:@"<td class=\"table_data_row\">%d</td>", ([animation getBytesLength] / [LPCubeEffect size])]];
            [animationsList appendString:[NSString stringWithFormat:@"<form action='index.html' method='POST'><td class=\"table_data_row\"><input type='submit' value='%@'><input type='hidden' name='DELETE_FILE' value='%@'/></td></form>", [dic objectForKey:@"FileDeleteButton"], [animation fileName]]];
        }
        
        NSString *templatePath = [[config documentRoot] stringByAppendingPathComponent:@"index.html"];
        
        NSMutableDictionary *replacementDict = [NSMutableDictionary dictionary];
        [replacementDict setObject:animationsList forKey:@"ANIMATIONS_LIST"];
        
        [replacementDict setObject:[dic objectForKey:@"Title"] forKey:@"TITLE"];
        
        
        [replacementDict setObject:[dic objectForKey:@"FileCountHeader"] forKey:@"FILE_COUNT_HEADER"];
        [replacementDict setObject:[dic objectForKey:@"FileNameHeader"] forKey:@"FILE_NAME_HEADER"];
        [replacementDict setObject:[dic objectForKey:@"FileSizeHeader"] forKey:@"FILE_SIZE_HEADER"];
        [replacementDict setObject:[dic objectForKey:@"FileEffectsCountHeader"] forKey:@"FILE_EFFECTS_COUNT_HEADER"];
        [replacementDict setObject:[dic objectForKey:@"FileDeleteHeader"] forKey:@"FILE_DELETE_HEADER"];
        [replacementDict setObject:[dic objectForKey:@"UploadFileHeader"] forKey:@"UPLOAD_FILE_HEADER"];
        [replacementDict setObject:[dic objectForKey:@"UploadFileButton"] forKey:@"UPLOAD_FILE_BUTTON"];
        [replacementDict setObject:[dic objectForKey:@"Copyright"] forKey:@"COPYRIGHT"];

        return [[HTTPDynamicFileResponse alloc] initWithFilePath:templatePath forConnection:self separator:@"%%" replacementDictionary:replacementDict];
    }
    
    return [super httpResponseForMethod:method URI:path];
}

- (void)prepareForBodyWithSize:(UInt64)contentLength
{
    NSString *boundary = [request headerField:@"boundary"];
    parser = [[MultipartFormDataParser alloc] initWithBoundary:boundary formEncoding:NSUTF8StringEncoding];
    parser.delegate = self;
}

- (void)processBodyData:(NSData *)postDataChunk
{
    [parser appendData:postDataChunk];
    
    [request appendData:postDataChunk];
}

- (void)processStartOfPartWithHeader:(MultipartMessageHeader *) header
{
    MultipartMessageHeaderField *disposition = [header.fields objectForKey:@"Content-Disposition"];
    fileName = [[disposition.params objectForKey:@"filename"] lastPathComponent];
    
    if ((nil == fileName) || [fileName isEqualToString: @""]) {
        // it's either not a file part, or
        // an empty form sent. we won't handle it.
        return;
    }
    
    mutableData = [NSMutableData new];
}

- (void)processContent:(NSData*)data WithHeader:(MultipartMessageHeader*)header
{
    if (mutableData) {
        [mutableData appendData:data];
    }
}

- (void)processEndOfPartWithHeader:(MultipartMessageHeader*) header
{
    if (mutableData) {
        LPAnimation *animation = [LPAnimation animationWithBuffer:(uint8_t *)[mutableData bytes] length:(int)[mutableData length]];
        animation.fileName = fileName;
        
        if (![[LPSharedManager sharedManager] checkIfSavedAnimationExists:animation.fileName]) {
            [[[LPSharedManager sharedManager] savedAnimations] addObject:animation];
            
            [[LPSharedManager sharedManager] saveSavedAnimations];
            
            [[NSNotificationCenter defaultCenter] postNotificationName:@"WebServerReloadTableView" object:nil];
        }
    }
    
    mutableData = nil;
    fileName = nil;
}

- (BOOL)isPasswordProtected:(NSString *)path
{
    return NO;
}

- (NSString *)passwordForUser:(NSString *)username
{
    if([username isEqualToString:@"admin"])
    {
        return @"admin";
    } else {
        return [NSString stringWithFormat:@"%d",INT_MAX];
    }
}

- (BOOL)useDigestAccessAuthentication
{
    return YES;
}

- (BOOL)isBrowseable:(NSString *)path
{
    return YES;
}

@end
