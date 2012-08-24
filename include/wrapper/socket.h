#ifndef _SOCKET_WRAPPER_H_
#define _SOCKET_WRAPPER_H_

#include <sys/socket.h>
#include <netinet/in.h>

#include "error.h"

class SocketWrapper {
    friend class SelectWrapper;
private:
    int sockfd;
    
public:
    SocketWrapper();
    ~SocketWrapper();

    bool create(int domain = AF_INET, int type = SOCK_STREAM, int protocol = 0);
    bool bind(const struct sockaddr *addr, socklen_t addrlen);
    bool listen(int backlog = 255);
    bool accept(SocketWrapper* socket, struct sockaddr *addr, socklen_t *addrlen);
    bool recv(void *buf, size_t len, ssize_t* read_len, int flags = 0);
    bool send(const void *buf, size_t len, ssize_t* write_len, int flags = 0);
    bool fcntl(int cmd, int arg, int* out_arg = NULL);
    bool setNonBlock();
    bool connect(const struct sockaddr *addr, socklen_t addrlen);

    bool close();

//public:
  //  bool bind(int listen_port);
  //  bool accept(SocketWrapper* socket);

public:
    bool isValid() {return sockfd != -1;}
    Error getLastError() {return error;}

private:
    bool setError(int ret, const char* function, int line);
    Error error;

protected:
    bool isListening;
};

class SocketListener {
public:
    virtual void onClientConnect(SocketWrapper* socket) = 0;
    virtual void onReadReady(SocketWrapper* socket) = 0;
    virtual void onWriteReady(SocketWrapper* socket) = 0;
    
  //  virtual void onAccept(SocketWrapper* socket) = 0;
  //  virtual void onRecv(void *buf, size_t len) = 0;
  //  virtual void onSend(const void *buf, size_t len) = 0;
};


class AnsycSocket : public SocketWrapper {
    friend class SelectWrapper;
public:
    AnsycSocket(SocketListener* socketListener = NULL);
    void setSocketListener(SocketListener* socketListener);

private:
    void onRead();
    void onWrite();
    void onExcept();
    
private:
    SocketListener* listener;
};

class IPSocket : public AnsycSocket {
public:
    bool bind(int listen_port, const char* address = NULL);
    bool accept(IPSocket* socket);
    bool connect(const char* address, int port);

private:
    struct sockaddr_in addr;
    struct sockaddr_in peer_addr;

};

#endif //_SOCKET_WRAPPER_H_
