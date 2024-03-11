#include "AIHelpConfig.h"
#include "AIHelpSupport.h"
#include <utility>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#define  LOG_TAG    "AIHelpSupport"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

const char *supportClazzName = "net/aihelp/init/AIHelpSupport";

OnAIHelpInitializedCallback initCallBack = nullptr;
OnNetworkCheckResultCallback networkCheckCallBack = nullptr;
OnMessageCountArrivedCallback unreadMsgCallback = nullptr;
OnSpecificFormSubmittedCallback formSubmittedCallback = nullptr;
OnAIHelpSessionOpenCallback sessionOpenCallback = nullptr;
OnAIHelpSessionCloseCallback sessionCloseCallback = nullptr;
OnAIHelpSpecificUrlClickedCallback specificUrlClickedCallback = nullptr;

jobject getAndroidContext() {
    const char *sig = "()Lorg/cocos2dx/cpp/AppActivity;";
    cocos2d::JniMethodInfo methodInfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(
            methodInfo,"org/cocos2dx/cpp/AppActivity", "getAppActivity", sig)) {
        return methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
    }
    return nullptr;
}

jstring string2jstring(JNIEnv *jniEnv, const string& str) {
    return jniEnv->NewStringUTF(str.c_str());
}

jobject getJavaApiConfig(JNIEnv *jniEnv, AIHelpSupportApiConfig apiConfig) {
    jclass clazz = jniEnv->FindClass("net/aihelp/config/ApiConfig$Builder");
    jobject builderObj = jniEnv->NewObject(clazz, jniEnv->GetMethodID(clazz, "<init>", "()V"));

    jstring entranceId = string2jstring(jniEnv, apiConfig.getEntranceId());
    jstring welcomeMessage = string2jstring(jniEnv, apiConfig.getWelcomeMessage());

    const char *sig = "(Ljava/lang/String;Ljava/lang/String;)Lnet/aihelp/config/ApiConfig;";
    jmethodID buildId = jniEnv->GetMethodID(clazz, "build", sig);
    jobject javaUserConfig = jniEnv->CallObjectMethod(builderObj, buildId, entranceId, welcomeMessage);

    jniEnv->DeleteLocalRef(entranceId);
    jniEnv->DeleteLocalRef(welcomeMessage);
    return javaUserConfig;
}

jobject getJavaUserConfig(JNIEnv *jniEnv, AIHelpSupportUserConfig userConfig) {
    jclass clazz = jniEnv->FindClass("net/aihelp/config/UserConfig$Builder");
    jobject builderObj = jniEnv->NewObject(clazz, jniEnv->GetMethodID(clazz, "<init>", "()V"));

    jstring userId = string2jstring(jniEnv, userConfig.getUserId());
    jstring userName = string2jstring(jniEnv, userConfig.getUserName());
    jstring serverId = string2jstring(jniEnv, userConfig.getServerId());
    jstring userTag = string2jstring(jniEnv, userConfig.getUserTags());
    jstring customData = string2jstring(jniEnv, userConfig.getCustomData());
    bool isSync = userConfig.getIsSyncCrmInfo();

    const char *sig = "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)Lnet/aihelp/config/UserConfig;";
    jmethodID buildId = jniEnv->GetMethodID(clazz, "build", sig);
    jobject javaUserConfig = jniEnv->CallObjectMethod(builderObj, buildId, userId,
                                                      userName, serverId, userTag, customData,
                                                      isSync);

    jniEnv->DeleteLocalRef(userId);
    jniEnv->DeleteLocalRef(userName);
    jniEnv->DeleteLocalRef(serverId);
    jniEnv->DeleteLocalRef(userTag);
    jniEnv->DeleteLocalRef(customData);
    return javaUserConfig;
}

jobject getJavaPushPlatform(JNIEnv *jniEnv, PushPlatform platform) {
    int pf = 0;
    if (platform == APNS) {
        pf = 1;
    } else if (platform == FIREBASE) {
        pf = 2;
    } else if (platform == JPUSH) {
        pf = 3;
    } else if (platform == GETUI) {
        pf = 4;
    }
    jclass clazz = jniEnv->FindClass("net/aihelp/config/enums/PushPlatform");
    jmethodID fromValueId = jniEnv->GetStaticMethodID(clazz, "fromValue",
                                                      "(I)Lnet/aihelp/config/enums/PushPlatform;");
    return jniEnv->CallStaticObjectMethod(clazz, fromValueId, pf);
}

