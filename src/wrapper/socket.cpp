#define LOG_LEVEL LOG_VERBOSE
#include <log.h>

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include <wrapper/socket.h>

#define SET_ERROR(rc) setError(rc, __FUNCTION__, __LINE__)

SocketWrapper::SocketWrapper()
{
    sockfd = -1;
    async = false;
    listener = NULL;
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
    LOGV("accept(sockfd:%d, addr:%p, addrlen:%d) return sockfd:%d", sockfd, addr, *addrlen, fd);
    socket->sockfd = fd;
    return SET_ERROR(fd);
}

bool SocketWrapper::recv(void *buf, size_t len, ssize_t* read_len, int flags)
{
    ssize_t ret = ::recv(sockfd, buf, len, flags);
    LOGV("recv(sockfd:%d, buf:%p, len:%d, flags:%d) return %d", sockfd, buf, len, flags, ret);
    *read_len = ret;
    if(ret == 0){
        LOGW("[%d]The return value will be 0 when the peer  has  performed  an  orderly shutdown.", sockfd);
        close();
    }
    return SET_ERROR(ret);
}

bool SocketWrapper::send(const void *buf, size_t len, ssize_t* write_len, int flags)
{
    ssize_t ret = ::send(sockfd, buf, len, flags);
    LOGV("send(sockfd:%d, buf:%p, len:%d, flags:%d) return %d", sockfd, buf, len, flags, ret);
    *write_len = ret;
    return SET_ERROR(ret);
}

bool SocketWrapper::fcntl(int cmd, int arg, int* out_arg)
{
    int ret = ::fcntl(sockfd, cmd, arg);
    LOGV("fcntl(sockfd:%d, cmd:%d, arg:%d) return %d", sockfd, cmd, arg, ret);
    if (out_arg != NULL) {
        *out_arg = ret;
    }
    return SET_ERROR(ret);
}

bool SocketWrapper::setNonBlock()
{
    int flags;
    if (!fcntl (F_GETFL, 0, &flags)) {
        return false;
    }
    
    flags |= O_NONBLOCK;
    async = fcntl (F_SETFL, flags);
    return async;
}

bool SocketWrapper::connect(const struct sockaddr *addr, socklen_t addrlen)
{
    int ret = ::connect(sockfd, addr, addrlen);
    LOGV("connect(sockfd:%d, addr:%p, addrlen:%d) return %d", sockfd, addr, addrlen, ret);
    return SET_ERROR(ret);
}

bool SocketWrapper::close()
{
    if(sockfd == -1){
        return true;
    }
    int ret = ::close(sockfd);
    LOGV("close(sockfd:%d) return %d", sockfd, ret);
    if(ret == 0){
        sockfd = -1;
    }
    return SET_ERROR(ret);
}
/*
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
*/
bool IPSocket::bind(int listen_port, const char* address)
{
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(listen_port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (address != NULL) {
        addr.sin_addr.s_addr = inet_addr(address);
    }
    return SocketWrapper::bind((const sockaddr*)&addr, sizeof(addr));
}

bool IPSocket::accept(IPSocket* socket)
{
    memset(&socket->peer_addr, 0, sizeof(socket->peer_addr));
    socklen_t addrlen = sizeof(socket->peer_addr);
    return SocketWrapper::accept(socket, (struct sockaddr *)&socket->peer_addr, &addrlen);
}

bool IPSocket::connect(const char* address, int port)
{
    memset(&peer_addr, 0, sizeof(peer_addr));
    peer_addr.sin_family = AF_INET;
    peer_addr.sin_port = htons(port);
    peer_addr.sin_addr.s_addr = inet_addr(address);
    return SocketWrapper::connect((const sockaddr*)&peer_addr, sizeof(addr));
}

