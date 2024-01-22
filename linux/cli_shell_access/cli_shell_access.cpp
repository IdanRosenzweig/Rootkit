//
// Created by idan on 12/31/23.
//

#include "../../basic/shell/basic_cli_shell_access.h"

#include "../error_codes.h"

std::string execute_cli_shell_command(std::string command) {
    FILE* pipe = popen(command.c_str(), "r");
    if (pipe == POPEN_ERROR) throw;

    std::string output;
    char ch = '\x00';
    while (fread((void*) &ch, sizeof(ch), 1, pipe) == 1) {
        output += ch;
    }

    if (pclose(pipe) == PCLOSE_ERROR) throw;

    return output;
}
