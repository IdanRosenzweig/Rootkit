//
// Created by idan on 12/31/23.
//

#include <unistd.h>
#include "cli_shell_listener.h"

void cli_shell_listener::listen() {
    while (1) {
        puts("waiting for a client");
        std::unique_ptr<basic_client_handler> new_client = accept_new_connection->next_client();

        puts("client connection established");

        while (true) {
            puts("client shell message:");

            std::string command;
            while (true) {
                char ch;

                if (new_client->read_from_client(&ch, 1) == 0)
                    goto close;

                if (ch == '\n')
                    break;

                command += ch;
            }
            if (command == "exit")
                goto close;

            puts(command.c_str());

            commands_queue.push(command);
        }

        close:
        {
            puts("client connection closed");
        }
    }
}

std::string cli_shell_listener::pop_next_command() {
    while (commands_queue.empty()) {
    }

    std::string command = commands_queue.front();
    commands_queue.pop();

    return command;
}
