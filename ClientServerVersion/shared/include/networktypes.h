#ifndef NETWORKTYPES_H
#define NETWORKTYPES_H

#include <QtGlobal>

namespace net
{
enum class PackageType : qint32 {
    INVALID = 10,
    PASSWORD_REQUEST,
    PASSWORD_RESPONSE,
    ADD_USER_REQUEST,
    ADD_USER_RESPONSE,
    TOP_TIME_REQUEST,
    TOP_TIME_RESPONSE,
    TOP_TURNS_REQUEST,
    TOP_TURNS_RESPONSE,
    ADD_RECORD_REQUEST,
    ADD_RECORD_RESPONSE,
    INTERNAL_SERVER_ERROR
};

enum class ConnectionState {
    Connected,
    Disconnected,
    Connecting
};

enum class InternalServerError {
    PASSWORD_ERROR,
    USER_ADDITION_ERROR,
    RECORD_ADDITION_ERROR,
    TOP_TIME_ERROR,
    TOP_TURNS_ERROR
};
}

#endif // NETWORKTYPES_H
