#include "AIHelpSupport.h"
#include "config/Enums.h"
#include <utility>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#define  LOG_TAG    "AIHelpSupport"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


namespace AIHelp {

    const char *supportClazzName = "net/aihelp/init/AIHelpSupport";

    std::unordered_map<EventType, OnAsyncEventListener> eventMap;
    std::unordered_map<EventType, jobject> callbackMap;

    jobject getAndroidContext() {
        const char *sig = "()Lorg/cocos2dx/cpp/AppActivity;";
        cocos2d::JniMethodInfo methodInfo;
        if (cocos2d::JniHelper::getStaticMethodInfo(
                methodInfo, "org/cocos2dx/cpp/AppActivity", "getAppActivity", sig)) {
            return methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
        }
        return nullptr;
    }

    jstring string2jstring(JNIEnv *jniEnv, const std::string &str) {
        return jniEnv->NewStringUTF(str.c_str());
    }

    jobject getJavaApiConfig(JNIEnv *jniEnv, ApiConfig apiConfig) {
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

    jobject getJavaUserConfig(JNIEnv *jniEnv, UserConfig userConfig) {
        jclass clazz = jniEnv->FindClass("net/aihelp/config/UserConfig$Builder");
        jobject builderObj = jniEnv->NewObject(clazz, jniEnv->GetMethodID(clazz, "<init>", "()V"));

        jstring userName = string2jstring(jniEnv, userConfig.getUserName());
        jstring serverId = string2jstring(jniEnv, userConfig.getServerId());
        jstring userTag = string2jstring(jniEnv, userConfig.getUserTags());
        jstring customData = string2jstring(jniEnv, userConfig.getCustomData());

        const char *sig = "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Lnet/aihelp/config/UserConfig;";
        jmethodID buildId = jniEnv->GetMethodID(clazz, "build", sig);
        jobject javaUserConfig = jniEnv->CallObjectMethod(builderObj, buildId, userName, serverId, userTag, customData);

        jniEnv->DeleteLocalRef(userName);
        jniEnv->DeleteLocalRef(serverId);
        jniEnv->DeleteLocalRef(userTag);
        jniEnv->DeleteLocalRef(customData);
        return javaUserConfig;
    }

    jobject getJavaLoginConfig(JNIEnv *jniEnv, LoginConfig loginConfig) {
        jclass clazz = jniEnv->FindClass("net/aihelp/config/LoginConfig$Builder");
        jobject builderObj = jniEnv->NewObject(clazz, jniEnv->GetMethodID(clazz, "<init>", "()V"));

        jstring jUserId = jniEnv->NewStringUTF(loginConfig.getUserId().c_str());
        jobject jUserConfig = getJavaUserConfig(jniEnv, loginConfig.getUserConfig());
        jboolean jEnterpriseAuth = static_cast<jboolean>(loginConfig.isEnterpriseAuth());

        const char *sig = "(Ljava/lang/String;Lnet/aihelp/config/UserConfig;Z)Lnet/aihelp/config/LoginConfig;";
        jmethodID buildId = jniEnv->GetMethodID(clazz, "build", sig);
        jobject javaUserConfig = jniEnv->CallObjectMethod(builderObj, buildId, jUserId, jUserConfig, jEnterpriseAuth);

        jniEnv->DeleteLocalRef(jUserId);
        jniEnv->DeleteLocalRef(jUserConfig);
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

    jobject getJavaPublishCountryOrRegion(JNIEnv *jniEnv, PublishCountryOrRegion countryOrRegion) {
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

    jobject getJavaEventType(JNIEnv *jniEnv, EventType eventType) {
        jclass clazz = jniEnv->FindClass("net/aihelp/event/EventType");
        jmethodID fromValueId = jniEnv->GetStaticMethodID(clazz, "fromValue", "(I)Lnet/aihelp/event/EventType;");
        return jniEnv->CallStaticObjectMethod(clazz, fromValueId, static_cast<int>(eventType));
    }

    void
    AIHelpSupport::initialize(const std::string &domainName, const std::string &appId, const std::string &language) {
        const char *sig = "(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V";
        const char *methodName = "initialize";
        cocos2d::JniMethodInfo methodInfo;
        if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, supportClazzName, methodName, sig)) {
            jobject jContext = getAndroidContext();
            jstring jDomain = methodInfo.env->NewStringUTF(domainName.c_str());
            jstring jAppId = methodInfo.env->NewStringUTF(appId.c_str());
            jstring jLanguage = methodInfo.env->NewStringUTF(language.c_str());
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jContext, jDomain, jAppId,
                                                 jLanguage);
            methodInfo.env->DeleteLocalRef(jContext);
            methodInfo.env->DeleteLocalRef(jDomain);
            methodInfo.env->DeleteLocalRef(jAppId);
            methodInfo.env->DeleteLocalRef(jLanguage);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
    }

    bool AIHelpSupport::show(const std::string &entranceId) {
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

    bool AIHelpSupport::show(ApiConfig apiConfig) {
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

    void AIHelpSupport::login(LoginConfig loginConfig) {
        const char *sig = "(Lnet/aihelp/config/LoginConfig;)V";
        cocos2d::JniMethodInfo info;
        if (cocos2d::JniHelper::getStaticMethodInfo(info, supportClazzName, "login", sig)) {
            jobject config = getJavaLoginConfig(info.env, std::move(loginConfig));
            info.env->CallStaticVoidMethod(info.classID, info.methodID, config);
            info.env->DeleteLocalRef(config);
            info.env->DeleteLocalRef(info.classID);
        }
    }

    void AIHelpSupport::logout() {
        const char *sig = "()V";
        cocos2d::JniMethodInfo info;
        if (cocos2d::JniHelper::getStaticMethodInfo(info, supportClazzName, "logout", sig)) {
            info.env->CallStaticVoidMethod(info.classID, info.methodID);
            info.env->DeleteLocalRef(info.classID);
        }
    }

    void AIHelpSupport::updateUserInfo(UserConfig userConfig) {
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

    void AIHelpSupport::updateSDKLanguage(const std::string &language) {
        const char *sig = "(Ljava/lang/String;)V";
        cocos2d::JniMethodInfo info;
        if (cocos2d::JniHelper::getStaticMethodInfo(info, supportClazzName, "updateSDKLanguage", sig)) {
            jstring jLanguage = info.env->NewStringUTF(language.c_str());
            info.env->CallStaticVoidMethod(info.classID, info.methodID, jLanguage);
            info.env->DeleteLocalRef(info.classID);
            info.env->DeleteLocalRef(jLanguage);
        }
    }

    void AIHelpSupport::setUploadLogPath(const std::string &path) {
        const char *sig = "(Ljava/lang/String;)V";
        cocos2d::JniMethodInfo info;
        if (cocos2d::JniHelper::getStaticMethodInfo(info, supportClazzName, "setUploadLogPath", sig)) {
            jstring jPath = info.env->NewStringUTF(path.c_str());
            info.env->CallStaticVoidMethod(info.classID, info.methodID, jPath);
            info.env->DeleteLocalRef(info.classID);
            info.env->DeleteLocalRef(jPath);
        }
    }

    void AIHelpSupport::setPushTokenAndPlatform(const std::string &pushToken, PushPlatform p) {
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

    void AIHelpSupport::additionalSupportFor(PublishCountryOrRegion countryOrRegion) {
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

    std::string AIHelpSupport::getSDKVersion() {
        const char *sig = "()Ljava/lang/String;";
        cocos2d::JniMethodInfo info;
        std::string ret;
        if (cocos2d::JniHelper::getStaticMethodInfo(info, supportClazzName, "getSDKVersion", sig)) {
            auto jret = (jstring) info.env->CallStaticObjectMethod(info.classID, info.methodID);
            ret = cocos2d::JniHelper::jstring2string(jret);
            info.env->DeleteLocalRef(info.classID);
            info.env->DeleteLocalRef(jret);
        }
        return ret;
    }

    void AIHelpSupport::showUrl(const std::string &url) {
        const char *sig = "(Ljava/lang/String;)V";
        cocos2d::JniMethodInfo info;
        if (cocos2d::JniHelper::getStaticMethodInfo(info, supportClazzName, "showUrl", sig)) {
            jstring jUrl = info.env->NewStringUTF(url.c_str());
            info.env->CallStaticVoidMethod(info.classID, info.methodID, jUrl);
            info.env->DeleteLocalRef(info.classID);
            info.env->DeleteLocalRef(jUrl);
        }
    }

    void AIHelpSupport::fetchUnreadMessageCount() {
        const char *sig = "()V";
        const char *methodName = "fetchUnreadMessageCount";
        cocos2d::JniMethodInfo info;
        if (cocos2d::JniHelper::getStaticMethodInfo(info, supportClazzName, methodName, sig)) {
            info.env->CallStaticVoidMethod(info.classID, info.methodID);
            info.env->DeleteLocalRef(info.classID);
        }
    }

    void AIHelpSupport::fetchUnreadTaskCount() {
        const char *sig = "()V";
        const char *methodName = "fetchUnreadTaskCount";
        cocos2d::JniMethodInfo info;
        if (cocos2d::JniHelper::getStaticMethodInfo(info, supportClazzName, methodName, sig)) {
            info.env->CallStaticVoidMethod(info.classID, info.methodID);
            info.env->DeleteLocalRef(info.classID);
        }
    }

    void AIHelpSupport::registerAsyncEventListener(EventType eventType, OnAsyncEventListener listener) {
        eventMap[eventType] = listener;
        const char *clazzName = "net/aihelp/init/CallbackHelper";
        const char *sig = "(Lnet/aihelp/event/EventType;)V";
        cocos2d::JniMethodInfo info;
        if (cocos2d::JniHelper::getStaticMethodInfo(info, clazzName, "registerAsyncEventListener", sig)) {
            jobject jEventType = getJavaEventType(info.env, eventType);
            info.env->CallStaticVoidMethod(info.classID, info.methodID, jEventType);
            info.env->DeleteLocalRef(info.classID);
            info.env->DeleteLocalRef(jEventType);
        }
    }

    void AIHelpSupport::unregisterAsyncEventListener(EventType eventType) {
        const char *sig = "(Lnet/aihelp/event/EventType;)V";
        const char *methodName = "unregisterAsyncEventListener";
        cocos2d::JniMethodInfo info;
        if (cocos2d::JniHelper::getStaticMethodInfo(info, supportClazzName, methodName, sig)) {
            jobject jEventType = getJavaEventType(info.env, eventType);
            info.env->CallStaticVoidMethod(info.classID, info.methodID, jEventType);
            info.env->DeleteLocalRef(info.classID);
            info.env->DeleteLocalRef(jEventType);
        }
    }

    extern "C" {

    static JavaVM *javaVM = nullptr;

    void acknowledge(EventType eventType, const char *jsonAckData) {
        JNIEnv *env;
        bool shouldDetach = false;

        // Attach the current thread to the JVM
        jint res = javaVM->GetEnv((void **) &env, JNI_VERSION_1_6);
        if (res == JNI_EDETACHED) {
            res = javaVM->AttachCurrentThread((JNIEnv **) &env, NULL);
            if (res != JNI_OK) {
                // Handle error
                return;
            }
            shouldDetach = true;
        } else if (res != JNI_OK) {
            // Handle error
            return;
        }

        // Retrieve the global callback reference from callbackMap
        jobject callback = nullptr;
        auto it = callbackMap.find(eventType);
        if (it != callbackMap.end()) {
            callback = it->second;
        } else {
            // Callback not found for eventType
            if (shouldDetach) {
                javaVM->DetachCurrentThread();
            }
            return;
        }

        // Find the Java method ID of the method to be called
        jclass callbackClass = env->GetObjectClass(callback);
        if (callbackClass == nullptr) {
            if (shouldDetach) {
                javaVM->DetachCurrentThread();
            }
            return;
        }

        jmethodID acknowledgeMethod = env->GetMethodID(callbackClass, "acknowledge", "(Ljava/lang/String;)V");
        if (acknowledgeMethod == nullptr) {
            env->DeleteLocalRef(callbackClass);
            if (shouldDetach) {
                javaVM->DetachCurrentThread();
            }
            return;
        }

        // Convert the C++ string to a Java string
        jstring jJsonAckData = env->NewStringUTF(jsonAckData);
        if (jJsonAckData == nullptr) {
            env->DeleteLocalRef(callbackClass);
            if (shouldDetach) {
                javaVM->DetachCurrentThread();
            }
            return;
        }

        // Call the Java method with the JSON acknowledgment data
        env->CallVoidMethod(callback, acknowledgeMethod, jJsonAckData);

        // Check for exceptions and handle them
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe(); // Print the exception to the console
            env->ExceptionClear();    // Clear the exception
        }

        // Clean up local references
        env->DeleteLocalRef(jJsonAckData);
        env->DeleteLocalRef(callbackClass);

        // Detach the thread from the JVM if it was attached in this function
        if (shouldDetach) {
            javaVM->DetachCurrentThread();
        }
    }

    JNIEXPORT void JNICALL Java_net_aihelp_init_CallbackHelper_onAsyncEventReceived
            (JNIEnv *env, jclass clazz, jint eventType, jstring jsonEventData, jobject callback) {

        env->GetJavaVM(&javaVM);
        EventType event = static_cast<EventType>(eventType);

        // Manage callbackMap
        auto it = callbackMap.find(event);
        if (it != callbackMap.end()) {
            // Delete existing global reference if it exists
            env->DeleteGlobalRef(it->second);
        }
        // Store new global reference to callback
        callbackMap[event] = env->NewGlobalRef(callback);

        // Manage eventMap
        auto it2 = eventMap.find(event);
        if (it2 != eventMap.end()) {
            // Call the listener function with the provided arguments
            it2->second(env->GetStringUTFChars(jsonEventData, NULL), acknowledge);
        }
    }

    }
}

#endif
