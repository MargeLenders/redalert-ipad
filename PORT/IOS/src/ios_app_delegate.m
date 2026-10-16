#import <UIKit/UIKit.h>
#import <objc/runtime.h>

#include <stdio.h>
#include <stdlib.h>

#import "SDL_uikitappdelegate.h"

static void RedAlertOrientationDebug(char const *message)
{
	if (getenv("RA_IOS_ORIENTATION_DEBUG")) {
		fprintf(stderr, "RA_IOS_ORIENTATION: %s\n", message);
		NSLog(@"RA_IOS_ORIENTATION: %s", message);
	}
}

@interface RedAlertIOSDelegate : SDLUIKitDelegate
- (void)redAlert_requestLandscapeGeometry;
@end

@interface RedAlertSceneDelegate : UIResponder <UIWindowSceneDelegate>
@property (strong, nonatomic) UIWindow *window;
@end

static UIWindowScene *s_activeWindowScene = nil;
static void (*s_orig_makeKeyAndVisible)(id, SEL) = NULL;

static void RedAlert_makeKeyAndVisible(UIWindow *self, SEL _cmd)
{
	if (self.windowScene == nil) {
		if (s_activeWindowScene) {
			self.windowScene = s_activeWindowScene;
		} else {
			for (UIScene *scene in [UIApplication sharedApplication].connectedScenes) {
				if ([scene isKindOfClass:[UIWindowScene class]] && scene.activationState != UISceneActivationStateUnattached) {
					self.windowScene = (UIWindowScene *)scene;
					s_activeWindowScene = (UIWindowScene *)scene;
					break;
				}
			}
		}
	}
	if (s_orig_makeKeyAndVisible) {
		s_orig_makeKeyAndVisible(self, _cmd);
	}
}

@implementation RedAlertSceneDelegate

- (void)scene:(UIScene *)scene willConnectToSession:(UISceneSession *)session options:(UISceneConnectionOptions *)connectionOptions
{
	RedAlertOrientationDebug("RedAlertSceneDelegate willConnectToSession");
	if ([scene isKindOfClass:[UIWindowScene class]]) {
		s_activeWindowScene = (UIWindowScene *)scene;
		UIWindow *appWindow = [(SDLUIKitDelegate *)[UIApplication sharedApplication].delegate window];
		if (appWindow && appWindow.windowScene == nil) {
			appWindow.windowScene = s_activeWindowScene;
		}
	}
}

- (void)sceneDidBecomeActive:(UIScene *)scene
{
	RedAlertOrientationDebug("RedAlertSceneDelegate didBecomeActive");
	if ([scene isKindOfClass:[UIWindowScene class]]) {
		s_activeWindowScene = (UIWindowScene *)scene;
	}
	RedAlertIOSDelegate *delegate = (RedAlertIOSDelegate *)[UIApplication sharedApplication].delegate;
	if ([delegate respondsToSelector:@selector(redAlert_requestLandscapeGeometry)]) {
		[delegate redAlert_requestLandscapeGeometry];
	}
}

- (UIWindow *)window
{
	UIWindow *w = _window;
	if (!w) {
		w = [(SDLUIKitDelegate *)[UIApplication sharedApplication].delegate window];
	}
	return w;
}

@end

@interface SDLUIKitDelegate (RedAlertPrivate)
- (void)postFinishLaunch;
@end

static NSString *RedAlertGetAppDelegateClassName(id self, SEL selector)
{
	return @"RedAlertIOSDelegate";
}

@implementation RedAlertIOSDelegate

+ (void)load
{
	Class meta_class = object_getClass([SDLUIKitDelegate class]);
	Method method = class_getClassMethod([SDLUIKitDelegate class], @selector(getAppDelegateClassName));
	char const *types = method ? method_getTypeEncoding(method) : "@@:";
	class_replaceMethod(meta_class, @selector(getAppDelegateClassName), (IMP)RedAlertGetAppDelegateClassName, types);
	RedAlertOrientationDebug("installed delegate class override");

	Method makeKeyMethod = class_getInstanceMethod([UIWindow class], @selector(makeKeyAndVisible));
	if (makeKeyMethod) {
		s_orig_makeKeyAndVisible = (void (*)(id, SEL))method_getImplementation(makeKeyMethod);
		class_replaceMethod([UIWindow class], @selector(makeKeyAndVisible), (IMP)RedAlert_makeKeyAndVisible, method_getTypeEncoding(makeKeyMethod));
		RedAlertOrientationDebug("installed UIWindow makeKeyAndVisible hook");
	}
}

- (UISceneConfiguration *)application:(UIApplication *)application configurationForConnectingSceneSession:(UISceneSession *)connectingSceneSession options:(UISceneConnectionOptions *)options
{
	RedAlertOrientationDebug("RedAlertIOSDelegate configurationForConnectingSceneSession");
	UISceneConfiguration *config = [[UISceneConfiguration alloc] initWithName:@"Default Configuration" sessionRole:connectingSceneSession.role];
	config.delegateClass = [RedAlertSceneDelegate class];
	return [config autorelease];
}

- (void)redAlert_requestLandscapeGeometry
{
	if (@available(iOS 16.0, *)) {
		UIWindowScene *window_scene = nil;
		UIWindow *window = [self window];
		if ([window respondsToSelector:@selector(windowScene)]) {
			window_scene = window.windowScene;
		}
		if (!window_scene) {
			window_scene = s_activeWindowScene;
		}
		if (!window_scene) {
			for (UIScene *scene in [UIApplication sharedApplication].connectedScenes) {
				if ([scene isKindOfClass:[UIWindowScene class]] && scene.activationState != UISceneActivationStateUnattached) {
					window_scene = (UIWindowScene *)scene;
					break;
				}
			}
		}
		if (!window_scene) {
			RedAlertOrientationDebug("no window scene for landscape request");
			return;
		}

		UIWindowSceneGeometryPreferencesIOS *preferences =
			[[UIWindowSceneGeometryPreferencesIOS alloc] initWithInterfaceOrientations:UIInterfaceOrientationMaskLandscape];
		[window_scene requestGeometryUpdateWithPreferences:preferences errorHandler:^(NSError *error) {
			(void)error;
			RedAlertOrientationDebug("landscape geometry request failed");
		}];
		[preferences release];

		for (UIWindow *scene_window in window_scene.windows) {
			[scene_window.rootViewController setNeedsUpdateOfSupportedInterfaceOrientations];
		}
	} else {
		[UIViewController attemptRotationToDeviceOrientation];
	}
}

- (UIInterfaceOrientationMask)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(UIWindow *)window
{
	return UIInterfaceOrientationMaskLandscape;
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	RedAlertOrientationDebug("RedAlertIOSDelegate didFinishLaunching");
	BOOL launched = [super application:application didFinishLaunchingWithOptions:launchOptions];
	[self redAlert_requestLandscapeGeometry];
	return launched;
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
	RedAlertOrientationDebug("RedAlertIOSDelegate didBecomeActive");
	[self redAlert_requestLandscapeGeometry];
}

- (void)postFinishLaunch
{
	RedAlertOrientationDebug("RedAlertIOSDelegate postFinishLaunch");
	[self redAlert_requestLandscapeGeometry];
	[super postFinishLaunch];
}

@end
