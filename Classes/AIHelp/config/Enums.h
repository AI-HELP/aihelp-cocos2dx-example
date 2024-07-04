#ifndef AIHELP_ENUMS_H
#define AIHELP_ENUMS_H

namespace AIHelp {

    enum PushPlatform {
        APNS, FIREBASE, JPUSH, GETUI
    };
    enum PublishCountryOrRegion {
        CN = 1, IN = 2
    };
    enum EventType {

        /**
         * Event for SDK initialization
         */
        INITIALIZATION,

        /**
         * Event for user login
         */
        USER_LOGIN,

        /**
         * Event for enterprise authentication
         */
        ENTERPRISE_AUTH,

        /**
         * Event for opening or closing a session (window)
         */
        SESSION_OPEN,
        SESSION_CLOSE,

        /**
         * Event for message arrival
         */
        MESSAGE_ARRIVAL,

        /**
         * Event for log upload
         */
        LOG_UPLOAD,

        /**
         * Event for URL click
         */
        URL_CLICK,

    };

} // namespace AIHelp

#endif // AIHELP_ENUMS_H
