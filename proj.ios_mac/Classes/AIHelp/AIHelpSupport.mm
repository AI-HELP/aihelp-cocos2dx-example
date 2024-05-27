//
//  ECServiceCocos2dx.mm
//  AIHelp Cocos2dx iOS SDK
//
//
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#import "AIHelpSupport.h"
#import <AIHelpSupportSDK/AIHelpSupportSDK.h>

#pragma mark Utility methods.

static OnNetworkCheckResultCallback s_theAIhelpNetworkCheckCallBack = NULL;
static OnAIHelpInitializedCallback s_theAIhelpInitCallBack = NULL;
static OnAIHelpInitializedAsyncCallback s_theAIhelpInitAsyncCallBack = NULL;
static OnMessageCountArrivedCallback s_theAIhelpUnreadMessageCallBack = NULL;
static OnSpecificFormSubmittedCallback s_theAIhelpSpecificFormSubmittedCallback = NULL;
static OnAIHelpSessionOpenCallback s_theAIhelpOnAIHelpSessionOpenCallback = NULL;
static OnAIHelpSessionCloseCallback s_theAIhelpOnAIHelpSessionCloseCallback = NULL;
static OnAIHelpSpecificUrlClickedCallback s_theAIHelpSpecificUrlClickedCallback = NULL;

static void AIHelp_onNetworkCheckFinish(const char * log) {
    if(s_theAIhelpNetworkCheckCallBack && log != nil) {
        s_theAIhelpNetworkCheckCallBack(log);
    }
}

static void AIHelp_onAIHelpInit(const bool isSuccess, const char * message) {
    if(s_theAIhelpInitCallBack && message != nil) {
        s_theAIhelpInitCallBack(isSuccess, message);
    }
}

static void AIHelp_onAIHelpInitAsync(const bool isSuccess, const char * message) {
    if(s_theAIhelpInitAsyncCallBack && message != nil) {
        s_theAIhelpInitAsyncCallBack(isSuccess, message);
    }
}

static void AIHelp_onAIHelpUnreadMessage(const int unreadCount) {
    if(s_theAIhelpUnreadMessageCallBack) {
        s_theAIhelpUnreadMessageCallBack(unreadCount);
    }
}

static NSString* AIHelpParseCString(const char *cstring) {
    if (cstring == NULL) {
        return NULL;
    }
    NSString * nsstring = [[NSString alloc] initWithBytes:cstring
                                                   length:strlen(cstring)
                                                 encoding:NSUTF8StringEncoding];
    return nsstring;
}

#pragma mark - Interface implementation

void AIHelpSupport::init(const string& apiKey, const string& domainName, const string& appId) {
    NSString *nsApikey = AIHelpParseCString(apiKey.c_str());
    NSString *nsDomainName = AIHelpParseCString(domainName.c_str());
    NSString *nsAppId = AIHelpParseCString(appId.c_str());
    [AIHelpSupportSDK initWithApiKey:nsApikey domainName:nsDomainName appId:nsAppId];
}

void AIHelpSupport::init(const string& apiKey, const string& domainName, const string& appId, const string& language) {
    NSString *nsApikey = AIHelpParseCString(apiKey.c_str());
    NSString *nsDomainName = AIHelpParseCString(domainName.c_str());
    NSString *nsAppId = AIHelpParseCString(appId.c_str());
    NSString *nsLanguage = AIHelpParseCString(language.c_str());
    [AIHelpSupportSDK initWithApiKey:nsApikey domainName:nsDomainName appId:nsAppId language:nsLanguage];
}

bool AIHelpSupport::show(const string& entranceId) {
    return [AIHelpSupportSDK showWithEntranceId:AIHelpParseCString(entranceId.c_str())];
}

bool AIHelpSupport::show(AIHelpSupportApiConfig apiConfig) {
    AIHelpApiConfigBuilder *configBuilder = [[AIHelpApiConfigBuilder alloc] init];
    configBuilder.entranceId = AIHelpParseCString(apiConfig.getEntranceId().c_str());
    configBuilder.welcomeMessage = AIHelpParseCString(apiConfig.getWelcomeMessage().c_str());
    return [AIHelpSupportSDK showWithApiConfig:configBuilder.build];
}

void AIHelpSupport::updateUserInfo(AIHelpSupportUserConfig userConfig) {
    NSString *nsuserId = AIHelpParseCString(userConfig.getUserId().c_str());
    NSString *nsuserName = AIHelpParseCString(userConfig.getUserName().c_str());
    NSString *nsserverId = AIHelpParseCString(userConfig.getServerId().c_str());
    NSString *nsuserTags = AIHelpParseCString(userConfig.getUserTags().c_str());
    NSString *nscustomData = AIHelpParseCString(userConfig.getCustomData().c_str());
    
    AIHelpUserConfigBuilder *userBuilder = [[AIHelpUserConfigBuilder alloc] init];
    userBuilder.userId = nsuserId;
    userBuilder.userName = nsuserName;
    userBuilder.serverId = nsserverId;
    userBuilder.isSyncCrmInfo = userConfig.getIsSyncCrmInfo();
    if ([nsuserTags containsString:@","] && [nsuserTags componentsSeparatedByString:@","]) {
        userBuilder.userTags = [nsuserTags componentsSeparatedByString:@","];
    }
    if (nscustomData && nscustomData.length) {
        NSData *jsonData = [nscustomData dataUsingEncoding:NSUTF8StringEncoding];
        NSError *error;
        NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:jsonData options:NSJSONReadingMutableContainers error:&error];
        if (dic) {
            userBuilder.customData = dic;
        }
    }
    [AIHelpSupportSDK updateUserInfo:userBuilder.build];
}

