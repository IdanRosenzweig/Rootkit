//
// Created by idan on 1/21/24.
//

#ifndef ROOTKIT_MSG_TO_CONTROLLER_H
#define ROOTKIT_MSG_TO_CONTROLLER_H

#define MAX_MSG_TO_CONTROLLER_SZ 2000

struct msg_to_controller {
    char data[MAX_MSG_TO_CONTROLLER_SZ];
};

#endif //ROOTKIT_MSG_TO_CONTROLLER_H
