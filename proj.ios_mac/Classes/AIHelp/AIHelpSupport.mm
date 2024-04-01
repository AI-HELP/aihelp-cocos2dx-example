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

static void AIHelp_onAIHelpInit() {
    if(s_theAIhelpInitCallBack) {
        s_theAIhelpInitCallBack();
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

void AIHelpSupport::showConversation() {
    [AIHelpSupportSDK showConversation];
}

void AIHelpSupport::showConversation(ConversationConfig conversationConfig) {
    bool alwaysOnline = conversationConfig.getAlwaysShowHumanSupportButtonInBotPage();
    string welcome = conversationConfig.getWelcomeMessage();
    string storyNode = conversationConfig.getStoryNode();
    
    AIHelpConversationConfigBuilder *builder = [[AIHelpConversationConfigBuilder alloc] init];
    builder.welcomeMessage = AIHelpParseCString(welcome.c_str());
    builder.alwaysShowHumanSupportButtonInBotPage = alwaysOnline;
    builder.storyNode = AIHelpParseCString(storyNode.c_str());
    builder.conversationIntent = conversationConfig.getConversationIntent() == HUMAN_SUPPORT?AIHelpConversationIntentHumanSupport:AIHelpConversationIntentBotSupport;
    [AIHelpSupportSDK showConversation:builder.build];
}

void AIHelpSupport::showAllFAQSections() {
    [AIHelpSupportSDK showAllFAQSections];
}

void AIHelpSupport::showAllFAQSections(FAQConfig faqConfig) {
    ConversationConfig conversationConfig = faqConfig.getConversationConfig();
    bool alwaysOnline = conversationConfig.getAlwaysShowHumanSupportButtonInBotPage();
    string welcome = conversationConfig.getWelcomeMessage();
    
    AIHelpConversationConfigBuilder *conversationConfigbuilder = [[AIHelpConversationConfigBuilder alloc] init];
    conversationConfigbuilder.welcomeMessage = AIHelpParseCString(welcome.c_str());
    conversationConfigbuilder.alwaysShowHumanSupportButtonInBotPage = alwaysOnline;
    conversationConfigbuilder.conversationIntent = conversationConfig.getConversationIntent() == HUMAN_SUPPORT?AIHelpConversationIntentHumanSupport:AIHelpConversationIntentBotSupport;
    
    AIHelpFAQConfigBuilder *faqBuilder = [[AIHelpFAQConfigBuilder alloc] init];
    if (faqConfig.getShowConversationMoment() == NEVER) {
        faqBuilder.showConversationMoment = AIHelpFAQShowConversationMomentNever;
    }else if (faqConfig.getShowConversationMoment() == ALWAYS) {
        faqBuilder.showConversationMoment = AIHelpFAQShowConversationMomentAlways;
    }else if (faqConfig.getShowConversationMoment() == AFTER_MARKING_UNHELPFUL) {
        faqBuilder.showConversationMoment = AIHelpFAQShowConversationMomentAfterMarkingUnhelpful;
    }
    faqBuilder.conversationConfig = conversationConfigbuilder.build;
    [AIHelpSupportSDK showAllFAQSections:faqBuilder.build];
}

void AIHelpSupport::showFAQSection(const string& sectionId) {
    NSString *nsSectionId = AIHelpParseCString(sectionId.c_str());
    [AIHelpSupportSDK showFAQSection:nsSectionId];
}

void AIHelpSupport::showFAQSection(const string& sectionId, FAQConfig faqConfig) {
    NSString *nsSectionId = AIHelpParseCString(sectionId.c_str());
    ConversationConfig conversationConfig = faqConfig.getConversationConfig();
    bool alwaysOnline = conversationConfig.getAlwaysShowHumanSupportButtonInBotPage();
    string welcome = conversationConfig.getWelcomeMessage();
    
    AIHelpConversationConfigBuilder *conversationConfigbuilder = [[AIHelpConversationConfigBuilder alloc] init];
    conversationConfigbuilder.welcomeMessage = AIHelpParseCString(welcome.c_str());
    conversationConfigbuilder.alwaysShowHumanSupportButtonInBotPage = alwaysOnline;
    conversationConfigbuilder.conversationIntent = conversationConfig.getConversationIntent() == HUMAN_SUPPORT?AIHelpConversationIntentHumanSupport:AIHelpConversationIntentBotSupport;
    
    AIHelpFAQConfigBuilder *faqBuilder = [[AIHelpFAQConfigBuilder alloc] init];
    if (faqConfig.getShowConversationMoment() == NEVER) {
        faqBuilder.showConversationMoment = AIHelpFAQShowConversationMomentNever;
    }else if (faqConfig.getShowConversationMoment() == ALWAYS) {
        faqBuilder.showConversationMoment = AIHelpFAQShowConversationMomentAlways;
    }else if (faqConfig.getShowConversationMoment() == AFTER_MARKING_UNHELPFUL) {
        faqBuilder.showConversationMoment = AIHelpFAQShowConversationMomentAfterMarkingUnhelpful;
    }
    faqBuilder.conversationConfig = conversationConfigbuilder.build;
    [AIHelpSupportSDK showFAQSection:nsSectionId config:faqBuilder.build];
}

void AIHelpSupport::showSingleFAQ(const string& faqId) {
    NSString *nsFaqId = AIHelpParseCString(faqId.c_str());
    [AIHelpSupportSDK showSingleFAQ:nsFaqId];
}

void AIHelpSupport::showSingleFAQ(const string& faqId, FAQConfig faqConfig) {
    NSString *nsFaqId = AIHelpParseCString(faqId.c_str());
    ConversationConfig conversationConfig = faqConfig.getConversationConfig();
    bool alwaysOnline = conversationConfig.getAlwaysShowHumanSupportButtonInBotPage();
    string welcome = conversationConfig.getWelcomeMessage();
    
    AIHelpConversationConfigBuilder *conversationConfigbuilder = [[AIHelpConversationConfigBuilder alloc] init];
    conversationConfigbuilder.welcomeMessage = AIHelpParseCString(welcome.c_str());
    conversationConfigbuilder.alwaysShowHumanSupportButtonInBotPage = alwaysOnline;
    conversationConfigbuilder.conversationIntent = conversationConfig.getConversationIntent() == HUMAN_SUPPORT?AIHelpConversationIntentHumanSupport:AIHelpConversationIntentBotSupport;
    
    AIHelpFAQConfigBuilder *faqBuilder = [[AIHelpFAQConfigBuilder alloc] init];
    if (faqConfig.getShowConversationMoment() == NEVER) {
        faqBuilder.showConversationMoment = AIHelpFAQShowConversationMomentNever;
    }else if (faqConfig.getShowConversationMoment() == ALWAYS) {
        faqBuilder.showConversationMoment = AIHelpFAQShowConversationMomentAlways;
    }else if (faqConfig.getShowConversationMoment() == AFTER_MARKING_UNHELPFUL) {
        faqBuilder.showConversationMoment = AIHelpFAQShowConversationMomentAfterMarkingUnhelpful;
    }
    faqBuilder.conversationConfig = conversationConfigbuilder.build;
    [AIHelpSupportSDK showSingleFAQ:nsFaqId config:faqBuilder.build];
}

void AIHelpSupport::showOperation() {
    [AIHelpSupportSDK showOperation];
}

void AIHelpSupport::showOperation(OperationConfig operationConfig) {
    NSString *nsBotTitle = AIHelpParseCString(operationConfig.getConversationTitle().c_str());
    ConversationConfig conversationConfig = operationConfig.getConversationConfig();
    bool alwaysOnline = conversationConfig.getAlwaysShowHumanSupportButtonInBotPage();
    string welcome = conversationConfig.getWelcomeMessage();
    
    AIHelpConversationConfigBuilder *conversationConfigbuilder = [[AIHelpConversationConfigBuilder alloc] init];
    conversationConfigbuilder.welcomeMessage = AIHelpParseCString(welcome.c_str());
    conversationConfigbuilder.alwaysShowHumanSupportButtonInBotPage = alwaysOnline;
    conversationConfigbuilder.conversationIntent = conversationConfig.getConversationIntent() == HUMAN_SUPPORT?AIHelpConversationIntentHumanSupport:AIHelpConversationIntentBotSupport;
    
    AIHelpOperationConfigBuilder *opConfigbuilder = [[AIHelpOperationConfigBuilder alloc] init];
    opConfigbuilder.selectIndex = operationConfig.getSelectIndex();
    opConfigbuilder.conversationTitle = nsBotTitle;
    opConfigbuilder.conversationConfig = conversationConfigbuilder.build;
    [AIHelpSupportSDK showOperation:opConfigbuilder.build];
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
    [AIHelpSupportSDK setNetworkCheckHostAddress:nsaddress callback:callback];
}

void AIHelpSupport::setOnAIHelpInitializedCallback(OnAIHelpInitializedCallback callback) {
    s_theAIhelpInitCallBack = callback;
    [AIHelpSupportSDK setOnInitializedCallback:AIHelp_onAIHelpInit];
}

void AIHelpSupport::startUnreadMessageCountPolling(OnMessageCountArrivedCallback callback) {
    s_theAIhelpUnreadMessageCallBack = callback;
    [AIHelpSupportSDK startUnreadMessageCountPolling:AIHelp_onAIHelpUnreadMessage];
}

void AIHelpSupport::setOnSpecificFormSubmittedCallback(OnSpecificFormSubmittedCallback callback) {
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
    [AIHelpSupportSDK setOnAIHelpSessionOpenCallback:callback];
}

void AIHelpSupport::setOnAIHelpSessionCloseCallback(OnAIHelpSessionCloseCallback callback) {
    [AIHelpSupportSDK setOnAIHelpSessionCloseCallback:callback];
}

void AIHelpSupport::setOnAIHelpOperationUnreadChangedCallback(OnAIHelpOperationUnreadCallback callback)
{
    [AIHelpSupportSDK setOnOperationUnreadChangedCallback:callback];
}

void setOnAIHelpSpecificUrlClickedCallback(OnAIHelpSpecificUrlClickedCallback callback)
{
    s_theAIHelpSpecificUrlClickedCallback = callback;
    [AIHelpSupportSDK setOnAIHelpSpecificUrlClickedCallback:callback];
}

#endif