jobject getJavaPublishCountryOrRegion(JNIEnv *jniEnv, PublishCountryOrRegion countryOrRegion){
    int jCountryOrRegion = -1;
    if (countryOrRegion == CN) {
        jCountryOrRegion = 1;
    } else if (countryOrRegion == IN) {
        jCountryOrRegion = 2;
    }
    jclass clazz = jniEnv->FindClass("net/aihelp/config/enums/PublishCountryOrRegion");
    jmethodID fromValueId = jniEnv->GetStaticMethodID(clazz, "fromValue",
                                                      "(I)Lnet/aihelp/config/enums/PublishCountryOrRegion;");
    return jniEnv->CallStaticObjectMethod(clazz, fromValueId, jCountryOrRegion);
}

void AIHelpSupport::init(const string& appKey, const string& domainName, const string& appId) {
    const char *methodName = "init";
    const char *sig = "(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V";
    cocos2d::JniMethodInfo methodInfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, supportClazzName, methodName, sig)) {
        jobject jContext = getAndroidContext();
        jstring jAppKey = methodInfo.env->NewStringUTF(appKey.c_str());
        jstring jDomain = methodInfo.env->NewStringUTF(domainName.c_str());
        jstring jAppId = methodInfo.env->NewStringUTF(appId.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jContext, jAppKey,jDomain, jAppId);
        methodInfo.env->DeleteLocalRef(jContext);
        methodInfo.env->DeleteLocalRef(jAppKey);
        methodInfo.env->DeleteLocalRef(jDomain);
        methodInfo.env->DeleteLocalRef(jAppId);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

void AIHelpSupport::init(const string& appKey, const string& domainName, const string& appId, const string& language) {
    const char *sig = "(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V";
    const char *methodName = "init";
    cocos2d::JniMethodInfo methodInfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, supportClazzName, methodName, sig)) {
        jobject jContext = getAndroidContext();
        jstring jAppKey = methodInfo.env->NewStringUTF(appKey.c_str());
        jstring jDomain = methodInfo.env->NewStringUTF(domainName.c_str());
        jstring jAppId = methodInfo.env->NewStringUTF(appId.c_str());
        jstring jLanguage = methodInfo.env->NewStringUTF(language.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,
                                             jContext, jAppKey,jDomain, jAppId, jLanguage);
        methodInfo.env->DeleteLocalRef(jContext);
        methodInfo.env->DeleteLocalRef(jAppKey);
        methodInfo.env->DeleteLocalRef(jDomain);
        methodInfo.env->DeleteLocalRef(jAppId);
        methodInfo.env->DeleteLocalRef(jLanguage);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

bool AIHelpSupport::show(string entranceId) {
    const char *sig = "(Ljava/lang/String;)Z";
    cocos2d::JniMethodInfo methodInfo;
    jboolean jret = JNI_FALSE;
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, supportClazzName, "show", sig)) {
        jstring jEntranceId = methodInfo.env->NewStringUTF(entranceId.c_str());
        jret = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, jEntranceId);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    return (jret == JNI_TRUE);
}

bool AIHelpSupport::show(AIHelpSupportApiConfig apiConfig) {
    const char *sig = "(Lnet/aihelp/config/ApiConfig;)Z";
    cocos2d::JniMethodInfo info;
    jboolean jret = JNI_FALSE;
    if (cocos2d::JniHelper::getStaticMethodInfo(info, supportClazzName, "show", sig)) {
        jobject config = getJavaApiConfig(info.env, std::move(apiConfig));
        jret = info.env->CallStaticBooleanMethod(info.classID, info.methodID, config);
        info.env->DeleteLocalRef(config);
        info.env->DeleteLocalRef(info.classID);
    }
    return (jret == JNI_TRUE);
}

void AIHelpSupport::updateUserInfo(AIHelpSupportUserConfig userConfig) {
    const char *sig = "(Lnet/aihelp/config/UserConfig;)V";
    cocos2d::JniMethodInfo info;
    if (cocos2d::JniHelper::getStaticMethodInfo(info, supportClazzName, "updateUserInfo", sig)) {
        jobject config = getJavaUserConfig(info.env, std::move(userConfig));
        info.env->CallStaticVoidMethod(info.classID, info.methodID, config);
        info.env->DeleteLocalRef(config);
        info.env->DeleteLocalRef(info.classID);
    }
}

