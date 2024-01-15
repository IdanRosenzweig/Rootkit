//
// Created by idan on 1/12/24.
//

#ifndef ROOTKIT_CHARS_TRIE_H
#define ROOTKIT_CHARS_TRIE_H

struct node;

struct node **get_child_holder(struct node *node, char val);

int isMarked(struct node *node);

void setMarked(struct node *node, int mark);

struct node *get_child(struct node *node, char val);

int has_child(struct node *node, char val);

int count_children(struct node *node);

struct node *create_child(struct node *node, char val);

void remove_all_children(struct node *node);

void remove_child(struct node *node, char val);

struct node *search(struct node* node, const char *str);


struct trie;

struct node* get_root(struct trie *trie);

void add_word(struct trie *trie, const char *str);

void remove_word(struct trie *trie, const char *str);

// does the trie contains this word
int contains_word(struct trie *trie, const char *str);

// does the trie contains some word which has this prefix
int is_prefix(struct trie *trie, const char *str);

// is there prefix starting from this node
int node_contains_prefix(struct node *node, const char *str);

// does the trie contains some word which is a prefix of str
int contains_prefix(struct trie *trie, const char *str);

struct trie* create_trie(void);

void free_trie(struct trie*);

#endif //ROOTKIT_CHARS_TRIE_H
