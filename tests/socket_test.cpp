#define LOG_LEVEL LOG_VERBOSE
#include <log.h>
#include <wrapper/socket.h>

int main()
{
    _LOGV("Begin test\n");
    
    SocketWrapper* socket = new SocketWrapper;

    socket->bind(8000);
    socket->listen();

    delete socket;

    _LOGV("End test\n");

    return 0;
}

