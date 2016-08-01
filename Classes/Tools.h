//
//  Tools.h
//  UtilityClass
//
//  Created by YHF-iOS on 15/1/13.
//  Copyright (c) 2015年 YHF. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ColorUtils.h"
#import "NSString+Utils.h"
#import "UIImage+Utils.h"
#import "NSDate+Utils.h"
#import "TKTimer.h"
#import "EnumType.h"
#import "UIView+Frame.h"
#import "UIView+TapHideKeyboard.h"
#import "NSDictionary+Unicode.h"
#import <CommonCrypto/CommonDigest.h>
#import "MyLogFormatter.h"
#import <CocoaLumberjack/CocoaLumberjack.h>
#import "CoreStatusMethod.h"

@interface Tools : NSObject

/**
 *  @author yhfwork, 15-10-14 11:10:03
 *
 *  @brief  开发框架
 
 MVVM模式
 
 网络层：网络访问YTKNetwork ，图片缓存SDWebImage
 
 视图层：Masonry适配   界面刷新：MJRefresh  提醒用户评分：UAAppReviewManager  展示空数据：DZNEmptyDataSet  应用中嵌套Web页面: TOWebViewController || KINWebBrowser   弹出卡片视图:CNPPopupController	 进度工具M13ProgressSuite	iOS Messages UI库JSQMessagesViewController	自动滚动的导航条TLYShyNavBar
 
 模型层：数据存储YTKKeyValueStore || keyModelStore  JSON解析与对象映射的库：MJExtension  存放账号密码组件UICKeyChainStore
 
 测试：单元测试：Xcode7自带XCTest
 
 
 第三方：性能监测：OneAPM     IM：融云  分享：ShareSDK  消息推送：Jpush  统计分析：友盟 || TakingData
 
 */

#ifdef DEBUG

/**
 *  debugLog输出,定位到具体类,函数,代码行数
 */

#define TK_DebugLog(xx, ...)  NSLog(@"%s(%d): " xx, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)

#else

#endif

#pragma mark - 宏定义

#pragma mark - 设备信息

/**
 *  @brief  版本号
 */
#define TK_APP_VERSION [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"]
#define TK_APP_BUILDVERSION  [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleVersion"]
/**
 *  @brief  APP名称
 */
#define TK_APP_NAME [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleDisplayName"]
/**
 *  @brief  用户设备系统版本
 */
#define TK_DEVICE_VERSION   [[UIDevice currentDevice] systemVersion]
/**
 *  @brief  Bundle Identifier
 */
#define TK_BundleIdentifier [[[NSBundle mainBundle] infoDictionary] objectForKey:(__bridge NSString *)kCFBundleIdentifierKey]

/**
 *  @brief  屏幕适配：以 iphone5,5s为标准,进行转换iphone6,6s,6Plus,6sPlus / iphone4,4s,类型类似PNG图片，1x，2x，3x的比例
 */
#define TK_PX(v)         (TK_IS_IPHONE_4_OR_LESS ? (v / 2.0) : (TK_IS_IPHONE_5 ? v : ((TK_IS_IPHONE_6 || TK_IS_IPHONE_6P) ? (v * 3.0 / 2.0) : (v * 3.0 / 2.0)) ))

#pragma mark - 函数相关

/**
 *  @brief  Window Identifier
 */
#define TK_KeyWindow [UIApplication sharedApplication].keyWindow
/**
 *  @brief  提示框
 */
#define TK_TipsAlert(_S_, ...)     [[[UIAlertView alloc] initWithTitle:@"提示" message:[NSString stringWithFormat:(_S_), ##__VA_ARGS__] delegate:nil cancelButtonTitle:@"知道了" otherButtonTitles:nil] show]

//获取根目录
#define TK_PATH_OF_APP_HOME    NSHomeDirectory()
//获取Documents文件夹目录
#define TK_PATH_OF_DOCUMENT    [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0]
//获取Cache目录
#define TK_PATH_OF_Cache       [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0]
//获取Library目录
#define TK_PATH_OF_Library     [NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES) objectAtIndex:0]
//获取temp目录
#define TK_PATH_OF_TEMP        NSTemporaryDirectory()

/**
 *  @author taiyi, 15-10-28 13:10:36
 *
 *  @brief  测试代码块执行时间
 *
 *  @return 执行代码放TICK TOCK中间
 */
#define TICK   NSDate *startTime = [NSDate date]
#define TOCK   NSLog(@"Time: %f", -[startTime timeIntervalSinceNow])

/**
 *  系统版本比较
 *  @param v 系统版本
 */
//系统版本等于v
#define TK_SYSTEM_VERSION_EQUAL_TO(v)                  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedSame)
//系统版本高于v
#define TK_SYSTEM_VERSION_GREATER_THAN(v)              ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedDescending)
//系统版本大于或等于v
#define TK_SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)
//系统版本低于v
#define TK_SYSTEM_VERSION_LESS_THAN(v)                 ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)
//系统版本小于或等于v
#define TK_SYSTEM_VERSION_LESS_THAN_OR_EQUAL_TO(v)     ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedDescending)

