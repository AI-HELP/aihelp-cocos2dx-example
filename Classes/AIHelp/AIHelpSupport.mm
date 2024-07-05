//
//  ECServiceCocos2dx.mm
//  AIHelp Cocos2dx iOS SDK
//
//
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#import "AIHelpSupport.h"
#import <AIHelpSupportSDK/AIHelpSupportSDK.h>

using namespace AIHelp;

#pragma mark Utility methods.

static NSString* AIHelpParseCString(const char *cstring) {
    if (cstring == NULL) {
        return NULL;
    }
    NSString * nsstring = [[NSString alloc] initWithBytes:cstring
                                                   length:strlen(cstring)
                                                 encoding:NSUTF8StringEncoding];
    return nsstring;
}

static AIHelpUserConfig* getAIHelpUserConfig(AIHelp::UserConfig userConfig) {
    NSString *nsuserName = AIHelpParseCString(userConfig.getUserName().c_str());
    NSString *nsserverId = AIHelpParseCString(userConfig.getServerId().c_str());
    NSString *nsuserTags = AIHelpParseCString(userConfig.getUserTags().c_str());
    NSString *nscustomData = AIHelpParseCString(userConfig.getCustomData().c_str());
    
    AIHelpUserConfigBuilder *userBuilder = [[AIHelpUserConfigBuilder alloc] init];
    userBuilder.userName = nsuserName;
    userBuilder.serverId = nsserverId;
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
    return userBuilder.build;
}

// Function to extract a value from JSON
std::string extractValue(const std::string& jsonString, const std::string& key) {
    std::string value;
    std::istringstream iss(jsonString);
    std::string line;

    while (std::getline(iss, line)) {
        size_t keyPos = line.find("\"" + key + "\"");
        if (keyPos != std::string::npos) {
            // Found the key, extract the value
            size_t colonPos = line.find(':', keyPos);
            if (colonPos != std::string::npos) {
                size_t valueStart = line.find_first_not_of(" \t\r\n", colonPos + 1);
                if (valueStart != std::string::npos) {
                    size_t valueEnd = line.find_last_not_of(" \t\r\n");
                    value = line.substr(valueStart, valueEnd - valueStart + 1);
                    // Remove surrounding quotes if present
                    if (!value.empty() && (value.front() == '"' && value.back() == '"')) {
                        value = value.substr(1, value.length() - 2);
                    }
                    break;
                }
            }
        }
    }
    return value;
}

#pragma mark - Interface implementation

void AIHelpSupport::initialize(const std::string& domainName, const std::string& appId, const std::string& language) {
    NSString *nsDomainName = AIHelpParseCString(domainName.c_str());
    NSString *nsAppId = AIHelpParseCString(appId.c_str());
    NSString *nsLanguage = AIHelpParseCString(language.c_str());
    [AIHelpSupportSDK initializeWithDomainName:nsDomainName appId:nsAppId language:nsLanguage];
}

bool AIHelpSupport::show(const std::string& entranceId) {
    return [AIHelpSupportSDK showWithEntranceId:AIHelpParseCString(entranceId.c_str())];
}

bool AIHelpSupport::show(ApiConfig apiConfig) {
    AIHelpApiConfigBuilder *configBuilder = [[AIHelpApiConfigBuilder alloc] init];
    configBuilder.entranceId = AIHelpParseCString(apiConfig.getEntranceId().c_str());
    configBuilder.welcomeMessage = AIHelpParseCString(apiConfig.getWelcomeMessage().c_str());
    return [AIHelpSupportSDK showWithApiConfig:configBuilder.build];
}

void AIHelpSupport::login(LoginConfig loginConfig) {
    AIHelpLoginConfigBuilder *builder = [[AIHelpLoginConfigBuilder alloc] init];
    builder.userId = AIHelpParseCString(loginConfig.getUserId().c_str());
    builder.userConfig = getAIHelpUserConfig(loginConfig.getUserConfig());
    builder.isEnterpriseAuth = loginConfig.isEnterpriseAuth();
    [AIHelpSupportSDK login:builder.build];
}

