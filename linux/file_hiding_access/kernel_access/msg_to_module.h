//
// Created by idan on 1/11/24.
//

#ifndef ROOTKIT_MSG_TO_MODULE_H
#define ROOTKIT_MSG_TO_MODULE_H

#include "operations_ids.h"

#define MAX_MSG_SIZE 500

struct msg_to_module {
    OPER_ID id;
    char data[MAX_MSG_SIZE];
};

#endif //ROOTKIT_MSG_TO_MODULE_H
