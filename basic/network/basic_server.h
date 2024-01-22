//
// Created by idan on 12/30/23.
//

#ifndef ROOTKIT_BASIC_SERVER_H
#define ROOTKIT_BASIC_SERVER_H

#include "basic_client_handler.h"
#include "basic_connection_establisher.h"

#include <memory>
#include <utility>

class basic_server {
protected:
    std::unique_ptr<basic_connection_establisher> connectionEstablisher = nullptr;

    std::unique_ptr<basic_client_handler> accept_next_client() {
        return connectionEstablisher->next_client();
    }

public:
    void setConnectionEstablisher(std::unique_ptr<basic_connection_establisher>&&connectionEstablisher) {
//        basic_server::connectionEstablisher.reset(connectionEstablisher.release());
        basic_server::connectionEstablisher = std::move(connectionEstablisher);
    }

    // is there a linux_client connected right now
    virtual bool is_client_connected() = 0;

    virtual const std::unique_ptr<basic_client_handler>& get_connected_client() = 0;

    virtual void listen() = 0;

};

#endif //ROOTKIT_BASIC_SERVER_H
