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
    ConversationConfigBuilder builder(*this);
    builder.alwaysShowHumanSupportButtonInBotPage = alwaysShowHumanSupportButtonInBotPage;
    return builder;
}
ConversationConfigBuilder ConversationConfigBuilder::setWelcomeMessage(string welcomeMessage) {
    ConversationConfigBuilder builder(*this);
    builder.welcomeMessage = welcomeMessage;
    return builder;
}
ConversationConfigBuilder ConversationConfigBuilder::setStoryNode(string storyNode) {
    ConversationConfigBuilder builder(*this);
    builder.storyNode = storyNode;
    return builder;
}
ConversationConfigBuilder ConversationConfigBuilder::setConversationIntent(ConversationIntent conversationIntent) {
    ConversationConfigBuilder builder(*this);
    builder.conversationIntent = conversationIntent;
    return builder;
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
    FAQConfigBuilder builder(*this);
    builder.showConversationMoment = showConversationMoment;
    return builder;
}
FAQConfigBuilder FAQConfigBuilder::setConversationConfig(const ConversationConfig& conversationConfig) {
    FAQConfigBuilder builder(*this);
    builder.conversationConfig = conversationConfig;
    return builder;
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
    OperationConfigBuilder builder(*this);
    builder.selectIndex = selectIndex;
    return builder;
}
OperationConfigBuilder OperationConfigBuilder::setConversationTitle(string conversationBotTitle) {
    OperationConfigBuilder builder(*this);
    builder.conversationTitle = conversationBotTitle;
    return builder;
}
OperationConfigBuilder OperationConfigBuilder::setConversationConfig(const ConversationConfig& conversationConfig) {
    OperationConfigBuilder builder(*this);
    builder.conversationConfig = conversationConfig;
    return builder;
}
OperationConfig OperationConfigBuilder::build() {
    return OperationConfig(selectIndex, conversationTitle, conversationConfig);
}


/* AIHelpUserConfig */
AIHelpUserConfig::AIHelpUserConfig(string userId, string userName, string serverId, string userTags, string customData, bool isSyncCrmInfo)
    :userId(userId),
    userName(userName),
    serverId(serverId),
    userTags(userTags),
    customData(customData),
    isSyncCrmInfo(isSyncCrmInfo){
}
string AIHelpUserConfig::getUserId() {
    return userId;
}
string AIHelpUserConfig::getUserName() {
    return userName;
}
string AIHelpUserConfig::getServerId() {
    return serverId;
}
string AIHelpUserConfig::getUserTags() {
    return userTags;
}
string AIHelpUserConfig::getCustomData() {
    return customData;
}
bool AIHelpUserConfig::getIsSyncCrmInfo() {
    return isSyncCrmInfo;
}

/* AIHelpUserConfigBuilder */
AIHelpUserConfigBuilder::AIHelpUserConfigBuilder(const AIHelpUserConfigBuilder& rBuilder){
    this->userId = rBuilder.userId;
    this->userName = rBuilder.userName;
    this->serverId = rBuilder.serverId;
    this->userTags = rBuilder.userTags;
    this->customData = rBuilder.customData;
    this->isSyncCrmInfo = rBuilder.isSyncCrmInfo;
}
AIHelpUserConfigBuilder AIHelpUserConfigBuilder::setUserId(string userId) {
    AIHelpUserConfigBuilder builder(*this);
    builder.userId = userId;
    return builder;
}
AIHelpUserConfigBuilder AIHelpUserConfigBuilder::setUserName(string userName) {
    AIHelpUserConfigBuilder builder(*this);
    builder.userName = userName;
    return builder;
}
AIHelpUserConfigBuilder AIHelpUserConfigBuilder::setServerId(string serverId) {
    AIHelpUserConfigBuilder builder(*this);
    builder.serverId = serverId;
    return builder;
}
AIHelpUserConfigBuilder AIHelpUserConfigBuilder::setUserTags(string userTags) {
    AIHelpUserConfigBuilder builder(*this);
    builder.userTags = userTags;
    return builder;
}
AIHelpUserConfigBuilder AIHelpUserConfigBuilder::setCustomData(string customData) {
    AIHelpUserConfigBuilder builder(*this);
    builder.customData = customData;
    return builder;
}
AIHelpUserConfigBuilder AIHelpUserConfigBuilder::setIsSyncCrmInfo(bool isSyncCrmInfo) {
    AIHelpUserConfigBuilder builder(*this);
    builder.isSyncCrmInfo = isSyncCrmInfo;
    return builder;
}
AIHelpUserConfig AIHelpUserConfigBuilder::build() {
    return AIHelpUserConfig(userId, userName, serverId, userTags, customData, isSyncCrmInfo);
}
