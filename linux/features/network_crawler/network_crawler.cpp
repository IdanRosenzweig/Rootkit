//
// Created by idan on 12/30/23.
//

#include "network_crawler.h"
#include "../../network_access/network_access.h"
#include "../../network_access/tcp/dummy_tcp_port_listener.h"


void network_crawler::run() {
    // open a test port using the network component
    tcp_port port {5000};
    open_tcp_port(port);

    // create a dummy tcp port listener for that port
    dummy_tcp_port_listener listener;
    // assign the connection establisher for the listener
    assign_tcp_port_connection_establisher(listener, port);

    listener.listen();

}

void network_crawler::stop() {

}
