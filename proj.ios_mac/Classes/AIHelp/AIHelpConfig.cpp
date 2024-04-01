//
//  AIHelpConfig.cpp
//
//  Created by AIHelp on 2020/7/29.
//

#include "AIHelpConfig.h"
USING_NS_CC;

/* AIHelpSupportApiConfig */
AIHelpSupportApiConfig::AIHelpSupportApiConfig(string entranceId, string welcomeMessage)
        :entranceId(entranceId),
         welcomeMessage(welcomeMessage){
}
string AIHelpSupportApiConfig::getEntranceId() {
    return entranceId;
}
string AIHelpSupportApiConfig::getWelcomeMessage() {
    return welcomeMessage;
}

/* AIHelpSupportApiConfigBuilder */
AIHelpSupportApiConfigBuilder::AIHelpSupportApiConfigBuilder(const AIHelpSupportApiConfigBuilder& rBuilder){
    this->entranceId = rBuilder.entranceId;
    this->welcomeMessage = rBuilder.welcomeMessage;
}
AIHelpSupportApiConfigBuilder AIHelpSupportApiConfigBuilder::setEntranceId(string entranceId) {
    (*this).entranceId = entranceId;
    return (*this);
}
AIHelpSupportApiConfigBuilder AIHelpSupportApiConfigBuilder::setWelcomeMessage(string welcomeMessage) {
    (*this).welcomeMessage = welcomeMessage;
    return (*this);
}
AIHelpSupportApiConfig AIHelpSupportApiConfigBuilder::build() {
    return AIHelpSupportApiConfig(entranceId, welcomeMessage);
}


/* AIHelpSupportUserConfig */
AIHelpSupportUserConfig::AIHelpSupportUserConfig(string userId, string userName, string serverId, string userTags, string customData, bool isSyncCrmInfo)
    :userId(userId),
    userName(userName),
    serverId(serverId),
    userTags(userTags),
    customData(customData),
    isSyncCrmInfo(isSyncCrmInfo){
}
string AIHelpSupportUserConfig::getUserId() {
    return userId;
}
string AIHelpSupportUserConfig::getUserName() {
    return userName;
}
string AIHelpSupportUserConfig::getServerId() {
    return serverId;
}
string AIHelpSupportUserConfig::getUserTags() {
    return userTags;
}
string AIHelpSupportUserConfig::getCustomData() {
    return customData;
}
bool AIHelpSupportUserConfig::getIsSyncCrmInfo() {
    return isSyncCrmInfo;
}

/* AIHelpSupportUserConfigBuilder */
AIHelpSupportUserConfigBuilder::AIHelpSupportUserConfigBuilder(const AIHelpSupportUserConfigBuilder& rBuilder){
    this->userId = rBuilder.userId;
    this->userName = rBuilder.userName;
    this->serverId = rBuilder.serverId;
    this->userTags = rBuilder.userTags;
    this->customData = rBuilder.customData;
    this->isSyncCrmInfo = rBuilder.isSyncCrmInfo;
}
AIHelpSupportUserConfigBuilder AIHelpSupportUserConfigBuilder::setUserId(string userId) {
    (*this).userId = userId;
    return (*this);
}
AIHelpSupportUserConfigBuilder AIHelpSupportUserConfigBuilder::setUserName(string userName) {
    (*this).userName = userName;
    return (*this);
}
AIHelpSupportUserConfigBuilder AIHelpSupportUserConfigBuilder::setServerId(string serverId) {
    (*this).serverId = serverId;
    return (*this);
}
AIHelpSupportUserConfigBuilder AIHelpSupportUserConfigBuilder::setUserTags(string userTags) {
    (*this).userTags = userTags;
    return (*this);
}
AIHelpSupportUserConfigBuilder AIHelpSupportUserConfigBuilder::setCustomData(string customData) {
    (*this).customData = customData;
    return (*this);
}
AIHelpSupportUserConfigBuilder AIHelpSupportUserConfigBuilder::setIsSyncCrmInfo(bool isSyncCrmInfo) {
    (*this).isSyncCrmInfo = isSyncCrmInfo;
    return (*this);
}
AIHelpSupportUserConfig AIHelpSupportUserConfigBuilder::build() {
    return AIHelpSupportUserConfig(userId, userName, serverId, userTags, customData, isSyncCrmInfo);
}
