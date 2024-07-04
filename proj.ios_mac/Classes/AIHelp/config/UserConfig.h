#ifndef AIHELP_USER_CONFIG_H
#define AIHELP_USER_CONFIG_H

#include <string>

namespace AIHelp {

    /* UserConfig */
    class UserConfig {
    private:
        std::string userName;
        std::string serverId;
        std::string userTags;
        std::string customData;

    public:
        UserConfig() = default;

        UserConfig(const std::string &userName, const std::string &serverId,
                   const std::string &userTags, const std::string &customData);

        std::string getUserName() const;

        std::string getServerId() const;

        std::string getUserTags() const;

        std::string getCustomData() const;
    };

    /* UserConfigBuilder */
    class UserConfigBuilder {
    private:
        std::string userName;
        std::string serverId;
        std::string userTags;
        std::string customData;

    public:
        UserConfigBuilder() = default;

        UserConfigBuilder(const UserConfigBuilder &rBuilder);

        UserConfigBuilder &setUserName(const std::string &userName);

        UserConfigBuilder &setServerId(const std::string &serverId);

        UserConfigBuilder &setUserTags(const std::string &userTags);

        UserConfigBuilder &setCustomData(const std::string &customData);

        UserConfig build() const;
    };

} // namespace AIHelp

#endif // AIHELP_USER_CONFIG_H
