//
// Created by idan on 1/17/24.
//

#include "hidden_tcp_ports.h"

int hidden_ports[NO_PORTS];

void add_hidden_tcp_port(PORT port) {
    hidden_ports[port] = 1;
}

void remove_hidden_tcp_port(PORT port) {
    hidden_ports[port] = 0;
}

int is_tcp_port_hidden(PORT port) {
    return hidden_ports[port];
}
