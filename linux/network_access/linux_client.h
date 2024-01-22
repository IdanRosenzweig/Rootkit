//
// Created by idan on 1/20/24.
//

#ifndef ROOTKIT_LINUX_CLIENT_H
#define ROOTKIT_LINUX_CLIENT_H

#include <string>

#include "../../basic/network/basic_client.h"
#include "../../basic/network/tcp_port.h"

class linux_client : public basic_client {
    TCP_PORT server_port;
    std::string server_addr;

#define SOCKET_ERROR (-1)
    int my_sd = SOCKET_ERROR;

public:
    linux_client() = delete;

    linux_client(TCP_PORT serverPort, const std::string &serverAddr);

    void connect() override;
    void disconnect() override;

    ssize_t send_data(const char* buff, int count) override;
    int recv_data(char *buff, int count) override;
};


#endif //ROOTKIT_LINUX_CLIENT_H
