//
// Created by idan on 12/30/23.
//

#ifndef ROOTKIT_BASIC_LISTENER_H
#define ROOTKIT_BASIC_LISTENER_H

#include "basic_client_handler.h"
#include "basic_connection_establisher.h"

#include <memory>
#include <utility>

class basic_listener {
protected:
    std::unique_ptr<basic_connection_establisher> accept_new_connection = nullptr;

public:

    void setConnectionEstablisher(std::unique_ptr<basic_connection_establisher> &&connectionEstablisher) {
//        accept_new_connection.reset(connectionEstablisher.release());
        accept_new_connection = std::move(connectionEstablisher);
    }

    virtual void listen() = 0;
};

#endif //ROOTKIT_BASIC_LISTENER_H
