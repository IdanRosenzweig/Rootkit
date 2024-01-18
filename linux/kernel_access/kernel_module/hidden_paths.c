//
// Created by idan on 1/14/24.
//

#include "hidden_paths.h"

#include "chars_trie.h"

static struct trie *trie = 0;

void initialize_trie(void) {
    trie = create_trie();
}

struct node* get_hidden_paths_root_node(void) {
    return get_root(trie);
}
void add_hidden_path(const char* path) {
    if (trie != 0)
        add_word(trie, path);
}
void remove_hidden_path(const char*path) {
    if (trie != 0)
        remove_word(trie, path);
}
int is_path_hidden(const char *path) {
    if (trie != 0)
        return contains_prefix(trie, path);
    else return 0;
}
int is_path_arr_hidden(const char *path_arr[], int len) {
    if (trie != 0) {
        struct node *s = get_root(trie);

        int i = 0;
        while (s != 0 && i < len) {
            if (node_contains_prefix(s, path_arr[i])) return 1; // found

            s = search(s, path_arr[i]);

            i++;
        }

        return 0;
    }
    else return 0;
}

void finish_trie(void) {
    if (trie != 0)
        free_trie(trie);
}
