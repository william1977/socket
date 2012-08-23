#define LOG_LEVEL LOG_VERBOSE
#include <log.h>

#include <errno.h>
#include <string.h>

#include <wrapper/socket.h>

SocketWrapper::SocketWrapper(int domain, int type, int protocol)
{
    LOGV("construct size : %d", sizeof(SocketWrapper));
    sockfd = socket(domain, type, protocol);
    LOGV("socket(domain:%d, type:%d, protocol:%d) return sockfd:%d", domain, type, protocol, sockfd);
    if (sockfd == -1) {
        error.errnum = errno;
        error.strerror = strerror(errno);
        LOGE("errno : %d, strerror : %s", error.errnum, error.strerror.c_str());
    }
}

SocketWrapper::~SocketWrapper()
{
    LOGV("destruct size : %d", sizeof(SocketWrapper));
}

