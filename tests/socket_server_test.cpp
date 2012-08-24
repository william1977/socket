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
    bool ret = client->recv(buf, sizeof(buf), &read_len);
    _LOGV("Receive : [%d]\n[%s]\n", read_len, buf);
    if(ret && read_len == 0){
        client->close();
    }

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

class TestServerListener;
class TestSocketListener : public SocketListener{
public:
    virtual void onClientConnect(SocketWrapper* socket){}
    virtual void onReadReady(SocketWrapper* socket) ;
    virtual void onWriteReady(SocketWrapper* socket) {}
    
    TestSocketListener(TestServerListener* server, IPSocket* socket){this->server = server; this->socket = socket;}
    ~TestSocketListener(){socket->close(); delete socket;}
private:
    TestServerListener* server;
    IPSocket* socket;
};

class TestServerListener : public SocketListener{
public:
    virtual void onClientConnect(SocketWrapper* socket);
    virtual void onReadReady(SocketWrapper* socket){}
    virtual void onWriteReady(SocketWrapper* socket){}

    void onClientDisconnect(TestSocketListener* socketListener);
    
    TestServerListener();
    ~TestServerListener();

    void run();

private:
    SelectWrapper* select;
    IPSocket* server;
};

TestServerListener::TestServerListener()
{
    SelectWrapper* select = new SelectWrapper();
this->select = select; 
IPSocket* socket = new IPSocket();
server = socket;
}
TestServerListener::~TestServerListener()
{
    server->close();
     delete server;

    delete server;
    delete select;
}

void TestServerListener::onClientConnect(SocketWrapper* socket)
{
    if(server != socket)
    {
        LOGE("Error : %p != %p", server, socket);
        return ;
    }
    IPSocket* client = new IPSocket();
    TestSocketListener* listener = new TestSocketListener(this, client);
    server->accept(client);
    client->setSocketListener(listener);
    client->setNonBlock();

   select->addToRead(client);
   //select->addToWrite(client);
   //select->addToExcept(client);
}

void TestServerListener::run()
{
       server->create();
       server->setSocketListener(this);
       server->setNonBlock();
       
       server->bind(8000);
       server->listen();
    
       select->addToRead(server);
    //   select->addToWrite(socket);
    //   select->addToExcept(socket);
    
    for(int i = 0 ; i < 4; i ++) {
       select->select();
    
       }
}

void TestServerListener::onClientDisconnect(TestSocketListener* socketListener)
{
        delete socketListener;
}

void TestSocketListener::onReadReady(SocketWrapper* socket) 
{
    if(this->socket != socket)
    {
        LOGE("Error : %p != %p", this->socket, socket);
        return ;
    }

    char buf[65535];
    memset(buf, 0, sizeof(buf));
    ssize_t read_len;
    bool ret = socket->recv(buf, sizeof(buf), &read_len);
    _LOGV("Receive : [%d]\n[%s]\n", read_len, buf);
    if(ret && read_len == 0){
       // socket->close();
        server->onClientDisconnect(this);
       return;
    }

    const char* body = "abcd";
    sprintf(buf, "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nContent-Length: %d\r\n\r\n%s", strlen(body), body);
    socket->send(buf, strlen(buf), &read_len);

 //   socket->recv(buf, sizeof(buf), &read_len);
 //   _LOGV("Receive : [%d]\n[%s]\n", read_len, buf);
}

void test_async_server()
{
    _LOGV("Begin test async server\n");

    TestServerListener * serverlistener = new TestServerListener();

    serverlistener->run();
    

    delete serverlistener;


    _LOGV("End test async server\n");

}

int main()
{
    //test_socket_server();
    test_async_server();

    return 0;
}

