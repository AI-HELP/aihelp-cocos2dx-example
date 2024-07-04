#include "ApiConfig.h"

namespace AIHelp {

    /* ApiConfig */
    ApiConfig::ApiConfig(const std::string &entranceId, const std::string &welcomeMessage)
            : entranceId(entranceId), welcomeMessage(welcomeMessage) {}

    std::string ApiConfig::getEntranceId() const {
        return entranceId;
    }

    std::string ApiConfig::getWelcomeMessage() const {
        return welcomeMessage;
    }

    /* ApiConfigBuilder */
    ApiConfigBuilder &ApiConfigBuilder::setEntranceId(const std::string &entranceId) {
        this->entranceId = entranceId;
        return *this;
    }

    ApiConfigBuilder &ApiConfigBuilder::setWelcomeMessage(const std::string &welcomeMessage) {
        this->welcomeMessage = welcomeMessage;
        return *this;
    }

    ApiConfig ApiConfigBuilder::build() const {
        return ApiConfig(entranceId, welcomeMessage);
    }

} // AIHelp