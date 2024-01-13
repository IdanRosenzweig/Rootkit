//
// Created by idan on 12/30/23.
//

#include "network_access.h"
#include "linux_client_handler.h"
#include "tcp/linux_tcp_port_connection_establisher.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <map>

static std::map<tcp_port, int> open_tcp_ports; // {tcp port, its open socket fd}

void open_tcp_port(tcp_port port) {
    if (open_tcp_ports.contains(port))
        return;

#define SOCKET_ERROR (-1)
#define BIND_ERROR (-1)
#define LISTEN_ERROR (-1)

    int sd = SOCKET_ERROR;
    struct sockaddr_in addr;
    bzero((void *) &addr, sizeof(addr));

    // opening a file descriptor
    sd = socket(
            AF_INET, // IPv4
            SOCK_STREAM,
            IPPROTO_TCP // TCP
    );
    if (sd == SOCKET_ERROR)
        goto err;

    // binding a socket
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(
            sd,
            (struct sockaddr *) &addr,
            sizeof(addr)
    ) == BIND_ERROR)
        goto err;

    // listening on the socket
    if (listen(sd, 1) == LISTEN_ERROR)
        goto err;

    open_tcp_ports.insert({port, sd});
    return;

    err:
    {
        if (sd != SOCKET_ERROR)
            close(sd);

    }
}

void close_tcp_port(tcp_port port) {
    if (!open_tcp_ports.contains(port))
        return;

    int sd = open_tcp_ports[port];
    close(sd);

    open_tcp_ports.erase(port);
}

void assign_tcp_port_connection_establisher(basic_tcp_port_listener &listener, tcp_port required_port) {
    listener.setConnectionEstablisher(
            std::make_unique<linux_tcp_port_connection_establisher>(open_tcp_ports[required_port])
    );
}

std::vector<tcp_port> get_all_open_tcp_ports() {
    std::vector<tcp_port> open_ports;
    for (const auto &ent: open_tcp_ports)
        open_ports.push_back(ent.first);

    return open_ports;
}

size_t count_open_tcp_ports() {
    return open_tcp_ports.size();
}

void recheck_open_tcp_ports() {

}




