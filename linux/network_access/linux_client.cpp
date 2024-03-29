#include "linux_client.h"

#include <iostream>

#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

void linux_client::connect() {
    my_sd = socket(AF_INET, SOCK_STREAM, 0);
    if (my_sd == SOCKET_ERROR) {
        disconnect();
        return;
    }

    struct sockaddr_in my_addr;
    memset(&my_addr, '\x00', sizeof(struct sockaddr_in));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET,
                  server_addr.c_str(),
                  (void *) &my_addr.sin_addr
    ) == INET_PTON_ERROR) {
        disconnect();
        return;
    }

    std::cout << "connecting to the rootkit..." << std::endl;
    if (::connect(my_sd,
                  (struct sockaddr *) &my_addr,
                  sizeof(my_addr)
    ) < 0) {
        disconnect();
        return;
    }

    std::cout << "connected successfully" << std::endl;

}

void linux_client::disconnect() {
    if (my_sd != SOCKET_ERROR)
        close(my_sd);
}

ssize_t linux_client::send_data(const char *buff, int count) {
    if (my_sd == SOCKET_ERROR)
        return 0;

    return write(my_sd, (void *) buff, count);
}

int linux_client::recv_data(char *buff, int count) {
    int done = 0;
    while (done < count) {
        if (read(my_sd, &buff[done], 1) == 1)
            done++;
    }
    return done;
}

linux_client::linux_client(TCP_PORT serverPort, const std::string &serverAddr) : server_port(serverPort),
                                                                            server_addr(serverAddr) {}
