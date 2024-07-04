#ifndef LOGIN_CONFIG_H
#define LOGIN_CONFIG_H

#include <string>
#include "UserConfig.h"
#include "Callbacks.h"

namespace AIHelp {

    /* LoginConfig */
    class LoginConfig {
    private:
        std::string userId;
        UserConfig userConfig;
        bool enterpriseAuth;

    public:
        LoginConfig(const std::string &userId, const UserConfig &userConfig, bool enterpriseAuth);

        std::string getUserId() const;

        const UserConfig &getUserConfig() const;

        bool isEnterpriseAuth() const;
    };

    // Builder class
    class LoginConfigBuilder {
    private:
        std::string userId;
        UserConfig userConfig;
        bool enterpriseAuth;

    public:
        LoginConfigBuilder &setUserId(const std::string &userId);

        LoginConfigBuilder &setUserConfig(const UserConfig &userConfig);

        LoginConfigBuilder &setEnterpriseAuth(bool enterpriseAuth);

        LoginConfig build();

        LoginConfigBuilder() = default;
    };

} // namespace AIHelp

#endif // LOGIN_CONFIG_H
