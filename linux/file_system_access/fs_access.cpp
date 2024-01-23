#include "../../basic/fs/basic_fs_access.h"

#include "../error_codes.h"

#include <filesystem>

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

std::string follow_symlink(std::string path) {
    std::filesystem::path p = path;
    while (std::filesystem::is_symlink(p))
        p = std::filesystem::read_symlink(p);

    return std::string{p};
}

std::vector<std::string> get_dir_entries(std::string dir) {
    std::vector<std::string> entries;
    for (const std::filesystem::directory_entry &entry: std::filesystem::directory_iterator(dir)) {
        entries.push_back(entry.path().filename().string());
    }
    return entries;
}

std::string read_file(char* path) {
    int fd = open(path, O_RDONLY);
    if (fd == OPEN_ERROR)
        return {};

    struct stat stat;
    if (fstat(fd, &stat) == FSTAT_ERROR)
        return {};
    size_t filesz = stat.st_size;

    std::string str(filesz, '\x00');

    lseek(fd, SEEK_SET, 0);
    read(fd, str.data(), filesz);

    if (close(fd) == CLOSE_ERROR)
        throw;

    return str;
}

void remove_file(char* path) {
    unlink(path);
}

void create_new_file(char* path) {
    creat(path, 0);
}

void append_to_file(char* path, char* buff, int count) {
    FILE* file = fopen(path, "a");
    if (file == nullptr)
        return;

    fwrite(buff, count, 1, file);

    fclose(file);
}