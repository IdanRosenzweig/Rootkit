#include "remote_control/remote_control_client.h"

#define REMOTE_PORT 1234
#define REMOTE_ADDR "127.0.0.1"

void execute() {
    remote_control_client client(REMOTE_PORT, REMOTE_ADDR);
    client.run();

}

int main() {
    execute();
}