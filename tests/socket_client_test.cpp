#define LOG_LEVEL LOG_VERBOSE
#include <log.h>
#include <wrapper/socket.h>
#include <string.h>
#include <string>

void test_socket_client()
{
    _LOGV("Begin test client\n");
    
    IPSocket* socket = new IPSocket;
    socket->create();
    //socket->setNonBlock();

    socket->connect("127.0.0.1", 8000);
    
    std::string strbuf = "GET / HTTP/1.1\r\n";
    strbuf = strbuf + "Host: 43.82.112.228:8000\r\n";
    strbuf = strbuf + "User-Agent: Mozilla/4.0 (compatible; MSIE 999.1; Unknown)\r\n";
    strbuf = strbuf + "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n";
    strbuf = strbuf + "Accept-Language: en-us,en;q=0.5\r\n";
    strbuf = strbuf + "Accept-Encoding: gzip, deflate\r\n";
    strbuf = strbuf + "Connection: keep-alive\r\n";
    strbuf = strbuf + "Cache-Control: max-age=0\r\n";
    strbuf = strbuf + "\r\n";
    
    ssize_t write_len;
    socket->send(strbuf.c_str(), strbuf.length(), &write_len);

    char buf[65535];
    memset(buf, 0, sizeof(buf));
    ssize_t read_len;
    socket->recv(buf, sizeof(buf), &read_len);
    _LOGV("Receive : [%d]\n[%s]\n", read_len, buf);

    socket->close();
    delete socket;

    _LOGV("End test client\n");

}


void test_async_client()
{
    _LOGV("Begin test async client\n");
    
    IPSocket* socket = new IPSocket;
    socket->create();
    //socket->setNonBlock();

    socket->connect("127.0.0.1", 8000);
    
    std::string strbuf = "GET / HTTP/1.1\r\n";
    strbuf = strbuf + "Host: 43.82.112.228:8000\r\n";
    strbuf = strbuf + "User-Agent: Mozilla/4.0 (compatible; MSIE 999.1; Unknown)\r\n";
    strbuf = strbuf + "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n";
    strbuf = strbuf + "Accept-Language: en-us,en;q=0.5\r\n";
    strbuf = strbuf + "Accept-Encoding: gzip, deflate\r\n";
    strbuf = strbuf + "Connection: keep-alive\r\n";
    strbuf = strbuf + "Cache-Control: max-age=0\r\n";
    strbuf = strbuf + "\r\n";
    
    ssize_t write_len;
    socket->send(strbuf.c_str(), strbuf.length(), &write_len);

    char buf[65535];
    memset(buf, 0, sizeof(buf));
    ssize_t read_len;
    socket->recv(buf, sizeof(buf), &read_len);
    _LOGV("Receive : [%d]\n[%s]\n", read_len, buf);

    socket->close();
    delete socket;

    _LOGV("End test async client\n");

}

int main()
{
    test_socket_client();
 //   test_async_client();

    return 0;
}

