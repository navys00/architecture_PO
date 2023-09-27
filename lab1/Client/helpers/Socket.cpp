#include <winsock2.h>
#include <WS2tcpip.h>

#include "Socket.h"
#include "UtilString.h"
#include <iostream>

static int sSocketId = 0;

Socket::Socket()
{
    if(++sSocketId == 1)
    {
        WSAData wsaData;
        WSAStartup(MAKEWORD(2,2), &wsaData); // выполняется один раз во время запуска
    }
}

Socket::~Socket()
{
    close();

    if(--sSocketId == 0)
        WSACleanup(); // this is executed once during app teardown ....во время прерывания приложения
}

bool Socket::init(DWORD timeout)
{
    if ((m_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) //1-тип адресации сокета, поток сокета для доставки данных, установка протокола сокета по умолчанию
    {
        printf("socket error\n");
        return false;
    }

    if(timeout)
        setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(DWORD));
    m_timeout = timeout;
    return true;
    //setsockopt установка поций сокета 1-сокет, 2-код опции зависит от типа сокета и протокола(указывает на максимальное время в течение которого сокет работает), 
}

bool Socket::isValid()
{
    return m_socket >= 0;
}

int Socket::send(const char* msg, int len)
{
    if(len <= 0)
        return 0;
    printf("SEND\n----------\n%s\n----------\n", msg);
    return ::send(m_socket, msg, len, 0);// flag 0 - работа send в обычном режиме
}

int Socket::sendStr(const std::string& str)
{
    return send(str.c_str(), str.length());
}

int Socket::recv()
{
    int cur = 0;
    int total = 0;
    const int CHUNK = 1024;
    do
    {
        if(m_recv.size() < total + CHUNK)
            m_recv.resize(m_recv.size() + CHUNK);
        cur = ::recv(m_socket, m_recv.data()+total, m_recv.size()-total-1, 0);
        if(cur > 0)
            total += cur;
    }
    while(cur > 0);
    m_recv[total] = 0;
    return total;
}

char* Socket::data()
{
    return m_recv.data();
}

void Socket::close()
{
    if(m_socket != -1)
    {
        shutdown(m_socket, SD_BOTH);
        closesocket(m_socket);
    }
}
