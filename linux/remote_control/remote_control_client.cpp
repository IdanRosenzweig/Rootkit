#include "remote_control_client.h"

#include <iostream>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "../network_access/linux_client.h"

#include "protocol.h"

void remote_control_client::run() {

    linux_client client(server_port, server_addr);

    client.connect();

    while (1) {
        int type;
        std::cin >> type;

        switch (type) {
            case 1: { // send shell command
                std::string command;

                while (1) {
                    char ch = getchar();
                    command += ch;

                    if (ch == '\n')
                        break;
                }
                for (int i = 0; i < command.size(); i++) {
                    if (command[i] != ' ') {
                        command = command.substr(i, command.size() - i);
                        break;
                    }
                }

                if (command.starts_with("exit")) {
                    std::cout << "closing client" << std::endl;

                    R_OPER dis = R_OPER_DISCONNECT;
                    client.send_data(reinterpret_cast<const char *>(&dis), sizeof(dis));

                    goto close;
                }

                // send command
                R_OPER id = R_OPER_EXEC_SHELL_COMMAND;
                client.send_data(reinterpret_cast<const char *>(&id), sizeof(id));

                R_OPER_SHELL_COMAMND_SZ len = command.length();
                client.send_data(reinterpret_cast<const char *>(&len), sizeof(len));

                client.send_data(reinterpret_cast<const char *>(command.data()), len);


                // receive output
                R_OPER_SHELL_COMAMND_OUTPUT_SZ output_len;
                client.recv_data(reinterpret_cast<char *>(&output_len), sizeof(output_len));

                std::string output(output_len, '\x00');
                client.recv_data(reinterpret_cast<char *>(output.data()), output_len);

                std::cout << "received data:" << std::endl;
                std::cout << output << std::endl;

                break;
            }
            case 2: { // execute C program
                std::string path;
                std::cin >> path;

                struct stat file_stat{};
                if (stat(path.c_str(), &file_stat) == STAT_ERROR) throw "error reading file stat";

                size_t size = file_stat.st_size;
                if (size == 0) throw "file is empty";

                int fd = open(path.c_str(), O_RDONLY);
                if (fd == OPEN_ERROR) throw "can't open file";

                char *ptr = new char[size];
                ssize_t no_bytes_read = read(fd, (void *) ptr, size);
                if (no_bytes_read == READ_ERROR || (size_t) no_bytes_read != size) throw "can't read file";


                // send data
                R_OPER id = R_OPER_EXEC_C_PROGRAM;
                client.send_data(reinterpret_cast<const char *>(&id), sizeof(id));

                R_OPER_C_PROGRAM_SZ len = size;
                client.send_data(reinterpret_cast<const char *>(&len), sizeof(len));

                client.send_data(reinterpret_cast<const char *>(ptr), len);

                // clean up
                delete[] ptr;
                if (close(fd) == CLOSE_ERROR)
                    throw "can't close file";

                // receive output
                // none

                break;
            }
            default: {
                std::cout << "bad type" << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                break;
            }
        }

    }

    close:
    client.disconnect();

}

