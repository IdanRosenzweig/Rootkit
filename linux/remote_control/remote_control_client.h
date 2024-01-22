//
// Created by idan on 1/21/24.
//

#ifndef ROOTKIT_REMOTE_CONTROL_CLIENT_H
#define ROOTKIT_REMOTE_CONTROL_CLIENT_H

#include <string>
#include "../../basic/network/tcp_port.h"

class remote_control_client {
    TCP_PORT server_port;
    std::string server_addr;

public:
    remote_control_client(TCP_PORT serverPort, const std::string &serverAddr) : server_port(serverPort),
                                                                                       server_addr(serverAddr) {}
    void run();

};

#endif //ROOTKIT_REMOTE_CONTROL_CLIENT_H
