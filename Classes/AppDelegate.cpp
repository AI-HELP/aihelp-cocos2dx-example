#include "AppDelegate.h"
#include "DemoScene.h"
#include "AIHelp/AIHelpSupport.h"

using namespace AIHelp;

USING_NS_CC;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs() {
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
        glview = GLViewImpl::createWithRect("AIHelp Demo", Rect(0, 0, 900, 600));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(900, 600, ResolutionPolicy::SHOW_ALL);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res");

    // create a scene. it's an autorelease object
    auto scene = GameScene::createScene();

    // run
    director->runWithScene(scene);

    // init AIHelp
    AIHelpSupport::enableLogging(true);

//    AIHelpSupport::additionalSupportFor(PublishCountryOrRegion::IN);
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    AIHelpSupport::initialize(
            "release.aihelp.net",
            "TryElva_platform_79453658-02b7-42fb-9384-8e8712539777",
            "zh_CN");
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    AIHelpSupport::initialize(
            "release.aihelp.net",
            "TryElva_platform_09ebf7fa-8d45-4843-bd59-cfda3d8a8dc0",
            "zh_CN");
#endif

    AIHelpSupport::registerAsyncEventListener(
            EventType::INITIALIZATION,
            [](const char *jsonData, Acknowledge ack) {
                CCLOG("AIHelp Cocos2dx init: %s", jsonData);
            });

    AIHelpSupport::registerAsyncEventListener(
            EventType::USER_LOGIN,
            [](const char *jsonData, Acknowledge ack) {
                CCLOG("AIHelp Cocos2dx login: %s", jsonData);
            });

    AIHelpSupport::registerAsyncEventListener(
            EventType::ENTERPRISE_AUTH,
            [](const char *jsonData, Acknowledge ack) {
                CCLOG("AIHelp Cocos2dx auth: %s", jsonData);
                ack(EventType::ENTERPRISE_AUTH, "{\"token\":\"this is your async token\"}");
            });

    AIHelpSupport::registerAsyncEventListener(
            EventType::MESSAGE_ARRIVAL,
            [](const char *jsonData, Acknowledge ack) {
                CCLOG("AIHelp Cocos2dx message arrived: %s", jsonData);
            });

    AIHelpSupport::registerAsyncEventListener(
            EventType::LOG_UPLOAD,
            [](const char *jsonData, Acknowledge ack) {
                CCLOG("AIHelp Cocos2dx upload log: %s", jsonData);
                ack(EventType::LOG_UPLOAD, "{\"content\":\"this is your log\"}");
            });

    AIHelpSupport::registerAsyncEventListener(
            EventType::SESSION_OPEN,
            [](const char *jsonData, Acknowledge ack) {
                CCLOG("AIHelp Cocos2dx open: %s", jsonData);
            });

    AIHelpSupport::registerAsyncEventListener(
            EventType::SESSION_CLOSE,
            [](const char *jsonData, Acknowledge ack) {
                CCLOG("AIHelp Cocos2dx close: %s", jsonData);
                AIHelpSupport::unregisterAsyncEventListener(EventType::SESSION_OPEN);
                AIHelpSupport::unregisterAsyncEventListener(EventType::SESSION_CLOSE);
                AIHelpSupport::unregisterAsyncEventListener(EventType::MESSAGE_ARRIVAL);
            });

    AIHelpSupport::registerAsyncEventListener(
            EventType::URL_CLICK,
            [](const char *jsonData, Acknowledge ack) {
                CCLOG("AIHelp Cocos2dx Url: %s", jsonData);
            });

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}
