//
//  AppDelegate.m
//  test_pb_xcode
//
//  Created by dang ta on 15/12/24.
//  Copyright © 2015年 dang ta. All rights reserved.
//

#import "AppDelegate.h"
#import "impb_interface.h"

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    unsigned char *szOutParam=new unsigned char[4000];
    int nOutLen=4000;
    int nSeq=123;
    int ret = IMReq(IM_LOGIN, IM_Login_Req, string("{\"sid\":0,\"cid\":0,\"online_status\":1,\"user_name\":\"100050\",\"password\":\"12345678901234567890123456789012\",\"client_type\":1,\"client_version\":\"100.0.1\",\"seqNo\":123}"), szOutParam, nOutLen);
    
    NSLog(@"================================ret=%d", ret);
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
