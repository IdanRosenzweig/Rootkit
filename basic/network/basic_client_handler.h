#ifndef ROOTKIT_BASIC_CLIENT_HANDLER_H
#define ROOTKIT_BASIC_CLIENT_HANDLER_H

// used by servers to handle clients
class basic_client_handler {
public:
    virtual int recv_data(char* buff, int count) = 0;
    virtual int send_data(const char* buff, int count) = 0;

    virtual bool is_connected() = 0;

};

#endif //ROOTKIT_BASIC_CLIENT_HANDLER_H
