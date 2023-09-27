#pragma once
#include <string>
#include <vector>
#include <windows.h>

class SocketServer;

// base class for a socket
class Socket
{
public:
    Socket();
    virtual ~Socket();
    bool init(DWORD timeout = 0); // creates socket and performs basic initialization
    bool isValid(); // checks if socket is valid
    int send(const char* msg, int len); // sends a message via socket via-через
    int sendStr(const std::string& str); // sends a string via socket вызывает send, который и отправляет
    int recv(); // receives a message via socket receive - получать
    char* data(); // buffer that holds received message хранит полученное сообщение
    void close(); // closes socket

protected:
    int m_socket = -1; // low-level socket object
    int m_timeout = 0; // if input/output operation is not complete during this period of time, this operation aborts
    std::vector<char> m_recv; // buffer that holds received message

    friend class SocketServer;
};
