#include "basic_server.h"

void basic_server::setConnectionEstablisher(std::unique_ptr<basic_connection_establisher> &&connectionEstablisher) {
//        basic_server::connectionEstablisher.reset(connectionEstablisher.release());
    basic_server::connectionEstablisher = std::move(connectionEstablisher);
}

void basic_server::accept_next_client() {
    curr_client = std::move(connectionEstablisher->next_client());
}

bool basic_server::is_client_connected() {
    return curr_client != nullptr;
}

const std::unique_ptr<basic_client_handler> &basic_server::get_connected_client() {
    return curr_client;
}

void basic_server::close_curr_client() {
    curr_client = nullptr;
}