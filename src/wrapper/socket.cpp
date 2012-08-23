#define LOG_LEVEL LOG_VERBOSE
#include <log.h>
#include <wrapper/socket.h>

SocketWrapper::SocketWrapper()
{
    LOGV("construct size : %d", sizeof(SocketWrapper));
}

SocketWrapper::~SocketWrapper()
{
    LOGV("destruct size : %d", sizeof(SocketWrapper));
}

