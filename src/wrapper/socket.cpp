#define LOG_LEVEL LOG_VERBOSE
#include <log.h>

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>

#include <wrapper/socket.h>

#define SET_ERROR(rc) setError(rc, __FUNCTION__, __LINE__)

SocketWrapper::SocketWrapper()
{
    sockfd = -1;
}

bool SocketWrapper::create(int domain, int type, int protocol)
{
    LOGV("construct size : %d", sizeof(SocketWrapper));
    sockfd = socket(domain, type, protocol);
    LOGV("socket(domain:%d, type:%d, protocol:%d) return sockfd:%d", domain, type, protocol, sockfd);
    return SET_ERROR(sockfd);
}

bool SocketWrapper::setError(int ret, const char* function, int line)
{
    if (ret == -1) {
        error.errnum = errno;
        error.strerror = strerror(errno);
        LOGE("[%s:%d]errno : %d, strerror : %s", function, line, error.errnum, error.strerror.c_str());
        return false;
    }
    return true;
}

SocketWrapper::~SocketWrapper()
{
    LOGV("destruct size : %d", sizeof(SocketWrapper));
}

bool SocketWrapper::bind(const struct sockaddr *addr, socklen_t addrlen)
{
    int ret = ::bind(sockfd, addr, addrlen);
    LOGV("bind(sockfd:%d, addr:%p, addrlen:%d) return %d", sockfd, addr, addrlen, ret);
    return SET_ERROR(ret);
}

bool SocketWrapper::listen(int backlog)
{
    int ret = ::listen(sockfd, backlog);
    LOGV("listen(sockfd:%d, backlog:%d) return %d", sockfd, backlog, ret);
    return SET_ERROR(ret);
}

bool SocketWrapper::accept(SocketWrapper* socket, struct sockaddr *addr, socklen_t *addrlen)
{
    int fd = ::accept(sockfd, addr, addrlen);
    LOGV("accept(sockfd:%d, addr:%p, addrlen:%d) return sockfd:%d", sockfd, addr, addrlen, fd);
    socket->sockfd = fd;
    return SET_ERROR(fd);
}

bool SocketWrapper::close()
{
    int ret = ::close(sockfd);
    LOGV("close(sockfd:%d) return %d", sockfd, ret);
    return SET_ERROR(ret);
}

bool SocketWrapper::bind(int listen_port)
{
    struct sockaddr_in my_addr;
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(listen_port);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    return bind((const sockaddr*)&my_addr, sizeof(my_addr));
}

bool SocketWrapper::accept(SocketWrapper* socket)
{
    struct sockaddr_in my_addr;
    memset(&my_addr, 0, sizeof(my_addr));
    socklen_t addrlen = sizeof(my_addr);
    return accept(socket, (struct sockaddr *)&my_addr, &addrlen);
}

