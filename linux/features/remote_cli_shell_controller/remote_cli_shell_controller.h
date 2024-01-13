//
// Created by idan on 12/31/23.
//

#ifndef ROOTKIT_REMOTE_CLI_SHELL_CONTROLLER_H
#define ROOTKIT_REMOTE_CLI_SHELL_CONTROLLER_H

#include "../../../basic/basic_plugin.h"

class remote_cli_shell_controller : public basic_plugin {
public:

    void run() override;

    void stop() override;
};


#endif //ROOTKIT_REMOTE_CLI_SHELL_CONTROLLER_H
