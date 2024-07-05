#ifndef AIHelpSupport_h
#define AIHelpSupport_h

#include "cocos2d.h"
#include <string>
#include "config/Enums.h"
#include "config/Callbacks.h"
#include "config/ApiConfig.h"
#include "config/UserConfig.h"
#include "config/LoginConfig.h"

namespace AIHelp {
    class AIHelpSupport {
    public:
        static void
        initialize(const std::string &domainName, const std::string &appId, const std::string &language = "");

        static bool show(const std::string &entranceId);

        static bool show(ApiConfig apiConfig);

        static void login(LoginConfig apiConfig);

        static void logout();

        static void updateUserInfo(UserConfig userConfig);

        static void resetUserInfo();

        static void updateSDKLanguage(const std::string &language);

        static void setUploadLogPath(const std::string &path);

        static void setPushTokenAndPlatform(const std::string &pushToken, PushPlatform platform);

        static std::string getSDKVersion();

        static bool isAIHelpShowing();

        static void enableLogging(bool enable);

        static void showUrl(const std::string &url);

        static void additionalSupportFor(PublishCountryOrRegion countryOrRegion);

        static void fetchUnreadMessageCount();

        static void registerAsyncEventListener(EventType eventType, OnAsyncEventListener listener);

        static void unregisterAsyncEventListener(EventType eventType);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        static void setSDKInterfaceOrientationMask(int interfaceOrientationMask);   // iOS only
        static void setSDKAppearanceMode(int mode); // iOS only  0: follow the system 1: light mode 2: dark mode
#endif
    };
} // AIHelp

namespace std {
    template<>
    struct hash<AIHelp::EventType> {
        std::size_t operator()(const AIHelp::EventType &e) const {
            return std::hash<int>()(static_cast<int>(e));
        }
    };
}

#endif
