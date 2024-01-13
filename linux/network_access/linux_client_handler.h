//
// Created by idan on 12/30/23.
//

#ifndef ROOTKIT_LINUX_CLIENT_HANDLER_H
#define ROOTKIT_LINUX_CLIENT_HANDLER_H

#include "basic_client_handler.h"

class linux_client_handler : public basic_client_handler {
protected:
    int socket_fd = -1;
public:
    explicit linux_client_handler(int socketFd);

    void setSocketFd(int socketFd);

    int read_from_client(char *buff, int count) override;

    int write_to_client(char *buff, int count) override;

    // todo deconstructor that closes socket_fd
};


#endif //ROOTKIT_LINUX_CLIENT_HANDLER_H
