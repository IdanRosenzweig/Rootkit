//
// Created by idan on 12/31/23.
//

#ifndef ROOTKIT_LINUX_SERVER_H
#define ROOTKIT_LINUX_SERVER_H

#include <queue>
#include "../../basic/network/basic_server.h"

class linux_server : public basic_server {
private:
    std::unique_ptr<basic_client_handler> curr_client = nullptr;

public:
    bool is_client_connected() override;

    const std::unique_ptr<basic_client_handler>& get_connected_client() override;

    void listen() override;
};


#endif //ROOTKIT_LINUX_SERVER_H
