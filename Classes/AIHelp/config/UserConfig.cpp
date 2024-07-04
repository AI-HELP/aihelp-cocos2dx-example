#include "UserConfig.h"

namespace AIHelp {

    /* UserConfig */
    UserConfig::UserConfig(const std::string &userName, const std::string &serverId,
                           const std::string &userTags, const std::string &customData)
            : userName(userName), serverId(serverId), userTags(userTags), customData(customData) {}

    std::string UserConfig::getUserName() const {
        return userName;
    }

    std::string UserConfig::getServerId() const {
        return serverId;
    }

    std::string UserConfig::getUserTags() const {
        return userTags;
    }

    std::string UserConfig::getCustomData() const {
        return customData;
    }

    /* UserConfigBuilder */
    UserConfigBuilder::UserConfigBuilder(const UserConfigBuilder &rBuilder)
            : userName(rBuilder.userName), serverId(rBuilder.serverId), userTags(rBuilder.userTags),
              customData(rBuilder.customData) {}

    UserConfigBuilder &UserConfigBuilder::setUserName(const std::string &userName) {
        this->userName = userName;
        return *this;
    }

    UserConfigBuilder &UserConfigBuilder::setServerId(const std::string &serverId) {
        this->serverId = serverId;
        return *this;
    }

    UserConfigBuilder &UserConfigBuilder::setUserTags(const std::string &userTags) {
        this->userTags = userTags;
        return *this;
    }

    UserConfigBuilder &UserConfigBuilder::setCustomData(const std::string &customData) {
        this->customData = customData;
        return *this;
    }

    UserConfig UserConfigBuilder::build() const {
        return UserConfig(userName, serverId, userTags, customData);
    }

} // namespace AIHelp
