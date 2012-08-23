#define LOG_LEVEL LOG_VERBOSE
#include <log.h>
#include <wrapper/socket.h>

int main()
{
    _LOGV("Begin test\n");
    
    SocketWrapper socket;

    _LOGV("End test\n");

    return 0;
}

