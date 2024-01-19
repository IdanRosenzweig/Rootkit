//
// Created by idan on 1/17/24.
//

#ifndef ROOTKIT_HIDDEN_TCP_PORTS_H
#define ROOTKIT_HIDDEN_TCP_PORTS_H

#include "../operations_protocol.h"

#define NO_PORTS 65536
//extern int hidden_ports[NO_PORTS];

void add_hidden_tcp4_port(PORT port);
void remove_hidden_tcp4_port(PORT port);

int is_tcp4_port_hidden(PORT port);

void add_hidden_tcp6_port(PORT port);
void remove_hidden_tcp6_port(PORT port);

int is_tcp6_port_hidden(PORT port);

#endif //ROOTKIT_HIDDEN_TCP_PORTS_H
