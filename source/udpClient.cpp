#if !defined(UDP_CLIENT_CPP)
#define UDP_CLIENT_CPP

#if defined(_WIN32)
#include <stdio.h>
#endif

#include <string>
#include <cstring>
#if !defined(_WIN32)
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#else 
#include <WinSock2.h>
#include <ws2tcpip.h>
#endif
#include "enums.h"
#include "ftdException.hpp"
#include "udpClient.hpp"

using namespace std;
using namespace FTDI;
using namespace udp;

udp_client::udp_client(const std::string& addr, int port)
    : f_port(port)
    , f_addr(addr)
{
#if !defined(_WIN32)
    string decimal_port=to_string(f_port);
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;

    int r(getaddrinfo(addr.c_str(), decimal_port.c_str(), &hints, &f_addrinfo));
    if(r != 0)
    {
        if(r == EAI_SYSTEM)  {
            socketThrow(errno);
        } else {
            addrinfoThrow(r);                                                                                                                                                    addrinfoThrow(r);
        }
    }
    f_socket = socket(f_addrinfo->ai_family, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);
    if(f_socket == -1)
    {
        freeaddrinfo(f_addrinfo);

        socketThrow(errno);
    }
#else
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2, 2),&wsa) != 0)
    {
        addrinfoThrow(WSAGetLastError());
    }
    if ((f_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
    {
        socketThrow(WSAGetLastError());
    }
    memset((char*)&f_addrinfo, 0, sizeof(f_addrinfo));
    f_addrinfo.sin_family = AF_INET;
    f_addrinfo.sin_port = htons(f_port);
    int retCode = inet_pton(AF_INET,f_addr.c_str(), &f_addrinfo.sin_addr);
    if (retCode != 1) {
        if (!retCode) {
            socketThrowInfo(EINVAL2,"The String reperesntation of the IPV4 is not a valid IPv4 dotted - decimal string");
        }
        else {
            socketThrow(WSAGetLastError());
        }
    }
#endif
}

udp_client::~udp_client()
{
#if !defined(_WIN32)
    freeaddrinfo(f_addrinfo);
    close(f_socket);
#else
    closesocket(f_socket);
    WSACleanup();
#endif
}

#if !defined(_WIN32)
int udp_client::get_socket() const
#else
SOCKET udp_client::get_socket() const
#endif
{
    return f_socket;
}

int udp_client::get_port() const
{
    return f_port;
}

std::string udp_client::get_addr() const
{
    return f_addr;
}

void udp_client::send(const string &msg)
{
#if !defined(_WIN32)
    ssize_t numBytesSent;

    numBytesSent=sendto(f_socket, msg.c_str(), msg.size(), 0, f_addrinfo->ai_addr, f_addrinfo->ai_addrlen);
    if(numBytesSent == (-1)) {
        socketThrow(errno);
    }
#else
    int numBytesSent;
    numBytesSent = sendto(f_socket, msg.c_str(), static_cast<int>(msg.size()), 0, (struct sockaddr*) & f_addrinfo, sizeof(f_addrinfo));
    if(numBytesSent==SOCKET_ERROR)
    {
        socketThrow(WSAGetLastError());
    }
#endif
}

void udp_client::send(const unsigned char *msg, size_t size)
{
#if !defined(_WIN32)
    ssize_t numBytesSent;

    numBytesSent=sendto(f_socket, msg, size, 0, f_addrinfo->ai_addr, f_addrinfo->ai_addrlen);
    if(numBytesSent == (-1)) {
        socketThrow(errno);
    }
#else
    int numBytesSent;
    numBytesSent = sendto(f_socket, (const char *)msg, static_cast<int>(size), 0, (struct sockaddr*) & f_addrinfo, sizeof(f_addrinfo));
    if (numBytesSent == SOCKET_ERROR)
    {
        socketThrow(WSAGetLastError());
    }
#endif
}
#endif