#include "LoginConfig.h"

namespace AIHelp {

    // Constructor implementation
    LoginConfig::LoginConfig(const std::string &userId, const UserConfig &userConfig, bool enterpriseAuth)
            : userId(userId), userConfig(userConfig), enterpriseAuth(enterpriseAuth) {}

    // Getter implementations
    std::string LoginConfig::getUserId() const {
        return userId;
    }

    const UserConfig &LoginConfig::getUserConfig() const {
        return userConfig;
    }

    bool LoginConfig::isEnterpriseAuth() const {
        return enterpriseAuth;
    }

    // Builder class method implementations
    LoginConfigBuilder &LoginConfigBuilder::setUserId(const std::string &userId) {
        this->userId = userId;
        return *this;
    }

    LoginConfigBuilder &LoginConfigBuilder::setUserConfig(const UserConfig &userConfig) {
        this->userConfig = userConfig;
        return *this;
    }

    LoginConfigBuilder &LoginConfigBuilder::setEnterpriseAuth(bool enterpriseAuth) {
        this->enterpriseAuth = enterpriseAuth;
        return *this;
    }

    LoginConfig LoginConfigBuilder::build() {
        return LoginConfig(userId, userConfig, enterpriseAuth);
    }

} // namespace AIHelp
