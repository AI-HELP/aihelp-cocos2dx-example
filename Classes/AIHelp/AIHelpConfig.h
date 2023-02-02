//
//  AIHelpConfig.h
//
//  Created by AIHelp on 2020/7/28.
//

#ifndef AIHelpConfig_h
#define AIHelpConfig_h

#include "cocos2d.h"
#include <string>
using namespace std;

enum PushPlatform {APNS, FIREBASE, JPUSH, GETUI};
enum PublishCountryOrRegion {CN = 1, IN = 2};

/* AIHelpSupportApiConfig */
class AIHelpSupportApiConfig {
private:
    string entranceId;
    string welcomeMessage;
public:
    AIHelpSupportApiConfig(string entranceId, string welcomeMessage);
    string getEntranceId();
    string getWelcomeMessage();
};

/* AIHelpSupportApiConfigBuilder */
class AIHelpSupportApiConfigBuilder {
private:
    string entranceId;
    string welcomeMessage;
public:
    AIHelpSupportApiConfigBuilder(){};
    ~AIHelpSupportApiConfigBuilder(){};
    AIHelpSupportApiConfigBuilder(const AIHelpSupportApiConfigBuilder& rBuilder);
    AIHelpSupportApiConfigBuilder setEntranceId(string entranceId);
    AIHelpSupportApiConfigBuilder setWelcomeMessage(string welcomeMessage);
    AIHelpSupportApiConfig build();
};

/* AIHelpSupportUserConfig */
class AIHelpSupportUserConfig {
private:
    string userId;
    string userName;
    string serverId;
    string userTags;
    string customData;
    bool isSyncCrmInfo;
public:
    AIHelpSupportUserConfig(string userId, string userName, string serverId, string userTags, string customData, bool isSyncCrmInfo);
    string getUserId();
    string getUserName();
    string getServerId();
    string getUserTags();
    string getCustomData();
    bool getIsSyncCrmInfo();
};

/* AIHelpSupportUserConfigBuilder */
class AIHelpSupportUserConfigBuilder {
private:
    string userId;
    string userName;
    string serverId;
    string userTags;
    string customData;
    bool isSyncCrmInfo;
public:
    AIHelpSupportUserConfigBuilder(){};
    ~AIHelpSupportUserConfigBuilder(){};
    AIHelpSupportUserConfigBuilder(const AIHelpSupportUserConfigBuilder& rBuilder);
    AIHelpSupportUserConfigBuilder setUserId(string userId);
    AIHelpSupportUserConfigBuilder setUserName(string userName);
    AIHelpSupportUserConfigBuilder setServerId(string serverId);
    AIHelpSupportUserConfigBuilder setUserTags(string userTags);
    AIHelpSupportUserConfigBuilder setCustomData(string customData);
    AIHelpSupportUserConfigBuilder setIsSyncCrmInfo(bool isSyncCrmInfo);
    AIHelpSupportUserConfig build();
};

#endif /* AIHelpConfig_h */
