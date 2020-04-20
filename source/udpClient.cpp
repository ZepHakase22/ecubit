#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
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
}

udp_client::~udp_client()
{
    freeaddrinfo(f_addrinfo);
    close(f_socket);
}

int udp_client::get_socket() const
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
    ssize_t numBytesSent;

    numBytesSent=sendto(f_socket, msg.c_str(), msg.size(), 0, f_addrinfo->ai_addr, f_addrinfo->ai_addrlen);
    if(numBytesSent == (-1)) {
        socketThrow(errno);
    }
}

void udp_client::send(const unsigned char *msg, size_t size)
{
    ssize_t numBytesSent;

    numBytesSent=sendto(f_socket, msg, size, 0, f_addrinfo->ai_addr, f_addrinfo->ai_addrlen);
    if(numBytesSent == (-1)) {
        socketThrow(errno);
    }
}