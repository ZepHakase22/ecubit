#if !defined(UDP_CLIENT_H)
#define UDP_CLIENT_H

#include <string>

namespace udp {
    class udp_client
    {
    public:
                            udp_client(const std::string& addr, int port);
                            ~udp_client();

#if !defined(_WIN32)
        int                 get_socket() const;
#else
        SOCKET              get_socket() const;
#endif
        int                 get_port() const;
        std::string         get_addr() const;

        void                 send(const string &msg);
        void                send(const unsigned char *msg, size_t size);

    private:
#if !defined(_WIN32)
        int                 f_socket;
#else
        SOCKET              f_socket;
#endif
        int                 f_port;
        std::string         f_addr;
#if !defined(_WIN32)
        struct addrinfo *   f_addrinfo;
#else
        sockaddr_in         f_addrinfo;
#endif
    };
}
#endif