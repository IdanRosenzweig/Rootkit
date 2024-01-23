#include <unistd.h>
#include <asm-generic/socket.h>
#include <sys/socket.h>
#include "linux_client_handler.h"

linux_client_handler::linux_client_handler(int socketFd) : socket_fd(socketFd) {}

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

linux_client_handler::~linux_client_handler() {
    close(socket_fd);
}

bool linux_client_handler::is_connected() {
    return true;
//    int error;
//    socklen_t len = sizeof(error);
//    int ret = getsockopt(socket_fd, SOL_SOCKET, SO_ERROR, &error, &len);
//
//    if (ret == 0 && error == 0)
//        return true;
//    else
//        return false;
}
