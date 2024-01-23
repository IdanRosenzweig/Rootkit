#include "hidden_tcp_ports.h"

static int hidden_tcp4_ports[NO_PORTS];

void add_hidden_tcp4_port(int port) {
    hidden_tcp4_ports[port] = 1;
}

void remove_hidden_tcp4_port(int port) {
    hidden_tcp4_ports[port] = 0;
}

int is_tcp4_port_hidden(int port) {
    return hidden_tcp4_ports[port];
}

int hidden_tcp6_ports[NO_PORTS];

void add_hidden_tcp6_port(int port) {
    hidden_tcp6_ports[port] = 1;
}

void remove_hidden_tcp6_port(int port) {
    hidden_tcp6_ports[port] = 0;
}

int is_tcp6_port_hidden(int port) {
    return hidden_tcp6_ports[port];
}
