//
// Created by idan on 1/19/24.
//

#ifndef ROOTKIT_BASIC_CONNECTION_ESTABLISHER_H
#define ROOTKIT_BASIC_CONNECTION_ESTABLISHER_H

#include <memory>
#include "basic_client_handler.h"

struct basic_connection_establisher {
    virtual std::unique_ptr<basic_client_handler> next_client() = 0;
};

#endif //ROOTKIT_BASIC_CONNECTION_ESTABLISHER_H