/**
 *  屏幕大小
 */
#define TK_SCREEN_WIDTH ([[UIScreen mainScreen] bounds].size.width)
#define TK_SCREEN_HEIGHT ([[UIScreen mainScreen] bounds].size.height)
#define TK_SCREEN_MAX_LENGTH (MAX(TK_SCREEN_WIDTH, TK_SCREEN_HEIGHT))
#define TK_SCREEN_MIN_LENGTH (MIN(TK_SCREEN_WIDTH, TK_SCREEN_HEIGHT))

/**
 *  判断设备
 */
#define TK_IS_IPAD (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
#define TK_IS_IPHONE (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone)
#define TK_IS_RETINA ([[UIScreen mainScreen] scale] >= 2.0)

#define TK_IS_IPHONE_4_OR_LESS (TK_IS_IPHONE && TK_SCREEN_MAX_LENGTH < 568.0)
#define TK_IS_IPHONE_5 (TK_IS_IPHONE && TK_SCREEN_MAX_LENGTH == 568.0)
#define TK_IS_IPHONE_6 (TK_IS_IPHONE && TK_SCREEN_MAX_LENGTH == 667.0)
#define TK_ISLAGER_IPHONE_6 (TK_IS_IPHONE && TK_SCREEN_MAX_LENGTH >= 667.0)
#define TK_IS_IPHONE_6P (TK_IS_IPHONE && TK_SCREEN_MAX_LENGTH == 736.0)

#define LS_WIDTH(W) (TK_IS_IPHONE_4_OR_LESS ? (W*YYScreenSize().width/720.0) : (W/1.78))

#define FontSize(H) (H/1.78)


#define font22 [UIFont systemFontOfSize:FontSize(22)]
#define font26 [UIFont systemFontOfSize:FontSize(26)]
#define font28 [UIFont systemFontOfSize:FontSize(28)]
#define font30 [UIFont systemFontOfSize:FontSize(30)]
#define font32 [UIFont systemFontOfSize:FontSize(32)]
#define font34 [UIFont systemFontOfSize:FontSize(34)]
#define font36 [UIFont systemFontOfSize:FontSize(36)]
#define font38 [UIFont systemFontOfSize:FontSize(38)]
#define font40 [UIFont systemFontOfSize:FontSize(40)]
#define font46 [UIFont systemFontOfSize:FontSize(46)]
#define font54 [UIFont systemFontOfSize:FontSize(54)]

#define TK_RGB(A, B, C)        [UIColor colorWithRed:A/255.0 green:B/255.0 blue:C/255.0 alpha:1.0]

#pragma mark - Method
#pragma mark - 网络相关

/**
 *  @author taiyi, 16-01-13 17:01:03
 *
 *  @brief 开启网络监听     获取监听结果通知： CoreNetworkOpenNotification(网络打开)
 */
+ (void)beginNotiNetwork;
/**
 *  @author taiyi, 16-01-13 17:01:03
 *
 *  @brief 关闭网络监听     获取监听结果通知： CoreNetworkOpenNotification(网络打开)
 */
+ (void)endNotiNetwork;

/**
 *  外网 IP地址
 */
+ (NSString *)WANIPAddress;

#pragma mark - 数据相关

+ (NSString *)md5StringFromString:(NSString *)string;

/**
 *  生成5位随机数
 *
 *  @return
 */
+ (NSString *)random5BitNum;
/**
 *  @author yhfwork, 15-10-21 17:10:14
 *
 *  @brief  校验手机号
 */
+ (CheckInfoType)checkPhoneNumber:(NSString *)number;
/**
 *  @author yhfwork, 15-10-22 09:10:09
 *
 *  @brief  校验邮箱Email
 */
+ (CheckInfoType)checkEmail:(NSString *)email;

/**
 *  @author yhfwork, 15-10-22 09:10:09
 *
 *  @brief  校验网址
 */
+ (CheckInfoType)checkInternetSite:(NSString *)internetSite;

/**
 *  检查字符串是否为数字
 *
 *  @param number 字符串
 *
 *  @return
 */
+ (BOOL)validateNumber:(NSString*)number;

/**
 *  设置 Log 颜色
 */
+ (void)setColorForLog;

/**
 *  根据一段文字动态计算出用于显示的 UILabel 或 UITextView 等控件的显示大小
 *
 *  @param string    字符串
 *  @param upperSize 最大
 *  @param aFont     字体大小
 *
 *  @return  返回 framesize
 */
+ (CGSize)string:(NSString *)string rectSize:(CGSize)upperSize font:(UIFont *)aFont;

@end
