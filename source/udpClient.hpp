#if !defined(UDP_CLIENT_H)
#define UDP_CLIENT_H

#include <string>

namespace udp {
    class udp_client
    {
    public:
                            udp_client(const std::string& addr, int port);
                            ~udp_client();

        int                 get_socket() const;
        int                 get_port() const;
        std::string         get_addr() const;

        void                 send(const string &msg);

    private:
        int                 f_socket;
        int                 f_port;
        std::string         f_addr;
        struct addrinfo *   f_addrinfo;
    };
}
#endif