void AIHelpSupport::resetUserInfo() {
    cocos2d::JniMethodInfo info;
    if (cocos2d::JniHelper::getStaticMethodInfo(info, supportClazzName, "resetUserInfo", "()V")) {
        info.env->CallStaticVoidMethod(info.classID, info.methodID);
        info.env->DeleteLocalRef(info.classID);
    }
}

void AIHelpSupport::updateSDKLanguage(const string& language) {
    const char *sig = "(Ljava/lang/String;)V";
    cocos2d::JniMethodInfo info;
    if (cocos2d::JniHelper::getStaticMethodInfo(info, supportClazzName, "updateSDKLanguage", sig)) {
        jstring jLanguage = info.env->NewStringUTF(language.c_str());
        info.env->CallStaticVoidMethod(info.classID, info.methodID, jLanguage);
        info.env->DeleteLocalRef(info.classID);
        info.env->DeleteLocalRef(jLanguage);
    }
}

void AIHelpSupport::setUploadLogPath(const string& path) {
    const char *sig = "(Ljava/lang/String;)V";
    cocos2d::JniMethodInfo info;
    if (cocos2d::JniHelper::getStaticMethodInfo(info, supportClazzName, "setUploadLogPath", sig)) {
        jstring jPath = info.env->NewStringUTF(path.c_str());
        info.env->CallStaticVoidMethod(info.classID, info.methodID, jPath);
        info.env->DeleteLocalRef(info.classID);
        info.env->DeleteLocalRef(jPath);
    }
}

void AIHelpSupport::setPushTokenAndPlatform(const string& pushToken, PushPlatform p) {
    const char *sig = "(Ljava/lang/String;Lnet/aihelp/config/enums/PushPlatform;)V";
    const char *methodName = "setPushTokenAndPlatform";
    cocos2d::JniMethodInfo methodInfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, supportClazzName, methodName, sig)) {
        jstring jPushToken = methodInfo.env->NewStringUTF(pushToken.c_str());
        jobject jPushPlatform = getJavaPushPlatform(methodInfo.env, p);
        methodInfo.env->CallStaticVoidMethod(
                methodInfo.classID, methodInfo.methodID, jPushToken, jPushPlatform);
        methodInfo.env->DeleteLocalRef(jPushToken);
        methodInfo.env->DeleteLocalRef(jPushPlatform);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

bool AIHelpSupport::isAIHelpShowing() {
    const char *sig = "()Z";
    cocos2d::JniMethodInfo info;
    jboolean jret = JNI_FALSE;
    if (cocos2d::JniHelper::getStaticMethodInfo(info, supportClazzName, "setUploadLogPath", sig)) {
        jret = info.env->CallStaticBooleanMethod(info.classID, info.methodID);
        info.env->DeleteLocalRef(info.classID);
    }
    return (jret == JNI_TRUE);
}

void AIHelpSupport::enableLogging(bool enable) {
    const char *sig = "(Z)V";
    cocos2d::JniMethodInfo info;
    if (cocos2d::JniHelper::getStaticMethodInfo(info, supportClazzName, "enableLogging", sig)) {
        info.env->CallStaticVoidMethod(info.classID, info.methodID, enable);
        info.env->DeleteLocalRef(info.classID);
    }
}

void AIHelpSupport::additionalSupportFor(PublishCountryOrRegion countryOrRegion){
    const char *sig = "(Lnet/aihelp/config/enums/PublishCountryOrRegion;)V";
    const char *methodName = "additionalSupportFor";
    cocos2d::JniMethodInfo methodInfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, supportClazzName, methodName, sig)) {
        jobject jCountryOrRegion = getJavaPublishCountryOrRegion(methodInfo.env, countryOrRegion);
        methodInfo.env->CallStaticVoidMethod(
                methodInfo.classID, methodInfo.methodID, jCountryOrRegion);
        methodInfo.env->DeleteLocalRef(jCountryOrRegion);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

string AIHelpSupport::getSDKVersion() {
    const char *sig = "()Ljava/lang/String;";
    cocos2d::JniMethodInfo info;
    std::string ret;
    if (cocos2d::JniHelper::getStaticMethodInfo(info, supportClazzName, "getSDKVersion", sig)) {
        auto jret = (jstring)info.env->CallStaticObjectMethod(info.classID, info.methodID);
        ret = cocos2d::JniHelper::jstring2string(jret);
        info.env->DeleteLocalRef(info.classID);
        info.env->DeleteLocalRef(jret);
    }
    return ret;
}

void AIHelpSupport::showUrl(const string& url) {
    const char *sig = "(Ljava/lang/String;)V";
    cocos2d::JniMethodInfo info;
    if (cocos2d::JniHelper::getStaticMethodInfo(info, supportClazzName, "showUrl", sig)) {
        jstring jUrl = info.env->NewStringUTF(url.c_str());
        info.env->CallStaticVoidMethod(info.classID, info.methodID, jUrl);
        info.env->DeleteLocalRef(info.classID);
        info.env->DeleteLocalRef(jUrl);
    }
}

void AIHelpSupport::setOnAIHelpInitializedCallback(OnAIHelpInitializedCallback callback) {
    initCallBack = callback;
    const char *clazzName = "net/aihelp/init/CallbackHelper";
    const char *sig = "(I[Ljava/lang/Object;)V";
    cocos2d::JniMethodInfo info;
    if (cocos2d::JniHelper::getStaticMethodInfo(info, clazzName, "registerCocos2dxCallback", sig)) {
        jclass clazz = info.env->FindClass("java/lang/Object");
        jobjectArray array = info.env->NewObjectArray(5, clazz, 0);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, 1001, array);
        info.env->DeleteLocalRef(array);
        info.env->DeleteLocalRef(info.classID);
    }
}

