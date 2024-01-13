//
// Created by idan on 12/31/23.
//

#include "remote_cli_shell_controller.h"
#include "shell_command_tcp_port_listener.h"
#include "../../network_access/network_access.h"

#include <thread>

void remote_cli_shell_controller::run() {

    // open port
    tcp_port port {11111};
    open_tcp_port(port);


    shell_command_tcp_port_listener my_listener;
    // assign the connection establisher for the tcp listener
    assign_tcp_port_connection_establisher(my_listener, port);


    std::thread listen_thread(&shell_command_tcp_port_listener::listen, &my_listener);
    auto func = [&my_listener]() -> void {
        while (true) {
            system(my_listener.pop_next_command().c_str());
        }
    };
    std::thread exec_thread(func);
    listen_thread.join();
}

void remote_cli_shell_controller::stop() {

}
