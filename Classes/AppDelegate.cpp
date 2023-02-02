#include "AppDelegate.h"
#include "DemoScene.h"
#include "AIHelp/AIHelpSupport.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

static void AIHelp_onAIHelpInit() {
    CCLOG("AIHelp Cocos2dx Callback init complete");
}

static void AIHelp_onFormSubmitted() {
    CCLOG("AIHelp Cocos2dx Callback onFormSubmitted");
}

static void AIHelp_onOperationUnreadChanged(bool hasUnreadArticles) {
    if (hasUnreadArticles) {
        CCLOG("AIHelp Cocos2dx Callback has unread articles");
    } else {
        CCLOG("AIHelp Cocos2dx Callback no unread articles");
    }

}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
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
//    AIHelpSupport::init(
//            "THIS IS YOUR APP KEY",
//            "THIS IS YOUR APP DOMAIN",
//            "THIS IS YOUR APP ID",
//            "THIS IS YOUR DEFAULT LANGUAGE(OPTIONAL)");

    AIHelpSupport::additionalSupportFor(PublishCountryOrRegion::IN);
    AIHelpSupport::init(
            "adfadf",
            "a.aihelp.net",
            "TryElva_platform_79453658-02b7-42fb-9384-8e8712539777",
            "zh_CN");
    AIHelpSupport::setOnAIHelpInitializedCallback(AIHelp_onAIHelpInit);
    AIHelpSupport::setOnSpecificFormSubmittedCallback(AIHelp_onFormSubmitted);

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
