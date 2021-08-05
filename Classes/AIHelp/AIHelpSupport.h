//
//  AIHelpSupport.h
//  Cocos2dx SDK
//

#ifndef AIHelpSupport_h
#define AIHelpSupport_h

#include "cocos2d.h"
#include <string>
#include "AIHelpConfig.h"

using namespace std;

typedef void (*OnAIHelpInitializedCallback)(void);
typedef void (*OnNetworkCheckResultCallback)(const char* net_log);
typedef void (*OnMessageCountArrivedCallback)(const int unreadCount);
typedef void (*OnSpecificFormSubmittedCallback)(void);
typedef void (*OnAIHelpSessionOpenCallback)(void);
typedef void (*OnAIHelpSessionCloseCallback)(void);
typedef void (*OnAIHelpOperationUnreadCallback)(const bool hasUnread);

class AIHelpSupport
{
public:
    static void init(string apiKey, string domainName, string appId);
    static void init(string apiKey, string domainName, string appId, string language);
    
    static void showConversation();
    static void showConversation(ConversationConfig conversationConfig);
    
    static void showAllFAQSections();
    static void showAllFAQSections(FAQConfig faqConfig);
    
    static void showFAQSection(string sectionId);
    static void showFAQSection(string sectionId, FAQConfig faqConfig);
    static void showSingleFAQ(string faqId);
    static void showSingleFAQ(string faqId, FAQConfig faqConfig);
    
    static void showOperation();
    static void showOperation(OperationConfig operationConfig);
    
    static void updateUserInfo(AIHelpSupportUserConfig userConfig);
    static void resetUserInfo();
    
    static void updateSDKLanguage(string language);
    static void setUploadLogPath(string path);
    static void setPushTokenAndPlatform(string pushToken, PushPlatform platform);
    static string getSDKVersion();
    static bool isAIHelpShowing();
    static void enableLogging(bool enable);
    static void showUrl(string url);
    static void additionalSupportFor(PublishCountryOrRegion countryOrRegion);

    static void setNetworkCheckHostAddress(string address, OnNetworkCheckResultCallback callback);
    static void setOnAIHelpInitializedCallback(OnAIHelpInitializedCallback callback);
    static void startUnreadMessageCountPolling(OnMessageCountArrivedCallback callback);
    static void setOnSpecificFormSubmittedCallback(OnSpecificFormSubmittedCallback callback);
    static void setOnAIHelpSessionOpenCallback(OnAIHelpSessionOpenCallback callback);
    static void setOnAIHelpSessionCloseCallback(OnAIHelpSessionCloseCallback callback);
    static void setOnAIHelpOperationUnreadChangedCallback(OnAIHelpOperationUnreadCallback callback);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    static void setSDKInterfaceOrientationMask(int interfaceOrientationMask);   // iOS only
    static void setSDKAppearanceMode(int mode); // iOS only  0: follow the system 1: light mode 2: dark mode
    static void setSDKEdgeInsets(float top,float bottom,bool enable); // iOS only
    static void setSDKEdgeColor(float red,float green,float blue,float alpha); // iOS only
#endif
};

#endif
