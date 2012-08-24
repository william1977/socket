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
#include <wrapper/select.h>

#define SET_ERROR(rc) setError(rc, __FUNCTION__, __LINE__)

SelectWrapper::SelectWrapper()
{
//    nfds = 0;

    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_ZERO(&exceptfds);
}

bool SelectWrapper::setError(int ret, const char* function, int line)
{
    if (ret == -1) {
        error.errnum = errno;
        error.strerror = strerror(errno);
        LOGE("[%s:%d]errno : %d, strerror : %s", function, line, error.errnum, error.strerror.c_str());
        return false;
    }
    return true;
}

SelectWrapper::~SelectWrapper()
{
    LOGV("destruct size : %d", sizeof(SocketWrapper));
}

bool SelectWrapper::select(struct timeval *timeout)
{
    int nfds = 0;
    fd_set* p_readfds = NULL;
    fd_set* p_writefds = NULL;
    fd_set* p_exceptfds = NULL;

    if (reads.size() > 0) {
        p_readfds = &readfds;
        nfds = getMaxfd(reads, nfds);
    }
    if (writes.size() > 0) {
        p_writefds = &writefds;
        nfds = getMaxfd(writes, nfds);
    }
    if (excepts.size() > 0) {
        p_exceptfds = &exceptfds;
        nfds = getMaxfd(excepts, nfds);
    }

    int ret = ::select(nfds, p_readfds, p_writefds, p_exceptfds, timeout);
    LOGV("select(nfds:%d, readfds:%p, writefds:%p, exceptfds:%p, timeout:%p) return %d", nfds, p_readfds, p_writefds, p_exceptfds, timeout, ret);
    return SET_ERROR(ret);
}

bool SelectWrapper::addToRead(SocketWrapper*socket)
{
    FD_SET(socket->sockfd, &readfds);
    return add(reads, socket);
}

bool SelectWrapper::removeFromRead(SocketWrapper*socket)
{
    FD_CLR(socket->sockfd, &readfds);
    return remove(reads, socket);
}

bool SelectWrapper::isReadable(SocketWrapper*socket)
{
    return FD_ISSET(socket->sockfd, &readfds);
}
      
bool SelectWrapper::addToWrite(SocketWrapper*socket)
{
    FD_SET(socket->sockfd, &writefds);
    return add(writes, socket);
}

bool SelectWrapper::removeFromWrite(SocketWrapper*socket)
{
    FD_CLR(socket->sockfd, &writefds);
    return remove(writes, socket);
}

bool SelectWrapper::isWritable(SocketWrapper*socket)
{
    return FD_ISSET(socket->sockfd, &writefds);
}

      
bool SelectWrapper::addToExpect(SocketWrapper*socket)
{
    FD_SET(socket->sockfd, &exceptfds);
    return add(excepts, socket);
}

bool SelectWrapper::removeFromExpect(SocketWrapper*socket)
{
    FD_CLR(socket->sockfd, &exceptfds);
    return remove(excepts, socket);
}

bool SelectWrapper::isExpect(SocketWrapper*socket)
{
    return FD_ISSET(socket->sockfd, &exceptfds);
}

bool SelectWrapper::add(std::vector<SocketWrapper*>& collection, SocketWrapper*socket)
{
    int size = collection.size();
    for (int i = 0; i < size; i++) {
        if(collection[i] == socket){
            return true;
        }
    }
    collection.push_back(socket);
    return true;
}

bool SelectWrapper::remove(std::vector<SocketWrapper*>& collection, SocketWrapper*socket)
{
    int size = collection.size();
    for (int i = 0; i < size; i++) {
        if(collection[i] == socket){
            collection.erase(collection.begin() + i);
            return true;
        }
    }
    return true;
}

int SelectWrapper::getMaxfd(std::vector<SocketWrapper*>& collection, int nfds)
{
    int maxfd = nfds;
    int size = collection.size();
    for (int i = 0; i < size; i++) {
        if(collection[i]->sockfd + 1 > maxfd){
            maxfd = collection[i]->sockfd + 1;
        }
    }
    return maxfd;
}
 
