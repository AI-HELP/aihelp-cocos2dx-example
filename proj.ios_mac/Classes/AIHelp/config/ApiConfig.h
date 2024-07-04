//
// Created by MAC on 2024/6/23.
//

#ifndef PROJ_ANDROID_APICONFIG_H
#define PROJ_ANDROID_APICONFIG_H

#include <string>

namespace AIHelp {

    class ApiConfig {
    private:
        std::string entranceId;
        std::string welcomeMessage;

    public:
        ApiConfig(const std::string& entranceId, const std::string& welcomeMessage);
        std::string getEntranceId() const;
        std::string getWelcomeMessage() const;
    };

    /* AIHelpSupportApiConfigBuilder */
    class ApiConfigBuilder {
    private:
        std::string entranceId;
        std::string welcomeMessage;

    public:
        ApiConfigBuilder& setEntranceId(const std::string& entranceId);
        ApiConfigBuilder& setWelcomeMessage(const std::string& welcomeMessage);
        ApiConfig build() const;
    };

} // AIHelp

#endif //PROJ_ANDROID_APICONFIG_H
