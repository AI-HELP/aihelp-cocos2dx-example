#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"

#define winSize_width 900
#define winSize_height 600

class GameScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

	// modules
	void showBotSupport(cocos2d::Ref *obj);
	void showManualSupport(cocos2d::Ref *obj);
	void showAllFAQSections(cocos2d::Ref *obj);
	void showSingleSection(cocos2d::Ref *obj);
	void showSingleFAQ(cocos2d::Ref *obj);
	void showOperation(cocos2d::Ref *obj);

	// configuration
	void updateUserInfo(Ref *obj);
	void resetUserInfo(Ref *obj);
	void updateLanguage(Ref *obj);

	// others
	void startUnreadMessageCountPolling(Ref *obj);
	void setPushTokenAndPlatform(Ref *obj);
	void setNetworkCheckHostAddress(Ref *obj);
	void setUploadLogPath(Ref *obj);
	void enableLogging(Ref *obj);
	void getSDKVersion(Ref *obj);

};

#endif
