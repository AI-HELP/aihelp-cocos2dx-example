#include "DemoScene.h"
#include "AIHelp/AIHelpSupport.h"
#include <iostream>
#include <random>

using namespace AIHelp;

USING_NS_CC;

cocos2d::Scene *GameScene::createScene() {
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init() {
    if (!Layer::init())
        return false;

//	auto BGColor = LayerColor::create(Color4B(211, 211, 211, 255));
//	this->addChild(BGColor);

    auto BGColor = LayerColor::create(Color4B(211, 211, 211, 255), winSize_width, winSize_height);
    BGColor->setPosition(Vec2::ZERO);
    this->addChild(BGColor);

    Color3B titleColor(82, 126, 250);

    auto moduleTitle = Label::createWithSystemFont("Modules", "Consolas", 50);
    moduleTitle->setPosition(Vec2(150, winSize_height - 70));
    moduleTitle->setColor(titleColor);
    addChild(moduleTitle);

    auto configureTitle = Label::createWithSystemFont("Configuration", "Consolas", 50);
    configureTitle->setPosition(Vec2(450, winSize_height - 70));
    configureTitle->setColor(titleColor);
    addChild(configureTitle);

    auto otherTitle = Label::createWithSystemFont("Others", "Consolas", 50);
    otherTitle->setPosition(Vec2(750, winSize_height - 70));
    otherTitle->setColor(titleColor);
    addChild(otherTitle);

    // ================================= Modules =================================

    auto menuItemBot = MenuItemFont::create("Robot",
                                            CC_CALLBACK_1(GameScene::showBotSupport, this));
    menuItemBot->setPosition(Vec2(150, 450));
    menuItemBot->setColor(Color3B(51, 51, 51));

    auto menuItemManual = MenuItemFont::create("Manual",
                                               CC_CALLBACK_1(GameScene::showManualSupport, this));
    menuItemManual->setPosition(Vec2(150, 380));
    menuItemManual->setColor(Color3B(51, 51, 51));

    auto menuItemAllSections = MenuItemFont::create("All Sections",
                                                    CC_CALLBACK_1(GameScene::showAllFAQSections,
                                                                  this));
    menuItemAllSections->setPosition(Vec2(150, 310));
    menuItemAllSections->setColor(Color3B(51, 51, 51));

    auto menuItemSingle = MenuItemFont::create("Single Section",
                                               CC_CALLBACK_1(GameScene::showSingleSection, this));
    menuItemSingle->setPosition(Vec2(150, 240));
    menuItemSingle->setColor(Color3B(51, 51, 51));

    auto menuItemSingleFAQ = MenuItemFont::create("Single FAQ",
                                                  CC_CALLBACK_1(GameScene::showSingleFAQ, this));
    menuItemSingleFAQ->setPosition(Vec2(150, 170));
    menuItemSingleFAQ->setColor(Color3B(51, 51, 51));

    // ================================= Modules =================================

    // ================================= Configuration =================================

    auto menuItemLogin = MenuItemFont::create("OnUserLogin",
                                              CC_CALLBACK_1(GameScene::updateUserInfo, this));
    menuItemLogin->setPosition(Vec2(450, 450));
    menuItemLogin->setColor(Color3B(51, 51, 51));

    auto menuItemLogout = MenuItemFont::create("OnUserLogout",
                                               CC_CALLBACK_1(GameScene::resetUserInfo, this));
    menuItemLogout->setPosition(Vec2(450, 380));
    menuItemLogout->setColor(Color3B(51, 51, 51));

    auto goInternational = MenuItemFont::create("Going International",
                                                CC_CALLBACK_1(GameScene::updateLanguage, this));
    goInternational->setPosition(Vec2(450, 310));
    goInternational->setColor(Color3B(51, 51, 51));

    // ================================= Configuration =================================

    // ================================= Configuration =================================

    auto menuItemUnread = MenuItemFont::create("Unread Messages", CC_CALLBACK_1(
            GameScene::startUnreadMessageCountPolling, this));
    menuItemUnread->setPosition(Vec2(750, 450));
    menuItemUnread->setColor(Color3B(51, 51, 51));

    auto menuItemPush = MenuItemFont::create("Push",
                                             CC_CALLBACK_1(GameScene::setPushTokenAndPlatform,
                                                           this));
    menuItemPush->setPosition(Vec2(750, 380));
    menuItemPush->setColor(Color3B(51, 51, 51));

//    auto menuItemNetCheck = MenuItemFont::create("Network Check",
//                                                 CC_CALLBACK_1(
//                                                         GameScene::setNetworkCheckHostAddress,
//                                                         this));
//    menuItemNetCheck->setPosition(Vec2(750, 310));
//    menuItemNetCheck->setColor(Color3B(51, 51, 51));

    auto menuItemUploadLog = MenuItemFont::create("Upload Log",
                                                  CC_CALLBACK_1(GameScene::setUploadLogPath, this));
    menuItemUploadLog->setPosition(Vec2(750, 240));
    menuItemUploadLog->setColor(Color3B(51, 51, 51));

    auto menuItemLog = MenuItemFont::create("Enable Logging",
                                            CC_CALLBACK_1(GameScene::enableLogging, this));
    menuItemLog->setPosition(Vec2(750, 170));
    menuItemLog->setColor(Color3B(51, 51, 51));

    auto menuItemVersion = MenuItemFont::create("SDK Version",
                                                CC_CALLBACK_1(GameScene::getSDKVersion, this));
    menuItemVersion->setPosition(Vec2(750, 100));
    menuItemVersion->setColor(Color3B(51, 51, 51));

    // ================================= Configuration =================================

    auto menu = Menu::create(menuItemBot, menuItemManual, menuItemAllSections, menuItemSingle,
                             menuItemSingleFAQ, menuItemLogin, menuItemLogout,
                             goInternational,
                             menuItemUnread, menuItemPush, menuItemUploadLog,
                             menuItemLog, menuItemVersion, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}

// ================================= Modules =================================

void GameScene::showBotSupport(cocos2d::Ref *obj) {
    AIHelpSupport::show("test004");
}

void GameScene::showManualSupport(cocos2d::Ref *obj) {
    ApiConfig apiConfig = ApiConfigBuilder()
            .setEntranceId("THIS IS YOUR ENTRANCE ID")
            .setWelcomeMessage("THIS IS YOUR WELCOME MESSAGE").build();
    AIHelpSupport::show(apiConfig);
}

void GameScene::showAllFAQSections(cocos2d::Ref *obj) {
    AIHelpSupport::show("test001");
}

void GameScene::showSingleSection(cocos2d::Ref *obj) {
    AIHelpSupport::show("test002");
}

void GameScene::showSingleFAQ(cocos2d::Ref *obj) {
    AIHelpSupport::show("test003");
}

// ================================= Modules =================================


// ================================= Configuration =================================
std::string generateRandomDigitsString() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<long long> dis(1000000000LL, 9999999999LL); // 范围是 10^9 到 10^10 - 1

    long long randomNumber = dis(gen);
    std::stringstream ss;
    ss << randomNumber;
    return ss.str();
}

void GameScene::updateUserInfo(cocos2d::Ref *obj) {
    UserConfig userConfig = UserConfigBuilder()
            .setServerId("SERVER ID")
            .setUserName("USER NAME")
            .setUserTags("pay1,s1,vip2")
            .setCustomData("{\"level\":34,\"total_recharge\":300,\"remaining\":56}")
            .build();

    LoginConfig config = LoginConfigBuilder()
            .setUserId(generateRandomDigitsString())
            .setUserConfig(userConfig)
//            .setEnterpriseAuth(true)
            .build();

    AIHelpSupport::login(config);
}

void GameScene::resetUserInfo(cocos2d::Ref *obj) {
    AIHelpSupport::resetUserInfo();
}

void GameScene::updateLanguage(cocos2d::Ref *obj) {
    AIHelpSupport::updateSDKLanguage("ja");
}

// ================================= Configuration =================================


// ================================= Others =================================

void GameScene::startUnreadMessageCountPolling(cocos2d::Ref *obj) {
    AIHelpSupport::startUnreadMessageCountPolling();
}

void GameScene::setPushTokenAndPlatform(cocos2d::Ref *obj) {
    AIHelpSupport::setPushTokenAndPlatform("YOUR PUSH TOKEN", FIREBASE);
}

void GameScene::setUploadLogPath(cocos2d::Ref *obj) {
    AIHelpSupport::setUploadLogPath("YOUR LOG PATH");
}

void GameScene::enableLogging(cocos2d::Ref *obj) {
    AIHelpSupport::enableLogging(true);
}

void GameScene::getSDKVersion(cocos2d::Ref *obj) {
    CCLOGERROR("AIHelp version is %s", AIHelpSupport::getSDKVersion().c_str());
}

// ================================= Others =================================

