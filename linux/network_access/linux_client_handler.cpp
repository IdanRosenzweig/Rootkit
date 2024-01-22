//
// Created by idan on 12/30/23.
//

#include <unistd.h>
#include "linux_client_handler.h"

linux_client_handler::linux_client_handler(int socketFd) : socket_fd(socketFd) {}

void linux_client_handler::setSocketFd(int socketFd) {
    socket_fd = socketFd;
}

int linux_client_handler::recv_data(char *buff, int count) {
    int done = 0;
    while (done < count) {
        if (read(socket_fd, &buff[done], 1) == 1)
            done++;
    }

    return done;
}

int linux_client_handler::send_data(const char *buff, int count) {
    int done = 0;
    while (done < count) {
        if (write(socket_fd, &buff[done], 1) == 1)
            done++;
    }

    return done;
}
