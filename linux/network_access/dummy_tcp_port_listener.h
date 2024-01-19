//
// Created by idan on 12/30/23.
//

#ifndef ROOTKIT_DUMMY_TCP_PORT_LISTENER_H
#define ROOTKIT_DUMMY_TCP_PORT_LISTENER_H

#include "../../basic/network/basic_listener.h"

class dummy_tcp_port_listener : public basic_listener {
public:
    void listen() override;
};


#endif //ROOTKIT_DUMMY_TCP_PORT_LISTENER_H
