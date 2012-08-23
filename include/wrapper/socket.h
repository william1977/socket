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

    bool bind(const struct sockaddr *addr, socklen_t addrlen);
    bool bind(int listen_port);
    bool listen(int backlog = 255);

    bool close();

public:
    bool isValid() {return sockfd != -1;}
    Error getLastError() {return error;}

private:
    bool setError(int ret, const char* function, int line);
    Error error;
};

#endif //_SOCKET_WRAPPER_H_
