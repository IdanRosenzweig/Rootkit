//
// Created by idan on 12/26/23.
//

#include "../../basic/process/basic_process_access.h"
#include "../../basic/fs/basic_fs_access.h"

#include "../error_codes.h"

#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

std::vector<int> find_all_procs_pids() {
    std::vector<int> pids;
    for (const std::string& entry : get_dir_entries("/proc")) {
        int pid = strtol(entry.c_str(), nullptr, 10);
        if (pid == 0)
            continue;

        pids.push_back(pid);
    }

    return pids;
}

int kill_proc(int pid) {
    return kill(pid, SIGKILL);
}

int start_proc(const char *exec_path, char *const args[], char *const env[]) {
    int pid = execve(exec_path, args, env);
    if (pid == 0) { // the new child process_access that was created
        execve(exec_path, args, env);
        exit(0); // in case this is reached
    }
    return pid;
    // else // parent process_access
}

int start_proc(char *exec_path) {
    char *args[] = {exec_path, NULL};
    return start_proc(exec_path, args, environ);
}

std::string get_proc_exec(int pid) {
    try {
        return follow_symlink("/proc/" + std::to_string(pid) + "/exe");
    } catch (...) {
        return "";
    }
}

std::string get_proc_cwd(int pid) {
    try {
        return follow_symlink("/proc/" + std::to_string(pid) + "/cwd");
    } catch (...) {
        return "";
    }
}

std::vector<std::string> get_proc_argument_variables(int pid) {
    std::string path{"/proc/" + std::to_string(pid) + "/cmdline"};

    int fd = open(path.c_str(), O_RDONLY);
    if (fd == OPEN_ERROR)
        return {};

    if (lseek(fd, 0, SEEK_SET) != 0)
        return {};

    std::vector<std::string> vars;
    std::string var;
    char ch = '\x00';
    while (read(fd, (void*) &ch, 1) == 1) {
        if (ch == '\x00') { // end of the argument
            vars.push_back(var);
            var.clear();
        } else {
            var += ch;
        }
    }

    return vars;
}


