//
// Created by idan on 1/21/24.
//

#ifndef ROOTKIT_MSG_TO_ROOTKIT_H
#define ROOTKIT_MSG_TO_ROOTKIT_H

#include "protocol.h"

#define MAX_MSG_TO_ROOTKIT_SZ 200

struct msg_to_rootkit {
    R_OPER id;
    char data[MAX_MSG_TO_ROOTKIT_SZ];
};

#endif //ROOTKIT_MSG_TO_ROOTKIT_H
