#ifndef AIHELP_CALLBACKS_H
#define AIHELP_CALLBACKS_H

#include "Enums.h"

namespace AIHelp {

    typedef void (*Acknowledge)(AIHelp::EventType eventType, const char *jsonAckData);

    typedef void (*OnAsyncEventListener)(const char *jsonEventData, Acknowledge ack);

}

#endif // AIHELP_CALLBACKS_H
