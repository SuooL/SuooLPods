//
//  Tools.m
//  UtilityClass
//
//  Created by YHF-iOS on 15/1/13.
//  Copyright (c) 2015年 YHF. All rights reserved.
//

#import "Tools.h"


@implementation Tools

+ (void)beginNotiNetwork{
    [[CoreStatusMethod shareInstance] beginNotiNetwork];
}

+ (void)endNotiNetwork{
    [[CoreStatusMethod shareInstance] endNotiNetwork];
}

+ (NSString *)WANIPAddress{
    NSError *error;
    NSURL *ipURL = [NSURL URLWithString:@"http://pv.sohu.com/cityjson?ie=utf-8"];
    NSString *urlResult = [NSString stringWithContentsOfURL:ipURL encoding:1 error:&error];
    if (urlResult == nil || urlResult.length <= 0) {
        return @"127.0.0.1";
    }
    NSString *regex = @"\\{.*\\}";
    NSString *result = @"";
    NSString *jsonStr = @"";
    NSError *gexError = nil;
    NSRegularExpression *regular = [NSRegularExpression regularExpressionWithPattern:regex options:NSRegularExpressionCaseInsensitive error:&gexError];
    if (!gexError) {
        NSTextCheckingResult *checkingResult = [regular firstMatchInString:urlResult options:0 range:NSMakeRange(0, urlResult.length)];
        if (checkingResult) {
            NSRange checkRange = [checkingResult rangeAtIndex:0];
            if (checkRange.location != NSNotFound) {
                jsonStr = [urlResult substringWithRange:checkRange];
            }
        }
        if (jsonStr.length) {
            NSError *jsonError = nil;
            NSDictionary *ipDic = [NSJSONSerialization JSONObjectWithData:[jsonStr dataUsingEncoding:NSUTF8StringEncoding] options:NSJSONReadingMutableContainers error:&jsonError];
            if (!jsonError) {
                result = ipDic[@"cip"];
            }
        }
    }
    return result;
}

+ (NSString *)md5StringFromString:(NSString *)string;{
    if(string == nil || string.length == 0)
        return nil;
    const char *value = string.UTF8String;
    unsigned char outputBuffer[CC_MD5_DIGEST_LENGTH];
    CC_MD5(value, (CC_LONG)strlen(value), outputBuffer);
    NSMutableString *outputString = [[NSMutableString alloc] initWithCapacity:CC_MD5_DIGEST_LENGTH * 2];
    for(NSInteger count = 0; count < CC_MD5_DIGEST_LENGTH; count++){
        [outputString appendFormat:@"%02x",outputBuffer[count]];
    }
    return outputString;
}

+ (NSString *)random5BitNum{
    return [NSString stringWithFormat:@"%d%d%d%d%d",arc4random() % 10,arc4random() % 10,arc4random() % 10,arc4random() % 10,arc4random() % 10,nil];
}

+ (CheckInfoType)checkPhoneNumber:(NSString *)number{
    if (number == nil || number.length==0){
        return PhoneNumberEmptyCheckInfoType;
    }
    NSError *regularExError = NULL;
    NSRegularExpression *regularexpression = [NSRegularExpression regularExpressionWithPattern:@"^1[0-9]{2}[0-9]{8}$" options:NSRegularExpressionCaseInsensitive error:&regularExError];
    NSUInteger numberofMatch = [regularexpression numberOfMatchesInString:number
                                                                  options:NSMatchingReportProgress
                                                                    range:NSMakeRange(0, number.length)];
    if(numberofMatch <= 0){
        return PhoneNumberInvalidateCheckInfoType;
    }
    return SuccessCheckInfoType;
}

+ (CheckInfoType)checkEmail:(NSString *)email{
    if (email == nil || email.length==0){
        return EmailEmptyCheckInfoType;
    }
    NSString *emailRegex = @"[A-Z0-9a-z._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}";
    NSPredicate *emailTest = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", emailRegex];
    BOOL result = [emailTest evaluateWithObject:email];
    return result ? SuccessCheckInfoType : EmailInvalidateCheckInfoType;
}

+ (CheckInfoType)checkInternetSite:(NSString *)internetSite{
    if (internetSite == nil || internetSite.length==0){
        return InternetSiteEmptyCheckInfoType;
    }
    NSString *regex = @"^((http)|(https))+:[^\\s]+\\.[^\\s]*$";
    NSPredicate *internetSitePredicate = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", regex];
    BOOL result = [internetSitePredicate evaluateWithObject:internetSite];
    return result ? SuccessCheckInfoType : InternetSiteInvalidateCheckInfoType;
}

+ (BOOL)validateNumber:(NSString*)number {
    BOOL res = YES;
    NSCharacterSet* tmpSet = [NSCharacterSet characterSetWithCharactersInString:@"0123456789."];
    int i = 0;
    while (i < number.length) {
        NSString * string = [number substringWithRange:NSMakeRange(i, 1)];
        NSRange range = [string rangeOfCharacterFromSet:tmpSet];
        if (range.length == 0) {
            res = NO;
            break;
        }
        i++;
    }
    return res;
}

+ (void)setColorForLog {
    // Enable XcodeColors
    setenv("XcodeColors", "YES", 0);
    // Standard lumberjack initialization
    [DDTTYLogger sharedInstance].logFormatter = [[MyLogFormatter alloc] init];
    [DDLog addLogger:[DDTTYLogger sharedInstance]];
    // And then enable colors
    [[DDTTYLogger sharedInstance] setColorsEnabled:YES];
    // Check out log colors:
    [[DDTTYLogger sharedInstance] setForegroundColor:[UIColor redColor] backgroundColor:nil forFlag:DDLogFlagError];
    [[DDTTYLogger sharedInstance] setForegroundColor:[UIColor orangeColor] backgroundColor:nil forFlag:DDLogFlagWarning];
    [[DDTTYLogger sharedInstance] setForegroundColor:[UIColor purpleColor] backgroundColor:nil forFlag:DDLogFlagInfo];
    [[DDTTYLogger sharedInstance] setForegroundColor:[UIColor greenColor] backgroundColor:nil forFlag:DDLogFlagVerbose];
}


+ (CGSize)string:(NSString *)string rectSize:(CGSize)upperSize font:(UIFont *)aFont
{
    CGSize size = [string boundingRectWithSize:upperSize
                                       options:\
                   NSStringDrawingTruncatesLastVisibleLine |
                   NSStringDrawingUsesLineFragmentOrigin |
                   NSStringDrawingUsesFontLeading
                                    attributes:@{NSFontAttributeName :aFont}
                                       context:nil].size;
    
    return size;
}

@end