void AIHelpSupport::logout() {
    [AIHelpSupportSDK logout];
}

void AIHelpSupport::updateUserInfo(UserConfig userConfig) {
    [AIHelpSupportSDK updateUserInfo: getAIHelpUserConfig(userConfig)];
}

void AIHelpSupport::resetUserInfo() {
    [AIHelpSupportSDK resetUserInfo];
}

void AIHelpSupport::updateSDKLanguage(const std::string& language) {
    NSString *nslanguage = AIHelpParseCString(language.c_str());
    [AIHelpSupportSDK updateSDKLanguage:nslanguage];
}

void AIHelpSupport::setUploadLogPath(const std::string& path) {
    NSString *nspath = AIHelpParseCString(path.c_str());
    [AIHelpSupportSDK setUploadLogPath:nspath];
}

void AIHelpSupport::setPushTokenAndPlatform(const std::string& pushToken, PushPlatform platform) {
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

std::string AIHelpSupport::getSDKVersion() {
    return [AIHelpSupportSDK getSDKVersion].UTF8String;
}

bool AIHelpSupport::isAIHelpShowing() {
    return [AIHelpSupportSDK isAIHelpShowing];
}

void AIHelpSupport::enableLogging(bool enable) {
    [AIHelpSupportSDK enableLogging:enable];
}

void AIHelpSupport::showUrl(const std::string& url) {
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

namespace {
    // Define a map to store event listeners
    std::unordered_map<AIHelp::EventType, AIHelp::OnAsyncEventListener> g_eventListeners;
    std::unordered_map<AIHelp::EventType, void (*)(const char *)> g_eventCompletions;

    void adapterAcknowledge(AIHelp::EventType eventType, const char *jsonAckData) {
        auto it = g_eventCompletions.find(eventType);
        if (it != g_eventCompletions.end()) {
            // Call the completion function associated with the event type
            it->second(jsonAckData);
        }
    }

    // Adapter function
    void adapterCallback(const char *jsonEventData, void (*acknowledge)(const char *jsonAckData)) {
        std::string eventType = extractValue(jsonEventData, "eventType");
        int eventTypeInt = std::stoi(eventType);
        AIHelp::EventType e = static_cast<AIHelp::EventType>(eventTypeInt);
        auto it = g_eventListeners.find(e);
        if (it != g_eventListeners.end()) {
            // Store the completion callback
            g_eventCompletions[e] = acknowledge;
            // Call the stored listener with acknowledge function
            it->second(jsonEventData, adapterAcknowledge);
        }
    }
}

void AIHelpSupport::registerAsyncEventListener(EventType eventType, OnAsyncEventListener listener) {
    AIHelpEventType aiHelpEventType = static_cast<AIHelpEventType>(static_cast<int>(eventType));
    g_eventListeners[eventType] = listener;
    [AIHelpSupportSDK registerAsyncListener:adapterCallback eventType:aiHelpEventType];
}

void AIHelpSupport::unregisterAsyncEventListener(EventType eventType) {
    AIHelpEventType aiHelpEventType = static_cast<AIHelpEventType>(static_cast<int>(eventType));
    [AIHelpSupportSDK unregisterAsyncListenerWithEvent:aiHelpEventType];
}

void AIHelpSupport::fetchUnreadMessageCount() {
    [AIHelpSupportSDK fetchUnreadMessageCount];
}

void AIHelpSupport::setSDKInterfaceOrientationMask(int interfaceOrientationMask) {
    [AIHelpSupportSDK setSDKInterfaceOrientationMask:interfaceOrientationMask];
}

void AIHelpSupport::setSDKAppearanceMode(int mode) {
    [AIHelpSupportSDK setSDKAppearanceMode:mode];
}

#endif
