//
//  helloworldAppDelegate.h
//  helloworld
//
//  Created by Deepak Antony on 8/30/11.
//  Copyright 2011 DA. All rights reserved.
//

#import <UIKit/UIKit.h>

@class helloworldViewController;

@interface helloworldAppDelegate : NSObject <UIApplicationDelegate>

@property (nonatomic, retain) IBOutlet UIWindow *window;

@property (nonatomic, retain) IBOutlet helloworldViewController *viewController;

@end