void AIHelpSupport::setNetworkCheckHostAddress(const string& address, OnNetworkCheckResultCallback cb) {
    networkCheckCallBack = cb;
    const char *clazzName = "net/aihelp/init/CallbackHelper";
    const char *sig = "(I[Ljava/lang/Object;)V";
    cocos2d::JniMethodInfo info;
    if (cocos2d::JniHelper::getStaticMethodInfo(info, clazzName, "registerCocos2dxCallback", sig)) {
        jstring jstr = string2jstring(info.env, address);
        jclass clazz = info.env->FindClass("java/lang/Object");
        jobjectArray array = info.env->NewObjectArray(5, clazz, 0);
        info.env->SetObjectArrayElement(array, 0, jstr);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, 1002, array);
        info.env->DeleteLocalRef(jstr);
        info.env->DeleteLocalRef(array);
        info.env->DeleteLocalRef(info.classID);
    }
}


void AIHelpSupport::startUnreadMessageCountPolling(OnMessageCountArrivedCallback callback) {
    unreadMsgCallback = callback;
    const char *clazzName = "net/aihelp/init/CallbackHelper";
    const char *sig = "(I[Ljava/lang/Object;)V";
    cocos2d::JniMethodInfo info;
    if (cocos2d::JniHelper::getStaticMethodInfo(info, clazzName, "registerCocos2dxCallback", sig)) {
        jclass clazz = info.env->FindClass("java/lang/Object");
        jobjectArray array = info.env->NewObjectArray(5, clazz, 0);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, 1003, array);
        info.env->DeleteLocalRef(array);
        info.env->DeleteLocalRef(info.classID);
    }
}

void AIHelpSupport::setOnSpecificFormSubmittedCallback(OnSpecificFormSubmittedCallback callback) {
    formSubmittedCallback = callback;
    const char *clazzName = "net/aihelp/init/CallbackHelper";
    const char *sig = "(I[Ljava/lang/Object;)V";
    cocos2d::JniMethodInfo info;
    if (cocos2d::JniHelper::getStaticMethodInfo(info, clazzName, "registerCocos2dxCallback", sig)) {
        jclass clazz = info.env->FindClass("java/lang/Object");
        jobjectArray array = info.env->NewObjectArray(5, clazz, 0);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, 1004, array);
        info.env->DeleteLocalRef(array);
        info.env->DeleteLocalRef(info.classID);
    }
}

