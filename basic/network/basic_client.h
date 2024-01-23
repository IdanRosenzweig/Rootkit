#ifndef ROOTKIT_BASIC_CLIENT_H
#define ROOTKIT_BASIC_CLIENT_H

#include <cstdio>

// used by clients
class basic_client {
public:
    virtual void connect() = 0;
    virtual void disconnect() = 0;

    virtual ssize_t send_data(const char* buff, int count) = 0;
    virtual int recv_data(char* buff, int count) = 0;
};

#endif //ROOTKIT_BASIC_CLIENT_H
