//
// Created by idan on 12/30/23.
//

#ifndef ROOTKIT_TCP_PORT_H
#define ROOTKIT_TCP_PORT_H

struct tcp_port {
    int num;

    operator int() {
        return num;
    }

    bool operator<(const tcp_port &rhs) const {
        return num < rhs.num;
    }
};

#endif //ROOTKIT_TCP_PORT_H
