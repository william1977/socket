#define LOG_LEVEL LOG_VERBOSE
#include <log.h>
#include <wrapper/socket.h>
#include <wrapper/select.h>
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

class TestSocketListener : public SocketListener{
public:
    virtual void onClientConnect(SocketWrapper* socket){}
    virtual void onReadReady(SocketWrapper* socket) ;
    virtual void onWriteReady(SocketWrapper* socket) {}
    
    TestSocketListener(SelectWrapper* select){this->select = select;}
private:
    SelectWrapper* select;
};

void TestSocketListener::onReadReady(SocketWrapper* socket) 
{
    char buf[65535];
    memset(buf, 0, sizeof(buf));
    ssize_t read_len;
    socket->recv(buf, sizeof(buf), &read_len);
    _LOGV("Receive : [%d]\n[%s]\n", read_len, buf);

    const char* body = "abcd";
    sprintf(buf, "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nContent-Length: %d\r\n\r\n%s", strlen(body), body);
    socket->send(buf, strlen(buf), &read_len);

 //   socket->recv(buf, sizeof(buf), &read_len);
 //   _LOGV("Receive : [%d]\n[%s]\n", read_len, buf);
}


class TestServerListener : public SocketListener{
public:
    virtual void onClientConnect(SocketWrapper* socket);
    virtual void onReadReady(SocketWrapper* socket){}
    virtual void onWriteReady(SocketWrapper* socket){}
    
    TestServerListener(SelectWrapper* select, IPSocket* socket){this->select = select; server = socket;}
    ~TestServerListener();

private:
    TestSocketListener * listener;
    IPSocket* client;
    SelectWrapper* select;
    IPSocket* server;
};

TestServerListener::~TestServerListener()
{
        client->close();
        
        delete client;
        delete listener;
}

void TestServerListener::onClientConnect(SocketWrapper* socket)
{
    if(server != socket)
    {
        LOGE("Error : %p != %p", server, socket);
        return ;
    }
    listener = new TestSocketListener(select);
    client = new IPSocket();
    server->accept(client);
    client->setSocketListener(listener);
    client->setNonBlock();

   select->addToRead(client);
   //select->addToWrite(client);
   //select->addToExcept(client);
    
}

void test_async_server()
{
    _LOGV("Begin test async server\n");

    SelectWrapper* select = new SelectWrapper();

    IPSocket* socket = new IPSocket();
    TestServerListener * serverlistener = new TestServerListener(select, socket);
    socket->create();
    socket->setSocketListener(serverlistener);
    socket->setNonBlock();
    
    socket->bind(8000);
    socket->listen();

    select->addToRead(socket);
 //   select->addToWrite(socket);
 //   select->addToExcept(socket);

 for(int i = 0 ; i < 4; i ++) {
    select->select();

    }

   socket->close();
    delete socket;
    delete serverlistener;

    delete select;

    _LOGV("End test async server\n");

}

int main()
{
    //test_socket_server();
    test_async_server();

    return 0;
}

