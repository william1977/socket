#define LOG_LEVEL LOG_VERBOSE
#include <log.h>
#include <wrapper/socket.h>
#include <string.h>

int main()
{
    _LOGV("Begin test\n");
    
    IPSocket* socket = new IPSocket;

    socket->create();
    socket->bind(8000);
    socket->listen();

    IPSocket* client = new IPSocket;
    socket->accept(client);

    char buf[65535];
    memset(buf, 0, sizeof(buf));
    ssize_t read_len;
    client->recv(buf, sizeof(buf), &read_len);
    _LOGV("Receive : %s \n", buf);

    sprintf(buf, "HTTP/1.1 200 OK\r\n\r\n");
    client->send(buf, strlen(buf), &read_len);

    client->close();
    delete client;

    socket->close();
    delete socket;

    _LOGV("End test\n");

    return 0;
}

