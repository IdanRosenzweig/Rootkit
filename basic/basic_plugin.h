//
// Created by idan on 12/24/23.
//

#ifndef ROOTKIT_BASIC_PLUGIN_H
#define ROOTKIT_BASIC_PLUGIN_H

#include "mex_generator.h"

class basic_plugin {
protected:
    id my_id;
public:
    basic_plugin() {}
    virtual ~basic_plugin() = default;

    const id &getMyId() const {
        return my_id;
    }

    void setMyId(id&& myId) {
        my_id = std::move(myId);
    }

    virtual void run() = 0;
    virtual void stop() = 0;

};

#endif //ROOTKIT_BASIC_PLUGIN_H
