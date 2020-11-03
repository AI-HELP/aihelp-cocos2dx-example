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


/* UserConfig */
UserConfig::UserConfig(string userId, string userName, string serverId, string userTags, string customData, bool isSyncCrmInfo)
    :userId(userId),
    userName(userName),
    serverId(serverId),
    userTags(userTags),
    customData(customData),
    isSyncCrmInfo(isSyncCrmInfo){
}
string UserConfig::getUserId() {
    return userId;
}
string UserConfig::getUserName() {
    return userName;
}
string UserConfig::getServerId() {
    return serverId;
}
string UserConfig::getUserTags() {
    return userTags;
}
string UserConfig::getCustomData() {
    return customData;
}
bool UserConfig::getIsSyncCrmInfo() {
    return isSyncCrmInfo;
}

/* UserConfigBuilder */
UserConfigBuilder::UserConfigBuilder(const UserConfigBuilder& rBuilder){
    this->userId = rBuilder.userId;
    this->userName = rBuilder.userName;
    this->serverId = rBuilder.serverId;
    this->userTags = rBuilder.userTags;
    this->customData = rBuilder.customData;
    this->isSyncCrmInfo = rBuilder.isSyncCrmInfo;
}
UserConfigBuilder UserConfigBuilder::setUserId(string userId) {
    UserConfigBuilder builder(*this);
    builder.userId = userId;
    return builder;
}
UserConfigBuilder UserConfigBuilder::setUserName(string userName) {
    UserConfigBuilder builder(*this);
    builder.userName = userName;
    return builder;
}
UserConfigBuilder UserConfigBuilder::setServerId(string serverId) {
    UserConfigBuilder builder(*this);
    builder.serverId = serverId;
    return builder;
}
UserConfigBuilder UserConfigBuilder::setUserTags(string userTags) {
    UserConfigBuilder builder(*this);
    builder.userTags = userTags;
    return builder;
}
UserConfigBuilder UserConfigBuilder::setCustomData(string customData) {
    UserConfigBuilder builder(*this);
    builder.customData = customData;
    return builder;
}
UserConfigBuilder UserConfigBuilder::setIsSyncCrmInfo(bool isSyncCrmInfo) {
    UserConfigBuilder builder(*this);
    builder.isSyncCrmInfo = isSyncCrmInfo;
    return builder;
}
UserConfig UserConfigBuilder::build() {
    return UserConfig(userId, userName, serverId, userTags, customData, isSyncCrmInfo);
}
