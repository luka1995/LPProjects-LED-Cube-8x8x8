//
//  AppDelegate.m
//  LP_LED_CUBE_8x8x8
//
//  Created by Luka Penger on 11/06/14.
//  Copyright (c) 2014 Luka Penger. All rights reserved.
//

#import "AppDelegate.h"


@interface AppDelegate ()

@end


@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    self.window.backgroundColor = [UIColor whiteColor];

    NSString *version = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
    [[NSUserDefaults standardUserDefaults] setObject:version forKey:@"Version"];

    LPScanViewController *scanViewController = [[LPScanViewController alloc] initWithNibName:@"LPScanViewController_iPhone" bundle:nil];
    UINavigationController *scanNavCon = [[UINavigationController alloc] initWithRootViewController:scanViewController];
    self.window.rootViewController = scanNavCon;
    
    BOOL didRunBefore = [[NSUserDefaults standardUserDefaults] boolForKey:@"didRunBefore"];
    
    if (!didRunBefore) {
        [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"didRunBefore"];
        [[NSUserDefaults standardUserDefaults] synchronize];
        
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"LED Cube 8x8x8" message:@"This application requires hardware to run. For more information visit http://lpprojects.eu" delegate:self cancelButtonTitle:@"Close" otherButtonTitles:nil, nil];
        [alertView show];
    }
    
    [self.window makeKeyAndVisible];
    return YES;
}

@end
