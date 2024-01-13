//
// Created by idan on 12/30/23.
//

#include "dummy_tcp_port_listener.h"

void dummy_tcp_port_listener::listen() {

    while (1) {
        puts("waiting for a client");
        std::unique_ptr<basic_client_handler> new_client = accept_new_connection->operator()();

        puts("client connection established");

        puts("client message:");
        while (true) {
            char msg[1];
//            memset((void*) msg, 'a', 1);

            if (new_client->read_from_client(msg, 1) == 0)
                break;

            printf("%c", *msg);
        }

        puts("client connection closed");
    }
}
