//
// Created by idan on 12/31/23.
//

#include <iostream>
#include <cstring>
#include <unistd.h>
#include "linux_server.h"

bool linux_server::is_client_connected() {
    return curr_client != nullptr;
}

const std::unique_ptr<basic_client_handler>& linux_server::get_connected_client() {
    return curr_client;
}

void linux_server::listen() {
    while (1) {
        std::cout << "waiting for a linux_client" << std::endl;
        curr_client = accept_next_client();
        std::cout << "linux_client connection established" << std::endl;

//        if (!create_new_pipe())
//            goto close;
//
//        while (true) {
//            char ch;
//            if (curr_client->recv_data(&ch, 1) == 0)
//                break;
//
//            write(pipefd[1], &ch, 1);
//        }
//
//        close:
//        {
//            curr_client = nullptr;
//            clear_pipe();
//
//            std::cout << "linux_client connection closed" << std::endl;
//        };

        // todo check the state of the conenction
        while (true) {

        }
    }
}








