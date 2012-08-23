#define LOG_LEVEL LOG_VERBOSE
#include <log.h>
#include <wrapper/socket.h>

int main()
{
    _LOGV("Begin test\n");
    
    SocketWrapper* socket = new SocketWrapper;

    socket->create();
    socket->bind(8000);
    socket->listen();

    SocketWrapper* client = new SocketWrapper;
    socket->accept(client);

    client->close();
    delete client;

    socket->close();
    delete socket;

    _LOGV("End test\n");

    return 0;
}

