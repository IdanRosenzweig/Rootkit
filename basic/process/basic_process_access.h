#ifndef ROOTKIT_BASIC_PROCESS_ACCESS_H
#define ROOTKIT_BASIC_PROCESS_ACCESS_H

#include <vector>
#include <string>


std::vector<int> find_all_procs_pids();

int kill_proc(int pid);

int start_proc(const char *exec_path, char *const args[], char *const env[]);

int start_proc(char *exec_path);

std::string get_proc_exec(int pid);

std::string get_proc_cwd(int pid);

std::vector<std::string> get_proc_argument_variables(int pid);


#endif //ROOTKIT_BASIC_PROCESS_ACCESS_H
