//
//  AIHelpConfig.cpp
//
//  Created by AIHelp on 2020/7/29.
//

#include "AIHelpConfig.h"
USING_NS_CC;

/* ConversationConfig */
ConversationConfig::ConversationConfig(bool alwaysShowHumanSupportButtonInBotPage, string welcomeMessage, string storyNode, ConversationIntent conversationIntent)
    :alwaysShowHumanSupportButtonInBotPage(alwaysShowHumanSupportButtonInBotPage),
    welcomeMessage(welcomeMessage),
    storyNode(storyNode),
    conversationIntent(conversationIntent){
}
bool ConversationConfig::getAlwaysShowHumanSupportButtonInBotPage() {
    return alwaysShowHumanSupportButtonInBotPage;
}
string ConversationConfig::getWelcomeMessage() {
    return welcomeMessage;
}
string ConversationConfig::getStoryNode() {
    return storyNode;
}
ConversationIntent ConversationConfig::getConversationIntent() {
    return conversationIntent;
}

/* ConversationConfigBuilder */
ConversationConfigBuilder::ConversationConfigBuilder(const ConversationConfigBuilder& rBuilder){
    this->alwaysShowHumanSupportButtonInBotPage = rBuilder.alwaysShowHumanSupportButtonInBotPage;
    this->welcomeMessage = rBuilder.welcomeMessage;
    this->storyNode = rBuilder.storyNode;
    this->conversationIntent = rBuilder.conversationIntent;
}
ConversationConfigBuilder ConversationConfigBuilder::setAlwaysShowHumanSupportButtonInBotPage(bool alwaysShowHumanSupportButtonInBotPage) {
    (*this).alwaysShowHumanSupportButtonInBotPage = alwaysShowHumanSupportButtonInBotPage;
    return (*this);
}
ConversationConfigBuilder ConversationConfigBuilder::setWelcomeMessage(string welcomeMessage) {
    (*this).welcomeMessage = welcomeMessage;
    return (*this);
}
ConversationConfigBuilder ConversationConfigBuilder::setStoryNode(string storyNode) {
    (*this).storyNode = storyNode;
    return (*this);
}
ConversationConfigBuilder ConversationConfigBuilder::setConversationIntent(ConversationIntent conversationIntent) {
    (*this).conversationIntent = conversationIntent;
    return (*this);
}
ConversationConfig ConversationConfigBuilder::build() {
    return ConversationConfig(alwaysShowHumanSupportButtonInBotPage, welcomeMessage, storyNode, conversationIntent);
}


/* FAQConfig */
FAQConfig::FAQConfig(ConversationMoment showConversationMoment, const ConversationConfig& conversationConfig) :showConversationMoment(showConversationMoment),
    conversationConfig(conversationConfig){
}
ConversationMoment FAQConfig::getShowConversationMoment() {
    return showConversationMoment;
}
const ConversationConfig& FAQConfig::getConversationConfig() {
    return conversationConfig;
}

/* FAQConfigBuilder */
FAQConfigBuilder::FAQConfigBuilder(const FAQConfigBuilder& rBuilder){
    this->showConversationMoment = rBuilder.showConversationMoment;
    this->conversationConfig = rBuilder.conversationConfig;
}
FAQConfigBuilder FAQConfigBuilder::setShowConversationMoment(ConversationMoment showConversationMoment) {
    (*this).showConversationMoment = showConversationMoment;
    return (*this);
}
FAQConfigBuilder FAQConfigBuilder::setConversationConfig(const ConversationConfig& conversationConfig) {
    (*this).conversationConfig = conversationConfig;
    return (*this);
}
FAQConfig FAQConfigBuilder::build() {
    return FAQConfig(showConversationMoment, conversationConfig);
}


/* OperationConfig */
OperationConfig::OperationConfig(int selectIndex, string conversationBotTitle, const ConversationConfig& conversationConfig) :selectIndex(selectIndex),
    conversationTitle(conversationBotTitle),
    conversationConfig(conversationConfig){
}
int OperationConfig::getSelectIndex() {
    return selectIndex;
}
string OperationConfig::getConversationTitle() {
    return conversationTitle;
}
const ConversationConfig& OperationConfig::getConversationConfig() {
    return conversationConfig;
}

/* OperationConfigBuilder */
OperationConfigBuilder::OperationConfigBuilder(const OperationConfigBuilder& rBuilder){
    this->selectIndex = rBuilder.selectIndex;
    this->conversationTitle = rBuilder.conversationTitle;
    this->conversationConfig = rBuilder.conversationConfig;
}
OperationConfigBuilder OperationConfigBuilder::setSelectIndex(int selectIndex) {
    (*this).selectIndex = selectIndex;
    return (*this);
}
OperationConfigBuilder OperationConfigBuilder::setConversationTitle(string conversationBotTitle) {
    (*this).conversationTitle = conversationBotTitle;
    return (*this);
}
OperationConfigBuilder OperationConfigBuilder::setConversationConfig(const ConversationConfig& conversationConfig) {
    (*this).conversationConfig = conversationConfig;
    return (*this);
}
OperationConfig OperationConfigBuilder::build() {
    return OperationConfig(selectIndex, conversationTitle, conversationConfig);
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
