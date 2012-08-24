#define LOG_LEVEL LOG_VERBOSE
#include <log.h>
#include <wrapper/socket.h>
#include <string.h>

void test_socket_server()
{
    _LOGV("Begin test server\n");
    
    IPSocket* socket = new IPSocket;
    socket->create();
    //socket->setNonBlock();
    
    socket->bind(8000);
    socket->listen();

    IPSocket* client = new IPSocket;
    socket->accept(client);
    //client->setNonBlock();

    char buf[65535];
    memset(buf, 0, sizeof(buf));
    ssize_t read_len;
    client->recv(buf, sizeof(buf), &read_len);
    _LOGV("Receive : [%d]\n[%s]\n", read_len, buf);

    const char* body = "abcd";
    sprintf(buf, "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nContent-Length: %d\r\n\r\n%s", strlen(body), body);
    client->send(buf, strlen(buf), &read_len);

    //client->recv(buf, sizeof(buf), &read_len);
    //_LOGV("Receive : [%d]%s \n", read_len, buf);

    client->close();

    socket->accept(client);

    memset(buf, 0, sizeof(buf));
    client->recv(buf, sizeof(buf), &read_len);
    _LOGV("Receive : [%d]\n[%s]\n", read_len, buf);

    sprintf(buf, "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nContent-Length: %d\r\n\r\n%s", strlen(body), body);
    client->send(buf, strlen(buf), &read_len);

    client->close();
    
    delete client;

    socket->close();
    delete socket;

    _LOGV("End test server\n");

}


class TestServerListener : public SocketListener{
public:
    virtual void onAccept(SocketWrapper* socket);
    virtual void onRecv(void *buf, size_t len) {}
    virtual void onSend(const void *buf, size_t len) {}
};

void TestServerListener::onAccept(SocketWrapper* socket)
{

}

class TestSocketListener : public SocketListener{
public:
    virtual void onAccept(SocketWrapper* socket) {}
    virtual void onRecv(void *buf, size_t len);
    virtual void onSend(const void *buf, size_t len);
};

void TestSocketListener::onRecv(void *buf, size_t len)
{

}

void TestSocketListener::onSend(const void *buf, size_t len)
{

}

void test_async_server()
{
    _LOGV("Begin test async server\n");

    TestServerListener * serverlistener = new TestServerListener();
    IPSocket* socket = new IPSocket();
    socket->create();
    socket->setSocketListener(serverlistener);
    socket->setNonBlock();
    
    socket->bind(8000);
    socket->listen();

    TestSocketListener * listener = new TestSocketListener();
    IPSocket* client = new IPSocket();
    socket->accept(client);
    client->setSocketListener(listener);
    client->setNonBlock();

    char buf[65535];
    memset(buf, 0, sizeof(buf));
    ssize_t read_len;
    client->recv(buf, sizeof(buf), &read_len);
    _LOGV("Receive : [%d]\n[%s]\n", read_len, buf);

    const char* body = "abcd";
    sprintf(buf, "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nContent-Length: %d\r\n\r\n%s", strlen(body), body);
    client->send(buf, strlen(buf), &read_len);

    //client->recv(buf, sizeof(buf), &read_len);
    //_LOGV("Receive : [%d]%s \n", read_len, buf);

    client->close();
    
    delete client;

    socket->close();
    delete socket;

    _LOGV("End test async server\n");

}

int main()
{
    //test_socket_server();
    test_async_server();

    return 0;
}
