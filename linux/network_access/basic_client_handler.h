//
// Created by idan on 12/30/23.
//

#ifndef ROOTKIT_BASIC_CLIENT_HANDLER_H
#define ROOTKIT_BASIC_CLIENT_HANDLER_H

class basic_client_handler {
public:
    virtual int read_from_client(char* buff, int count) = 0; // returns the number of bytes actually read
    virtual int write_to_client(char* buff, int count) = 0; // returns the number of bytes actually written
};

#endif //ROOTKIT_BASIC_CLIENT_HANDLER_H
