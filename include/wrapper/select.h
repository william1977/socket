#ifndef _SELECT_WRAPPER_H_
#define _SELECT_WRAPPER_H_

#include <vector>
#include <sys/select.h>

#include "error.h"

class SelectWrapper {
public:
    SelectWrapper();
    ~SelectWrapper();

    bool select(struct timeval *timeout = NULL);

//    bool add(SocketWrapper*socket, bool addToRead = false, bool addToWrite = false, bool addToExpect = false);
//    bool remove(SocketWrapper*socket, bool addToRead = false, bool addToWrite = false, bool addToExpect = false);

    bool addToRead(SocketWrapper*socket);
    bool removeFromRead(SocketWrapper*socket);
    bool isReadable(SocketWrapper*socket);

    bool addToWrite(SocketWrapper*socket);
    bool removeFromWrite(SocketWrapper*socket);
    bool isWritable(SocketWrapper*socket);

    bool addToExpect(SocketWrapper*socket);
    bool removeFromExpect(SocketWrapper*socket);
    bool isExpect(SocketWrapper*socket);

private:
//    int nfds;
    fd_set readfds;
    fd_set writefds;
    fd_set exceptfds;

    std::vector<SocketWrapper*> reads;
    std::vector<SocketWrapper*> writes;
    std::vector<SocketWrapper*> excepts;

    bool add(std::vector<SocketWrapper*>& collection, SocketWrapper*socket);
    bool remove(std::vector<SocketWrapper*>& collection, SocketWrapper*socket);
    int getMaxfd(std::vector<SocketWrapper*>& collection, int nfds);

public:
    Error getLastError() {return error;}

private:
    bool setError(int ret, const char* function, int line);
    Error error;
};

#endif //_SELECT_WRAPPER_H_
