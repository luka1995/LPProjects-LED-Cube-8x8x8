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

    [Crashlytics startWithAPIKey:@"a9459aeddf8d2b763e780f0e0b323a9b59627e19"];
    
    NSString *version = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
    [[NSUserDefaults standardUserDefaults] setObject:version forKey:@"Version"];
    
    // Set Notification
    if ([application respondsToSelector:@selector(isRegisteredForRemoteNotifications)])
    {
        // iOS 8 Notifications
        [application registerUserNotificationSettings:[UIUserNotificationSettings settingsForTypes:(UIUserNotificationTypeSound | UIUserNotificationTypeAlert | UIUserNotificationTypeBadge) categories:nil]];
        
        [application registerForRemoteNotifications];
    } else {
        // iOS < 8 Notifications
        [application registerForRemoteNotificationTypes:
         (UIRemoteNotificationTypeBadge | UIRemoteNotificationTypeAlert | UIRemoteNotificationTypeSound)];
    }
    
    // UINavigationBar style
    
    [UIApplication sharedApplication].statusBarStyle = UIStatusBarStyleLightContent;
    
    NSMutableDictionary *titleBarAttributes = [NSMutableDictionary dictionaryWithDictionary:[[UINavigationBar appearance] titleTextAttributes]];
    [titleBarAttributes setValue:[UIFont boldSystemFontOfSize:20.0f] forKey:NSFontAttributeName];
    [titleBarAttributes setValue:[UIColor whiteColor] forKey:NSForegroundColorAttributeName];
    
    [[UINavigationBar appearance] setTitleTextAttributes:titleBarAttributes];
    [[UINavigationBar appearance] setTranslucent:NO];
    [[UINavigationBar appearance] setBarTintColor:[UIColor colorWithRed:(0.0/255.0) green:(140.0/255.0) blue:(170.0/255.0) alpha:1.0f]];
    [[UIBarButtonItem appearance] setTintColor:[UIColor colorWithRed:(50.0/255.0) green:(50.0/255.0) blue:(50.0/255.0) alpha:1.0f]];
    [[UIBarButtonItem appearanceWhenContainedIn:[UISearchBar class], nil] setTintColor:[UIColor whiteColor]];
    
    // Init Controllers
    
    LPScanDevicesViewController *scanDevicesViewController = [[LPScanDevicesViewController alloc] initWithNibName:@"LPScanDevicesViewController" bundle:nil];
    UINavigationController *scanDevicesViewControllerNavCon = [[UINavigationController alloc] initWithRootViewController:scanDevicesViewController];
    
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        self.window.rootViewController = scanDevicesViewControllerNavCon;
    } else {
        LPEditCustomEffectViewController *editCustomEffectViewController = [[LPEditCustomEffectViewController alloc] initWithNibName:@"LPEditCustomEffectViewController" bundle:nil];
        UINavigationController *editCustomEffectViewControllerNavCon = [[UINavigationController alloc] initWithRootViewController:editCustomEffectViewController];

        LPSplitViewController *splitViewController = [[LPSplitViewController alloc] initWithMenuViewController:scanDevicesViewControllerNavCon detailsViewController:editCustomEffectViewControllerNavCon];
        [[LPSharedManager sharedManager] setSplitViewControllerIpad:splitViewController];
        
        self.window.rootViewController = splitViewController;
    }

    [self showHardwareAlertView];
    
    [self.window makeKeyAndVisible];
    return YES;
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    [self checkNetwork];
}

- (void)checkNetwork
{
    Reachability *reachability = [Reachability reachabilityForInternetConnection];
    
    NetworkStatus networkStatus = [reachability currentReachabilityStatus];
    
    if(((networkStatus != ReachableViaWiFi) && (networkStatus != ReachableViaWWAN)) || (networkStatus == NotReachable)) {
        NSDictionary *dictionary = [[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"NoInternetConnectionError"];
        
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:[dictionary objectForKey:@"Title"] message:[dictionary objectForKey:@"Description"] delegate:self cancelButtonTitle:[dictionary objectForKey:@"CancelButton"] otherButtonTitles:nil];
        
        [alertView show];
    }
}

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
    NSLog(@"My token is: %@", deviceToken);
    
    NSString *tokenString = [self stringWithDeviceToken:deviceToken];

    [[[LPSharedManager sharedManager] ledCubeAPI] uploadDeviceToken:tokenString successfulBlock:^(NSString *responseString) {
        NSLog(@"%@", responseString);
    } failureBlock:^(NSError *error) {
       NSLog(@"Failure: %@", error.description);
    }];
}

- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error
{
    NSLog(@"Failed to get token, error: %@", error);
}

- (NSString *)stringWithDeviceToken:(NSData *)deviceToken
{
    const char *data = [deviceToken bytes];
    NSMutableString *token = [NSMutableString string];
    
    for (int i=0; i<[deviceToken length]; i++) {
        [token appendFormat:@"%02.2hhX", data[i]];
    }
    
    return token;
}

- (void)showHardwareAlertView
{
    BOOL didRunBefore = [[NSUserDefaults standardUserDefaults] boolForKey:@"didRunBefore"];
    
    if (!didRunBefore) {
        [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"didRunBefore"];
        [[NSUserDefaults standardUserDefaults] synchronize];
        
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"FirstRunAlertViewTitle"] message:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"FirstRunAlertViewMessage"] delegate:self cancelButtonTitle:[[[LPSharedManager sharedManager] languageDictionary] objectForKey:@"AlertViewCloseButton"] otherButtonTitles:nil, nil];
        [alertView show];
    }
}

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
    if (url) {
        NSData *data = [NSData dataWithContentsOfURL:url];
        LPAnimation *animation = [LPAnimation animationWithBuffer:(uint8_t *)[data bytes] length:(int)[data length]];
        animation.fileName = [[url path] lastPathComponent];

        [[LPSharedManager sharedManager] loadSavedAnimations];
        
        if (![[LPSharedManager sharedManager] checkIfSavedAnimationExists:animation.fileName]) {
            [[[LPSharedManager sharedManager] savedAnimations] addObject:animation];
            
            [[LPSharedManager sharedManager] saveSavedAnimations];
        }
    }
    return YES;
}

@end
