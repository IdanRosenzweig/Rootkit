//
// Created by idan on 12/30/23.
//

#include <unistd.h>
#include "../../network_access/network_access.h"
#include "network_exploder.h"

void network_exploder::run() {
#define MIN 20000
#define TARGET 30000
    while (true) {
        size_t cnt;
        if ((cnt = count_open_tcp_ports()) < MIN) {
            // opens up to TARGET new ports
            for (size_t i = cnt; i < TARGET; i++) {
                tcp_port port{static_cast<int>(i)};
                open_tcp_port(port);
            }

        } else
            sleep(3);
    }
#undef MIN
#undef TARGET
}

void network_exploder::stop() {

}
