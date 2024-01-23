#include "linux_tcp_connection_establisher.h"

#include "../error_codes.h"

std::unique_ptr <basic_client_handler> linux_tcp_connection_establisher::next_client() {
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
        if (client_sd == ACCEPT_ERROR) // can't accept the client
            continue;

        return std::make_unique<linux_client_handler>(client_sd);
    }
}
