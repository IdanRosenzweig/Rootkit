//
// Created by idan on 12/30/23.
//

#include <unistd.h>
#include "linux_client_handler.h"


linux_client_handler::linux_client_handler(int socketFd) : socket_fd(socketFd) {}

void linux_client_handler::setSocketFd(int socketFd) {
    socket_fd = socketFd;
}

int linux_client_handler::read_from_client(char *buff, int count) {
    int i = 0;
    while (i < count && read(socket_fd, (void*) (buff + i), 1) == 1) {
        i++;
    }

    return i;
}

int linux_client_handler::write_to_client(char *buff, int count) {
    int i = 0;
    while (i < count && write(socket_fd, (void*) (buff + i), 1) == 1) {
        i++;
    }

    return i;
}
