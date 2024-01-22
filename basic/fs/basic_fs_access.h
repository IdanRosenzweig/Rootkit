//
// Created by idan on 12/30/23.
//

#ifndef ROOTKIT_BASIC_FS_ACCESS_H
#define ROOTKIT_BASIC_FS_ACCESS_H

#include <string>
#include <vector>

std::vector<std::string> get_dir_entries(std::string dir);

std::string read_file(char* path);

void remove_file(char* path);

void create_new_file(char* path);

void append_to_file(char* path, char* buff, int count);

std::string follow_symlink(std::string path);

#endif //ROOTKIT_BASIC_FS_ACCESS_H
