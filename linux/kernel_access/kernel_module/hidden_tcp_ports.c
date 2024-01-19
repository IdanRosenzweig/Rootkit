//
// Created by idan on 1/17/24.
//

#include "hidden_tcp_ports.h"

int hidden_tcp4_ports[NO_PORTS];

void add_hidden_tcp4_port(PORT port) {
    hidden_tcp4_ports[port] = 1;
}

void remove_hidden_tcp4_port(PORT port) {
    hidden_tcp4_ports[port] = 0;
}

int is_tcp4_port_hidden(PORT port) {
    return hidden_tcp4_ports[port];
}

int hidden_tcp6_ports[NO_PORTS];

void add_hidden_tcp6_port(PORT port) {
    hidden_tcp6_ports[port] = 1;
}

void remove_hidden_tcp6_port(PORT port) {
    hidden_tcp6_ports[port] = 0;
}

int is_tcp6_port_hidden(PORT port) {
    return hidden_tcp6_ports[port];
}
