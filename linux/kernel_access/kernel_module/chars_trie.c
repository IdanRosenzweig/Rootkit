#include <linux/slab.h>
#include <linux/module.h>
#include <linux/delay.h>

struct node {
    int marked;

    struct node *children[128 - 1]; // all 128 ASCII besides NULL byte
    int child_count;
};

struct node **get_child_holder(struct node *node, char val) {
    int in = val;
    if (in < 0 || 126 < in) {
        return NULL;
    }
    return (struct node **) &(node->children[in]);
}

int isMarked(struct node *node) {
    return node->marked;
}

void setMarked(struct node *node, int mark) {
    node->marked = mark;
}

struct node *get_child(struct node *node, char val) {
    int in = val;
    if (in < 0 || 126 < in) {
        return NULL;
    }
    return node->children[in];
//    return *get_child_holder(node, val);
}

int has_child(struct node *node, char val) {
    return get_child(node, val) != 0;
}

int count_children(struct node *node) {
    return node->child_count;
}

struct node *create_child(struct node *node, char val) {
    struct node **holder = get_child_holder(node, val);

    if (*holder != 0) // child already exists
        return *holder;

    int sz = sizeof(struct node);

    struct node *ptr = kmalloc(sz, GFP_NOWAIT);

    memset((void *) ptr, '\x00', sz);
    *holder = ptr;
    node->child_count++;

    return ptr;
}

void remove_all_children(struct node *node) {
    if (node == 0) return;

    for (int i = 0; i < 26; i++) {
        struct node *child = node->children[i];

        if (child == 0) // child doesn't exist
            return;

        remove_all_children(child);
        kfree(child);
    }
}

void remove_child(struct node *node, char val) {
    struct node **child = get_child_holder(node, val);

    if (*child == 0) // no such child
        return;

    remove_all_children(node);
    kfree(*child);

    *child = 0;
    node->child_count--;
}

struct node *search(struct node *node, const char *str) {
    if (node == 0) return 0;

    struct node *curr_node = node;

    for (int i = 0; str[i] != '\x00'; i++) {
        char c = str[i];

        struct node *child = get_child(curr_node, c);
        if (child == 0) // word doesn't exists
            return 0;

        curr_node = child;
    }

    return curr_node;
}


struct trie {
    struct node root;
};

struct node* get_root(struct trie *trie) {
    return &trie->root;
}

void add_word(struct trie *trie, const char *str) {
    if (str[0] == '\x00')
        return;

    struct node *curr_node = &trie->root;
    for (int i = 0; str[i] != '\x00'; i++) {
        char c = str[i];

        struct node *child = get_child(curr_node, c);
        if (child == 0) // node should be added
            child = create_child(curr_node, c);

        curr_node = child;
    }
    setMarked(curr_node, 1);
}

void remove_word(struct trie *trie, const char *str) {
    if (str[0] == '\x00') return;

    // is there another word with some common prefix as str?
    struct node *common_substr_node = &trie->root; // the node representing the prefix
    char common_substr_val = str[0]; // the value related to str in that node, which can be removed

    struct node *curr_node = &trie->root;
    for (int i = 0; str[i] != '\x00'; i++) {
        char c = str[i];

        struct node *child = get_child(curr_node, c);
        if (child == 0) // word doesn't exists
            return;

        if (isMarked(curr_node) || count_children(curr_node) > 1) {
            common_substr_node = curr_node;
            common_substr_val = c;
        }

        curr_node = child;
    }

    if (!isMarked(curr_node)) // word doesn't exists
        return;

    // remove the highest ancestor which only contributes to the removed str
    remove_child(common_substr_node, common_substr_val);
}

// does the trie contains this word
int contains_word(struct trie *trie, const char *str) {
    struct node *node = search(&trie->root, str);
    return node != 0 && isMarked(node);
}

// does the trie contains some word which has this prefix
int is_prefix(struct trie *trie, const char *str) {
    struct node *node = search(&trie->root, str);
    return node != 0;
}

int node_contains_prefix(struct node* node, const char *str) {
    if (str[0] == '\x00' || node == 0)
        return 0;

    struct node *curr_node = node;

    for (int i = 0; str[i] != '\x00'; i++) {
        char c = str[i];
        struct node *child = get_child(curr_node, c);
        if (child == 0)
            return 0;

        curr_node = child;
        if (isMarked(curr_node))
            return 1;
    }

    return 0;
}
// does the trie contains some word which is a prefix of str
int contains_prefix(struct trie *trie, const char *str) {
    return node_contains_prefix(&trie->root, str);
}

struct trie *create_trie(void) {
    int sz = sizeof(struct trie);
    struct trie *ptr = kmalloc(sz, GFP_KERNEL);
    memset((void *) ptr, '\x00', sz);
    return ptr;
}

void free_trie(struct trie *trie) {
    kfree(trie);
}