//
// Created by idan on 12/30/23.
//

#ifndef ROOTKIT_NETWORK_ACCESS_H
#define ROOTKIT_NETWORK_ACCESS_H

#include <vector>

#include "../../basic/network/basic_listener.h"
#include "../../basic/network/tcp_port.h"

void open_tcp_port(tcp_port);
void close_tcp_port(tcp_port);

std::unique_ptr<basic_connection_establisher> generate_tcp_port_connection_establisher(tcp_port);

std::vector<tcp_port> get_all_open_tcp_ports();
size_t count_open_tcp_ports();


#endif //ROOTKIT_NETWORK_ACCESS_H
