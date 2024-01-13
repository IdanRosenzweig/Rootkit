//
// Created by idan on 12/30/23.
//

#ifndef ROOTKIT_NETWORK_ACCESS_H
#define ROOTKIT_NETWORK_ACCESS_H

#include <vector>

#include "tcp/basic_tcp_port_listener.h"
#include "tcp/tcp_port.h"

void open_tcp_port(tcp_port);
void close_tcp_port(tcp_port);
void assign_tcp_port_connection_establisher(basic_tcp_port_listener& listener, tcp_port);
std::vector<tcp_port> get_all_open_tcp_ports();
size_t count_open_tcp_ports();
void recheck_open_tcp_ports();


#endif //ROOTKIT_NETWORK_ACCESS_H