void AIHelpSupport::setOnAIHelpSessionOpenCallback(OnAIHelpSessionOpenCallback callback) {
    formSubmittedCallback = callback;
    const char *clazzName = "net/aihelp/init/CallbackHelper";
    const char *sig = "(I[Ljava/lang/Object;)V";
    cocos2d::JniMethodInfo info;
    if (cocos2d::JniHelper::getStaticMethodInfo(info, clazzName, "registerCocos2dxCallback", sig)) {
        jclass clazz = info.env->FindClass("java/lang/Object");
        jobjectArray array = info.env->NewObjectArray(5, clazz, 0);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, 1005, array);
        info.env->DeleteLocalRef(array);
        info.env->DeleteLocalRef(info.classID);
    }
}

void AIHelpSupport::setOnAIHelpSessionCloseCallback(OnAIHelpSessionCloseCallback callback) {
    formSubmittedCallback = callback;
    const char *clazzName = "net/aihelp/init/CallbackHelper";
    const char *sig = "(I[Ljava/lang/Object;)V";
    cocos2d::JniMethodInfo info;
    if (cocos2d::JniHelper::getStaticMethodInfo(info, clazzName, "registerCocos2dxCallback", sig)) {
        jclass clazz = info.env->FindClass("java/lang/Object");
        jobjectArray array = info.env->NewObjectArray(5, clazz, 0);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, 1006, array);
        info.env->DeleteLocalRef(array);
        info.env->DeleteLocalRef(info.classID);
    }
}

void AIHelpSupport::setOnAIHelpSpecificUrlClickedCallback(OnAIHelpSpecificUrlClickedCallback callback) {
    specificUrlClickedCallback = callback;
    const char *clazzName = "net/aihelp/init/CallbackHelper";
    const char *sig = "(I[Ljava/lang/Object;)V";
    cocos2d::JniMethodInfo info;
    if (cocos2d::JniHelper::getStaticMethodInfo(info, clazzName, "registerCocos2dxCallback", sig)) {
        jclass clazz = info.env->FindClass("java/lang/Object");
        jobjectArray array = info.env->NewObjectArray(5, clazz, 0);
        info.env->CallStaticVoidMethod(info.classID, info.methodID, 1008, array);
        info.env->DeleteLocalRef(array);
        info.env->DeleteLocalRef(info.classID);
    }
}

extern "C" {
JNIEXPORT void JNICALL Java_net_aihelp_init_CallbackHelper_handleCocos2dxCallback
        (JNIEnv *jniEnv, jclass clazz, jint type, jobjectArray objArray) {
    if (type == 1001 && initCallBack) {
        initCallBack();
    } else if (type == 1004 && formSubmittedCallback) {
        formSubmittedCallback();
    } else if (type == 1005 && sessionOpenCallback) {
        sessionOpenCallback();
    } else if (type == 1006 && sessionCloseCallback) {
        sessionCloseCallback();
    } else {
        jobject element = jniEnv->GetObjectArrayElement(objArray, 0);
        if (type == 1002 && networkCheckCallBack) {
            jstring netLog = nullptr;
            const char *result = nullptr;
            if (jniEnv->IsInstanceOf(element, jniEnv->FindClass("java/lang/String"))) {
                netLog = static_cast<jstring>(element);
                result = jniEnv->GetStringUTFChars(netLog, 0);
            }
            networkCheckCallBack(result);
            if (netLog != nullptr) {
                jniEnv->ReleaseStringUTFChars(netLog, result);
            }
        }
        if (type == 1003 && unreadMsgCallback) {
            jclass cls = jniEnv->GetObjectClass(element);
            int result = 0;
            if (jniEnv->IsInstanceOf(element, jniEnv->FindClass("java/lang/Integer"))) {
                jmethodID intValueMethodID = jniEnv->GetMethodID(cls, "intValue", "()I");
                result = jniEnv->CallIntMethod(element, intValueMethodID);
            }
            unreadMsgCallback(result);
        }
        if (type == 1008 && specificUrlClickedCallback) {
            jstring url = nullptr;
            const char *result = nullptr;
            if (jniEnv->IsInstanceOf(element, jniEnv->FindClass("java/lang/String"))) {
                url = static_cast<jstring>(element);
                result = jniEnv->GetStringUTFChars(url, 0);
            }
            specificUrlClickedCallback(result);
            if (url != nullptr) {
                jniEnv->ReleaseStringUTFChars(url, result);
            }
        }
    }

}

}

#endif
