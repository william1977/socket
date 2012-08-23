#define LOG_LEVEL LOG_VERBOSE
#include <log.h>
#include <wrapper/socket.h>
#include <string.h>

int main()
{
    _LOGV("Begin test\n");
    
    IPSocket* socket = new IPSocket;
    socket->setNonBlock();

    socket->create();
    socket->bind(8000);
    socket->listen();

    IPSocket* client = new IPSocket;
    socket->accept(client);
    client->setNonBlock();

    char buf[65535];
    memset(buf, 0, sizeof(buf));
    ssize_t read_len;
    client->recv(buf, sizeof(buf), &read_len);
    _LOGV("Receive : [%d]%s \n", read_len, buf);

    const char* body = "abcd";
    sprintf(buf, "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nContent-Length: %d\r\n\r\n%s", strlen(body), body);
    client->send(buf, strlen(buf), &read_len);

    client->recv(buf, sizeof(buf), &read_len);
    _LOGV("Receive : [%d]%s \n", read_len, buf);

    client->close();
    delete client;

    socket->close();
    delete socket;

    _LOGV("End test\n");

    return 0;
}

