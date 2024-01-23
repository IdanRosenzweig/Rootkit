#ifndef ROOTKIT_MSG_TO_USER_H
#define ROOTKIT_MSG_TO_USER_H

#define MAX_MSG_TO_USR_SZ 200

struct msg_to_user {
    char data[MAX_MSG_TO_USR_SZ];
};

#endif //ROOTKIT_MSG_TO_USER_H
