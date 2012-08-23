#ifndef _SOCKET_WRAPPER_H_
#define _SOCKET_WRAPPER_H_

#include <sys/socket.h>

#include "error.h"

class SocketWrapper {
private:
    int sockfd;
    
public:
    SocketWrapper(int domain = AF_INET, int type = SOCK_STREAM, int protocol = 0);
    ~SocketWrapper();

public:
    bool isValid() {return sockfd != -1;}
    Error getLastError() {return error;}

private:
    Error error;
};

#endif //_SOCKET_WRAPPER_H_