void AIHelpSupport::resetUserInfo() {
    [AIHelpSupportSDK resetUserInfo];
}

void AIHelpSupport::updateSDKLanguage(const string& language) {
    NSString *nslanguage = AIHelpParseCString(language.c_str());
    [AIHelpSupportSDK updateSDKLanguage:nslanguage];
}

void AIHelpSupport::setUploadLogPath(const string& path) {
    NSString *nspath = AIHelpParseCString(path.c_str());
    [AIHelpSupportSDK setUploadLogPath:nspath];
}

void AIHelpSupport::setPushTokenAndPlatform(const string& pushToken, PushPlatform platform) {
    NSString *nspushToken = AIHelpParseCString(pushToken.c_str());
    AIHelpTokenPlatform ePlatform;
    switch (platform) {
        case APNS:
            ePlatform = AIHelpTokenPlatformAPNS;
            break;
        case FIREBASE:
            ePlatform = AIHelpTokenPlatformFirebase;
            break;
        case JPUSH:
            ePlatform = AIHelpTokenPlatformJpush;
            break;
        case GETUI:
            ePlatform = AIHelpTokenPlatformGeTui;
            break;
        default:
            break;
    }
    [AIHelpSupportSDK setPushToken:nspushToken pushPlatform:ePlatform];
}

string AIHelpSupport::getSDKVersion() {
    return [AIHelpSupportSDK getSDKVersion].UTF8String;
}

bool AIHelpSupport::isAIHelpShowing() {
    return [AIHelpSupportSDK isAIHelpShowing];
}

void AIHelpSupport::enableLogging(bool enable) {
    [AIHelpSupportSDK enableLogging:enable];
}

void AIHelpSupport::showUrl(const string& url) {
    NSString *urlStr = AIHelpParseCString(url.c_str());
    [AIHelpSupportSDK showUrl:urlStr];
}

void AIHelpSupport::additionalSupportFor(PublishCountryOrRegion countryOrRegion) {
    AIHelpPublishCountryOrRegion tmpCountryOrRegion = AIHelpCN;
    if(countryOrRegion == IN) {
        tmpCountryOrRegion = AIHelpIN;
    }
    [AIHelpSupportSDK additionalSupportFor:tmpCountryOrRegion];
}

void AIHelpSupport::setSDKInterfaceOrientationMask(int interfaceOrientationMask) {
    [AIHelpSupportSDK setSDKInterfaceOrientationMask:interfaceOrientationMask];
}

void AIHelpSupport::setNetworkCheckHostAddress(const string& address, OnNetworkCheckResultCallback callback) {
    NSString *nsaddress = AIHelpParseCString(address.c_str());
    s_theAIhelpNetworkCheckCallBack = callback;
    [AIHelpSupportSDK setNetworkCheckHostAddress:nsaddress callback:AIHelp_onNetworkCheckFinish];
}

void AIHelpSupport::setOnAIHelpInitializedCallback(OnAIHelpInitializedCallback callback) {
    s_theAIhelpInitCallBack = callback;
    [AIHelpSupportSDK setOnInitializedCallback:AIHelp_onAIHelpInit];
}

void AIHelpSupport::setOnAIHelpInitializedAsyncCallback(OnAIHelpInitializedCallback callback) {
    s_theAIhelpInitAsyncCallBack = callback;
    [AIHelpSupportSDK setOnInitializedAsyncCallback:AIHelp_onAIHelpInitAsync];
}

void AIHelpSupport::startUnreadMessageCountPolling(OnMessageCountArrivedCallback callback) {
    s_theAIhelpUnreadMessageCallBack = callback;
    [AIHelpSupportSDK startUnreadMessageCountPolling:AIHelp_onAIHelpUnreadMessage];
}

void AIHelpSupport::setOnSpecificFormSubmittedCallback(OnSpecificFormSubmittedCallback callback) {
    s_theAIhelpSpecificFormSubmittedCallback = callback;
    [AIHelpSupportSDK setOnSpecificFormSubmittedCallback:callback];
}

void AIHelpSupport::setSDKAppearanceMode(int mode) {
    [AIHelpSupportSDK setSDKAppearanceMode:mode];
}

void AIHelpSupport::setSDKEdgeInsets(float top,float bottom,bool enable) {
    [AIHelpSupportSDK setSDKEdgeInsetsWithTop:top bottom:bottom enable:enable];
}

void AIHelpSupport::setSDKEdgeColor(float red,float green,float blue,float alpha) {
    [AIHelpSupportSDK setSDKEdgeColorWithRed:red green:green blue:blue alpha:alpha];
}

void AIHelpSupport::setOnAIHelpSessionOpenCallback(OnAIHelpSessionOpenCallback callback) {
    s_theAIhelpOnAIHelpSessionOpenCallback = callback;
    [AIHelpSupportSDK setOnAIHelpSessionOpenCallback:callback];
}

void AIHelpSupport::setOnAIHelpSessionCloseCallback(OnAIHelpSessionCloseCallback callback) {
    s_theAIhelpOnAIHelpSessionCloseCallback = callback;
    [AIHelpSupportSDK setOnAIHelpSessionCloseCallback:callback];
}

void AIHelpSupport::setOnAIHelpSpecificUrlClickedCallback(OnAIHelpSpecificUrlClickedCallback callback)
{
    s_theAIHelpSpecificUrlClickedCallback = callback;
    [AIHelpSupportSDK setOnAIHelpSpecificUrlClickedCallback:callback];
}

#endif
