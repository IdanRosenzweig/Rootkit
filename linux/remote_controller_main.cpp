//
// Created by idan on 1/20/24.
//

#include <iostream>

#include "remote_control/remote_control_client.h"

void execute() {
    std::cout << "remove controller start" << std::endl;

    remote_control_client client(1234, "127.0.0.1");
    client.run();

    std::cout << "remove controller end"  << std::endl;

}

int main() {
    execute();
}