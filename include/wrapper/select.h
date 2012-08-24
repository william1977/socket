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

    bool addToRead(AnsycSocket*socket);
    bool removeFromRead(AnsycSocket*socket);

    bool addToWrite(AnsycSocket*socket);
    bool removeFromWrite(AnsycSocket*socket);

    bool addToExcept(AnsycSocket*socket);
    bool removeFromExcept(AnsycSocket*socket);

private:
    bool isReadable(AnsycSocket*socket);
    bool isWritable(AnsycSocket*socket);
    bool isExcept(AnsycSocket*socket);
    
//    int nfds;
//    fd_set readfds;
  //  fd_set writefds;
   // fd_set exceptfds;

    std::vector<AnsycSocket*> reads;
    std::vector<AnsycSocket*> writes;
    std::vector<AnsycSocket*> excepts;

    bool add(std::vector<AnsycSocket*>& collection, AnsycSocket*socket);
    bool remove(std::vector<AnsycSocket*>& collection, AnsycSocket*socket);
    int getMaxfd(std::vector<AnsycSocket*>& collection, int nfds, fd_set* fds);
    int checkRead(std::vector<AnsycSocket*>& collection, fd_set* fds);
    int checkWrite(std::vector<AnsycSocket*>& collection, fd_set* fds);
    int checkExcept(std::vector<AnsycSocket*>& collection, fd_set* fds);

public:
    Error getLastError() {return error;}

private:
    bool setError(int ret, const char* function, int line);
    Error error;
};

#endif //_SELECT_WRAPPER_H_
