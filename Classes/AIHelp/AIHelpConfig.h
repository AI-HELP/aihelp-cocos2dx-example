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

enum ConversationIntent {BOT_SUPPORT, HUMAN_SUPPORT};
enum ConversationMoment {NEVER, ALWAYS, ONLY_IN_ANSWER_PAGE, AFTER_MARKING_UNHELPFUL};
enum PushPlatform {APNS, FIREBASE, JPUSH, GETUI};
enum PublishCountryOrRegion {CN = 1, IN = 2};
/* ConversationConfig */
class ConversationConfig {
private:
    bool alwaysShowHumanSupportButtonInBotPage;
    string welcomeMessage;
    string storyNode;
    ConversationIntent conversationIntent;
public:
    ConversationConfig(){};
    ConversationConfig(bool alwaysShowHumanSupportButtonInBotPage, string welcomeMessage, string storyNode, ConversationIntent conversationIntent);
    bool getAlwaysShowHumanSupportButtonInBotPage();
    string getWelcomeMessage();
    string getStoryNode();
    ConversationIntent getConversationIntent();
};

/* ConversationConfigBuilder */
class ConversationConfigBuilder {
private:
    bool alwaysShowHumanSupportButtonInBotPage;
    string welcomeMessage;
    string storyNode;
    ConversationIntent conversationIntent;
public:
    ConversationConfigBuilder(){};
    ~ConversationConfigBuilder(){};
    ConversationConfigBuilder(const ConversationConfigBuilder& rBuilder);
    ConversationConfigBuilder setAlwaysShowHumanSupportButtonInBotPage(bool alwaysShowHumanSupportButtonInBotPage);
    ConversationConfigBuilder setWelcomeMessage(string welcomeMessage);
    ConversationConfigBuilder setStoryNode(string storyNode);
    ConversationConfigBuilder setConversationIntent(ConversationIntent conversationIntent);
    ConversationConfig build();
};


/* FAQConfig */
class FAQConfig {
private:
    ConversationMoment showConversationMoment;
    const ConversationConfig& conversationConfig;
public:
    FAQConfig(ConversationMoment showConversationMoment,const ConversationConfig& conversationConfig);
    ConversationMoment getShowConversationMoment();
    const ConversationConfig& getConversationConfig();
};

/* FAQConfigBuilder */
class FAQConfigBuilder {
private:
    ConversationMoment showConversationMoment;
    ConversationConfig conversationConfig;
public:
    FAQConfigBuilder(){};
    ~FAQConfigBuilder(){};
    FAQConfigBuilder(const FAQConfigBuilder& rBuilder);
    FAQConfigBuilder setShowConversationMoment(ConversationMoment showConversationMoment);
    FAQConfigBuilder setConversationConfig(const ConversationConfig& conversationConfig);
    FAQConfig build();
};


/* OperationConfig */
class OperationConfig {
private:
    int selectIndex;
    string conversationTitle;
    const ConversationConfig& conversationConfig;
public:
    OperationConfig(int selectIndex, string conversationTitle, const ConversationConfig& conversationConfig);
    int getSelectIndex();
    string getConversationTitle();
    const ConversationConfig& getConversationConfig();
};

/* OperationConfigBuilder */
class OperationConfigBuilder {
private:
    int selectIndex;
    string conversationTitle;
    ConversationConfig conversationConfig;
public:
    OperationConfigBuilder(){};
    ~OperationConfigBuilder(){};
    OperationConfigBuilder(const OperationConfigBuilder& rBuilder);
    OperationConfigBuilder setSelectIndex(int selectIndex);
    OperationConfigBuilder setConversationTitle(string conversationTitle);
    OperationConfigBuilder setConversationConfig(const ConversationConfig& conversationConfig);
    OperationConfig build();
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
