#ifndef ROOTKIT_LINUX_CLIENT_HANDLER_H
#define ROOTKIT_LINUX_CLIENT_HANDLER_H

#include "../../basic/network/basic_client_handler.h"

class linux_client_handler : public basic_client_handler {
protected:
    const int socket_fd = -1;
public:
    explicit linux_client_handler(int socketFd);
    virtual ~linux_client_handler();

    int recv_data(char *buff, int count) override;
    int send_data(const char *buff, int count) override;

    bool is_connected() override;
};


#endif //ROOTKIT_LINUX_CLIENT_HANDLER_H
