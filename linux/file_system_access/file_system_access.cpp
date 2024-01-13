//
// Created by idan on 12/30/23.
//

#include "file_system_access.h"

// static std::vector<int> open_fds;

std::string follow_symlink(std::string path) {
    std::filesystem::path p = path;
    while (std::filesystem::is_symlink(p))
        p = std::filesystem::read_symlink(p);

    return std::string{p};
}

//inline int no_filter(const struct dirent *) {
//    return 1;
//}
//std::vector<std::string> get_dir_entries(char *path, int (*filter)(const struct dirent *) = no_filter) {
//    struct dirent **entries;
//
//    int count = scandir(path, &entries, filter,
//                        [](const struct dirent **a, const struct dirent **b) -> int { return true; });
//#define SCAN_DIR_ERROR (-1)
//    if (count == SCAN_DIR_ERROR)
//        return {};
//
//    std::vector<std::string> names(count);
//
//    for (int i = 0; i < count; i++) {
//        struct dirent *ent = entries[i];
//
//        names[i] = std::string{ent->d_name};
//
//        free(ent);
//    }
//    free(entries);
//
//    return names;
//}
std::vector<std::string> get_dir_entries(std::string dir) {
    std::vector<std::string> entries;
    for (const std::filesystem::directory_entry &entry: std::filesystem::directory_iterator(dir)) {
        entries.push_back(entry.path().filename().string());
    }
    return entries;
}

std::string read_file(char* path) {
    return {};
}

void remove_file(char* path) {

}

void create_new_file(char* path) {

}

void append_to_file(char* path, char* data) {

}